#pragma once

#include <string>
#include <rv_walk.h>
#include "rv_side.h"
#include "rv_etc.h"
#include "rv_unroller.h"
#include "rv_temps.h"

class RVTextualUnroller :
	public RVWalk
{
public:
	RVTextualUnroller(Project* _tree, bool call_uf = false);
	virtual ~RVTextualUnroller();
	void add_unrolling_functions(const std::string& pair_name, int unrolling_threshold);

	void modifyOriginalFunction( FunctionDef* def, int unrolling_threshold );

	bool matchingStatement( Statement* st, const std::string& pair_name );
	FunctionDef* create_deepest_dup( const FunctionDef* def, const std::string& pair_name );

	void create_uf_deep_func( const std::string& pair_name, const FunctionDef* def, FunctionDef* deep );

	void create_assume_false_deep_func( FunctionDef* deep );

	void print_all( RVTemp& m_temps );
	FunctionDef* create_unrolling_iteration_dup( FunctionDef* def, int i, int unrolling_threshold );

	void adjustFunctionCalls( FunctionDef* unroll_i , int i, int unrolling_threshold, string funcName);
	virtual bool process(Symbol* it);
	bool arithmeticAbstraction( Statement* st );
	std::string extract_uf_function_name( const std::string& pair_name );
private:
	Project* parsetree;

	bool call_uf;

	string curFunc;
	string curPostFix;
	string curFuncUf;
};

