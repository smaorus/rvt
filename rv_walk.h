#ifndef RV_WALK_H
#define RV_WALK_H

#include <rv_ctool.h>

#include <ctool/stemnt.h>


/* RVWalk 
     a framework for code traverseing. The go() and go_...() functions
     are used to recurse into statements, expressions and declarations.
     The process() and process_...() functions are for the user 
     to implement if he wants to do anything (collect or change)
     specific objects of the input type of the process() function.
     The user should implement them in a child of RVWalk.
     When implementing a process() function one should remember
     to call the appropreate go() function if he want's the traversal
     recurse into the substructures.
*/

class RVWalk : public RVCtool
{
  protected:
    char *where;  /* func name - for debug and error prints. */

    bool walk_goto_trg;

    bool decl_to_symbol; // set false to prevent such walk and thus infinite recursion 

    StructDef* recursive_struct; // the last recursive type encountered

    bool go(Expression* s0p);
    bool go(Statement* s0p);
    bool go(Type* s0p);
    bool go(ExprVector& s0p);
    bool go(StructDef* s0p);
    bool go(Symbol* s0p);
    bool go(Decl* s0p);
    bool go(DeclVector& s0p);
    bool go(SymEntry* s0p);
    bool go(Label* s0p);
    bool go(LabelVector& s0p);
    bool go(EnumDef* s0p);

    /* Contant is a typeof Expression and deserves its oun treatment: */
    bool go_const(Constant* s0p);

    /* BinaryExpr has a lot of special cases: */
    bool go_binary(BinaryExpr* s0p);

    /* Special Type case: */
    bool go_function_type(FunctionType* s0p);

    /* Special Statement case */
    bool go_block(Block* s0p);

    bool go_basetype(BaseType* s0p);
    bool go_struct_type(Type* s0p, bool use_tag = true);
    bool go_sizeof(SizeofExpr* s0p);
    bool go_member_op(BinaryExpr* s0p);

  public:
    RVWalk(bool _decl_to_symbol = false);
    virtual ~RVWalk();

    void set_where(const char* _where);

    void clear_recursive_struct()
    { recursive_struct = NULL; }

    StructDef* get_recursive_struct()
    { return recursive_struct; }

    /*==== Funcs which can be implemented by user (successor): ====*/
    virtual bool process(Expression* it) { return go(it); }
    virtual bool process(Statement* it)  { return go(it); }
    virtual bool process(Type* it)       { return go(it); }
    virtual bool process(ExprVector& it) { return go(it); }
    virtual bool process(StructDef* it)  { return go(it); }
    virtual bool process(Decl* it)       { return go(it); }
    virtual bool process(DeclVector& it) { return go(it); }
    virtual bool process(Symbol* it)     { return go(it); }
    virtual bool process(Label* it)      { return go(it); }
    virtual bool process(LabelVector& it) { return go(it); }
    virtual bool process(EnumDef* it)    { return go(it); }

    virtual bool process_const(Constant* it)    { return go_const(it); }
    virtual bool process_binary(BinaryExpr* it) { return go_binary(it); }
    virtual bool process_function_type(FunctionType* it) { return go_function_type(it); }
    virtual bool process_block(Block* it)       { return go_block(it); }
    virtual bool process_basetype(BaseType* it) { return go_basetype(it); }
    virtual bool process_member_op(BinaryExpr* it) { return go_member_op(it); }


    /*==== try_replace() returns true if process() should be called: ====*/
    virtual bool try_replace(Expression** it) { return true; }
    virtual bool try_replace(Statement** it)  { return true; }
    virtual bool try_replace(Type** it)       { return true; }
    virtual bool try_replace(StructDef** it)  { return true; }
    virtual bool try_replace(Decl** it)       { return true; }
    virtual bool try_replace(Symbol** it)     { return true; }
    virtual bool try_replace(Label** it)      { return true; }
    virtual bool try_replace(EnumDef** it)    { return true; }
    virtual bool try_replace(FunctionDef** it)  { return true; }

    static FunctionType *getFunctionFromFuncPtr(Type* tp);

};


#endif /* RV_WALK_H */
