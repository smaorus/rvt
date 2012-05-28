#ifndef RV_REPLACE_H
#define RV_REPLACE_H

#include <string>
#include <rv_walk.h>
#include "rv_side.h"
#include "rv_etc.h"

class RVFuncPair;
class ScopeTbl;
class FunctionCall;
class RVDirectives;
class RVTemp;
struct RVDecisionParams;


/* RVRenameTree
     renames global func and var identifiers in the parse tree.
     All symbols related to global declarations and typedefs are
     renamed. Also is used to insert the right code in the check
     points according to their labels.
*/

class RVRenameTree : public RVWalk, public RVIDischargee
{
  protected:
    Project* parsetree;
    const RVSide side;

    RVDirectives* directs;

    FunctionDef* body;
    Block* current_block;

    RVFuncPair* semchk_pair;
    bool semchk_recursive;
    bool semchk_use_uf_prefix;
    Symbol* semchk_uf_sym;
    FunctionDef* semchk_func;

    ScopeTbl*     rvact_scope;
    Decl*         rvact_decl;
    FunctionCall* rvact_call;

    Expression** def_rvact_vals;
    
    // for special care of recursion, and loops when they are not "the pair"
    // that is compared

    std::string  current_func_name;
    bool m_bSymbolForTypeName;
//  DIMA_DEL
//    std::set<std::string> recursive_func_lst;

    bool rename_globs(HashTbl* ht, const RVDecisionParams &, bool tags = false);

    Expression* gen_check_point_code(ExprVector& vals, std::string& type_name);

    bool fix_loop_pvars(Variable** pit);
    bool fix_symbol_entry(Symbol* sym);    

    void update_symbol(Symbol* sym, SymEntry* new_se) const;
    void changeBaseTypeName(BaseType *bt, const std::string& newName) const;
    void copyFromEntryName(Symbol* sym) const;
    void copyFromEntryNameCond(Symbol* sym) const;
    void changeSymbolName(Symbol* sym, const std::string& newName) const;
    static void prependPrefix(std::string& name, const std::string prefix);

  public:
    static BaseType* channel_type; 

    RVRenameTree(Project* _tree, const RVSide& _side);
    virtual ~RVRenameTree();

    void delete_parsetree() { delete parsetree; parsetree = NULL; }

    void set_semchk_pair(RVFuncPair* pair, bool recursive);

//  DIMA_DEL
//    void set_recursive_func_lst(const std::set<std::string>& the_lst)
//    {
//        recursive_func_lst = the_lst;
//    }
//
//    const std::set<std::string>& get_recursive_func_lst(void) const
//    {
//        return recursive_func_lst;
//    }

    bool is_recursive_func(const std::string& fname) const;
    void set_directs(RVDirectives* _dirs);

    //bool identify_recursive_functions(int side, std::vector <std::string> *special_func_lst);
    bool remove_unneeded_funcs();
    //bool remove_call_for_loop_func(int side);
    bool print_uf_rec_decl(const std::string& fname, std::ostream& out);
    bool is_outlined(BinaryOp    bOp);
    std::string get_outlined_name(BinaryOp    bOp);

    std::string add_prefix(std::string& name, const char* prefix);

    bool rename_all_globs(const RVDecisionParams &);
      /* adds RVTemp::get_side_prefix(current_side)  or 
	    RVTemp::get_semchk_prefix(current_side) */

    bool rename_all_tags(const RVDecisionParams &);

    bool rename_all(const RVDecisionParams &);

    bool print_all(RVTemp& temps, bool print_decls = true, bool print_funcs = true) const;

    bool create_rvact_proto();

    bool create_semchk_uf_proto(Decl**);

    bool process_func(FunctionDef *_body);

    virtual bool process_block(Block* it);       /* update current_block */ 

    virtual bool process(Symbol* it);    /* copy it->name from entry */

    virtual bool process(SymbolVector& vec);
    virtual bool process(DeclVector& vec) { return go(vec); }

    virtual bool try_replace(Statement** pit);  /* insert RVCHECK/RVSAVE() */
    virtual bool try_replace(Expression** pit); /* add LOOP_DEREF_PREFIX */

    virtual bool process_basetype(BaseType* it);  /* fix tag names */
    virtual bool process(EnumDef* it);
    virtual bool process(StructDef* it);
    virtual bool process(Decl* it);

    /* process as usual: */
    virtual bool process(Statement* it)  { return go(it); }
    virtual bool process(Expression* it) { return go(it); } 
    virtual bool process(Type* it)       { return go(it); }
    virtual bool process_const(Constant* it) { return go_const(it); }

    // Interface RVIDischargee:
    virtual void discharge(RVDischarger&);
};






/* RVLoopReplaceBase
     the base of all replacing abilities.
     Traverses the code and lets try_replace(Statement**) and
     try_replace(Expression** pst) replace statements or
     expressions.
*/

class RVLoop;
class ScopeTbl;

#include <ctool/stemnt.h>

class RVLoopReplaceBase : public RVWalk
{
  protected:
    bool break_from_switch;

  public:
    RVLoopReplaceBase();
    virtual ~RVLoopReplaceBase() {}

    static void copy(LabelVector& dest, const LabelVector& src);

    /* try_replace() returns true if replaced anything */
    virtual bool try_replace(Statement** pst) = 0;
    virtual bool try_replace(Expression** pst) = 0;

    virtual bool process(Statement* it);
    virtual bool process(Expression* it) { return RVWalk::process(it); }

    virtual bool process(Symbol* it) { return true; /* ignore by default */}

    /* ignore the next parts of the code: */
    virtual bool process(Type* it) { return true; }
    virtual bool process_const(Constant* it) { return true; }
    virtual bool process(Label* it)   { return true; }
    virtual bool process(EnumDef* it) { return true; }
    virtual bool process(StructDef* it)  { return true; }
    virtual bool process_function_type(FunctionType* it) { return true; }
    virtual bool process_basetype(BaseType* it) { return true; }
};



class RVReplaceInLoops : public RVLoopReplaceBase
{
  protected: 
    RVLoop*     loop;
    ScopeTbl*   scope;
    Statement*  res;

    bool replace_parts(Statement* s0p);

    bool replace_by_call(Statement** pst, Expression* init);

    Statement* find_containing_block(Symbol* label);

    Block* make_loop_return_block(Expression* result, 
				  unsigned termination_code, Location& l);

  public:
    RVReplaceInLoops();
    virtual ~RVReplaceInLoops() {}

    bool replace(RVLoop* _loop);

    Statement* get_res();

    /* don't replace component symbols - process only left side. */
    bool process_member_op(BinaryExpr* s0p);

    /* try_replace() returns true if replaced anything */
    virtual bool try_replace(Statement** pst);
    virtual bool try_replace(Expression** pst); 
};




/* RVReplaceLoopCalls
     processes in place a single function,
     replaces all top level loops (which are not nested in other loops),
     by calls to recursive functions.
     Also adds the Decl of LOOP_RETVAL to the function.
*/

class RVReplaceLoopCalls : public RVLoopReplaceBase
{
  protected: 
    FunctionDef* body;

    Project* parsetree;

    Symbol* retvar;	
    bool replace_by_call(Statement** pst, Expression* init);
    bool create_retvar();

  public:
    RVReplaceLoopCalls();
    virtual ~RVReplaceLoopCalls() {}

    bool replace(FunctionDef* _body, Project* _parsetree = NULL);

    /* try_replace() returns true if replaced anything */
    virtual bool try_replace(Statement** pst);
    virtual bool try_replace(Expression** pst) { return true; }
};




class RVReplaceType : public RVWalk
{
  protected:
    Project* parsetree;
    int side;
    FunctionDef* body;

    const Type *from;
    Type *real_from;
    Type *into;

  public:
    RVReplaceType(const Type* _from, Type* _into);
    virtual ~RVReplaceType() {}

    bool replace_all(Project* _tree, int _side);    

    bool process_func(FunctionDef *_body);

    virtual bool try_replace(Type** it);
};

#endif /* RV_REPLACE_H */
