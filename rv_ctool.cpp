#include <rv_error.h>
#include <rv_consts.h>
#include <rv_macros.h>
#include <rv_ctool.h>

#include <ctool/lexer.h>
#include <ctool/decl.h>
#include <ctool/stemnt.h>

#define RV_SECTION 0

FunctionType* RVCtool::current_func0;
FunctionType* RVCtool::current_func1;

void RVCtool::adjust_all_functions_to_unitrv(Project* parsetree, int side, std::vector<std::string>* uf_names)
{
	Statement* first_st = get_glob_stemnt(parsetree);
	for(Statement* st = first_st; st; st = st->next) {
		if( (st->isFuncDef()) )
		{ 
			adjust_function_to_unitrv((FunctionDef*) st, first_st, side, uf_names);
		}
	}
}

void RVCtool::adjust_function_to_unitrv( FunctionDef* st, Statement* global_statement, int side, std::vector<std::string>* uf_names) 
{
	// What about situations where one side might have and rvget\malloc but the other side doesn't? We will have functions 
	// with a different parameter list.
	transform_rvget_to_function_parameters(st, global_statement);
	//transform_malloc_to_function_parameters(st, global_statement);
	add_cprover_not_null_assume(st);
	
}

void RVCtool::transform_malloc_to_function_parameters( FunctionDef* st, Statement* global_statement )
{
	int* rv_get_index = new int();
	Block* block = (Block*) st;
	*rv_get_index = 0;
	for (Statement *statement = block->head; statement; statement = statement->next)
	{
		if (statement->statementContainsBlock()){
			std::vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				transform_malloc_to_function_parameters(st, global_statement);
			}
		}
		else if (statement -> type == ST_ExpressionStemnt){
			ExpressionStemnt* exprStemnt = (ExpressionStemnt*) statement;
			Expression* expr = exprStemnt->expression;
			//if (expr_is_malloc_init(expr)){
			//	//BaseTypeSpec rv_get_type = get_rv_get_type(expr);
			//	//exprStemnt->expression = create_new_parameter(st, rv_get_index, rv_get_type, global_statement);
			//}
			//else{
			//	look_for_rv_get_call_in_expression_and_replace(st, expr, rv_get_index, global_statement);
			//}
		}
	}
}

void RVCtool::add_first_call_flag_initialization( FunctionDef* st, std::vector<std::string>* uf_names)
{
	for (unsigned int i = 0 ; i < uf_names->size() ; i++){
		Symbol* s = new Symbol();
		s->name = (*uf_names)[i];
		Variable* flag_name = new Variable(s, st->location);
		IntConstant* const_flag_value = new IntConstant(1, false, st->location);
		BinaryExpr* b = new AssignExpr(AO_Equal, flag_name, const_flag_value, st->location);
		ExpressionStemnt* ex = new ExpressionStemnt(b, st->location);
		st->head->insertBefore(ex, st);
	}
}


void RVCtool::transform_rvget_to_function_parameters( FunctionDef* st, Statement* global_statement  ) 
{
	replace_rv_get_calls(st, (Block*) st, global_statement);
}

void RVCtool::replace_rv_get_calls( FunctionDef* st, Block* block, Statement* global_statement ) 
{
	int* rv_get_index = new int();
	*rv_get_index = 0;
	for (Statement *statement = block->head; statement; statement = statement->next)
	{
		if (statement->statementContainsBlock()){
			std::vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				replace_rv_get_calls(st, b->at(i), global_statement);
			}
		}
		else if (statement -> type == ST_ExpressionStemnt){
			ExpressionStemnt* exprStemnt = (ExpressionStemnt*) statement;
			Expression* expr = exprStemnt->expression;
			if (expr_is_rv_get_call(expr)){
				BaseTypeSpec rv_get_type = get_rv_get_type(expr);
				exprStemnt->expression = create_new_parameter(st, rv_get_index, rv_get_type, global_statement);
			}
			else{
				look_for_rv_get_call_in_expression_and_replace(st, expr, rv_get_index, global_statement);
			}
		}
	}

}

void RVCtool::look_for_rv_get_call_in_expression_and_replace(FunctionDef* st, Expression* parentExpr, int* rv_get_index, Statement* global_statement) 
{
	std::vector<Expression*>* subExpressions = parentExpr->getSubExpressions();

	for (unsigned int i = 0 ; i < subExpressions->size() ; i++){
		Expression* expr = subExpressions->at(i);
		if (expr_is_rv_get_call(expr)){
			BaseTypeSpec rv_get_type = get_rv_get_type(expr);
			Variable* replacement = create_new_parameter(st, rv_get_index, rv_get_type, global_statement);
			parentExpr->replaceSubExpression(expr, replacement);
		}
		else{
			look_for_rv_get_call_in_expression_and_replace(st, expr, rv_get_index, global_statement);
		}
	}

}

Variable* RVCtool::create_new_parameter( FunctionDef* st, int* rv_get_index, BaseTypeSpec rv_get_type, Statement* global_statement) 
{
	Decl* d = create_new_declaration(rv_get_index, rv_get_type);
	((FunctionType*)st->decl->form)->addArg(d);

	Decl* headerd = create_new_declaration(rv_get_index, rv_get_type);
	update_declaration(headerd, st->decl->name->name, global_statement);

	Decl* vard = create_new_declaration(rv_get_index, rv_get_type);

	(*rv_get_index)++;

	return new Variable(vard->name, st->location);
}

void RVCtool::update_declaration(Decl* headerd, std::string funcName, Statement* global_statement) 
{
	for(Statement* st = global_statement; st; st = st->next) {
		if( (st->isDeclaration()) )
		{
			DeclStemnt* decl = (DeclStemnt*) st;
			std::string declFuncName = decl->decls.at(0)->name->name;
			if (declFuncName == funcName){
				((FunctionType*) decl->decls.at(0)->form)->addArg(headerd);
			}
		}
	}
}


bool RVCtool::expr_is_rv_get_call( Expression* expr ) 
{
	if (expr->etype == ET_FunctionCall){
		FunctionCall* funcCallExpr = (FunctionCall*) expr;
		Variable* v = (Variable*) funcCallExpr->function;
		std::string funcName = v->name->name;
		return func_is_rv_get(funcName);
	}
	else{
		return false;
	}
} 

bool RVCtool::func_is_rv_get( std::string funcName ) 
{
	return funcName == "rvs0_rv_getint" || funcName == "rvs1_rv_getint" || funcName == "rvs0_rv_getchar" || funcName == "rvs1_rv_getchar";
}


void RVCtool::add_cprover_not_null_assume( FunctionDef* st ) 
{
	std::vector<std::string>* pointerParameters = get_pointer_parameters(st);

	for (unsigned int i = 0 ; i < pointerParameters->size() ; i++){
		add_cprover_assume_for_parameter(st, pointerParameters->at(i));
	}
}


void RVCtool::add_cprover_assume_for_parameter( FunctionDef* st, std::string parameterName) 
{
	std::string funcName = "__CPROVER_assume";
	Symbol* symbolFuncName = new Symbol();
	symbolFuncName -> name = funcName;
	Variable* funcNameVar = new Variable(symbolFuncName, st->location);

	Symbol* symbol = new Symbol();
	symbol -> name = parameterName;
	Variable* param = new Variable(symbol, st->location);
	IntConstant* zero = new IntConstant(0, false, st->location);

	RelExpr* paramNotNull = new RelExpr(RO_NotEqual, param, zero, st->location);
	FunctionCall* funcCallExpr = new FunctionCall(funcNameVar, st->location);
	funcCallExpr->addArg(paramNotNull);



	ExpressionStemnt* funcCallStatmenet = new ExpressionStemnt(funcCallExpr, st->location);

	Statement* head = st->head;
	head->insertBefore(funcCallStatmenet, st);
}

std::vector<std::string>* RVCtool::get_pointer_parameters( FunctionDef* st )
{
	std::vector<std::string>* result = new std::vector<std::string>();

	FunctionType* type = (FunctionType*) st->decl->form;
	Decl* decl;
	for (int i = 0 ; i < type -> nArgs ; i++){
		decl = type->args[i];
		if (decl->form->isPointer()){ // maybe I should also check if its array..
			result->push_back(decl->name->name);
		}
	}
	return result;
}

BaseTypeSpec RVCtool::get_rv_get_type( Expression* expr ) 
{
	FunctionCall* funcCallExpr = (FunctionCall*) expr;
	Variable* v = (Variable*) funcCallExpr->function;
	std::string funcName = v->name->name;
	if (funcName == "rvs0_rv_getint" || funcName == "rvs1_rv_getint"){
		return BT_Int;
	}
	else
		return BT_Char;

}


Decl* RVCtool::create_new_declaration( int* rv_get_index, BaseTypeSpec rv_get_type ) 
{
	Decl* d = new Decl();

	std::ostringstream convert;
	convert<<"rv_get"<<*rv_get_index;
	std::string newParamName = convert.str();

	d->name = new Symbol();
	d->name->name = newParamName;
	d->form = new BaseType(rv_get_type);

	return d;
}






int RVCtool::get_funcdef_parameter_index(Symbol* name, FunctionType* current_func){
	if (current_func == NULL){
		return -1;
	}

	Decl **args = current_func-> args;
	int nArgs = current_func -> nArgs;

	for (int i = 0 ; i < nArgs ; i++){
		Decl *argument = args[i];
		if (argument -> name-> name == name -> name){
			return i;
		}
	}

	return -1;
}

bool RVCtool::is_unary_change(UnaryExpr *exp) 
{
    if (exp->uOp == UO_PreInc ||
            exp->uOp == UO_PreDec ||
            exp->uOp == UO_PostInc ||
            exp->uOp == UO_PostDec) return true;
    return false;
}


bool RVCtool::is_top_level(const SymEntry *se)
{
  if( !se || !se->scope ) return false;

  if( se->IsParamDecl() || se->IsComponentDecl() || se->IsLabelDecl() )
	return false;

  return(se->scope->level == FILE_SCOPE ||
		 se->scope->level == EXTERN_SCOPE );
}


ScopeTbl* RVCtool::get_root_scope(Project* pt, SymEntryType entry_type /* = VarDeclEntry */)
{
  Context*  ctx = NULL;
  ScopeTbl* top = NULL;
  if( pt && pt->Parse_TOS && pt->Parse_TOS->transUnit )
	ctx = &(pt->Parse_TOS->transUnit->contxt);

  switch( entry_type )
  {
	case TypedefEntry:
	case VarDeclEntry:          // variable declaration.
	case FctDeclEntry:
	  if( ctx && ctx->syms )
	top = ctx->syms->root;
	  break;
	  
	case LabelEntry:            // label definition.
	  if( ctx && ctx->labels )
	top = ctx->labels->root;
	  break;
	  
	case TagEntry:              // struct/union/enum tags
	  if( ctx && ctx->tags )
	top = ctx->tags->root;
	  break;
	  
	case VarFctDeclEntry:
	case ParamDeclEntry:        // parameter declaration.
	case EnumConstEntry:        // enum constant.
	case ComponentEntry:        // components of a struct/union.
	  rv_errstrm << "Internal: RVCtool::get_root_scope() SymEntries of entry_type "
		 << entry_type <<" can't be at the file scope.\n";
	  fatal_error("Bad entry_type in get_root_scope()", false);
	  return NULL;
  }

  return top;
}
	

ScopeTbl* RVCtool::get_file_scope(Project* pt, SymEntryType entry_type /* = VarDeclEntry */,
				  bool exit_on_error /* = true */)
{
  ScopeTbl* top = get_root_scope(pt, entry_type);

  if(!top || top->nchild < 1 || !top->children || !top->children[0] ) {
	if( exit_on_error ) {
	  rv_errstrm <<"Internal: RVCtool::get_file_scope() of entry_type "<< entry_type 
		 <<" : NULL in path to file scope!\n";
	  fatal_error("RVCtool::get_file_scope() - NULL in path to file scope!\n", false);
	}
	return NULL;
  }

  return top->children[0];
}


ScopeTbl* RVCtool::get_file_tags(Project* pt)
{
  return get_file_scope(pt, TagEntry, false);
}


bool RVCtool::is_global_decl( SymEntry *se )
{
  if( !se || !is_top_level(se) )
	return false;

  // check if it one of the possible global decl types:
  if( !se->IsTypeDef() && !se->IsVarDecl() && 
	  !se->IsFctDecl() && !se->IsVarFctDecl() )
	return false;

  Decl* decl = se->uVarDecl;
  if( !decl || !decl->form )
	return false;

  return true;
}

bool RVCtool::is_static_var( SymEntry *se ) {
  if( !se || !se->IsVarDecl() ) 
	return false;

  Decl* decl = se->uVarDecl;

  return decl->isStatic();
}

bool RVCtool::is_global_var( SymEntry *se )
{
  if( !se || !se->IsVarDecl() || !is_top_level(se) ) 
	return false;
  Decl* decl = se->uVarDecl;

  if( !decl || !decl->form )
	return false;

  return true;
}

bool RVCtool::is_function(const SymEntry *se )
{
  if( !se || !se->IsFctDecl() || !is_top_level(se) ) 
	return false;

  Decl* decl  = se->uVarDecl;
  if( !decl || !decl->form || !decl->form->isFunction() )
	return false;

  return true;
}

bool RVCtool::valid_function(const SymEntry *se ) 
  // has FunctionDef (not necessary a body)
{
  if( !is_function(se) )
	return false;
  
  if( !se->u2FunctionDef || !se->u2FunctionDef->isFuncDef() ||
	  !se->uVarDecl || !se->u2FunctionDef->decl )
	return false;

  return true;
}

bool RVCtool::function_has_body( SymEntry *se )
{
  if( !valid_function(se) )
	return false;

  FunctionDef* def = se->u2FunctionDef;
  if( def->fnode.has_body() )
	return true;

  if( def->head || def->tail )
	rv_errstrm << "Internal warning: function "<< se->name <<
	  "is marked 'external' but contains statements.\n";

  return false;
}

bool RVCtool::is_static_var( Symbol *sym )
{ return( sym ? is_static_var(sym->entry) : false); }

bool RVCtool::is_global_var( Symbol *sym )
{ return( sym ? is_global_var(sym->entry) : false); }

bool RVCtool::is_function(const Symbol *sym )
{ return( sym ? is_function(sym->entry) : false); }

bool RVCtool::valid_function(const Symbol *sym )
{ return( sym ? valid_function(sym->entry) : false); }

bool RVCtool::function_has_body( Symbol *sym )
{ return( sym ? function_has_body(sym->entry) : false); }


SymEntry* RVCtool::lookup_global_var(const std::string& name, Project *pt )
{
  ScopeTbl* fs = get_file_scope( pt );
  SymEntry* se = fs->Lookup( name );

  if( !is_global_var( se ) )
	return NULL;

  return se;
} 


SymEntry* RVCtool::lookup_function(const std::string& name, Project *pt )
{
  ScopeTbl* fs = get_file_scope( pt );
  SymEntry* se = fs->Find( name );

  if( !se || !is_function(se) )
	return NULL;

  return se;
}

///<summary>
/// open the UserType(s) to find the base type definition
///</summary>
Type* RVCtool::real_type(const Type *tp, const char *where)
{
  if( !tp ) { 
	fatal_error( "RVCtool::real_type() received NULL type. in: ",
				(where ? where : "UNKNOWN"), false);
    return NULL; 
  }

  if( tp->isBaseType() && (static_cast<const BaseType*>(tp)->typemask & BT_UserType) ) {

	Symbol *name = static_cast<const BaseType*>(tp)->typeName;
	if( !name || !name->entry || !name->entry->uVarDecl )
	  fatal_error( "RVCtool::real_type() received NULL in UserType definition. in: ",
				  (where ? where : "UNKNOWN"), false);

	return real_type( get_symbol_type(name, where), where);
  }

  return const_cast<Type*>(tp);
}

bool RVCtool::is_pointer(const Type *tp, const char *where, Type **ret_subType /*= NULL*/ )
  /* returns the subtype in ret_subType if != NULL */
{
  tp = real_type(tp, where);

  switch( tp->type )
  {
	case TT_Pointer:
	  if( ret_subType )
	    *ret_subType = static_cast<const PtrType*>(tp)->subType;
	  return true;

	case TT_Array:
	  if( ret_subType )
	    *ret_subType = static_cast<const ArrayType*>(tp)->subType;
	  return true;

	default:
	  return false;
  }
}

static Type *unroll_one_ptr_level(Type *tp) {
	Type *tmp_tp = tp;

	switch( tmp_tp->type )
	{
		case TT_Pointer:
		   tmp_tp = ((PtrType*)tmp_tp)->subType;
		   break;
		case TT_Array:
		   tmp_tp = ((ArrayType*)tmp_tp)->subType;
		   break;
		default:
		   break;
	}

	return tmp_tp;
}


BaseType *RVCtool::get_ptr_base(Type *tp)
{
	Type *tmp_tp = tp;

	while (tmp_tp && ((tmp_tp->type == TT_Pointer) || (tmp_tp->type == TT_Array)))
		tmp_tp = unroll_one_ptr_level(tmp_tp);

	return tmp_tp && tmp_tp->isBaseType()? static_cast<BaseType*>(tmp_tp) : NULL;
}

bool RVCtool::is_pointer2pointer(const Type *tp) {
	const char *where_ = "RVCtool::is_pointer2pointer";
	Type *subType = NULL;
	return is_pointer(tp, where_, &subType)? is_pointer(subType, where_, NULL)
			                               : false;
}

bool RVCtool::is_basetype(const Type *tp, BaseTypeSpec specific /*= BT_BaseMask*/)
{
  if( !tp || !tp->isBaseType() )
	return false;
  return( (static_cast<const BaseType*>(tp)->typemask & specific) != 0 );
}


bool RVCtool::is_const_null(const Expression* exp)
{
  CHK_NULL1(exp, "exp in RVCtool::is_const_null()");
  if( exp->etype == ET_CastExpr )
	exp = static_cast<const CastExpr*>(exp)->expr;

  if( exp && exp->etype == ET_Constant ) {
	const Constant* con = static_cast<const Constant*>(exp);
	switch( con->ctype ) {
	  case CT_Char: return static_cast<const CharConstant*>(con)->ch == 0;
	  case CT_Int:  return static_cast<const IntConstant*>(con)->lng == 0;
	  case CT_UInt: return static_cast<const UIntConstant*>(con)->ulng == 0;
	  default:;
	}    
  }
  return false;
}


BaseTypeSpec RVCtool::fix_int_mask(BaseTypeSpec mask)
{
  /* fix unsigned/signed omitted BT_Int: */
  if( mask == BT_UnSigned || mask == BT_Signed )
	return(mask | BT_Int);

  /* if the type is enum or no type is provided - assume unsigned int (C convention) */
  if( mask == BT_NoType || mask & BT_Enum )
	return(BT_STD_INT);

  return mask;
}

  
int RVCtool::sizeof_base_type(BaseTypeSpec typemask)
{
  enum nothing { NOTHING };

  if( typemask & BT_NoType ) return 0;
  if( typemask & BT_Void   ) return 0;
  if( typemask & BT_Bool   ) return sizeof(bool);
  if( typemask & BT_Char   ) return sizeof(char);
  if( typemask & BT_Short  ) return sizeof(short);
  if( typemask & BT_Int    ) return sizeof(int);
  if( typemask & BT_Int64  ) return 8;
  if( typemask & BT_Int32  ) return 4;
  if( typemask & BT_Int16  ) return 2;
  if( typemask & BT_Int8   ) return 1;
  if( typemask & BT_Long   ) return sizeof(long);
  if( typemask & BT_LongLong) return sizeof(long long);
  if( typemask & BT_Float  ) return sizeof(float);
  if( typemask & BT_Double ) return sizeof(double);
  if( typemask & BT_Ellipsis) return 0;
  if( typemask & BT_Enum   ) return sizeof(enum nothing);

  /* sometimes the ints come without the BT_Int mask: */ 
  if( typemask & BT_Signed ) return sizeof(signed);
  if( typemask & BT_UnSigned) return sizeof(unsigned);

  rv_errstrm << "Error: a call to sizeof_base_type() on non-base typemask: " << typemask << " \n";
  throw;
  return 0;
}


int RVCtool::sizeof_type(const Type* tp )
{
  if( !tp )
	fatal_error("sizeof_type() got a NULL type.\n",false);
  
  if( tp->isBaseType() )
	return sizeof_base_type(static_cast<const BaseType*>(tp)->typemask );

  if( tp->isPointer() )
	return sizeof(void*);  /* all pointers are of same size */
  
  if( tp->isFunction() ) {
	rv_errstrm << "Warning: in sizeof_type(): function type has no size !\n";
	return 0;
  }

  if( tp->isArray() ) {
	rv_errstrm << "Warning: in sizeof_type(): currently we can not know length of array !\n";
	return sizeof_type(static_cast<const ArrayType*>(tp)->subType );  /* at least one item <<=== FIX */
  }

  return 0;
}


Type* RVCtool::get_symbol_type(Symbol* sym, const char *where)
{
  return get_symbol_type( (sym ? sym->entry : NULL), where);
}

Type* RVCtool::get_symbol_type(SymEntry* se, const char *where)
{  
  Type* form = NULL;

  if( se ) {
	if( se->IsComponentDecl() && se->uComponent )
	  form = se->uComponent->form;
	else if( se->IsTagDecl() ) 
	  form = se->uStructDef;
	else if( se->IsEnumConst() && se->uEnumValue )
	  form = se->uEnumValue->type;
	else if( se->uVarDecl )
	  form = se->uVarDecl->form;
  }

  if( !form ) {
	rv_errstrm << "Error: get_symbol_type() got NULL on path to type.\n";
	if(se)
	  rv_errstrm << "  Symbol \""<< se->name <<"\"";
	rv_errstrm << "  For functions: please declare them before use.\n";
	rv_errstrm << "  in "<< where <<" .\n";
	fatal_error("get_symbol_type(): NULL path to symbol type.", false);
  }

  return form;
}


Decl* RVCtool::get_field_decl(StructDef *def, const Variable *fld)
{
  if( !def || !fld || fld->etype != ET_Variable || !fld->name ) {
	rv_errstrm << "Field ident (variable) expected in get_field_decl() :";
	if(def) def->print(rv_errstrm, NULL, 0); rv_errstrm << " \n";
	return NULL;
  }         
  
  return get_field_decl(def, fld->name);
}


Decl* RVCtool::get_field_decl(StructDef *def, Symbol *sym)
{
  Decl  *comp;

  if( !def || !sym ) {
	rv_errstrm << "Field ident (symbol) expected in get_field_decl() :";
	if(def) def->print(rv_errstrm, NULL, 0); rv_errstrm << " \n";
	fatal_error("Field ident (symbol) expected in get_field_decl().",false); // <<=== DEL
	return NULL;
  }         

  for(int i=0; i < def->nComponents; i++) {
	comp = def->components[i];
	while( comp ) {
	  if( comp->name->name == sym->name )
	return comp;
	  comp = comp->next;
	}
  }

  rv_errstrm << "Warning: get_field_decl() unable to find symbol \"" << *sym <<
	"\" in struct/union: \n";
  def->print(rv_errstrm, NULL, 0); rv_errstrm << "\n";

  return NULL;
}


int RVCtool::get_field_index(StructDef *def, const Variable *fld)
{
  Symbol *sym;
  Decl  *comp;
  int ind = -1;

  if( !def || !fld || fld->etype != ET_Variable || !fld->name ) {
	rv_errstrm << "Field ident expected in get_field_index() :";
	if(def) def->print(rv_errstrm, NULL, 0); rv_errstrm << " \n";
	return -1;
  }         
  
  sym = fld->name;
  for(int i=0; i < def->nComponents; i++) {
	comp = def->components[i];
	while( comp ) {
	  ind++;  /* first component is 0 index. */
	  if( comp->name->name == sym->name )
	return ind;
	  comp = comp->next;
	}
  }

  rv_errstrm << "Warning: get_field_index() unable to find symbol " << *sym << 
	" in struct/union: \n";
  def->print(rv_errstrm, NULL, 0); rv_errstrm << "\n";

  return -1;
}

int RVCtool::get_general_arg_index(FunctionType *def, Symbol *arg)
{
  Decl  *comp;

  if( !def )
	fatal_error("get_arg_index() got NULL function type definition.\n",false);

  if( !arg || !arg->entry || !arg->entry->IsParamDecl() || 
	  !arg->entry->uVarDecl || !arg->entry->uVarDecl->form ) {
	return -1;
  }         
  
  for(int i=0; i < def->nArgs; i++) {
	comp = def->args[i];
	if( comp == arg->entry->uVarDecl || comp->name->name == arg->name )
	  return i;
  }

  return -1;
}



int RVCtool::get_arg_index(FunctionType *def, Symbol *arg)
{
  Decl  *comp;

  if( !def )
	fatal_error("get_arg_index() got NULL function type definition.\n",false);

  if( !arg || !arg->entry || !arg->entry->IsParamDecl() || 
	  !arg->entry->uVarDecl || !arg->entry->uVarDecl->form ) {
	rv_errstrm << "get_arg_index() got bad function argument identifier in:";
	def->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
	if (arg)
	rv_errstrm << "arg name is " << arg->name << "\n";
	return -1;
  }         
  
  for(int i=0; i < def->nArgs; i++) {
	comp = def->args[i];
	if( comp == arg->entry->uVarDecl || comp->name->name == arg->name )
	  return i;
  }

  rv_errstrm << "Warning: get_arg_index() unable to find symbol " << arg->name << 
	" in function definition: ";
  def->printType(rv_errstrm, NULL, true, 0); rv_errstrm << "\n";

  return -1;
}




Decl* RVCtool::get_type_decl(Symbol* var_or_typedef)
{
  if( var_or_typedef == NULL || !var_or_typedef->entry ||
	  ( !var_or_typedef->entry->IsTypeDef() &&
		!var_or_typedef->entry->IsVarDecl() &&
		!var_or_typedef->entry->IsFctDecl() &&
		!var_or_typedef->entry->IsParamDecl() ) ||
	  var_or_typedef->entry->uVarDecl == NULL )
  {
	rv_errstrm << "get_type_decl() recieved NULL or non var/typedef identifier: "
			   << (var_or_typedef ? var_or_typedef->name.data() : "UNPRINTABLE") << " \n";
	fatal_error("\n",false);
	return NULL;
  }

  return var_or_typedef->entry->uVarDecl;
}


StructDef* RVCtool::get_struct_def(const Type* s0p, const char *where)
{
  Type* real = real_type(s0p, where);

  /* check that it is really a struct/union before processing: */
  if( !is_basetype(real, (BT_Struct|BT_Union)) ) {
	rv_errstrm<<"Bad type of struct/union in get_struct_def() in: "<<where<<" :\n";
	s0p->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
fatal_error("Bad type of struct/union in get_struct_def().",false);
	return NULL;
  }

  BaseType* bt = (BaseType*)real;
  if( bt->stDefn )
	return bt->stDefn;

  if( bt->tag ) {
	Symbol* tag = bt->tag;
	if( !tag->entry || !tag->entry->IsTagDecl() || 
	!tag->entry->uStructDef || !tag->entry->uStructDef->stDefn ) {
	  rv_errstrm<<"get_struct_def(): Can't get struct/union definition from its tag. in: "
		<<where<<" :\n";
	  s0p->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
	  return NULL;
	}
	return tag->entry->uStructDef->stDefn; 
  }

  /* if we couldn't find struct either way: */
  rv_errstrm << "Can't get (NULL) struct/union definition in: "<<where<<": \n";
  s0p->printType(rv_errstrm, NULL, true, 0); 
  rv_errstrm << " \n";
  
  return NULL;
}


ScopeTbl* RVCtool::get_scope(DeclStemnt* s0p, const char *where)
{
  Symbol* sym = NULL;
  if( !s0p || s0p->decls.size() == 0 || !s0p->decls[0] ||
	  !(sym = s0p->decls[0]->name) || !sym->entry || !sym->entry->scope ) {
	rv_errstrm << "get_scope() can't get scope from DeclStemnt of \""
		   << (sym?sym->name.data():"") << " at ";
	if( s0p )
	  s0p->location.printLocation(rv_errstrm); rv_errstrm << " .\n";
	if( where )
	  rv_errstrm << "  called from "<< where <<" \n";
	fatal_error("\n",false);
	return NULL;
  }

  return sym->entry->scope;
}


Statement* RVCtool::get_glob_stemnt(Project* pt)
{
  if( !pt || !pt->Parse_TOS || !pt->Parse_TOS->transUnit )
	fatal_error("Error: Can't get TransUnit of parse-tree.", false);
  
  if( !pt->Parse_TOS->transUnit->head )
	fatal_error("Error: No statements in TransUnit of parse-tree of: ",
		pt->Parse_TOS->transUnit->filename, false);

  return pt->Parse_TOS->transUnit->head;
}


FunctionDef* RVCtool::try_get_function(Statement* st)
{
  if( !st )
	return NULL;
  
  if( st->isFuncDef() )
	return (FunctionDef*)st;

  /* Function prototypes (decls) must be treated separately: */
  if( st->isDeclaration() && ((DeclStemnt*)st)->decls.size() > 0 ) 
  {
	Decl* decl = ((DeclStemnt*)st)->decls[0];
	if( decl && !decl->isTypedef() && decl->form && decl->form->isFunction() ) {
	  Symbol* sym = decl->name;
	  if( sym && sym->entry )
	return sym->entry->u2FunctionDef;
	}
  }

  return NULL;
}

///<summary> 
/// if the input expression is a variable (var, function name, var function (?), func argument, component (struct field)), 
/// then it returns its name (which is of type symbol)
///</summary>
Symbol* RVCtool::try_var2symbol(Expression* expr)

{
  CHK_NULL1(expr, "RVCtool::try_var2symbol()");

  if( expr->etype != ET_Variable )
	return NULL;
  
  Variable *var = (Variable*)expr;
  if( !var->name || !var->name->entry )
	return NULL;

  SymEntry* se = var->name->entry;
  if( !se->IsVarDecl() && !se->IsFctDecl() && !se->IsVarFctDecl() && !se->IsParamDecl() && !se->IsComponentDecl() ) // ofer: added IsComponentDecl() for struct fields.
	return NULL;
  
  return var->name;
}


SymEntry* RVCtool::ScopeTbl_remove(ScopeTbl* scope, const std::string& name )
{
  if( !scope || !scope->htab )
	return NULL;

  SymEntry* ent = scope->Lookup( name );
  if( !ent )
	return NULL;

  scope->htab->Delete( ent );
  ent->scope = NULL;
  scope->nsyms--;

  return ent;
}


Symbol* RVCtool::mk_symbol(const std::string& name, SymEntry* ent)
{
  Symbol* ret = new Symbol();
  ret->name = name;
  ret->entry = ent;
  if( ent )
	ent->name = name;
  return ret;
}


Decl* RVCtool::mk_global_decl(Project* pt, Type* form, const std::string& symname,
				  SymEntryType entry_type /*= FctDeclEntry*/)
{
  if( !pt || !form )
	fatal_error( "pt or form is NULL in RVCtool::mk_global_decl().");

  Decl* decl = new Decl(form);

  SymEntry* ent = NULL;
  switch( entry_type ) {
	case TypedefEntry: ent = mk_typedef(symname, decl); break;
	case VarDeclEntry: ent = mk_vardecl(symname, decl); break;
	case FctDeclEntry: ent = mk_fctdecl(symname, decl); break;
	case EnumConstEntry: ent = mk_enum_const(symname, NULL); break;
	default: 
	  rv_errstrm << "Internal: RVCtool::mk_global_decl() can't create global \""<<
	symname <<"\" of SymEntryType: " << entry_type <<" \n";
	  fatal_error( "Bad SymEntryType in RVCtool::mk_global_decl()");
  }	  
  
  Symbol* sym = mk_symbol(symname, ent);
  decl->name = sym;

  ScopeTbl* sym_scope = get_file_scope(pt);
  sym_scope->Insert(ent);

  return decl;
}



Expression* RVCtool::mk_deref(Symbol* sym, const Location& l)
{
  Variable* var = new Variable(sym, l);
  return new UnaryExpr(UO_Deref, var, l);
}

Expression* RVCtool::mk_addrof(Symbol* sym, const Location& l)
{
  Variable* var = new Variable(sym, l);
  return new UnaryExpr(UO_AddrOf, var, l);
}

FunctionCall* RVCtool::mk_func_call(Symbol* sym, const Location& l)
{
  Variable* var = new Variable(sym, l);
  return new FunctionCall(var, l);
}

FunctionCall* RVCtool::mk_func_call(const std::string& name, SymEntry* ent, const Location& l)
{
  Symbol* sym = mk_symbol(name, ent);
  return mk_func_call(sym, l);
}


void RVCtool::add_strdef_component(StructDef* strdef, std::string name, Type* tp)
{
  if( !strdef || !tp )
	fatal_error("NULL str or tp in RVCtool::add_strdef_component()",false);

  Decl* comp_decl = new Decl(tp);
  Symbol* comp_sym = mk_symbol(name, mk_component(name, comp_decl, strdef));
  comp_sym->entry->scope = NULL;
  comp_decl->name = comp_sym;
  strdef->addComponent(comp_decl);
}


Decl* RVCtool::add_func_param(FunctionType* ftp, std::string param_name, Type* tp, 
				  ScopeTbl* proto_scope /* = NULL */)
{
  Decl* d1 = new Decl(tp);
  d1->name = mk_symbol(param_name, mk_paramdecl(param_name, d1));
  ftp->addArg(d1);
  
  if( proto_scope )
	proto_scope->Insert(d1->name->entry);

  return d1;
}


ScopeTbl* RVCtool::create_last_scope(Project* pt, int level, ScopeTbl* parent /* = NULL */,
					 SymEntryType entry_type /* = VarDeclEntry */)
{
  if( !pt )
	fatal_error("NULL project in RVCtool::create_last_scope()", false);

  if( parent && parent->level > level-1 ) {
	rv_errstrm << "Internal: can't create child scope of level "<< level <<
	  " to a scope at level "<< parent->level <<" . \n";
	return NULL;
  }

  if( !parent && level >= BLOCK_SCOPE ) {
	rv_errstrm << "Internal: One must supply a parent scope to create a BLOCK_SCOPE child"; 
	return NULL;
  }

  if( !parent )
	parent = get_root_scope(pt, entry_type);

  ScopeTbl *child = NULL;
  while( parent->level < level-1 ) 
  {
	if( parent->nchild == 0 ) { 
	  // if it has no childen - create one
	  child = new ScopeTbl(parent);
	  
	  if(!child || !parent->ChildInsert(child)) {
	rv_errstrm << "Internal: failed to create scope of level "<< level <<" .\n";
	return NULL;
	  }

	  parent = child;
	}
	else
	  parent = parent->children[parent->nchild-1]; // go to last child.
  }

  return parent;
}


ScopeTbl* RVCtool::get_func_param_scope(FunctionDef* func)
{
  if( !func )
	fatal_error("NULL func in RVCtool::get_func_param_scope()", false);

  FunctionType* ftp = (FunctionType*)func->decl->form;
  if( !ftp || !ftp->isFunction() ) {
	rv_errstrm << "Error: function \""<< func->FunctionName() <<"\" doesn't have "
	  " a FunctionType declaration type. (in RVCtool::get_func_param_scope()) \n";
	return NULL;
  }

  Decl* d0 = NULL;
  if( ftp->nArgs > 0 && (d0 = ftp->args[0]) && d0->name && d0->name->entry )
	return d0->name->entry->scope;

  return NULL;
}


ScopeTbl* RVCtool::get_func_local_scope(FunctionDef* func, Project* parsetree /*= NULL*/)
  // tries to find the scope by first declaration statement
  //   if no such statement exits and parsetree != NULL then tries to create it.
{
  if( !func )
	fatal_error( "NULL func in RVCtool::get_func_local_scope()", false);

  ScopeTbl* scp = NULL;
  DeclStemnt* st0 = (DeclStemnt*)func->head;

  if( func->head->isDeclaration() && st0->decls.size() > 0 ) 
  {
	Decl* d0 = st0->decls[0];
	if( d0 && d0->name && d0->name->entry )
	  scp = d0->name->entry->scope;
  }
  else if( parsetree ) {
	/* Create func's local scope: */
	ScopeTbl* parent = get_func_param_scope(func);
	if( parent )
	  scp = create_last_scope(parsetree, BLOCK_SCOPE, parent);
  }
		
  return scp;
}


SymEntry* RVCtool::get_same_symbol(ScopeTbl* orig_base_scp, SymEntry* orig,
				   ScopeTbl* trg_base_scp, const char* trg_prefix /*=NULL*/)
// Tries to get the same symbol as orig at the same subscope of the trg_base_scp.
// We assume that orig_base_scp and trg_base_scp are basic scopes related to 
// two instances of the same block of code (with maybe some of the vars prefixed
// on one side but not on the other).
{
  if( !orig_base_scp || !trg_base_scp || !orig )
	fatal_error("One of the scopes or the symbol is NULL. In RVCtool::get_same_symbol()", false);

  std::vector<ScopeTbl*> scp_stack;
  ScopeTbl *scp, *trg_scp, *sub_scp;

  // collect all predecessor scopes up to orig_base_scp (not including)
  for( scp  = orig->scope; 
	   scp != orig_base_scp && scp != NULL &&  scp->level != EXTERN_SCOPE;
	   scp = scp->parent )
	scp_stack.push_back(scp);

  if( scp != orig_base_scp ) {
	rv_errstrm << "Internal: symbol \""<< orig <<"\" is not in the subscope of "
	  "a base scope with ID: ";
	orig_base_scp->ShowScopeId(rv_errstrm);
	rv_errstrm << " . (in RVCtool::get_func_param_scope()) \n";
	return NULL;
  }

  int i,j,len = scp_stack.size();
  int        nchild, trg_nchild;
  ScopeTbl** children;

  scp = orig_base_scp;
  trg_scp = trg_base_scp;
  for(i = len-1; i >= 0; --i)
  {
	nchild = scp->nchild;
	trg_nchild = trg_scp->nchild;
	children = scp->children;
	sub_scp = scp_stack[i];
	
	for(j=0; j<nchild; ++j)
	  if( children[j] == sub_scp )
	break;

	if(j >= nchild) {
	  rv_errstrm << "Internal: unable to find a predecessor scopes of \""
		 << orig <<"\" with ID: ";
	  sub_scp->ShowScopeId(rv_errstrm);
	  rv_errstrm << " . (in RVCtool::get_func_param_scope()) \n";
	  return NULL;
	}
	  
	if(j >= trg_nchild) {
	  trg_scp = NULL;
	  break;
	}
	  
	trg_scp = trg_scp->children[j];
  }

  std::string trg_name(trg_prefix? trg_prefix: "");
  trg_name += orig->name;

  if(trg_scp == NULL) {
	  rv_errstrm << "Internal: unable to find a target predecessor scopes of \""
		 << trg_name <<"\" with ID: ";
	  trg_scp->ShowScopeId(rv_errstrm);
	  rv_errstrm << " . (in RVCtool::get_func_param_scope()) \n";
	  return NULL;
  }

  SymEntry *ret = trg_scp->Lookup(trg_name);
  if(ret == NULL) {
	  rv_errstrm << "Internal: unable to find symbol identical to \""<< orig <<
	"\" (named \""<< trg_name <<"\") under the base scope with ID: ";
	  orig_base_scp->ShowScopeId(rv_errstrm);
	  rv_errstrm << " . (in RVCtool::get_func_param_scope()) \n";
	  return NULL;
  }
	
  return ret;
}



std::string RVCtool::get_where(Statement* st)
{
  if( !st )
	return "NULL Statement";

  if( st->isDeclaration() ) {
	  DeclStemnt* dst = (DeclStemnt*)st;
	  if( dst->decls.size() > 0 && dst->decls[0] && dst->decls[0]->name )
		return std::string("Declaration of ") + dst->decls[0]->name->name;
  }

  if( st->isFuncDef() ) {
	FunctionDef* func = (FunctionDef*)st;
	if( func->decl && func->FunctionName() )
	  return func->FunctionName()->name;
  }

  return "UNKNOWN";
}

bool RVCtool::isDirectPointerToFunction(Type* tp, FunctionType **ppFuncType) {
	if (tp == NULL || !tp->isPointer())
		return false;
	PtrType *ptrType = static_cast<PtrType*>(tp);
	if (ptrType->subType == NULL || !ptrType->subType->isFunction())
		return false;
	if (ppFuncType != NULL)
		*ppFuncType = static_cast<FunctionType*>(ptrType->subType);
	return true;
}









/* RVStrIter code: */
/*=================*/

RVStrIter::RVStrIter(StructDef* _str) 
  : str(_str)
{
  ind = 0;
  comp = NULL;
}

Decl* RVStrIter::begin()
{
  for (ind=0; ind < str->nComponents; ind++)
	if( (comp = str->components[ind]) )
	  return comp;
		  
  return (comp=NULL);
}

bool  RVStrIter::end()
{ 
  return (comp == NULL);
}

Decl* RVStrIter::next()
{
  if( !comp )
	return NULL;

  if( (comp = comp->next) )
	return comp;

  for(ind++; ind < str->nComponents; ind++)
	if( (comp = str->components[ind]) )
	  return comp;

  return (comp=NULL);
}



/*  HashTblIter functions:  */
/* ======================== */

HashTblIter::HashTblIter(HashTbl* _ht) : ht(_ht)
{
  slot = 0;
  curr = NULL;
}

SymEntry* HashTblIter::begin()
{
  for (slot=0; slot < ht->tsize; slot++)
	if( (curr = ht->tab[slot]) )
	  return curr;
		  
  return (curr=NULL);
}

bool HashTblIter::end() const
{
  return (curr == NULL);
}

SymEntry* HashTblIter::next()
{
  if( !curr )
	return NULL;

  if( (curr = curr->next) )
	return curr;

  for(slot++; slot < ht->tsize; slot++ )
	if( (curr = ht->tab[slot]) )
	  return curr;

  return (curr=NULL);
}



/*  HashTblConstIter functions:  */
/* ======================== */

HashTblConstIter::HashTblConstIter(const HashTbl* _ht) : ht(_ht)
{
  slot = 0;
  curr = NULL;
}

const SymEntry* HashTblConstIter::begin()
{
  for (slot=0; slot < ht->tsize; slot++)
	if( (curr = ht->tab[slot]) )
	  return curr;

  return (curr=NULL);
}

bool HashTblConstIter::end() const
{
  return (curr == NULL);
}

const SymEntry* HashTblConstIter::next()
{
  if( !curr )
	return NULL;

  if( (curr = curr->next) )
	return curr;

  for(slot++; slot < ht->tsize; slot++ )
	if( (curr = ht->tab[slot]) )
	  return curr;

  return (curr=NULL);
}
