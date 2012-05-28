#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_temps.h>

#include <rv_arrays.h>
#include "rv_genctx.h"
#include <rv_consts.h>
#include "rv_glob.h"
#include "rv_propagate.h"

#include <stdlib.h>
#include <fstream>
#include <sstream>

#ifndef _MSC_VER
	#define _CrtDumpMemoryLeaks()
#endif

// currently debugged together with rv_gen
#define RV_SECTION RV_SEC_GEN

using namespace std;

static const std::string Deref_pref = "*";


/* RVGenCtx code: */
/*================*/

unsigned RVGenCtx::local_var_count = 0;

void RVGenCtx::check_lane(unsigned lane, const char* caller) const {
	check_inited(caller);
	if( lane >= get_width() ) {
		rv_errstrm << "Internal: "<< caller <<": lane "<< lane <<" is out of range.\n"
			"  Current number of lanes is "<< get_width() <<" (in: \""<< where <<"\")\n";
		fatal_error("Bad lane", false);
	}
}

void RVGenCtx::check_inited(const char* caller) const {
	if( get_width() == 0 ) {
		rv_errstrm << "Internal: "<< caller <<" lanes were not inited yet. in: \""<<
		where <<"\"\n";
		fatal_error("RVGenCtx not inited", false);
	}
}

RVGenCtx::RVGenCtx(const char *_where, bool in, const RVGen* pRenamer, const RVSide& side)
  : m_side(side), m_pRenamer(pRenamer)
{
	where = _where;
	input   = in;

	my_parent = NULL;
	my_comp_num = my_item_num = 0;
}

RVGenCtx::RVGenCtx(Symbol *sym,
		           Type* item_tp,
		           const string& item,
		           const string& item_pref,
		           Type* var_tp,
		           const string& var,
		           const RVSide& var_side,
		           bool in, bool global,
		           const char *_where,
		           const RVGen* pRenamer)
  : m_side(var_side), m_pRenamer(pRenamer)
{
	if (DBG)
		if (sym) rv_errstrm << "RVGenCtx_1(" << item << "," << var << "," << sym->name << ")\n";

	init_uf_ctx(sym,item_tp, item, item_pref, var_tp, var, var_side, in, global, _where);
}

RVGenCtx::RVGenCtx(Symbol *sym,
                   Type* side0_tp,
                   const string& side0_name,
                   const string& item_pref,
                   bool in,
                   bool global,
                   const char *_where,
                   const RVGen* pRenamer)
  : m_side(SIDE0), m_pRenamer(pRenamer)
{
	if (DBG)
		if (sym) rv_errstrm << "RVGenCtx_0(" << side0_name <<  "," << sym->name << ")\n";

	/* in case of side0 UF the item name and type is similar to var's ones */
	init_uf_ctx(sym,side0_tp, side0_name, item_pref, side0_tp, side0_name, SIDE0, in, global, _where);
}

void RVGenCtx::init_uf_ctx(Symbol *sym,Type* item_tp, const string& item, const string& item_pref, Type* var_tp, const string& var,	const RVSide& var_side, bool in, bool global, const char *_where)
{
	const char* var_pref = global ? var_side.get_side_prefix() : "";

	where = _where;
	input   = in;

	my_parent = NULL;
	my_comp_num = my_item_num = 0;


	add_lane(sym,item_tp, item, NO_SIDE, item_pref + RVTemp::uf_item_prefix(input));
	add_lane(sym,var_tp, var, var_side, var_pref);
}

Decl* RVGenCtx::find_comp(unsigned lane, unsigned comp_num, unsigned item_num)
{
	CHK_NULL1(my_parent, "RVGenCtx::find_comp()");
	my_parent->check_lane(lane, "RVGenCtx::find_comp()");

	Type* strtype;
	StructDef* str;
	Decl*      comp;
	unsigned   j;

	strtype  = my_parent->get_real_type(lane); 
	str = get_struct_def(strtype, where);

	if( comp_num >= (unsigned)str->nComponents ) {
		rv_errstrm << "Internal: RVGenCtx::find_comp(): comp_num "<< comp_num <<
			" is out of struct range (nComponents = "<< str->nComponents <<") of type: ";
		str->print(rv_errstrm, NULL, 0);
		rv_errstrm << "\n  in: \"" << where <<"\" \n";
		fatal_error("Struct component out of range", false);
	}

	comp = str->components[comp_num];
	for(j = 0; comp && j < item_num; comp = comp->next, j++)
		;

	if( j < item_num ) {
		rv_errstrm << "Internal: RVGenCtx::find_comp(): No item "<< item_num <<
			" in component "<< comp_num <<" of: ";
		str->print(rv_errstrm, NULL, 0);
		rv_errstrm << "\n  in: \"" << where <<"\" \n";
		fatal_error("Struct item number out of range", false);
	}

	if( !comp->name ) {
		rv_errstrm << "RVGenCtx::find_comp(): item "<< item_num <<
			" in component "<< comp_num <<" has no name. in struct: ";
		str->print(rv_errstrm, NULL, 0);
		rv_errstrm << "\n  in: \"" << where <<"\" \n";
		fatal_error("Struct item without name", false);
	}

	return comp;
}

std::string RVGenCtx::expand_name(const std::string& parent_name, Decl* comp, bool is_pointer)
{
	return parent_name + (is_pointer ? "->" :".") + comp->name->name;
}

RVGenCtx* RVGenCtx::cloneCtx(void) const {
    return new RVGenCtx(where, is_input(), m_pRenamer, m_side);
}

auto_ptr<RVGenCtx> RVGenCtx::dup_for_struct_item(unsigned comp_num, unsigned item_num) {
	Decl*      comp;
	std::string name;

	if( !is_aggregate() ) {
		rv_errstrm << "Internal: RVGenCtx::on_struct_item(): attempt to take item <"
			<< comp_num <<","<< item_num << "> in non-struct type: ";
		get_real_type(0)->printType(rv_errstrm, NULL, true, 0);
		fatal_error("\nNon struct item",false);
		return auto_ptr<RVGenCtx>();
	}

	RVGenCtx* clone = cloneCtx();
	clone->my_parent = this;
	clone->my_comp_num = comp_num;
	clone->my_item_num = item_num;

	unsigned width = get_width();
	for(unsigned i = 0; i < width; i++) {
		comp = clone->find_comp(i, comp_num, item_num);

		name = expand_name(get_name(i), comp, is_pointer(i));

		clone->add_lane(comp->name, comp->form, name, get_side(i), get_prefix(i));
	}

	return auto_ptr<RVGenCtx>(clone);
}

auto_ptr<RVGenCtx> RVGenCtx::create_derefed_ctx(void) {
	if( is_aggregate() || !var_is_pointer() ) {
		rv_errstrm << "Internal: RVGenCtx::create_derefed_ctx(): attempt to deref a struct/union "
			" or non-pointer type: ";
		get_real_type(0)->printType(rv_errstrm, NULL, true, 0);
		fatal_error("\nDeref in struct or non-pointer item",false);
		return auto_ptr<RVGenCtx>();
	}

	RVGenCtx* res = cloneCtx();
	res->my_parent = this;
	res->my_comp_num = 0;
	res->my_item_num = 0;

	unsigned width = get_width();
	for(unsigned i = 0; i < width; i++)
		res->add_lane((Symbol *) NULL, get_real_type(i), get_name(i), get_side(i), Deref_pref + get_prefix(i));

	return auto_ptr<RVGenCtx>(res);
}

///<summary>
/// If the context contains a reference, such as p -> a, this will store p -> a in
/// old_full_name and update name to a new variable.
/// (to be completed - what happens with pointer2pointer)
///</summary>

bool RVGenCtx::localize_lanes()
{
	Decl*  comp;
	std::string name_base;
	char buf[11];

	bool is_aggr = is_aggregate();
	bool pointer2pointer = is_pointer2pointer();
	
	unsigned width = get_width();
	for(unsigned i = 0; i < width; i++) {
		Lane& lane = lanes[i];

		if(my_parent && my_parent->is_aggregate()) { // if the lane is p -> a -> b this will result in name_base = "b"; my_parent != NULL means it is not a root in some unbounded structure
			comp = find_comp(i, my_comp_num, my_item_num);
			name_base = comp->name->name; 
		}
		else
			name_base = lane.name;

		lane.old_full_name = lane.pref + lane.name;

		/* if the var is simple type or just the UF argument: */
		if( (!is_aggr && !pointer2pointer) || 
			(i == var_lane() && !my_parent) ) 
		{
			lane.name = lane.old_full_name; // no need of new local name.
			lane.pref = "";
		}    
		else { 
			// gen new local name and prefix:
#ifndef _MSC_VER
			snprintf(buf, sizeof(buf), "%d", ++local_var_count);
#else 
			_snprintf(buf, sizeof(buf), "%d", ++local_var_count);
#endif
			buf[sizeof(buf)-1] = '\0';
			lane.name = name_base + "_" + buf;
			lane.pref = lane.side.toString("s");
		}

		lane.localized = true;
	} /* for */

	return true;
}

void RVGenCtx::add_lane(Symbol *sym, Type* tp, const string& name, const RVSide& side, const string& prefix)
{
	RVTreeComp compare;
	int arr_sz = 0, the_ind;
	bool is_array = false, is_func_ptr = false;
	Symbol *org_sym;
	array_item *the_arr = NULL;

	if( !tp )
		fatal_error((char *)"RVGenCtx::add_lane() received NULL Type. in: ", where, false);

	if (sym && (the_ind = RVGlob::getArrHooks().find_sym(sym , &arr_sz, &org_sym, side)) != -1) {
		is_array = true;
		the_arr  = RVGlob::getArrHooks().get_arr_item(side.index(), the_ind);
	}

	// check whether its a UA:
	RVArrayRef* ua_ref = rv_arrays().get_array_ref(tp);
	if(ua_ref)
		tp = ua_ref->token_type;
	else {
		// use the original type: remove typedef(s):
		Type *origType = tp;
	    tp = real_type(tp, where);
        if (is_basetype(tp, BT_Enum))
            tp = origType;
        else if (isDirectPointerToFunction(tp, NULL)) {
			tp = origType;
			is_func_ptr = true;
		}
	}

	TypeType orig_tt = tp->type;

	if (!is_func_ptr)
		RVCtool::is_pointer(tp, where, &tp); // take item type for pointers and arrays

	if( get_width() != 0 ) {
		/* we must check consistency with previous lanes: */ 
		if( !compare.eq_type(lanes[0].tp, tp) ) {
			rv_errstrm << "RVGenCtx::add_lane(): incompatible lane types in: \""<< where <<"\" :";
			rv_errstrm << "\n  Lane 0 type: ";
			lanes[0].tp->printType(rv_errstrm, NULL, true, 0);
			rv_errstrm << "\n  Lane "<< lanes.size() <<" type: ";
			tp->printType(rv_errstrm, NULL, true, 0);
			fatal_error("\nRVGenCtx: Incompatible lane types", false);
		}
	}
	
	Lane l(tp, orig_tt, name, side, prefix, is_array,arr_sz, the_arr);
	l.ua_ref = ua_ref;
	add_lane(l);
}

void RVGenCtx::add_lane(Lane& l)
{
	lanes.push_back(l);
}

unsigned RVGenCtx::var_lane() const {
	return( get_width() == 1 ? 0 : 1 );
}

bool RVGenCtx::is_pointer(unsigned lane) const {
	check_lane(lane, "RVGenCtx::is_pointer()");
	TypeType tt = lanes[lane].typetype;
	return (tt == TT_Pointer || tt == TT_Array);
}

bool RVGenCtx::var_is_pointer() const {
	return is_pointer(var_lane());
}

bool RVGenCtx::is_array(unsigned lane) const {
	check_lane(lane, "RVGenCtx::is_array()");
	TypeType tt = lanes[lane].typetype;
	return (tt == TT_Array);
}

array_item *RVGenCtx::get_arr_item(unsigned lane) const {
	return lanes[lane].the_arr;
}

bool RVGenCtx::is_new_array(unsigned lane) const {
	return lanes[lane].is_array;
}

int RVGenCtx::new_array_size(unsigned lane) const {
	return lanes[lane].array_size;
}

bool RVGenCtx::is_ua(unsigned lane) const {
	check_lane(lane, "RVGenCtx::is_ua()");
	return(lanes[lane].ua_ref != NULL);
}

bool RVGenCtx::is_aggregate(void) const {
	Type *type = get_real_type(0);
	return is_basetype(type, (BT_Struct|BT_Union));
}

bool RVGenCtx::is_union() const {
	check_inited("RVGenCtx::is_union()");
	Type *type = lanes[0].tp;
	return is_basetype(type, BT_Union);
}

bool RVGenCtx::is_pointer2pointer() const {
	return( var_is_pointer() && 
		RVCtool::is_pointer(get_real_type(var_lane()), where) );
}

unsigned RVGenCtx::get_size() const {
	if( is_aggregate() ) {
		rv_errstrm << "Warning: RVGenCtx::get_size(): current type is struct/union: ";
		lanes[0].tp->printType(rv_errstrm, NULL, true, 0);
		rv_errstrm << " - unknown size \n";
		return 0;
	}
	if (isFuncPtrSubstitution(0))
		return sizeof(void*);

	return sizeof_type(get_real_type(0));
}

bool RVGenCtx::is_long() const {
	return( get_size() == sizeof(long) );
}

Type* RVGenCtx::get_nominal_type(unsigned lane) const {
	check_lane(lane, "RVGenCtx::get_nominal_type()");
	return lanes[lane].tp;
}

Type* RVGenCtx::get_real_type(unsigned lane) const {
	Type *result = NULL;
	isFuncPtrSubstitution(lane, &result);
	return result;
}

bool RVGenCtx::isFuncPtrSubstitution(unsigned lane, Type **ppRealType) const {
	Type *nom_tp = get_nominal_type(lane), *real_tp = real_type(nom_tp, where);
	bool subst = isDirectPointerToFunction(real_tp) && nom_tp != real_tp;
    if (ppRealType != NULL) *ppRealType = subst? nom_tp : real_tp;
    return subst;
}

std::string RVGenCtx::get_print_type(unsigned lane) const {
	Type *print_type = get_nominal_type(lane);
	if (m_pRenamer == NULL || RVTypeProp::isPointerToFunctionSubstitutingType(print_type))
		get_print_type_basic(print_type, NULL);
	const RVSide& side = m_side.isIllegalIndex()? get_side(lane) : m_side;
	return get_print_type_with_side(print_type, side, NULL);
}

string RVGenCtx::get_print_type_with_side(Type *tp,
		                                  const RVSide& side,
		                                  Symbol *sname) const {
	Type* print_type(tp->dup());
	m_pRenamer->add_prefix_to_type(side.get_side_prefix(), print_type);
	return get_print_type_basic(print_type, sname);
	//delete print_type will be a bug here, as every type registers itself in Project, which later deletes it.
}

std::string RVGenCtx::get_print_type_basic(const Type *print_type, Symbol *sname) {
	// if its a BitField (f.e. "int val:2;") - don't print the bit size
	if(print_type->type == TT_BitField)
		print_type = static_cast<const BitFieldType*>(print_type)->subType;
	std::ostringstream type_strm;
	print_type->printType(type_strm, sname, true, 0);
	return type_strm.str();
}

const std::string& RVGenCtx::get_name(unsigned lane) const {
	check_lane(lane, "RVGenCtx::get_name()");
	return lanes[lane].name;
}

std::string  RVGenCtx::get_full_name(unsigned lane) const {
	std::string ret(get_prefix(lane));
	ret += get_name(lane);
	return ret;
}

std::string  RVGenCtx::get_old_full_name(unsigned lane) const {
	check_lane(lane, "RVGenCtx::get_old_full_name()");
	return lanes[lane].old_full_name;
}

const RVSide& RVGenCtx::get_side(unsigned lane) const {
	check_lane(lane, "RVGenCtx::get_side()");
	return lanes[lane].side;
}

std::string RVGenCtx::get_prefix(unsigned lane) const {
	check_lane(lane, "RVGenCtx::get_prefix()");
	return lanes[lane].pref;
}

bool RVGenCtx::is_localized(unsigned lane) const {
	check_lane(lane, "RVGenCtx::is_localized()");
	return lanes[lane].localized;
}

RVArrayRef* RVGenCtx::get_ua_ref(unsigned lane) const {
	check_lane(lane, "RVGenCtx::get_ua_ref()");
	return lanes[lane].ua_ref;
}

bool RVGenCtx::check_out_arg(unsigned lane) const {
	if( is_pointer(lane) )
		return true;

	rv_errstrm << "Warning: output argument \""<< get_name(lane) <<
			      "\" is not a pointer ! in: \""<< where <<"\" \n";
	return false;
}

