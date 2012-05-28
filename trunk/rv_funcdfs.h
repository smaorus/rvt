#ifndef RV_FUNCDFS_H
#define RV_FUNCDFS_H

#include <rv_ctool.h>

class SymbolVector;
class RVFuncNode;
class FunctionDef;

typedef  std::vector<FunctionDef*>  FuncVector;


/*
  RVFuncDfs 
    a DFS engine which runs on the function call graph.
    The links in the call graph are in RVFuncNodes.
    runs_counter counts always up so we don't have to clean
      RVFuncNodes::dfs_marks between runs.
    Note: because the use of runs_counter and RVFuncNode::dfs_marks
      you can't run two DFSs in parallel.
 */

class RVFuncDfs : public RVCtool
{
  protected:
    static long runs_counter;

    Project *parsetree;

    void go(FunctionDef* it);
    virtual void go_sons(FunctionDef* it, FuncVector &ret_sons);

  public:
    RVFuncDfs() { parsetree = NULL; }
    virtual ~RVFuncDfs() { }

    void new_run(FunctionDef* root);

    void set_parsetree(Project* pt) { parsetree = pt; }

    bool isNew(RVFuncNode* node);  /* first time we meet this node. */
    bool isNew(FunctionDef* func);
    bool isOnStack(RVFuncNode* node);  /* DFS has found a cycle */
    bool isOnStack(FunctionDef* func);
    bool isFinished(RVFuncNode* node); /* finished it and its whole subtree */
    bool isFinished(FunctionDef* func);

    /* returns a vector of son symbol (callees by default): */
    virtual SymbolVector& get_potential_sons(FunctionDef* it);

    /* don't enter these children nodes: */
    virtual bool ignore_son(Symbol* func_sym);

    /* executed before enter the children nodes: */
    virtual void before_sons(FunctionDef* it) {}  

    /* executed after enter the children nodes: */
    virtual void after_sons(FunctionDef* it, FuncVector& sons) {}

    /* executed on nodes which are isOnStack() or isFinished(): */
    virtual void revisit(FunctionDef* it) {}
};



class Project;
struct RVDecisionParams;

/*
  RVPropagateEquality
    a class to propagate equality or inequlaity up the call graph.
    Uses RVFuncDfs capabilities to do its work.
*/

//class RVPropagateEquality : public RVFuncDfs
//{
//  protected:
//    Project*     sides[2];
//    FunctionDef* roots[2];
//    int side;
//    RVDecisionParams& params;
//
//  public:
//    RVPropagateEquality(Project* _sides[2], std::string& _root_name,
//			RVDecisionParams& _params);
//    virtual ~RVPropagateEquality() {}
//
//    /* decide equality: */
//    virtual void after_sons(FunctionDef* it, FuncVector& sons);
//
//    /* worn mutually recursive functions: */
//    virtual void revisit(FunctionDef* it);
//};



/* 
  RVArgTypesDfs 
    a class used in pair with RVPropArgTypes to propagate the ArgTypes of function
    arguments up the call graph. RVArgTypesDfs is responsible for the DFS
    part between the functions when RVPropArgTypes does the traversing
    of each function body.
*/

class RVPropArgTypes;

class RVArgTypesDfs : public RVFuncDfs
{
  friend class RVPropArgTypes;

  protected:
    Project*     sides[2];
    FunctionDef* roots[2];
    int side;

    /* the DFS step itself - thru the function body using RVPropArgTypes */
    virtual void go_sons(FunctionDef* it, FuncVector &ret_sons);  

  public:
    RVArgTypesDfs() {}
    virtual ~RVArgTypesDfs() {}

    void propagate_argtypes(Project* _sides[2], std::string& root_name);
};


#include <rv_funcnode.h>

/* 
  RVGlobDfs
    used to collect all the read/written globals in a functions and
    its successors in the call graph.
*/
  
class RVGlobDfs : public RVFuncDfs
{
  protected:
    SymbolVector read, written;

  public:
    RVGlobDfs() { }
    virtual ~RVGlobDfs() { }

    void collect(Project* pt, FunctionDef* start, std::string& func_name, int _side);

    virtual void after_sons(FunctionDef* it, FuncVector& sons);

    void sort_vectors();

    bool equal_vectors(RVGlobDfs& other);

    SymbolVector& get_read()    { return read; }
    SymbolVector& get_written() { return written; }
};



/*
  RVMarkNeededDfs 
    is used to mark call cones on both sides.
    We don't traverse callees of functions which will be converted to UFs.
*/

class RVMarkNeededDfs : public RVFuncDfs
{
  protected:
    Project*     sides[2];
    FunctionDef* roots[2];
    int side;

  public:
    RVMarkNeededDfs(Project* _sides[2], const std::string& _root_name);
    virtual ~RVMarkNeededDfs() {}

    void mark_side(int _side);

    void mark_indirect_func_subtrees();

    /* the mark itself: */
    virtual void before_sons(FunctionDef* it);

    /* don't go down from UFs: */
    virtual void go_sons(FunctionDef* it, FuncVector &ret_sons);
};


#endif /* RV_FUNCDFS_H */
