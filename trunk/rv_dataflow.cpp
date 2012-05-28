/*
 * rv_dataflow.cpp
 *
 *  Created on: May 21, 2011
 *      Author: edima
 */

#include "rv_macros.h"
#include <limits.h>
#include <set>
#include <stack>
#include <sstream>
#include <algorithm>
#include "ctool/PrintTraversal.h"
#include "ctool/stemnt.h"
#include "ctool/symbol.h"
#include "ctool/express.h"
#include "rv_funcnode.h"
#include "rv_etc.h"
#include "rv_walk.h"
#include "rv_parse.h"
#include "rv_dataflow.h"

#define RV_SECTION  RV_DBG_GRAPH

using namespace std;


template<> const std::string RVSetVertexInfo<Symbol*>::ms_typeName = "std::set<Symbol*>";
template<> const std::string RVSetVertexInfo<Constant*>::ms_typeName = "std::set<Constant*>";
template<> const std::string RVSetVertexInfo<Expression*>::ms_typeName = "std::set<const Expression*>";


  /********************************************************************/
 /*                    class ArtificialNodeExpression                */
/********************************************************************/
///<summary>
///An artificial expression for auxiliary dataflow graph nodes.
///enum RVDummyNodeType defines the types of the auxiliary nodes.
///</summary>
struct ArtificialNodeExpression : public Expression {
	RVDummyNodeType       m_type;
	unsigned long         m_sumcheck;

public:
	Statement            *m_owner;
	Symbol               *m_name;
    Expression           *m_attached;

	ArtificialNodeExpression(RVDummyNodeType type, Statement *owner, Symbol* name, Expression *attached)
	  : Expression(ET_VoidExpr, Location(0, 0, "dummy_file")),
	    m_type(type), m_owner(owner), m_name(name), m_attached(attached)
	{
		reassignType(type);
	}

	virtual ~ArtificialNodeExpression() {
		if (m_type == DN_EndLoop && m_name != NULL ) {
			RVDELETE( m_name );
		}
		m_sumcheck = ~0L;
	}

	virtual void accept(Traversal *t) {}

	virtual Expression *dup0() const {
		Symbol *dup = NULL;
		if (m_name != NULL) {
			dup = new Symbol();
			dup->name  = m_name->name;
			dup->entry = m_name->entry;
		}
		return new ArtificialNodeExpression(m_type, m_owner->dup(), dup, m_attached->dup());
	}

	static string expressionToString(Expression *id) {
		if (isArtificialNode(id))
		    return static_cast<const ArtificialNodeExpression*>(id)->toString();
	    ostringstream str;
	    PrintTraversal pt(str, false);
	    id->accept(&pt);
	    return str.str();
	}


	string toString(void) const {
		switch(m_type) {
			case DN_Start:     return "DN_Start";
			case DN_Finish:    return "DN_Finish";
			case DN_Init:
			{
				string s(m_name->name + ":=");
				if (m_attached != NULL)
					s.append(expressionToString(m_attached));
				return s;
			}
			case DN_EndLoop:   return string("End of ") + m_name->name + " loop";
			case DN_RetVal:    return string("return ") + expressionToString(m_attached);
			case DN_Connector: return "DN_Connector";
			case DN_Label:
			{
				string s("DN_Label_");
				if (m_name != NULL) s.append(m_name->name);
				return s;
			}
			case DN_LastDummyNodeType: break;
		}

		fatal_error("ArtificialNodeExpression::toString() : unsupported m_type");
		return "";
	}

	bool isValid(void) const {
		return (unsigned)m_type < DN_LastDummyNodeType &&
		       m_sumcheck == calculateSumCheck();
	}

	RVDummyNodeType getType(void) const { return m_type; }

	void reassignType(RVDummyNodeType type) {
		m_type = type;
		m_sumcheck = calculateSumCheck();
	}

private:
	unsigned long calculateSumCheck(void) const {
		static const unsigned long magicWord = ~(ULONG_MAX/3);
		union { const ArtificialNodeExpression *ptrV;
		        unsigned long                   ulV;
		} converter;
		converter.ptrV = this;
		return magicWord ^ converter.ulV ^ m_type;
	}
};


bool isArtificialNode(const Expression *e) {
	if (e == NULL || e->etype != ET_VoidExpr)
		return false;
	const ArtificialNodeExpression *node = static_cast<const ArtificialNodeExpression*>(e);
	return node->isValid();
}

bool isArtificialNodeOfType(const Expression *e, RVDummyNodeType type) {
	if (!isArtificialNode(e))
		return false;
	const ArtificialNodeExpression *node = static_cast<const ArtificialNodeExpression*>(e);
	return node->getType() == type;
}



struct FuncArg {
	Expression *m_function;
	int         m_iArg;

	FuncArg(Expression *f = NULL, int argIdx = -1)
	  : m_function(f), m_iArg(argIdx) {
	}
};


typedef stack<Expression*> RVExprStack;

class RVPopper {
public:
	RVPopper(RVExprStack* &rStk, const RVExprStack::value_type& elem)
	  : m_pStack(rStk), m_rStk(rStk) {
		if (rStk == NULL) {
			m_pStack = rStk = new RVExprStack;
			m_delete = RVPopper_Delete;
		}
		else
			m_delete = RVPopper_DontDelete;
		m_pStack->push(elem);
	}

	~RVPopper() { pop(); }

	void pop(void) {
		switch(m_delete) {
		case RVPopper_DontDelete: m_pStack->pop(); break;
		case RVPopper_Delete:     delete m_pStack; m_rStk = NULL; break;
		case RVPopper_Disposed:   return;
		default:                  fatal_error("RVPopper::pop() - unsupported m_delete.", false);
		}
		m_delete = RVPopper_Disposed;
	}

	bool wasEmpty(void) const {	return m_delete || m_pStack->size() == 1; }

private:
	RVExprStack*       m_pStack;
	RVExprStack*      &m_rStk;
	enum { RVPopper_DontDelete, RVPopper_Delete, RVPopper_Disposed} m_delete;
};


  /********************************************************************/
 /*                    class RVDataflowGraphBuilderIntrinsic         */
/********************************************************************/
///<summary>
///The supermost class for every dataflow graph builder.
///It creates two nodes which are present in every graph: DN_Start and DN_Finish.
///</summary>
abstract class RVDataflowGraphBuilderIntrinsic {
protected:
	typedef set<Expression*>          Latest;

	RVDataflowGraphBuilderIntrinsic(RVDataflowGraph& graph,
                                    bool backward,
                                    bool cover_branches)
	  : m_after(NULL),  m_graph(graph),
	    m_revert(backward), m_coverBranches(cover_branches)
	{
		graph.setDefaultProperty(RVDataflowGraph::RV_Constants,
				                 RVSetVertexInfo<Constant*>(m_constants));
		m_start = appendDummyVertex(DN_Start);
		Latest start(m_latest);
		m_finish = appendDummyVertex(DN_Finish);
		m_latest.swap(start);
	}

	virtual ~RVDataflowGraphBuilderIntrinsic() {
	}

	void postBuild(bool successfulBuild) {
		RVDataflowGraph::Vertices startCallees, endCallers;
		m_graph.getCallees(m_start, startCallees);
		m_graph.getCallers(m_finish, endCallers);
		assert((startCallees.size() > 1) == (endCallers.size() > 1));
		if (startCallees.size() > 1)
			m_graph.remove_edge(m_start, m_finish);
		if (m_coverBranches)
			coverBranches();
		if (m_revert)
			revertGraph();
		m_graph.setSuccessfullyBuilt(successfulBuild);
	}

	void revertGraph(void) {
		m_graph.reverse();
		m_start->reassignType(DN_Finish);
		m_finish->reassignType(DN_Start);
		swap(m_start, m_finish);
	}

	void coverBranches(void) {
		RVDataflowGraph::Vertices verts;
		m_graph.getVertices(verts);
		RVDataflowGraph::Vertices::iterator it = verts.begin();
		for(; it != verts.end(); ++it) {
            Expression *condExpr = *it;
            if (m_graph.outdegree(condExpr) <= 1)
                continue;

			set<int> coveredNodeIndices;
			m_graph.getNodesTillCommonAncestor(condExpr, coveredNodeIndices);
			set<int>::const_iterator iit = coveredNodeIndices.begin();
			for (; iit != coveredNodeIndices.end(); ++iit)
				m_graph.addInfluent(*iit, condExpr);
		}
	}

	void shiftFinishToTheEnd(void) {
		m_graph.reincarnate(m_finish);
	}

	void encountered(Expression *e) {
		m_after = NULL;
        if (e == NULL)
            return;
		connectTo(e, m_latest);
		m_graph.setProperty(e, RVDataflowGraph::RV_Constants,
				            RVSetVertexInfo<Constant*>(m_constants));
		if (!m_funcargs.empty())
			m_graph.setProperty(e, RVDataflowGraph::RV_FuncArg,
					            RVTypedVertexInfo<FuncArg>(m_funcargs.top()));
		m_latest.clear();
		m_latest.insert(e);
	}

	ArtificialNodeExpression *appendDummyVertex(RVDummyNodeType type = DN_Connector,
												Statement *owner = NULL,
                                                Symbol *name = NULL,
                                                Expression *attached = NULL) {
		ArtificialNodeExpression *artificial = new ArtificialNodeExpression(type, owner, name, attached);
		encountered(artificial);
		return artificial;
	}

	void connectTo(Expression *to, const Latest& what) {
		for (Latest::iterator it = what.begin(); it != what.end(); ++it)
			m_graph.edge(*it, to);
	}

	Latest                    m_latest;
    ArtificialNodeExpression *m_finish, *m_start;
    set<Constant*>            m_constants;
    Expression               *m_after;
    stack<FuncArg>            m_funcargs;
	RVDataflowGraph          &m_graph;
	bool                      m_revert, m_coverBranches;
};





  /********************************************************************/
 /*                    class RVIntraProcDataflowGraphBuilder         */
/********************************************************************/
///<summary>
///Builds a dataflow graph for a given block (usually a function body)
///without referencing called routines.
///<summary>
class RVIntraProcDataflowGraphBuilder :
	protected RVWalk,
	private RVDataflowGraphBuilderIntrinsic
{
	typedef map<Latest, Symbol*>      GotoMap;
	typedef map<string, Expression*>  LabelMap;

public:
	RVIntraProcDataflowGraphBuilder(Statement *b,
			                        bool backward = false,
			                        bool coverBranches = false)
	  : RVWalk(true),
	    RVDataflowGraphBuilderIntrinsic(*new RVDataflowGraph, backward, coverBranches),
	    m_defaultExists(false),
	    m_block(b), m_tempVarCounter(0),
	    m_toBeAssigned(false), m_pWrapper(NULL)
	{}

	virtual ~RVIntraProcDataflowGraphBuilder() {}

	virtual RVDataflowGraph *build(void) {
		bool ret = process(m_block) && finalSteps();
		shiftFinishToTheEnd();
		postBuild(ret);
		return &m_graph;
	}

protected:
    virtual bool process(Expression* s0p) {
    	static const char *where_ = "RVDataflowGraphBuilder::process(Expression*)";
    	CHK_NULL(where_);
    	m_after = s0p;
    	RVPopper popper(m_pWrapper, s0p);

		switch (s0p->etype) {
		case ET_VoidExpr:
			break;

		case ET_Constant:
			m_constants.insert(static_cast<Constant*>(s0p));
			break;

		case ET_Variable:
			break;

		case ET_FunctionCall: // f(x, y)  ==>  $1 = f(x, y); m_after = $1  /*if f is not void*/
		{                     // f(x, y)  ==>  f(x, y); m_after = NULL;    /*if f is void*/
			FunctionCall *sp = static_cast<FunctionCall*>(s0p), *afterSp = sp;
			if (!processFuncCallArgs(sp->function, sp->args, &afterSp))
				return RVBoolStatus(false, DBG_INFO, DBG);
			RVLocalBackup<bool> oldToBeAssigned(m_toBeAssigned, true);
			if (try_replace(&sp->function) && !process(sp->function))
				return RVBoolStatus(false, DBG_INFO, DBG);
			if (m_after != sp->function) {
				if (afterSp == sp)
					afterSp = duplicate(sp);
				deleteAndReplace(afterSp->function, m_after, sp->function);
			}
			if( is_basetype(real_type(sp->type, where_), BT_Void) || popper.wasEmpty())
				encountered(afterSp);
			else
				m_after = allocTempAssignment(afterSp);
			break;
		}

		case ET_AssignExpr:
		case ET_RelExpr:
			fatal_error("RVDataflowGraphBuilder::process(Expression*) - ET_AssignExpr or ET_RelExpr");
			break;

		case ET_UnaryExpr:
			// ++(expr)   ==>  ++(expr); m_after = expr
			// (expr)++   ==>  $1 = expr; ++(expr); m_after = $1
			// else       ==>  no change
		{
			UnaryExpr *sp = static_cast<UnaryExpr*>(s0p);
			RVLocalBackup<bool> oldToBeAssigned(m_toBeAssigned, true);
			if (try_replace(&sp->_operand) && !process(sp->_operand))
				return RVBoolStatus(false, DBG_INFO, DBG);

			Expression *operand = m_after;
			switch(sp->uOp) {
			case UO_Plus:   case UO_Minus:
			case UO_BitNot: case UO_Not:
			case UO_AddrOf: case UO_Deref:
				m_after = replaceIfNeed(sp, operand, &UnaryExpr::_operand);
				break;
			case UO_PreInc: case UO_PreDec:
				sp = replaceIfNeed(sp, operand, &UnaryExpr::_operand);
				encountered(sp);
				m_after = operand;
				break;
			case UO_PostInc:
			case UO_PostDec:
				{
					Variable *tmpvar = popper.wasEmpty()?
							NULL : allocTempAssignment(operand);
					UnaryExpr *clone = duplicate(sp);
					deleteAndReplace(clone->_operand, operand, sp->_operand);
					makePreUnaryOp(clone->uOp); // UO_PostInc => UO_PreInc, UO_PostDec => UO_PreDec
					encountered(clone);
					m_after = tmpvar;
					break;
				}
			default:
				fatal_error("RVIntraProcDataflowGraphBuilder::process(Expression*) : unsupported uOp", false);
			}

			break;
		}

		case ET_BinaryExpr:
		    if( !process_binary( static_cast<BinaryExpr*>(s0p ) ) )
			    return RVBoolStatus(false, DBG_INFO, DBG);
		    break;

		case ET_TrinaryExpr:  // x ? y : z  ==> $1; x? $1 = y : $1 = z; m_after = $1
		{                     //            ==> x ? y : z   /*if the type of the expression is void or this is a stand-alone expression*/
			TrinaryExpr *sp = static_cast<TrinaryExpr*>(s0p);
			Variable *result = is_basetype(sp->type, BT_Void) || !m_toBeAssigned ?
					          NULL : allocTempAssignment(NULL, sp);
			if(sp->condExpr() != NULL && try_replace(&sp->_condExpr) && !process(sp->condExpr()))
				return RVBoolStatus(false, DBG_INFO, DBG);
			encountered(m_after);
			Latest store(m_latest);
			if(sp->trueExpr() != NULL && try_replace(&sp->_trueExpr) && !process(sp->trueExpr()))
				return RVBoolStatus(false, DBG_INFO, DBG);
			if (result != NULL)
				insertTempAssignment(result, m_after, sp->trueExpr()->location);
			store.swap(m_latest);
			if(sp->falseExpr() != NULL && try_replace(&sp->_falseExpr) && !process(sp->falseExpr()))
				return RVBoolStatus(false, DBG_INFO, DBG);
			if (result != NULL)
				insertTempAssignment(result, m_after, sp->falseExpr()->location);
			appendToLatest(store);
			m_after = result;
			break;
		}

		case ET_CastExpr:             // (type) x
		{
			CastExpr *sp = static_cast<CastExpr*>(s0p);
			if (try_replace(&sp->expr) && !process(sp->expr))
				return RVBoolStatus(false, DBG_INFO, DBG);

			m_after = replaceIfNeed(sp, m_after, &CastExpr::expr);
			break;
		}

		case ET_SizeofExpr:           // sizeof(type) -or- sizeof(expr)
		{
			SizeofExpr *sp = static_cast<SizeofExpr*>(s0p );
			if( !go_sizeof(sp) )
				return RVBoolStatus(false, DBG_INFO, DBG);
			m_after = replaceIfNeed(sp, m_after, &SizeofExpr::expr);
			break;
		}

		case ET_IndexExpr:             // x[y]...[]  ==> $1 = x + y; m_after = *$1
		{
			IndexExpr *sp = static_cast<IndexExpr*>(s0p);
			RVLocalBackup<bool> oldToBeAssigned(m_toBeAssigned, true);
			if (try_replace(&sp->_subscript) && !process(sp->_subscript))
				return RVBoolStatus(false, DBG_INFO, DBG);
			Expression *subscript = m_after;
			if (try_replace(&sp->array) && !process(sp->array))
				return RVBoolStatus(false, DBG_INFO, DBG);
			Expression *array = m_after;
			BinaryExpr *offset =
				new BinaryExpr(BO_Plus, array->dup(), subscript->dup(), sp->location);
			offset->type = array->type;
			UnaryExpr *deref =
				new UnaryExpr(UO_Deref, allocTempAssignment(offset)->dup(), sp->location);
			deref->type = sp->type;
			replace(deref);
			break;
		}

		default:
			fatal_error("RVIntraProcDataflowGraphBuilder::process(Expression*) : unsupported s0p->etype", false);
			return RVWalk::process(s0p);
		}

		return true;
	}

    virtual bool process_binary(BinaryExpr* s0p)
    {
      CHK_NULL("RVDataflowGraphBuilder::process_binary()");

      switch( s0p->op() )
      {
        case BO_Assign: {
        	RVLocalBackup<bool> oldToBeAssigned(m_toBeAssigned, true);
    		if (try_replace(&s0p->_rightExpr) && !process(s0p->rightExpr()))
    		    return RVBoolStatus(false, DBG_INFO, DBG);
    		Expression *result = m_after;
        	if (try_replace(&s0p->_leftExpr) && !process(s0p->leftExpr()))
    			return RVBoolStatus(false, DBG_INFO, DBG);
    		//if (isTempVariable(result) && m_after->etype == ET_Variable)
    		//	replaceAssignmentIntoTempVar(result, m_after);
    		//else
    		if (m_after != s0p->leftExpr() || result != s0p->rightExpr()) {
    			BinaryExpr *clone = duplicate(s0p);
    			deleteAndReplace(clone->_leftExpr, m_after, s0p->leftExpr());
    			deleteAndReplace(clone->_rightExpr, result, s0p->rightExpr());
    			s0p = clone;
    		}
   			encountered(s0p);
   			m_after = s0p->leftExpr();
      	    break;
        }
        case BO_And:
    	case BO_Or:
    	{
    		RVLocalBackup<bool> oldToBeAssigned(m_toBeAssigned);
    		if (!m_toBeAssigned && m_pWrapper->size() > 1)
    			m_toBeAssigned = true;
    		if (try_replace(&s0p->_leftExpr) && !process(s0p->leftExpr()))
    			return RVBoolStatus(false, DBG_INFO, DBG);
    		Variable *tmpVar = NULL;
    		if (m_toBeAssigned)
    		    tmpVar = allocTempAssignment(m_after);
    		else
    		    encountered(m_after);
    		Latest store(m_latest);
    		if (try_replace(&s0p->_rightExpr) && !process(s0p->rightExpr()))
    		    return RVBoolStatus(false, DBG_INFO, DBG);
    		if (tmpVar != NULL)
    			insertTempAssignment(tmpVar, m_after, s0p->location);
    		else
    			encountered(m_after);
    		appendToLatest(store);
    		m_after = tmpVar;
    		break;
    	}

    	case BO_Member:
    	case BO_PtrMember:  //m_after->
            REP_PROC( _leftExpr );
		    m_after = replaceIfNeed(s0p, m_after, &BinaryExpr::_leftExpr);
            break;

    	default: {
   		  REP_PROC( _leftExpr );
   		  Expression *leftExpr = m_after;
   		  REP_PROC( _rightExpr );
   		  if (leftExpr != s0p->leftExpr() || m_after != s0p->rightExpr()) {
   			  BinaryExpr *clone = duplicate(s0p);
   			  deleteAndReplace(clone->_leftExpr, leftExpr, s0p->leftExpr());
   			  deleteAndReplace(clone->_rightExpr, m_after, s0p->rightExpr());
   			  m_after = clone;
   		  }
   		  else
   			  m_after = s0p;
    	}
      }

      return true;
    }

    virtual bool process(Statement* s0p)
    {
    	CHK_NULL("RVDataflowGraphBuilder::process(Expression*)");
    	bool ret = true;
    	RVLocalBackup<RVExprStack*> backup(m_pWrapper, NULL);

    	PROC( labels );
    	switch( s0p->type )
    	{
    	case ST_ExpressionStemnt: {
    		RETYPE( ExpressionStemnt );
    		TRY_REP_PROC( expression );
    		encounterIfSenseful(m_after);
    		break;
    	}

    	case ST_IfStemnt: {
    		RETYPE( IfStemnt );
    		RVPopper popper(m_pWrapper, NULL); // to make sure the expression stack won't be empty
   			TRY_REP_PROC( cond );
   			popper.pop();
   			encountered(m_after);
    		Latest store(m_latest);
    		TRY_REP_PROC( thenBlk );
    		encounterIfSenseful(m_after);
    		store.swap(m_latest);
    		TRY_REP_PROC( elseBlk );
    		encounterIfSenseful(m_after);
    		appendToLatest(store);
    		break;
    	}

    	case ST_SwitchStemnt: {
    		RETYPE( SwitchStemnt );
    		RVPopper popper(m_pWrapper, NULL); // to make sure the expression stack won't be empty
    		TRY_REP_PROC( cond );
    		popper.pop();
    		encountered(m_after);
    		Latest store(m_latest);
    		Latest prevSwitchStart, prevBreaks, prevContinues;
    		prevSwitchStart.swap(m_switchStart);
    		prevBreaks.swap(m_breaks);
    		prevContinues.swap(m_continues);
    		bool prevDefaultExists = m_defaultExists;
    		TRY_REP_PROC( block );
    		assert(m_after == NULL);
    		encounterIfSenseful(m_after); //should have no effect
    		if (!m_defaultExists)
    			appendToLatest(store);
    		m_defaultExists = prevDefaultExists;
    		Expression *dummy = appendDummyVertex(DN_Connector, s0p);
    		connectTo(dummy, m_breaks);
    		//Restoring:
    		prevBreaks.swap(m_breaks);
    		prevSwitchStart.swap(m_switchStart);
    		prevContinues.swap(m_continues); // continue in switch{...} ?
    		break;
    	}

    	case ST_ForStemnt: {
        	RETYPE( ForStemnt );
    		TRY_REP_PROC( init );
    		encounterIfSenseful(m_after);
    		Expression *preCond = appendDummyVertex(DN_Connector, s0p);
    		RVPopper popper(m_pWrapper, NULL); // to make sure the expression stack won't be empty
    		TRY_REP_PROC( cond );
    		encountered(m_after);
    		popper.pop();
    		//Backing up:
    		Latest prevBreaks, prevContinues, postCond(m_latest);
    		prevBreaks.swap(m_breaks);
    		prevContinues.swap(m_continues);
    		TRY_REP_PROC( block );
    		encounterIfSenseful(m_after);
    		Expression *preIncr = appendDummyVertex(DN_Connector, s0p);
    		connectTo(preIncr, m_continues);
    		TRY_REP_PROC( incr );
    		encounterIfSenseful(m_after);
    		connectTo(preCond, m_latest);
    		m_latest.swap(postCond);
    		Expression *endLoop = appendEndOfLoop(s0p, "for");
    		connectTo(endLoop, m_breaks);
    		//Restoring:
    		prevBreaks.swap(m_breaks);
    		prevContinues.swap(m_continues);
    		break;
    	}

    	case ST_WhileStemnt: {
    		RETYPE( WhileStemnt );
    		Expression *preCond = appendDummyVertex(DN_Connector, s0p);
    		RVPopper popper(m_pWrapper, NULL); // to make sure the expression stack won't be empty
    		TRY_REP_PROC( cond );
    		encountered(m_after);
    		popper.pop();
    		//Backing up:
    		Latest prevBreaks, prevContinues, postCond(m_latest);
    		prevBreaks.swap(m_breaks);
    		prevContinues.swap(m_continues);
    		TRY_REP_PROC( block );
    		encounterIfSenseful(m_after);
    		connectTo(preCond, m_latest);
    		connectTo(preCond, m_continues);
    		m_latest.swap(postCond);
    		Expression *endLoop = appendEndOfLoop(s0p, "while");
    		connectTo(endLoop, m_breaks);
    		//Restoring:
    		prevBreaks.swap(m_breaks);
    		prevContinues.swap(m_continues);
    		break;
    	}

    	case ST_DoWhileStemnt: {
    		RETYPE( DoWhileStemnt );
    		Expression *preBody = appendDummyVertex(DN_Connector, s0p);
    		//Backing up:
    		Latest prevBreaks, prevContinues;
    		prevBreaks.swap(m_breaks);
    		prevContinues.swap(m_continues);
    		TRY_REP_PROC( block );
    		encounterIfSenseful(m_after);
    		Expression *preCond = appendDummyVertex(DN_Connector, s0p);
    		connectTo(preCond, m_continues);
    		RVPopper popper(m_pWrapper, NULL); // to make sure the expression stack won't be empty
    		TRY_REP_PROC( cond );
    		encountered(m_after);
    		popper.pop();
    		connectTo(preBody, m_latest);
    		Expression *endLoop = appendEndOfLoop(s0p, "do...while");
    		connectTo(endLoop, m_breaks);
    		//Restoring:
    		prevBreaks.swap(m_breaks);
    		prevContinues.swap(m_continues);
    		break;
    	}

    	case ST_ContinueStemnt:
        	m_continues.insert(m_latest.begin(), m_latest.end());
    		m_latest.clear();
    		break;

    	case ST_BreakStemnt:
    		m_breaks.insert(m_latest.begin(), m_latest.end());
    		m_latest.clear();
    		break;

    	case ST_GotoStemnt: {
    		RETYPE( GotoStemnt );
    		REP_PROC( dest );
    		m_gotoMap.insert(GotoMap::value_type(m_latest, static_cast<GotoStemnt*>(s0p)->dest));
    		m_latest.clear();
    		break;
    	}

    	case ST_ReturnStemnt: {
    		RETYPE( ReturnStemnt );
    		RVLocalBackup<bool> oldToBeAssigned(m_toBeAssigned, true);
    		TRY_REP_PROC( result );
    		if (m_after != NULL)
    			appendDummyVertex(DN_RetVal, s0p, NULL, m_after);
    		connectTo(m_finish, m_latest);
    		m_latest.clear();
    		break;
    	}

    	case ST_Block:
    		if( s0p->isFuncDef() ) {
    			RETYPE( FunctionDef );
    			if (DBG) rv_errstrm << "RVIntraProcDataflowGraphBuilder::processing " << s0p->FunctionName()->name << "\n";
    			if( decl_to_symbol )
    				REP_PROC( decl )
    			else
    				REP_PROC( decl->name );
    		}
    		ret = process_block( static_cast<Block*>(s0p) );
    		//DIMAXXX assert(m_after == NULL);
    		encounterIfSenseful(m_after); //should have no effect
    		break;

    	default:
    		ret = RVWalk::process(s0p);
    	}

    	return RVBoolStatus(ret, __FUNCTION__, DBG);
    }

    virtual bool process(Label* s0p)
    {
    	CHK_NULL("RVDataflowGraphBuilder::process(Label*)");
    	Expression *offspring = NULL;

    	switch( s0p->type )
    	{
    	case LT_Default:             // default:
    		if (!m_switchStart.empty()) {
    			m_defaultExists = true;
    		    offspring = appendDummyVertex();
    		    connectTo(offspring, m_switchStart);
    		}
    		break;

    	case LT_Case:                // case <expr>:
		    offspring = appendDummyVertex();
		    connectTo(offspring, m_switchStart);
    		REP_PROC( begin );
    		break;

    	case LT_CaseRange:           // case <expr> ... <expr>: (gcc extension)
		    offspring = appendDummyVertex();
		    connectTo(offspring, m_switchStart);
    		REP_PROC( begin );
    		REP_PROC( end );
    		break;

    	case LT_Goto:                 // A named label (goto destination).
    		if( decl_to_symbol )
    			REP_PROC( name );
		    offspring = appendDummyVertex(DN_Label, NULL, s0p->name);
		    m_labelExprs.insert(LabelMap::value_type(s0p->name->name, offspring));
    		break;

    	default:
    		if (DBG) {
				rv_errstrm << "Unable to walk Label: ";
				s0p->print(rv_errstrm, 0);
				rv_errstrm << " \n";
    		}
    		return false;
    	}

    	return true;
    }

    virtual bool process(Decl* s0p){
    	CHK_NULL("RVDataflowGraphBuilder::process(Decl*)");
    	if (s0p->name == NULL || s0p->initializer == NULL)
    		return RVWalk::process(s0p);

		ArtificialNodeExpression initExpr(DN_Init, NULL, NULL, NULL);
    	bool ret = RVWalk::process(s0p);

    	if (RVBoolStatus(ret, __FUNCTION__, DBG))
    		appendDummyVertex(DN_Init, NULL, s0p->name, m_after);
                //Utils::containsElem(m_latest, s0p->initializer)? NULL : s0p->initializer);

    	return ret;
    }
 
    virtual bool process(ExprVector& it)  { assert(false); return go(it); }
    virtual bool process(Symbol* it)      { return go(it); }
    virtual bool process(LabelVector& it) { return go(it); }
    virtual bool process(EnumDef* it)     { return true; }
    virtual bool process(StructDef* it)   { return true; }

private:
    bool processFuncCallArgs(Expression *function, ExprVector &args, FunctionCall** pCall) {
    	if (args.empty())
    		return true;
    	bool replaced = false;
    	FuncArg funcArg(function);
    	for (unsigned i = 0; i < args.size(); ++i) {
    		Expression* &rArg = (*pCall)->args.at(i);
    		funcArg.m_iArg = i;
    		if( !try_replace(&rArg) )
    			continue;
    		m_funcargs.push(funcArg);
    		bool result = process(rArg);
    		if (m_after != rArg) {
    			if (!replaced) {
    				*pCall = static_cast<FunctionCall*>((*pCall)->dup());
    				replaced = true;
    			}
    			deleteAndReplace((*pCall)->args.at(i), m_after, rArg);
    		}
    		encountered(m_after);
    		m_funcargs.pop();
    		if (!result)
    			return RVBoolStatus(false, DBG_INFO, DBG);
    	}
    	return true;
    }

    Variable *allocTempAssignment(Expression *result, Expression *prototype = NULL) {
    	Symbol *tmpvar = new Symbol();
    	tmpvar->name = Utils::itoa(m_tempVarCounter++).insert(0, 1, '$');

    	Decl* decl = new Decl(prototype? prototype->type : result->type);
    	decl->name = tmpvar->dup();
    	decl->initializer = result->dup();

    	SymEntry* entry = mk_vardecl(tmpvar->name, decl);
    	tmpvar->entry = entry;

		ArtificialNodeExpression initExpr(DN_Init, NULL, NULL, NULL);
   		appendDummyVertex(DN_Init, NULL, tmpvar, decl->initializer);

   		const Location& l = result? result->location :
   		                            (prototype? prototype->location : NoLocation);
   		Variable *newVar = new Variable(tmpvar, l);
    	m_graph.dischargeLater(decl);
    	m_graph.dischargeLater(entry);
    	m_graph.dischargeLater(newVar);
   		return newVar;
    }

    void insertTempAssignment(Variable *dest, Expression *result, const Location& l) {
    	AssignExpr *assignment =
    		new AssignExpr(AO_Equal, dest->dup(), result->dup(), l);
    	encountered(assignment);
    	m_graph.dischargeLater(assignment);
    }

    template <typename T, typename F>
    T* replaceIfNeed(T *srcPtr, F *newFldVal, F* T::*field) {
    	if (srcPtr->*field == newFldVal)
    		return srcPtr;
   		T* clone = duplicate(srcPtr);
   		deleteAndReplace(clone->*field, newFldVal, srcPtr->*field);
   		return clone;
    }

    template <typename T> void replace(T *ptr) {
    	m_graph.dischargeLater(ptr);
    	m_after = ptr;
    }

    template <typename T> T* duplicate(const T *src) {
    	T* clone = static_cast<T*>(src->dup());
    	m_graph.dischargeLater(clone);
    	return clone;
    }

    template <typename T>
    void deleteAndReplace(T* &field, const T* newPtr, const T *origPtr) {
    	if (newPtr != origPtr) {
    		delete field;
    		field = static_cast<T*>(newPtr->dup());
    	}
    }

    Expression *encounterIfSenseful(Expression *e) {
    	if (e != NULL && e->etype != ET_Variable && e->etype != ET_Constant)
    		encountered(e);
    	m_after = NULL;
    	return e;
    }

    static void makePreUnaryOp(UnaryOp &rOp) {
    	switch(rOp) {
    	case UO_PostInc: rOp = UO_PreInc; return;
    	case UO_PostDec: rOp = UO_PreDec; return;
    	default: return;
    	}
    }

    bool finalSteps(void) {
    	bool mismatch = false;

    	//1. Connect goto statements to the label nodes
    	GotoMap::iterator gotoit = m_gotoMap.begin();
    	for (; gotoit != m_gotoMap.end(); ++gotoit) {
    		LabelMap::iterator labelIt = m_labelExprs.find(gotoit->second->name);
    		if (labelIt != m_labelExprs.end())
    			connectTo(labelIt->second, gotoit->first);
    		else {
    			if (DBG)
    				endl(rv_errstrm << "RVDataflowGraphBuilder::finalSteps(): failed to locate goto's label "
    					        	<< gotoit->second->name);
    			mismatch = true;
    		}
    	}

    	//2. Connect the latest statements to the finish node (if the parsed block ended without a return statement):
    	connectTo(m_finish, m_latest);

    	//3. Eliminate connector and label nodes:
    	RVDataflowGraph::Vertices vertices;
    	m_graph.getVertices(vertices);
    	RVDataflowGraph::Vertices::iterator it = vertices.begin();
    	for (; it != vertices.end(); ++it) {
    		if (*it == NULL || !isArtificialNode(*it))
    			continue;
    		ArtificialNodeExpression *node = static_cast<ArtificialNodeExpression*>(*it);
    		if (node->getType() == DN_Connector || node->getType() == DN_Label) {
    			m_graph.collapseVertex(node);
    			RVDELETE( node );
    		}
    	}

    	return !mismatch;
    }

	void appendToLatest(const Latest& store) {
        m_latest.insert(store.begin(), store.end());
    }

	ArtificialNodeExpression *appendEndOfLoop(Statement *owner, const char *loopType) {
		Symbol *loopTypeSymb = new Symbol();
		loopTypeSymb->name.assign(loopType);
		return appendDummyVertex(DN_EndLoop, owner, loopTypeSymb, NULL);
	}

    bool                m_defaultExists; //true when switch() {... default:...} found
    Latest              m_switchStart;   // for switch(..){...}
    Latest              m_breaks;        // break; in loops and switch
    Latest              m_continues;     // continue; in loops and switch
    GotoMap             m_gotoMap;
    LabelMap            m_labelExprs;
    Statement          *m_block;
	int                 m_tempVarCounter;
	bool                m_toBeAssigned;
	RVExprStack        *m_pWrapper;
};






  /********************************************************************/
 /*               Implementation of class RVDataflowGraph            */
/********************************************************************/
const std::string RVDataflowGraph::RV_Constants("Constants");
const std::string RVDataflowGraph::RV_FuncArg("FuncArg");
const std::string RVDataflowGraph::RV_Influence("Influence");

string RVDataflowGraph::getDottyAttrsOfVertex(int idx,
											  std::string & label,
											  std::string & fontcolor,
											  std::string & color,
											  std::string & shape,
											  std::string & style,
											  std::string & fillcolor) const
{
    Expression *id = fromIndex(idx);
    if (id == NULL)
		return "";
    string name(RVIntGraph::getDottyAttrsOfVertex(idx, label, fontcolor, color, shape, style, fillcolor));
    label.assign(ArtificialNodeExpression::expressionToString(id));
    if (isArtificialNode(id)) {
    	shape.assign("pentagon");
    	fontcolor.assign(color.assign("grey"));
    }
    return name;
}

string RVDataflowGraph::getVertexLabel(int idx) const {
	string label, srak;
	getDottyAttrsOfVertex(idx, label, srak, srak, srak, srak, srak);
	ostringstream buf;
	buf << "#" << idx << ": " << label;
	return buf.str();
}

///<summary>
///Searches for an artificial node of the given type owned by <paramref name="owner" />
///</summary>
///<returns>the index if the node found; -1 otherwise</returns>
int RVDataflowGraph::findArtifNodeByTypeOwnedByStmt(RVDummyNodeType type,
			                                        const Statement *owner) const
{
	Vertices vertices;
	getVertices(vertices);
	vector<int> vertIndices;
	getReportedVertixIndices(vertIndices);
	assert(vertIndices.size() == vertices.size());
	vector<int>::iterator idxIt = vertIndices.begin();
	Vertices::iterator it = vertices.begin();
	for (; it != vertices.end(); ++it, ++idxIt)
		if (isArtificialNodeOfType(*it, type)) {
			const ArtificialNodeExpression *ae =
					static_cast<const ArtificialNodeExpression*>(*it);
			if (ae->m_owner == owner)
				return *idxIt;
		}

	return -1;
}

///<summary> Reverses the dataflow graph </summary>
void RVDataflowGraph::reverse(void) {
	RVIntGraph::reverse();
	m_reverse = !m_reverse;
}


set<Expression*> *RVDataflowGraph::accessInfluents(Expression *v) const {
	const RVVertexInfo& inf = getProperty(v, RV_Influence);
	set<Expression *> *pInluents = NULL;
	inf.getPtr(pInluents);
	return pInluents;
}

void RVDataflowGraph::addInfluent(int influencedIdx, Expression *influent) {
	set<Expression *> *pInluents = accessInfluents(fromIndex(influencedIdx));

	if (pInluents != NULL) {
		pInluents->insert(influent);
		return;
	}

	set<Expression *> influents;
	influents.insert(influent);
	RVIntGraphWData::setProperty(influencedIdx, RV_Influence,
   			                     RVSetVertexInfo<Expression*>(influents));
}

const set<Expression *>& RVDataflowGraph::getInfluents(Expression *v) const {
	set<Expression *> *pInluents = accessInfluents(v);
	if (pInluents != NULL)
		return *pInluents;

	static const set<Expression *> emptySet;
	return emptySet;
}

RVDataflowGraph::~RVDataflowGraph() {
	Vertices vertices;
	getVertices(vertices);
	Vertices::iterator it = vertices.begin();
	for (; it != vertices.end(); ++it)
		if (isArtificialNode(*it))
			RVDELETE( *it );
}




class RVReadVarsCollector : public RVWalk {
	typedef RVWalk super;

	struct RVLessSymbolPtrs {
		bool operator() (const Symbol *s1, const Symbol *s2) const {
			return RVComparableDataflowAnalysisRecord::compareSymbolPtrs(s1, s2) < 0;
		}
	};

	typedef set<Symbol*, RVLessSymbolPtrs> RVSymbolPtrSet;

public:
	virtual bool process(Decl* s0p) {
	    CHK_NULL("RVReadVarsCollector::process(Decl*)");
	    TRY_REP_PROC( initializer );
	    return true;
	}

    virtual bool process_member_op(BinaryExpr* s0p) {
    	CHK_NULL("RVReadVarsCollector::process_member_op()");
        REP_PROC( _leftExpr );
        return true;
    }

	virtual bool process(Expression* s0p) {
		if (s0p != NULL && s0p->etype == ET_Variable) {
			m_vars.insert(static_cast<Variable*>(s0p)->name);
			return true;
		}
		return super::process(s0p);
	}

	virtual bool process_binary(BinaryExpr* s0p) {
        CHK_NULL("RVReadVarsCollector::process(BinaryExpr*)");
		bool ret = true;
        
		if (s0p != NULL && s0p->op() == BO_Assign) {
            AssignExpr *aep = dynamic_cast<AssignExpr*>(s0p);
			ret = process(s0p->rightExpr());
			if (s0p->leftExpr()->etype != ET_Variable || aep->op() != AO_Equal)
				ret = process(s0p->leftExpr()) && ret;
			return RVBoolStatus(ret, __FUNCTION__, DBG);
		}
		return super::process_binary(s0p);
	}

	void fill(SymbolVector& v) const {
		v.insert(v.end(), m_vars.begin(), m_vars.end());
	}

protected:
	RVSymbolPtrSet m_vars;
};



  /********************************************************************/
 /*         Implementation of class RVDataflowAnalysisRecord         */
/********************************************************************/
bool RVDataflowAnalysisRecord::operator ==(const RVDataflowAnalysisRecord& other) const {
	return !(*this < other && other < *this);
}




  /********************************************************************/
 /*    Implementation of class RVComparableDataflowAnalysisRecord    */
/********************************************************************/
int RVComparableDataflowAnalysisRecord::comparePointers(const void *p1, const void *p2) {
	return p1 == p2 ? 0 : p1 < p2 ? -1 : 1;
}

int RVComparableDataflowAnalysisRecord::compareSymbolPtrs(const Symbol *s1,
		                                                  const Symbol *s2) {
	if (s1 == NULL || s2 == NULL)
		return comparePointers(s1, s2);
	//Lexicographic order matters most of all. Contents of the sets where
	//compareSymbolPtrs() is the comparison engine can be copied into
	//SymbolVector, which implies that its elements are lexicographically
	//sorted.
	int sdiff = s1->name.compare(s2->name);
	if (sdiff)
		return sdiff;
	int diff = comparePointers(s1->entry, s2->entry);
	//assert(!diff); We must avoid two different variables with the same name. It may occur when a block declares a variable such that a variable of the same name exists in the outer scope.
	return diff;
}

bool RVComparableDataflowAnalysisRecord::operator< (const RVDataflowAnalysisRecord& other) const {
	return compare(other) < 0;
}

bool RVComparableDataflowAnalysisRecord::operator== (const RVDataflowAnalysisRecord& other) const {
	return compare(other) == 0;
}


static bool equalSymbolPtrs(const Symbol *s1, const Symbol *s2) {
	return !RVComparableDataflowAnalysisRecord::compareSymbolPtrs(s1, s2);
}


  /********************************************************************/
 /*           Implementation of class RVDataflowAnalysisInfo         */
/********************************************************************/

bool RVDataflowAnalysisInfo::RVDataflowAnalysisRecordPtrComparator::
  operator() (const RVDataflowAnalysisRecord *a, const RVDataflowAnalysisRecord *b) const
{
	return (a == NULL || b == NULL)? a < b : *a < *b;
}



RVDataflowAnalysisInfo::RVDataflowAnalysisInfo(const RVDataflowAnalysisRecord &elem) {
	insert(elem);
}

RVDataflowAnalysisInfo::RVDataflowAnalysisInfo(const RVDataflowAnalysisInfo& other)
{
	copyFrom(other);
}

RVDataflowAnalysisInfo::~RVDataflowAnalysisInfo() {
	releaseElements(begin(), end());
}

RVDataflowAnalysisInfo& RVDataflowAnalysisInfo::operator= (const RVDataflowAnalysisInfo& other) {
	if (this != &other) {
		releaseElements(begin(), end());
		m_set.clear();
		copyFrom(other);
	}
	return *this;
}

void RVDataflowAnalysisInfo::copyFrom(const RVDataflowAnalysisInfo& other) {
	BaseClassIterator it = other.begin();
	for (; it != other.end(); ++it)
		m_set.insert((*it)->clone());
}

void RVDataflowAnalysisInfo::releaseElements(BaseClassIterator from,
			                                 BaseClassIterator to)
{
	for (BaseClassIterator it = from; it != to; ++it)
		RVDELETE( *it );
}

bool RVDataflowAnalysisInfo::operator< (const RVDataflowAnalysisInfo& o) const {
	return lexicographical_compare(begin(), end(), o.begin(), o.end(),
			                       RVDataflowAnalysisRecordPtrComparator());
}

static bool areAnalysisRecordPtrsEqual(const RVDataflowAnalysisRecord *a,
		                               const RVDataflowAnalysisRecord *b) {
		return (a == NULL || b == NULL)? a == b : *a == *b;
}

bool RVDataflowAnalysisInfo::operator== (const RVDataflowAnalysisInfo& o) const {
	if (size() != o.size())
		return false;
	return equal(begin(), end(), o.begin(), areAnalysisRecordPtrsEqual);
}

bool RVDataflowAnalysisInfo::operator!= (const RVDataflowAnalysisInfo& o) const {
	return ! operator== (o);
}

RVDataflowAnalysisRecord* RVDataflowAnalysisInfo::findKey(RVDataflowAnalysisRecord* const &key) const  {
	RVDataflowAnalysisInfoBaseClass::const_iterator it = m_set.find(key);
	return it == end() ? NULL : *it;
}

bool RVDataflowAnalysisInfo::containsKey(const RVDataflowAnalysisRecord& key) const  {
    RVDataflowAnalysisInfoBaseClass::const_iterator it =
    		m_set.find(const_cast<RVDataflowAnalysisRecord* const>(&key));
	return it != m_set.end();
}

bool RVDataflowAnalysisInfo::remove(RVDataflowAnalysisRecord* const &elem) {
	BaseClassIterator it = m_set.find(elem);
	if (it == end())
		return false;
	BaseClassIterator next = it;
	releaseElements(it, ++next);
	m_set.erase(it);
	return true;
}

void RVDataflowAnalysisInfo::remove(const RVDataflowAnalysisInfo& delendum) {
	RVDataflowAnalysisInfoBaseClass::const_iterator it = delendum.begin();
	for (; it != delendum.end(); ++it)
		remove(*it);
}

bool RVDataflowAnalysisInfo::insert(const RVDataflowAnalysisRecord &elem) {
	RVDataflowAnalysisRecord *cloned = elem.clone();
	pair<BaseClassIterator, bool> inserted = m_set.insert(cloned);
	if (!inserted.second)
		delete cloned;
	return inserted.second;
}

void RVDataflowAnalysisInfo::insert(const BaseClassIterator& from,
		                            const BaseClassIterator& to) {
	for (BaseClassIterator it = from; it != to; ++it)
		insert(**it);
}

void RVDataflowAnalysisInfo::unionImpl(const RVDataflowAnalysisInfo& other) {
	if (this == &other)
		return;
	RVDataflowAnalysisInfoBaseClass additional;
	BaseClassIterator thisIt = begin();
	BaseClassIterator otherIt = other.begin();

	while (thisIt != end() && otherIt != other.end()) {
		if( m_set.key_comp()(*thisIt, *otherIt) )        // *this < *otherIt
			++thisIt;
		else if( m_set.key_comp()(*otherIt, *thisIt) ) { // *otherIt < *thisIt
			additional.insert((*otherIt)->clone());
			++otherIt;
		}
		else {                                           // *this == *otherIt
			++thisIt;
			++otherIt;
		}
	}

    for (; otherIt != other.end(); ++otherIt)
        additional.insert((*otherIt)->clone());

	m_set.insert(additional.begin(), additional.end());
	return;
}

void RVDataflowAnalysisInfo::intersectImpl(const RVDataflowAnalysisInfo& other) {
	if (this == &other)
		return;
	RVDataflowAnalysisInfoBaseClass res;
	BaseClassIterator thisIt = begin();
	BaseClassIterator otherIt = other.begin();

	while (thisIt != end() && otherIt != other.end()) {
		if( m_set.key_comp()(*thisIt, *otherIt) ) {    // *this < *otherIt
			RVDELETE( *thisIt );
			++thisIt;
		}
		else if( m_set.key_comp()(*otherIt, *thisIt) ) // *otherIt < *thisIt
			++otherIt;
		else {                                         // *this == *otherIt
			res.insert(*thisIt);
			++thisIt;
			++otherIt;
		}
	}

	if (thisIt != end())
		releaseElements(thisIt, end());

	m_set.swap(res);
	return;
}

void RVDataflowAnalysisInfo::dropRepeated(void) {
	m_set.erase(m_repeated.begin(), m_repeated.end());
	releaseElements(m_repeated.begin(), m_repeated.end());
	clearRepeated();
}

static ostream& operator<< (ostream& out, const RVDataflowAnalysisInfo& obj) {
	bool first = true;
	RVDataflowAnalysisInfo::BaseClassIterator it;
	out << '{';
	for (it = obj.begin(); it != obj.end(); ++it, first = false) {
		out << (first? "[" :", [");
		(*it)->printAnalysisRecord(out);
		out << ']';
	}
	return out << '}';
}



  /********************************************************************/
 /*              Implementation of IRVJoint class hierarchy          */
/********************************************************************/
RVJoint::RVJoint(const RVJoint& prototype) : m_pJoint(prototype.clone()) {
}

RVJoint::~RVJoint(void) {
	if (m_pJoint) RVDELETE(m_pJoint);
}

RVJoint *RVJoint::clone(void) const {
	assert(m_pJoint != NULL);
	return m_pJoint->clone();
}

void RVJoint::joint(RVDataflowAnalysisInfo& inOut,
		            const RVDataflowAnalysisInfo& in) const {
	assert(m_pJoint != NULL);
	m_pJoint->joint(inOut, in);
}

void RVJoint::postJoint(RVDataflowAnalysisInfo& in, unsigned nIn) const {
	assert(m_pJoint != NULL);
	m_pJoint->postJoint(in, nIn);
}

const char *RVJoint::getJointOpName(void) const {
	return m_pJoint? m_pJoint->getJointOpName() : "joint";
}

void RVIntersectJoint::joint(RVDataflowAnalysisInfo& inOut,
		                     const RVDataflowAnalysisInfo& in) const {
	inOut.intersectImpl(in);
}

void RVUnionJoint::joint(RVDataflowAnalysisInfo& inOut,
		                 const RVDataflowAnalysisInfo& in) const {
	inOut.unionImpl(in);
	inOut.clearRepeated();
}

void RVXorJoint::joint(RVDataflowAnalysisInfo& inOut,
		               const RVDataflowAnalysisInfo& in) const {
	inOut.unionImpl(in);
}

void RVXorJoint::postJoint(RVDataflowAnalysisInfo& in, unsigned nIn) const {
	if (nIn > 0)
		in.dropRepeated();
	else
		in.clearRepeated();
}


  /********************************************************************/
 /*     Wrappers for iterators implementing the same interfaces      */
/********************************************************************/
template <typename V> interface RVICommonIterator {
	virtual ~RVICommonIterator() {}
	virtual bool hasMore(void) const = 0;
	virtual void operator++ (void)  = 0;
	virtual void operator++ (int) = 0;
	virtual const typename V::value_type& operator* (void) const = 0;
};

template <typename IT, typename V>
class RVCommonIteratorImpl : public RVICommonIterator<V> {
public:
	virtual ~RVCommonIteratorImpl() {}
	virtual void operator++ (void) { ++m_it; }
	virtual void operator++ (int) { ++m_it; }
	virtual const typename V::value_type& operator* (void) const { return *m_it; }
protected:
	RVCommonIteratorImpl(const IT& it) : m_it(it) {}
	bool isEnd(const IT& end) const { return m_it == end; }
private:
	IT m_it;
};

template <typename V> class RVForwardIterator :
	public RVCommonIteratorImpl<typename V::const_iterator, V>
{
public:
	RVForwardIterator(const V& v) :
		RVCommonIteratorImpl<typename V::const_iterator, V>(v.begin()),
		m_v(v) {}
	virtual ~RVForwardIterator() {}

	virtual bool hasMore(void) const { return !isEnd(m_v.end()); }

private:
	const V& m_v;
};

template <typename V> class RVBackwardIterator :
	public RVCommonIteratorImpl<typename V::const_reverse_iterator, V>
{
public:
	RVBackwardIterator(const V& v) :
		RVCommonIteratorImpl<typename V::const_reverse_iterator, V>(v.rbegin()),
		m_v(v) {}
	virtual ~RVBackwardIterator() {}

	virtual bool hasMore(void) const { return !isEnd(m_v.rend()); }

private:
	const V& m_v;
};

///<summary> Allocates forward or backward iterator by caller's wish</summary>
///<remark> Don't forget to delete the result of this function! </remark>
template <typename V>
RVICommonIterator<V>& allocateIterator(const V& v, bool backward) {
	RVICommonIterator<V>* p_idxIt;
    if (backward)
        p_idxIt = new RVBackwardIterator<V>(v);
	else
		p_idxIt = new RVForwardIterator<V>(v);
    return *p_idxIt;
}


  /********************************************************************/
 /*          Implementation of class RVMonotonousFramework           */
/********************************************************************/
RVMonotonousFramework::RVMonotonousFramework(const RVJoint &jointOp,
		                                     const RVDataflowGraph& rGraph,
		                                     const string& typeName)
  : m_pGraphToDelete(NULL), m_graph(rGraph), m_jointOp(jointOp),
    m_direction("D"), m_analysisType(typeName)
{
	init();
}

RVMonotonousFramework::RVMonotonousFramework(const RVJoint &jointOp,
		                                     RVDataflowGraph *pGraph,
		                                     const std::string& typeName)
: m_pGraphToDelete(pGraph), m_graph(*pGraph), m_jointOp(jointOp),
  m_direction("D"), m_analysisType(typeName)
{
	init();
}

RVMonotonousFramework::RVMonotonousFramework(const RVJoint &jointOp,
		                   RVIntraProcDataflowGraphBuilder* pBuilder,
		                   const string& typeName)
  : m_pGraphToDelete(pBuilder->build()), m_graph(*m_pGraphToDelete),
    m_jointOp(jointOp),
    m_direction(m_graph.isReverse()? "Backward d" : "Forward d"),
    m_analysisType(typeName)
{
	init();
	delete pBuilder;
}

RVMonotonousFramework::RVMonotonousFramework(const RVMonotonousFramework &o,
		                                     const RVDataflowGraph &rGraph)
  : m_pGraphToDelete(NULL), m_graph(rGraph), m_jointOp(o.m_jointOp),
    m_direction(o.m_direction), m_analysisType(o.m_analysisType),
    m_indent(o.m_indent)
{
}

void RVMonotonousFramework::init(void) {
    initBeforeRun();
	m_indent = 0;
}

void RVMonotonousFramework::initBeforeRun(void) {
	m_out.clear();
	m_out.resize(m_graph.size());
	m_prevChanged.clear();
	m_prevChanged.resize(m_graph.size(), true);
	m_freshChanged.resize(m_graph.size());
}

RVMonotonousFramework::~RVMonotonousFramework() {
	if (m_pGraphToDelete)
		RVDELETE( m_pGraphToDelete );
	Utils::deleteValues(m_readVars);
}

bool RVMonotonousFramework::run(void) {
	initBeforeRun();
	if (DBG) m_graph.toDotty(getAnalysisBriefName());
	if (!m_graph.isSuccessfullyBuilt()) {
		if (DBG)
			rv_errstrm << indent() << "Dataflow graph for " + getAnalysisFullName() << " was not built.\n";
		return true;
	}

	const long maxIterations = m_graph.size()*m_graph.size();
	bool changed = true;

#ifdef RV_TEE_ANALYSIS
	string logfile(Utils::mkFilename(getAnalysisBriefName(), "log"));
	rv_errstrm.tee(logfile);
#endif
	if (DBG)
		rv_errstrm << eolWIndent() << getAnalysisFullName() << " starts.\n";

	vector<int> vertIndices;
	m_graph.getReportedVertixIndices(vertIndices);

	for (long iterations = 0; changed && iterations < maxIterations; ++iterations) {
		if (DBG)
			rv_errstrm << indent() << "----------------------------------------------"
				       << eolWIndent() << "Chaotic iteration #" << iterations << ":\n";
		changed = iterate(vertIndices);
	}

	if (changed) {
		if (DBG)
			rv_errstrm << indent() << "RVMonotonousFramework::run() : the number of iterations exceeded the limit. Analysis running aborted.\n";
	}
	else
		if (DBG) rv_errstrm << indent() << getAnalysisFullName() << " ended.\n";
#ifdef RV_TEE_ANALYSIS
	rv_errstrm.untee(logfile);
#endif
	return !changed;
}

bool RVMonotonousFramework::iterate(const vector<int>& vertIndices) {
	bool anyChanged = false;

	RVICommonIterator<vector<int> >& idxIt =
			allocateIterator(vertIndices, isGraphReverse());
	for (; idxIt.hasMore(); ++idxIt) {
		Expression* node = m_graph.fromIndex(*idxIt);
		const list<int>& callers = m_graph.RVIntGraph::getParents(*idxIt);
		bool changed = m_prevChanged.at(*idxIt);
		list<int>::const_iterator callIt;
		for (callIt = callers.begin(); !changed && callIt != callers.end(); ++callIt)
			changed = m_prevChanged.at(*callIt);
		m_freshChanged.at(*idxIt) = changed;
		RVDataflowAnalysisInfo &in = m_out.at(*idxIt);
		if (!changed) {
            if (DBG) rv_errstrm << indent() << "Skipping " << m_graph.getVertexLabel(*idxIt) << "\n";
			continue;
        }

		RVDataflowAnalysisInfo oldOut(in);
        if (DBG) rv_errstrm << indent() << "Processing: " << m_graph.getVertexLabel(*idxIt) << eolWIndent() << "in = ";

        jointEnteringInfo(in, *idxIt, true);
        killgen(in, node, *idxIt);
        anyChanged |= m_freshChanged.at(*idxIt) = in != oldOut;

        if (DBG) rv_errstrm << eolWIndent() << "Killgen yields: " << in << eolWIndent() << "====> " << (m_freshChanged.at(*idxIt)? "Changed" : "No change") << "\n";
	}

	m_prevChanged.swap(m_freshChanged);
	delete &idxIt;
	return anyChanged;
}

const char *RVMonotonousFramework::getJointOpName(void) const {
	return m_jointOp.getJointOpName();
}

void RVMonotonousFramework::jointEnteringInfo(RVDataflowAnalysisInfo& in, int idx, bool report) const {
	Expression* node = m_graph.fromIndex(idx);
	if (isArtificialNodeOfType(node, DN_Start))
		in = getInfoAtStart();

	const list<int>& callers = m_graph.RVIntGraph::getParents(idx);
	if (callers.empty()) {
    	if (report && DBG) rv_errstrm << in;
    }
    else {
    	unsigned n = 0;
    	list<int>::const_iterator callIt = callers.begin();
		for (; callIt != callers.end(); ++callIt, ++n) {
			if (n == 0) { //First element of "in"
				in = getInfoAt(*callIt);
				in.clearRepeated();
				if (report && DBG) rv_errstrm << in;
			}
			else {         //Further elements of "in"
				if (report && DBG) rv_errstrm << ", " << m_out.at(*callIt);
				m_jointOp.joint(in, getInfoAt(*callIt));
			}

			if (report && DBG) rv_errstrm << " from " << m_graph.getVertexLabel(*callIt);
		}
		m_jointOp.postJoint(in, n);

		if (report && DBG && n > 0) rv_errstrm << eolWIndent() << "The " << getJointOpName() << " of in's elements results in: " << in;
    }
}

const RVDataflowAnalysisInfo& RVMonotonousFramework::getInfoAt(int nodeIdx) const {
	return m_out.at(nodeIdx);
}

const RVDataflowAnalysisInfo& RVMonotonousFramework::getInfoAtFinish(void) const {
	return getInfoAtArtificialNode(DN_Finish);
}

const RVDataflowAnalysisInfo& RVMonotonousFramework::getInfoAtStart(void) const {
	return m_infoAtStart;
}

const RVDataflowAnalysisInfo&
RVMonotonousFramework::getInfoAtArtificialNode(RVDummyNodeType type) const {
	vector<int> indices;
	m_graph.getReportedVertixIndices(indices);
	for (vector<int>::iterator it = indices.begin(); it != indices.end(); ++it)
		if( isArtificialNodeOfType(m_graph.fromIndex(*it), type) )
			return m_out.at(*it);

	fatal_error("RVMonotonousFramework::getInfoAtArtificialNode() could not find the node of desired type");
	return *new RVDataflowAnalysisInfo;
}

string RVMonotonousFramework::getAnalysisFullName(void) const {
	return m_direction + "ataflow analysis " + getAnalysisBriefName();
}

string RVMonotonousFramework::getAnalysisBriefName(void) const {
	return m_uniqName.empty() ? m_analysisType
			                  : m_analysisType + " " + m_uniqName;
}

RVMonotonousFramework& RVMonotonousFramework::uniqueName(const std::string& name) {
	m_uniqName.assign(name);
	return *this;
}

void RVMonotonousFramework::setInfoAtStart(const RVDataflowAnalysisInfo &initialInfo,
		                                   const Symbol* funcName) {
	m_infoAtStart = initialInfo;
}

bool RVMonotonousFramework::isGraphReverse(void) const {
	return m_graph.isReverse();
}

SymbolVector* RVMonotonousFramework::collectReadVars(Expression *e) {
	RVExprToVars::const_iterator it = m_readVars.find(e);
	if (it != m_readVars.end())
		return it->second;

	SymbolVector *pV = new SymbolVector;
	RVReadVarsCollector collector;
	if (collector.process(e))
		collector.fill(*pV);
	return m_readVars[e] = pV;
}

  /********************************************************************/
 /*            Implementation of class RVUnrollCounter               */
/********************************************************************/
const string RVUnrollCounter::ms_refCounter(1, '#');

RVUnrollCounter::RVUnrollCounter(unsigned nUnrolls)
  : m_nUnrolls(nUnrolls << 1), m_pInlinings(new map<string, RVUnrollCount>) {
	incUnrollCounter(ms_refCounter);
}

RVUnrollCounter::RVUnrollCounter(const RVUnrollCounter& o) :
	m_nUnrolls(o.m_nUnrolls), m_pInlinings(o.m_pInlinings) {
	m_pInlinings->at(ms_refCounter).inc();
}

RVUnrollCounter::~RVUnrollCounter() {
	if (decUnrollCounter(ms_refCounter) == 0) {
		if (DBG) {
			map<string, RVUnrollCount>::const_iterator it = m_pInlinings->begin();
			for (; it != m_pInlinings->end(); ++it)
				assert(it->second.m_curCount == 0);
		}

		delete m_pInlinings;
	}
}

bool RVUnrollCounter::incUnrollCounter(const string& funcname) {
	map<string, RVUnrollCount>::iterator it = m_pInlinings->find(funcname);
	if (it == m_pInlinings->end())
		m_pInlinings->insert(
			map<string, RVUnrollCount>::value_type(funcname, RVUnrollCount(getLimit())));

	if (m_pInlinings->at(funcname).inc())
		return true;
	if (DBG)
		rv_errstrm << "RVUnrollCounter::incInliningCounter() : "
				   << "Reached unroll limit " << m_pInlinings->at(funcname).m_maxCount
				   << " for function " << funcname << ".\n";
	decUnrollCounter(funcname);
	return false;
}

unsigned RVUnrollCounter::decUnrollCounter(const string& funcname) {
	if (m_pInlinings->at(funcname).m_curCount < 2) {
		if (DBG)
			rv_errstrm << "RVUnrollCounter::decInliningCounter() : "
			  	       << "m_inlinings[" << funcname << "] < 0.\n";
		fatal_error("", false);
	}
	return m_pInlinings->at(funcname).m_curCount -= 2;
}

RVAnalysisRes RVUnrollCounter::incDepth(const string& funcname) {
	RVUnrollCount& count = m_pInlinings->at(funcname);
	if (count.m_maxCount >= getLimit())
		return RVA_REC_DEPTH;
	++count.m_maxCount;
	return RVA_SUCCESS;
}

const unsigned RVUnrollCounter::RVUnrollCount::ms_initialLimit = 4U;

RVUnrollCounter::RVUnrollCount::RVUnrollCount(unsigned limit)
  : m_curCount(0), m_maxCount(std::min(ms_initialLimit, limit)) {
}

bool RVUnrollCounter::RVUnrollCount::inc(void) {
	return (m_curCount+=2) <= m_maxCount;
}


  /********************************************************************/
 /*                    class RVIntraGraphDb                          */
/********************************************************************/
///<summary>Binds a dataflow graph to a name, usually of a function </summary>
class RVIntraGraphDb : public map<string, RVDataflowGraph*> {
public:
	RVIntraGraphDb(void) : m_pPrimaryGraph(NULL) {}

	///<summary>
	///Marks that garbage collection will start from the given graph
	///</summary>
	void setPrimary(RVDataflowGraph* graph) {
		m_pPrimaryGraph = graph;
	}

	///<summary>
	///Tells if the given graph is the starting point for garbage collection
	///</summary>
	bool isPrimary(const RVDataflowGraph* graph) const {
		return m_pPrimaryGraph == graph;
	}

private:
	RVDataflowGraph* m_pPrimaryGraph;
};



  /********************************************************************/
 /*                 class RVInterProcGraphBuilder                    */
/********************************************************************/
///<summary>
///Base class for every inter-procedural graph builder.
///</summary>
abstract class RVInterProcGraphBuilder : protected RVDataflowGraphBuilderIntrinsic
{
public:
	RVInterProcGraphBuilder(Statement *b,
			                bool backward = false,
			                bool coverBranches = false,
			                bool releaseIntraGraphs = false)
	  : RVDataflowGraphBuilderIntrinsic(*new RVDataflowGraph, backward, coverBranches),
	    m_startFunc(NULL),
	    m_bReleaseIntraGraphs(releaseIntraGraphs),
	    m_block(b) {
	}

	virtual ~RVInterProcGraphBuilder() {
		if (m_bReleaseIntraGraphs)
			Utils::deleteValues(m_procGraph);
	}

	///<summary>
	///Builds the graph. Declared in interface RVIDataflowGraphBuilder.
	///</summary>
	virtual RVDataflowGraph* build(const Symbol *startFunc, unsigned nUnrolls) {
		m_startFunc = startFunc;
		m_procGraph.setPrimary(&m_graph);
		for(Statement* st = m_block; st; st = st->next ) {
			if(! st->isFuncDef() )
				continue;
			if (!processFuncDef(static_cast<FunctionDef*>(st)))
				return false;
		}

		bool res = continueBuilding(m_block);
		postBuild(res);
		return &m_graph;
	}

protected:
	///<summary>
	///Specific actions that affiliate separate graphs of each called function.
	///</summary>
	virtual bool continueBuilding(Statement *b) = 0;

private:
	bool processFuncDef(FunctionDef *func) {
		string name = getFuncName(func);
		if (m_procGraph.find(name) != m_procGraph.end())
			return false;

		RVDataflowGraph* graph = m_procGraph[name] =
				RVIntraProcDataflowGraphBuilder(func, m_revert, m_coverBranches).build();
		return graph->isSuccessfullyBuilt();
	}

	string getFuncName(const FunctionDef *func) {
		return func->FunctionName()->name;
	}

protected:
	RVIntraGraphDb m_procGraph;
	const Symbol  *m_startFunc;
	bool           m_bReleaseIntraGraphs;
	Statement     *m_block;
};


//abstract class RVInterProcInlineAnalysis : public RVMonotonousFramework {
//protected:
//	RVInterProcInlineAnalysis(RVJointDelegate jointOp,
//							  Statement *b,
//							  const std::string& typeName,
//							  unsigned nUnrolls,
//							  const std::string& startFuncName);
//};
//
//
//class RVInlineInterProcGraphBuilder : public RVInterProcGraphBuilder {
//public:
//	RVInlineInterProcGraphBuilder(RVDataflowGraph& graph,
//								  unsigned nUnrolls,
//								  const string& startFuncName)
//	  : RVInterProcGraphBuilder(graph, startFuncName, true), m_unrolls(nUnrolls) {
//	}
//
//protected:
//	virtual bool continueBuilding(Statement *b) {
//		RVIntraGraphDb::iterator it = m_procGraph.find(m_startFuncName);
//		if (it == m_procGraph.end())
//			return false;
//
//		return connectIntraProcGraph(m_start, m_finish, it->first, it->second);
//	}
//
//private:
//	bool connectIntraProcGraph(Expression* callPoint,
//							   Expression* returnPoint,
//							   const string& funcname,
//							   const RVDataflowGraph* intraG) {
//		if (!m_unrolls.incUnrollCounter(funcname))
//			return true;
//
//		if (callPoint->etype == ET_FunctionCall)
//			replaceCallRetPoints(callPoint, returnPoint, funcname);
//
//
//		m_unrolls.decUnrollCounter(funcname);
//		return true;
//	}
//
//	void replaceCallRetPoints(Expression* &rCallPoint, Expression* &rRetPoint,
//							  const string& funcname)
//	{
//		Symbol nameSym;
//		nameSym.name = funcname;
//		Expression *newCallPoint = new ArtificialNodeExpression(DN_FuncStart, NULL, nameSym.dup(), NULL);
//		Expression *newRetPoint = new ArtificialNodeExpression(DN_FuncEnd, NULL, nameSym.dup(), NULL);
//		m_graph.split(rCallPoint, newCallPoint, newRetPoint);
//		rCallPoint = newCallPoint;
//		rRetPoint = newRetPoint;
//	}
//
//	RVUnrollCounter m_unrolls;
//};



//static RVDataflowGraph* buildInlineInterProcGraph(Statement *b,
//		                                          unsigned nUnrolls,
//		                                          const string& startFuncName)
//{
//	const RVInterProcGraphBuilderFactory<RVInlineInterProcGraphBuilder> bf(nUnrolls, startFuncName);
//	RVDataflowGraph* g = new RVDataflowGraph;
//	g->buildYourself(b, bf);
//	return g;
//}
//
//RVInterProcInlineAnalysis::RVInterProcInlineAnalysis(RVJointDelegate jointOp,
//													 Statement *b,
//													 const string& typeName,
//													 unsigned nUnrolls,
//													 const string& startFuncName)
//  : RVMonotonousFramework(jointOp,
//		                  buildInlineInterProcGraph(b, nUnrolls, startFuncName),
//		                  typeName)
//{
//}


static const string sPropIntraAnalysesDb("IntraAnalysesDb");


  /********************************************************************/
 /*                 class RVFuncAnalysesDb                          */
/********************************************************************/
///<summary>
///Binds dataflow (both intra- and inter-procedural) analyses to function names.
///Implements dynamic programming principle, i.e., avoids re-running an analysis
///upon given some previously received input.
///</summary>
class RVFuncAnalysesDb {
	typedef pair<string, RVDataflowAnalysisInfo> TKey;
	typedef map<TKey, pair<RVMonotonousFramework*, RVAnalysisRes> > RVIntraAnalysisMap;

public:
	RVFuncAnalysesDb(const RVIntraGraphDb &graphs) :
		m_intraGraphs(graphs) {}

	///<summary>
	///If there is an analysis for the given function name which was formerly
	///run for the given input (initAnalInfo), then that run analysis
	///is returned.
	///Otherwise, a new analysis is created, run, and remembered for future
	///re-uses (the dynamic programming principle).
	///</summary>
	///<param name="ppAnal">
	///a pointer to the pointer of the re-used or a new run analysis (OUT var)
	///</param>
	///<param name="funcname">
	///the name of the function (a part of the key)
	///</param>
	///<param name="initAnalInfo">
	///the input for running the analysis (a part of the key)
	///</param>
	///<param name="caller">
	///the analysis whose dataflow graph contains a call of the function funcname
	///</param>
	RVAnalysisRes runAnalysis(RVMonotonousFramework** ppAnal,
			                  const Symbol* funcname,
			                  const RVDataflowAnalysisInfo& initAnalInfo,
			                  const RVInterProcOutlineAnalysis& caller) {
		RVIntraGraphDb::const_iterator git = m_intraGraphs.find(funcname->name);
		if (git == m_intraGraphs.end()) {
			if (DBG)
				rv_errstrm << "RVFuncAnalysesDb::runAnalysis() : "
					       << "Missing dataflow graph for function "
					       << funcname->name << ".\n";
			return RVA_FUNC_NOT_FOUND;
		}

		RVMonotonousFramework* intraAnalysis = caller.createAnalysis(*git->second);
		intraAnalysis->uniqueName(funcname->name);
		intraAnalysis->setIndent(caller.getIndent() + 1);
		intraAnalysis->setInfoAtStart(initAnalInfo, funcname);

		TKey key(funcname->name, intraAnalysis->getInfoAtStart());
		RVIntraAnalysisMap::const_iterator it = m_analyses.find(key);
		if (it != m_analyses.end())	{
			delete intraAnalysis;
			if (ppAnal != NULL) *ppAnal = it->second.first;
			return it->second.second;
		}

		saveYourself(*git->second);
		RVAnalysisRes result = intraAnalysis->run()? RVA_SUCCESS : RVA_FAILURE;

		key.second = intraAnalysis->getInfoAtStart();
		it = m_analyses.find(key);
		if (it != m_analyses.end())  // recursive calls created an analysis
			delete it->second.first; // which is to be forgotten
		m_analyses[key] = RVIntraAnalysisMap::mapped_type(intraAnalysis, result);

		if (ppAnal != NULL) *ppAnal = intraAnalysis;
		return result;
	}

	///<summary>
	///Basically, an RVFuncAnalysesDb instance is created during building
	///the primary dataflow graph. A reference to the object is stored in
	///every graph for which an analysis is run, because the analysis might
	///access might inquire the RVFuncAnalysesDb instance.
	///<summary>
	void saveYourself(RVDataflowGraph& rGraph) {
		rGraph.RVIntGraphWData::setDefaultProperty(sPropIntraAnalysesDb,
				RVTypedVertexInfo<RVFuncAnalysesDb*>(this, sPropIntraAnalysesDb));
	}

	///<summary>
	///Begins garbage collection process if the given graph was the primary
	///graph built by RVInterProcGraphBuilder.
	///</summary>
	///<remark>This method is called under the destructor of each subclass of
	///RVInterProcOutlineAnalysis, but only one object holds the primary graph.
	///It will begin the garbage collection.
	///</remark>
	void releaseIfPrimary(const RVDataflowGraph *pGraph) {
		if (m_intraGraphs.isPrimary(pGraph))
			releaseAll();
	}

private:
	RVFuncAnalysesDb(const RVFuncAnalysesDb& o) :
		m_intraGraphs(o.m_intraGraphs), m_analyses(o.m_analyses) {}

	void releaseAll(void) {
		RVIntraAnalysisMap::iterator it = m_analyses.begin();
		for (; it != m_analyses.end(); ++it)
			RVDELETE( it->second.first );
		Utils::deleteValues(m_intraGraphs);
        delete this;
	}

	RVIntraGraphDb     m_intraGraphs;
	RVIntraAnalysisMap m_analyses;
};




  /********************************************************************/
 /*                 class RVOutlineInterProcGraphBuilder             */
/********************************************************************/
///<summary>
///Builds a dataflow graph where every function has its own separate
///graph. The references to the graphs of the function are held in an instance
///of class RVIntraGraphDb (which is a member of RVFuncAnalysesDb).
///</summary>
class RVOutlineInterProcGraphBuilder : public RVInterProcGraphBuilder {
public:
	RVOutlineInterProcGraphBuilder(Statement *b,
			                       bool backward = false,
						 		   bool coverBranches = false)
	  : RVInterProcGraphBuilder(b, backward, coverBranches, false)
    {
        connectTo(m_finish, m_latest);
	}

protected:
	virtual bool continueBuilding(Statement *b) {
		RVFuncAnalysesDb *pDb = new RVFuncAnalysesDb(m_procGraph);
		pDb->saveYourself(m_graph);
		return true;
	}
};




  /********************************************************************/
 /*       Implementation of class RVInterProcOutlineAnalysis         */
/********************************************************************/
const SymEntry* RVInterProcOutlineAnalysis::ms_noStartFunc(NULL);

RVInterProcOutlineAnalysis::RVInterProcOutlineAnalysis(const RVJoint& jointOp,
		                       RVInterProcGraphBuilder* pBuilder,
		                       const string& typeName,
		                       unsigned nUnrolls,
		                       const Symbol *startFunc)
  : RVMonotonousFramework(jointOp, pBuilder->build(startFunc, nUnrolls), typeName),
    m_unrolls(nUnrolls)
{
	delete pBuilder;
	if (startFunc != NULL)
		setStartFunc(startFunc->entry);
}

RVInterProcOutlineAnalysis::RVInterProcOutlineAnalysis(
		                       const RVJoint& jointOp,
					 		   const RVDataflowGraph& rGraph,
							   const std::string& typeName,
							   unsigned nUnrolls,
							   const Symbol *startFunc)
  : RVMonotonousFramework(jointOp, rGraph, typeName),
    m_unrolls(nUnrolls)
{
	if (startFunc != NULL)
		setStartFunc(startFunc->entry);
}

RVInterProcOutlineAnalysis::RVInterProcOutlineAnalysis(
		                   const RVInterProcOutlineAnalysis& o,
				 		   const RVDataflowGraph& rGraph)
  : RVMonotonousFramework(o, rGraph),
    m_unrolls(o.m_unrolls) {
}

RVInterProcOutlineAnalysis::~RVInterProcOutlineAnalysis() {
	RVFuncAnalysesDb **ppDb = accessIntraAnalysisDb();
	if( ppDb != NULL && *ppDb != NULL )
		(*ppDb)->releaseIfPrimary(&getGraph());
}

void RVInterProcOutlineAnalysis::setStartFunc(SymEntry* const startFunc) {
	if (m_startFunc.entry != startFunc) {
		m_startFunc.entry = startFunc;
		m_startFunc.name = startFunc->name;
	}
}

static bool isProcFunctionRetStatusGood(RVAnalysisRes s) {
    return s == RVA_SUCCESS || s == RVA_FUNC_NOT_FOUND;
}

FunctionCall *RVInterProcOutlineAnalysis::getCalledFuncName(Expression *e,
		                                                    Symbol **pSymbPtr,
		                                                    bool *pWrapped) {
	bool dummy;
	if (pWrapped == NULL)
		pWrapped = &dummy;
	else
		*pWrapped = false;
	if (e == NULL)
		return NULL;
	if (e->etype == ET_FunctionCall) {
		FunctionCall *sp = static_cast<FunctionCall*>(e);
		if (pSymbPtr != NULL && sp->function->etype == ET_Variable)
			*pSymbPtr = static_cast<Variable*>(sp->function)->name;
		return sp;
	}

	if (isArtificialNode(e)) {
		ArtificialNodeExpression *aen = static_cast<ArtificialNodeExpression*>(e);
		return aen->getType() == DN_Init && aen->m_attached != NULL?
			(*pWrapped = true, getCalledFuncName(aen->m_attached, pSymbPtr, &dummy)) : NULL;
	}
	if (e->etype != ET_BinaryExpr)
		return NULL;

	BinaryExpr *be = static_cast<BinaryExpr*>(e);
	*pWrapped = true;
	return getCalledFuncName(be->rightExpr(), pSymbPtr, &dummy);
}

void RVInterProcOutlineAnalysis::killgen(RVDataflowAnalysisInfo& io,
		                                 Expression *e,
		                                 int nodeIdx)
{
	bool intraProcAnalFailed = false;
    RVAnalysisRes res;

	if (isArtificialNode(e)) {
		ArtificialNodeExpression *aen = static_cast<ArtificialNodeExpression*>(e);
		if (aen->getType() == DN_Start && m_startFunc.entry != ms_noStartFunc) {
			res = procFunction(&m_startFunc, true, io, aen);
            if (isProcFunctionRetStatusGood(res))
				return;
			intraProcAnalFailed = true;
		}
	}

	Symbol *funcName = NULL;
	bool wrapped = false;
	FunctionCall *callExpr = getCalledFuncName(e, &funcName, &wrapped);
	if (funcName != NULL) {
		res = procFunction(funcName, false, io, callExpr);
		intraProcAnalFailed = !isProcFunctionRetStatusGood(res);
        if (!intraProcAnalFailed && !wrapped)
       		return;
	}

	killgenRegNode(io, e, nodeIdx, intraProcAnalFailed);
}

RVAnalysisRes RVInterProcOutlineAnalysis::procFunction(const Symbol *symname,
		                                               bool startPoint,
		                                               RVDataflowAnalysisInfo& io,
		                                               Expression *callExpr)
{
	if (symname == NULL || !RVCtool::valid_function(symname))
		return RVA_FUNC_NOT_FOUND;

	if (!m_unrolls.incUnrollCounter(symname->name)) {
		RVAnalysisRes res = reachedUnrollLimit(symname, io);
		return res == RVA_INC_DEPTH? m_unrolls.incDepth(symname->name)
				                   : res;
	}

	//No early returns since now!!!
	RVMonotonousFramework *pIntraAnal = NULL;
	RVAnalysisRes succ = runIntraAnalysis(&pIntraAnal, symname, io);
	if (succ == RVA_SUCCESS)
		io = pIntraAnal->getInfoAtFinish();

	m_unrolls.decUnrollCounter(symname->name);
	return succ;
}

RVFuncAnalysesDb**
RVInterProcOutlineAnalysis::accessIntraAnalysisDb(void) const {
    RVFuncAnalysesDb **ppDb = NULL;
    const RVVertexInfo & inf = getGraph().RVIntGraphWData::getProperty(0,
    		sPropIntraAnalysesDb);
    inf.getPtr(ppDb, sPropIntraAnalysesDb);
    return ppDb;
}

RVAnalysisRes RVInterProcOutlineAnalysis::runIntraAnalysis(
		RVMonotonousFramework **ppIntraAnal,
		const Symbol *funcname,
        RVDataflowAnalysisInfo& io)
{
	RVFuncAnalysesDb **ppDb = accessIntraAnalysisDb();
	return ppDb != NULL && *ppDb != NULL ?
	       (*ppDb)->runAnalysis(ppIntraAnal, funcname, io, *this) :
	       RVA_INT_ERROR;
}

RVAnalysisRes RVInterProcOutlineAnalysis::reachedUnrollLimit(
		const Symbol *funcname, RVDataflowAnalysisInfo& io)
{
	return RVA_REC_DEPTH;
}


static const RVUnionJoint     Merger;
static const RVIntersectJoint Intersector;


  /********************************************************************/
 /*            class RVStringPrimitiveAnalysisRecord<T>              */
/********************************************************************/
///<summary>
///A comparable dataflow analysis record that holds a name and a primitive
///value (like int, etc.)
///</summary>
template <typename T>
struct RVStringPrimitiveAnalysisRecord : public RVComparableDataflowAnalysisRecord {
	RVStringPrimitiveAnalysisRecord(const T& v, const string& s = "")
	  : m_sVal(s), m_value(v) {}

	virtual ~RVStringPrimitiveAnalysisRecord() {}

	//Methods we must define:
	virtual RVDataflowAnalysisRecord* clone(void) const {
		return new RVStringPrimitiveAnalysisRecord(m_value, m_sVal);
	}

	///<remark>
	///If you swap the primary/secondary keys, update
	///RVFuncCallCountAnalysis::mergeCallCounts()!
	///</remark>
	virtual int compare(const RVDataflowAnalysisRecord& o) const {
		const RVStringPrimitiveAnalysisRecord<T>& x =
				dynamic_cast<const RVStringPrimitiveAnalysisRecord<T>&>(o);
		int sCompare = m_sVal.compare(x.m_sVal);
		return sCompare? sCompare
				       : m_value < x.m_value? -1
				    		                : m_value > x.m_value? 1 : 0;
	}

	virtual void printAnalysisRecord(ostream& dbgOut) const {
		dbgOut << "<\"" << m_sVal << "\"," << m_value << ">";
	}

	string m_sVal;
	T      m_value;
};



  /********************************************************************/
 /*           Implementation of class RVFuncCallCountAnalysis        */
/********************************************************************/

typedef RVStringPrimitiveAnalysisRecord<RVFuncCallCountAnalysis::TCounter> RVFuncCallCounterRecord;

const string RVFuncCallCountAnalysis::ms_sAnalysisType("CallCountAnalysys");

RVFuncCallCountAnalysis::RVFuncCallCountAnalysis(Statement *b, unsigned nUnrolls)
  : super(RVUnionJoint(), new RVOutlineInterProcGraphBuilder(b),
		  ms_sAnalysisType, nUnrolls, NULL),
	m_startSymbolEntry(NULL) {
}

RVFuncCallCountAnalysis::RVFuncCallCountAnalysis(const RVFuncCallCountAnalysis &o,
		                                         const RVDataflowGraph &rGraph)
  : super(o, rGraph),
	m_sCallees(o.m_sCallees),
	m_startSymbolEntry(o.m_startSymbolEntry) {
}

void RVFuncCallCountAnalysis::killgenNodeLow(RVDataflowAnalysisInfo& io,
						                     int delta,
						                     const string& funcname)
{
	map<string, TCounter> maxVals;
	map<string, TCounter>::iterator found;
	RVDataflowAnalysisInfo out;
	RVDataflowAnalysisInfo::iterator<RVFuncCallCounterRecord> it;
	for (it = io.begin(); it != io.end(); ++it) {
		found = maxVals.find(it->m_sVal);
		maxVals[it->m_sVal] = found == maxVals.end() ?
				it->m_value : max(found->second, it->m_value);
	}

	if (delta != 0) {
		found = maxVals.find(funcname);
		maxVals[funcname] = found == maxVals.end() ?
				delta : min(found->second + delta, INT_MAX);
	}
	else if (maxVals.size() == io.size())
		return;            // No modification occurred

	for (found = maxVals.begin(); found != maxVals.end(); ++found)
		out.insert(RVFuncCallCounterRecord(found->second, found->first));

	io.swap(out);
}

void RVFuncCallCountAnalysis::killgenRegNode(RVDataflowAnalysisInfo& io,
			             	 	 	   	     Expression *e,
			                                 int nodeIdx,
			                                 bool intraProcAnalFailed)
{
	if (intraProcAnalFailed)
		for (set<string>::const_iterator it = m_sCallees.begin(); it != m_sCallees.end(); ++it)
			killgenNodeLow(io, INT_MAX, *it);
	else
		killgenNodeLow(io, 0, "");
}

RVAnalysisRes RVFuncCallCountAnalysis::procFunction(const Symbol* symfuncname,
		                                            bool startPoint,
		                                            RVDataflowAnalysisInfo& io,
		                                            Expression *callExpr)
{
	const string &funcname = symfuncname->name;
	if ( !startPoint && m_sCallees.find(funcname) != m_sCallees.end() )
		killgenNodeLow(io, 1, funcname);

	if (RVParse::ignore_func(funcname))
		return RVA_SUCCESS;

	RVDataflowAnalysisInfo funcOut;
	RVAnalysisRes res = super::procFunction(symfuncname, startPoint, funcOut, callExpr);
	mergeCallCounts(io, funcOut, startPoint? NULL : symfuncname);
	return res;
}

///<summary>
///Goes through <paramref name="io" /> and <paramref name="funcOut" />
///If exists f such that <i>(f, n) in io</i> && <i>(f, m) in funcOut</i>,
///then <i>out += (f, m+n)</i>.
///Unpaired records are added into <i>out</i> as is.
///The result <i>out</i> is assigned into <paramref name="io" />.
///</summary>
///<remark>
///This method assumes that RVFuncCallCounterRecord instances are sorted
///first by m_sVal.
///</remark>
void RVFuncCallCountAnalysis::mergeCallCounts(RVDataflowAnalysisInfo& io,
                                              RVDataflowAnalysisInfo& funcOut,
                                              const Symbol* ignored) {
	RVDataflowAnalysisInfo out;
	RVDataflowAnalysisInfo::iterator<RVFuncCallCounterRecord> itIo, itFuncOut;
	for (itIo = io.begin(), itFuncOut = funcOut.begin();
		 itIo != io.end() && itFuncOut != funcOut.end();)
	{
		int cmp = itIo->m_sVal.compare(itFuncOut->m_sVal);
		if (cmp < 0) {
			out.insert(*itIo);
			++itIo;
		}
		else if (ignored != NULL && ignored->name == itFuncOut->m_sVal)
			++itFuncOut;
		else if (cmp > 0) {
			out.insert(*itFuncOut);
			++itFuncOut;
		}
		else {
			out.insert(RVFuncCallCounterRecord(itIo->m_value + itFuncOut->m_value,
					                           itIo->m_sVal));
			++itIo;
			++itFuncOut;
		}
	}

	out.insert(itIo, io.end());
	out.insert(itFuncOut, funcOut.end());
	io.swap(out);
}

RVMonotonousFramework *RVFuncCallCountAnalysis::createAnalysis(const RVDataflowGraph& g) const {
	return new RVFuncCallCountAnalysis(*this, g);
}

RVAnalysisRes RVFuncCallCountAnalysis::reachedUnrollLimit(const Symbol *funcname,
				                                          RVDataflowAnalysisInfo& io) {
	return RVA_SUCCESS;
}

unsigned int RVFuncCallCountAnalysis::countCalls(SymEntry* const startFunc,
			                                     const std::string& callee)
{
	if (m_startSymbolEntry != startFunc) {
		m_startSymbolEntry = startFunc;
		setStartFunc(m_startSymbolEntry);
		if (!run())
            return INT_MAX;
	}
	return getK(callee);
}

unsigned int RVFuncCallCountAnalysis::getK(const string& callee) const {
	unsigned int result = 0;
	bool found = false;
	const RVDataflowAnalysisInfo& final = getInfoAtFinish();

	RVDataflowAnalysisInfo::iterator<RVFuncCallCounterRecord> it = final.begin();
	for (; it != final.end(); ++it)
		if (it->m_sVal == callee) {
			assert(!found); //Avoid duplication of final results. See killgenNodeLow()
			result = it->m_value;
			found = true;
		}

	//assert(found); //The sought callee is unreachable??
	return result;
}




  /********************************************************************/
 /*  Record for analyses RVWriteVarAnalysis and RVUninitVarAnalysis  */
/********************************************************************/
///<summary>
///Holds symbols (usually variable names) collected in dataflow analyses.
///<seealso cref="RVUninitVarAnalysis"/>
///<seealso cref="RVWriteVarAnalysis"/>
///</summary>
struct RVVarAnalysisRecord : public RVComparableDataflowAnalysisRecord {
	RVVarAnalysisRecord(Symbol *varName)
	  : m_var(varName->dup()) {}

	virtual ~RVVarAnalysisRecord() {
		delete m_var;
	}

	//Methods we must define:
	virtual RVDataflowAnalysisRecord* clone(void) const {
		return new RVVarAnalysisRecord(m_var);
	}

	virtual int compare(const RVDataflowAnalysisRecord& x) const {
		const RVVarAnalysisRecord& other = static_cast<const RVVarAnalysisRecord&>(x);
		return compareSymbolPtrs(m_var, other.m_var);
	}

	virtual void printAnalysisRecord(ostream& dbgOut) const {
		dbgOut << (m_var == NULL? "NULL" : m_var->name);
	}

	Symbol *m_var;
};



  /********************************************************************/
 /*                    class RVWriteVarAnalysis                      */
/********************************************************************/
///<summary>
///An example how to implement a dataflow analysis.
///Analysis type: flow-sensitive, "must", forward direction
///<seealso cref="RVVarAnalysisRecord" />
///<summary>
class RVWriteVarAnalysis : public RVMonotonousFramework {
	friend class RVUninitVarAnalysis;

public:
	RVWriteVarAnalysis(const RVDataflowGraph&);
	virtual ~RVWriteVarAnalysis() {}

	static Symbol *getWriteToVarName(Expression *e);

protected:
	///<summary> Executes kill&gen operation over the given node. </summary>
	///<param name="io"> input/output analysis info for the given node </param>
	///<param name="e"> the expression identifying the dataflow graph node </param>
	///<param name="nodeIdx"> the index the given node </param>
	virtual void killgen(RVDataflowAnalysisInfo& in, Expression *e, int nodeIdx);

private:
	void addWrite(Symbol *, RVDataflowAnalysisInfo& in);
};

///<summary>
///Constructor that receives a data flow graph.
///</summary>
///<remark>
///"Must" type of the analysis is expressed with &RVDataflowAnalysisInfo::intersectOp
///passed as an argument into the super class constructor
///</remark>
RVWriteVarAnalysis::RVWriteVarAnalysis(const RVDataflowGraph& rGraph)
  : RVMonotonousFramework(RVIntersectJoint(), rGraph, "WriteVar") {}

static bool isModifyingUnaryExpression(Expression *e)  {
	if (e->etype != ET_UnaryExpr)
		return false;
	switch(static_cast<const UnaryExpr*>(e)->uOp) {
	case UO_PostDec:
	case UO_PostInc:
	case UO_PreDec:
	case UO_PreInc: return true;
	default: return false;
	}
}

Symbol *RVWriteVarAnalysis::getWriteToVarName(Expression *e) {
	if (e == NULL)
		return NULL;

	if (isArtificialNode(e)) {
		const ArtificialNodeExpression* ane = static_cast<const ArtificialNodeExpression*>(e);
		return ane->getType() == DN_Init? ane->m_name : NULL;
	}

	if (isModifyingUnaryExpression(e) ||
		(e->etype == ET_BinaryExpr && static_cast<const BinaryExpr*>(e)->op() == BO_Assign))
	{
		const Expression *destination = static_cast<const BinaryExpr*>(e)->leftExpr();
		if (destination != NULL && destination->etype == ET_Variable)
			return static_cast<const Variable*>(destination)->name;
	}

	return NULL;
	//We ignore assignment destinations that are complex expressions.
}

///<summary>
///Executes kill&gen operation over the given node.
///Kill: nothing.
///Gen: if the node writes something to a variable, then the variable is inserted to <paramref name="io" />.
///</summary>
///<param name="io"> input/output analysis info for the given node </param>
///<param name="e"> the expression identifying the dataflow graph node </param>
///<param name="nodeIdx"> the index the given node </param>
void RVWriteVarAnalysis::killgen(RVDataflowAnalysisInfo& in,
		                         Expression *e,
		                         int nodeIdx) {
	Symbol *destVarName = getWriteToVarName(e);
	if (destVarName != NULL)
		addWrite(destVarName, in);
}

void RVWriteVarAnalysis::addWrite(Symbol *name, RVDataflowAnalysisInfo& in) {
	RVVarAnalysisRecord varRec(name);
	RVDataflowAnalysisInfo elem(varRec);
	Merger.joint(in, elem);
}



  /********************************************************************/
 /*           Implementation of class RVLiveVarsAnalysis             */
/********************************************************************/
///<summary>
///Constructor that receives a ready dataflow graph
///</summary>
///<remark>
///"May" type of the analysis is expressed with &RVDataflowAnalysisInfo::unionOp
///passed as an argument into the super class constructor
///</remark>
RVUninitVarAnalysis::RVUninitVarAnalysis(RVDataflowGraph& rGraph)
  : RVMonotonousFramework(RVUnionJoint(), rGraph, "UninitVar"),
    m_writeAnal(prepareWriteVarAnalysis(rGraph))
{
}

///<summary>
///Constructor that builds the dataflow graph of the given block
///</summary>
///<remark>
///"May" type of the analysis is expressed with &RVDataflowAnalysisInfo::unionOp
///passed as an argument into the super class constructor
///</remark>
RVUninitVarAnalysis::RVUninitVarAnalysis(Statement *b)
  : RVMonotonousFramework(RVUnionJoint(),
		                  new RVIntraProcDataflowGraphBuilder(b),
		                  "UninitVar"),
    m_writeAnal(prepareWriteVarAnalysis(getGraph()))
{
}

RVUninitVarAnalysis::~RVUninitVarAnalysis() {
	RVDELETE( &m_writeAnal );
}

///<summary>
///Executes kill&gen operation over the given node.
///Kill: nothing.
///Gen: if the node reads an unitialized variable, then the variable is inserted to <paramref name="io" />.
///</summary>
///<param name="io"> input/output analysis info for the given node </param>
///<param name="e"> the expression identifying the dataflow graph node </param>
///<param name="nodeIdx"> the index the given node </param>
void RVUninitVarAnalysis::killgen(RVDataflowAnalysisInfo& in,
		                          Expression *e,
		                          int nodeIdx)
{
	SymbolVector *vars = collectReadVars(e);
	for (SymbolVector::iterator it = vars->begin(); it != vars->end(); ++it)
		addRead(*it, in, nodeIdx);
}

void RVUninitVarAnalysis::addRead(Symbol *name, RVDataflowAnalysisInfo& inOut, int nodeIdx) {
	RVDataflowAnalysisInfo writeIn;
	RVVarAnalysisRecord varRec(name);
	m_writeAnal.jointEnteringInfo(writeIn, nodeIdx, false);
	if (!writeIn.containsKey(varRec)) {
		RVDataflowAnalysisInfo elem(varRec);
		Merger.joint(inOut, elem);
	}
}

RVWriteVarAnalysis& RVUninitVarAnalysis::prepareWriteVarAnalysis(const RVDataflowGraph& rGraph) {
	RVWriteVarAnalysis* writeAnal = new RVWriteVarAnalysis(rGraph);
	writeAnal->run();
	return *writeAnal;
}

void RVUninitVarAnalysis::getUninitializedVars(SymbolVector& uninit) const {
	uninit.clear();
	const RVDataflowAnalysisInfo& final = getInfoAtFinish();
	RVDataflowAnalysisInfo::iterator<RVVarAnalysisRecord> it = final.begin();
	for (; it != final.end(); ++it)
		uninit.push_back((*it).m_var);
}





  /********************************************************************/
 /*           Implementation of class RVLiveVarsAnalysis             */
/********************************************************************/
///<summary>
///Constructor that builds the dataflow graph of the given block
///</summary>
///<remark>
///"May" type of the analysis is expressed with &RVDataflowAnalysisInfo::unionOp
///passed as an argument into the super class constructor
///Backward direction is signed by the 3d argument <b>true</b>.
///</remark>
RVLiveVarsAnalysis::RVLiveVarsAnalysis(Statement *b)
  : RVMonotonousFramework(RVUnionJoint(),
		                  new RVIntraProcDataflowGraphBuilder(b, true),
		                  "LiveVars") {
}

RVLiveVarsAnalysis::~RVLiveVarsAnalysis() {
}

///<summary>
///Executes kill&gen operation over the given node.
///Kill: write-to variable
///Gen: if the node reads a variable, then the variable is inserted to <paramref name="io" />.
///</summary>
///<param name="io"> input/output analysis info for the given node </param>
///<param name="e"> the expression identifying the dataflow graph node </param>
///<param name="nodeIdx"> the index the given node </param>
void RVLiveVarsAnalysis::killgen(RVDataflowAnalysisInfo& in,
		                         Expression *e,
		                         int nodeIdx)
{
	//Kill:
	Symbol *destVarName = RVWriteVarAnalysis::getWriteToVarName(e);
	if (destVarName != NULL) {
		RVVarAnalysisRecord varRec(destVarName);
		in.remove(&varRec);
	}

	//Gen:
	SymbolVector *vars = collectReadVars(e);
	for (SymbolVector::iterator it = vars->begin(); it != vars->end(); ++it) {
		RVDataflowAnalysisInfo elem = RVVarAnalysisRecord(*it);
		Merger.joint(in, elem);
	}
}

///<summary>
///Retrieves the names of live variables at the end of a loop identified with <paramref name="loopStmt" />
///<summary>
///<param name="v">destination of the retrieved live variable names.</param>
///<param name="loopStmt">the identifier of the loop</param>
///<returns><b>true</b> iff there was no error. </returns>
bool RVLiveVarsAnalysis::getLiveVarsAtEndOfLoop(SymbolVector& v,
		                                        const Statement* loopStmt) const
{
	int idx = getGraph().findArtifNodeByTypeOwnedByStmt(DN_EndLoop, loopStmt);
	if (idx < 0)
		return false;

	const RVDataflowAnalysisInfo& inf = getInfoAt(idx);
	RVDataflowAnalysisInfo::iterator<RVVarAnalysisRecord> it;
	for (it = inf.begin(); it != inf.end(); ++it)
		v.push_back((*it).m_var);
	return true;
}
