#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_treecomp.h>
#include <rv_replace.h>
#include <rv_funcnode.h>
#include <rv_temps.h>
#include <rv_arrays.h>
#include "rv_etc.h"
#include "rv_glob.h"
#include "rv_dataflow.h"

#include <ctool/decl.h>
#include <ctool/stemnt.h>

#include <stdlib.h>
#include <sstream>

#define RV_SECTION RV_SEC_ARRAYS


RVArrays& rv_arrays(void) {
	return RVGlob::getRvArrays();
}


/*  RVArrayRef functions:  */
/* ======================= */

RVArrayRef::RVArrayRef()
{
	ar_type = AR_NONE;

	ret_func = from_func = NULL;
	orig_expr = NULL; // the original expression of array access.
	entry = trg_entry = NULL;
	type = token_type = real_item_type = NULL;
}

void RVArrayRef::inVar(SymEntry* _entry, Expression* ex)
{
	if(!_entry) fatal_error("_entry in RVArrayRef::inVar()", false);

	ar_type = AR_VAR;
	entry = _entry;

	if( !entry->IsVarDecl() && !entry->IsParamDecl() ) {
		rv_errstrm << "Internal: RVArrayRef::inVar(): variable declaration entry was expected.\n";
		if( ex ) {
			rv_errstrm <<"  got: "; ex->print(rv_errstrm); rv_errstrm << " at: ";
			ex->location.printLocation(rv_errstrm); rv_errstrm << " .\n";
		}
		fatal_error("non-var entry in RVArrayRef::inVar()", false);
	}

	orig_expr = ex;
}

void RVArrayRef::inVar(SymEntry* _entry, FunctionDef* from, Expression* ex)
{
	inVar(_entry, ex);
	from_func = from;
}

void RVArrayRef::inComp(SymEntry* _entry, FunctionDef* from, Expression* ex)
{
	if(!_entry) fatal_error("_entry in RVArrayRef::inComp()", false);

	ar_type = AR_COMP;
	entry = _entry;
	if( !entry->IsComponentDecl() ) {
		rv_errstrm << "Internal: RVArrayRef::inComp(): struct component declaration entry was expected.\n";
		if( ex ) {
			rv_errstrm <<"  got: "; ex->print(rv_errstrm); rv_errstrm << " at: ";
			ex->location.printLocation(rv_errstrm); rv_errstrm << " .\n";
		}
		fatal_error("non-var entry in RVArrayRef::inComp()", false);
	}

	from_func = from;
	orig_expr = ex;
}

void RVArrayRef::inType(Type* _type, FunctionDef* from, Expression* ex)
{
	if(!_type) fatal_error("_type in RVArrayRef::inType()", false);

	ar_type = AR_TYPE;
	type = _type;
	orig_expr = ex;
}

void RVArrayRef::inFuncRet(FunctionDef* callee, FunctionDef* from, Expression* ex)
{
	if(!callee) fatal_error("_entry in RVArrayRef::inFuncRet()", false);

	ar_type = AR_FUNC;
	ret_func = callee;
	from_func = from;
	orig_expr = ex;
}

Type* RVArrayRef::get_orig_type()
{
	Type* tp = NULL;

	switch(ar_type)
	{
	case AR_VAR:
		if(entry->uVarDecl)
			tp = entry->uVarDecl->form;
		break;

	case AR_COMP:
		if(entry->uComponent)
			tp = entry->uComponent->form;
		break;

	case AR_TYPE: 
		tp = type;
		break;

	case AR_FUNC: {
		Type* ftp;
		if(ret_func && ret_func->decl && (ftp = ret_func->decl->form) && ftp->isFunction() )
			tp = ((FunctionType*)ftp)->subType;
		break;
	}

	default:
		fatal_error("RVArrayRef::get_orig_type(): bad ARType.", false);
	}

	return tp;
}

Type* RVArrayRef::getArrayItemType()
{
	if( real_item_type )
		return real_item_type;

	Type* tp = get_orig_type();

	if( !is_pointer(tp, "RVArrays::getArrayItemType()", &tp) ) {
		rv_errstrm << "Internal: RVArrays::getArrayItemType(): a pointer type was "
				"expected for an array candidate declaration.\n  ";
		if( orig_expr ) {
			orig_expr->print(rv_errstrm); rv_errstrm << " at: ";
			orig_expr->location.printLocation(rv_errstrm); rv_errstrm << "\n";
		}
		return NULL;
	}

	real_item_type = tp;

	return tp;
}

bool RVArrayRef::same_as(const RVArrayRef* o) const
{
	CHK_NULL1(o, "o in RVArrayRef::same_as()");

	if( ar_type != o->ar_type )
		return false;

	switch(ar_type)
	{
	case AR_VAR:  
		if( entry == o->entry || entry->uVarDecl == o->entry->uVarDecl )
			return true;
		if( trg_entry )
			return( trg_entry == o->entry || trg_entry->uVarDecl == o->entry->uVarDecl );
		return false;

	case AR_COMP:
		if( entry == o->entry ||
				( entry->uComponent == o->entry->uComponent &&
						entry->u2Container == o->entry->u2Container ) )
			return true;
		if( trg_entry )
			return ( trg_entry == o->entry ||
					( trg_entry->uComponent == o->entry->uComponent &&
							trg_entry->u2Container == o->entry->u2Container ) );
		return false;

	case AR_TYPE: 
		if( type == o->type || type->equalTo == o->type )
			return true;
		// maybe we already replaced it by its token_type
		return( token_type == o->type );

	case AR_FUNC:
		if( ret_func == o->ret_func && ret_func->equalTo == ((Statement*)o->ret_func) )
			return true;

	default:
		fatal_error("RVArrayRef::same_as(): attempt to compare refs of bad ARType.", false);
	}

	return false;
}

void RVArrayRef::print(std::ostream& out, bool printLocation /*=false*/) const
{
	switch(ar_type)
	{
	case AR_VAR: entry->uVarDecl->print(out, true, 0); break;
	case AR_COMP: entry->uComponent->print(out, true, 0);
	if(printLocation) {
		out << " in: "; entry->u2Container->print(out, NULL, 0); }
	break;
	case AR_TYPE: type->printType(rv_errstrm, NULL, true, 0); break;
	case AR_FUNC: ret_func->decl->print(rv_errstrm, true, 0); break;
	default: fatal_error("RVArrayRef::print(): attempt to compare refs of bad ARType.", false);
	}

	if(printLocation && orig_expr) {
		out << " at: ";
		orig_expr->location.printLocation(out);
	}
}


/* class RVClearEqualTo  */
/* ===================== */

class RVClearEqualTo : public RVWalk
{
  protected:
    Project* parsetree;
    int side;
    FunctionDef* body;

  public:
    RVClearEqualTo();
    virtual ~RVClearEqualTo() {}

    bool clear_all(Project* _tree, int _side);

    bool process_func(FunctionDef *_body);

    virtual bool process(Expression* it);
    virtual bool process(Statement* it);
    virtual bool process(Type* it);
    virtual bool process(Symbol* it);
};

RVClearEqualTo::RVClearEqualTo()
{
  parsetree = NULL;
  side = -1;
  body = NULL;
}

bool RVClearEqualTo::clear_all(Project* _tree, int _side)
{
  CHK_NULL1(_tree && (_side == 0 || _side == 1),
			"_tree is NULL or bad _side in RVClearEqualTo::clear_all()");
  bool ret = true;

  parsetree = _tree;
  side = _side;

  Statement* first_st = get_glob_stemnt(parsetree);

  for(Statement* st = first_st; st; st = st->next)
	if( st->isFuncDef() )
	  ret = process_func((FunctionDef*)st) && ret;
	else {
	  set_where("Global declaration");
	  if( !process(st) ) {  // for other decls.
		ret = false;
if(DBG) { rv_errstrm <<"Error: Failed to clear Decl: \n  ";
  st->print(rv_errstrm, 0);rv_errstrm << "\n"; }
	  }
	}

  return ret;
}

bool RVClearEqualTo::process_func(FunctionDef *_body)
{
  CHK_NULL1(_body, "body in RVClearEqualTo::process_func()");
  bool ret = true;

  body = _body;
  std::string orig_fname = body->FunctionName()->name;
  set_where( orig_fname.data() );

  body->equalTo = NULL;

  ret = process(body->FunctionName()) && ret; // is not processed thru decl
  ret = RVWalk::process(body->decl) && ret;
  ret = process_block(body) && ret; // process body only

  return ret;
}

bool RVClearEqualTo::process(Expression* it)
{
  it->equalTo = NULL;
  return go(it);
}

bool RVClearEqualTo::process(Statement* it)
{
  it->equalTo = NULL;
  return go(it);
}

bool RVClearEqualTo::process(Type* it)
{
  it->equalTo = NULL;
  return go(it);
}

bool RVClearEqualTo::process(Symbol* it)
{
  if(it->entry)
	it->entry->equalTo = NULL;
  return go(it);
}



/*  RVArrays functions:  */
/* ===================== */

RVArrays::RVArrays(RVTemp& _temps)
: RVGenRename(_temps), typecomp(false, false)
{ 
	body = NULL;
	current_side = -1;
	where = "UNKNOWN";
	orig_parsetree[0] = orig_parsetree[1] = NULL;
}

void RVArrays::save_parsetree(Project* _parsetree, int _side)
{
	if( !_parsetree || (_side != 0 && _side != 1) )
		fatal_error("_parsetree is NULL or bad side in RVArrays::save_parsetree()", false);

	orig_parsetree[_side] = _parsetree;
}

void RVArrays::init(FunctionDef* _body, int _side, const char *_where)
{
	body = _body;
	current_side = _side;
	where = _where;
}

bool RVArrays::add_type(Type* tp)
{
	CHK_NULL1(tp && (current_side==0 || current_side==1),
			"tp==NULL or bad side in RVArrays::add_type()"); 

	bool found = false;
	TypeVector::iterator it;
	FORVEC(it, array_item_types[current_side])
	if( typecomp.eq_type(tp, *it) ) {
		found = true;
		// prefer user type names:
		if( is_basetype(tp, BT_UserType) )
			*it = tp;
	}

	if( !found ) {
		array_item_types[current_side].push_back(tp);

		if(DBG) { rv_errstrm << "RVArrays::add_type of ";
		tp->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
		}

		return true;
	}
	else
		return false;
}

Type* RVArrays::find_array_type(Type* tp, int side)
// returns NULL when no similar type was found.
{
	CHK_NULL1(tp && (side==0 || side==1),
			"tp==NULL or bad side in RVArrays::find_array_type()"); 

	TypeVector::iterator it;
	FORVEC(it, array_item_types[side])
	if( typecomp.eq_type(tp, *it) )
		return(*it);

	return NULL;
}

bool RVArrays::add_ref(RVArrayRef* ref)
{
	CHK_NULL1(ref && (current_side==0 || current_side==1),
			"decl is NULL or bad side in RVArrays::add_ref()"); 

	Type *tp, *tp2;

	bool found = false;
	ARVector::const_iterator it;
	FORVEC(it, array_refs[current_side])
	if((*it)->same_as(ref)) {
		found = true;
		break;
	}

	if( found ) {
		tp = (*it)->getArrayItemType();
		tp2 = ref->getArrayItemType();
		if( !typecomp.eq_type(tp2, tp) ) {
			rv_errstrm << "Warning: different array item types in different places for same array reference: \n  ";
			(*it)->print(rv_errstrm); rv_errstrm << "\n  ";
			ref->print(rv_errstrm); rv_errstrm << "\n";
		}
	}
	else {
		array_refs[current_side].push_back(ref);

		if(DBG) { rv_errstrm << "RVArrays::add_ref of ";
		ref->print(rv_errstrm, true); rv_errstrm << "\n";
		}

		tp = ref->getArrayItemType();
		add_type(tp);
	}

	return true;
}

RVArrayRef* RVArrays::get_same_ref(const RVArrayRef* ref)
{
	CHK_NULL1(ref && (current_side==0 || current_side==1),
			"ref is NULL or bad side in RVArrays::has_ref()"); 

	ARVector::const_iterator it;
	FORVEC(it, array_refs[current_side])
	if((*it)->same_as(ref))
		return (*it);

	return NULL;
}

bool RVArrays::has_ref(const RVArrayRef* ref)
{
	return( get_same_ref(ref) != NULL);
}

RVArrayRef* RVArrays::get_array_ref(Expression* expr)
{
	RVCollectArrayRefs collector;
	collector.init(body, current_side, where);
	collector.collect_internally(expr);
	ARVector& refs = collector.get_internal_refs();

	if( refs.size() == 0 )
		return NULL;

	if( refs.size() > 1 ) {
		rv_errstrm << "Warning: RVArrays::get_array_ref() expected "
				"single array reference in expresion, but got "<< refs.size() <<"\n  in: ";
		expr->print(rv_errstrm); rv_errstrm << "\n  at: ";
		expr->location.printLocation(rv_errstrm); rv_errstrm << "\n";
	}

	return get_same_ref(refs[0]);
}

RVArrayRef* RVArrays::get_array_ref(Type* orig_expr_type)
{
	Type* ref_type;

	// find a ref with this type:
	ARVector::const_iterator it;
	FORVEC(it, array_refs[current_side]) {
		ref_type = (*it)->get_orig_type();
		// regard types which are exactly the same *object*
		if(ref_type == orig_expr_type)
			return (*it);
	}

	return NULL;
}

std::string RVArrays::type2name(Type* tp)
/* converts textual type appearence to an identifier form. */
{
	CHK_NULL1(tp, "tp in RVArrays::type2name()");

	std::ostringstream type_strm;
	std::string ret;
	int len, i;

	tp->printType(type_strm, NULL, true, 0);
	ret = type_strm.str();

	len = ret.size();
	for(i=0; i<len; ++i)
		switch(ret[i])
		{
		case ' ':
		case '\t': ret[i] = '_'; break;
		case '*': ret[i] = 'P'; break;
		case '(': ret[i] = 'b'; break;
		case ')': ret[i] = 'e'; break;
		case '[': ret[i] = 'B'; break;
		case ']': ret[i] = 'E'; break;
		case '_': break;
		default:
			if( !isalnum(ret[i]) ) {
				rv_errstrm << "Internal: RVArrays::type2name(): unexpected char '"<< ret[i] <<
						"' in textual representation of ";
				tp->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
			}
		}

	return ret;
}

void RVArrays::clear()
{
	// Note: no need to delete array_item_types and array_decls items -
	//   these are deleted as part of the respective parsetrees
	array_item_types[0].resize(0);
	array_refs[0].resize(0);

	array_item_types[1].resize(0);
	array_refs[1].resize(0);
}

std::string RVArrays::array_operator_func_prefix(Type* item_type)
{
	if( !item_type )
		fatal_error("item_type is NULL in RVArrays::array_operator_func_prefix()", false);

	std::string ret(current_side ? RV_S1_UA_PREFIX : RV_S0_UA_PREFIX);
	Type* recorded_type = find_array_type(item_type, current_side);
	if (!recorded_type) {
		rv_errstrm << "Internal: unable to find array item type in collected array types on side " <<
				current_side << ", looking for type: ";
		item_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
		return "CANT_FIND_ARRAY_ITEM_TYPE";
	}

	ret += type2name(recorded_type);

	return ret;
}

std::string RVArrays::array_access_func_name(Type* item_type)
{
	std::string ret = array_operator_func_prefix(item_type);
	ret += "_ITEM";
	return ret;
}

std::string RVArrays::array_operator_func_name(Type* item_type, UnaryOp op)
{
	std::string ret = array_operator_func_prefix(item_type);
	switch(op) {
	case UO_PreInc:  ret += "_PreInc"; break;
	case UO_PreDec:  ret += "_PreDec"; break;
	case UO_PostInc: ret += "_PostInc"; break;
	case UO_PostDec: ret += "_PostDec"; break;
	default: {
		rv_errstrm << "Internal: bad UnaryOp: "; PrintUnaryOp(rv_errstrm, op);
		rv_errstrm << " on array operand of type: ";
		item_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
		return "BAD_UnaryOp_ON_ARRAY_OPERAND";
	}
	}

	return ret;
}

std::string RVArrays::array_operator_func_name(Type* item_type, BinaryOp op)
{
	std::string ret = array_operator_func_prefix(item_type);
	switch(op) {
	case BO_Plus:  ret += "_Plus"; break;
	case BO_Minus: ret += "_Minus"; break;
	default: {
		rv_errstrm << "Internal: bad BinaryOp: "; PrintBinaryOp(rv_errstrm, op);
		rv_errstrm << " on array operand of type: ";
		item_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
		return "BAD_BinaryOp_ON_ARRAY_OPERAND";
	}
	}

	return ret;
}

std::string RVArrays::array_operator_func_name(Type* item_type, AssignOp op)
{
	std::string ret = array_operator_func_prefix(item_type);
	switch(op) {
	case AO_PlusEql:  ret += "_PlusEql"; break;
	case AO_MinusEql: ret += "_MinusEql"; break;
	default: {
		rv_errstrm << "Internal: bad AssignOp: "; PrintAssignOp(rv_errstrm, op);
		rv_errstrm << " on array operand of type: ";
		item_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
		return "BAD_AssignOp_ON_ARRAY_OPERAND";
	}
	}

	return ret;
}

std::string RVArrays::array_operator_func_name(Type* item_type, RelOp op)
{
	std::string ret = array_operator_func_prefix(item_type);
	switch(op) {
	case RO_Equal:    ret += "_Equal"; break;
	case RO_NotEqual: ret += "_NotEqual"; break;
	case RO_Less:     ret += "_Less"; break;
	case RO_LessEql:  ret += "_LessEql"; break;
	case RO_Grtr:     ret += "_Grtr"; break;
	case RO_GrtrEql:  ret += "_GrtrEql"; break;
	default: {
		rv_errstrm << "Internal: bad RelOp: "; PrintRelOp(rv_errstrm, op);
		rv_errstrm << " on array operand of type: ";
		item_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
		return "BAD_RelOp_ON_ARRAY_OPERAND";
	}
	}

	return ret;
}

Expression* RVArrays::create_item_access(Expression* it, Expression* offset)
{
	if( !it )
		fatal_error("it is NULL in RVArrays::create_item_access()", false);

	Location& l = it->location;
	RVArrayRef* ref = get_array_ref(it);
	if( !ref )
		return NULL;
	Type* item_type = ref->getArrayItemType();
	std::string func_name = array_access_func_name(item_type);
	FunctionCall *call = mk_func_call(func_name, NULL, l);

	if( !offset )
		offset = new IntConstant(0, false, l);

	call->addArg(it);
	call->addArg(offset);

	return (Expression*)call;
}

Expression* RVArrays::create_unary_call(UnaryOp op, Expression* operand)
{
	if( !operand || !is_pointer(operand->type, where) )
		fatal_error("operand is NULL or non-pointer operand in RVArrays::create_unary_call()", false);

	Location& l = operand->location;
	RVArrayRef* ref = get_array_ref(operand);
	if( !ref )
		return NULL;
	Type* item_type = ref->getArrayItemType();
	std::string name = array_operator_func_name(item_type, op);

	FunctionCall* call = mk_func_call(name, NULL, l);
	UnaryExpr *arg = new UnaryExpr(UO_AddrOf, operand->dup(), l);
	call->addArg(arg);

	return (Expression*)call;
}

Expression* RVArrays::create_binary_call(BinaryExpr* orig)
{
	Location& l = orig->location;
	RVArrayRef* left_ref = NULL;
	RVArrayRef* right_ref = NULL;
	Type* item_type = NULL;
	BinaryOp op = orig->op();
	std::string name;

	if( is_pointer(orig->leftExpr()->type, where) )
		left_ref = get_array_ref(orig->leftExpr());

	if( is_pointer(orig->rightExpr()->type, where) )
		right_ref = get_array_ref(orig->rightExpr());

	if( !left_ref && !right_ref ) {
		/* OK. Maybe they are just pointers:
	rv_errstrm << "Internal: RVArrays::create_binary_call(): binary operation was expected \n"
	  "  between two array references: ";  
	rv_errstrm << "\n  at: "; l.printLocation(rv_errstrm);
	rv_errstrm << " but no collected references where found.\n";
		 */
		return NULL;
	}

	if( left_ref && right_ref ) {
		if( op != BO_Minus ||
				!typecomp.eq_type(left_ref->getArrayItemType(), right_ref->getArrayItemType()) )
		{
			rv_errstrm << "Error: Bad operation between two array references: ";
			orig->print(rv_errstrm); rv_errstrm << "\n  at: ";
			l.printLocation(rv_errstrm);
			return NULL;
		}

		item_type = left_ref->getArrayItemType();
		name = array_operator_func_prefix(item_type) + RV_DIFF_AU_SUFFIX;
	}
	else {
		// if it an expression of the form a->c - make it UA_ITEM(a).c:
		if( left_ref && op == BO_PtrMember ) {
			Expression* item = create_item_access(orig->leftExpr(), NULL);
			BinaryExpr *ret = new BinaryExpr(BO_Member, item, orig->rightExpr(), l);
			return (Expression*)ret;
		}

		if( left_ref )
			item_type = left_ref->getArrayItemType();
		else
			item_type = right_ref->getArrayItemType();

		name = array_operator_func_name(item_type, op);
	}

	FunctionCall* call = mk_func_call(name, NULL, l);
	call->addArg(orig->leftExpr()->dup());
	call->addArg(orig->rightExpr()->dup());

	return (Expression*)call;
}

Expression* RVArrays::create_assign_call(AssignExpr* orig)
{
	Location& l = orig->location;
	RVArrayRef* left_ref = NULL;
	Type* item_type = NULL;
	AssignOp op = orig->op();
	std::string name;

	if( is_pointer(orig->leftExpr()->type, where) )
		left_ref = get_array_ref(orig->leftExpr());

	// if it is not an array ref:
	if( !left_ref )
		return NULL;

	item_type = left_ref->getArrayItemType();
	name = array_operator_func_name(item_type, op);

	FunctionCall* call = mk_func_call(name, NULL, l);
	UnaryExpr *larg = new UnaryExpr(UO_AddrOf, orig->leftExpr()->dup(), l);
	call->addArg(larg);
	call->addArg(orig->rightExpr()->dup());

	return (Expression*)call;
}

Expression* RVArrays::create_rel_call(RelExpr* orig)
{
	Location& l = orig->location;
	RVArrayRef* left_ref = NULL;
	RVArrayRef* right_ref = NULL;
	Type* item_type = NULL;
	RelOp op = orig->op();
	std::string name;

	if( is_pointer(orig->leftExpr()->type, where) )
		left_ref = get_array_ref(orig->leftExpr());

	if( is_pointer(orig->rightExpr()->type, where) )
		right_ref = get_array_ref(orig->rightExpr());

	// if none of them is an array ref:
	if( !left_ref && !right_ref )
		return NULL;

	if( !(left_ref && right_ref) ) {
		rv_errstrm << "Error: RVArrays::create_rel_call(): only relation expressions with  \n"
				"  array references on both sides are supported. ";
		rv_errstrm << "at: "; l.printLocation(rv_errstrm); rv_errstrm << "\n";
		return NULL;
	}

	item_type = left_ref->getArrayItemType();
	name = array_operator_func_name(item_type, op);

	FunctionCall* call = mk_func_call(name, NULL, l);
	call->addArg(orig->leftExpr()->dup());
	call->addArg(orig->rightExpr()->dup());

	return (Expression*)call;
}

bool RVArrays::gen_macros_and_typedefs()
{
	std::ostringstream ts0, ts1;
	std::string uaname;
	std::string s0_item_type;
	std::string s1_item_type;
	Type *tp0, *tp1;
	bool ret = true;

	temps.gen_INIT_UA_STRUCT_macro();

	TypeVector::iterator it;
	FORVEC(it, array_item_types[0]) {
		tp0 = *it;
		uaname = type2name(tp0);

		tp0->printType(ts0, NULL, true, 0);
		s0_item_type = convert_type(ts0.str(), 0);

		// tp1 = tp0->equalTo; - doesn't work
		tp1 = find_array_type(tp0, 1);
		if(!tp1) {
			rv_errstrm << "Warning: unable to find array item type on side 1 which is related to (on side 0): ";
			tp0->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
			continue;
		}
		tp1->printType(ts1, NULL, true, 0);
		s1_item_type = convert_type(ts1.str(), 1);

		temps.gen_ua_struct_def(uaname, s0_item_type, s1_item_type);
	}

	/* Check if there are array_item_types[1] which are not in array_item_types[0]: */
	FORVEC(it, array_item_types[1]) {
		tp1 = *it;
		tp0 = find_array_type(tp1, 0);
		if(!tp0) {
			rv_errstrm << "Error: unable to find array item type on side 0 which is related to (on side 1): ";
			tp1->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
			ret = false;
		}
	}

	return ret;
}

bool RVArrays::gen_common_funcs_and_vars(bool decls_only)
{
	bool ret = true;
#if 0
	std::ostringstream ts0, ts1;
	std::string uaname;
	std::string s0_item_type;
	std::string s1_item_type;
	Type *tp0, *tp1;

	TypeVector::iterator it;
	FORVEC(it, array_item_types[0]) {
		tp0 = *it;
		uaname = type2name(tp0);

		// tp1 = tp0->equalTo; - doesn't work
		tp1 = find_array_type(tp0, 1);
		if(!tp1) {
			rv_errstrm << "Warning: unable to find array item type on side 1 which is related to (on side 0): ";
			tp0->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";
			continue;
		}

		temps.gen_ua_new_array_func(uaname, decls_only);

		temps.gen_ua_assert_eq_head(uaname, decls_only);

		/* if decls_only - the prev func printed the proto - just continue. */
		if (decls_only)
			continue;

		/* ASSERT_EQ( a->s0_data[s0_pl], a->s1_data[s1_pl] ); */
		m_where = (std::string("gen ua_assert_eq() for ") + uaname).data();
		RVGenCtx ctx1(m_where);
		ctx1.add_lane(tp0, "", 0, "a->s0_data[s0_pl]");
		ctx1.add_lane(tp1, "", 1, "a->s1_data[s1_pl]");
		ret = gen_item_or_struct_op(ASSERT_EQ, ctx1) && ret;

		temps.gen_ua_assert_eq_middle();
		ret = gen_item_or_struct_op(ASSERT_EQ, ctx1) && ret;  // again

		temps.print("  }\n}\n");

		tp0->printType(ts0, NULL, true, 0);
		s0_item_type = convert_type(ts0.str(), 0);

		tp1->printType(ts1, NULL, true, 0);
		s1_item_type = convert_type(ts1.str(), 1);

		temps.gen_ua_data_arrays(uaname, s0_item_type, s1_item_type);
	}

#endif
	return ret;
}

bool RVArrays::gen_side_funcs_for_type(Type* item_type, bool decls_only)
{
	bool ret = true;
#if 0
	static UnaryOp unary_ops[] = {UO_PreInc, UO_PreDec, UO_PostInc, UO_PostDec};
	static BinaryOp binary_ops[] = {BO_Plus, BO_Minus};
	static AssignOp assign_ops[] = {AO_PlusEql, AO_MinusEql};
	static RelOp rel_ops[] = {RO_Equal, RO_NotEqual, RO_Less, RO_LessEql, RO_Grtr, RO_GrtrEql};

	CHK_NULL1(item_type, "RVArrays::gen_side_funcs_for_type()");

	std::string uaname = type2name(item_type);

	std::ostringstream type_strm;
	item_type->printType(type_strm, NULL, true, 0);
	std::string type_name(convert_type(type_strm.str(), current_side));

	temps.gen_ua_init_func(uaname, current_side, decls_only);
	temps.gen_ua_clear_func(uaname, current_side, decls_only);
	temps.gen_ua_val_func(uaname, type_name, current_side, decls_only);

	if( current_side ) {
		temps.gen_ua_s1_ind_func_head(uaname, look_back, decls_only);
		if( !decls_only ) {
			m_where = (std::string("gen ua_s1_ind_func for ") + uaname).data();
			RVGenCtx ctx1(m_where);
			ctx1.add_lane(item_type, "", 1,  "a->s1_data[array_pl]");
			ctx1.add_lane(item_type, "", NO_SIDE, "a->first[first_pl]");
			ret = gen_item_or_struct_op(FETCH, ctx1) && ret;

			temps.print("  } else {\n");

			RVGenCtx ctx2(m_where);
			ctx2.add_lane(item_type, "", 1, "a->s1_data[array_pl]");
			ret = gen_item_or_struct_op(NONDET, ctx2) && ret;

			temps.gen_ua_s1_ind_func_tail();
		}
	} else {
		temps.gen_ua_s0_ind_func_head(uaname, look_back, decls_only);
		if( !decls_only ) {
			temps.print("  /* generate nondet values for it in a->first */\n");
			m_where = (std::string("gen ua_s0_ind_func for ") + uaname).data();
			RVGenCtx ctx(m_where);
			ctx.add_lane(item_type, "", NO_SIDE, "a->first[place]");
			ctx.add_lane(item_type, "", 0, "a->s0_data[place]");
			ret = gen_item_or_struct_op(NONDET_SAVE, ctx) && ret;

			temps.gen_ua_s0_ind_func_tail();
		}
	}

	std::string func_name = array_access_func_name(item_type);

	if( !decls_only )
		temps.gen_ua_access_macro(func_name, uaname, current_side);

	unsigned i;
	for(i=0; i<ARRAY_LEN(unary_ops); ++i) {
		func_name = array_operator_func_name(item_type, unary_ops[i]);
		temps.gen_ua_unary_func(unary_ops[i], func_name, uaname, decls_only);
	}

	for(i=0; i<ARRAY_LEN(binary_ops); ++i) {
		func_name = array_operator_func_name(item_type, binary_ops[i]);
		temps.gen_ua_binary_func(binary_ops[i], func_name, uaname, decls_only);
	}

	for(i=0; i<ARRAY_LEN(assign_ops); ++i) {
		func_name = array_operator_func_name(item_type, assign_ops[i]);
		temps.gen_ua_assign_func(assign_ops[i], func_name, uaname, decls_only);
	}

	for(i=0; i<ARRAY_LEN(rel_ops); ++i) {
		func_name = array_operator_func_name(item_type, rel_ops[i]);
		temps.gen_ua_rel_func(rel_ops[i], func_name, uaname, decls_only);
	}

#endif
	return ret;
}

bool RVArrays::gen_funcs_for_UA_types(bool decls_only)
{
	bool ret = true;

	// if there are no arrays to replace - just return:
	if( array_item_types[0].size() + array_item_types[0].size() == 0 )
		return true;

	ret = gen_common_funcs_and_vars(decls_only) && ret;

	TypeVector::iterator it;
	for(current_side = 0; current_side < 2; ++current_side)
		FORVEC(it, array_item_types[current_side])
		ret = gen_side_funcs_for_type(*it, decls_only) && ret;

	return ret;
}

bool RVArrays::gen_prototypes()
{
	bool ret = true;

	ret = gen_macros_and_typedefs() && ret;
	ret = gen_funcs_for_UA_types(true) && ret;

	return ret;
}

std::string RVArrays::type2token_name(Type* tp)
{
	return std::string("rv_UA_")+ type2name(tp) +"_token";
}

Type* RVArrays::item_type_to_token_type(Type* tp)
{
	std::string token_name = type2token_name(tp);
	BaseType* ret = new BaseType(BT_UserType);
	ret->typeName = mk_symbol(token_name, NULL);
	return ret;
}

bool RVArrays::replace_occurrences_of_type(Project* parsetree, const Type* replace_type, Type* token_type)
{
	CHK_NULL1(parsetree && replace_type && token_type,
			"RVArrays::replace_occurrences_of_type()");

	RVReplaceType replacer(replace_type, token_type);

	return replacer.replace_all(parsetree, current_side);
}

bool RVArrays::replace_array_decls_and_types(Project* parsetree, int side)
{
	CHK_NULL1(parsetree && (side==0 || side==1),
			"parsetree is NULL or bad side in RVArrays::replace_array_decls_and_types()"); 

	bool ret = true;
	current_side = side;

	// Note: we keep the orig side parsetree (in which array refs were collected).
	// Clear all equalTo fields in the orig parsetree:
	RVClearEqualTo clearer;
	clearer.clear_all(orig_parsetree[side], side);

	/* For each function in parsetree do RVTreeComp::eq_block()
	 on the orig and current parsetrees to connect decls and types by equalTo. */
	if( !equalize_parsetrees(orig_parsetree[side], parsetree) ) {
		rv_errstrm << "Internal: RVArrays::replace_array_decls_and_types():"
				" the original and the newly parsed parsetrees are not equal -"
				" unable to relate declarations and types.\n";
		ret = false;
	}

	/* For each ref in array_refs[side] find its Decl or Type in parsetree
	   and replace it with the right AU type. */  
	Type *orig_type, *item_type, *token_type;
	SymEntry *orig_entry, *entry;
	Decl* decl;
	RVArrayRef::ARType at_type;

	ARVector::const_iterator it;
	FORVEC(it, array_refs[side]) {
		item_type = (*it)->getArrayItemType();
		token_type = item_type_to_token_type(item_type);
		at_type = (*it)->ar_type;

		switch(at_type) {
		case RVArrayRef::AR_VAR:
		case RVArrayRef::AR_COMP:
			orig_entry = (*it)->entry;
			entry = orig_entry->equalTo;
			if (!entry) {
				rv_errstrm << "Internal: can not find the parallel entry "
						"of the array reference var: \n  ";
				orig_entry->Show(rv_errstrm); rv_errstrm << "\n";
				ret = false;
				break;
			}
			(*it)->trg_entry = entry;
			decl = (at_type == RVArrayRef::AR_VAR ? entry->uVarDecl : entry->uComponent);
			if( !decl || !decl->form ) {
				rv_errstrm << "Internal: bad decl or decl form (Type) of: \n  ";
				entry->Show(rv_errstrm); rv_errstrm << "\n";
				ret = false;
				break;
			}
			(*it)->token_type = token_type; // save the new type
			decl->form = token_type;  // fix the decl
			break;

		case RVArrayRef::AR_TYPE:
		{
			const Expression *orig_expr = (*it)->orig_expr;
			const Type *replace_type = NULL;
			if(orig_expr) {
				const Expression *expr = orig_expr->equalTo;
				replace_type = expr->type;
			}
			else if( (orig_type = (*it)->type) && orig_type->equalTo )
				replace_type = orig_type->equalTo;
			else {
				rv_errstrm << "Internal: can not find the parallel expression or type "
						"of the array reference expression of type: \n  ";
				orig_expr->print(rv_errstrm); rv_errstrm << "\n";
				ret = false;
				break;
			}
			(*it)->token_type = token_type;
			ret = replace_occurrences_of_type(parsetree, replace_type, token_type) && ret;
			break;
		}
		case RVArrayRef::AR_FUNC:
			// FIN <<===
			break;

		default:
			fatal_error("RVArrayRef::replace_array_decls_and_types(): bad ARType.", false);
		} /* switch */
	} /* for */

	return ret;
}

bool RVArrays::equalize_parsetrees(Project* pt1, Project* pt2)
{
	bool equal = true;
	RVTreeComp comp_code(false, true);

	Statement* st1 = get_glob_stemnt(pt1);
	Statement* st2 = get_glob_stemnt(pt2);

	for(; st1 && st2; st1 = st1->next, st2 = st2->next) {
		if( st1->isFuncDef() ) {
			if( !st2->isFuncDef() ) {
				rv_errstrm << "Internal: RVArrays::equalize_parsetrees() the side statements "
						" are expected to be function bodies together ! at: ";
				st1->location.printLocation(rv_errstrm);  rv_errstrm << "  and at: ";
				st2->location.printLocation(rv_errstrm);  rv_errstrm << "\n";
			}

			// must treat specifivcally the func declarations
			equal = comp_code.eq_type( ((FunctionDef*)st1)->decl->form,
					((FunctionDef*)st2)->decl->form ) && equal;
			equal = comp_code.eq_stmt(st1, st2) && equal;
		}
		else
			// just compare the declarations
			equal = comp_code.eq_stmt(st1, st2) && equal;
	} /* for */

	// if not both programs end together:
	if( st1 || st2 ) {
		rv_errstrm << "Internal: RVArrays::equalize_parsetrees() both parsetrees "
				"should have the same number of statements. (side = "<< current_side <<")\n";
		equal = false;
	}

	return equal;
}


/*  RVCollectArrayRefs functions:  */
/* =============================== */

RVCollectArrayRefs::RVCollectArrayRefs()
{ 
	body = NULL;
	side = -1;
	where = "UNKNOWN";
	collect_array_refs_internally = true; // safety
}

RVCollectArrayRefs::~RVCollectArrayRefs() {
	Utils::deleteElems(internal_array_refs);
}

void RVCollectArrayRefs::init(FunctionDef* _body, int _side, const char *_where)
{
	body = _body;
	side = _side;
	where = _where;

	internal_array_refs.clear();
}

bool RVCollectArrayRefs::add_array_ref(RVArrayRef* ref)
{
	CHK_NULL1(ref, "decl is NULL in RVCollectArrayRefs::add_array_ref()");

	// if we must collect internally:
	if( collect_array_refs_internally ) {
		internal_array_refs.push_back(ref);
		return true;
	}

	return rv_arrays().add_ref(ref);
}

void RVCollectArrayRefs::add_argtype(int ind, ArgType type)
{
	if( !body ) {
		fatal_error("RVCollectArrayRefs::add_argtype() received bad function body", false);
		return;
	}

	body->fnode.switchOn_argtype(ind, type);
}  

bool RVCollectArrayRefs::collect_array_in_symbol(Symbol* sym, Expression* orig_expr, Type* real_item_type /*= NULL*/)
// may be a direct var or a component name
{
	CHK_NULL1(sym && orig_expr, " sym or orig_expr in RVCollectArrayRefs::collect_array_in_symbol()");

	bool ret = true;
	SymEntry* se = NULL;

	if( !sym || !sym->entry ) {
		rv_errstrm << "Error: RVCollectArrayRefs::collect_array_in_symbol(): ";
		orig_expr->location.printLocation(rv_errstrm); rv_errstrm << ": NULL variable Symbol or its SymEntry.\n";
		fatal_error("NULL symbol in variable in: ", where, false);
	}

	se = sym->entry;
	if( !se || (!se->IsVarDecl() && !se->IsParamDecl() && !se->IsComponentDecl() ) ) {
		rv_errstrm << "Error: RVCollectArrayRefs::collect_array_in_symbol(): expression ";
		orig_expr->print(rv_errstrm);
		rv_errstrm << " is dereferenced as array but is not a var or struct component symbol: ";
		orig_expr->location.printLocation(rv_errstrm); rv_errstrm << " .\n";
		return false;
	}

	RVArrayRef* ref = new RVArrayRef();

	if( se->IsComponentDecl() && se->uComponent )
		ref->inComp(se, body, orig_expr);
	else {
		ref->inVar(se, body, orig_expr);

		// if it is a function parameter and we should collect argtypes:
		if( !collect_array_refs_internally && sym->entry->IsParamDecl() )
			if( body && body->decl && body->decl->form && body->decl->form->isFunction() ) {
				// find it in the prototype
				int ind = get_arg_index( (FunctionType*)body->decl->form, sym );

				// add argtype AT_Array to this param in the function prototype:
				add_argtype(ind, AT_Array);
			}
	} /* inVar */

	if( real_item_type )
		ref->real_item_type = real_item_type;

	ret = add_array_ref(ref) && ret;

	return ret;
}

bool RVCollectArrayRefs::collect_array_unary_expr(UnaryExpr* s0p)
{
	CHK_NULL("RVCollectArrayRefs::collect_array_unary_expr()");
	bool ret = true;

	switch( s0p->op() )
	{
	case UO_PreInc:         // ++x
	case UO_PreDec:         // --x
	case UO_PostInc:        // x++
	case UO_PostDec:        // x--
		ret = collect_array_ref_rec(s0p->operand()) && ret;
		break;

	case UO_AddrOf:         // &
	case UO_Deref:          // *
		ret = collect_array_in_expr_type(s0p) && ret;
		break;

	default:
		rv_errstrm << "Error: the next expression can not be an array: \n  ";
		s0p->print(rv_errstrm);  rv_errstrm << " at: ";
		s0p->location.printLocation(rv_errstrm); rv_errstrm << " \n";
		ret = false;
	}

	return ret;
}

bool RVCollectArrayRefs::collect_array_binary_expr(BinaryExpr* s0p)
{
	CHK_NULL("RVCollectArrayRefs::collect_array_binary_expr()");
	bool ret = true;
	Symbol* sym = NULL;

	switch( s0p->bOp )
	{
	case BO_Comma:       // x,y
	case BO_Member:      // x.y
	case BO_PtrMember:   // x->y  
		sym = try_var2symbol(s0p->rightExpr());
		if (sym) ret = collect_array_in_symbol(sym, s0p) && ret; // ofer: added condition
		break;

	case BO_Assign: {
		RETYPE( AssignExpr );
		ret = collect_array_assign(s0p) && ret;
		break;
	}

	case BO_Plus:        // +
	case BO_Minus: {     // -
		// collect the side which is the base pointer:
		bool take_left = s0p->leftExpr() && is_pointer(s0p->leftExpr()->type, where);
		bool take_right = s0p->rightExpr() && is_pointer(s0p->rightExpr()->type, where);

		if( take_left && take_right ) {
			rv_errstrm << "Warning: found pointers on both sides of dereference-"
					"with-offset expression. in : " << where << ", ";
			s0p->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
		}

		if( take_left )
			ret = collect_array_ref_rec(s0p->leftExpr()) && ret;
		if( take_right )
			ret = collect_array_ref_rec(s0p->rightExpr()) && ret;
		break;
	}

	default:
		rv_errstrm << "Error: RVCollectArrayRefs::collect_array_binary_expr() "
		"bad operation on a pointer (or array): ";
		PrintBinaryOp(rv_errstrm, s0p->op()); rv_errstrm <<" at: ";
		s0p->location.printLocation(rv_errstrm); rv_errstrm << " \n";
		ret = false;
	}

	return ret;
}

bool RVCollectArrayRefs::internal_ref_is_array()
{
	// Checks whether one of the refs kept in internal_array_refs are
	//   really array ref collected previously (in rv_arrays())
	ARVector::const_iterator it;
	FORVEC(it, internal_array_refs)
	if( rv_arrays().has_ref(*it) )
		return true;

	return false;
}

bool RVCollectArrayRefs::collect_array_assign(AssignExpr* s0p, bool check_sides /*=false*/)
{
	CHK_NULL("RVCollectArrayRefs::collect_array_assign()");
	bool ret = true;

	switch(s0p->op()) {
	case AO_Equal: {
		bool go_right = true;  // by default collect both sides of "="
		bool go_left = true;

		if( check_sides ) {
			// check whether one of the sides is already marked
			//   as array and add the other side too.
			go_right = go_left = false; // nothing is known yet
			collect_array_refs_internally = false;

			internal_array_refs.clear();
			collect_array_ref_rec(s0p->rValue());
			if( internal_ref_is_array() )
				go_left = true;

			internal_array_refs.clear();
			collect_array_ref_rec(s0p->lValue());
			if( internal_ref_is_array() )
				go_right = true;

			collect_array_refs_internally = false;
		} /* check_sides */

		if( go_right )
			ret = collect_array_ref_rec(s0p->rValue()) && ret;
		if (go_left)
			ret = collect_array_ref_rec(s0p->lValue()) && ret;
		break;
	} /* AO_Equal */

	case AO_PlusEql:         // +=
	case AO_MinusEql:        // -=
		if( !check_sides ) // no other side - no copying of array ref
			ret = collect_array_ref_rec(s0p->lValue()) && ret;
		break;

	default:
		if( !check_sides ) {
			rv_errstrm << "Error: RVCollectArrayRefs::collect_array_assign() "
					"bad operation on a pointer (or array): ";
			PrintAssignOp(rv_errstrm, s0p->op()); rv_errstrm <<" at: ";
			s0p->location.printLocation(rv_errstrm); rv_errstrm << " \n";
			ret = false;
		}
	}

	return ret;
}

bool RVCollectArrayRefs::collect_array_in_decl_type(Decl* s0p)
// take the Type of the whole *array* expression to be the array reference ancore
{
	CHK_NULL("RVCollectArrayRefs::collect_array_in_decl_type()");
	RVArrayRef* ref = new RVArrayRef();
	ref->inType(s0p->form, body, NULL);
	return add_array_ref(ref);
}

bool RVCollectArrayRefs::collect_array_in_expr_type(Expression* s0p)
// take the Type of the whole *array* expression to be the array reference ancore
{
	CHK_NULL("RVCollectArrayRefs::collect_array_in_expr_type()");
	RVArrayRef* ref = new RVArrayRef();
	ref->inType(s0p->type, body, s0p);
	return add_array_ref(ref);
}

bool RVCollectArrayRefs::collect_array_in_func_ret(FunctionCall* s0p)
{
	CHK_NULL("RVCollectArrayRefs::collect_array_in_func_ret()");

	Symbol *funcSymb = NULL;
	assert(RVInterProcOutlineAnalysis::getCalledFuncName(s0p, &funcSymb) && funcSymb); //Check if is a function call, indeed

	FunctionDef* func = RVCtool::valid_function(funcSymb)? funcSymb->entry->u2FunctionDef
                                                         : NULL;

	//fatal_error("RVCollectArrayRefs::collect_array_in_func_ret() is unimplemented yet.\n"
	//		"  Array return form function is not supported yet.\n", false);

	RVArrayRef* ref = new RVArrayRef();
	ref->inFuncRet(func, body, s0p);
	return add_array_ref(ref);
}

bool RVCollectArrayRefs::collect_array_ref_rec(Expression* s0p)
// a version of collect_array_ref() which may recurse.
{
	CHK_NULL("RVCollectArrayRefs::collect_array_ref()");

	// ignore operations (like +index, ++ etc.) on non-pointers
	if( !is_pointer(s0p->type, where) )
		return true;

	bool ret = true;
	Symbol* sym = NULL;

	/*
	 Find the right symbol (may be a struct component) or type.
	 Add the decl to rv_array array_decls and array_item_types
		if it is a struct component - keep its enclosing struct and function too.
	 */

	switch( s0p->etype )
	{
	// when the array is direct symbol:
	case ET_Variable:
		sym = try_var2symbol(s0p);
		ret = collect_array_in_symbol(sym, s0p) && ret;
		break;

	case ET_UnaryExpr:
		ret = collect_array_unary_expr((UnaryExpr*)s0p) && ret;
		break;

		// when the top operation is X.Y or X->Y take Y decl and type.
	case ET_BinaryExpr:
		ret = collect_array_binary_expr((BinaryExpr*)s0p) && ret;
		break;

	case ET_CastExpr: {      // (type) x
		RETYPE( CastExpr );
		sym = try_var2symbol(s0p->expr); // returns NULL in cases such as (void *) (0)
		if (sym) ret = collect_array_in_symbol(sym, s0p, s0p->castTo) && ret;
		break;
	}

	case ET_IndexExpr: {     // x[y]...[]
		RETYPE( IndexExpr );
		// Note: pass the *array* type to be collected:
		ret = collect_array_in_expr_type(s0p->array) && ret;
		break;
	}

	case ET_TrinaryExpr: {
		RETYPE( TrinaryExpr );
		ret = collect_array_ref(s0p->trueExpr()) && ret;
		ret = collect_array_ref(s0p->falseExpr()) && ret;
		break;
	}

	case ET_FunctionCall:
		ret = collect_array_in_func_ret((FunctionCall*)s0p) && ret;
		break;

	default:
		rv_errstrm << "Error: the next expression can not be an array: \n  ";
		s0p->print(rv_errstrm);  rv_errstrm << " at: ";
		s0p->location.printLocation(rv_errstrm); rv_errstrm << " \n";
		ret = false;
	} /* switch( s0p->etype ) */

	return ret;
}

bool RVCollectArrayRefs::collect_array_ref(Expression* s0p)
{
	// This function is called when we really find an array deref
	//   ("[]" or "pointer + index" operation). Therefore we must collect
	//   the array refs to rv_arrays():
	collect_array_refs_internally = false;

	return collect_array_ref_rec(s0p);
}

bool RVCollectArrayRefs::collect_internally(Expression* s0p)
{
	collect_array_refs_internally = true;
	return collect_array_ref_rec(s0p);
}
