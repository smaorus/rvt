#include "rv_unroller.h"


rv_unroller::rv_unroller(int unrolling_threshold_in, int side_in)
{
	unrolling_threshold = unrolling_threshold_in;
	side = side_in;
}

rv_unroller::rv_unroller(){
	
}

rv_unroller::~rv_unroller(void)
{
}

void rv_unroller::add_uf_function_call(string func_name)
{
	if (func_to_appearance_count.find(func_name) != func_to_appearance_count.end()){
		func_to_appearance_count[func_name]++;
	}
	else{
		func_to_appearance_count[func_name] = 1;
	}
}

string rv_unroller::format_helper_func_name(string func_name, int index){
	stringstream ss;
	ss << UNROLLING_HELPER_FUNCTION_START;
	ss << "side" << side << "_" << index << "_";
	ss << func_name;
	return ss.str();
}

string rv_unroller::get_unroll_helper_func(string func_name){
	
	//I'm assuming that this function is called right after "add_uf_function_call".
	//This is a bad assumption but it is the easiest implementation.
	if (func_to_appearance_count.find(func_name) != func_to_appearance_count.end()){
		return format_helper_func_name(func_name, func_to_appearance_count[func_name]);
	}

	return "";
}

string rv_unroller::get_all_unroll_variables(){
	stringstream ss;

	/*if (side == 0){
		ss << UNROLLING_GLOBAL_VARIABLES_START;
		ss << "int " << GLOBAL_BASECASE_FALG_NAME << " = 0;\n";

		ss << UNROLLING_GLOBAL_VARIABLES_END;
	}*/

	ss << UNROLLING_VARIABLE_DEFINITION_TITLE;
	
	for (map<string,int>::iterator it=func_to_appearance_count.begin(); it!=func_to_appearance_count.end(); ++it){
		for (int i = 0 ; i < it->second ; i++){
			ss << "int rv_unroll_" << it->first << i << "_side" << side << " = 0;\n";
		}
	}

	ss << UNROLLING_VARIABLE_DEFINITION_END;

	return ss.str();
}

string rv_unroller::get_all_unroll_helper_func_prototypes(){
	stringstream ss;
	ss << UNROLLING_HELPER_DEFINITION_TITLE;

	for (map<string,int>::iterator it=func_to_appearance_count.begin(); it!=func_to_appearance_count.end(); ++it){
		for (int i = 0 ; i < it->second ; i++){
			
			print_func_header(it->first, i, ss);

			ss << "{\n" << get_uf_func_call_unrolling_code(it->first, i);
			ss << "}\n";
		}
	}
	
	ss << UNROLLING_HELPER_DEFINITION_END;

	return ss.str();
}

string rv_unroller::get_uf_func_call_unrolling_code(string func_name,  int appearance_index){
	stringstream var_name_stream;
	var_name_stream << "rv_unroll_" << func_name << appearance_index<< "_side" << side;
	string var_name = var_name_stream.str();

	string parameter_list = format_parameter_list(func_name);

	string returnOrEmpty = return_if_non_void(func_name);

	stringstream ss;
	
	ss << "\tif (" <<  var_name << " < " << unrolling_threshold << "){\n";
	ss << "\t\t" << var_name << "++;\n";
	ss << "\t\t" << returnOrEmpty << CHECK_FUNC_PREFIX << side << "_" << func_name << parameter_list << ";\n";
	ss << "\t}";
	ss << "\n\telse " << returnOrEmpty << UF_PREFIX << side <<"_" << func_name << parameter_list << ";\n";

	return ss.str();
}

void rv_unroller::save_func_decl(Decl* decl){
	func_to_decl[decl->name->name] = decl->dup();
}

void rv_unroller::print_func_header( string func_name, int i, stringstream& ss )
{
	string updated_func_name = format_helper_func_name(func_name, i+1);
	Decl* decl = func_to_decl[func_name];
	decl->name->name = updated_func_name;
	decl->print(ss, true, 0);
}

string rv_unroller::format_parameter_list( string func_name )
{
	stringstream ss;

	Decl* decl = func_to_decl[func_name];
	Decl** args = ((FunctionType*)decl->form)->args;
	int nargs = ((FunctionType*)decl->form)->nArgs;

	ss << "(";
	for (int i = 0 ; i < nargs ; i++){
		string s = args[i]->name->name;
		ss << s;
		if (i < nargs - 1){
			ss << ",";
		}
	}
	ss << ")";

	return ss.str();
}

string rv_unroller::return_if_non_void( string func_name )
{
	stringstream s;

	Decl* decl = func_to_decl[func_name];
	FunctionType* t= (FunctionType*)decl->form; 
	
	t->printBase(s, 0);
	string ss = s.str();
	return ss.compare("void") == 0? "" : "return ";
}

string rv_unroller::get_unroll_base_case_update()
{
	//return "";
	stringstream s;
	s <<"\t" << GLOBAL_BASECASE_FALG_NAME;
	s << "++;\n";

	return s.str();
}

string rv_unroller::get_unroll_basecase_name()
{
	return GLOBAL_BASECASE_FALG_NAME;
}
