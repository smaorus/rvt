#ifndef RV_LOOPS_H
#define RV_LOOPS_H

#include <rv_funcnode.h>
#include <rv_ctool.h>

class Symbol;
class RVTemp;
class RVSide;

class RVLoop : public RVCtool
{
    static const char* LTC_VAR_NAME;

    FunctionType* proto;    /* of the recursive replacement */
    Statement*    new_loop_code;
    int           nested_count; /* counts nested loops - children of this loop */
	SymbolVector  refs_to_global; // [* ofer: save those pvar variables that we now turn into global variables *]
	SymbolVector  interimVars;    // external variables that are found to be used inside the loop only

  public:
    Symbol*       name;
    Statement*    block;
    FunctionDef*  orig_func;
    RVLoop*       parent;
    ScopeTbl*     proto_scope;
    Symbol*       retarg;   /* != NULL if the orig func return non-void */
    bool          has_break; // in loop body
	bool          has_continue;
    SymbolVector  used_labels;  /* labels to which we may goto from the loop */

    RVLoop(Statement* _block, FunctionDef *_orig_func, RVLoop* _parent);

    ~RVLoop();

    void print_proto(std::ostream& out);

    int inc_nested_count();
      
    static std::string ref_argname(std::string& name);
    static bool is_loop_name(const std::string& name, const RVSide&);

    /* the name of the recursive function: */
    Symbol* create_name(std::string parent_name, int cnt);

    /* generate the prototype for the recursiv func: */
    FunctionType* create_proto(ScopeTbl* file_scope, int side);

    /* call to the recursive func: */ 
    Statement*  create_call(Expression* init, Symbol* retsym, bool loop_has_return); 
	Statement*  create_call_from_loop(Expression* init, RVLoop* from_loop, Symbol* retsym, bool loop_has_return); 

    Expression* get_cond();
    Statement*  get_body();
    Symbol*     create_ret_symbol();

    /* generate the recursive function which replaces the loop: */
    bool gen_loop_func(RVTemp& temps);

    /* replace outvars in the loop code to pointer formal arguments,
       also replace "continue" and "break" by gotos: */
    void replace_vars_by_pointers(); 

  private:
    Symbol*   dup_caller_symbol(RVLoop *caller, Symbol* orig, bool& is_ref);
    void      add_call_args(FunctionCall* call, RVLoop* from_loop, Location& l);
    SymEntry* add_proto_arg(Symbol* base, bool pointer, Type* type);
    Block*    gen_loop_call_switch_body(RVLoop* from_loop, Location& l);
    void      filterOutInterimPvars(int side);
    void      declareInterimVars(RVTemp&) const;
};



class RVLoops : public std::vector<RVLoop*>
{
  public:
    int the_side;
    RVLoops() { }
    ~RVLoops();

    void clear();

    RVLoop* add_loop(Statement* block, FunctionDef *_orig_func, RVLoop* parent);
    void set_side(int side) {the_side = side;}

    bool print_protos(RVTemp& _temps, FunctionDef* caller, ScopeTbl* file_scope);

    /* generate all recuersive funcs from loops: */
    bool gen_loop_funcs(RVTemp& temps, FunctionDef* caller);

    int get_next_index() { return size(); }
};

extern RVLoops rv_loops;


#endif /* RV_LOOPS_H */
