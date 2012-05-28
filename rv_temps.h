/* Functions to generate func and structs for output */

#ifndef RV_TEMPS_H
#define RV_TEMPS_H

#include <iostream>
#include <fstream>
#include <ctool/express.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "rv_etc.h"
#include "rv_dbg.h"

class array_item;

class RVTemp : public RVIDischargee
{
   std::fstream foutstream;
   RVErrStrm glob_fstream, code_uf_stream, decl_uf_stream, assert_main_stream, protect_null_deref_stream;
   RVErrStrm *outstreamP, *declarationsStreamP, *assertStreamP, *codePartStreamP;
   std::string arr_nondet_decl;
   std::string arr_nondet_assign;

   unsigned max_records;

   public:
     RVTemp(void);
     RVTemp(std::ostream&);
     ~RVTemp();

     bool open(RVDischarger& discharger,
    		   const std::string& filename,
    		   std::ios_base::openmode openmode = std::ios_base::out);
     void close(RVDischarger&);
	 void separate_assert_stream(); // ofer 
	 void unite_assert_stream();
	 void separate_uf_streams(); // ofer
	 void unite_uf_streams(); // ofer
	 void separate_protect_streams(); // ofer
     void gen_assert_proto(void);
	 void include_rv_declarations(); // ofer 
     void gen_cbmc_func_headers();
     void gen_rvt_array_macros();
     void gen_cbmc_array_macros();
     void gen_nondet_arr_sz(int sz);
     void gen_input_code();
     void gen_channel_def();
     void gen_channel(const std::string& channel);
     void gen_RVCHECK();
     void gen_checkpoint(const RVSide& side, const std::string& channel, const std::string& cond, const std::string& val);
     void gen_rv_init_head();
     void gen_channel_init(const std::string& channel);
     void gen_close_func();
     void gen_main_head();
     void gen_retval_declarations(const std::string& ret_type0, const std::string& ret_type1);
     void gen_rv_check_head();
     void gen_channel_compares(const std::string& channel);

     void gen_call_head(const std::string* ret_var, const std::string& func);
     void gen_var_decl(const std::string& type_text, const std::string& var, std::string& by, bool pointer = false);
	 void gen_var_decl_text(const std::string& type_text, std::string& by);
     void gen_alloc(const std::string& var, const std::string& type_text, std::string& by);
	 void gen_safe_alloc(const std::string& var, const std::string& type_text, std::string& by);
	 void gen_local_copy_uf(const std::string& type_text, const std::string& local_name, const std::string& old_name,  std::string& by, bool pointer=false);
//     void gen_local_copy(const std::string& type_text, const std::string& local_name, const std::string& old_name, std::string& by, bool pointer = false);
//     void gen_take_addr(const std::string& pointer_var, const std::string& addr_var);
     void gen_copy_val(const std::string& v0, const std::string& v1, std::string& by, bool pointer = false);
     void gen_assert_eq(const std::string& var0, const std::string& var1, std::string& by, bool pointer = false);
     void gen_assert_neq(const std::string& var0, const std::string& var1, std::string& by, bool pointer = false);
     void gen_eq_null(const std::string& var, std::string& by);
     void gen_nondet_value(const std::string& var, const std::string& type_text, bool pointer, bool is_long, std::string& by);
     void gen_nondet_save_val(const std::string& item, const std::string& var,
			      	  	  	  const std::string& type_text, bool pointer, bool is_long, std::string& by);
     void gen_compare_val(const std::string& item, const std::string& var,
			  	  	  	  bool pointer, bool first, std::string& by);
     void gen_fetch_val(const std::string& item, const std::string& var, bool pointer, std::string& by);
     void gen_nondet_if(std::string& by);
     void gen_if_eq_null(const std::string& var, bool equal, std::string& by);

     void gen_nondet_save_val_arr(const std::string& item, const std::string& var, const std::string& type_text,
				 	 	 	 	  int array_size, bool is_long, const array_item *the_arr, std::string& by);
     void gen_save_val_arr(const std::string& item, const std::string& var, int array_size, const array_item *the_arr, std::string& by);
     void gen_fetch_val_arr(const std::string& item, const std::string& var, int arr_sz, const array_item *the_arr, std::string& by);
     void gen_compare_val_arr(const std::string& item, const std::string& var,  int arr_sz, bool first_compare, const array_item *the_arr, std::string& by);
     void gen_nondet_value_arr(const std::string& var, const std::string& type_text, int arr_sz, bool is_long, const array_item *the_arr, std::string& by);
     void gen_assert_eq_arr(const std::string& var0, const std::string& var, int arr_sz, const array_item *the_arr, std::string& by);
     void gen_memcpy(const std::string& item, const std::string& var, int array_size, std::string& by);
     void gen_memcmp(const std::string& item, const std::string& var, int array_size, std::string& by);

     
     /* For UFs: */
     static std::string uf_array_name(const std::string& ufname);
     static std::string uf_count_name(const std::string& ufname, const RVSide& side);
     static std::string uf_array_size_name(const std::string& ufname);
     static std::string uf_array_size_name_definition(const std::string& ufname,
     		                                          unsigned nRecords,
     		                                          const char *comment = NULL);
     static const char* uf_item_prefix(bool in);

     void gen_uf_struct_head(const std::string& ufname);
     void gen_uf_struct_tail(const std::string& ufname);
     void gen_uf_array(const std::string& ufname);

     void gen_uf_inc_count(const std::string& ufname, int side);
     void gen_uf_head(const std::string& ret_type, const std::string* ret_var);
     void gen_uf_tail(const std::string *retvar);
     void gen_uf_search_head(const std::string& ufname, int look_back);
     void gen_uf_search_tail(const std::string& on_found);
     void gen_uf_side_comment(int side);
     
     /* For UAs: */
     void gen_INIT_UA_STRUCT_macro();
     std::string ua_data_arrays_prefix(const std::string& uaname);
     void gen_ua_data_arrays(const std::string& uaname,
    		 	 	 	 	 const std::string& s0_item_type,
    		 	 	 	 	 const std::string& s1_item_type);
     void gen_ua_struct_def(const std::string& uaname,
    		 	 	 	 	const std::string& s0_item_type,
    		 	 	 	    const std::string& s1_item_type);
     void gen_ua_new_array_func(const std::string& uaname, bool decls_only);
     void gen_ua_init_func(const std::string& uaname, int side, bool decls_only);
     void gen_ua_clear_func(const std::string& uaname, int side, bool decls_only);
     void gen_ua_val_func(const std::string& uaname, const std::string& item_type, int side, bool decls_only);
     void gen_ua_s0_ind_func_head(const std::string& uaname, int look_back, bool decls_only);
     void gen_ua_s0_ind_func_tail(void);
     void gen_ua_s1_ind_func_head(const std::string& uaname, int look_back, bool decls_only);
     void gen_ua_s1_ind_func_tail(void);
     void gen_ua_access_macro(const std::string& func_name, const std::string& uaname, int size);
     void gen_ua_unary_func(UnaryOp op, const std::string& func_name, const std::string& uaname, bool decls_only);
     void gen_ua_binary_func(BinaryOp op, const std::string& func_name, const std::string& uaname, bool decls_only);
     void gen_ua_assign_func(AssignOp op, const std::string& func_name, const std::string& uaname, bool decls_only);
     void gen_ua_rel_func(RelOp op, const std::string& func_name, const std::string& uaname, bool decls_only);
     void gen_ua_assert_eq_head(const std::string& uaname, bool decls_only);
     void gen_ua_assert_eq_middle(void);
     void gen_nondet_ua_value(const std::string& uaname, const std::string& var,
                              bool pointer, const RVSide& side, bool set_eq);
     void gen_ua_assert_eq(const std::string& uaname, const std::string& var, bool pointer = false);
     void gen_ua_new_array_call(const std::string& uaname, const std::string& var, bool pointer, bool set_eq);
     void get_reach_equivalence_check_start(void);
     void gen_reach_equiv_over_uf_array(const std::string& ufname);

     /* general funcs: */
	 
     void do_indent(int indent);

     void print(const std::string& str);
	 void print(const std::string& str, RVErrStrm& strm);
     void flush(void);
     RVErrStrm& get_strm() { return *outstreamP; }
	 RVErrStrm& get_assert_strm() { return *assertStreamP; }
	 void set_max_records(unsigned _num) { max_records = _num; }
     unsigned get_max_records() { return max_records; } 

     static const char* RV_CHANNEL_UT;
     static const char* RV_CHANNEL_TAG;

     static const char* NULL_TEXT;

	 void add_array_nondet_decl(std::string s) {arr_nondet_decl.append(s);}
	 void reset_array_nondet_decl() {arr_nondet_decl.clear();}
	 void add_array_nondet_assign(std::string s) {arr_nondet_assign.append(s);}
	 void reset_array_nondet_assign() {arr_nondet_assign.clear();}
	 void print_array_nondet_decl(){print(arr_nondet_decl);}
	 void print_array_nondet_assign(){print(arr_nondet_assign);};

	 //Interface RVIDischargee:
	 virtual void discharge(RVDischarger&);
};

/* standard name for vars that return values from generated functions: */
extern const std::string uf_retvar;

#endif /* RV_TEMPS_h */
