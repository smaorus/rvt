#ifndef RV_UNROL_H
#define RV_UNROL_H

#define UNROLLING_VARIABLE_DEFINITION_TITLE "\/\/ Global Unrolling Variable Definition\n"
#define UNROLLING_VARIABLE_DEFINITION_END "\/\/ End of Unrolling Variable Definition\n"
#define UNROLLING_HELPER_DEFINITION_TITLE "\/\/ Unrolling helper function prototypes\n"
#define UNROLLING_HELPER_DEFINITION_END "\/\/ End of unrolling helper function prototypes\n"
#define UNROLLING_HELPER_FUNCTION_START "rv_unroll_helper_"
#define UNROLLING_GLOBAL_VARIABLES_START "\/\/ Global Variables for Unrolling\n"
#define UNROLLING_GLOBAL_VARIABLES_END "\/\/ End of Global Variables for Unrolling\n"
#define GLOBAL_BASECASE_FALG_NAME "rv_unroll_helper_basecase_flag"
#define UF_PREFIX "rvs"
#define CHECK_FUNC_PREFIX "chk"

#include <string.h>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
#include <sstream>
#include "decl.h"

using std::string;
using std::map;
using std::fstream;
using std::stringstream;

class rv_unroller
{
private:
	map<string, int> func_to_appearance_count;
	map<string, Decl*> func_to_decl;
	int unrolling_threshold;
	int side;

	string format_helper_func_name(string func_name, int index);
	void print_func_header( string func_name, int i, stringstream& ss );

public:
	rv_unroller(int unrolling_threshold_in, int side_in);
	rv_unroller(void);
	~rv_unroller(void);

	void add_uf_function_call(string func_name);
	string get_all_unroll_variables();
	string get_all_unroll_helper_func_prototypes();

	
	string get_uf_func_call_unrolling_code(string func_name, int appearance_index);
	string get_unroll_helper_func(string func_name);
	void save_func_decl(Decl* decl);
	string format_parameter_list( string func_name );
	string return_if_non_void( string func_name );
	string get_unroll_base_case_update();
	string get_unroll_basecase_name();
};


#endif