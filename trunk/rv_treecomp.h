#ifndef RV_TREECOMP_H
#define RV_TREECOMP_H

#include <rv_ctool.h>
#include <rv_funcnode.h>
class RVFuncPairList;


/* RVTreeComp - 
     checks whether 2 expresion trees (or statement trees, or type definitions)
     are equal. The check is syntactic but ignores identifier names
     as long as they are of equal type. But function calls to
     functions which are already on the ufs list must be
     to paired functions to be considered equal.
     We check in the ufs list only when use_uf_lists is true.
     force_eq_comp_names=true is used mainly when comparing 
     on the same side - in such case we expect struct component names
     and function formal argument names to be exactly the same.
*/ 

class RVTreeComp : public RVCtool
{
	typedef const Expression *PC_Expression;

  public:
    RVTreeComp(bool _use_uf_lists = false, 
	           bool _force_eq_comp_names = false);

    bool eq_expr(const Expression* s0p, const Expression* s1p) const;
    bool eq_stmt(const Statement* s0p,  const Statement* s1p) const;
    bool eq_type(const Type* s0p, const Type* s1p) const;
	bool eq_type_loose(FunctionDef* s0p, FunctionDef* s1p) const; 
    bool eq_expr_vec(const ExprVector *s0p, const ExprVector *s1p) const;
    bool eq_struct_def(const StructDef *s0p, const StructDef *s1p) const;

    /* Constant is a type of Expression and deserves its own treatment: */
    bool eq_const(const Constant* s0p, const Constant* s1p) const;

    /* BinaryExpr has a lot of special cases - has its own compare function:*/
    bool eq_binary(const BinaryExpr* s0p, const BinaryExpr* s1p) const;

    /* FunctionType compare: */
    bool eq_function_type(const FunctionType* s0p, const FunctionType* s1p) const;

    /* Compare blocks: */
    bool eq_block(const Block* s0p, const Block* s1p) const;

    bool eq_enum_idents(const SymEntry* e0p, const SymEntry* e1p) const;
  
  protected:
    bool use_uf_lists;
    bool force_eq_comp_names;

    bool eq_basetype(const BaseType* s0p, const BaseType* s1p) const;
    bool eq_sizeof(const SizeofExpr* s0p, const SizeofExpr* s1p) const;
    bool eq_member_op(const BinaryExpr* s0p, const BinaryExpr* s1p) const;

    bool skip_unneeded_cast(PC_Expression& s0p, PC_Expression& s1p) const;
    bool mark_equal_labels(Symbol* s0p, Symbol* s1p) const;

    bool ignore_funcs(const Expression *s0p, const Expression *s1p) const;

    bool get_enum_val(const SymEntry* e0p, PC_Expression& out_base, unsigned& out_rel_ind) const;
};


#endif /* RV_TREECOMP_H */
