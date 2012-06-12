#ifndef RV_COLLECT_H
#define RV_COLLECT_H

#include <rv_walk.h>
#include <rv_funcnode.h>
#include <rv_arrays.h>


class RVCollectBase : public RVWalk
{
  protected:
    FunctionDef *body;
    Project     *parsetree;
    int          side;

    std::vector<Statement*> lstack; /* stack of nested loop statements */
    int top_loops_cnt;              /* top (function) level loops count */

    bool first_decl_in_block;

    Symbol* get_pointer_in_offset_expr(Expression* s0p); 

    void add_callees( Symbol *sym, int num_args );
    void add_read( Symbol *sym );
    void add_written( Symbol *sym );
    void add_argtype(int ind, ArgType type);

    void add_scope_vartype(Symbol* sym, bool is_written);

    void add_label_to_block( Symbol *sym );

    void start_func(); /* children must call before preccecing new func */

    /* Things for collecting array refs: */
    RVCollectArrayRefs* array_ref_collector;

    bool collect_array_ref(Expression* expr);
    bool try_collect_non_offset_expr(Expression* expr);

  public:
    RVCollectBase();
    virtual ~RVCollectBase() 
      { /* doesn't own parsetree nor body */ }

    void set_array_ref_collector(RVCollectArrayRefs* arc);

    virtual bool process(Statement* it);
    virtual bool process(Decl* it); /* only for local initializers */
    virtual bool process_block(Block* it);

    virtual bool process(Expression* it) { return go(it); }

    /* ignore the next parts of the code: */
    virtual bool process(Type* it) { return true; }
    virtual bool process_const(Constant* it) { return true; }
    virtual bool process(Label* it)   { return true; }
    virtual bool process(Symbol* it)  { return true; }
    virtual bool process(EnumDef* it) { return true; }
    virtual bool process(StructDef* it)  { return true; }
    virtual bool process_function_type(FunctionType* it) { return true; }
    virtual bool process_basetype(BaseType* it) { return true; }
};


class RVDirectives;

/* RVCollect -
     an object to traverse the function code and 
     collect caller(s) and callee(s) info, also read and writen global
     vars, and ArgType info for function arguments.
     Uses RVWalk as a framework to traverse the function code.
*/

class RVCollect : public RVCollectBase
{
  protected:
    RVDirectives *directs;

    Symbol* symbol_already_collected;
    bool    next_symbol_is_unused;
    bool    m_bPartEquivCheck;

    int omega_deref_bound;
	bool left, right;

private:
    bool collect_bodyless();
	void mark_aliased(Symbol* sym, Expression* leftExpr, Expression *rightExpr, bool pointer_deref);

  public:
    RVCollect(bool part_equiv_check);
    virtual ~RVCollect() {}

    void init();

    bool init_argtypes( FunctionDef *func );

    bool collect( FunctionDef *_body, Project *_parsetree, 
		  RVDirectives* _directs, int _side );

    virtual bool process(Statement* it);
    virtual bool process(Expression* expr);
    virtual bool process(Decl*);
    virtual bool process_binary(BinaryExpr* it);

    Symbol* get_assigned_symbol(Expression* s0p, bool* pderef, bool* parray);
    Symbol* get_assigning_symbol(Expression* s0p);
    
    bool process_deref(Expression* it, bool is_read, bool is_written, bool is_array = false);

    void collect_symbol(Symbol* sym, bool is_read, bool is_written,
			bool is_deref = false, bool is_array = false);

    int get_omega_deref_bound() { return omega_deref_bound; }
};



/* 
  RVPropArgTypes
    a class used in pair with RVArgTypesDfs to propagate the ArgTypes of function
    arguments up the call graph. 
    RVPropArgTypes traverses each function body and 
    propagates the ArgTypes up from function calls it encounters.
    Arguments passed by reference and array indexing and pointer
    offsets need special treatment.
    RVArgTypesDfs does the DFS part between the functions.
*/

class RVArgTypesDfs;

class RVPropArgTypes : public RVCollectBase
{
  friend class RVArgTypesDfs;

  protected:
    ArgType argtype_for_next_var;

  public:
    RVArgTypesDfs* dfs;

    RVPropArgTypes(RVArgTypesDfs* _dfs);
    virtual ~RVPropArgTypes() {}

    void set_friend(RVArgTypesDfs* _dfs);
    void set_params(Project *_parsetree, int _side);
    
    void go_sons(FunctionDef* it);

    /* some functions (assume, assert, rv_getint, ...) should be ignored: */
    bool ignore_function_call(FunctionCall* call);

    virtual bool process(Expression* expr);

    void add_argtype_from_callee(Expression* s0p, FunctionDef* func, int ind);
    void add_symbol_argtype(ArgType at, Symbol* sym);    
};


#endif /* RV_COLLECT_H */
