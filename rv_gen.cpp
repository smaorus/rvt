#include <limits.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_error.h>
#include <rv_treecomp.h>
#include <rv_temps.h>

#include <rv_funcpair.h>
#include <rv_arrays.h>
#include <rv_genctx.h>
#include <rv_funcflags.h>
#include <rv_traversal.h>
#include <rv_main.h>
#include <rv_structs.h>
#include "rv_propagate.h"
#include "rv_dataflow.h"
#include "rv_glob.h"

#include "rv_summarizer.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>

#ifndef _MSC_VER
	#define _CrtDumpMemoryLeaks()
#endif

#define RV_SECTION RV_SEC_GEN

// as long as CBMC does not check the case that malloc returns 0, this should be commented
//#define MALLOC_EQ0 

// Comment out to use the old UF code (without the CBMC macros)
#define CBMC_UF

#define G_ARR_SAVE "RV_ARR_SAVE"
#define G_ARR_OUT "RV_ARR_OUT"
#define ARR_EQ_PREFIX "RV_ARR_EQ"
#define ARR_P "RV_ARR_P"
#define RV_NONDET_ARR " rv_nd_"

#define ACT_BY by.append("(").append(Utils::itoa(__LINE__)).append(")")


using namespace std;


static const string rv_uf_ind("rv_uf_ind");


/* RVGen code: */
/*=============*/

RVGen::RVGen(RVTemp& _temps) :
	temps(_temps), current_side(0)
{ 
	m_where = "UNKNOWN";
	first_compare = true;
	local_count = 0;
	ubs_depth = -1; 
	look_back = 0;
	m_pSemChecker = NULL;

}

RVGen::~RVGen()
{ 
	read_only_globals[0].delete_all();
	read_only_globals[1].delete_all();  
}

std::string RVGen::convert_type(std::string type_text, const RVSide& side)
{
	/* by default do nothing: */
	return type_text;
}

std::string RVGen::item_prefix()
{
	return ""; /* by default - no prefix */
}

void RVGen::set_read_only_globals(SymbolVector vec[2])
{
	read_only_globals[0].add_dup(vec[0]);
	read_only_globals[1].add_dup(vec[1]);
}

bool RVGen::ignore_in_global(Symbol* sym, int side)
{
	if(!sym) return false;
	return read_only_globals[side].find(sym->name) != NULL; // ofer: changed to supress warning
}

bool RVGen::unnamed_arg(Decl* decl0, Decl* decl1, int arg_index, bool warn /*=false*/)
	// returns true if at least on one side it is unnamed
{
	bool un0 = !decl0 || !decl0->name;
	bool un1 = !decl1 || !decl1->name;

	if( warn && ((un0 && !un1) || (un1 && !un0)) )
		rv_errstrm << "Warning: in \""<< m_where <<"\" argument #"<< arg_index <<
		" is not named on side "<< (un0 ? 0 :1) <<" but named on the other side.\n";

	return (un0 || un1);
}

void RVGen::gen_decl(Type* print_type, const char* symPrefix, Symbol* orig_sym, std::string& by ) {
	gen_decl_low(print_type, symPrefix, orig_sym, NULL, ACT_BY);
}

void RVGen::gen_decl_w_side(Type* print_type, const char* symPrefix, Symbol* orig_sym, std::string& by) {
	gen_decl_low(print_type, symPrefix, orig_sym, &current_side, ACT_BY);
}

static Symbol* find_root_of_array(const RVSide& side, int index, Symbol* const in_orig_sym) {
	array_item *the_arr = RVGlob::getArrHooks().get_arr_item(side, index);
	if (the_arr == NULL || the_arr->arr_type == REG_arr)
		return in_orig_sym;
	Symbol *orig_sym = the_arr->orig_sym;
	int the_ind = RVGlob::getArrHooks().find_sym(orig_sym, side);
	return the_ind != -1? find_root_of_array(side, the_ind, orig_sym) : orig_sym;
}

void RVGen::gen_decl_low(Type* print_type, const char* prefix, Symbol* orig_sym, const RVSide* pSide, std::string& by) {
	by.append("/ "); by.append(__FUNCTION__);
	Symbol sym; // for full item name.
	int arr_sz;
	Symbol *org_arr_sym;
	int the_ind;
	
	sym.entry = orig_sym->entry;
	sym.name = prefix + orig_sym->name;  

    Type *tmp = NULL;
    the_ind = RVGlob::getArrHooks().find_sym(orig_sym , &arr_sz, &org_arr_sym,current_side);
    bool isArr = the_ind != -1;
	if (isArr) {	// array
		org_arr_sym = find_root_of_array(current_side, the_ind, org_arr_sym); // current_side is only updated when this function is called for declaring function arguments. Not clear if this code is reached when called for declaring old UF array.
		if (!arr_sz) { arr_sz = 4; rv_errstrm << "Warning: cannot compute array size of " + orig_sym->name +  ". Using default.\n" ; }// default value when it cannot detect the real size in dynamic arrays.
		tmp = ptr_2_array_types(org_arr_sym, (PtrType *) print_type, arr_sz); // converting int *a; to int a[#];
	} else 
        tmp = print_type->dup();
	
	if (pSide != NULL)
		add_prefix_to_type(pSide->get_side_prefix(), tmp);	
	if (isArr && is_pointer2pointer(print_type))
		gen_ptr2array_decl(tmp, print_type, &sym, ACT_BY);
	else
		temps.gen_var_decl_text(RVGenCtx::get_print_type_basic(tmp, &sym), ACT_BY); // we use this function because we want declarations to go into a separate stream (to be printed in the beginning of the function)
	// delete tmp is a bug here as all the types are registered in Project. Later it'll delete them all.
}

ArrayType *RVGen::ptr_2_array_types(Symbol *sym, PtrType *in_pt_type, int sz) const
{
    static const char *where_ = "RVCtool::ptr_2_array_types";
	ArrayType *res;
	Location l(__LINE__,0,__FILE__);
	IntConstant *exp;
	Type *ptr_base = NULL, *pt_type = in_pt_type;

	exp =  new IntConstant( sz,false,l);
	if (sym != NULL) {
		pt_type = get_symbol_type(sym, where_);
        if (pt_type->isArray()) {
        	res = static_cast<ArrayType*>(pt_type->dup0());
			if (!res->size){
				res->size = exp;
			}

		    add_prefix_to_type(current_side.get_side_prefix(), res);
        	return res;
        }
    }
	
    is_pointer(pt_type, where_, &ptr_base);
    ptr_base = ptr_base->dup();
	res = new ArrayType(exp);
	res->subType = ptr_base;
	return res;
}

void RVGen::gen_ptr2array_decl(Type *arrType, Type *ptrType, Symbol *arr, std::string& by) {
    by.append("/ "); by.append(__FUNCTION__);	
	Type *subType = NULL;
	if (! is_pointer(ptrType, "RVGen::gen_ptr2array_decl", &subType) )
		return;
	temps.gen_var_decl_text(RVGenCtx::get_print_type_basic(ptrType, arr), ACT_BY);
	Symbol arg, ptr;
	arg.entry = arr->entry;
	arg.name = arr->name + "_locArr";
	temps.gen_var_decl_text(RVGenCtx::get_print_type_basic(arrType, &arg), ACT_BY);
	ptr.entry = arg.entry;
	ptr.name = arg.name + "Ptr";
	temps.gen_var_decl_text(RVGenCtx::get_print_type_basic(subType, &ptr), ACT_BY);
	temps.print("  /* initialization of double pointer to array: */\n  ");
	temps.print(ptr.name + " = " + arg.name + ";\n  ");
	temps.print(arr->name + " = &" + ptr.name + ";\n");
}

/// <summary>
/// given an operation op (an element of ItemOp, such as 'SAVE', 'NONDET', etc), and a context (which typically holds two 'lanes', which are the left- (the 'item') and right- (the 'var') variables 
/// to be used in the operation, this function generates the code that performs this operation. For example if the item is 'x', the var is 'y' and the operation is SAVE, 
/// it will generate the code x = y; through a call to 'gen_save_val'. See a more detailed explanation in rv_genctx.h before the declaration of class rv_genctx.
///</summary>
bool RVGen::gen_single_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth /*=-1*/)
	// generates a single (non-recursive) operation:
{
	int var_lane = ctx.var_lane();
	std::string type_text("BAD TYPE");
	bool pointer = ctx.var_is_pointer();	
	RVArrayRef* ua_ref = ctx.get_ua_ref(var_lane);
	std::string item   = ctx.get_full_name( item_lane() );
	std::string var    = ctx.get_full_name( var_lane );

		
	bool is_array = false;
	int arr_sz;
	array_item *the_arr;
	
	is_array = ctx.is_new_array(var_lane);
	arr_sz   = (is_array) ? ctx.new_array_size(var_lane) : 0;
	the_arr  = ctx.get_arr_item(var_lane);

	std::string my_str = (is_array) ? " true" : " false";
	
	if (op == ADD || op == NONDET || op == NONDET_SAVE || op == COMPARE || op == COPY_S1_to_S0)
		ctx.throw_on_void_pointer();

	switch( op )
	{
	case ADD: // used in gen_side(0/1)_cbmc_uf
		tmp_var.name = item;
		tmp_var.type = convert_type(ctx.get_print_type(0), ctx.get_side(0));
		tmp_var.is_pointer = ctx.is_pointer(0);;
		tmp_var.is_aggregate = this->is_aggregate;
		tmp_var.is_array = ctx.is_new_array(0);
		tmp_var.array_size = (tmp_var.is_array) ? ctx.new_array_size(0) : 0;
		m_vars.push_back(tmp_var);
		break;

	case NONDET:
		if( is_basetype(ctx.get_real_type(0), BT_Void) )
			break;
		if(ua_ref) {
			std::string uaname = rv_arrays().type2name(ua_ref->getArrayItemType());
			temps.gen_nondet_ua_value(uaname, var, pointer, ctx.get_side(var_lane), false);
		}
		else {
			type_text = convert_type(ctx.get_print_type(0), ctx.get_side(0));
			bool is_long = ctx.is_long();
			if (is_array) {
				temps.gen_nondet_value_arr(var, type_text, arr_sz, is_long,the_arr, ACT_BY);
			} else {
				temps.gen_nondet_value(var, type_text, pointer, is_long, ACT_BY);
			}
		}
		break;

	case NONDET_SAVE:				
		type_text = convert_type(ctx.get_print_type(1), ctx.get_side(1));
		if(ua_ref) {
			std::string uaname = rv_arrays().type2name(ua_ref->getArrayItemType());
			temps.gen_nondet_ua_value(uaname, var, pointer, ctx.get_side(var_lane), true);
			temps.gen_copy_val(item, var, ACT_BY, pointer);
		} else {
			bool is_long = ctx.is_long();
			if (is_array) {
				temps.gen_nondet_save_val_arr(item, var, type_text, arr_sz, is_long,the_arr, ACT_BY);
			} else {
				if (m_unitrv){
					temps.gen_nondet_unitrv_save_val(item, var, type_text, pointer, is_long, ACT_BY);
				}
				else{
					temps.gen_nondet_save_val(item, var, type_text, pointer, is_long, ACT_BY);
				}
			}
		}
		break;

	case COMPARE:				
		if (is_array) {
			temps.gen_compare_val_arr(item, var, arr_sz, first_compare,the_arr, ACT_BY);
		} else temps.gen_compare_val(item, var, pointer, first_compare, ACT_BY);
		first_compare = false;
		break;

	case COPY_S0_to_S1:				
		if (is_array) {
			temps.gen_save_val_arr(var, item, arr_sz,the_arr, ACT_BY);
		}
		else if( is_basetype(ctx.get_real_type(0), BT_Void) )
			temps.gen_memcpy(var, item, RV_VOID_PTR_SIZE, ACT_BY);
		else{
			temps.gen_copy_val(var, item, ACT_BY, pointer);
		}
		break;

	case COPY_S1_to_S0:
		if (is_array)
			temps.gen_save_val_arr(item,var,arr_sz,the_arr, ACT_BY);
		else if( is_basetype(ctx.get_real_type(1), BT_Void) )
			temps.gen_memcpy(item, var, RV_VOID_PTR_SIZE, ACT_BY);
		else
			temps.gen_copy_val(item, var, ACT_BY, pointer);
		break;

	case ASSERT_EQ:				
		if(ua_ref) {
			std::string uaname = rv_arrays().type2name(ua_ref->getArrayItemType());
			temps.gen_ua_assert_eq(uaname, var, pointer);
		}
		else {
			if (is_array) {
				temps.gen_assert_eq_arr(item, var, arr_sz,the_arr, ACT_BY);
				m_pSemChecker->set_K(arr_sz + 1);
			}
			else if( is_basetype(ctx.get_real_type(0), BT_Void) )
				temps.gen_memcmp(var, item, RV_VOID_PTR_SIZE, ACT_BY);
			else
				temps.gen_assert_eq(item, var, ACT_BY, pointer);
		}
		break;

	case ASSIGN_NULL:		
		if( pointer && !is_array ) {			
			temps.gen_eq_null(item, ACT_BY);
			if( ctx.get_width() > 1 ) {				
				temps.gen_eq_null(var, ACT_BY);
			}
		}
		break;

	
	case ALLOC:		
		if( pointer && !is_array ) {   // allocates only pointer items.	
			type_text = convert_type(ctx.get_print_type(item_lane()), ctx.get_side(item_lane()));
			temps.gen_alloc(item, type_text, ACT_BY);

			/* alloc the other lane if exists: */
			assert(ctx.get_width() == 1);
			/*if( ctx.get_width() > 1 ) {
				type_text = convert_type(ctx.get_print_type(var_lane), ctx.get_side(var_lane));
				temps.gen_alloc(var, type_text, ACT_BY);
			}*/
		}

		if(ua_ref) {
			assert(0);
			std::string uaname = rv_arrays().type2name(ua_ref->getArrayItemType());						
			temps.gen_ua_new_array_call(uaname, item, pointer, false);

			/* copy to other lane if exists: */
			if( ctx.get_width() > 1 ) {				
				temps.gen_copy_val(var, item, ACT_BY, pointer);
			}
		}
		break;

	default:
		rv_errstrm << "RVGen::gen_single_op(): bad ItemOp: "<< op <<" in: \""
			<< m_where << "\" \n";
		return false;
	}

	return true;
}

/// <summary>
/// Part of deconstructing the type before performing 'op' with gen_single_op() - see detailed explanation in gen_simple_op().
/// Here it handles the case of two pointers (e.g. **x = ...) by stripping one pointer, and (apparently) the (void *) case.
/// </summary>
bool RVGen::gen_simple_component_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth /*=-1*/)
{
	bool always_single = (op == ASSIGN_NULL);
	bool pointer2pointer = ctx.is_pointer2pointer();

	// In case of a pointer-to-pointer component and a non-pointer action - 
	// go deeper and perform it through gen_item_or_struct_op().
	// Note: pointer actions are always done for the current item.
	if( pointer2pointer && !always_single ) {
		auto_ptr<RVGenCtx> son_ctx(ctx.create_derefed_ctx());
		return gen_item_or_struct_op(op, *son_ctx, ACT_BY, depth-1);
	}

	/* can't do nothing (except EQ_NULL) with void type: */
	//if(is_basetype(ctx.get_real_type(0), BT_Void) && op != ASSIGN_NULL)
	//	return true;

	// otherwise - just gen a single op:
	return gen_single_op(op, ctx, ACT_BY, depth);
}

/// <summary>
/// Part of deconstructing the type before performing 'op' with gen_single_op - see detailed explanation in gen_simple_op.
/// Here it handles structures/ unions by breaking them to fields. 
/// </summary>
bool RVGen::gen_struct_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth /*=-1*/)
{
	StructDef* str = NULL;
	unsigned son_depth, size, max_size = 0;
	Decl* comp = NULL;
	bool ret = true;
	auto_ptr<RVGenCtx> max_ctx;
	bool is_union = ctx.is_union();

	str = get_struct_def(ctx.get_real_type(0), m_where);

	for(int i = 0; i < str->nComponents; i++) {  
		comp = str->components[i];

		for(int j = 0; comp; comp = comp->next, j++) {
			if( !comp->name )
				continue;

			auto_ptr<RVGenCtx> pSonCtx(ctx.dup_for_struct_item(i, j));
			if( !is_union ) {
				son_depth = pSonCtx->var_is_pointer() ? depth-1: depth;
				ret = gen_item_or_struct_op(op, *pSonCtx, ACT_BY, son_depth) && ret;
			} 
			else {
				/* for union find the biggest item and set only its value: */
				size = pSonCtx->get_size();
				if( size > max_size ) {
					max_ctx = pSonCtx;
					max_size = size;
				}
			}
		}
	}

	/* for unions process only max_comp: */
	if( is_union && max_size > 0 ) {
		son_depth = (max_ctx->var_is_pointer() ? depth-1: depth);
		ret = gen_simple_component_op(op, *max_ctx, ACT_BY, son_depth) && ret;
		/*      <<=== what about struct components (size is 0)? */
	}

	return ret;
}

bool RVGen::protect_pointer(ItemOp op, int depth, RVGenCtx& ctx, bool& out_continue, std::string& by)
{
	int  var_lane = ctx.var_lane();
	bool pointer = ctx.var_is_pointer();
	Type* tp0 = ctx.get_real_type(0);

	if(!pointer || ctx.is_array(var_lane) || ctx.is_new_array(var_lane)) // || op == ASSERT_EQ || op == ASSUME_EQ)
	{ // alloc only non-array pointers		
		out_continue = true;
		return true;
	}
	
	/* do nothing with void type vars/items: */
	if( false /* DIMAXXX */ && is_basetype(tp0, BT_Void) ) {
		
		out_continue = false;
		return true;
	}

	by.append("/ "); by.append(__FUNCTION__);
	
	out_continue = true;


	return localize_and_alloc_pointer(op, depth, ctx, by);

}


bool RVGen::localize_and_alloc_pointer(ItemOp op, int depth, RVGenCtx& ctx, string& by) {
	if(!ctx.is_localized(item_lane())) {	// check if ok.
		ctx.localize_lanes();
		by.append(" [op=").append(Utils::itoa(op)).append("]");

		bool pointer = ctx.var_is_pointer(); // side 0 is a pointer iff side 1 is
		for (unsigned int i = 0; i < ctx.get_width(); ++i) {
			std::string old_name, local_name, type_text;

			old_name = ctx.get_old_full_name(i);
			local_name = ctx.get_full_name(i);
			type_text = convert_type(ctx.get_print_type(i), ctx.get_side(i));
			assert(op != NONDET_SAVE || dont_alloc_root);
			if (op == NONDET || (op == NONDET_SAVE && !isProcessingRoot(depth))) // !! unrelated to localization. Should be taken out ?
				temps.gen_alloc(old_name, type_text, ACT_BY);
			if(old_name != local_name)
				temps.gen_local_copy_uf(type_text, local_name, old_name, ACT_BY, pointer); // note that now even for nondet and nondet_save it uses the streams defined in gen_local_copy_uf.
		}
	}

	assert(op != NONDET_SAVE || isProcessingRoot(depth) == dont_alloc_root);
	dont_alloc_root = false;
	return true;	
}

bool RVGen::isProcessingRoot(int depth) const {
	return depth == ubs_depth;
}

/*
bool RVGen::localize_pointer(ItemOp op, RVGenCtx& ctx, std::string& by) {
	bool pointer = ctx.var_is_pointer();
	if( !ctx.is_localized(item_lane()) ) 
		ctx.localize_lanes(); 

	by.append(" [op=").append(Utils::itoa(op)).append("]");

	for (int i = 0; i < ctx.get_width(); ++i) {
		std::string old_name, local_name, type_text;

		old_name= ctx.get_old_full_name(i);
		local_name = ctx.get_full_name(i);
		type_text = ctx.get_print_type(i); 
		if (op == ADD || op == ALLOC || op == COPY_S1_to_S0 || op == COPY_S0_to_S1 || op == SAVE || dont_alloc_root) { //Check if we need dont_alloc_root here
			if(old_name != local_name) {
				temps.gen_local_copy_uf(type_text, local_name, old_name, ACT_BY, pointer);
			}
		}
		else {
			bool alloc = false;
			switch(i) {
			case 0: alloc = !dont_alloc_root && (op == NONDET || op == NONDET_SAVE);//DIMAXXX || op == COPY_S0_to_S1);
			        //Basically it is possible that op == NONDET_SAVE && !dont_alloc_root
			        //in recursive calls of gen_item_or_struct_op().
			 	    //However, we don't know why we should skip allocating when op == NONDET_SAVE && dont_alloc_root
			        break;
			case 1: alloc = !dont_alloc_root && op == NONDET_SAVE; //DIMAXXX op === SAVE || op == COPY_S1_to_S0;
			        break;
			default: fatal_error("RVGen::localize_pointer(): ctx.get_width() > 2");
			}

			if (alloc) {
				temps.gen_alloc(old_name, type_text, ACT_BY);
				if(local_name!= old_name) {
					temps.gen_var_decl(type_text, local_name, ACT_BY, pointer);
					temps.gen_copy_val(local_name, old_name, ACT_BY); // copy pointer to local
				}
			}
		}
	}
	dont_alloc_root = false;
	return true;

	//bool alloc_var  = !dont_alloc_root && 
	//	(op == NONDET || op == NONDET_SAVE || op == COPY_S0_to_S1); // || op == COPY_S1_to_S0); // ofer: added COPY_S1_to_S0
	//bool alloc_item = (op == SAVE || op == NONDET_SAVE || op == COPY_S1_to_S0);

	//if (var_old_name!= var_local_name) {		
	//	// if needed - declare local copy for var
	//	if( alloc_var )
	//		// new struct - don't copy old
	//		temps.gen_var_decl(var_type_text, var_local_name, ACT_BY, pointer);
	//	else
	//		// declare local and copy old var to it:
	//		temps.gen_local_copy_uf(var_type_text, var_local_name, var_old_name, ACT_BY, pointer);
	//}

	//// if we need local version of the item:
	//if (item_local_name!= item_old_name) {
	//	if( alloc_item ) {
	//		// new struct - don't copy old			
	//		temps.gen_var_decl(item_type_text, item_local_name, ACT_BY, pointer);
	//	}
	//	else if(op != NONDET) {
	//		// all ops but NONDET may need the UF array item			
	//		temps.gen_local_copy_uf(item_type_text, item_local_name, item_old_name, ACT_BY, pointer);
	//	}
	//} 
	//	
	//if (alloc_var) {  		
	//		temps.gen_alloc(var_old_name, var_type_text, ACT_BY);
	//		if(var_old_name!= var_local_name) {			
	//			temps.gen_copy_val(var_local_name, var_old_name, ACT_BY); // copy pointer to local
	//		}
	//	}

	//if (alloc_item) {		
	//		temps.gen_alloc(item_old_name, item_type_text, ACT_BY);
	//	//temps.print("// allocation for" + item_type_text + " " + item_old_name+ "\n");
	//	if(item_local_name!= item_old_name) {						
	//		temps.gen_copy_val(item_local_name, item_old_name, ACT_BY); // copy pointer to local
	//	}
	//}


}
*/

	
/// <summary>
/// The entry function to a mechanism that performs 'op' (an element of ItemOp such as 'SAVE', 'ASSUME' etc) on the two variables ('lanes') saved in the context ctx. 
/// Eventually this process reaches gen_simple_op -- see detailed explanation there and in rv_genctx.h about contexts. 
/// Here it passes the work to either gen_struct_op (in case of struct/union), or to gen_simple_component_op, which typically later passes control to gen_simple_op
/// <param name="ctx"> cts holds the variables relevant to the operation. </param>
/// <param name="op"> The operation (from ItemOp) to perform</param>
/// <param name="depth"> used in unbounded structures. We start with depth = ubs_depth. In gen_simple_component_op we deref and call again with depth-1. </param>
/// </summary>
bool RVGen::gen_item_or_struct_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth /*=-1*/)
{
	bool ret = true;
	bool should_continue = true;
	Type *print_type = ctx.get_real_type(0);  /* without pointer */
    assert(!print_type->isArray() && !print_type->isFunction()); // gen_item_or_struct_op(): can't operate on function or array pointer types.
	
	bool is_aggregate = ctx.is_aggregate() && !ctx.is_ua(0); // treat UA refs (array reference) as a single item.
	bool pointer2pointer = ctx.is_pointer2pointer();

	if( depth < 0 ) depth = ubs_depth; // by default set ubs_depth
		
	/* need to allocate structs before pointer protection: */
	if( op == ALLOC) {
		if( depth == 0 ) ret = gen_single_op(ASSIGN_NULL, ctx, ACT_BY) && ret; // set pointers to NULL
		else ret = gen_single_op(op, ctx, ACT_BY) && ret;
		// if the item is of simple type:
		if( !(is_aggregate || pointer2pointer) ) return ret;  // nothing internal to allocate.
	}
	
	if( depth == 0 ) return true; 	// if we have reached maximal depth	
	
	ret = protect_pointer(op, depth, ctx, should_continue, ACT_BY) && ret; 
	if( !should_continue )	return ret;

	// This is the main work-horse:
	if( is_aggregate ) ret = gen_struct_op(op, ctx, ACT_BY, depth) && ret;	/* if it is a struct/union: */
	else ret = gen_simple_component_op(op, ctx, ACT_BY) && ret;

#ifdef MALLOC_EQ0
	ret = close_protect_pointer(op, ctx) && ret; 
#endif

	/* add shape assumptions after generation: */
	//if( op == ALLOC  || op == NONDET || op == NONDET_SAVE ) ret = add_UBS_shapers(op, ctx) && ret; // ofer: this mechanism is based on user defined assumptions in the directive file, which we currently do not use anyway.
	
	return ret;
}


///<summary>
/// utility to turn 'struct s' into e.g., 'struct rvs0_s'. Same for "union s" and enum s;
///</summary>
void RVGen::add_prefix_to_type(const char* prefix, Type* form) { // ofer
	BaseType *bt = NULL;
	for (Type *cur = form, *st = NULL; cur != NULL; cur = st, st = NULL) {  // for "struct s *a" or "struct s a[1]";
        if(cur->isPointer()) {
		    PtrType * pt = static_cast<PtrType *>(cur);
		    st = pt->subType;
		    if (st->isBaseType()) {
			    bt = (BaseType*) st;
                break;
            }
        }
        else if (cur->isArray()) {
		    ArrayType * pt = static_cast<ArrayType *>(cur);
		    st = pt->subType;
		    if (st->isBaseType()) {
			    bt = (BaseType*) st;
                break;
            }
        }
	}

	if (form->isBaseType())
		bt = static_cast<BaseType*>(form);  // for "struct s a";
	if (bt) {
		if (bt->tag)
			bt->tag->name = prefix + bt->tag->name;
		else if (bt->typeName)
			bt->typeName->name = prefix + bt->typeName->name; // for typedef, e.g.  T x; will turn into rvs0_T x;
	}
}


///<summary>
/// utility to turn 'struct s' into e.g., 'struct rvs0_s'. Same for "union s" and enum s;
///</summary>
void RVGen::add_side_prefix_to_type(Type* form) const {
	add_prefix_to_type(current_side.get_side_prefix(), form);
}



/* Auxiliary class RVTextFileBuffer: */
/*===================================*/

class RVTextFileBuffer {
public:
	RVTextFileBuffer(const string& fname) : m_fname(fname) {
		RVTextFileReader reader(fname);
		reader.setIgnoreEmptyTokens(false);
        reader.setSpaceCharsDelimiting(false);

		list<string> tokens;
		while (reader.readNextLineTokens(tokens)) {
			assert(tokens.size() == 1);
			m_lines.push_back(tokens.front());
		}

		m_bad = reader.errorOccurred();
	}

	bool errorOccurred(void) const { return m_bad; }

	bool output(void) {
		ofstream fout(m_fname.data());
		m_bad = !fout.is_open();
		if (m_bad)
			return false;

		list<string>::const_iterator it;
		for (it = m_lines.begin(); it != m_lines.end(); ++it)
			fout << *it << "\n";

		fout.close();
		return !m_bad;
	}

	int replaceInLine(const string& what, const string& with) {
		int nReplaces = 0;
		list<string>::iterator it;
		for (it = m_lines.begin(); it != m_lines.end(); ++it) {
			size_t pos = 0;
			while ((pos = it->find(what, pos)) != it->npos) {
				it->replace(pos, what.length(), with);
				++nReplaces;
			}
		}
		return nReplaces;
	}

private:
	const string& m_fname;
	list<string>  m_lines;
	bool          m_bad;
};




/* UF generation code: */
/*=====================*/

RVUFGen::RVUFGen(RVTemp& _temps, RVFramaSum& _summarizer_side0, RVFramaSum& _summarizer_side1, bool _seperate_basecase_proof) :
RVGenRename(_temps), summarizer_side0(_summarizer_side0), summarizer_side1(_summarizer_side1)
{ 
	pfp = NULL;
	uf_strname[0] = "ERROR_SIDE0";
	uf_strname[1] = "ERROR_SIDE1";
	seperate_basecase_proof = _seperate_basecase_proof;
}

bool RVUFGen::is_in_arg(unsigned i)
{
	return( (pfp->get_united_argtype(i) & AT_In) != 0 );
}

bool RVUFGen::is_out_arg(unsigned i)
{
	return( (pfp->get_united_argtype(i) & AT_Out) != 0 );
}

bool RVUFGen::is_Aout_arg(unsigned i)
{
	return( (pfp->get_united_argtype(i) & AT_Aout) != 0 );
}


RVArrayRef* RVUFGen::try_get_ua_ref(Decl *decl)
	// returns NULL if decl is not of an AU
{
	SymEntry* ent = NULL;
	Type* orig_type = decl->form;
	RVArrayRef* ref = rv_arrays().get_array_ref(orig_type);

	if( !ref )
		return NULL;

	// Check also that the symbol resembles the one in the ref:
	if( decl->name && (ent = decl->name->entry) && ent != ref->entry ) {
		rv_errstrm << "Warning: found UA refernce related to formal argument \""<<
			*decl->name <<"\" of "<< m_where <<" but the symbol entries does not match.\n";
		rv_errstrm << "  the symbol entry saved in the AU ref is: "<< ref->entry->name <<"\" .\n";
	}

	return ref;
}

Type* RVUFGen::try_get_ua_token_type(Decl *decl)
	// returns NULL if decl is not of an AU
{
	RVArrayRef* ref = try_get_ua_ref(decl);
	if(!ref)
		return NULL;
	return ref->token_type;
}

bool RVUFGen::gen_uf_item_decl(Decl *decl, bool in, bool out, unsigned &rNumUfStructItems)
{
	std::string location(__FUNCTION__);
	if( !decl || !decl->form )
		return false;
	if( !decl->name ) // don't generate for unnamed agruments
		return true;

	Type *print_type = decl->form;

	/* if unknown whether in or out - decide by pointer: */
	if (DBG) {
		if( !in && !out ) {
			rv_errstrm << "Warning: In \""<< m_where <<"\" UF: no struct item is generated"
				" for unused argument \""<< decl->name->name << "\" \n";
		}
	}
	// if the item is a UA - generate a token container for it: 
	Type* ua_type = try_get_ua_token_type(decl);
	if(ua_type)
		print_type = ua_type;

	if( in ) {
		gen_decl_w_side(print_type, temps.uf_item_prefix(true), decl->name, location);
		++rNumUfStructItems;
	}
	if( out ) {
		gen_decl_w_side(print_type, temps.uf_item_prefix(false), decl->name, location);
		++rNumUfStructItems;
	}

	return true;
}

///<summary> Part of the Uf generation in the original way (without the cbmc UF macros). Generates the array
/// that holds the inputs and outputs to the UFs.
///</summary>
bool RVUFGen::gen_uf_array()
{
	std::string location(__FUNCTION__);
	int i;
	SymbolVector *rvec;
	SymbolVector *wvec;
	SymbolVector::const_iterator  it;

	current_side = SIDE0; // all types are as on side 0
	m_where = pfp->side_name[0].data();

	/* get function prototype: */
	FunctionType *proto0 = (FunctionType*)pfp->side_func[0]->decl->form;
	if( !proto0 || proto0->type != TT_Function ) {
		rv_errstrm << "RVUFGen::gen_uf_array(): bad prototype for side 0 function: " 
			<< pfp->side_name[0] << " .\n";
		return false;
	}

	temps.gen_uf_struct_head(pfp->name);

	unsigned int nUfStructItems = 0;

	/* gen args to hold values of argument + global values: */
	for(i = 0; i < proto0->nArgs; i++)
		gen_uf_item_decl(proto0->args[i], is_in_arg(i), is_out_arg(i), nUfStructItems);


	rvec = &pfp->side_func[0]->fnode.read;
	FORVEC(it,(*rvec)) {
		if( !ignore_in_global(*it, 0) )
			gen_uf_item_decl((*it)->entry->uVarDecl, true, false, nUfStructItems);
		/* rv_errstrm << "var :" << (*it)->name << "in rvec loop\n"; */
	}


	wvec = &pfp->side_func[0]->fnode.written;
	FORVEC(it,(*wvec)) {
		gen_uf_item_decl((*it)->entry->uVarDecl, false, true, nUfStructItems);
		/*rv_errstrm << "var :" << (*it)->name << "in wvec loop\n"; */
	}


	/* if the function has return value: */
	if( !is_basetype(proto0->subType, BT_Void) ) {
		Symbol dummy_sym;
		dummy_sym.name = uf_retvar;
		gen_decl( proto0->subType, temps.uf_item_prefix(false), &dummy_sym, location);
		nUfStructItems++;
	}

	gen_reach_equiv_flag(nUfStructItems);

	if(nUfStructItems == 0) // if there is nothing in the struct - add some dummy:
		temps.print("int dummy;\n");

	temps.gen_uf_struct_tail(pfp->name);

	/* gen an UFarr array of this struct: */
	temps.gen_uf_array(pfp->name);

	return true;
}

bool RVReUfGen::gen_unitrv_uf_array()
{
	/* get function prototype: */
	FunctionType *proto0 = (FunctionType*)pfp->side_func[0]->decl->form;
	if( !proto0 || proto0->type != TT_Function ) {
		rv_errstrm << "RVReUfGen::gen_unitrv_uf_array(): bad prototype for side 0 function: " 
			<< pfp->side_name[0] << " .\n";
		return false;
	}

	// generating the #define statement
	temps.gen_max_array_size(pfp->name);
	
	//generating the recording arrays for all inputs (both local and global)
	gen_all_recording_arrays(proto0, pfp->name);
	
	// generating the arrays that will record the outputs of the side 0 function so that incase both sides are equivalent
	// the values recorded will be used on side1
	gen_all_output_recording_arrays(proto0, pfp->name);

	// generating the mark arrays that unitrv will assert when running
	gen_mark_arrays(pfp->name);

	// generating the count variable 
	gen_count_variable(pfp->name);

	if (get_is_mutual_termination_set()){
		// generating a boolean variable that will tell the uf on side 0 that this is its first call so that it will initialize
		// all variables.
		gen_first_call_to_uf_flag(pfp->name);
	}

	temps.flush();
}

void RVReUfGen::gen_first_call_to_uf_flag( std::string name )
{
	BaseType* p = new BaseType(BT_Bool);

	Symbol* sym = new Symbol();
	sym->name = get_first_call_flag_name(name) + ";";

	std::ostringstream type_strm;
	p->printType(type_strm, sym, true, 0);
	std::string s = type_strm.str();

	temps.print(s + "\n");
}

void RVReUfGen::gen_count_variable( std::string name )
{
	BaseType* p = new BaseType(BT_Int);

	Symbol* sym = new Symbol();
	sym->name = get_unitrv_count_var_name(name) + ";";

	std::ostringstream type_strm;
	p->printType(type_strm, sym, true, 0);
	std::string s = type_strm.str();

	temps.print(s + "\n");
}

void RVReUfGen::gen_mark_arrays( std::string name )
{
	gen_mark_array(name, "0");
	gen_mark_array(name, "1");
}

void RVReUfGen::gen_mark_array( std::string name, std::string side )
{
	BaseType* p = new BaseType(BT_Int);

	Symbol* sym = new Symbol();
	sym->name = get_mark_array_dereferencing(name, side);

	std::ostringstream type_strm;
	p->printType(type_strm, sym, true, 0);
	std::string s = type_strm.str();

	temps.print(s + "\n");
}

void RVReUfGen::gen_all_recording_arrays( FunctionType * proto0, const std::string& ufname )
{
	temps.print("\n//Recording arrays for local parameter input\n");
	for(int i = 0; i < proto0->nArgs; i++){
		Decl* d = proto0->args[i];
		//if( is_out_arg(i)){
			print_array_for_parameter(d, ufname);
		//}
	}

	// now we create the global ones.

	temps.print("\n//Recording arrays for global input\n");
	SymbolVector vec = pfp->side_func[0]->fnode.read;

	SymbolVector::const_iterator  it;
	FORVEC(it,(vec)) {
		if( ignore_in_global(*it, 0) ) continue;
		/* gen code to save its value in UFarr: */
		Decl *d = (*it)->entry->uVarDecl;
		print_array_for_parameter(d, ufname);
	}   
	
}

//todo: add the ufnam to the recording array name
void RVReUfGen::print_array_for_parameter(Decl* d, const std::string& ufname )
{
	Type* sub;
	if (d->form->type == TT_Base){
		sub = d->form;
	}
	else if (d->form->type == TT_Pointer){
		sub = ((PtrType*) d->form)->subType;
	}
	
	string var_name = UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + ufname + "_" + d->name->name + "[" + temps.uf_array_size_name(ufname) + "];";
	Symbol* newsym = new Symbol();
	newsym->name = var_name;
	std::ostringstream type_strm;
	sub->printType(type_strm, newsym, true, 0);
	std::string s = type_strm.str();

	temps.print(s + "\n");
}


std::string RVUFGen::item_prefix()
{
	return uf_strname[current_side.index()];
}

Decl* RVUFGen::related_side0_global(Symbol* glob, bool in)
	/* used to get the right UFarr struct item - no add_side_prefix() is needed. */
{
	Symbol*  ret = pfp->related_other_side_global(glob, 0, in);
	if( ret )
		return ret->entry->uVarDecl;

	fatal_error("Internal Error: related_side0_global() can't find a side 0 global var \n"
		"  related to side 1 global var: ", glob->name, false);

	return glob->entry->uVarDecl;
}

Decl* RVUFGen::related_side0_arg(int arg_num)
{
	return pfp->side_arg(arg_num, 0);
}

static void normalizename(string& name) {
	int pos = -1;
	while ((pos = name.find_first_of(".", pos + 1)) != -1)
		name.replace(pos, 1, "_dot_");
	while ((pos = name.find_first_of("->", pos + 1)) != -1)
		name.replace(pos, 2, "_arrow_");
	while ((pos = name.find_first_of("*", pos + 1)) != -1)
		name.replace(pos, 1, "_astrk_");
}

string RVUFGen::arr_out_name(int counter, int call_counter, string name, int side) {
	stringstream s;
	s << G_ARR_OUT << "_s" << side << "_" << name << "_" << counter << "_" << call_counter;
	return s.str();
}

void RVUFGen::arr_save_in(int counter, unsigned int max_records, int i, string& arr_save_decl, string *arr_save_assign) { // change tag: ARRAYS_IN_UF	
			array_in_names.push_back(m_vars[i].name);			
			stringstream s;
			s << G_ARR_SAVE << "_";
			if (counter) {  // in case there are multiple UFs, they can be called with the same array name, so we need to disambiguate 
				s << counter << "_";
			}
			stringstream ind;
			for (unsigned int ii = 0; ii < 	max_records; ++ii) {
				ind << ii;
				string save_name;
				save_name = s.str() + m_vars[i].name + "_" + ind.str();
				stringstream sz;
				sz << m_vars[i].array_size;
				arr_save_decl.append(ren[0]->convert_ids(m_vars[i].type) + " " + save_name + "[" + sz.str() + "];\n"); 
				arr_save_assign[ii].append("RVT_COPY_ARRAY(" + save_name + ", " + m_vars[i].name + ", " + sz.str() + "); "); 
				ind.str("");
			} 
}

///<summary>
/// Called by gen_side0_cbmc_uf, and handles a part of the arrays solution.  change tag: ARRAYS_IN_UF
///</summary>
void RVUFGen::arr_out(int counter, unsigned int max_records, int i, string arr_p, string& arr_out_decl, string *arr_out_save_assign, string& arr_P_out) {			
			array_out_names.push_back(m_vars[i].name);
			for (unsigned int ii = 0; ii < max_records; ++ii) {
				stringstream sz;
				sz << m_vars[i].array_size;
				string name0, name1;
				name0 = arr_out_name(counter, ii, m_vars[i].name, 0);
				name1 = arr_out_name(counter, ii, m_vars[i].name, 1);
				
				arr_out_decl.append(ren[0]->convert_ids(m_vars[i].type) + " " + name0 + "[" + sz.str() + "];\n");
				arr_out_decl.append(ren[0]->convert_ids(m_vars[i].type) + " " + name1 + "[" + sz.str() + "];\n"); 				
				arr_out_save_assign[ii].append(arr_p + "_s0_" + m_vars[i].name + " = " + arr_out_name(counter, ii, m_vars[i].name, 0) + "; ");
				arr_out_save_assign[ii].append(arr_p + "_s1_" + m_vars[i].name + " = " + arr_out_name(counter, ii, m_vars[i].name, 1) + "; ");

				// these will be used in main:
				temps.add_array_nondet_decl("  " + ren[0]->convert_ids(m_vars[i].type) + RV_NONDET_ARR + name0 + "[" + sz.str() + "];\n");
				temps.add_array_nondet_decl("  " + ren[0]->convert_ids(m_vars[i].type) + RV_NONDET_ARR + name1 + "[" + sz.str() + "];\n");
				temps.add_array_nondet_assign("  __CPROVER_array_copy(" + name0 + ", " + RV_NONDET_ARR + name0 + ");\n");
				temps.add_array_nondet_assign("  __CPROVER_array_copy(" + name1 + ", " + RV_NONDET_ARR + name1 + ");\n");				
			}
			arr_P_out.append("  " + ren[0]->convert_ids(m_vars[i].type) + "*" + arr_p + "_s0_" + m_vars[i].name + ";\n");
			arr_P_out.append("  " + ren[0]->convert_ids(m_vars[i].type) + "*" + arr_p + "_s1_" + m_vars[i].name + ";\n");
}


class SearchTypeofArg : public RVWalk {
public:
	string searchitem;
	unsigned int paramNum;
	Type *argType;
	RVTreeComp compare;
	SearchTypeofArg(const string& item, unsigned int param) : searchitem(item), paramNum(param), argType(NULL) {}

	virtual bool process(Expression* s0p) {
		if (s0p->etype == ET_FunctionCall) {
			RETYPE( FunctionCall );
			assert (!RVTypePropIgnoreNondet::ignored(static_cast<const Variable*>(s0p->function)));
			if (s0p->function->etype != ET_Variable) return false; // in case this is an indirect function, we do not know if it points to the searched function or not. In case it is, it might use a parameter with an incompatible type, which is the case that we need to fail;
			if (((Variable *)s0p->function)->name->name == searchitem)  
			{
				cout << "bingo!";		  
				Type *type = real_type(s0p->args.at(paramNum)->type, __FUNCTION__);		  
				if (is_basetype(type, BT_Void) || (argType != NULL && !compare.eq_type(argType, type ))) return false; // must abort this branch
				argType = type;				
			}
		}
		return true;
	}
};





typedef struct { // change tag: NULL_DEREF_IN_UF
	Type *tp;
	string name;
} pvar;

///<summary>
/// Based on the CBMC UF macros. Generates the UF for side 0 + cbmc macro function declarations. 
/// Arrays are handled in a special way, because we cannot send them as parameters to the UF macros. We need the array macros for that. 
/// The solution is explained in change_tags.txt
/// <param name="counter">if we have multiple UFs calls, we need to add a counter to the name to avoid colisions (e.g. if the variable 'x' is an output of both 'f' and 'g')</param>
///</summary>
void RVUFGen::gen_side0_cbmc_uf(int counter, bool rec_func_uf)
{
	string location(__FUNCTION__);
	Decl *decl;
	SymbolVector *vec;
	SymbolVector::const_iterator it;
	std::ostringstream proto_strm;
	std::ostringstream ret_type_strm;
	const std::string *pretvar = &uf_retvar;		
	m_vars.clear();	
	UF_names.clear();
	array_in_names.clear();
	array_out_names.clear();
	current_side = SIDE0;
	m_where = pfp->side_name[0].data();
	FunctionType *proto = (FunctionType*)pfp->side_func[0]->decl->form;
	assert(proto && proto->type == TT_Function );
	unsigned int local_max_records = m_pSemChecker->countMaxCallChain(current_side, &m_pSemChecker->getMainPair()->side_name[0], pfp->side_name[0]); // This returns the number of times that this UF is being called. It scans the *original* program, and hence might overapproximate, e.g., consider the call graph f -> h, h -> g, f -> g, and that both h and g are UFs. So we do not need to count the call h -> g. This overapproximation does not affet soundness/completeness: it only generates 'case' statements that will never be used. 

	/* if the function returns void: */
	if( is_basetype(proto->subType, BT_Void) )	pretvar = NULL;  /* gen no retvar */
	else proto->subType->printType(ret_type_strm, NULL, true, 0);	
	
	string ufprefix;
	if (counter) {
		stringstream s;
		s << counter;
		ufprefix = UFPREFIX + s.str() + "_";
	}
	else ufprefix = UFPREFIX;	

	bool first = true;	
	string arg;  // collects the input arguments to the UF calls (same arguments to all). 	
	string UF_proto; // list of types (e.g. (int, int)) that is the argument to the UF in the declaration.

	// arrays
	string arr_save_decl; // We declare one global array variable per array that is an input to the function. This strings accumulate the declarations. // change tag: ARRAYS_IN_UF
	string *arr_save_assign = new string[local_max_records]; // see above. This string accumulates the assignments at the beginning of the function. 
	string arr_out_decl; // two global array outputs for each array (times the number of records in local_max_records). This string accumulates the declararions.
	string *arr_out_save_assign = new string[local_max_records]; // see above
	string arr_P_out; // local auxiliary variable
	string arr_p(ARR_P); // constant string (not using ARR_P directly because cannot concatenate two cstrings simply)
	vector<pvar> pvars; // change tag: NULL_DEREF_IN_UF. If an input/global pointer variable arrives as null, we allocate it. Otherwise the automatic 'assume not null deref' will block the pass, and make it unsound.

	// for each input arg: 	
	for(int i = 0; i < proto->nArgs; i++) {		
		decl = proto->args[i];
		if( !decl || !decl->name || !is_in_arg(i)) continue;
		//DIMAXXX RVGenCtx ctx(decl->name, decl->form, decl->name->name, "", true, false, m_where, this);

		RVGenCtx ctx(m_where, true, this);
		ctx.set_unitrv(m_unitrv);
    	ctx.add_lane(decl->name, decl->form, decl->name->name, SIDE0, "");

		gen_item_or_struct_op(ADD, ctx, location);
		if (ctx.is_pointer(0) && !ctx.is_array(0)) {
			pvar p = {decl->form, decl->name->name};			
			pvars.push_back(p);
		}
	}
	// for each input global:
	
	vec = &pfp->side_func[0]->fnode.read;
	FORVEC(it,(*vec)) {
		if( ignore_in_global(*it, 0) ) continue;	// globals that are read-only are ignored.
		decl = (*it)->entry->uVarDecl;
		//DIMAXXX RVGenCtx ctx1(decl->name, decl->form, decl->name->name, "", true, true, m_where, this);
        
        RVGenCtx ctx(m_where, true, this);
		ctx.set_unitrv(m_unitrv);
		string global_var_prefix = "";
		if (!m_unitrv){
			global_var_prefix = SIDE0.get_side_prefix();
		}
    	ctx.add_lane(decl->name, decl->form, decl->name->name, SIDE0, global_var_prefix);

		gen_item_or_struct_op(ADD, ctx, location);
		if (ctx.is_pointer(0)&& !ctx.is_array(0)) {
			pvar p = {decl->form, SIDE0.get_side_prefix() + decl->name->name};			
			pvars.push_back(p);
		}
	}

	// Generating the argument list arg, and the UF proto-types UF_proto

	for (unsigned int i = 0; i < m_vars.size(); ++i) {		
		if (!first) {
			arg.append(", "); 
			UF_proto.append(", ");			
		}
		else first = false;
		if(m_vars[i].is_array) {
			arg.append("1"); 
			arr_save_in(counter, local_max_records, i, arr_save_decl, arr_save_assign);
		}				
		else {
			if (m_vars[i].is_pointer) arg.append("*");				
			arg.append(m_vars[i].name);		
		}
		string type = ren[0]->convert_ids(m_vars[i].type);

		UF_proto.append(type);
	}
	m_vars.clear();	
	

	temps.print("\n  /* Declarations of the CBMC uninterpreted functions */\n");
	if (arr_save_decl.size() > 0) {
		temps.print("  /* Globals for saving input arrays: */\n");
		temps.print(arr_save_decl + "\n");
		printf ("%s calls %s %d times\n", m_pSemChecker->getMainPair()->side_name[0].data(),
										  pfp->side_name[0].data(),
										  local_max_records) ;

	}
	// for each output argument
	for(int i = 0; i < proto->nArgs; i++) {
		decl = proto->args[i];
		if( !is_out_arg(i) || !decl || !decl->name ) continue;
	// declaration of the UFs (e.g. int *__CPROVER_uninterpreted_x(int, int);)
		//DIMAXXX RVGenCtx ctx(decl->name, decl->form, decl->name->name, "", false, false, m_where, this);

		RVGenCtx ctx(m_where, false, this);
		ctx.set_unitrv(m_unitrv);
    	ctx.add_lane(decl->name, decl->form, decl->name->name, SIDE0, "");

		if (ctx.is_aggregate()) is_aggregate = true;
		gen_item_or_struct_op(ADD, ctx, location);	
		is_aggregate = false;
	}
	// for each written-to global
	vec = &pfp->side_func[0]->fnode.written;
	FORVEC(it,(*vec)) {
	// declarations of the UFs (same as above)
		decl = (*it)->entry->uVarDecl;		
		//DIMAXXX RVGenCtx ctx(decl->name, decl->form, decl->name->name, "", false, true, m_where, this);

		RVGenCtx ctx(m_where, false, this);
		ctx.set_unitrv(m_unitrv);
		string global_var_prefix = "";
		if (!m_unitrv){
			global_var_prefix = SIDE0.get_side_prefix();
		}

    	ctx.add_lane(decl->name, decl->form, decl->name->name, SIDE0, global_var_prefix);

		if (ctx.is_aggregate()) is_aggregate = true;
		gen_item_or_struct_op(ADD, ctx, location);	
		is_aggregate = false;
	}
	// for the return value
	if(pretvar) {				
		//DIMAXXX RVGenCtx ctx((Symbol *) NULL,proto->subType, *pretvar, "",	false, false, m_where, this);

		RVGenCtx ctx(m_where, false, this);
    	ctx.add_lane((Symbol *) NULL, proto->subType, *pretvar, SIDE0, "");

		if (ctx.is_aggregate()) is_aggregate = true;
		gen_item_or_struct_op(ADD, ctx, location);
		is_aggregate = false;
	}	
	
	for (unsigned int i = 0; i < m_vars.size(); ++i) {
		if (m_vars[i].is_array) 			
            arr_out(counter, local_max_records, i, arr_p, arr_out_decl, arr_out_save_assign, arr_P_out);		 
		string flat_name = m_vars[i].name;				
		normalizename(flat_name);
		UF_names.push_back(flat_name);		
		temps.print(ren[0]->convert_ids(m_vars[i].type) + " " + ufprefix + flat_name + "(" + UF_proto + ");\n");		
	}
	if (arr_out_decl.length() > 0) {
		temps.print("  /* For each array X side X record, an output array. */\n");
		temps.print(arr_out_decl + "\n");
	}
	temps.print("\n  /* CBMC-UF side 0: */ \n");

	add_prefix_if_required_side0(pfp, "rvs0_");
	
	pfp->side_func[0]->decl->print(proto_strm, true, 0);
	
	temps.print(ren[0]->convert_ids( proto_strm.str() ));	
	temps.gen_uf_head(ren[0]->convert_ids(ret_type_strm.str()), pretvar);		
	
	// allocating pointers that are sent as NULL. See change tag: NULL_DEREF_IN_UF
	temps.separate_protect_streams(); // this must be printed at the beginning of the code, hence the separate stream.
	if (pvars.size()) temps.print("  /* Protecting pointers from being NULL-dereferenced: */\n");
	for (unsigned int i = 0; i < pvars.size(); ++i) {		
		RVGenCtx ctx(m_where, false, this);
    	ctx.add_lane((Symbol *) NULL,pvars[i].tp, pvars[i].name, 0, "");		
		temps.print("  if (" + pvars[i].name + "== 0) {\n");
		gen_item_or_struct_op(ALLOC, ctx, location);
		temps.print("  }\n");  
	}

	temps.separate_uf_streams();

	if (seperate_basecase_proof && rec_func_uf){
		print_basecase_flag_update();
	}

	if (arr_P_out.length() > 0) {
		temps.print("  static unsigned char rv_call_counter = 0;\n");	
		temps.print(arr_P_out); 
		temps.print("  switch(rv_call_counter) {\n");
		stringstream s;
		for (unsigned int ii = 0; ii < local_max_records; ++ii) {
			s << ii;
			temps.print("    case " + s.str() + ":" + arr_out_save_assign[ii] + arr_save_assign[ii] + "break;\n");
			s.str("");
		}

		temps.print("    default: assert(0);\n  }\n");
		temps.print("  rv_call_counter++;\n");
	}
	temps.print("  /* Each output is assigned a UF:*/\n");
	for (unsigned int i = 0; i < m_vars.size(); ++i) {
		if (m_vars[i].is_array) {
			stringstream sz;
			sz << m_vars[i].array_size;
			temps.print("  if (" + ufprefix + UF_names[i] + "(" + arg + "))\n"); 
			temps.print("  {RVT_COPY_ARRAY(" + m_vars[i].name + ", " + arr_p + "_s0_" + m_vars[i].name + ", " + sz.str() + ");}\n");
			temps.print("  else\n");
			temps.print("  {RVT_COPY_ARRAY(" + m_vars[i].name + ", " + arr_p + "_s1_" + m_vars[i].name + ", " + sz.str() + ");}\n");
		}
		else {
			string p = m_vars[i].is_pointer?"*":"";
			temps.print("  " + p + m_vars[i].name + "= " + ufprefix + UF_names[i] + "(" + arg + ");\n");			
		}
	}

	temps.unite_uf_streams();
	//This is where the summary should go.
	temps.print("__CPROVER_assume(" + summarizer_side0.getIntervalCondition(pfp->name) + ");");
	temps.gen_uf_tail(pretvar);
}

///<summary>
/// Based on the CBMC UF macros. Generates the UF for side 1.
/// <param name="counter">if we have multiple UFs calls, we need to add a counter to the name to avoid colisions (e.g. if the variable 'x' is an output of both 'f' and 'g')</param>
///</summary>
void RVUFGen::gen_side1_cbmc_uf(int counter, bool rec_func_uf)
{
	string location(__FUNCTION__);
	Decl *decl, *side0_decl; 
	SymbolVector *vec;
	SymbolVector::const_iterator  it;
	std::ostringstream proto_strm;
	std::ostringstream ret_type_strm;
	const std::string *pretvar = &uf_retvar;		
	current_side = SIDE1;
	unsigned int local_max_records = m_pSemChecker->countMaxCallChain(current_side, &m_pSemChecker->getMainPair()->side_name[1], pfp->side_name[1]);	
	m_where = pfp->side_name[1].data();	
	FunctionType *proto = (FunctionType*)pfp->side_func[1]->decl->form;
	assert(proto && proto->type == TT_Function );
	string *arr_out_save_assign = new string[local_max_records]; // see above
	string arr_P_out; // local auxiliary variable
	string arr_p(ARR_P); // constant string (not using ARR_P directly because cannot concatenate two cstrings simply)
	vector<pvar> pvars; // change tag: NULL_DEREF_IN_UF. If an input/global pointer variable arrives as null, we allocate it. Otherwise the automatic 'assume not null deref' will block the pass, and make it unsound. 

	m_vars.clear();	

	/* if the function returns void: */
	if( is_basetype(proto->subType, BT_Void) )	pretvar = NULL;  /* gen no retvar */
	else proto->subType->printType( ret_type_strm, NULL, true, 0);	
	
	string ufprefix;
	if (counter) {
		stringstream s;
		s << counter;
		ufprefix = UFPREFIX + s.str() + "_";
	}
	else ufprefix = UFPREFIX;

	bool first = true;	
	string arg;  // collects the input arguments to the UF calls (same arguments to all). 
	string arr_eq_decl; // for each array A, declares "_Bool equal_A;" 
	string *arr_save_assign = new string[local_max_records]; 
	
	// for each input arg: 	
	for(int i = 0; i < proto->nArgs; i++) {		
		decl = proto->args[i];
		if( !is_in_arg(i) || !decl || !decl->name ) continue;				
		side0_decl = related_side0_arg(i);
		//DIMAXXX RVGenCtx ctx(decl->name,side0_decl->form, side0_decl->name->name, "", decl->form, decl->name->name, SIDE1, true, false, m_where, this);

		RVGenCtx ctx(m_where, true, this, SIDE1);
		ctx.add_lane(decl->name, decl->form, decl->name->name, SIDE1, "");

		gen_item_or_struct_op(ADD, ctx, location);		
		if (ctx.is_pointer(0) && !ctx.is_array(0)) {
			pvar p = {decl->form, decl->name->name};			
			pvars.push_back(p);
		}
	}
	// for each input global
	vec = &pfp->side_func[1]->fnode.read;
	FORVEC(it,(*vec)) {
		if( ignore_in_global(*it, 1) ) continue;	// globals that are read-only are ignored.
		decl = (*it)->entry->uVarDecl;		
		side0_decl = related_side0_global(decl->name, true);
		//DIMAXXX RVGenCtx ctx(decl->name,side0_decl->form, side0_decl->name->name, "", decl->form, decl->name->name, SIDE1, true, true, m_where, this);

		RVGenCtx ctx(m_where, true, this, SIDE1);
		string global_var_prefix = "";
		if (!m_unitrv){
			global_var_prefix = SIDE1.get_side_prefix();
		}

		ctx.add_lane(decl->name, decl->form, decl->name->name, SIDE1, global_var_prefix);

		gen_item_or_struct_op(ADD, ctx, location);	
		if (ctx.is_pointer(0) && !ctx.is_array(0)) {
			pvar p = {decl->form, SIDE1.get_side_prefix() + decl->name->name};
			pvars.push_back(p);
		}
	}

	// Generating the argument list arg
	unsigned int count = 0;
	for (unsigned int i = 0; i < m_vars.size(); ++i) {
		if (!first) {
			arg.append(", "); 		
		}
		else first = false;
		
		
		if(m_vars[i].is_array) { // change tag: ARRAYS_IN_UF						
			stringstream s, s1;
			s << ARR_EQ_PREFIX << "_";			
			s1 << G_ARR_SAVE << "_";			
			if (counter) {  // in case there are multiple UFs called with the same array name, we need to disambiguate 
				s << counter << "_";
				s1 << counter << "_";
			}
			string eq_name = s.str() + m_vars[i].name;
			arg.append(eq_name);  
			arr_eq_decl.append("  _Bool " + eq_name + ";\n");
			for (unsigned int ii = 0; ii < local_max_records; ++ii) {
				s.str("");
				s << "_" << ii;
				arr_save_assign[ii].append("  " + eq_name + " = __CPROVER_array_equal(" + m_vars[i].name + "," + s1.str() + array_in_names[count] +  s.str() + "); ");  				
			}
			count++;
		}
		else {
			if (m_vars[i].is_pointer) arg.append("*");
			arg.append(m_vars[i].name);	
		}
	}
	m_vars.clear();	
	

	// for each output argument
	for(int i = 0; i < proto->nArgs; i++) {
		decl = proto->args[i];
		if( !is_out_arg(i) || !decl || !decl->name ) continue;
	// declaration of the UFs (e.g. int *__CPROVER_uninterpreted_x(int, int);)		
		side0_decl = related_side0_arg(i);
		//DIMAXXX RVGenCtx ctx(decl->name,side0_decl->form, side0_decl->name->name, "", decl->form, decl->name->name,	SIDE1, false, false, m_where, this);

		RVGenCtx ctx(m_where, false, this, SIDE1);
		ctx.add_lane(decl->name, decl->form, decl->name->name, SIDE1, "");

		if( !ctx.check_out_arg(item_lane()) ) continue; // outputs should be pointers. This checks that.
		if (ctx.is_aggregate()) is_aggregate = true;
		gen_item_or_struct_op(ADD, ctx, location);	
		is_aggregate = false;
	}
	
	// for each writtento global
	vec = &pfp->side_func[1]->fnode.written;
	FORVEC(it,(*vec)) {
	// declarations of the UFs (same as above)
		decl = (*it)->entry->uVarDecl;				
		side0_decl = related_side0_global(decl->name, false);
		//DIMAXXX RVGenCtx ctx(decl->name, side0_decl->form, side0_decl->name->name, "", decl->form, decl->name->name, SIDE1, false, true, m_where, this);

		RVGenCtx ctx(m_where, false, this, SIDE1);
		string global_var_prefix = "";
		if (!m_unitrv){
			global_var_prefix = SIDE1.get_side_prefix();
		}
		ctx.add_lane(decl->name, decl->form, decl->name->name, SIDE1, global_var_prefix);

		if (ctx.is_aggregate()) is_aggregate = true;
		gen_item_or_struct_op(ADD, ctx, location);	
		is_aggregate = false;
	}
	// for the return value
	if(pretvar) {						
		//DIMAXXX Type* side0_type = ((FunctionType*)pfp->side_func[1]->decl->form)->subType;
		//DIMAXXX RVGenCtx ctx((Symbol *) NULL ,side0_type, *pretvar, "",	proto->subType, *pretvar, SIDE1, false, false, m_where, this);

		RVGenCtx ctx(m_where, false, this, SIDE1);
		ctx.add_lane((Symbol *) NULL ,proto->subType, *pretvar, SIDE1, "");

		if (ctx.is_aggregate()) is_aggregate = true;
		gen_item_or_struct_op(ADD, ctx, location);
		is_aggregate = false;
	}	
	
	count = 0;
	for (unsigned int i = 0; i < m_vars.size(); ++i) {
		if (m_vars[i].is_array) {
			string name0 = array_out_names[count++];
			for (unsigned int ii = 0; ii < local_max_records; ++ii) {
				stringstream sz;
				sz << m_vars[i].array_size;
				arr_out_save_assign[ii].append(arr_p + "_s0_" + m_vars[i].name + " = " + arr_out_name(counter, ii, name0, 0) + "; ");
				arr_out_save_assign[ii].append(arr_p + "_s1_" + m_vars[i].name + " = " + arr_out_name(counter, ii, name0, 1) + "; ");
			}
			arr_P_out.append("  " + ren[0]->convert_ids(m_vars[i].type) + "*" + arr_p + "_s0_" + m_vars[i].name + ";\n");
			arr_P_out.append("  " + ren[0]->convert_ids(m_vars[i].type) + "*" + arr_p + "_s1_" + m_vars[i].name + ";\n");
		}
	}



	temps.print("\n  /* CBMC-UF side 1: */ \n");
	
	add_prefix_if_required_side1(pfp, "rvs1_");
	
	pfp->side_func[1]->decl->print(proto_strm, true, 0);	

	temps.print(ren[1]->convert_ids( proto_strm.str() ));
	
	temps.gen_uf_head(ren[1]->convert_ids(ret_type_strm.str()), pretvar);	
	
	
	
	// allocating pointers that are sent as NULL. See change tag: NULL_DEREF_IN_UF
	temps.separate_protect_streams(); // this must be printed at the beginning of the code, hence the separate stream.
	if (pvars.size()) temps.print("  /* Protecting pointers from being NULL-dereferenced: */\n");
	for (unsigned int i = 0; i < pvars.size(); ++i) {		
		RVGenCtx ctx(m_where, false, this);
    	ctx.add_lane((Symbol *) NULL,pvars[i].tp, pvars[i].name, 1, "");		
		temps.print("  if (" + pvars[i].name + "== 0) {\n");
		gen_item_or_struct_op(ALLOC, ctx, location);
		temps.print("  }\n");  
	}
	
	if (seperate_basecase_proof && rec_func_uf ){
		print_basecase_flag_update();
	}

	temps.separate_uf_streams();  // we separate streams because the following involves both declarations and code. 
	temps.print(arr_eq_decl);

	if (arr_P_out.length() > 0) {
		temps.print("  static unsigned char rv_call_counter = 0;\n");	
		temps.print(arr_P_out); 
		temps.print("  switch(rv_call_counter) {\n");	
		stringstream s;
		for (unsigned int ii = 0; ii < local_max_records; ++ii) {
			s << ii;
			temps.print("    case " + s.str() + ":" + arr_out_save_assign[ii] + arr_save_assign[ii] + " break;\n");
			s.str("");
		}
		temps.print("    default: assert(0);\n  }\n");
		temps.print("  rv_call_counter++;\n");
	}

	temps.print("  /* Each output is assigned a UF:*/\n");
	for (unsigned int i = 0; i < m_vars.size(); ++i) {				
			if (m_vars[i].is_array) {
			stringstream sz;
			sz << m_vars[i].array_size;
			temps.print("  if (" + ufprefix + UF_names[i] + "(" + arg + "))\n"); 
			temps.print("  {RVT_COPY_ARRAY(" + m_vars[i].name + ", " + arr_p + "_s0_" + m_vars[i].name + ", " + sz.str() + ");}\n");
			temps.print("  else\n");
			temps.print("  {RVT_COPY_ARRAY(" + m_vars[i].name + ", " + arr_p + "_s1_" + m_vars[i].name + ", " + sz.str() + ");}\n");
		}
		else{
	
		string p = m_vars[i].is_pointer?"*":"";
		temps.print("  " + p + m_vars[i].name + "= " + ufprefix + UF_names[i] + "(" + arg + ");\n");
		}
	}
	m_vars.clear();	
	temps.unite_uf_streams(); // This prints the stream in order: declaraions; code.

	temps.print("__CPROVER_assume(" + summarizer_side1.getIntervalCondition(pfp->name) + ");");


	temps.gen_uf_tail(pretvar);
}


bool RVReUfGen::gen_unitrv_side0_uf()
{
	string location(__FUNCTION__);
	bool ret = true;
	int i;
	Decl *decl;
	bool pointer;
	SymbolVector *vec;
	SymbolVector::const_iterator  it;
	std::ostringstream proto_strm;
	std::ostringstream ret_type_strm;
	const std::string *pretvar = &uf_retvar;
	std::string item_pref;

	RVGenCtx::reset_local_var_count();

	current_side = SIDE0;
	m_where = pfp->side_name[0].data();
	//item_pref = item_prefix(); // gotta change this function

	//item_pref = unitrv_item_prefix();

	temps.print("\n /*** uninterpreted function side 0: ***/ \n");

	/* generate 0 side func prototype: */
	FunctionType *proto0 = (FunctionType*)pfp->side_func[0]->decl->form;
	if( !proto0 || proto0->type != TT_Function ) {
		rv_errstrm << "RVUFGen::gen_side0_uf(): bad prototype for side 0 function: " 
			<< pfp->side_name[0] << " .\n";
		return false;
	}
	add_prefix_if_required_side0(pfp, "rvs0_");
	pfp->side_func[0]->decl->print(proto_strm, true, 0);
	CHK_NULL1( ren[0], "ren[0] in RVUFGen::gen_side0_uf()");

	//temps.separate_uf_streams();
	temps.print( ren[0]->convert_ids( proto_strm.str() ));

	/* if the function returns void: */
	if( is_basetype(proto0->subType, BT_Void) )
		pretvar = NULL;  /* gen no retvar */
	else {
		pointer = is_pointer(proto0->subType, m_where);
		if( pointer )  /* returns non tokenized pointer: */
			rv_errstrm << "Warning: return value of UF \"" << pfp->side_name[0].data() 
			<< "\" (side 0) is a pointer !\n";

		proto0->subType->printType( ret_type_strm, NULL, true, 0);
	}
	temps.gen_uf_head( ren[0]->convert_ids(ret_type_strm.str()), pretvar);


	indent = 1;

	temps.print(" /* Zeroing both mark arrays and count variable for unitrv mutual termination check */\n");

	//gen_initializing_of_unitrv_mutual_termination_variables();


	temps.print("  /* save values of input arguments: */\n");
	/* for each input arg: */
	for(i = 0; i < proto0->nArgs; i++) {
		/* gen code to save its value in UFarr: */
		decl = proto0->args[i];
		if( !is_in_arg(i) || !decl || !decl->name ) continue;
		item_pref = unitrv_item_prefix(decl->name->name);
		string type_prefix = get_variable_prefix(decl->form);
		temps.print("	" + item_pref + " = " + type_prefix + decl->name->name + ";\n");
		/*gen_unitrv_record_data_line(decl->name->name);*/

		/*RVGenCtx ctx(decl->name, decl->form, decl->name->name, item_pref, true, false, m_where, this);		
		ret = gen_item_or_struct_op(COPY_S1_to_S0, ctx, location) && ret;*/
	}
	//item_pref = item_prefix();
	/* for each input global: */
	temps.print("  /* save values of input globals: */\n");
	vec = &pfp->side_func[0]->fnode.read;
	FORVEC(it,(*vec)) {
		if( ignore_in_global(*it, 0) ) continue;
		/* gen code to save its value in UFarr: */
		decl = (*it)->entry->uVarDecl;
		item_pref = unitrv_item_prefix(decl->name->name);
		RVGenCtx ctx(decl->name, decl->form, decl->name->name, item_pref, true, true, m_where, this);
		ret = gen_item_or_struct_op(COPY_S1_to_S0, ctx, location) && ret;
	}   


	temps.print("\n  /* generate and save values of output arguments and globals: */\n");
	/* for each output arg: */
	for(i = 0; i < proto0->nArgs; i++) {
		decl = proto0->args[i];
		if( !is_out_arg(i) || !decl || !decl->name ) continue;
		
		item_pref = unitrv_output_item_prefix(decl->name->name);


		RVGenCtx ctx(decl->name,decl->form, decl->name->name, item_pref, false, false, m_where, this);
		if( !ctx.check_out_arg(1) ) continue;

		// pointer arg value must be changed in place - 
		//  allocating new place won't change the value visible from outside.
		dont_alloc_root = true;
		//temps.gen_nondet_save_val("left", "right", 
		ret = gen_item_or_struct_op(NONDET_SAVE, ctx, location) && ret;
	}

	/* for the return value: */
	//decl = proto0->args[proto0->nArgs - 1];
	//item_pref = unitrv_output_item_prefix(decl->name->name);

	if(pretvar) {
		temps.print("\n  /* generate and save value for the functino output : */\n");
		Symbol* retvalsym= new Symbol();
		retvalsym->name = *pretvar;

		Decl* decl = new Decl(retvalsym);
		decl->form = proto0->subType;

		item_pref = unitrv_output_item_prefix(decl->name->name);
		

		RVGenCtx ctx((Symbol *) NULL,proto0->subType, *pretvar, item_pref,	false, false, m_where, this);
		ret = gen_item_or_struct_op(NONDET_SAVE, ctx, location) && ret;
	}

	///* Now printing the return variable */
	


	//RVGenCtx ctx(decl->name,decl->form, decl->name->name, item_pref, false, false, m_where, this);
	////if( !ctx.check_out_arg(1) ) continue;

	//// pointer arg value must be changed in place - 
	////  allocating new place won't change the value visible from outside.
	//dont_alloc_root = true;
	////temps.gen_nondet_save_val("left", "right", 
	//ret = gen_item_or_struct_op(NONDET_SAVE, ctx, location) && ret;

	/* for each output global: */
	vec = &pfp->side_func[0]->fnode.written;
	FORVEC(it,(*vec)) {
		decl = (*it)->entry->uVarDecl;
		item_pref = unitrv_output_item_prefix(decl->name->name);
		RVGenCtx ctx(decl->name,decl->form, decl->name->name, item_pref, false, true, m_where, this);
		ret = gen_item_or_struct_op(NONDET_SAVE, ctx, location) && ret;
	}

	std::string count_var_name = get_count_var_name(pfp->name);
	print_unitrv_mark_array_flagging(pfp->name, "0", count_var_name);

	gen_unitrv_uf_inc_count(pfp->name);
	
	//temps.print(proto_strm.str());
	temps.gen_uf_tail(pretvar);
	temps.flush();
	
	return ret;
}

void RVReUfGen::gen_unitrv_record_data_line( std::string name )
{//todo: gotta figure out how their function figures our pointers and shit like that
	std::string ufname = pfp->side_name[0];
	std::string line = UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + ufname +"_" + name + "[" + UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + ufname + "_count] = *" + name + ";\n";
	temps.print(line);
}


std::string RVReUfGen::unitrv_item_prefix( std::string name )
{
	return UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + pfp->side_name[0] + "_" + name + "[" + UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + pfp->side_name[0] + "_count]";
}

bool RVUFGen::gen_side0_uf()
{
	string location(__FUNCTION__);
	bool ret = true;
	int i;
	Decl *decl;
	bool pointer;
	SymbolVector *vec;
	SymbolVector::const_iterator  it;
	std::ostringstream proto_strm;
	std::ostringstream ret_type_strm;
	const std::string *pretvar = &uf_retvar;
	std::string item_pref;

	RVGenCtx::reset_local_var_count();

	current_side = SIDE0;
	m_where = pfp->side_name[0].data();
	item_pref = item_prefix();

	temps.print("\n /*** uninterpreted function side 0: ***/ \n");

	/* generate 0 side func prototype: */
	FunctionType *proto0 = (FunctionType*)pfp->side_func[0]->decl->form;
	if( !proto0 || proto0->type != TT_Function ) {
		rv_errstrm << "RVUFGen::gen_side0_uf(): bad prototype for side 0 function: " 
			<< pfp->side_name[0] << " .\n";
		return false;
	}
	add_prefix_if_required_side0(pfp, "rvs0_");
	pfp->side_func[0]->decl->print(proto_strm, true, 0);
	CHK_NULL1( ren[0], "ren[0] in RVUFGen::gen_side0_uf()");

	temps.separate_uf_streams();
	temps.print( ren[0]->convert_ids( proto_strm.str() ));
		
	/* if the function returns void: */
	if( is_basetype(proto0->subType, BT_Void) )
		pretvar = NULL;  /* gen no retvar */
	else {
		pointer = is_pointer(proto0->subType, m_where);
		if( pointer )  /* returns non tokenized pointer: */
			rv_errstrm << "Warning: return value of UF \"" << pfp->side_name[0].data() 
			<< "\" (side 0) is a pointer !\n";

		proto0->subType->printType( ret_type_strm, NULL, true, 0);
	}
	temps.gen_uf_head( ren[0]->convert_ids(ret_type_strm.str()), pretvar);

//	gen_no_aliasing_assertions(proto0); // ofer. doesn't work (inserts things like assert (b != b))

	indent = 1;
	temps.print("  /* save values of input arguments: */\n");
	/* for each input arg: */
	for(i = 0; i < proto0->nArgs; i++) {
		/* gen code to save its value in UFarr: */
		decl = proto0->args[i];
		if( !is_in_arg(i) || !decl || !decl->name ) continue;
		RVGenCtx ctx(decl->name, decl->form, decl->name->name, item_pref, true, false, m_where, this);		
		ret = gen_item_or_struct_op(COPY_S1_to_S0, ctx, location) && ret;
	}

	/* for each input global: */
	temps.print("  /* save values of input globals: */\n");
	vec = &pfp->side_func[0]->fnode.read;
	FORVEC(it,(*vec)) {
		if( ignore_in_global(*it, 0) ) continue;
		/* gen code to save its value in UFarr: */
		decl = (*it)->entry->uVarDecl;
		RVGenCtx ctx(decl->name, decl->form, decl->name->name, item_pref, true, true, m_where, this);
		ret = gen_item_or_struct_op(COPY_S1_to_S0, ctx, location) && ret;
	}   

	temps.print("\n  /* generate and save values of output arguments and globals: */\n");
	/* for each output arg: */
	for(i = 0; i < proto0->nArgs; i++) {
		decl = proto0->args[i];
		if( !is_out_arg(i) || !decl || !decl->name ) continue;
		RVGenCtx ctx(decl->name,decl->form, decl->name->name, item_pref, false, false, m_where, this);
		if( !ctx.check_out_arg(1) ) continue;

		// pointer arg value must be changed in place - 
		//  allocating new place won't change the value visible from outside.
		dont_alloc_root = true;
		ret = gen_item_or_struct_op(NONDET_SAVE, ctx, location) && ret;
	}

	/* for each output global: */
	vec = &pfp->side_func[0]->fnode.written;
	FORVEC(it,(*vec)) {
		decl = (*it)->entry->uVarDecl;
		RVGenCtx ctx(decl->name,decl->form, decl->name->name, item_pref, false, true, m_where, this);
		ret = gen_item_or_struct_op(NONDET_SAVE, ctx, location) && ret;
	}

	/* for the return value: */
	if(pretvar) {
		RVGenCtx ctx((Symbol *) NULL,proto0->subType, *pretvar, item_pref,	false, false, m_where, this);
		ret = gen_item_or_struct_op(NONDET_SAVE, ctx, location) && ret;
	}

	temps.gen_uf_inc_count(pfp->name, 0);

	/* write "return retvar;" (if not void) and close the function */
	temps.gen_uf_tail(pretvar);
	temps.unite_uf_streams();
	return ret;
}

bool RVReUfGen::gen_unitrv_side1_uf( bool seq_equiv_to_cps )
{
	string location(__FUNCTION__);
	bool ret = true;
	int i;
	Decl *decl, *side0_decl;
	bool pointer;
	bool gen_seq_equiv_code = false;
	SymbolVector *vec;
	SymbolVector::const_iterator  it;
	std::ostringstream proto_strm;
	std::ostringstream ret_type_strm;
	const std::string *pretvar = &uf_retvar;
	std::string item_pref;

	current_side = SIDE1;
	m_where = pfp->side_name[1].data();
	gen_seq_equiv_code = seq_equiv_to_cps && pfp->has_cps_in_subtrees();
	item_pref = item_prefix();

	temps.print("\n/*** uninterpreted function side 1: ***/ \n");

	/* gen 1 side func prototype. */
	FunctionType *proto1 = (FunctionType*)(pfp->side_func[1]->decl->form);
	if(!proto1 || proto1->type != TT_Function){
		rv_errstrm << "RVUFGen::gen_side1_uf(): bad prototype for side 1 function: " << pfp->side_name[1] << " .\n";
		return false;
	}
	add_prefix_if_required_side1(pfp, "rvs1_");
	pfp->side_func[1]->decl->print(proto_strm, true, 0);
	CHK_NULL1( ren[1], "ren[1] in RVUFGen::gen_side1_uf()");
	temps.print(ren[1]->convert_ids(proto_strm.str()));
	/* if the function returns void: */
	if( is_basetype(proto1->subType, BT_Void) )
		pretvar = NULL;  /* gen no retvar */
	else {

		pointer = is_pointer(proto1->subType, m_where);
		if( pointer )  /* returns non tokenized pointer: */
			rv_errstrm << "Warning: return value of UF \"" << pfp->side_name[1].data() 
			<< "\" (side 0) is a pointer !\n";

		proto1->subType->printType( ret_type_strm, NULL, true, 0);
	}
	temps.gen_uf_head(ren[1]->convert_ids(ret_type_strm.str()), pretvar);
	//gen_no_aliasing_assertions(proto1);
	/* gen main search and compare loop (according to look_back): */
	unsigned actual_look_back = (gen_seq_equiv_code ? 1 : look_back);
	//temps.gen_uf_search_head(pfp->name, actual_look_back);
	gen_unitrv_uf_search_head(pfp->name, actual_look_back);

	indent = 2;
	first_compare = true; /* the next compare we gen is the first one */
	/* for each input arg/global - compare to saved value:*/
	for(i = 0;i < proto1->nArgs;i++){
		decl = proto1->args[i];
		if(!is_in_arg(i) || !decl || !decl->name)
			continue;
		side0_decl = related_side0_arg(i);

		item_pref = get_unitrv_found_access(side0_decl->name->name);
		string var_prefix = get_variable_prefix(side0_decl->form);
		temps.print("		equal = equal && " + var_prefix + decl->name->name + " == " + item_pref + ";\n");
		first_compare = false;
		/*side0_decl = related_side0_arg(i);
		RVGenCtx ctx(decl->name, side0_decl->form, side0_decl->name->name, item_pref, decl->form, decl->name->name, SIDE1, true, false, m_where, this);
		ret = gen_item_or_struct_op(COMPARE, ctx, location) && ret;*/
	}

	/* for each input global: */
	vec = &pfp->side_func[1]->fnode.read;
	FORVEC(it,(*vec)) {
		if( ignore_in_global(*it, 1) ) continue;
		decl = (*it)->entry->uVarDecl;
		item_pref = get_unitrv_found_access(decl->name->name);
		side0_decl = related_side0_global(decl->name, true);
		RVGenCtx ctx(decl->name,side0_decl->form, side0_decl->name->name, item_pref,
			decl->form, decl->name->name, 
			SIDE1, true, true, m_where, this);
		ret = gen_item_or_struct_op( COMPARE, ctx, location ) && ret;
	}
	if(first_compare)
		/* if no arguments/globals to compare: */
		temps.print("    equal = 1;\n"); /* compare always succeeds. */

	temps.gen_uf_search_tail(gen_unitrv_mark_array_flagging(pfp->name, "1", "rv_uf_ind"));
	/*item_pref = item_prefix();
	string found_item_pref(item_pref);
	found_item_pref.replace(item_pref.find(rv_uf_ind), rv_uf_ind.length(), "found_ind");*/
	ret = gen_unitrv_input_found_case(proto1, vec, pretvar, gen_seq_equiv_code) && ret;

	temps.print("\n  } else {\n\n"); /* no matching input values were found */

	ret = gen_input_not_found_case(proto1, vec, pretvar, gen_seq_equiv_code) && ret;

	temps.print("\n  }\n");
	
	/* write return code and close the function */
	temps.gen_uf_tail(pretvar);


	temps.flush();
}


bool RVUFGen::gen_side1_uf(bool seq_equiv_to_cps)
{
	string location(__FUNCTION__);
	bool ret = true;
	int i;
	Decl *decl, *side0_decl;
	bool pointer;
	bool gen_seq_equiv_code = false;
	SymbolVector *vec;
	SymbolVector::const_iterator  it;
	std::ostringstream proto_strm;
	std::ostringstream ret_type_strm;
	const std::string *pretvar = &uf_retvar;
	std::string item_pref;

	current_side = SIDE1;
	m_where = pfp->side_name[1].data();
	gen_seq_equiv_code = seq_equiv_to_cps && pfp->has_cps_in_subtrees();
	item_pref = item_prefix();

	temps.print("\n/*** uninterpreted function side 1: ***/ \n");

	/* gen 1 side func prototype. */
	FunctionType *proto1 = (FunctionType*)(pfp->side_func[1]->decl->form);
    if(!proto1 || proto1->type != TT_Function){
        rv_errstrm << "RVUFGen::gen_side1_uf(): bad prototype for side 1 function: " << pfp->side_name[1] << " .\n";
        return false;
    }
	add_prefix_if_required_side1(pfp, "rvs1_");
	pfp->side_func[1]->decl->print(proto_strm, true, 0);
    CHK_NULL1( ren[1], "ren[1] in RVUFGen::gen_side1_uf()");
    temps.print(ren[1]->convert_ids(proto_strm.str()));
    /* if the function returns void: */
    if( is_basetype(proto1->subType, BT_Void) )
		pretvar = NULL;  /* gen no retvar */
	else {

		pointer = is_pointer(proto1->subType, m_where);
		if( pointer )  /* returns non tokenized pointer: */
			rv_errstrm << "Warning: return value of UF \"" << pfp->side_name[1].data() 
			<< "\" (side 0) is a pointer !\n";

		proto1->subType->printType( ret_type_strm, NULL, true, 0);
	}
    temps.gen_uf_head(ren[1]->convert_ids(ret_type_strm.str()), pretvar);
    //gen_no_aliasing_assertions(proto1);
    /* gen main search and compare loop (according to look_back): */
    unsigned actual_look_back = (gen_seq_equiv_code ? 1 : look_back);
    temps.gen_uf_search_head(pfp->name, actual_look_back);
    indent = 2;
    first_compare = true; /* the next compare we gen is the first one */
    /* for each input arg/global - compare to saved value:*/
    for(i = 0;i < proto1->nArgs;i++){
        decl = proto1->args[i];
        if(!is_in_arg(i) || !decl || !decl->name)
            continue;

        side0_decl = related_side0_arg(i);
        RVGenCtx ctx(decl->name, side0_decl->form, side0_decl->name->name, item_pref, decl->form, decl->name->name, SIDE1, true, false, m_where, this);
        ret = gen_item_or_struct_op(COMPARE, ctx, location) && ret;
    }
    /* for each input global: */
    vec = &pfp->side_func[1]->fnode.read;
    FORVEC(it,(*vec)) {
		if( ignore_in_global(*it, 1) ) continue;
		decl = (*it)->entry->uVarDecl;
		side0_decl = related_side0_global(decl->name, true);
		RVGenCtx ctx(decl->name,side0_decl->form, side0_decl->name->name, item_pref,
			decl->form, decl->name->name, 
			SIDE1, true, true, m_where, this);
		ret = gen_item_or_struct_op( COMPARE, ctx, location ) && ret;
	}
    if(first_compare)
        /* if no arguments/globals to compare: */
        temps.print("    equal = 1;\n"); /* compare always succeeds. */

    temps.gen_uf_search_tail(get_on_found_action(actual_look_back, item_pref));
    string found_item_pref(item_pref);
    found_item_pref.replace(item_pref.find(rv_uf_ind), rv_uf_ind.length(), "found_ind");

    ret = gen_input_found_case(proto1, found_item_pref, vec, pretvar) && ret;

    temps.print("\n  } else {\n\n"); /* no matching input values were found */

    ret = gen_input_not_found_case(proto1, vec, pretvar, gen_seq_equiv_code) && ret;

    temps.print("\n  }\n");

    temps.gen_uf_inc_count(pfp->name, 1);

    /* write return code and close the function */
    temps.gen_uf_tail(pretvar);

    return true;
}

///<summary>
///Generates part. equiv. code in UF_1 that processes the case when the current input is found at side 0,
///i.e., the code that retrieves the corresponding outputs of side 0 for the current input.
///</summary>
///<param name="proto1">prototype of UF_1 (for retrieving output args)</param>
///<param name="item_pref">the found array element of the inputs at side 0</param>
///<param name="vec">vector of global outputs</param>
///<param name="pretvar">pointer to the name of the generated "retval" variable</param>
///<seealso cref="RVReUfGen::gen_input_found_case"/>
bool RVUFGen::gen_input_found_case(const FunctionType *proto1, const string& item_pref, const SymbolVector *vec, const string *pretvar)
{
	string location(__FUNCTION__);
    int i;
    Decl *decl = NULL, *side0_decl = NULL;
    bool ret = true;
    SymbolVector::const_iterator it;

    /* if input values matching - retrive output values: */
    for(i = 0;i < proto1->nArgs;i++){
        decl = proto1->args[i];
        if(!is_out_arg(i) || !decl || !decl->name)
            continue;

        side0_decl = related_side0_arg(i);
        RVGenCtx ctx(decl->name, side0_decl->form, side0_decl->name->name, item_pref, decl->form, decl->name->name, SIDE1, false, false, m_where, this);
        if(!ctx.check_out_arg(1))
            continue;

        // pointer arg value must be changed in place - dont alloc
        dont_alloc_root = true;
        ret = gen_item_or_struct_op(COPY_S0_to_S1, ctx, location) && ret;
    }
    /* retrive output globals: */
    vec = &pfp->side_func[1]->fnode.written;
    FORVEC(it,(*vec)) {
		decl = (*it)->entry->uVarDecl;
		side0_decl = related_side0_global(decl->name, false);
		RVGenCtx ctx(decl->name, side0_decl->form, side0_decl->name->name, item_pref,
			decl->form, decl->name->name,
			1, false, true, m_where, this);
		ret = gen_item_or_struct_op( COPY_S0_to_S1, ctx, location ) && ret;
	}
    /* retrive return code if exists: */
    if( pretvar ) {
		Type* side0_type = ((FunctionType*)pfp->side_func[1]->decl->form)->subType;
		RVGenCtx ctx((Symbol *) NULL ,side0_type, *pretvar, item_pref,
			proto1->subType, *pretvar,
			1, false, false, m_where, this);
		ret = gen_item_or_struct_op( COPY_S0_to_S1, ctx, location ) && ret;
	}

    return ret;
}

///<summary>
///Generates part. equiv. code in UF_1 that processes the case when the current input is not found at side 0,
///i.e., the code that creates new non-deterministic outputs for the current input.
///</summary>
///<param name="proto1">prototype of UF_1 (for retrieving output args)</param>
///<param name="vec">vector of global outputs</param>
///<param name="pretvar">pointer to the name of the generated "retval" variable</param>
///<param name="gen_seq_equiv_code">flag telling that sequence-equivalent code is being generated</param>
///<seealso cref="RVReUfGen::gen_input_found_case"/>
///<seealso cref="RVReUfGen::gen_input_not_found_case"/>
bool RVUFGen::gen_input_not_found_case(const FunctionType *proto1,
		                               const SymbolVector *vec,
		                               const std::string *pretvar,
		                               bool gen_seq_equiv_code)
{
	string location(__FUNCTION__);
	Decl *decl = NULL;
	bool  ret = true;
	SymbolVector::const_iterator  it;

 	if( gen_seq_equiv_code ) {
		/* <<=== FIN
		- get list of check-points in this func
		- for each check point
		gen nondet vale ndval
		send it to its chanel: RVSAVE(&cp_channel,1,ndval);
		save it in its place in the uf_array.
		*/
		return ret;
	}

    /* gen nondet output values: */
    for(int i = 0;i < proto1->nArgs;i++){
        decl = proto1->args[i];
        if(!is_out_arg(i) || !decl || !decl->name)
            continue;

        RVGenCtx ctx(m_where, false, this);
        ctx.add_lane(decl->name, decl->form, decl->name->name, 1, "");
        if(!ctx.check_out_arg(0))
            continue;

        // pointer arg value must changed in place - dont alloc
        dont_alloc_root = true;
        ret = gen_item_or_struct_op(NONDET, ctx, location) && ret;
    }

    /* nondet output globals: */
    vec = &pfp->side_func[1]->fnode.written;
    FORVEC(it,(*vec)) {
    	decl = (*it)->entry->uVarDecl;
    	RVGenCtx ctx(m_where, false, this);
    	ctx.add_lane(decl->name,decl->form, decl->name->name, 1, SIDE1.get_side_prefix());
    	ret = gen_item_or_struct_op( NONDET, ctx, location ) && ret;
    }

    if( pretvar ) {
    	RVGenCtx ctx(m_where, false, this);
    	ctx.add_lane((Symbol *) NULL,proto1->subType, *pretvar, 1, "");
    	ret = gen_item_or_struct_op( NONDET, ctx, location ) && ret;
    }

    return ret;
}


///<summary>
///Returns the code of the action to be executed in the input search loop of UF_1 when the current input is just found at side 0.
///</summary>
///<param name="look_back_">the depth of the search; it is 1 when sequence equivalence is sought; in this case there the action is executed inside if{} clause</param>
///<param name="item_pref">the found side 0 array element</param>
///<seealso cref="RVReUfGen::get_on_found_action"/>
string RVUFGen::get_on_found_action(unsigned look_back_, const string& item_pref) const {
	return look_back_ == 1 ? "" : "      break;\n";
}



void RVUFGen::gen_one_uf(RVFuncPair *_pfp, bool seq_equiv_to_cps, bool rec_func_uf)
{	
	assert(_pfp);
	pfp = _pfp;
	pfp->unite_argtypes();
	
	gen_one_uf_in_both_sides(seq_equiv_to_cps ,rec_func_uf);

	is_created_mutual_termination_tokens = true;
	
	pfp = NULL;	// needed!
	return;
}


///<summary>
///Generates UFs for both sides for checking their partial equivalence.
///</summary>
///<param name="seq_equiv_to_cps">if true then the input parameter passed to
///                               side 1 will be sought among all the
///                               parameters passed to side 0
///</param>
void RVUFGen::gen_one_uf_in_both_sides(bool seq_equiv_to_cps, bool rec_func_uf)
{



#ifdef CBMC_UF
	static int counter = 0;
	//RVSummarizer sum(pfp);
	gen_side0_cbmc_uf(counter, rec_func_uf); 
	gen_side1_cbmc_uf(counter, rec_func_uf); 
	++counter;
#else
	std::string& name = pfp->name;

	uf_name_list.push_back(name);
	uf_strname[0] = temps.uf_array_name(name) + "[" + temps.uf_count_name(name,0) + "].";
	uf_strname[1] = temps.uf_array_name(name) + "[" + rv_uf_ind + "].";
	gen_uf_array();

	gen_side0_uf();
	gen_side1_uf(seq_equiv_to_cps);

	pfp = NULL;
#endif
}

void RVUFGen::gen_ufs(bool seq_equiv_to_cps)
{
	HashTblIter  it = rv_ufs.get_func_pair_iter(1);
	RVFuncPair*  pfp;
	SymEntry*    item;	
	bool         first = true;

	/* for all RVFuncPairs in RVFuncPairList aufs (automatic) or fufs (forced): */
	for(item = it.begin(); !it.end(); item = it.next()) {
		pfp = (RVFuncPair*)item->u2FunctionDef;
		if (DBG) {
			rv_errstrm << "gen_one_uf(" << pfp->name << ")\n";
			rv_errstrm << "is_needed : " << pfp->is_needed() << " is_uf :" << pfp->is_uf() << "\n";
		}
		assert(pfp->valid_pair());
		if( pfp && pfp->is_uf() ) {
			if (first) {
				temps.print("\n/* Implementations of the uninterpreted functions: */\n");
				first = false;
			}
			gen_one_uf(pfp, seq_equiv_to_cps);
			
			if (get_is_mutual_termination_set()){
				gen_initializing_of_unitrv_mutual_termination_variables_function(pfp);
			}
		}
	}	
}


void RVUFGen::generate_channel_inits()
{
  SymEntry* se;
  HashTblIter hit = m_pSemChecker->accessDirectives().get_channels_iter();
  for(se = hit.begin(); !hit.end(); se = hit.next())
	if( RVDirectives::is_channel(se) )
	  temps.gen_channel_init( se->name );
}


void RVUFGen::generate_channel_compares()
{
  SymEntry* se;
  HashTblIter hit = m_pSemChecker->accessDirectives().get_channels_iter();
  for(se = hit.begin(); !hit.end(); se = hit.next())
	if( RVDirectives::is_channel(se) )
	  temps.gen_channel_compares( se->name );
}


void RVUFGen::generate_aux(void)
{
  temps.print("\n\n");

  // ofer: include an external file with declarations of functions for external input (rv_getint, rv_getchar) instead of generating it each time.
  //rv_temps.gen_input_code();

  temps.print("\n\n");

  /* generate: rv_check() in outstream */
  temps.gen_rv_init_head();
  generate_channel_inits();
  temps.gen_close_func();

  /* generate: rv_check() in outstream */
  temps.gen_rv_check_head();
  generate_channel_compares();
  temps.gen_close_func();
}

void RVUFGen::determineLoopBackDepths(const string& ofpath, RVMain& main, std::string fname) const {
	if (uf_name_list.empty()) return;

	//Pre-compile ofpath and store the result into ofpath#pp.c . 
	string cpp_ofpath = ofpath + "pp.c";
	rv_commands.cpp(ofpath, cpp_ofpath);

	//Read ofpath into memory
	RVTextFileBuffer ofBuf(ofpath);
	if (ofBuf.errorOccurred()) return;

	//Parse the precompiled file
	RVParse parser;
	if( !parser.parse_path(cpp_ofpath, "input for CBMC") ) return;

	//Obtain the global statement of the the parsed file
	Project *pt = parser.take_parsetree();
	RVTypePropIgnoreNondet type_prop;
    if (!type_prop.process_all(pt, RVSide("rv.c")))	return;
	Statement* glob = RVCtool::get_glob_stemnt(pt);
	SymEntry *mainSymEntry1 = RVCtool::lookup_function(RV_SEMCHK0_PREFIX + fname, pt);
	SymEntry *mainSymEntry2 = RVCtool::lookup_function(RV_SEMCHK1_PREFIX + fname, pt);
	SymEntry *mainSymEntry = RVCtool::lookup_function("main", pt);
	
	//Prepare the inter-procedural analysis that counts the maximal call chain for every UF
	RVFuncCallCountAnalysis a(glob, 1);
	list<string>::const_iterator it;
	for (it = uf_name_list.begin(); it != uf_name_list.end(); ++it) {
		a.addCallee(SIDE0.insert_side_ufprefix(*it));
		a.addCallee(SIDE1.insert_side_ufprefix(*it));
		//unsigned c0 = main.countMaxCallChain(SIDE0, NULL, *it);
		//unsigned c1 = main.countMaxCallChain(SIDE1, NULL, *it);
	}

	//Run analysis and process its results:

	if (m_unitrv){
		determineKWithoutMain(a, mainSymEntry1, mainSymEntry2, ofBuf);
	}
	else{
		determineK(a, mainSymEntry, ofBuf);
	}

	

	//Write back the file stored in the memory
	ofBuf.output();

	//Delete the result file of the pre-compilation
	remove(cpp_ofpath.data());
}

bool RVUFGen::determineKWithoutMain( RVFuncCallCountAnalysis& a, SymEntry * const mainSymEntry1, SymEntry * mainSymEntry2, RVTextFileBuffer& ofBuf ) const
{
	bool ret = true;
	list<string>::const_iterator it;
	for (it = uf_name_list.begin(); it != uf_name_list.end(); ++it) {
		unsigned int k = max(
			a.countCalls(mainSymEntry1, SIDE0.insert_side_ufprefix(*it)),
			a.countCalls(mainSymEntry2, SIDE1.insert_side_ufprefix(*it)));
		assert(k > 0 && k < INT_MAX);
		if (k >= temps.get_max_records()) {
			ret = false;
			continue;
		}

		string newDef =
			temps.uf_array_size_name_definition(*it, k, "determined by RVT");
		string oldDef =
			temps.uf_array_size_name_definition(*it, temps.get_max_records());
		ofBuf.replaceInLine(oldDef, newDef);

		m_pSemChecker->set_K(k + 1);
	}
	return ret;
}

bool RVUFGen::determineK(RVFuncCallCountAnalysis& a,
		                 SymEntry* const startFunc,
		     		     RVTextFileBuffer& ofBuf) const
{
	bool ret = true;
	list<string>::const_iterator it;
	for (it = uf_name_list.begin(); it != uf_name_list.end(); ++it) {
		unsigned int k = max(
				a.countCalls(startFunc, SIDE0.insert_side_ufprefix(*it)),
				a.countCalls(startFunc, SIDE1.insert_side_ufprefix(*it)));
		assert(k > 0 && k < INT_MAX);
		if (k >= temps.get_max_records()) {
			ret = false;
			continue;
		}

		string newDef =
				temps.uf_array_size_name_definition(*it, k, "determined by RVT");
		string oldDef =
				temps.uf_array_size_name_definition(*it, temps.get_max_records());
		ofBuf.replaceInLine(oldDef, newDef);

		m_pSemChecker->set_K(k + 1);
	}
	return ret;
}

void RVGenRename::set_unitrv( bool unitrv )
{
	m_unitrv = unitrv;
}
bool RVGenRename::is_variable_declared_globally_for_both_sides(std::string name){
	return (m_apRenTree)[0]->is_variable_declared_globally_for_both_sides(name);
}

void RVGenRename::add_prefix_if_required_side0( RVFuncPair * pfp, std::string prefix )
{
	
	if(pfp->side_func[0]->decl->name->name.substr(0, prefix.size()) == prefix) {
		return;
	}

	pfp->side_func[0]->decl->name->name = prefix + pfp->side_func[0]->decl->name->name;
	return;
}

void RVGenRename::add_prefix_if_required_side1( RVFuncPair * pfp, std::string prefix )
{
	if(pfp->side_func[1]->decl->name->name.substr(0, prefix.size()) == prefix) {
		return;
	}

	pfp->side_func[1]->decl->name->name = prefix + pfp->side_func[1]->decl->name->name;
	return;
}

void RVGenRename::add_prefix_if_required(Decl* d, std::string prefix, int side){
	if(d->name->name.substr(0, prefix.size()) == prefix) {
		return;
	}

	d->name->name = prefix + d->name->name;
	return;
}






/* RVReUfGen code */
/*================*/

RVReUfGen::RVReUfGen(RVTemp& _temps, RVFramaSum& _summarizer_side0, RVFramaSum& _summarizer_side1, bool _seperate_basecase_proof)
  : RVUFGen(_temps, _summarizer_side0, _summarizer_side1, _seperate_basecase_proof)
{
}

///<summary>
///Adds reach_equiv_flag to the UF data array.
///</summary>
///<param name="rNumUfStructItems">a reference to the counter of the data fields</param>
void RVReUfGen::gen_reach_equiv_flag(unsigned &rNumUfStructItems) {
	temps.print("  _Bool reach_equiv_flag;\n");
	++rNumUfStructItems;
}

///<summary>
///Generates part. equiv. code in UF_1 that processes the case when the current input is found at side 0,
///i.e., the code that either retrieves the corresponding outputs of side 0 for the current input if UFs are partially-equivalent,
///or creates new non-deterministic outputs for the current input, respectively otherwise.
///</summary>
///<param name="proto1">prototype of UF_1 (for retrieving output args)</param>
///<param name="item_pref">the found array element of the inputs at side 0</param>
///<param name="vec">vector of global outputs</param>
///<param name="pretvar">pointer to the name of the generated "retval" variable</param>
bool RVReUfGen::gen_input_found_case(const FunctionType * proto1, const string& item_pref, const SymbolVector *vec, const string *pretvar)
{
	assert(pfp != NULL);
	bool ret = false;

	if (pfp->is_equal_semantics()) {
		temps.print("   /* Sides 0 and 1 are partially equivalent.\n"
				    "    * Returning the results of side 0: */\n");
		ret = RVUFGen::gen_input_found_case(proto1, item_pref, vec, pretvar);
	}
	else {
		temps.print("   /* Sides 0 and 1 are not known to be partially equivalent.\n"
				    "    * Returning some results unrelated to the side 0: */\n");
		ret = RVUFGen::gen_input_not_found_case(proto1, vec, pretvar, false);
	}

	return  ret;
}

///<summary>
///Generates part. equiv. code in UF_1 that processes the case when the current input is not found at side 0,
///i.e., the code that forces assertion failure.
///</summary>
///<param name="proto1">prototype of UF_1 (for retrieving output args)</param>
///<param name="vec">vector of global outputs</param>
///<param name="pretvar">pointer to the name of the generated "retval" variable</param>
///<param name="gen_seq_equiv_code">flag telling that sequence-equivalent code is being generated</param>
bool RVReUfGen::gen_input_not_found_case(const FunctionType *proto1,
		                                 const SymbolVector *vec,
		                                 const std::string *pretvar,
		                                 bool gen_seq_equiv_code)
{
	temps.print("    /* Assert reach-equivalence: side 0 and 1 inputs are equal.*/\n");
	temps.print("    assert( 0 );\n");
	return true;
}

///<summary>
///Returns the code of the action to be executed in the input search loop of UF_1 when the current input is just found at side 0.
///</summary>
///<param name="look_back_">the depth of the search; it is 1 when sequence equivalence is sought; in this case there the action is executed inside if{} clause</param>
///<param name="item_pref">the found side 0 array element</param>
///<remark>'break' is intentionally not called to cover a hypothetical case when 2 identical inputs are received</remark>
string RVReUfGen::get_on_found_action(unsigned look_back_, const string& item_pref) const {
	return string("      ") + item_pref + "reach_equiv_flag = 1;\n";
}

void RVReUfGen::generate_channel_inits()
{
}

///<summary>
///Generates the final reach-equivalence checking code.
///</summary>
void RVReUfGen::generate_channel_compares()
{
	temps.get_reach_equivalence_check_start();

	for(list<string>::const_iterator it = uf_name_list.begin(); it != uf_name_list.end(); ++it)
		temps.gen_reach_equiv_over_uf_array(*it);
}

///<summary>
///Generates UFs for both sides for checking reach-equivalence.
///</summary>
///<param name="seq_equiv_to_cps">if true then the input parameter passed to
///                               side 1 will be sought among all the
///                               parameters passed to side 0
///</param>
void RVReUfGen::gen_one_uf_in_both_sides(bool seq_equiv_to_cps)
{
	const std::string& name = pfp->name;

	uf_name_list.push_back(name);
	
	if (m_unitrv){
		//uf_strname[0] = temps.unitrv_uf_array_name(name) + "[" + temps.uf_count_name(name,0) + "].";
		//uf_strname[1] = temps.unitrv_uf_array_name(name) + "[" + rv_uf_ind + "].";
		gen_unitrv_uf_array();
		gen_unitrv_side0_uf();
		gen_unitrv_side1_uf(seq_equiv_to_cps);
	}
	else{
		uf_strname[0] = temps.uf_array_name(name) + "[" + temps.uf_count_name(name,0) + "].";
		uf_strname[1] = temps.uf_array_name(name) + "[" + rv_uf_ind + "].";
		gen_uf_array();
		gen_side0_uf();
		gen_side1_uf(seq_equiv_to_cps);
	}

	
}

void RVReUfGen::gen_unitrv_uf_inc_count( std::string name )
{
	std::string t("	");
	temps.print(t + UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + name + "_count++;");
}

void RVReUfGen::gen_unitrv_uf_search_head( std::string ufname, unsigned look_back )
{
	std::string rv_counter_type = "int";
	stringstream outstreamP;
	(outstreamP) <<
		"  _Bool found = 0;\n" <<
		"  _Bool equal = 1;\n" <<
		"  " << rv_counter_type << " found_ind = -1;\n";

	if( look_back > 1 ) {
		(outstreamP) << 
			"  " << rv_counter_type << " rv_uf_ind = " << get_unitrv_count_var_name(ufname) <<"+"<< look_back-1 <<";\n" <<
			"  " << rv_counter_type << " rv_uf_cnt = 0;\n" <<
			"  if( rv_uf_ind > " << get_unitrv_count_var_name(ufname) <<"-1 )\n" <<
			"    rv_uf_ind = " << get_unitrv_count_var_name(ufname) <<"-1;\n" <<
			"  for(; rv_uf_cnt < " << 2*look_back-1 << " && rv_uf_ind >= 0; ++rv_uf_cnt, ++rv_uf_ind) {\n";

	} else
		if( look_back == 1 ) {
			/* look only at the same index on side 0 (if exists): */
			(outstreamP) << 
				"  " << rv_counter_type << " rv_uf_ind = " << get_unitrv_count_var_name(ufname) <<";\n" <<
				"  if( " << get_unitrv_count_var_name(ufname) << " && rv_uf_ind > " << get_unitrv_count_var_name(ufname) << "-1 )\n" <<
				"    rv_uf_ind = " << get_unitrv_count_var_name(ufname) <<"-1;\n" <<
				"// Make sure that side0 was called at least once \n" <<
				"  if( " << get_unitrv_count_var_name(ufname)  << ")\n" <<
				"  {\n";
		} else
			if( look_back == 0 ) { 
				/* search all values of side 0: */
				(outstreamP) << 
					"  " << rv_counter_type << " rv_uf_ind = " << get_unitrv_count_var_name(ufname) << "-1;\n" <<
					"  for(; rv_uf_ind >= 0; rv_uf_ind--) {\n";
			}

	temps.print(outstreamP.str());
}

std::string RVUFGen::get_unitrv_count_var_name( std::string name )
{
	return UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + name + "_count";
}

std::string RVReUfGen::gen_unitrv_mark_array_flagging( std::string name, std::string side, std::string index_var_name )
{
	
	std::string mark_array_flagging_line= UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + name + "_call_mark_array" + side + "[" + index_var_name +"] = 1;\n";
	return mark_array_flagging_line;
}

void RVReUfGen::print_unitrv_mark_array_flagging( std::string name, std::string side, std::string index_var_name )
{
	std::string mark_array_flagging_line = "	" + gen_unitrv_mark_array_flagging(name, side, index_var_name);
	temps.print(mark_array_flagging_line);
}

bool RVReUfGen::gen_unitrv_input_found_case( FunctionType * proto1, SymbolVector * vec, const std::string* pretvar, bool gen_seq_equiv_code )
{
	assert(pfp != NULL);
	bool ret = false;

	if (pfp->is_equal_semantics()) {
		temps.print("   /* Sides 0 and 1 are partially equivalent.\n"
				    "    * Returning the results of side 0: */\n");

		string location(__FUNCTION__);
		int i;
		Decl *decl = NULL, *side0_decl = NULL;
		bool ret = true;
		SymbolVector::const_iterator it;
		std::string item_pref;

		/* if input values matching - retrive output values: */
		for(i = 0;i < proto1->nArgs;i++){
			decl = proto1->args[i];
			if(!is_out_arg(i) || !decl || !decl->name)
				continue;
			item_pref = get_unitrv_found_access_output(decl->name->name);//unitrv_item_prefix(decl->name->name);
			side0_decl = related_side0_arg(i);
			
			temps.print("	*" + decl->name->name + " = " + item_pref + ";\n");
			//RVGenCtx ctx(decl->name, ((PtrType*)side0_decl->form)->subType, side0_decl->name->name, item_pref, decl->form, decl->name->name, SIDE1, false, false, m_where, this);
			//
			//// pointer arg value must be changed in place - dont alloc
			//dont_alloc_root = true;
			//ret = gen_item_or_struct_op(COPY_S0_to_S1, ctx, location) && ret;
		}
		/* retrive output globals: */
		vec = &pfp->side_func[1]->fnode.written;
		FORVEC(it,(*vec)) {
			decl = (*it)->entry->uVarDecl;
			side0_decl = related_side0_global(decl->name, false);
			//proto1->
			RVGenCtx ctx(decl->name, side0_decl->form, side0_decl->name->name, item_pref,
				decl->form, decl->name->name,
				1, false, true, m_where, this);
			ret = gen_item_or_struct_op( COPY_S0_to_S1, ctx, location ) && ret;
		}
		/* retrive return code if exists: */
		if( pretvar ) {

			FunctionType *proto0 = (FunctionType*)pfp->side_func[1]->decl->form;
			Symbol* retvalsym= new Symbol();
			retvalsym->name = *pretvar;

			Decl* decl = new Decl(retvalsym);
			decl->form = proto0->subType;

			item_pref = get_unitrv_found_access_output(decl->name->name);
			RVGenCtx ctx((Symbol *) NULL ,proto0->subType, *pretvar, item_pref,
				proto1->subType, *pretvar,
				1, false, false, m_where, this);
			ret = gen_item_or_struct_op( COPY_S0_to_S1, ctx, location ) && ret;
		}

		return ret;
	}
	else {
		temps.print("   /* Sides 0 and 1 are not known to be partially equivalent.\n"
				    "    * Returning some results unrelated to the side 0: */\n");


		string location(__FUNCTION__);
		Decl *decl = NULL;
		bool  ret = true;
		SymbolVector::const_iterator  it;

 		if( gen_seq_equiv_code ) {
			/* <<=== FIN
			- get list of check-points in this func
			- for each check point
			gen nondet vale ndval
			send it to its chanel: RVSAVE(&cp_channel,1,ndval);
			save it in its place in the uf_array.
			*/
			return ret;
		}

		/* gen nondet output values: */
		for(int i = 0;i < proto1->nArgs;i++){
			decl = proto1->args[i];
			if(!is_out_arg(i) || !decl || !decl->name)
				continue;

			RVGenCtx ctx(m_where, false, this);
			ctx.add_lane(decl->name, decl->form, decl->name->name, 1, "");
			if(!ctx.check_out_arg(0))
				continue;

			// pointer arg value must changed in place - dont alloc
			dont_alloc_root = true;
			ret = gen_item_or_struct_op(NONDET, ctx, location) && ret;
		}

		/* nondet output globals: */
		vec = &pfp->side_func[1]->fnode.written;
		FORVEC(it,(*vec)) {
    		decl = (*it)->entry->uVarDecl;
    		RVGenCtx ctx(m_where, false, this);
    		ctx.add_lane(decl->name,decl->form, decl->name->name, 1, SIDE1.get_side_prefix());
    		ret = gen_item_or_struct_op( NONDET, ctx, location ) && ret;
		}

		if( pretvar ) {
    		RVGenCtx ctx(m_where, false, this);
    		ctx.add_lane((Symbol *) NULL,proto1->subType, *pretvar, 1, "");
    		ret = gen_item_or_struct_op( NONDET, ctx, location ) && ret;
		}

		return ret;
		}

	return  ret;
}

void RVUFGen::gen_initializing_of_unitrv_mutual_termination_variables_function(RVFuncPair *_pfp){
	pfp = _pfp;
	
	std::string mark_array_side0 = get_mark_array_name(pfp->name, "0");
	std::string mark_array_side1 = get_mark_array_name(pfp->name, "1");
	std::string count_var_name = get_unitrv_count_var_name(pfp->name);
	std::string first_call_flag_var_name = get_first_call_flag_name(pfp->name);

	std::string func_name = "initialize_mutual_termination_tokens_";
	std::string func_name_full =  UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + func_name + pfp->name;
	temps.print("void " + func_name_full + "(){\n");
	
	temps.print("	int rvt_token_i = 0;\n");
	temps.print("		for (rvt_token_i = 0 ; rvt_token_i < " + temps.uf_array_size_name(pfp->name) + " ; rvt_token_i++){\n");
	temps.print("			" + mark_array_side0 + "[rvt_token_i] = 0;\n");
	temps.print("			" + mark_array_side1 + "[rvt_token_i] = 0;\n");
	temps.print("		}\n");
	temps.print("		" + count_var_name + " = 0;\n");
	temps.print("		" + first_call_flag_var_name + " = 0;\n");
	temps.print("\n");
	
	temps.print("}\n");
}

void RVUFGen::gen_initializing_of_unitrv_mutual_termination_variables()
{
	std::string mark_array_side0 = get_mark_array_name(pfp->name, "0");
	std::string mark_array_side1 = get_mark_array_name(pfp->name, "1");
	std::string count_var_name = get_unitrv_count_var_name(pfp->name);
	std::string first_call_flag_var_name = get_first_call_flag_name(pfp->name);

	temps.print("	int rvt_token_i = 0;\n");
	temps.print("	if (" + first_call_flag_var_name + "){\n");
	temps.print("		for (rvt_token_i = 0 ; rvt_token_i < " + temps.uf_array_size_name(pfp->name) + " ; rvt_token_i++){\n");
	temps.print("			" + mark_array_side0 + "[rvt_token_i] = 0;\n");
	temps.print("			" + mark_array_side1 + "[rvt_token_i] = 0;\n");
	temps.print("		}\n");
	temps.print("		" + count_var_name + " = 0;\n");
	temps.print("		" + first_call_flag_var_name + " = 0;\n");
	temps.print("	}\n\n");

}

std::string RVReUfGen::get_mark_array_dereferencing( std::string name, std::string side )
{
	return get_mark_array_name(name, side) + "[" + temps.uf_array_size_name(name) + "];";
}

std::string RVUFGen::get_mark_array_name( std::string name, std::string side )
{
	return UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + name + "_call_mark_array" + side;
}

std::string RVUFGen::get_first_call_flag_name( std::string name )
{
	return UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + name + "_first_call_to_uf_flag";
}

void RVUFGen::print_basecase_flag_update()
{
	stringstream ss;
	ss << "\t" << GLOBAL_BASECASE_FALG_NAME << "++;\n";
	temps.print(ss.str());
}


std::string RVReUfGen::get_count_var_name( std::string name )
{
	return UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + name + "_count";
}

std::string RVReUfGen::get_unitrv_found_access( std::string name )
{
	return UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + pfp->side_name[0] + "_" + name + "[rv_uf_ind]";
}


std::string RVReUfGen::get_unitrv_found_access_output( std::string name )
{
	return UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + pfp->side_name[0] + "_" + name + "_output[rv_uf_ind]";
}



void RVReUfGen::gen_all_output_recording_arrays( FunctionType * proto0, std::string name )
{
	temps.print("\n//Output arrays for local input\n");
	for(int i = 0; i < proto0->nArgs; i++){
		Decl* d = proto0->args[i];
		//gen_uf_item_decl(proto0->args[i], is_in_arg(i), is_out_arg(i), nUfStructItems);
		print_output_array_for_parameter(d, name);
	}

	temps.print("\n//Output arrays for global input\n");
	SymbolVector vec = pfp->side_func[0]->fnode.read;

	SymbolVector::const_iterator  it;
	FORVEC(it,(vec)) {
		if( ignore_in_global(*it, 0) ) continue;
		/* gen code to save its value in UFarr: */
		Decl *d = (*it)->entry->uVarDecl;
		print_output_array_for_parameter(d, name);
	}   
	
	if( !is_basetype(proto0->subType, BT_Void)){
		std::string s = uf_retvar;
		
		Symbol* retvalsym= new Symbol();
		retvalsym->name = s;
		
		Decl* d = new Decl(retvalsym);
		d->form = proto0->subType;

		temps.print("\n//Output array for function output\n");
		print_output_array_for_parameter(d, name);
	}
}

void RVReUfGen::print_output_array_for_parameter( Decl* d, std::string name )
{
	Type* sub;
	if (d->form->type == TT_Pointer){
		sub = ((PtrType*) d->form)->subType;
	}
	else{
		sub = d->form;
	}

	string var_name = UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + name + "_" + d->name->name + "_output[" + temps.uf_array_size_name(name) + "];";
	Symbol* newsym = new Symbol();
	newsym->name = var_name;
	std::ostringstream type_strm;
	sub->printType(type_strm, newsym, true, 0);
	std::string s = type_strm.str();

	temps.print(s + "\n\n");
}

std::string RVReUfGen::unitrv_output_item_prefix( std::string name )
{
	return UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + pfp->side_name[0] + "_" + name + "_output[" + UNITRV_SPECIAL_MUTUAL_TERMINATION_TOKEN + pfp->side_name[0] + "_count]";
}

std::string RVReUfGen::get_variable_prefix( Type * form )
{
	if (form->isBaseType()){
		return "";
	}
	else{
		return "*";
	}

	return "";
}














































/* main() generation code: */
/*=========================*/


RVMainGen::RVMainGen(RVTemp& _temps, Project* _sides[2], const std::string& _main_name)
	: RVGenRename(_temps, _sides), main_name(_main_name)
{
	//adjust_all_functions_to_unitrv(_sides[0]);
	//adjust_all_functions_to_unitrv(_sides[1]);
	
	sides[0] = _sides[0];
	sides[1] = _sides[1];
	arg_prefix[0] = SIDE0.get_side_prefix();
	arg_prefix[1] = SIDE1.get_side_prefix();
	main_pair = NULL;
	has_retvar = false;
	input_assumption = "";
}

bool RVMainGen::is_out_arg(unsigned i)
{
	return (main_pair->get_united_argtype(i) & AT_Out) != 0 ;
}


///<summary>
/// checks if the i-th argument is aggregate (struct/union). Also works if it it a pointer to an aggregate (this is what the is_pointer line does)
/// Seems we can remove the is_pointer() line. It was needed when deref variables were not marked correctly as outputs. ??? !!
///</summary>
bool RVMainGen::is_aggregate_arg(unsigned i)
{
	CHK_NULL1(proto0 && (i < (unsigned)proto0->nArgs) && proto0->args[i],
		"proto0 or its arg in RVMainGen::is_aggregate_arg()");

	Type* realtp = proto0->args[i]->form;
	is_pointer(realtp, m_where, &realtp); 
	realtp = real_type(realtp, m_where);
	return is_basetype(realtp, (BT_Struct|BT_Union));
}

bool RVMainGen::check_mains(bool semchk)
{
	bool ret = true;
	bool print_globals = ((rv_debug_flags & (RV_SECTION | RV_DBG_CALLGRAPH))!= 0);
	Location tmploc(__LINE__, 0, __FILE__);

	m_where = main_name.data();
	current_side = SIDE0;

	main_pair = rv_ufs.lookup(main_name, 0);

	if( !main_pair ) {
		if(DBG) rv_errstrm<<"call new_pair("<<main_name<<")\n";
		/* add new to rv_ufs */
		main_pair = rv_ufs.new_pair(main_name, main_name, main_name, tmploc, RVFuncPair::AUTODETECT);
	}

	/* connect to bodies if not connected yet - checks proto and globals eq: */
	if( main_pair && !main_pair->side_func[0] )
		ret = main_pair->connect2bodies(sides);

	if( !main_pair || !ret ) {
		rv_errstrm << "Error: rv_ufs.new_pair(" << main_name <<",...) or connect2bodies() failed.\n";
		return false;
	}

	/* DFS collect globals */
	globdfs[0].collect( sides[0], main_pair->side_func[0], main_pair->side_name[0], 0);
	globdfs[1].collect( sides[1], main_pair->side_func[1], main_pair->side_name[1], 1);

	if( !globdfs[0].equal_vectors(globdfs[1]) ) {
		rv_errstrm << "Error: The globals used by \""<< main_name <<"\" and its succesors " <<
			"are not the same on both sides.\n";
		print_globals = true;
		ret = false;
	}

	if( print_globals ) {
		rv_errstrm << "All globals accessed by "<< main_name <<" pair and its subtrees:\n";
		globdfs[0].get_read().print("side 0 read globals: ", rv_errstrm);
		globdfs[1].get_read().print("side 1 read globals: ", rv_errstrm);
		globdfs[0].get_written().print("side 0 written globals: ", rv_errstrm);
		globdfs[1].get_written().print("side 1 written globals: ", rv_errstrm);
	}

	if( !ret )
		return false;

	bool allow_ubs = ( ubs_depth > 1 );
	if( semchk && !main_pair->can_compare_semantically(allow_ubs) ) {
		rv_errstrm << "Warning: Can't call with equal arguments to " << main_name << " \n"
			"  because of some unsupported construct(s) in its arguments, used globals or code.\n";
		return false;
	}

	/* try to unite argument types (AT_In/AT_Out ...) from both side funcs: */
	if( !main_pair->has_united_argtypes() && !main_pair->unite_argtypes() )
		return false;

	return true;
}

std::string RVMainGen::get_type_text(Decl* decl, int side)
{
	return get_type_text(decl->form, side);
}

std::string RVMainGen::get_type_text(Type* form, int side)
{
	if( !(side == 0 || side == 1) || !ren[side] )
		fatal_error("Error: RVMainGen::get_type_text() got bad side or"
		" has NULL RVRename for this side !", false); 

	std::ostringstream type_strm;

	form->printType(type_strm, NULL, true, 0);
	return ren[side]->convert_ids(type_strm.str());
}

void RVMainGen::gen_arg_decl()
{
	std::string location(__FUNCTION__);
  /* for each main arg: print its type (without pointer), print its name and ';' */
	for(int i = 0; i < proto0->nArgs; i++) {
		Decl *decl0 = proto0->args[i]->dup();
		Decl *decl1 = proto1->args[i]->dup(); 

		unnamed_arg(decl0, decl1, i, true);	  
		//if( is_out_arg(i) || is_aggregate_arg(i) ) { // note: it refers to any aggregate(struct/union/..) as an output. Probably because it doesn't support checking the individual fields. this should be fixed.
		/* generate two vars: */  // originally, if it was not output variable, then we used only one copy of the variable. This led to various bugs with type names. So we now always use two versions.  
		temps.print("  /* output: */\n");		  

		if(decl0 && decl0->name) {
			current_side = SIDE0;			  
			add_prefix_to_type(arg_prefix[0], decl0->form);			  
			gen_decl(decl0->form, arg_prefix[0], decl0->name, location);			  			  
		}

		if(decl1 && decl1->name) {
			current_side = SIDE1;
			add_prefix_to_type(arg_prefix[1], decl1->form);
			gen_decl(decl1->form, arg_prefix[1], decl1->name, location);			  
		}		  
		// }
		//else if(decl0 && decl0->name) { 
		// current_side = SIDE0; // convert types to side 0 version
		// add_prefix_to_type(arg_prefix[0], decl0->form); // adds prefixes if it is a typedef
		// gen_decl(decl0->form, "", decl0->name);
		//}	

		delete decl0;
		delete decl1;
	} /* for */
  temps.print_array_nondet_decl(); // adds declarations of nondet arrays (these are generated in uf_cbmc of side0)
  temps.reset_array_nondet_decl();
  //return res;
}

void RVMainGen::gen_arg_alloc()
{
	gen_arg_alloc_side(proto0, SIDE0);
	gen_arg_alloc_side(proto1, SIDE1);
}

void RVMainGen::gen_arg_alloc_side(FunctionType *proto, const RVSide& side)
{
	std::string location(__FUNCTION__);
	Decl *decl;
	bool first = true;

	for(int i = 0; i < proto->nArgs; i++) {
		decl = proto->args[i]->dup();
		
		if (m_unitrv){
			std::string prefix = "rvs";
			if (side.index() == 0){
				prefix += "0";
			}
			else{
				prefix += "1";
			}
			prefix += "_";
			add_prefix_if_required(decl, prefix, side.index());
		}
		//is_out = is_out_arg(i);
		RVGenCtx ctx(m_where, 0);
		ctx.set_unitrv(m_unitrv);
		//if( is_out  || is_aggregate_arg(i)) {
		assert(decl && decl->name);
		ctx.add_lane(decl->name,decl->form, decl->name->name, side, arg_prefix[side.index()]);
		/*}
		else {
			if(decl0 && decl0->name) {
				in = true;
				ctx.add_lane(decl0->name, decl0->form, decl0->name->name, 0, "");
			}
		}*/

		assert(ctx.get_width() > 0); //{ // allocating for e.g. ubs-s
		if (first)
			temps.print(string("  /* Allocations for side ") + side.toString() + ": */\n");
		first = false;
		gen_item_or_struct_op(ALLOC, ctx, location, -1); // before May 12, 2012 the passed value for depth was 'ubs_depth + 1', which is inconsistent with the default cases. The reason for 'ubs_depth + 1' stayed unknown.
        delete decl;
	}
}


bool RVMainGen::gen_struct_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth /*=-1*/)
{
	return RVGen::gen_struct_op(op, ctx, ACT_BY, depth);
}

bool RVMainGen::gen_equal_nondet_globals()
{
	std::string location(__FUNCTION__);
	bool ret = true;
	SymbolVector& vec0 = globdfs[0].get_read();
	SymbolVector& vec1 = globdfs[1].get_read();
	Symbol *sym0, *sym1;
	Type *tp0, *tp1;


	/* For each input global: */
	SymbolVector::const_iterator i;
	bool first = true;
	FORVEC(i,vec0) {
		sym0 = (*i);
		assert(sym0 && sym0->entry && sym0->entry->IsVarDecl() && sym0->entry->uVarDecl && (tp0 = sym0->entry->uVarDecl->form)); 				
		if( ignore_in_global(sym0, 0) )	continue; // if this global is not written-to at all in both programs (the entire programs, not just in the current functions), then it is equal to 0. No need to inititizlize to equal non-det.
		if (first) {
			temps.print("\n  /* Begin: Assume globals are equal: */ \n");
			first = false;
		}
		sym1 = vec1.find_related(sym0);
		if( !sym1 ) continue; /* if no related side 1 var - nothing to do. */			
		assert(sym1->entry && sym1->entry->IsVarDecl() && sym1->entry->uVarDecl && (tp1 = sym1->entry->uVarDecl->form));
			
		temps.print("//nondet values for side 0:\n");
		RVGenCtx ctx0(m_where, true);
		ctx0.set_unitrv(m_unitrv);
		ctx0.add_lane(sym0,tp0, sym0->name, SIDE0, arg_prefix[0]);
		ret = gen_item_or_struct_op(NONDET, ctx0, location) && ret;
		temps.print("//alloc for side 1:\n");
		RVGenCtx ctx1(m_where, true);
		ctx1.set_unitrv(m_unitrv);
		ctx1.add_lane(sym1,tp1, sym1->name, SIDE1, arg_prefix[1]);
		ret = gen_item_or_struct_op(ALLOC, ctx1, location) && ret;

		temps.print("//copy leaves from side 0 to 1:\n");
		/* copy sym0 value to sym1 */
		RVGenCtx ctx2(m_where, true);
		ctx2.set_unitrv(m_unitrv);
		ctx2.add_lane(sym0,tp0, sym0->name, 0, arg_prefix[0]);
		ctx2.add_lane(sym1,tp1, sym1->name, 1, arg_prefix[1]);
		ret = gen_item_or_struct_op(COPY_S0_to_S1, ctx2, location) && ret;
		temps.print("//until here\n");
		//dont_alloc_root = false;
		//ret = gen_item_or_struct_op(NONDET_SAVE, ctx2, location) && ret;
	}
	if (first == false) temps.print("\n  /* End: Assume globals are equal: */ \n");

	/* set nondet value to side 1 globals without side 0 counterpart */
	FORVEC(i,vec1) {
		sym1 = (*i);
		assert(sym1 && sym1->entry && sym1->entry->IsVarDecl() && sym1->entry->uVarDecl && (tp1 = sym1->entry->uVarDecl->form));

		if( vec0.find_related(sym1)) continue; /* if has counterpart - we have already done */		
		if( ignore_in_global(sym1, 1))	continue;	

		RVGenCtx ctx1(m_where, true);
		ctx1.add_lane(sym1,tp1, sym1->name, 1, arg_prefix[1]);
		ret = gen_item_or_struct_op(NONDET, ctx1, location) && ret;
	} 
	return ret;
}

bool RVMainGen::gen_main_call(const RVSide& side, bool check_output)
{
	Decl* decl;
	bool first = true;
	std::string retname = uf_retvar + side.toString();
	std::string func_name = main_pair->side_name[side.index()];
	FunctionType *proto;

	switch(side.index()) {
	case 0:  proto = proto0; break;
	case 1:  proto = proto1; break;
	default: proto = NULL;
	}

	current_side = side;

	func_name = std::string(side.get_main_prefix(check_output)) + func_name;

	if( check_output && has_retvar )
		temps.gen_call_head(&retname, func_name);
	else
		temps.gen_call_head(NULL, func_name);

	/* for each arg: print its name (+'&' if poi) +',' */
	for(int i = 0; i < proto->nArgs; i++) {
		std::string arg_text("");
		decl = proto->args[i];

		/* if the decl is like func(void): */
		if(decl && decl->form && is_basetype(decl->form, BT_Void))
			continue;

		if(!decl || !decl->name)
			arg_text = "0";
		else {					
//			if( is_out_arg(i) || is_aggregate_arg(i)) {				
				arg_text = arg_text + arg_prefix[side.index()] + decl->name->name;
			//}
			//else
			//	arg_text = arg_text + proto0->args[i]->name->name; // take side 0 name
		}

		if( !first )
			temps.print(", ");
		temps.print(arg_text); 

		first = false;
	}

	temps.print(");\n");

	return true;
}

///<summary>
/// This function is called twice: once before the calls to the chk functions, and once after
/// in order to check the equivalence of the output arguments. The difference is in the parameter
/// 'before'; This is why the action is 'copy_val' before and 'assert_eq' after.
///</summary>
bool RVMainGen::gen_args_equality(int nItems, Decl **items0, Decl **items1, bool before)
{
	std::string location(__FUNCTION__);
	bool ret = true;	
	ItemOp op = before ? COPY_S1_to_S0 : ASSERT_EQ;
	Decl *decl0, *decl1;
	Type *tp0, *tp1;	
	bool  struct_arg;	

	for(int i = 0; i < nItems; i++) {
		decl0 = items0[i];
		decl1 = items1[i];

		if(!decl0 || !decl1 || !decl0->name || !decl1->name) continue;

		tp0 = decl0->form;
		tp1 = decl1->form;

		bool is_out = before ? 1 : is_out_arg(i);
		RVGenCtx ctx(m_where, !is_out);
		ctx.set_unitrv(m_unitrv);
		ctx.add_lane(decl0->name,tp0, decl0->name->name, 0, arg_prefix[0]);
		ctx.add_lane(decl1->name,tp1, decl1->name->name, 1, arg_prefix[1]);

		struct_arg = ctx.is_aggregate();

		if( struct_arg) {
			ret = gen_struct_op(op, ctx, location) && ret; // just equalize.	
			continue;
		}
		
		if(!is_out) continue;
				
		ret = gen_item_or_struct_op(op, ctx, location) && ret;
	} 
	return ret;
}

bool RVMainGen::gen_globals_check_output()
{
	std::string location(__FUNCTION__);
	bool ret = true;
	SymbolVector& vec0 = globdfs[0].get_written();
	SymbolVector& vec1 = globdfs[1].get_written();
	Symbol *sym0, *sym1;
	Type *tp0, *tp1;

	if( vec0.empty() )
		return ret;

	//temps.print("\n  /* Compare output globals: */ \n");

	/* For each output global: */
	SymbolVector::const_iterator i;
	FORVEC(i,vec0) {
		sym0 = (*i);
		if( !sym0 || !sym0->entry || !sym0->entry->IsVarDecl() ||
			!sym0->entry->uVarDecl || !(tp0 = sym0->entry->uVarDecl->form) ) {
				rv_errstrm <<"Bad side 0 global var (?): \""<<(sym0?sym0->name.data():"UNPRINTABLE")<<"\"\n";
				ret = false;
				continue;
		}
		sym1 = vec1.find_related(sym0);
		if( !sym1 )  /* if no related var - nothing to do. */
			continue;

		if( !sym0->entry || !sym1->entry->IsVarDecl() ||
			!sym1->entry->uVarDecl || !(tp1 = sym1->entry->uVarDecl->form) ) {
				rv_errstrm <<"Bad side 1 global var (?): \""<<(sym1?sym1->name.data():"UNPRINTABLE")<<"\"\n";
				ret = false;
				continue;
		}

		first_compare = true; 
		RVGenCtx ctx(m_where, false);
		ctx.set_unitrv(m_unitrv);
		temps.print("// for asserting global equality:\n");
		ctx.add_lane(sym0,tp0, sym0->name, 0, arg_prefix[0]);
		ctx.add_lane(sym1,tp1, sym1->name, 1, arg_prefix[1]);		
		ret = gen_item_or_struct_op(ASSERT_EQ, ctx, location) && ret;		
	}

	return ret;
}

FunctionType* RVMainGen::get_main_proto(int side)
{
	Type* ret = main_pair->side_func[side]->decl->form;
	if( !ret || !ret->isFunction() ) {
		rv_errstrm <<"Internal: RVMainGen::get_main_proto(): NULL or bad function type, of \""<< 
			main_pair->side_name[side] <<"\" on side "<< side <<" .\n"; 

		return NULL;
	}

	return (FunctionType*)ret;
}

void RVMainGen::gen_main(bool reach_equiv_check, int first_side_to_call)
{	
	std::string location(__FUNCTION__);
	std::string type_text0, type_text1;
	if( !main_pair || !main_pair->side_func[0] || !main_pair->side_func[1] ) fatal_error("Internal: main_pair or its side_func is NULL.\n", false);

	proto0 = get_main_proto(0);
	proto1 = get_main_proto(1);

	
	if( !proto0 || !proto1 )	fatal_error("Internal: can't get prototype(s) of main_pair function(s) :",	m_where, false);

	/* gen main head + 2Xretval */
	if( !is_basetype(proto0->subType, BT_Void) ) {
		type_text0 = get_type_text(proto0->subType, 0);
		type_text1 = get_type_text(proto1->subType, 1);
		temps.gen_retval_declarations(type_text0, type_text1);
		has_retvar = true;
	}
		
	gen_arg_decl();
	temps.print_array_nondet_assign();
	temps.reset_array_nondet_assign();
	gen_arg_alloc();

	if( reach_equiv_check )
		temps.print("\n  rv_init();\n");

	
	temps.print("\n  /* Assume input args are equal: */ \n");
	gen_args_equality(proto0->nArgs, proto0->args, proto1->args, true);	
	// globals should be initialized to nondet because in the real program, 
	// by the time we reached the checked functions (f,f'), the global may have been modified, so the initial value of 0 is not relevant.
	
	gen_equal_nondet_globals(); 	
	temps.flush();
	if (reach_equiv_check) {
		temps.print("\n  /* run each side's main() */\n");
		gen_main_call(0, true);
		gen_main_call(1, true);
		temps.print("\n  rv_check();\n");
		temps.unite_uf_streams();
	}
	else { //There is no need to compare outputs for reach-equivalence
		
		temps.separate_assert_stream(); 

		if( has_retvar ) {
			temps.print("\n  /* Compare return values: */ \n", temps.get_assert_strm());
	
			/* should work OK from simple values, tokens and structs: */
			RVGenCtx ctx(m_where, false);
			ctx.set_unitrv(m_unitrv);
			ctx.add_lane((Symbol *) NULL, proto0->subType, uf_retvar+"0", 0, "");
			ctx.add_lane((Symbol *) NULL, proto1->subType, uf_retvar+"1", 1, "");
			gen_item_or_struct_op(ASSERT_EQ, ctx, location);
		}
		temps.print("\n  /* Compare output args: */ \n", temps.get_assert_strm());		
		gen_args_equality(proto0->nArgs, proto0->args, proto1->args, false);
		gen_globals_check_output();

		temps.print("\n  /* run each side's main() */\n");
		
		temps.print("\n  /* add any pre-computed assumption on the input */\n  ");
		temps.print("__CPROVER_assume(" + input_assumption + ");");
		temps.print("\n");

		gen_main_call(first_side_to_call, true);
		gen_main_call(1 - first_side_to_call, true);

		temps.unite_assert_stream(); // this one subsumes unite_uf_stream();
	}
	
	temps.print("\n  return 0;\n}\n");
}

void RVMainGen::set_input_assumption( const std::string& baseCasePredicate )
{
	input_assumption = baseCasePredicate;
}





/* RVGenRename code */
/*==================*/

RVGenRename::RVGenRename(RVTemp& _temps) :
RVGen(_temps)
{
	ren[0] = ren[1] = NULL;
	m_apRenTree[0] = m_apRenTree[1] = NULL;
}

RVGenRename::RVGenRename(RVTemp& _temps, Project* _sides[2]) :
RVGen(_temps)
{
	RVRenameTree *apRenTree[2] = {NULL, NULL};
	set_rens(_sides, apRenTree);
}

void RVGenRename::init_ren(Project* prj, const RVSide& side)
{
	if( side.isIllegalIndex() )
		fatal_error("Error: RVGenRename::init_ren() got bad side !", false);

	ren[side.index()] = new RVRename(prj, side, true);
}

RVGenRename::~RVGenRename()
{
	for(int i=0; i<2; ++i)
		if(ren[i])
			delete ren[i];
}

void RVGenRename::set_rens(Project* _sides[2], RVRenameTree *apRenTree[2])
{
	init_ren(_sides[0], SIDE0);
	init_ren(_sides[1], SIDE1);
	m_apRenTree[0] = apRenTree[0];
	m_apRenTree[1] = apRenTree[1];
}

std::string RVGenRename::convert_type(std::string type_text, int side)
{
	// if no side is specified for the type assume we use side 0 format.
	if( RVSide(side) == NO_SIDE )
		side = 0;

	if( !(side == 0 || side == 1) || !ren[side] )
		fatal_error("Error: RVGenRename::convert_type() got bad side or"
		" has NULL RVRename for this side !", false);

	return ren[side]->convert_ids(type_text);
}
