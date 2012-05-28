/*
 * rv_dataflow.h
 *
 *  Created on: May 21, 2011
 *      Author: edima
 */

#ifndef RV_DATAFLOW_H_
#define RV_DATAFLOW_H_

#include "rv_graph.h"

class Expression;
class Statement;
class Symbol;
class SymbolVector;
class RVDataflowAnalysisInfo;
class RVFuncAnalysesDb;
class RVIntraProcDataflowGraphBuilder;
class RVInterProcGraphBuilder;


enum RVDummyNodeType { DN_Start, DN_Finish, DN_Init, DN_EndLoop, DN_RetVal,
	                   /* All the rest should not appear in the dataflow graph: */
	                   DN_Connector, DN_Label,
					   /* Don't append any new type after this line */
					   DN_LastDummyNodeType };


bool isArtificialNode(const Expression *e);
bool isArtificialNodeOfType(const Expression *e, RVDummyNodeType type);


interface RVIDataflowGraphBuilderFactory;


///<summary>
///Represents dataflow graph useful for intra-procedural analyses.
///Each node represents a pointer of type Expression.
///</summary>
class RVDataflowGraph : public RVGraphWData<Expression*> {
public:
	static const std::string RV_Constants;
	static const std::string RV_FuncArg;

	typedef std::vector<Expression*> Vertices;

	RVDataflowGraph(void) : m_successfullyBuilt(false), m_reverse(false) {}
	virtual ~RVDataflowGraph();

	///<summary>Tells whether the graph has been successfully built</summary>
	///<returns><b>true</b> iff the graph has been successfully built </returns>
	bool isSuccessfullyBuilt(void) const { return m_successfullyBuilt; }

	void setSuccessfullyBuilt(bool v) { m_successfullyBuilt = v; }

	///<summary>
	///Returns the label of the queried vertex for dotty and debug purposes
	///<summary>
	///<param name="idx">the the index of the queried graph node </param>
	std::string getVertexLabel(int idx) const;

	///<summary>
	///Searches for an artificial node of the given type owned by <paramref name="owner" />
	///</summary>
	///<returns>the index if the node found; -1 otherwise</returns>
	int findArtifNodeByTypeOwnedByStmt(RVDummyNodeType type,
			                           const Statement *owner) const;

	///<summary> Tells if the dataflow graph is reverse </summary>
	bool isReverse(void) const { return m_reverse; }

	///<summary> Reverses the dataflow graph </summary>
	void reverse(void);

	void addInfluent(int influencedIdx, Expression *influent);
	const std::set<Expression *>& getInfluents(Expression *v) const;

	template <typename T> void dischargeLater(T *ptr) {
		m_gc.addDischargeeHeapPtr(new RVTypedDischargee<T>(ptr));
	}

protected:
	/// <summary>
	/// Retrieves dotty attributes of a vertex.
	/// </summary>
	/// <return>the name of the vertex node</return>
	/// <param name="idx"> the index of the vertex </param>
	/// <param name="label"> here the label of the vertex can be assigned </param>
	/// <param name="fontcolor"> here the font color of the vertex label can be assigned </param>
	/// <param name="color"> here the color of the vertex node can be assigned </param>
	/// <param name="shape"> here the shape of the vertex node can be assigned </param>
	/// <param name="style"> here the style of the vertex node can be assigned </param>
	/// <param name="fillcolor"> here the color to fill the vertex node can be assigned </param>
	/// <remark> Unused attributes may be left unassigned. </remark>
	virtual std::string getDottyAttrsOfVertex(int idx,
											  std::string &label,
											  std::string &fontcolor,
											  std::string &color,
											  std::string &shape,
											  std::string &style,
											  std::string &fillcolor) const;

private:
	std::set<Expression*> *accessInfluents(Expression *v) const;

	static const std::string RV_Influence;
	bool m_successfullyBuilt, m_reverse;
	RVDischarger m_gc;
};





///<summary>
///Base class for data records collected in dataflow analyses.
///<seealso cref="RVVarAnalysisRecord" />
///<seealso cref="RVComparableDataflowAnalysisRecord" />
///</summary>
abstract class RVDataflowAnalysisRecord {
public:
	virtual ~RVDataflowAnalysisRecord() {}

	//Methods you must define:
	virtual RVDataflowAnalysisRecord* clone(void) const = 0;
	virtual bool operator< (const RVDataflowAnalysisRecord&) const = 0;
	virtual void printAnalysisRecord(std::ostream&) const = 0; //for debug info

	//You may override this operator to speed up comparing.
	virtual bool operator== (const RVDataflowAnalysisRecord&) const;
};



///<summary>
///Base class for data records collected in dataflow analyses, such that
///comparison of the records is implemented through int compare(...) method.
///<seealso cref="RVVarAnalysisRecord" />
///</summary>
abstract class RVComparableDataflowAnalysisRecord : public RVDataflowAnalysisRecord {
public:
	static int comparePointers(const void *, const void *);
	static int compareSymbolPtrs(const Symbol *, const Symbol *);

	virtual ~RVComparableDataflowAnalysisRecord() {}

	//Methods defined here:
	virtual bool operator< (const RVDataflowAnalysisRecord&) const;
	virtual bool operator== (const RVDataflowAnalysisRecord&) const;

	//Methods you must still define:
	virtual RVDataflowAnalysisRecord* clone(void) const = 0;
	virtual void printAnalysisRecord(std::ostream&) const = 0;

protected:
	virtual int compare(const RVDataflowAnalysisRecord&) const = 0;

	template<class T>
	struct lessPtr : public std::binary_function<T, T, bool> {
	    bool operator()(const T& x, const T& y) const {
	        return comparePointers(x, y) < 0;
	    };
	};
};




///<summary>
///Holder of information collected during dataflow analyses,
///i.e., a set of the data records.
///</summary>
///<remark>
///This class is not intended for overriding. Any proprietary analysis
///data is defined through a sub-class of RVDataflowAnalysisRecord.
///</remark>
///<remark>
///If you wish to define a new kind of joint operation (in addition to union
///and intersect), just add the appropriate method.
///</remark>
class RVDataflowAnalysisInfo  {
	struct RVDataflowAnalysisRecordPtrComparator {
		bool operator() (const RVDataflowAnalysisRecord *, const RVDataflowAnalysisRecord *) const;
	};

	typedef std::set<RVDataflowAnalysisRecord*, RVDataflowAnalysisRecordPtrComparator> RVDataflowAnalysisInfoBaseClass;

public:
	typedef RVDataflowAnalysisInfoBaseClass::iterator BaseClassIterator;

	template<typename T> struct iterator : public BaseClassIterator {
		iterator(void) {}
		iterator(const BaseClassIterator& it)
		  : BaseClassIterator(it) {}

		const T& operator* (void) const {
			return * operator-> ();
		}

		T* operator-> (void) const {
			return static_cast<T*>(BaseClassIterator::operator*());
		}
	};

	RVDataflowAnalysisInfo(void) {}
	RVDataflowAnalysisInfo(const RVDataflowAnalysisRecord &elem);
	RVDataflowAnalysisInfo(const RVDataflowAnalysisInfo&);
	~RVDataflowAnalysisInfo(void);

	RVDataflowAnalysisInfo& operator= (const RVDataflowAnalysisInfo&);

	bool operator< (const RVDataflowAnalysisInfo&) const;
	bool operator== (const RVDataflowAnalysisInfo&) const;
	bool operator!= (const RVDataflowAnalysisInfo&) const;

	BaseClassIterator begin(void) const {return m_set.begin();}
	BaseClassIterator end(void) const {return m_set.end();}

	size_t size(void) const { return m_set.size(); }

	void swap(RVDataflowAnalysisInfo& other) { m_set.swap(other.m_set); }

	bool containsKey(const RVDataflowAnalysisRecord &key) const;

	bool insert(const RVDataflowAnalysisRecord &elem);
	void insert(const BaseClassIterator& from, const BaseClassIterator& to);
	bool remove(RVDataflowAnalysisRecord* const &elem);
	void remove(const RVDataflowAnalysisInfo& delendum);

	void clearRepeated(void) { m_repeated.clear(); }

private:
	friend struct RVIntersectJoint;
	friend struct RVUnionJoint;
	friend struct RVXorJoint;
	void intersectImpl(const RVDataflowAnalysisInfo&);
	void unionImpl(const RVDataflowAnalysisInfo&);
	void dropRepeated(void);
	void releaseElements(BaseClassIterator from, BaseClassIterator to);
	void copyFrom(const RVDataflowAnalysisInfo&);
	RVDataflowAnalysisRecord* findKey(RVDataflowAnalysisRecord* const &) const;

	RVDataflowAnalysisInfoBaseClass m_set;
	RVDataflowAnalysisInfoBaseClass m_repeated;
};



struct RVJoint {
	RVJoint(const RVJoint& prototype);
	virtual ~RVJoint();
	virtual void joint(RVDataflowAnalysisInfo&, const RVDataflowAnalysisInfo&) const;
	virtual void postJoint(RVDataflowAnalysisInfo&, unsigned nIn) const;
	virtual const char *getJointOpName(void) const;

protected:
	RVJoint(void) : m_pJoint(NULL) {}
	virtual RVJoint* clone(void) const;

private:
	RVJoint *m_pJoint;
};


struct RVIntersectJoint : public RVJoint {
	virtual void joint(RVDataflowAnalysisInfo&, const RVDataflowAnalysisInfo&) const;
	virtual void postJoint(RVDataflowAnalysisInfo&, unsigned nIn) const {}
	virtual const char *getJointOpName(void) const { return "intersect"; }

protected:
	virtual RVJoint* clone(void) const {return new RVIntersectJoint;}
};


struct RVUnionJoint : public RVJoint {
	virtual void joint(RVDataflowAnalysisInfo&, const RVDataflowAnalysisInfo&) const;
	virtual void postJoint(RVDataflowAnalysisInfo&, unsigned nIn) const {}
	virtual const char *getJointOpName(void) const { return "union"; }

protected:
	virtual RVJoint* clone(void) const {return new RVUnionJoint;}
};


struct RVXorJoint : public RVJoint {
	virtual void joint(RVDataflowAnalysisInfo&, const RVDataflowAnalysisInfo&) const;
	virtual void postJoint(RVDataflowAnalysisInfo&, unsigned nIn) const;
	virtual const char *getJointOpName(void) const { return "xor"; }

protected:
	virtual RVJoint* clone(void) const {return new RVXorJoint;}
};


///<summary>
///The framework for running a dataflow analysis. The analysis should inherit
///from this class.
///<seealso cref="RVUninitVarAnalysis"/>
///<seealso cref="RVWriteVarAnalysis"/>
///</summary>
abstract class RVMonotonousFramework {
	typedef std::map<Expression *, SymbolVector *> RVExprToVars;

public:
	virtual ~RVMonotonousFramework();

	///<summary>
	///Runs the underlying analysis over this framework.
	///</summary>
	///<returns>
	///<b>true</b>  => running has successfully ended
	///<b>false</b> => running was terminated as it was too long
	///>/returns>
	bool run(void);

	///<summary>
	///Assigns name to this framework in order to distinguish it from other
	///frameworks of the same type
	///</summary>
	///<returns>A reference to itself </returns>
	RVMonotonousFramework& uniqueName(const std::string& name);

	///<summary>
	///Assigns the initial analysis info of the DN_Start node
	///</summary>
	virtual void setInfoAtStart(const RVDataflowAnalysisInfo&, const Symbol *);

	///<summary>
	///Yields the analysis info of the DN_Finish node, where final results
	///are usually found
	///</summary>
	const RVDataflowAnalysisInfo& getInfoAtFinish(void) const;

	///<summary>
	///Yields the analysis info of the DN_Start node, with which the analysis started running
	///</summary>
	const RVDataflowAnalysisInfo& getInfoAtStart(void) const;

	///<summary>
	///Sets the level of inclusion of this analysis.
	///Relevant for outline inter-procedural analyses <see cref="RVInterProcOutlineAnalysis">
	///</summary>
	void setIndent(int v) { m_indent = v; }

	///<summary>
	///Gets the level of inclusion of this analysis.
	///Relevant for outline inter-procedural analyses <see cref="RVInterProcOutlineAnalysis">
	///</summary>
	int getIndent(void) const { return m_indent; }

protected:
	///<summary>
	///Constructor that gets a ready dataflow graph <paramref name="rGraph" />.
	///</summary>
	///<param name="jointOp">
	///Specifies the joint operation"
	///&RVDataflowAnalysisInfo::intersectOp for "must" analyses;
	///&RVDataflowAnalysisInfo::unionOp for "may" analyses.
	///</param>
	///<param name="rGraph">the ready dataflow graph</param>
	///<param name="typeName">the name of the analysis type</param>
	RVMonotonousFramework(const RVJoint &jointOp,
			              const RVDataflowGraph &rGraph,
			              const std::string& typeName);

	///<summary>
	///Constructor that gets a ready dataflow graph <paramref name="rGraph" />.
	///At the end the graph will be released.
	///</summary>
	///<param name="jointOp">
	///Specifies the joint operation"
	///&RVDataflowAnalysisInfo::intersectOp for "must" analyses;
	///&RVDataflowAnalysisInfo::unionOp for "may" analyses.
	///</param>
	///<param name="pGraph">a pointer to the ready dataflow graph</param>
	///<param name="typeName">the name of the analysis type</param>
	RVMonotonousFramework(const RVJoint &jointOp,
			              RVDataflowGraph *pGraph,
			              const std::string& typeName);

	///<summary>
	///Constructor that builds a dataflow graph for the given block <paramref name="b" />.
	///</summary>
	///<param name="jointOp">
	///Specifies the joint operation"
	///&RVDataflowAnalysisInfo::intersectOp for "must" analyses;
	///&RVDataflowAnalysisInfo::unionOp for "may" analyses.
	///</param>
	///<param name="b">the code block</param>
	///<param name="typeName">the name of the analysis type</param>
	///<param name="backwardDirection"><b>true</b> for backward directed analyses</param>
	RVMonotonousFramework(const RVJoint &jointOp,
			              RVIntraProcDataflowGraphBuilder *,
			              const std::string& typeName);

	///<summary>
	///Almost copy-constructor that receives an alternative dataflow graph <paramref name="rGraph" />.
	///</summary>
	///<param name="o">the source object</param>
	///<param name="rGraph">the alternative dataflow graph</param>
	RVMonotonousFramework(const RVMonotonousFramework &o,
			              const RVDataflowGraph &rGraph);

	///<summary> Executes kill&gen operation over the given node. </summary>
	///<param name="io"> input/output analysis info for the given node </param>
	///<param name="e"> the expression identifying the dataflow graph node </param>
	///<param name="nodeIdx"> the index the given node </param>
	virtual void killgen(RVDataflowAnalysisInfo& io, Expression *e, int nodeIdx) = 0;

	virtual std::string getAnalysisBriefName(void) const;
	virtual std::string getAnalysisFullName(void) const;

	virtual SymbolVector* collectReadVars(Expression *e);

	const RVDataflowGraph& getGraph(void) const { return m_graph; }
	const RVDataflowAnalysisInfo& getInfoAt(int nodeIdx) const;
	void jointEnteringInfo(RVDataflowAnalysisInfo& in, int idx, bool report) const;

private:
	bool iterate(const std::vector<int>& vertIndices);
	void init(void);
    void initBeforeRun(void);
	const char *getJointOpName(void) const;
	bool isGraphReverse(void) const;
	const RVDataflowAnalysisInfo& getInfoAtArtificialNode(RVDummyNodeType type) const;
	std::string indent(void) const { return std::string(2U*getIndent(), ' '); }
	std::string eolWIndent(void) const { return "\n" + indent(); }

private:
	RVDataflowGraph*                    m_pGraphToDelete;
	const RVDataflowGraph&              m_graph;
	std::vector<RVDataflowAnalysisInfo> m_out;
	std::vector<bool>                   m_prevChanged;
	std::vector<bool>                   m_freshChanged;
	RVJoint                             m_jointOp;
	std::string                         m_direction, m_analysisType, m_uniqName;
	RVDataflowAnalysisInfo              m_infoAtStart;
	RVExprToVars                        m_readVars;
	int                                 m_indent;
};




enum RVAnalysisRes { RVA_SUCCESS, RVA_FAILURE, RVA_FUNC_NOT_FOUND, RVA_REC_DEPTH, RVA_INC_DEPTH, RVA_INT_ERROR };




///<summary>
///Counter of unrolls of function calls. It is useful for preventing infinite
///unrolling of recursive funcions.
///</summary>
class RVUnrollCounter {
	struct RVUnrollCount {
		RVUnrollCount(unsigned limit = ms_initialLimit);
		bool inc(void);

		static const unsigned ms_initialLimit;
		unsigned m_curCount, m_maxCount;
	};

public:
	///<param name="nUnrolls">
	///the maximum limit of unrolls for every function
	///</param>
	RVUnrollCounter(unsigned nUnrolls);

	///<summary> Copy constructor </summary>
	RVUnrollCounter(const RVUnrollCounter& o);

	///<summary> Destructor </summary>
	~RVUnrollCounter();

	///<summary>
	///Increments the counter of the unrolls of the calls of function funcname
	///</summary>
	///<return>true iff the counter has not yet exceeded the allowed limit</return>
	bool incUnrollCounter(const std::string& funcname);

	///<summary>
	///Decrements the counter of the unrolls of the calls of function funcname
	///</summary>
	unsigned decUnrollCounter(const std::string& funcname);

	///<summary>
	///Increments the maximal depth of the unrolls of the calls of function
	///<paramref cref="funcname"/>, if the incremented value won't exceed
	///<paramref cref="limit"/>
	///</summary>
	///<return>RVA_SUCCESS if successfully incremented, RVA_REC_DEPTH otherwise</return>
	RVAnalysisRes incDepth(const std::string& funcname);

private:
	unsigned getLimit(void) const { return m_nUnrolls; }

	static const std::string ms_refCounter;
	unsigned m_nUnrolls;
	std::map<std::string, RVUnrollCount> *m_pInlinings;
};




///<summary>
///A framework for inter-procedural analyses that run over outlined dataflow
///graphs (i.e., a graph per each function affiliated through RVFuncAnalysesDb).
///</summary>
abstract class RVInterProcOutlineAnalysis : public RVMonotonousFramework {
public:
	virtual ~RVInterProcOutlineAnalysis();

	///<summary>
	///Creates the same analysis to be run over the given dataflow graph
	///</summary>
	virtual RVMonotonousFramework *createAnalysis(const RVDataflowGraph&) const = 0;

	void setStartFunc(SymEntry* const startFunc);

protected:
	///<summary>
	///Constructor that builds a dataflow graph from the given statement
	///</summary>
	RVInterProcOutlineAnalysis(const RVJoint& jointOp,
			                   RVInterProcGraphBuilder*,
							   const std::string& typeName,
							   unsigned nUnrolls,
							   const Symbol *startFunc);

	///<summary> Constructor that receives a ready dataflow graph </summary>
	RVInterProcOutlineAnalysis(const RVJoint& jointOp,
					 		   const RVDataflowGraph&,
							   const std::string& typeName,
							   unsigned nUnrolls,
							   const Symbol *startFunc);

	///<summary> Copy-constructor with an alternative dataflow graph </summary>
	RVInterProcOutlineAnalysis(const RVInterProcOutlineAnalysis& o,
					 		   const RVDataflowGraph& g);

	///<summary> Implements the pure method declared in the super class </summary>
	///<seealso cref="RVMonotonousFramework" />
	///<param name="io"> input/output analysis info for the given node </param>
	///<param name="e"> the expression identifying the dataflow graph node </param>
	///<param name="nodeIdx"> the index the given node </param>
	virtual void killgen(RVDataflowAnalysisInfo& io, Expression *e, int nodeIdx);

	///<summary> Executes kill&gen operation over the given node. </summary>
	///<param name="io"> input/output analysis info for the given node </param>
	///<param name="e"> the expression identifying the dataflow graph node </param>
	///<param name="nodeIdx"> the index the given node </param>
	///<param name="nodeIdx">
	///an indicator that this is a function call node, such that the analysis
	///for the function failed running or was not run because its unroll count
	///exceeded the allowed maximum
	///</param>
	virtual void killgenRegNode(RVDataflowAnalysisInfo& io,
			                    Expression *e,
			                    int nodeIdx,
			                    bool intraProcAnalFailed) = 0;

	///<summary> Processes a function call node </summary>
	///<param name="symname"> the name of the called function </param>
	///<param name="startPoint">
	///flag pointing that this is the starting function call of the analysed
	///code (like main() in C)
	///</param>
	///<param name="io"> input/output analysis info for the given node </param>
	///<param name="callExpr"> the call expression for gaining info about context </param>
	virtual RVAnalysisRes procFunction(const Symbol *symname,
			                           bool startPoint,
			                           RVDataflowAnalysisInfo& io,
			                           Expression *callExpr);

	///<summary>
	///Callback upon exceeding unroll limit due to recursive calls and loops
	///</summary>
	virtual RVAnalysisRes reachedUnrollLimit(const Symbol *funcname,
			                                 RVDataflowAnalysisInfo& io);

	const Symbol* getStartFunc(void) const { return &m_startFunc; }

	static FunctionCall *getCalledFuncName(Expression *e, Symbol **pSymbPtr = NULL, bool *pWrapped = NULL);

private:
	RVAnalysisRes runIntraAnalysis(RVMonotonousFramework **ppAnal,
			                       const Symbol *funcname,
                                   RVDataflowAnalysisInfo& io);
    RVFuncAnalysesDb **accessIntraAnalysisDb(void) const;

    static const SymEntry* ms_noStartFunc;
	Symbol                 m_startFunc;
	RVUnrollCounter        m_unrolls;
};



///<summary>
///An example how to implement an inter-procedural dataflow analysis.
///Analysis type: flow-sensitive, "may", forward direction.
///Counts the maximal number of calls of each traced function in any
///non-recursive sequence.
///<summary>
class RVFuncCallCountAnalysis : public RVInterProcOutlineAnalysis {
public:
	typedef int TCounter;

	///<summary>Constructor that builds the dataflow graph of the given block </summary>
	RVFuncCallCountAnalysis(Statement *b, unsigned nUnrolls);

	virtual ~RVFuncCallCountAnalysis() {}

	///<summary>
	///Creates a new instance of RVFuncCallCountAnalysis to be run over the
	///given dataflow graph
	///</summary>
	virtual RVMonotonousFramework *createAnalysis(const RVDataflowGraph&) const;

	///<summary> Adds a function for tracing </summary>
	void addCallee(const std::string& name) { m_sCallees.insert(name); }

	///<summary> Returns the result for the given function </summary>
	unsigned int countCalls(SymEntry* const startFunc,
			                const std::string& callee);

protected:
	///<summary> Processes a function call node </summary>
	///<param name="symname"> the name of the called function </param>
	///<param name="startPoint">
	///flag pointing that this is the starting function call of the analysed
	///code (like main() in C)
	///</param>
	///<param name="io"> input/output analysis info for the given node </param>
	virtual RVAnalysisRes procFunction(const Symbol *symname,
			                           bool startPoint,
			                           RVDataflowAnalysisInfo& io,
			                           Expression *callExpr);

	///<summary> Executes kill&gen operation over the given node. </summary>
	///<param name="io"> input/output analysis info for the given node </param>
	///<param name="e"> the expression identifying the dataflow graph node </param>
	///<param name="nodeIdx"> the index the given node </param>
	///<param name="nodeIdx">
	///an indicator that this is a function call node, such that the analysis
	///for the function failed running or was not run because its unroll count
	///exceeded the allowed maximum
	///</param>
	virtual void killgenRegNode(RVDataflowAnalysisInfo& io,
				                Expression *e,
				                int nodeIdx,
				                bool intraProcAnalFailed);

	///<summary>
	///Callback upon exceeding unroll limit due to recursive calls and loops
	///</summary>
	virtual RVAnalysisRes reachedUnrollLimit(const Symbol *funcname,
				                             RVDataflowAnalysisInfo& io);
private:
	typedef RVInterProcOutlineAnalysis super;

	RVFuncCallCountAnalysis(const RVFuncCallCountAnalysis &,
			                const RVDataflowGraph &);

	unsigned int getK(const std::string& callee) const;

	static void killgenNodeLow(RVDataflowAnalysisInfo& io,
			                   int delta,
			                   const std::string& funcname);
	static void mergeCallCounts(RVDataflowAnalysisInfo& io,
			                    RVDataflowAnalysisInfo& funcOut,
			                    const Symbol* ignored);

	static const std::string ms_sAnalysisType;
	std::set<std::string>    m_sCallees;
	SymEntry                *m_startSymbolEntry;
};



class RVWriteVarAnalysis;

///<summary>
///An example how to implement an intra-procedural dataflow analysis.
///Analysis type: flow-sensitive, "may", forward direction
///<seealso cref="RVVarAnalysisRecord" />
///<summary>
class RVUninitVarAnalysis : public RVMonotonousFramework {
public:
	///<summary>Constructor that gets a ready dataflow graph </summary>
	RVUninitVarAnalysis(RVDataflowGraph&);
	///<summary>Constructor that builds the dataflow graph of the given block </summary>
	RVUninitVarAnalysis(Statement *b);
	virtual ~RVUninitVarAnalysis();

	void getUninitializedVars(SymbolVector&) const;

protected:
	///<summary> Executes kill&gen operation over the given node. </summary>
	///<param name="io"> input/output analysis info for the given node </param>
	///<param name="e"> the expression identifying the dataflow graph node </param>
	///<param name="nodeIdx"> the index the given node </param>
	virtual void killgen(RVDataflowAnalysisInfo& io, Expression *e, int nodeIdx);

private:
	void addRead(Symbol *, RVDataflowAnalysisInfo& in, int nodeIdx);

private:
	static RVWriteVarAnalysis& prepareWriteVarAnalysis(const RVDataflowGraph&);

	RVWriteVarAnalysis& m_writeAnal;
};


///<summary>
///An example how to implement an intra-procedural dataflow analysis.
///Analysis type: flow-sensitive, "may", backward direction
///<seealso cref="RVVarAnalysisRecord" />
///<summary>
class RVLiveVarsAnalysis : public RVMonotonousFramework {
public:
	///<summary>Constructor that builds the dataflow graph of the given block </summary>
	RVLiveVarsAnalysis(Statement *b);
	virtual ~RVLiveVarsAnalysis();

	///<summary>
	///Retrieves the names of live variables at the end of a loop identified with <paramref name="loopStmt" />
	///<summary>
	///<param name="v">destination of the retrieved live variable names.</param>
	///<param name="loopStmt">the identifier of the loop</param>
	///<returns><b>true</b> iff there was no error. </returns>
	bool getLiveVarsAtEndOfLoop(SymbolVector& v, const Statement* loopStmt) const;

protected:
	///<summary> Executes kill&gen operation over the given node. </summary>
	///<param name="io"> input/output analysis info for the given node </param>
	///<param name="e"> the expression identifying the dataflow graph node </param>
	///<param name="nodeIdx"> the index the given node </param>
	virtual void killgen(RVDataflowAnalysisInfo& io, Expression *e, int nodeIdx);

};

#endif /* RV_DATAFLOW_H_ */
