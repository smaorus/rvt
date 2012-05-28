#ifndef _RvTraversal_h
#define _RvTraversal_h

#include <ctool/Traversal.h>
#include <rv_ctool.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "rv_side.h"

// This data structure is per identified array
//
enum algType
{
    Fixed_Size_NMAC,        // method 1 fixed size no macros
    finite_CBMC_MAC,        // method 2 fixed size use CBMC macros
    finite_CBMC_MAC_SHADOW, // method 3 type 1 finite size + macros
    inf_CBMC_MAC_SHADOW     // method 3 type 2 infinite size + macros
};

enum arrType {
    REG_arr,
    PTR_arr,
    MALLOC_arr
};


class array_item {
public:
  algType  alg_type;
  arrType  arr_type;
  int      array_size;
  int      dimension;
  Symbol   *sym;
  Symbol   *orig_sym;
  std::vector<FunctionCall *> array_access;

  // constrcutor
  array_item(algType alg, arrType ty, Symbol *tsym, int dim=1 )
  {
      alg_type   = alg;
      sym        = tsym;
      array_size = -1;
      arr_type   = ty;
      dimension = dim;
      orig_sym   = NULL;
  }

  void set_size(int sz) 
  {
      array_size = sz;
  }

  std::string prt_arr_type(arrType ty, std::ostream& out  ) const {
      std::string ret;

      switch(ty) {
          case REG_arr    : ret = "REG_arr "; break;
          case PTR_arr    : ret = "PTR_arr " ; break;
          case MALLOC_arr : ret = "MALLOC_arr "; break;
          default : break;
      }

      return ret;
  }

  std::string prt_alg_type(algType ty, std::ostream& out ) const {
      std::string ret;

      switch(ty) {
          case Fixed_Size_NMAC       : ret = "Fixed_Size_NMAC"; break;
          case finite_CBMC_MAC       : ret = "finite_CBMC_MAC "; break;
          case finite_CBMC_MAC_SHADOW: ret = "finite_CBMC_MAC_SHADOW "; break;
          case inf_CBMC_MAC_SHADOW   : ret = "inf_CBMC_MAC_SHADOW "; break;
          default : ret = "NO_ALG_TYPE_ERR" ; break;
      }
      return ret;
  }

  bool find_sym(Symbol *tsym) {      
      return (
		  (sym->entry == tsym->entry) && 
		  (sym->entry->scope == tsym->entry->scope));            
  }

  bool find_sym(Symbol *tsym, int *sz) {
      bool ret;

      (*sz) = 0;
	  if (sym == NULL) return false; // Dima: tried to add: || sym->entry == NULL, but it leads to an infinite loop in find_arrays().
      ret = ((sym->entry == tsym->entry) && (sym->entry->scope == tsym->entry->scope));
      if (ret) { (*sz) = array_size; }
      return ret;
  }

  void print( std::ostream& out) const;
 
    friend std::ostream& operator<< ( std::ostream& out, const array_item& i );
};


class RvTraversal : public Traversal , public RVCtool
{
public:
  RvTraversal(std::ostream &, bool);
  virtual void traverse_base(BaseType *);
  virtual void traverse_ptr(PtrType *);
  virtual void traverse_array(ArrayType *);
  virtual void traverse_bit_field(BitFieldType *);
  virtual void traverse_function(FunctionType *);

  virtual void traverse_symbol(Symbol *);

  virtual void traverse_int(IntConstant *);
  virtual void traverse_uint(UIntConstant *);
  virtual void traverse_float(FloatConstant *);
  virtual void traverse_char(CharConstant *);
  virtual void traverse_string(StringConstant *);
  virtual void traverse_array(ArrayConstant *);
  virtual void traverse_enum(EnumConstant *);
  virtual void traverse_variable(Variable *);
  virtual void traverse_call(FunctionCall *);

  virtual void traverse_unary(UnaryExpr *);
  virtual void traverse_binary(BinaryExpr *);
  virtual void traverse_trinary(TrinaryExpr *);
  virtual void traverse_assign(AssignExpr *);
  virtual void traverse_rel(RelExpr *);
  virtual void traverse_cast(CastExpr *);
  virtual void traverse_sizeof(SizeofExpr *);
  virtual void traverse_index(IndexExpr *);

  virtual void traverse_label(Label *);
  virtual void traverse_decl(Decl *);

  virtual void traverse_statement(Statement *);
  virtual void traverse_file_line(FileLineStemnt *);
  virtual void traverse_include(InclStemnt *);
  virtual void traverse_end_include(EndInclStemnt *);
  virtual void traverse_expression(ExpressionStemnt *);
  virtual void traverse_if(IfStemnt *);
  virtual void traverse_switch(SwitchStemnt *);
  virtual void traverse_for(ForStemnt *);
  virtual void traverse_while(WhileStemnt *);
  virtual void traverse_do_while(DoWhileStemnt *);
  virtual void traverse_goto(GotoStemnt *);
  virtual void traverse_return(ReturnStemnt *);
  virtual void traverse_declaration(DeclStemnt *);
  virtual void traverse_typedef(TypedefStemnt *);
  virtual void traverse_block(Block *);
  virtual void traverse_function_definition(FunctionDef *);
  virtual void traverse_unit(TransUnit *);

  void prt_scopelevel(int level);
  static bool is_alloc(std::string name);
  bool is_array_exp(Expression *exp , Symbol **sym);
  void find_arrays( TransUnit *unit, const RVSide& side);
  void clear_arrays(int side) ;
  
  int  current_fixed_array_size; // hold the current size
  int  current_array_dimension;

  std::vector<array_item *> array_vec0;
  std::vector<array_item *> array_vec1;
  std::vector<int>          array_sizes; // for method 2, need array sizes

  void prt_array_vec(int side, int stage);
  void side_push_back(const RVSide& side, array_item *item);

  bool find_sym_func(Symbol *sym , std::string current_func, int side, int *the_sz);

  array_item *get_arr_item(const RVSide& side, int item_num);
  int get_arr_sz(const RVSide& side) const;

  int get_array_dimension(ArrayType *arr);
  int get_the_malloc_size(ExprVector    args);
  int get_const_val(Constant *tconst);
  int get_size_of_val(SizeofExpr *sz_expr);
  int find_sym(Symbol *sym , int *sz, Symbol ** orig_sym, const RVSide& side);
  int find_sym(Symbol *sym,  const RVSide& side);
  void create_nondet_vec();
  Symbol *get_orig_orig(Symbol *sym);
  void   get_ref_ptr(Expression *exp, int *num_deref, int *ptr_nesting);
  bool   is_ptr_arithmetic(Expression *exp);
  Symbol* get_assigned_ptr_sym(Expression* s0p);
  Symbol* ptr_var2symbol(Expression* expr);


private:
  void block(Statement *);

  std::ostream &out;
  bool          debug;
  int           level;
  bool          show_base;
  bool          disabled;
  RVSide        this_side;
};

extern RvTraversal *arrhooks;

#endif
