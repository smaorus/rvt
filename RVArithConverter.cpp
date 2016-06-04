#include "RVArithConverter.h"


RVArithConverter::RVArithConverter(Project* _tree) : RVWalk(/*decl_to_symbol =*/ true), parsetree(_tree)
{
}


RVArithConverter::~RVArithConverter(void)
{
}

void RVArithConverter::convert_abstract_arithmetics_to_concrete()
{
	Statement* first_st = get_glob_stemnt(parsetree);
	for(Statement* st = first_st; st; st = st->next) {
		if (arithmeticAbstraction(st)){
			Location l(st->location);
			FunctionDef* def1 = new FunctionDef(l);
			def1->decl = ((DeclStemnt*) st)->decls[0]->dup();
			def1->next = st->next;
			st->next = def1;
			
			Symbol* sx  = new Symbol();
			sx->name = "x";
			Symbol* sy  = new Symbol();
			sy->name = "y";
			BinaryExpr* b = new BinaryExpr(BO_Mult, new Variable(sx, l), new Variable(sy, l), l);
			ReturnStemnt* r = new ReturnStemnt(b, l);
			
			def1->head = r;
		}
	}
}

bool RVArithConverter::arithmeticAbstraction( Statement* st )
{
	return (st->isDeclaration() && ((DeclStemnt*) st)->decls[0]->name->name.find("rv_mult") != std::string::npos);
}
