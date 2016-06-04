/* Code base for travering and processing syntactic trees. */
#include <string.h>
#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_walk.h>

#include <ctool/stemnt.h>

#define RV_SECTION  RV_SEC_COLLECT
//(RV_SEC_COLLECT | RV_SEC_REPLACE)


/*  RVWalk functions:  */
/* =================== */

RVWalk::RVWalk(bool _decl_to_symbol /*= false*/)
  : where(NULL)
{
  walk_goto_trg = false; /* by default we go thru statements only sequentially. */  
  set_where("UNKNOWN");
  decl_to_symbol = _decl_to_symbol;
}

RVWalk::~RVWalk() {
  set_where(NULL);
}

void RVWalk::set_where(const char* _where)
{
  if (where != NULL)
	  delete[] where;
  if (_where == NULL)
	  where = NULL;
  else {
    size_t len = strlen(_where) + 1;
	where = new char[len];
	strcpy(where, _where);
  }
}

bool RVWalk::go(Expression* s0p)
{
  CHK_NULL("RVWalk::go(Expression*)"); 
  if(DBG) {s0p->print(rv_errstrm);rv_errstrm<<"\n";}

  switch( s0p->etype )
  {
	case ET_VoidExpr:            // No value
	  return true;

	case ET_Constant:
	  if( !process_const( (Constant*)s0p ) )
		  return false;
	  break;

	case ET_Variable: {      
	  RETYPE( Variable );
	  REP_PROC( name );
	  break;
	}

	case ET_FunctionCall: {
	  RETYPE( FunctionCall );
	  REP_PROC( function );
	  PROC( args );
	  break;
	}
	  
	case ET_AssignExpr:
	case ET_RelExpr: 
	  rv_errstrm << "Internal: ET_AssignExpr or ET_RelExpr was unused in ctool " <<
		"- unexpected Expression::etype = " << s0p->etype << " .\n";
	  return false;

	case ET_UnaryExpr: {
	  RETYPE( UnaryExpr );
	  REP_PROC( _operand );
	  break;
	}

	case ET_BinaryExpr:
	  if( !process_binary( (BinaryExpr*)s0p ) )
		return false;
	  break;
	  
	case ET_TrinaryExpr: {         // x ? y : z
	  RETYPE( TrinaryExpr );
	  TRY_REP_PROC( _condExpr );
	  TRY_REP_PROC( _trueExpr );
	  TRY_REP_PROC( _falseExpr );
	  break;
	}

	case ET_CastExpr: {           // (type) x
	  RETYPE( CastExpr );
	  REP_PROC( castTo );
	  REP_PROC( expr );
	  break;
	}

	case ET_SizeofExpr:           // sizeof(type) -or- sizeof(expr)
	  if( !go_sizeof( (SizeofExpr*)s0p ) )
		return false;
	  break;
	  
	case ET_IndexExpr: {          // x[y]...[]
	  RETYPE( IndexExpr );
	  REP_PROC( array );
	  REP_PROC( _subscript );
	  break;
	}

	default:
	  rv_errstrm << "Unable to walk Expression: ";
	  s0p->print(rv_errstrm);  rv_errstrm << " \n";
	  return false;
  }

  return true;
}


bool RVWalk::go_const(Constant* s0p)
{
  CHK_NULL("RVRVWalk::go_const()"); if(DBG){s0p->print(rv_errstrm);rv_errstrm<<"\n";}

  switch( s0p->ctype )
  {
	case CT_Char:
	case CT_Int:
	case CT_UInt:
	case CT_Float:
	case CT_String:
	case CT_Enum:
	  break;

	case CT_Array: {          // For an array initializer
	  RETYPE( ArrayConstant );
	  PROC( items );
	  break;
	}

	default:
	  rv_errstrm << "Unable to walk Constant: ";
	  s0p->print(rv_errstrm);  rv_errstrm << " \n";
	  return false;
  }
  
  return true;
}


bool RVWalk::go_binary(BinaryExpr* s0p)
{
  CHK_NULL("RVWalk::go_binary()");

  switch( s0p->bOp ) 
  {
	case BO_Assign: {
	  RETYPE( AssignExpr );
	  REP_PROC( _rightExpr );
	  REP_PROC( _leftExpr );
	  break;
	}

	case BO_Member:
	case BO_PtrMember:
	  /* special treatment to union or struct members: */
	  if( !process_member_op( s0p ) )
		return false;
	  break;
	  
	default:
	  REP_PROC( _leftExpr );
	  REP_PROC( _rightExpr );
  }

  return true;
}


bool RVWalk::go(Type* s0p)
{
  CHK_NULL("RVWalk::go(Type*)");; 
  //if(DBG){s0p->printType(rv_errstrm, NULL, true, 0);rv_errstrm<<"\n";}

  switch( s0p->type )
  {
	case TT_Base:        // a simple base type, T
	  if( !process_basetype( (BaseType*)s0p ) )
		return false;
	  break;

	case TT_Pointer: {    // pointer to T
	  RETYPE( PtrType );
	  if( s0p->qualifier == TQ_Volatile )
		  rv_errstrm << "Warning: \"volatile\" qualifier may invalidate the verification !\n";
	
	  REP_PROC( subType );
	  break;
	}
	  
	case TT_Array: {     // an array of T
	  RETYPE( ArrayType );
	  REP_PROC( subType );
	  TRY_REP_PROC( size );
	  break;
	}

	case TT_BitField: {  // a bitfield
	  RETYPE( BitFieldType );
	  REP_PROC(subType);
	  REP_PROC( size );
	  break;
	}

	case TT_Function:    // <args> -> <result>
	  if( !process_function_type( (FunctionType*)s0p ))
		return false;
	  break;

	default:
	  rv_errstrm << "Unable to walk Type: ";
	  s0p->printType(rv_errstrm, NULL, true, 0);
	  rv_errstrm << " \n";
	  return false;
  }

  return true;
}


bool RVWalk::go_basetype(BaseType* s0p)
{
  CHK_NULL("RVWalk::go_basetype()"); 
if(DBG){s0p->printType(rv_errstrm, NULL, true, 0);rv_errstrm<<"\n";}

  BaseTypeSpec tm0 = s0p->typemask;

  if( s0p->typemask & BT_UserType )
	REP_PROC( typeName );

  if ( tm0 & (BT_Struct|BT_Union|BT_Enum)) 
	if( !go_struct_type( s0p ) )
	  return false;
  
  return true;
}


bool RVWalk::go_function_type(FunctionType* s0p)
{
  CHK_NULL("RVWalk::go_function_type()"); 
  if(DBG){s0p->printType(rv_errstrm, NULL, true, 0);rv_errstrm<<"\n";}

  REP_PROC( subType );

  for(int i =0; i<s0p->nArgs; i++)
	if( s0p->args[i]->name && !decl_to_symbol )  /* try process thru the symbol first: */
	  REP_PROC( args[i]->name )
	else
	  REP_PROC( args[i] );   /* try the rest of the declaration. */ 

  return true;
}


bool RVWalk::go(ExprVector& s0p)
{
  ExprVector::iterator  i;
  FORVEC(i,s0p)
	if( try_replace(&(*i)) && !process(*i) )
	  return false;

  return true;
}


bool RVWalk::go(StructDef *s0p)
{
  Decl  *comp0;

  CHK_NULL("RVWalk::go(StructDef*)"); 
  //if(DBG){s0p->print(rv_errstrm,NULL,0);rv_errstrm<<"\n";}

  /* prevent infinite recursion in recursive structs: */
  if( s0p->assumeEq == s0p ) {
	recursive_struct = s0p;
	return true;
  }
  s0p->assumeEq = s0p;

  /* Note: to prevent infinite recursion we don't call TRY_REP_PROC( tag ).
	 The tag should be processed expicitly by process(StructDef* it) in a child class.
  */

  bool failed = false;

  for(int i=0; i < s0p->nComponents; i++) {  
	comp0 = s0p->components[i];
	while( comp0 ) {

    if(DBG) rv_errstrm <<"go(StructDef*): processing \""<<comp0->name->name<<"\" \n";

	  if( decl_to_symbol )
	failed = try_replace( &comp0 ) && !process(comp0);
	  else
	failed = try_replace( &(comp0->name) ) && !process(comp0->name);

	  if( failed ) {
	s0p->assumeEq = NULL; // pop DFS mark
	return false;
	  }
	  comp0 = comp0->next;
	}
  }
	  
  s0p->assumeEq = NULL; // pop DFS mark
  return true;
}


bool RVWalk::go_member_op(BinaryExpr* s0p)
{
  Type *st0 = NULL;   // struct or union types.
  Variable *fld = NULL;
  StructDef* strdef = NULL;
  Decl* fld_decl = NULL;

  CHK_NULL("RVWalk::go_member_op(BinaryExpr*)"); 
  if(DBG){s0p->print(rv_errstrm);rv_errstrm<<"\n";}

  if( s0p->bOp != BO_Member && s0p->bOp != BO_PtrMember ) {
	rv_errstrm << "Attempt to walk non member expressions in go_member_op() :";
	s0p->print(rv_errstrm); rv_errstrm << " \n";
	return false;
  }

  CHK_NULL1(s0p->leftExpr(), "s0p->leftExpr() in RVWalk::go_member_op(BinaryExpr*)"); 
  st0 = real_type(s0p->leftExpr()->type, where);

  if( s0p->bOp == BO_PtrMember ) {   // if its an arrow (->) operation
	/* check it is really pointer: */
	if( !st0 || !is_pointer(st0, "go_member_op()", &st0) ) {
	  rv_errstrm << "Warning: PtrType expected bofore '->' (in go_member_op()):";
	  s0p->print(rv_errstrm); rv_errstrm << " \n";
	  /* return false; */
	}       
  }

  if( st0 && !(strdef = get_struct_def(st0, where)) )
	return false;

  REP_PROC( _leftExpr );

  fld = (Variable*)s0p->rightExpr();
  fld_decl = get_field_decl(strdef, fld);
  if( !fld_decl )
	return false;

  /* if leagal struct field - process the symbol: */
  REP_PROC( _rightExpr );

  /* then process the type: */
  if( !process( fld_decl ) )
	return false;
  
  return true;
}


bool RVWalk::go_struct_type(Type* s0p, bool use_tag /*= true*/)
{
  CHK_NULL("RVWalk::go_struct_type()");
 if(DBG) {s0p->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";}

  /* check that it is really a struct/union before processing: */
 if( !is_basetype(s0p, (BT_Struct|BT_Union|BT_Enum)) ) {
	rv_errstrm<<"Bad type of struct/union in go_struct_type() in: "<<where<<" :\n";
	s0p->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
	return false;
  }


  {
	RETYPE(BaseType);
	if( use_tag && s0p->tag ) /* the tag name may be significant */
	  REP_PROC( tag )
	else if( (s0p->typemask & (BT_Struct|BT_Union)) && s0p->stDefn )
	  REP_PROC( stDefn )
	else if( (s0p->typemask & BT_Enum) && s0p->enDefn )
	  REP_PROC( enDefn )
	else {
	  rv_errstrm << "Unknown (NULL ?) struct/union definition: ";
	  s0p->printType(rv_errstrm, NULL, true, 0); 
	  rv_errstrm << " \n";
	}
  }

  return true;
}


bool RVWalk::go_sizeof(SizeofExpr* s0p)
{
  CHK_NULL("RVWalk::go_sizeof()"); 
if(DBG) {s0p->print(rv_errstrm);rv_errstrm<<"\n";}

  /* before and after sizeof is done thru go(Expression*) */

  if( s0p->sizeofType )
	REP_PROC( sizeofType )
  else if( s0p->expr )
	REP_PROC( expr )
  else {
	rv_errstrm << "Error: sizeof operator argument type or expression are NULL at: ";
	s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
	return false; 
  }

  return true;
}

bool RVWalk::go(Statement* s0p)
{ 
  CHK_NULL("RVWalk::go(Statement*)"); 
  //if(DBG){s0p->print(rv_errstrm,0);rv_errstrm<<"\n";}

  PROC( labels );

  switch( s0p->type )
  {
	case ST_NullStemnt:   // The null statement.
	  break;

	case ST_TypedefStemnt:
	case ST_DeclStemnt: {
	  RETYPE( DeclStemnt );
	  PROC( decls );	
	  break;
	}

	case ST_ExpressionStemnt: {
	  RETYPE( ExpressionStemnt );
	  TRY_REP_PROC( expression );
	  break;
	}

	case ST_IfStemnt: {
	  RETYPE( IfStemnt );
	  TRY_REP_PROC( cond );
	  TRY_REP_PROC( thenBlk );
	  TRY_REP_PROC( elseBlk );
	  break;
	}

	case ST_SwitchStemnt: {
	  RETYPE( SwitchStemnt );
	  TRY_REP_PROC( cond );
	  TRY_REP_PROC( block );
	  break;
	}
	  
	case ST_ForStemnt: {
	  RETYPE( ForStemnt );
	  TRY_REP_PROC( init );
	  TRY_REP_PROC( cond );
	  TRY_REP_PROC( incr );
	  TRY_REP_PROC( block );
	  break;
	}

	case ST_WhileStemnt: {
	  RETYPE( WhileStemnt );
	  TRY_REP_PROC( cond );
	  TRY_REP_PROC( block );
	  break;
	}

	case ST_DoWhileStemnt: {
	  RETYPE( DoWhileStemnt );
	  TRY_REP_PROC( cond );
	  TRY_REP_PROC( block );
	  break;
	}

	case ST_ContinueStemnt:
	case ST_BreakStemnt:
	  break;

	case ST_GotoStemnt: {
	  RETYPE( GotoStemnt );
	  REP_PROC( dest );
	  break;
	}
	  
	case ST_ReturnStemnt: {
	  RETYPE( ReturnStemnt );
	  TRY_REP_PROC( result );
	  break;
	}

	case ST_Block:
	  if( s0p->isFuncDef() ) {
	RETYPE( FunctionDef );
	if (DBG) rv_errstrm << "RVWALK::processing " << s0p->FunctionName()->name << "\n";
	if( decl_to_symbol )
	  REP_PROC( decl )
	else
	  REP_PROC( decl->name );
	  }
	  if( !process_block( (Block*)s0p ))
		return false;
	  break;

	default:
	  rv_errstrm << "Unable to walk Statement: ";
	  s0p->print(rv_errstrm, 0);  rv_errstrm << " \n";
	  return false;
  }

  return true;
}


bool RVWalk::go_block(Block* s0p)
{
  CHK_NULL("RVWalk::go_block()"); 
if(DBG){rv_errstrm<<"RVWalk::go_block() starts block at ";
  s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";}
  //if(DBG){s0p->print(rv_errstrm,0);rv_errstrm<<"\n";}


  Statement** pst = &s0p->head;
  if( !(*pst) )
	return true; /* empty block */

  Statement* next = s0p->head;
  while( next ) {
	next = (*pst)->next;

	if( try_replace(pst) && !process(*pst) )
	return false;
	
	/* connect chain (may be desrupted by try_repslace()): */
	(*pst)->next = next;

	if( next )
	  pst = &((*pst)->next);
  }

  s0p->tail = *pst;

  return true;
}


bool RVWalk::go(Symbol* s0p)
{
  CHK_NULL("RVWalk::go(Symbol*)");

  /* some symbols (like struct fields don't have entry! */
  if( s0p->entry && !go(s0p->entry) )
	return false;

  return true;
}

bool RVWalk::go(Decl* s0p)
{
  CHK_NULL("RVWalk::go(Decl*)");

  if( decl_to_symbol )
	TRY_REP_PROC( name );

  TRY_REP_PROC( form );

  TRY_REP_PROC( initializer );

  return true;
}

bool RVWalk::go(DeclVector& it)
{
  for(unsigned i = 0; i < it.size(); i++)
	if( decl_to_symbol ) {
	  if( try_replace( &it[i] ) && !process(it[i]) ) 
	return false;
	}
	else if( try_replace( &(it[i]->name) ) && !process( it[i]->name ) ) 
	  return false;

  return true;
}


bool RVWalk::go(SymEntry* s0p)
{
  CHK_NULL("RVWalk::go(SymEntry*)");
if(DBG){s0p->Show(rv_errstrm);rv_errstrm<<"\n";} 

  /* Note: SymEntry is treated only thru its Symbol (in go(Symbol*)). */

  switch (s0p->type)
  {
    case VarFctDeclEntry:
	case FctDeclEntry:
	  if( !decl_to_symbol ) // prevent infinite recursion
	REP_PROC( uVarDecl );
	  /* Don't process u2FunctionDef to prevent infinite recursion -
		   is processed through FunctionDef statement. */
	  break;
 
	case VarDeclEntry:
	case TypedefEntry:
	case ParamDeclEntry:
	  if( !decl_to_symbol ) // prevent infinite recursion
	REP_PROC( uVarDecl );
	  break;

	case EnumConstEntry:
	  TRY_REP_PROC( uEnumValue );
	  if( !decl_to_symbol ) // prevent infinite recursion
	REP_PROC( u2EnumDef );
	  break;
	  
	case LabelEntry:
	  if( !decl_to_symbol ) // prevent infinite recursion      
	REP_PROC( uLabelDef );
	  /* May need here something against infinite recursion <<==== */
	  if( walk_goto_trg )
		REP_PROC( u2LabelPosition );
	  break;
	  
	case TagEntry:
	  /* go struct type with use_tag=false, to prevent infinite recursion */
	  if( !go_struct_type( s0p->uStructDef, false ) )
	return false;
	  break;
		
	case ComponentEntry:
	  if( !decl_to_symbol ) // prevent infinite recursion
	REP_PROC( uComponent );
	  /* ! Don't go to the container (u2Container) - we always get back here from it ! */
	  break;

	default:
	  rv_errstrm << "Unable to walk SymEntry: ";
	  s0p->Show(rv_errstrm);  rv_errstrm << " \n";
	  return false;
  }
  
  return true;
}


bool RVWalk::go(Label* s0p)
{
  CHK_NULL("RVWalk::go(Label*)");
  
  switch( s0p->type ) 
  {
	case LT_Default:             // default:
	  break;

	case LT_Case:                // case <expr>:
	  REP_PROC( begin );
	  break;

	case LT_CaseRange:           // case <expr> ... <expr>: (gcc extension)
	  REP_PROC( begin );
	  REP_PROC( end );
	  break;

	case LT_Goto:                 // A named label (goto destination).
	  if( decl_to_symbol )
	REP_PROC( name );
	  break;

	default:
	  rv_errstrm << "Unable to walk Label: ";
	  s0p->print(rv_errstrm, 0);  rv_errstrm << " \n";
	  return false;
  }

  return true;
}


bool RVWalk::go(LabelVector& it)
{
  LabelVector::const_iterator i;
  FORVEC(i, it)
	if( !process(*i) )
	  return false;
	
  return true;
}
  

bool RVWalk::go(EnumDef* s0p)
{
  CHK_NULL("RVWalk::go(EnumDef*)");
  
  TRY_REP_PROC( tag );

  for(int i=0; i < s0p->nElements; i++) {  
	if( decl_to_symbol )
	  TRY_REP_PROC( names[i] );

	TRY_REP_PROC( values[i] );
  }

  return true;
}

FunctionType *RVWalk::getFunctionFromFuncPtr(Type* in_tp) {
	Type *tp = real_type(in_tp, "RVTypeProp::getFunctionFromFuncPtr");
	if (tp == NULL || !tp->isPointer())
		return NULL;

	PtrType *ptrType = static_cast<PtrType*>(tp);
	assert(ptrType->subType != NULL);

	if (ptrType->subType->isPointer())
		return getFunctionFromFuncPtr(ptrType->subType); //recursive call

	return ptrType->subType->isFunction()?
			static_cast<FunctionType*>(ptrType->subType) : NULL;
}
