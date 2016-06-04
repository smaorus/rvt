
/*  o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o
	o+
	o+     Programmer:   Yossi Levhari
	o+     Date:         2009-09-30
	o+
	o+     Traverse all elements in code
	o+
	o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o+o  */

using namespace std;

#include <limits.h>
#include "rv_consts.h"
#include <ctool/decl.h>
#include <ctool/stemnt.h>
#include <ctool/project.h>
#include <ctool/express.h>
#include <ctool/symbol.h>
#include <algorithm>
#include <vector>
#include "rv_error.h"
#include "rv_traversal.h"

#define DBG_TRV 0

static std::string current_function; 
static ScopeTbl* root_scope = NULL;

// scope
// function symbol pointer (if scope not global)
// array symbols
// 


void array_item::print(std::ostream& out) const
{
	out <<  "\n\nNAME                 " << sym->name  << std::endl; 
	out <<  "-----------------------------------" << std::endl; 
	out <<  "arr_type                 " << prt_arr_type(arr_type,out) << std::endl;
	out <<  "alg_type                 " << prt_alg_type(alg_type,out) << std::endl;
	out <<  "array_size               " << array_size << std::endl;
	out <<  "dim                      " << dimension  << std::endl;
	if (orig_sym) {
	   out <<  "orig_name                " << orig_sym->name  << std::endl; 
	} else {
	   out <<  "orig_name       NULL\n";
	}

	if (sym->entry->equalTo) {
	  out << "Equal to                 "  << sym->entry->equalTo->name << std::endl;
	} else { out << "Equal to nothing \n"; }
}


std::ostream& operator<< (std::ostream& out, const array_item& i)
{
	i.print(out);
	return out;
}

RvTraversal::RvTraversal(std::ostream &os, bool d)
   : out(os), debug(d), level(0), show_base(true), disabled(false),
     this_side(NO_SIDE) {
	 current_fixed_array_size = current_array_dimension = INT_MIN;
}

void RvTraversal::create_nondet_vec()
{
	int sz , sd;
	int i, last_val;
	std::vector<int>          array_sizes; // for method 2, need array sizes
	std::vector<array_item *> array_vec;
	std::vector<int>          tmp;

	for (sd=0;sd <2;sd++) {
	   sz        = (sd == 0) ? array_vec0.size() : array_vec1.size();
	   array_vec = (sd == 0) ? array_vec0 : array_vec1;

	   for (i=0;i<sz;i++) {
		   algType alg =  array_vec[i]->alg_type;

		   if ((alg  == finite_CBMC_MAC) || (finite_CBMC_MAC_SHADOW)) {
			   array_sizes.push_back(array_vec[i]->array_size);
		   }
	   }
	}
	sort(array_sizes.begin(),array_sizes.end());

	last_val = -1;
	sz = array_sizes.size();

	for (i=0;i < sz;i++) {
		if (last_val != array_sizes[i]) {
			tmp.push_back(array_sizes[i]);
			last_val = array_sizes[i];
		}
	}
	array_sizes.clear();
	array_sizes = tmp;

}

int RvTraversal::get_array_dimension(ArrayType *arr) {
	int dim = 1;
	ArrayType *tarr = arr;

	while (tarr->subType->type == TT_Array) {
		dim++;
		tarr = (ArrayType *) tarr->subType ;
	}
	return dim;
}

void RvTraversal::prt_array_vec(int side, int stage)
{
	int i;
	int sz = (side == 0) ? array_vec0.size() : array_vec1.size();

	if (DBG_TRV) {
		out << "Start Array_vec " <<  "side : " << side <<
		   ((stage == 1) ? " before loop conversion" : " after loop conversion" ) << "\n";

	 out << "----------------------------------------------------\n";

	if (side == 0) {
	   for (i=0;i<sz;i++) {
		   out << (*array_vec0[i]);
		   out << "\n";
	   }
	} else {
	   for (i=0;i<sz;i++) {
		   out << (*array_vec1[i]);
		   out << "\n";
	   }
	}
	out << "----------------------------------------------------\n";
	out << "End Array_vec\n\n\n";
	}

	if (stage == 1) create_nondet_vec();
}

bool RvTraversal::find_sym_func(Symbol *sym , std::string current_func, int side, int *the_sz) {
	std::vector<array_item *> array_vec = (side == 0) ? array_vec0 : array_vec1;
	int i,j;

	if (sym == (Symbol *) NULL ) return false; // ofer: used to be -1

	for(i = 0; i < (int) array_vec.size(); i++) {
	  if (sym->name == array_vec[i]->sym->name) {
		// Need to see if this is a function call that used it.
		int sz = array_vec[i]->array_access.size();
		//cout << "name : " << sym->name << " i : " << i << " j : " << j << "\n";
		for (j=0;j<sz;j++) {
			 Variable *func_var_exp = (Variable *) array_vec[i]->array_access[j]->function;
			 if (current_func ==  func_var_exp->name->name) {
				 (*the_sz) = array_vec[i]->array_size;
				 return true;
			 }
		}
	  }
	}
	return false;
}

///<summary>
/// checks whether 'sym' is an array on side 'side' 
///</summary>
int RvTraversal::find_sym(Symbol *sym, const RVSide& side) {
	  int i;	  
	  std::vector<array_item *> array_vec = side.select(array_vec0, array_vec1);

	  if (disabled) return (-1);	  	  
	  if (sym == (Symbol *) NULL ) return -1;

	  for(i = 0; i < (int) array_vec.size(); i++) {		
		  if (array_vec[i]->find_sym(sym)) { 		
			  return ((int) i);
		  }
	  }
	  return (-1);
}

///<summary>
/// checks whether 'sym' is an array on side 'side'. If yes updates sz with the size 
///</summary>
int RvTraversal::find_sym(Symbol *sym , int *sz , Symbol **org_sym, const RVSide& side) {
	  if (side.isIllegalIndex())
		  return -1;

	  int i;	  
	  std::vector<array_item *> array_vec = side.select(array_vec0, array_vec1);

	  if (disabled) return (-1);

	  (*org_sym) = (Symbol *) NULL;
	  if (sym == (Symbol *) NULL ) return -1;

	  for(i = 0; i < (int) array_vec.size(); i++) {

		  //
		  //if (array_vec[i]->sym == (Symbol *)NULL)   continue; // ofer
		  
		  if (array_vec[i]->find_sym(sym,sz)) { 
			  (*org_sym) = array_vec[i]->sym;
			  return i;
		  }
	  }
	  return (-1);
}

array_item *RvTraversal::get_arr_item(const RVSide& side, int item_num) {
    switch(side.index()) {
    case 0: return array_vec0[item_num];
    case 1: return array_vec1[item_num];
    }
    return NULL;
}

int RvTraversal::get_arr_sz(const RVSide& side) const {
    return side.select(array_vec0, array_vec1).size();
}

void RvTraversal::find_arrays( TransUnit *unit, const RVSide& side)
{
	int this_count=0, last_count = 0;
	bool found=true;
	Context *ctx;

	if (disabled) return;

	this_side = side;

	if (unit) {
		   ctx = &(unit->contxt);
		   root_scope = ctx->syms->root->children[0];
		   this->traverse_unit(unit);
		   while (found) {
			   this->traverse_unit(unit);
			   this_count = get_arr_sz(side);
			   found =  (this_count != last_count)  ? true : false;
			   last_count = this_count;
		   }
	}
}


void RvTraversal::clear_arrays(int side) 
{
	array_item *it;
	
	if (disabled) return;

	if (side == 0) {
		while (array_vec0.size()) {
			it = array_vec0.back();
			array_vec0.pop_back();
			delete it;
		}
	} else {
		while (array_vec1.size()) {
			it = array_vec1.back();
			array_vec1.pop_back();
			delete it;
		}
	}
}

void RvTraversal::traverse_base(BaseType *type)
{
	if (DBG_TRV) {
		out << "\ntraverse_base:\n";
		type->printType(out,NULL,true,0);
	}
}

void RvTraversal::traverse_ptr(PtrType *ptr)
{
	if (DBG_TRV) {
		out << "\ntraverse_ptr:\n";
		ptr->printType(out,NULL,true,0);
	}
}

void RvTraversal::traverse_array(ArrayType *arr)
{
	if (DBG_TRV) {
		out << "\ntraverse_array:\n";
		arr->printType(out,NULL,true,0);

	}
	int arraySize = -1;
	if (try_calc_constant_array_size_expression(arr->size, &arraySize)){
		current_fixed_array_size = arraySize;
	} 
	else {
		warn("ARRAY traverse should not be here\n", "RvTraversal::traverse_array");
	}

}

void RvTraversal::traverse_bit_field(BitFieldType *bfld)
{
	if (DBG_TRV) {
		out << "\ntraverse_bit_field:\n";
		bfld->printType(out,NULL,true,0);
	}
}

void RvTraversal::traverse_function(FunctionType *func)
{
	if (DBG_TRV) {
		out << "\ntraverse_function:\n";
		func->printType(out,NULL,true,0);
	}
}

void RvTraversal::traverse_symbol(Symbol *node)
{
	int sz;
	Symbol *org_sym;

	if (DBG_TRV) {
		out << "\ntraverse_symbol:\n";
		out << node->name << "\n";

	}

	if (node->entry && node->entry->IsVarDecl() && node->entry->uVarDecl->form->isArray() ) {
		/*
		out << node->name << " is array \n";
		prt_scopelevel(  node->entry->scope->level );
		*/

		// Explicit array so, going to Method 2
		//

		if (find_sym(node,&sz,&org_sym,this_side) == -1) {
			array_item *tmp_arr;
			tmp_arr = new array_item(finite_CBMC_MAC,REG_arr,node, current_array_dimension);
			if (DBG_TRV) out << "before push_back " << node->name << " " <<  current_fixed_array_size  << "\n";
			if (current_fixed_array_size != -1)
			   tmp_arr->set_size(current_fixed_array_size);
			//
			// change start
			//tmp_arr->orig_sym = node;;
			// change end
			side_push_back(this_side, tmp_arr) ;
		}
	}

	// in case it has a structure which has an array inside, there is need 
	// to mark the internal field as an array
}

void RvTraversal::traverse_int(IntConstant *node)
{
	if (DBG_TRV) {
		out << "\ntraverse_int:\n";
	}
}

void RvTraversal::traverse_uint(UIntConstant *node)
{
	if (DBG_TRV) {
		out << "\ntraverse_uint:\n";
	}
}

void RvTraversal::traverse_float(FloatConstant *node)
{
	if (DBG_TRV) {
		out << "\ntraverse_float:\n";
	}
}

void RvTraversal::traverse_char(CharConstant *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_char:\n";
  }
}

void RvTraversal::traverse_string(StringConstant *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_string:\n";
  }
}

void RvTraversal::traverse_array(ArrayConstant *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_array:\n";
  }
  if (!node->items.empty())
  {
	ExprVector::const_iterator i = node->items.begin();
	(*i)->accept(this);
	for (++i; i != node->items.end(); ++i)
	{
	  (*i)->accept(this);
	}
  }
}

void RvTraversal::traverse_enum(EnumConstant *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_enum:\n";
  }
  traverse_symbol(node->name);
  if (node->value)
  {
	node->value->accept(this);
  }
}

void RvTraversal::traverse_variable(Variable *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_variable:\n";
		node ->print(out);
		out <<"\n";
  }
  traverse_symbol(node->name);
}

///<summary>
/// Given a function call f(a, b, c) where e.g. a and c are arrays, and a function definition int f(int *x, int *y, int *z), this function adds x and z to the list of array names. 
///</summary>
void RvTraversal::traverse_call(FunctionCall *node)
{

	// Using two integer vectors, for ease of coding 
	// no need for a class as this is the only place it is used

	std::vector<int>    arr_lst;
	std::vector<int>    sz_lst;
	std::vector<Symbol *> sym_lst;
	Symbol *tmp_org;
	int j = 0;


	if (DBG_TRV) {
		out << "\ntraverse_call:\n";
		node->print(out);
		out << "\n";
	}
	node->function->accept(this);
	if (node->args.empty()) return;

	
		
		//if (((*i)->etype == ET_BinaryExpr) // ofer replaced with the one line below
		//	&& ((static_cast<BinaryExpr*>(*i))->op() == BO_Comma))
		//{
		//	(*i)->accept(this);
		//}
		//else
		//	(*i)->accept(this);

		/*(*i)->accept(this);

		if (is_array_exp((*i), &tmp_org)) {
			arr_lst.push_back(j);
			sz_lst.push_back(current_fixed_array_size);
			sym_lst.push_back(tmp_org);

			if (tmp_org) {
				int t_ind, sz;
				Symbol *tmp_org1;
				vector<FunctionCall *>::iterator it;

				if ((t_ind = find_sym(tmp_org,&sz,&tmp_org1,this_side)) != -1) {
					array_item  *arr_it;
					arr_it = (get_arr_item(this_side, t_ind));
					it = find(arr_it->array_access.begin(), arr_it->array_access.end(),node);
					if (it == arr_it->array_access.end()) arr_it->array_access.push_back(node);
				}
			}

		}
		j++;*/
		ExprVector::const_iterator i;
		for (i = node->args.begin(); i != node->args.end(); ++i)
		{
			/*if (((*i)->etype == ET_BinaryExpr)
				&& ((static_cast<BinaryExpr*>(*i))->op() == BO_Comma))
			{
				(*i)->accept(this);
			}
			else (*i)->accept(this);
*/
			(*i)->accept(this);
			if (is_array_exp((*i),&tmp_org)) {
				arr_lst.push_back(j);
				sz_lst.push_back(current_fixed_array_size);
				sym_lst.push_back(tmp_org);

				if (tmp_org) {
					int t_ind, sz;
					Symbol *tmp_org1;
					vector<FunctionCall *>::iterator it;

					if ((t_ind = find_sym(tmp_org,&sz,&tmp_org1,this_side)) != -1) {
						array_item  *arr_it;
						arr_it = (get_arr_item(this_side, t_ind));
						it = find(arr_it->array_access.begin(), arr_it->array_access.end(),node);
						if (it == arr_it->array_access.end()) arr_it->array_access.push_back(node);
					}
				}

			}

			j++;
		}

		// If the function call is with an argument that is an array
		// we need to go to the definition, and add the symbol of the
		// argument to the list of arrays

		if (arr_lst.size() > 0) {
			Variable *the_func_var  = (Variable *) node->function;
			FunctionDef *funcdef    = the_func_var->name->entry->u2FunctionDef;
			FunctionType *func_type  = (FunctionType *) 0;
			int sz = 0;
			int i = 0;

			if (!funcdef) {
				SymEntry   *func_entry;
				if ((func_entry=root_scope->Lookup(the_func_var->name->name))) {
					funcdef =  func_entry->u2FunctionDef;
				}
			}

			if (funcdef)  { // not "else" because the previous lines may create funcdef
				func_type =  (FunctionType *) funcdef->decl->form;
				sz = func_type->nArgs;
				for (j=0;j<sz;j++) {
					array_item *tmp_arr, *tmp_arr_lst;
					Symbol *org;
					int tmp_ind;

					if (j == arr_lst[i]) {
						//out << "index " << arr_lst[i] << " is arr\n";
						if (func_type->args[j]->name != NULL && find_sym(func_type->args[j]->name,&sz,&org,this_side) == -1) { // ofer: changed "func_type->args[i]->name != NULL" to "func_type->args[j]->name != NULL"
							//out << func_type->args[j]->name->name << " is the name of the new array" << "\n";
							if ((tmp_ind = find_sym(sym_lst[i],&sz,&org,this_side)) != -1) {
								tmp_arr_lst = get_arr_item(this_side, tmp_ind);
								tmp_arr = new array_item(tmp_arr_lst->alg_type,
									tmp_arr_lst->arr_type,
									func_type->args[j]->name);
								tmp_arr->set_size(sz_lst[i]);
								tmp_arr->orig_sym = sym_lst[i];
								side_push_back(this_side, tmp_arr) ;
							} else {
								out << "ERROR : the symbol " << sym_lst[i]->name << " can not be found\n";
								break;
							}
						}
						i++;
					}
					if (i == (int) arr_lst.size()) break;
				}
			}
		}
	
}


Symbol *RvTraversal::get_orig_orig(Symbol *sym)
{
	Symbol *org,*t_sym;
	int sz;
	bool orig_orig = false;
	int the_ind;
	Symbol *ret;

	t_sym = sym;

	if (!sym) out << "get_orig_orig: with null\n";

	while (!orig_orig)  {
	   ret = t_sym;
	   the_ind = find_sym(t_sym, &sz,&org,this_side);

	   if (the_ind == -1) {
		   out << "should not be here symbol : " << t_sym->name << "\n";
	   } else {
		   t_sym = this_side.select(array_vec0,array_vec1)[the_ind]->orig_sym;									

		   if (!t_sym) orig_orig = true;
	   }
	}

	if (t_sym) out << "get_orig_orig : " << t_sym->name << "\n";

	
	return ret;
}

void RvTraversal::traverse_unary(UnaryExpr *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_unary:\n";
		node->print(out);
		out << "\n";
  }

  if (!is_ptr_arithmetic(node)) {
	  Symbol *sym = get_assigned_ptr_sym(node);
	  if (sym) {
		  Symbol *tmp_origin;
		  int sz, ind;

		  if ((ind = find_sym(sym,&sz, &tmp_origin,this_side)) != -1) {
			  array_item *tmp = get_arr_item(this_side,ind);
			  if (tmp->arr_type != REG_arr) tmp->alg_type = finite_CBMC_MAC_SHADOW;
		  }
	  }
  }
}

void RvTraversal::traverse_binary(BinaryExpr *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_binary:\n";
		node->print(out);
		out << "\n";
  }
}

void RvTraversal::traverse_trinary(TrinaryExpr *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_trinary:\n";
		node->print(out);
		out << "\n";
  }
}


bool RvTraversal::is_array_exp(Expression *exp , Symbol **sym)
{
   bool ret;
   int sz;
   Symbol *org_sym = NULL;

   ret = false;

   (*sym) = (Symbol *) NULL;

  if (exp->etype != ET_BinaryExpr &&
	  exp->etype != ET_UnaryExpr &&
	  exp->etype != ET_Variable  &&
	  exp->etype != ET_TrinaryExpr &&
	  exp->etype!=ET_IndexExpr )
   {
	   ret = false;
   } else {
	  switch (exp->etype) {
		  case ET_BinaryExpr  : {
									BinaryExpr *bin_exp = (BinaryExpr *) exp; 
									ret = (is_array_exp(bin_exp->leftExpr(),sym) || is_array_exp(bin_exp->rightExpr(),sym)) ; 
									break;
								}
		  case ET_UnaryExpr   : {
									UnaryExpr *un_exp = (UnaryExpr *) exp; 
									if (un_exp->op() == UO_Deref) { ret = false;}
									else { ret = is_array_exp(un_exp->operand(),sym); }
									break;
								}
		  case ET_Variable    : {
									Variable *var_ptr = (Variable *) exp;
									if (find_sym(var_ptr->name, &sz,&org_sym,this_side) != -1) {
									   (*sym) = org_sym;
									   current_fixed_array_size = sz;
									   ret  = true;
									} else {
										(*sym) = var_ptr->name;
									}
									break;
								}
		  case ET_TrinaryExpr : {
									TrinaryExpr *tri_exp = (TrinaryExpr *) exp; 
									ret = (is_array_exp(tri_exp->trueExpr(),sym) || 
										   is_array_exp(tri_exp->falseExpr(),sym)) ; 
									break;
								}
		  case ET_IndexExpr   : ret = false; break; // YL need to think here
		  default             : ret = false;
	  }
   }
  return ret;
}


bool RvTraversal::is_alloc(std::string name) {
	bool ret;

	ret = ( name == "calloc" || name == "malloc" || name == "realloc" || name == "free" ||
			name == "memalign" || name == "_malloc_r" || name == "_realloc_r" ||
			name == "_memalign_r") ;
	return ret;
}

int RvTraversal::get_size_of_val(SizeofExpr *sz_expr)
{
	int ret = 0;

	switch(sz_expr->sizeofType->type) {
		case TT_Base     : ret = 4; break;
		case TT_Pointer  : ret = 4; break;
		default : break;
	}
	return ret;
}

int RvTraversal::get_const_val(Constant *tcon) {
	int ret = 0;
	switch  (tcon->ctype)  {
		case CT_Int  : ret = static_cast<IntConstant *>(tcon)->lng  ;break;
		case CT_UInt : ret = static_cast<UIntConstant *>(tcon)->ulng;break;
		default : break;
	}
	return ret;
}

// cases are :
//
//  1 : constant , sizeof
//  2 : sizeof , constant
//  3 : constant, constant
//  4 : constant
//  5 : longer (will handle it later)
//

int RvTraversal::get_the_malloc_size(ExprVector    args)
{
	ExprVector::iterator  j;
	ExprVector    new_args;
	int ret = RV_DEFAULT_ARRAY_SIZE;

	for (j=args.begin(); j != args.end(); j++)
	{
		if ((*j)->etype ==  ET_BinaryExpr) {
			BinaryExpr *binexp = (BinaryExpr *) (*j);
			int op1 = 0, op2 = 0;

			if (binexp->leftExpr()->etype == ET_Constant && binexp->rightExpr()->etype == ET_SizeofExpr) {
			   op1 = get_size_of_val(static_cast<SizeofExpr *>(binexp->rightExpr()));
			   op2 = get_const_val(static_cast<Constant *>(binexp->leftExpr()));
			}
			if (binexp->leftExpr()->etype == ET_SizeofExpr   && binexp->rightExpr()->etype == ET_Constant ) {
				op1 = get_size_of_val(static_cast<SizeofExpr *>(binexp->leftExpr()));
				op2 = get_const_val(static_cast<Constant *>(binexp->rightExpr()));
			}
			if (binexp->leftExpr()->etype == ET_Constant && binexp->rightExpr()->etype == ET_Constant) {
				op1 = get_const_val(static_cast<Constant *>(binexp->leftExpr()));
				op2 = get_const_val(static_cast<Constant *>(binexp->rightExpr()));
			}

			// If the expression is long the assumption, is that the constant is at the end or the sizeof is at 
			// the end, although this may change
			//

			if (binexp->leftExpr()->etype == ET_BinaryExpr && binexp->rightExpr()->etype == ET_Constant) {
				new_args.push_back(binexp->leftExpr());
				op1 = get_the_malloc_size(new_args);
				op2 = get_const_val(static_cast<Constant *>(binexp->rightExpr()));
			}
			if (binexp->leftExpr()->etype == ET_BinaryExpr && binexp->rightExpr()->etype == ET_SizeofExpr) {
				new_args.push_back(binexp->rightExpr());
				op1 = get_the_malloc_size(new_args);
				op2 = get_size_of_val(static_cast<SizeofExpr *>(binexp->rightExpr()));
			}

			if (binexp->bOp == BO_Plus)   ret = op1 + op2;
			if (binexp->bOp == BO_Mult)   ret = op1 * op2;

		} else if ((*j)->etype ==  ET_Constant && args.size() == 1) {
			 ret = get_const_val(static_cast<Constant *>(*j));
		}
	}
	return ret;
}



void RvTraversal::traverse_assign(AssignExpr *node)
{
  bool is_malloc;   // global indication that right hand side is array
  bool is_an_array; // global indication that right hand side is array
  arrType  arr_ty = PTR_arr;
  int sz;
  Symbol *arr_origin = (Symbol *) NULL;

  is_malloc   = false;
  is_an_array = false;

  if (DBG_TRV) {
		out << "\ntraverse_assign:\n";
		node->print(out);
		out << "\n";
  }

  if (!is_ptr_arithmetic(node)) {
	  Symbol *sym = get_assigned_ptr_sym(node);
	  if (sym) {
		  Symbol *tmp_origin;
		  int sz, ind;

		  if ((ind = find_sym(sym,&sz, &tmp_origin,this_side)) != -1) {
			  array_item *tmp = get_arr_item(this_side,ind);
			  tmp->alg_type = finite_CBMC_MAC_SHADOW;
		  }
	  }
  }

  //out << "assign " << is_ptr_arithmetic(node->lValue()) << "\n";

  // first case call malloc
  //
  if (node->rValue()->etype==ET_FunctionCall) {
	 FunctionCall *func_ptr = (FunctionCall *) node->rValue();

	 if (func_ptr->function->etype == ET_Variable) {
		 Variable *var_ptr = (Variable *) func_ptr->function;

		 //out << " name of right side " << var_ptr->name->name << "\n";
		 if (is_alloc(var_ptr->name->name)) {
			 /* start change */
			 ExprVector    args = func_ptr->args;
			 current_fixed_array_size = get_the_malloc_size(args);
			 /* end change */
			 //out << "calling malloc()\n";
			 is_malloc = true;
			 is_an_array = true;
			 arr_ty    = MALLOC_arr;
		 }
		 // YL - need to get the size of the malloced area if possible here
	 }
  } else {
	  // second case right hand side is direct array variable
	  if (node->rValue()->etype==ET_Variable ) {
		  Variable *var_ptr = (Variable *) node->rValue();

		  if (find_sym(var_ptr->name, &sz, &arr_origin,this_side) != -1) {
			  // using is_malloc for the same purpose here
			  //out << "found " << var_ptr->name->name << " \n";
			  is_malloc = true;
			  //if (arr_origin) out << "inside variable " << arr_origin->name << "\n";
		  }
	  } else {
		  // Eat up casts, until we get to the variable, assumption is
		  // that cilly cleaned it up for me
		  if (node->rValue()->etype==ET_CastExpr ) {
			  Expression *exp =  node->rValue();

			  //out << "\n";
			  while (exp->etype==ET_CastExpr) {
				  CastExpr *tmp = (CastExpr *) exp;
				  exp = tmp->expr;
			  }

			  if (exp->etype == ET_Variable) {
				  Variable *var_ptr = (Variable *) exp;
				  if (find_sym(var_ptr->name,&sz, &arr_origin,this_side) != -1) {
					  // using is_malloc for the same purpose here
					  //out << "found " << var_ptr->name->name << " \n";
					  is_malloc = true;
				  }
			  } else { // function call behind cast
				  if (exp->etype==ET_FunctionCall) {
					  FunctionCall *func_ptr = (FunctionCall *) exp;

					  if (func_ptr->function->etype == ET_Variable) {
						   Variable *var_ptr = (Variable *) func_ptr->function;
						   if (is_alloc(var_ptr->name->name)) {
							   ExprVector    args = func_ptr->args;
							   current_fixed_array_size = get_the_malloc_size(args);
							   //out << "calling malloc()\n";
							   is_malloc = true;
							   is_an_array = true;
							   arr_ty    = MALLOC_arr;
						   }
						   // YL - need to get the size of the malloced area if possible here
					  }
				  }     // function call behind cast
				  else {
					  is_malloc = is_array_exp(exp,&arr_origin);
				  }
			  }
		  }  else {
			  // in the general case is there a non deref array on right side
			  
			  is_malloc = is_array_exp(node->rValue(),&arr_origin);
		  }
	  }
  } // else of malloc function call

  if (node->lValue()->etype==ET_Variable && is_malloc) {
	  Variable *var_ptr = (Variable *) node->lValue();
	  Symbol *tmp_origin;

	  if (find_sym(var_ptr->name,&sz, &tmp_origin,this_side) == -1) {
		  //out << " name of left side " << var_ptr->name->name << "\n";
		  array_item *tmp_arr;

		  // assumption is that there is pointer arithmetic
		  tmp_arr = new array_item(Fixed_Size_NMAC,arr_ty,var_ptr->name);
		  if (current_fixed_array_size != -1) {
			 tmp_arr->set_size(current_fixed_array_size);
		  } 

		  if (is_an_array) {
		  }
		  else {
			  tmp_arr->orig_sym = get_orig_orig(arr_origin);
		  }
		  side_push_back(this_side, tmp_arr) ;
	  }
  }

  node->lValue()->accept(this);
  node->rValue()->accept(this);
}

void RvTraversal::side_push_back(const RVSide& side, array_item *item) {
  side.select(array_vec0, array_vec1).push_back(item) ;
}

void RvTraversal::traverse_rel(RelExpr *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_rel:\n";
		node->print(out);
		out << "\n";
  }
  node->leftExpr()->accept(this);
  node->rightExpr()->accept(this);
}

void RvTraversal::traverse_cast(CastExpr *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_cast:\n";
  }
  node->expr->accept(this);
}

void RvTraversal::traverse_sizeof(SizeofExpr *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_sizeof:\n";
		
  }
  if (node->expr) node->expr->accept(this);
}

void RvTraversal::traverse_index(IndexExpr *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_index:\n";
  }
  node->array->accept(this);
  node->_subscript->accept(this);
}

void RvTraversal::traverse_label(Label *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_label:\n";
  }
  switch (node->type)
  {
	case LT_None:
	  assert(0);
	  break;

	case LT_Default:
	  break;

	case LT_Case:
	  assert(node->begin);
	  node->begin->accept(this);
	  break;

	case LT_CaseRange:
	  assert(node->begin);
	  assert(node->end);
	  node->begin->accept(this);
	  node->end->accept(this);
	  break;

	case LT_Goto:
	  assert(node->name);
	  traverse_symbol(node->name);
	  break;
  }
}

void RvTraversal::traverse_decl(Decl *node)
{

  if (DBG_TRV) {
		out << "\ntraverse_decl:\n";
		node->print(out,true,0);
		out <<"\n";
  }

  if (node->form) {
	  node->form->accept(this);
  }

  if (node->name) {
	  traverse_symbol(node->name);
  }

  if (node->initializer) {
	  node->initializer->accept(this);
  }
  //Decl            *next;    // For linking into lists

}

void RvTraversal::traverse_statement(Statement *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_statement:\n";
		out << "\nstatement type: " << node->type << "\n";
  }

}

void RvTraversal::traverse_file_line(FileLineStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_file_line:\n";
  }
}

void RvTraversal::traverse_include(InclStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_include:\n";
  }
}

void RvTraversal::traverse_end_include(EndInclStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_end_include:\n";
  }
}

void RvTraversal::traverse_expression(ExpressionStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_expression:\n";
		node->expression->print(out);
		out << "\n";
		
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);

  assert(node->expression);
  node->expression->accept(this);
}

void RvTraversal::traverse_if(IfStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_if:\n";
		node->print(out,0);
		out << "\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);
  node->cond->accept(this);
  block(node->thenBlk);
  if (node->elseBlk)
  {
	block(node->elseBlk);
  }
}

void RvTraversal::traverse_switch(SwitchStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_switch:\n";
		node->print(out,0);
		out << "\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);

  node->cond->accept(this);
  block(node->block);
}

void RvTraversal::traverse_for(ForStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_for:\n";
		node->print(out,0);
		out << "\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);

  if (node->init) node->init->accept(this);
  if (node->cond) node->cond->accept(this);
  if (node->incr) node->incr->accept(this);
  block(node->block);
}

void RvTraversal::traverse_while(WhileStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_while:\n";
		node->print(out,0);
		out << "\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);

  node->cond->accept(this);
  block(node->block);
}

void RvTraversal::traverse_do_while(DoWhileStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_do_while:\n";
		node->print(out,0);
		out << "\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);
  
  block(node->block);
  node->cond->accept(this);
}

void RvTraversal::traverse_goto(GotoStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_goto:\n";
		node->print(out,0);
		out <<"\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);

	traverse_symbol(node->dest);
}

void RvTraversal::traverse_return(ReturnStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_return:\n";
		node->print(out,0);
		out <<"\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);
  
  if (node->result)
  {
	node->result->accept(this);
  }
}

void RvTraversal::traverse_declaration(DeclStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_declaration:\n";
		node->print(out,0);
		out <<"\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);
  
  if (!node->decls.empty())
  {
	DeclVector::const_iterator i = node->decls.begin();
	
	traverse_decl(*i);
	for (++i; i != node->decls.end(); ++i)
	{
	  traverse_decl(*i);
	}
  }
}

void RvTraversal::traverse_typedef(TypedefStemnt *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_typedef:\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);
  
  if (!node->decls.empty())
  {
	DeclVector::const_iterator i = node->decls.begin();
	traverse_decl(*i);
	for (++i; i != node->decls.end(); ++i)
	{
	  traverse_decl(*i);
	}
  }
}

void RvTraversal::traverse_block(Block *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_block:\n";
  }
  for (LabelVector::const_iterator i = node->labels.begin();
	   i != node->labels.end();
	   ++i)
	traverse_label(*i);

  bool isDecl = (node->head != 0) ? node->head->isDeclaration() : false;
  for (Statement *statement = node->head; statement; statement = statement->next)
  {
	if (isDecl && !statement->isDeclaration())
	{
	  isDecl = false;
	}
	statement->accept(this);
  }
}

void RvTraversal::traverse_function_definition(FunctionDef *node)
{
  if (DBG_TRV) {
		out << "\ntraverse_function_definition:\n";
		node->print(out,0);
		out << "\n";
  }
  current_function = (node->decl->name->name);
  traverse_decl(node->decl);
  traverse_block(node);
}


void RvTraversal::traverse_unit(TransUnit *unit)
{
  int inInclude = 0;
  if (DBG_TRV) {
		out << "\ntraverse_unit:\n";
  }
  for (Statement *statement = unit->head; statement; statement = statement->next)
  {
	if (inInclude > 0)
	{
	  if (statement->isEndInclude()) inInclude--;
	  else if (statement->isInclude()) inInclude++;
	}
	else
	{
	  if (statement->isInclude()) inInclude++;
	  statement->accept(this);
	}
  }
}

void RvTraversal::block(Statement *node)
{
  if (DBG_TRV) {
		out << "block:\n";
  }
  if (node->isBlock()) node->accept(this);
  else
  {
	node->accept(this);
  }
}

// Assumption is that I get the parameters initialized
// another assumption is that I get the master assigning expression
// from the right hand side

void RvTraversal::get_ref_ptr(Expression *exp, int *num_deref, int *ptr_nesting)
{

	  switch (exp->etype) {
		  case ET_UnaryExpr   : {
									if ((static_cast<UnaryExpr*>(exp))->op() == UO_Deref) {
										(*num_deref)++;
									}
									get_ref_ptr((static_cast<UnaryExpr*>(exp))->operand(),num_deref,ptr_nesting);
									break;
								}
		  case ET_Variable    : { 
									SymEntry *entry = (static_cast<Variable*>(exp))->
													  name->entry;
									Type *tmp_tp = (static_cast<Decl*>(entry->uVarDecl))->form;

									while ((tmp_tp != 0) && (tmp_tp->type == TT_Pointer)) {
										(*ptr_nesting)++;
										tmp_tp = ((PtrType*)tmp_tp)->subType;
									}
									break;
								}
		  default: break;
	  }
}


bool RvTraversal::is_ptr_arithmetic(Expression *exp)
{
  bool ret = true;
  int num_deref = 0, ptr_nesting = 0;
  get_ref_ptr(exp, &num_deref, &ptr_nesting);

  //out << "num_deref " << num_deref << " ptr_nesting " << ptr_nesting << "\n";

  if (num_deref < ptr_nesting) ret = true;
  else ret = false;

  return ret;
}


Symbol* RvTraversal::ptr_var2symbol(Expression* expr)
{
  if( expr->etype != ET_Variable ) return NULL;
  Variable *var = (Variable*)expr;
  if( !var->name || !var->name->entry ) return NULL;

  SymEntry* se = var->name->entry;
  if( !se->IsVarDecl() && !se->IsFctDecl() && !se->IsVarFctDecl() && !se->IsParamDecl() )
	return NULL;
  
  return var->name;
}


Symbol* RvTraversal::get_assigned_ptr_sym(Expression* s0p)
{
  switch( s0p->etype ) 
  {
	case ET_Variable:
	  return ptr_var2symbol( s0p );
	  
	case ET_UnaryExpr:  {
	  UnaryExpr *tmp = (UnaryExpr *) s0p;

	  if( tmp->uOp == UO_Deref ) { 
		  Symbol* sym = ptr_var2symbol( tmp->operand() );
		  if(sym) return sym;
	  }
	  return NULL;
	  break;
	}  
	case ET_BinaryExpr: { 
	  BinaryExpr *tmp = (BinaryExpr *) s0p;
	  switch( tmp->bOp )
	  {
		case BO_PtrMember:   // x->y
		case BO_Member:      // x.y
			return get_assigned_ptr_sym( tmp->leftExpr()); 
		case BO_Comma:       // x,y
			return get_assigned_ptr_sym( tmp->rightExpr());
	  
		default:
		 /* any other BinaryExpr can't be left side of assignment. */
		 return NULL; 			  
	  }
	  return NULL;
	}
	case ET_CastExpr: {      // (type) x
	  CastExpr * tmp = (CastExpr *) s0p;
	  /* just ignore the cast in assignments (?) */
	  return get_assigned_ptr_sym( tmp->expr);
	}

	default:
	  return NULL;
  }
  return NULL;
}



void RvTraversal::prt_scopelevel(int level)
{
	switch (level) {
	   case CURRENT_SCOPE  : out << "CURRENT_SCOPE\n"; break;    // the default
	   case EXTERN_SCOPE   : out << "EXTERN_SCOPE\n"; break;
	   case FILE_SCOPE     : out << "FILE_SCOPE\n"; break;
	   case FUNCTION_SCOPE : out << "FUNCTION_SCOPE\n"; break;
	   case BLOCK_SCOPE    : out << "BLOCK_SCOPE\n"; break;    // really, 4 or more.
	   default             : out << "in default " << level << "\n";break;
	}
}

bool RvTraversal::try_calc_constant_array_size_expression( Expression * exp, int* result )
{
	if (!exp){
		return false;
	}

	ExpressionType type = exp->etype;
	if (type == ET_Constant){
		*result = extract_integer_from_constant( (Constant*) exp);
		return true;
	} 
	if (type == ET_BinaryExpr){
		BinaryExpr* binaryExpr = (BinaryExpr*) exp;
		Expression* left = binaryExpr->_leftExpr;
		Expression* right = binaryExpr->_rightExpr;

		int leftNum, rightNum;
		if (!try_calc_constant_array_size_expression(left, &leftNum) || 
			!try_calc_constant_array_size_expression(right, &rightNum)){
				return false;
		}

		*result = calc_expression(leftNum, rightNum, binaryExpr->bOp);

		return true;
	}

	return false;
}

bool RvTraversal::expression_is_legal_for_constant_value_calculation( Expression * exp )
{
	return exp->etype == ET_BinaryExpr || exp->etype == ET_Constant;
}

int RvTraversal::extract_integer_from_constant( Constant* constExpr )
{
	if (constExpr->ctype ==  CT_Int){
		return ((IntConstant*) constExpr)->lng;
	}
	if (constExpr->ctype ==  CT_UInt){
		return ((UIntConstant*) constExpr)->ulng;
	}
}

int RvTraversal::calc_expression( int leftNum, int rightNum, BinaryOp bOp )
{
	switch(bOp){
		case BO_Plus:
			  return leftNum + rightNum;
		case BO_Minus:
			  return leftNum - rightNum;
		case BO_Mult:
			  return leftNum * rightNum;
	}

	return -1;
}
