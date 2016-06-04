#include "RVTextualUnroller.h"


RVTextualUnroller::RVTextualUnroller(Project* _tree, bool _call_uf)
: RVWalk(/*decl_to_symbol =*/ true), parsetree(_tree), call_uf(_call_uf){

}


RVTextualUnroller::~RVTextualUnroller(){

}

void RVTextualUnroller::add_unrolling_functions(const std::string& pair_name, int unrolling_threshold)
{
	Statement* first_st = get_glob_stemnt(parsetree);
	for(Statement* st = first_st; st; st = st->next) {
		if(matchingStatement(st, pair_name)){

			FunctionDef* def = (FunctionDef*) st;

			FunctionDef* def1 = create_deepest_dup(def, pair_name);
			def->insertBeforeTransUnit(def1, parsetree->Parse_TOS->transUnit);

			for (int i = unrolling_threshold ; i > 0 ; i--){
				FunctionDef* def2 = create_unrolling_iteration_dup(def, i, unrolling_threshold);
				def->insertBeforeTransUnit(def2, parsetree->Parse_TOS->transUnit);
			}

			modifyOriginalFunction(def, unrolling_threshold);

			break;
		}
	}
}

bool RVTextualUnroller::matchingStatement( Statement* st, const std::string& pair_name )
{
	return st->isFuncDef() && ((FunctionDef*)st)->FunctionName()->name.compare(pair_name) == 0;
}

FunctionDef* RVTextualUnroller::create_deepest_dup( const FunctionDef* def, const std::string& pair_name )
{
	FunctionDef* deep = (FunctionDef*) def->dup();

	if (call_uf){
		create_uf_deep_func(pair_name, def, deep);

	}
	else{
		create_assume_false_deep_func(deep);

	}	
	deep->decl->name->name += "_deepest";
	return deep;

}



FunctionDef* RVTextualUnroller::create_unrolling_iteration_dup( FunctionDef* def, int i, int unrolling_threshold )
{

	string funcName = def->decl->name->name;

	stringstream ss;
	
	FunctionDef* unroll_i = (FunctionDef*) def->dup();
	
	ss << funcName << "_unroll_" << i;
	unroll_i->decl->name->name =  ss.str();
	
	adjustFunctionCalls(unroll_i, i, unrolling_threshold, funcName);
	
	return unroll_i;
}


void RVTextualUnroller::adjustFunctionCalls( FunctionDef* unroll_i, int i, int unrolling_threshold, string funcName )
{
	curFunc = funcName;
	curFuncUf = funcName;
	curFuncUf[0] = 'r';
	curFuncUf[1] = 'v';
	curFuncUf[2] = 's';
	
	
	stringstream ss;
	ss << "_unroll_" << (i+1);

	curPostFix = funcName + (i == unrolling_threshold? "_deepest" : ss.str());
	process_block((Block*) unroll_i);
}

bool RVTextualUnroller::process(Symbol* it){
	if (it->name.compare(curFunc) == 0 || it->name.compare(curFuncUf) == 0){
		it->name = curPostFix;
	}
	return true;
}

void RVTextualUnroller::print_all( RVTemp& m_temps )
{
	Statement* first_st = get_glob_stemnt(parsetree);
	for(Statement* st = first_st; st; st = st->next) {
		st->print(m_temps.get_strm(),0);
		m_temps.print("\n");
	}
}

void RVTextualUnroller::modifyOriginalFunction( FunctionDef* def, int unrolling_threshold )
{
	adjustFunctionCalls(def, 0, unrolling_threshold, def->decl->name->name);
}

std::string RVTextualUnroller::extract_uf_function_name( const std::string& pair_name )
{
	string result = pair_name;
	result[0] = 'r';
	result[1] = 'v';
	result[2] = 's';
	return result;
}

void RVTextualUnroller::create_assume_false_deep_func( FunctionDef* deep )
{
	Symbol* assumeSymbol = new Symbol();
	assumeSymbol->name = "__CPROVER_assume";
	FunctionCall* s  = new FunctionCall(new Variable(assumeSymbol, deep->location), deep->location);
	s->addArg(new IntConstant(0, false, deep->location));

	deep->head = new ExpressionStemnt(s, deep->location);
}

void RVTextualUnroller::create_uf_deep_func( const std::string& pair_name, const FunctionDef* def, FunctionDef* deep )
{
	Symbol* uf_name = new Symbol();
	uf_name->name = extract_uf_function_name(pair_name);
	FunctionCall* fc = new FunctionCall(new Variable(uf_name, def->location), def->location);

	FunctionType* funcType = ((FunctionType*) deep->decl->form);
	for (int i = 0 ; i < funcType->nArgs ; i++){
		Symbol* s = new Symbol();
		s->name = funcType->args[i]->name->name;
		Variable* v = new Variable(s, deep -> location);
		fc->addArg(v);
	}

	if (deep->isVoid()){
		deep->head = new ReturnStemnt(fc, def->location);
	}
	else{
		deep->head = new ExpressionStemnt(fc, def->location);
	}
}





