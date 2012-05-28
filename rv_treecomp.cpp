/* Code for syntactic comparison of expression trees. */
#include <rv_consts.h>
#include <rv_error.h>
#include <rv_parse.h>
#include <rv_funcpair.h>
#include <rv_treecomp.h>

#define RV_SECTION RV_SEC_TREECOMP


/* definitions for syntactic comparison between the sides: */

/* compare a single field: */
#define COMPF(F) {if(s0p->F != s1p->F) return false;}

/* recourse into field F on both sides: */  
#define RECF(EQ,F)  {if( !EQ(s0p->F,s1p->F) ) return false;}

#define CHK_EQ_NULL \
  { if(s0pUser == s1pUser) return true;  \
	if( s0pUser == NULL || s1pUser == NULL ) return false;}

/* chenge the type of the pointers that are used for the sides to T: */
#define RETYPE2(T)  const T *t0=static_cast<const T*>(s0p),*t1=static_cast<const T*>(s1p); const T *s0p=t0,*s1p=t1; \
 // if(DBG){rv_errstrm<<"RETYPE2: "<<#T<<"\n";}

/* mark objects on two sides as equal to each other: */
#define MARKEQ(T) { const_cast<T*>(s0p)->equalTo = s1p; const_cast<T*>(s1p)->equalTo = s0p; }

/* check whether objects are marked equal - return true: */
#define CHK_MARK {if(s0pUser->equalTo == s1pUser && s1pUser->equalTo == s0pUser) return true;}



/*  RVTreeComp functions:  */
/* ======================= */

RVTreeComp::RVTreeComp(bool _use_uf_lists /*=false*/, bool _force_eq_comp_names /*=false*/)
{ 
  use_uf_lists = _use_uf_lists; 
  force_eq_comp_names = _force_eq_comp_names;
}


bool RVTreeComp::ignore_funcs(const Expression *s0pUser, const Expression *s1pUser) const
{
  CHK_EQ_NULL;
  if(DBG) {s0pUser->print(rv_errstrm);rv_errstrm<<"\n";}

  const Location *problem_location = NULL;
 
   if( s0pUser->etype != ET_Variable )
	problem_location = &(s0pUser->location);
  else if( s1pUser->etype != ET_Variable )
	problem_location = &(s1pUser->location);
	
  if( problem_location ) {
	rv_errstrm << "Indirect function calls are not supported. Problem at: ";
	problem_location->printLocation( rv_errstrm );
	rv_errstrm << " .\n";
	return false;
  }

  const Variable* v0 = static_cast<const Variable*>(s0pUser);
  const Variable* v1 = static_cast<const Variable*>(s1pUser);
  if( !v0->name || !v1->name )
	return false;

  /* the function names still need to be equal: */
  if( v0->name->name != v1->name->name )
	return false;
  
  /* ignore functions that can't have bodies: */
  if( RVParse::ignore_func(v0->name->name) || 
	  RVParse::supplied_by_rvt(v0->name->name) )
	return true;
	  
  return false;
}


bool RVTreeComp::eq_expr(const Expression* s0pUser, const Expression* s1pUser) const
{
  CHK_EQ_NULL; if(DBG) {s0pUser->print(rv_errstrm);rv_errstrm<<"\n";}
  CHK_MARK; // if both sides are marked as equal to each other - return true; 
  const Expression *s0p = s0pUser, *s1p = s1pUser;
  
  if( !skip_unneeded_cast( s0p, s1p ) )
	return false;

  COMPF( etype );

  switch( s0p->etype )
  {
	case ET_VoidExpr:            // No value
	  return true;

	case ET_Constant:
	  if( !eq_const( static_cast<const Constant*>(s0p), static_cast<const Constant*>(s1p) ))
		return false;	  
	  break;
	  

	case ET_Variable: {      
	  RETYPE2( Variable );
	  
	  if( !s0p->name || !s1p->name )
		fatal_error("Variable with a NULL name symbol was found !\n");

	  SymEntry* e0p = s0p->name->entry;
	  SymEntry* e1p = s1p->name->entry;

	  if( !e0p || !e1p )
		return false;

	  /* If the sides are marked equal it should be *to each other* : */
	  if( e0p->equalTo || e1p->equalTo )
		return( e0p->equalTo == e1p && e1p->equalTo == e0p );

	  bool is_enum0 = e0p->IsEnumConst();
	  bool is_enum1 = e1p->IsEnumConst();

	  if( is_enum0 != is_enum1 )
	    return false;

	  if( is_enum0 ) {
	if( !eq_enum_idents(e0p, e1p) )
	  return false;
	  }
	  else {  // it is a var symbol
	/* Can't interchange global and local vars: */
	if( is_top_level(e0p) != is_top_level(e1p) )
	  return false;

	Decl* vd0 = get_type_decl( s0p->name );
	Decl* vd1 = get_type_decl( s1p->name );
	if( !eq_type( vd0->form, vd1->form ) )
	  return false;
	if( !eq_expr( vd0->initializer, vd1->initializer ) )
	  return false;
	  }

	  /* below when detected a global - let the user ack <<=== */
if(DBG && is_top_level(e0p)) 
  rv_errstrm << "Detected globals: " << e0p->name << " -- " << e1p->name << " .\n";

	  /* MARKEQ the respective SymEntries for next time we meet these vars: */
	  e0p->equalTo = e1p; 
	  e1p->equalTo = e0p; 
	  break;
	}

	case ET_FunctionCall: {
	  RETYPE2( FunctionCall );
if(DBG){ rv_errstrm << "The callees are:"; s0p->function->print(rv_errstrm); rv_errstrm<<" and ";
  s1p->function->print(rv_errstrm); rv_errstrm << " \n";}

	  if( !ignore_funcs( s0p->function, s1p->function ) ) {

	/* if func_pairs exist: check funcs are defined equal by user or other method 
	   otherwise compare by name and arg list. */
	bool eqaul_in_uf_lists = false;
	if( use_uf_lists ) { 
	  if( rv_ufs.are_related( s0p->function, s1p->function ) )
		eqaul_in_uf_lists = true;
	  else {
if(DBG) rv_errstrm << "These functions on different sides are unrelated (yet).\n"; 
	  }
	}
	if( !eqaul_in_uf_lists )
	  RECF(eq_expr, function );
	  }

	  if( !eq_expr_vec( &(s0p->args), &(s1p->args)) )
		return false;
	  break;
	}
	  
	case ET_AssignExpr:
	case ET_RelExpr: 
	  rv_errstrm << "Internal: ET_AssignExpr or ET_RelExpr was unused in ctool " <<
		"- unexpected Expression::etype = " << s0p->etype << " .\n";
	  return false;

	case ET_UnaryExpr: {
	  RETYPE2( UnaryExpr );
	  COMPF( uOp );
	  RECF(eq_expr, operand() );
	  break;
	}

	case ET_BinaryExpr:
	  if( !eq_binary( static_cast<const BinaryExpr*>(s0p), static_cast<const BinaryExpr*>(s1p) ) )
		return false;
	  break;
	  
	case ET_TrinaryExpr: {         // x ? y : z
	  RETYPE2( TrinaryExpr );
	  RECF(eq_expr, condExpr() );
	  RECF(eq_expr, trueExpr() );
	  RECF(eq_expr, falseExpr() );
	  break;
	}

	case ET_CastExpr: {           // (type) x
	  RETYPE2( CastExpr );
	  RECF(eq_type, castTo );
	  RECF(eq_expr, expr );
	  break;
	}

	case ET_SizeofExpr:           // sizeof(type) -or- sizeof(expr)
	  if( !eq_sizeof( static_cast<const SizeofExpr*>(s0p), static_cast<const SizeofExpr*>(s1p) ) )
		return false;
	  break;
	  
	case ET_IndexExpr: {          // x[y]...[]
	  RETYPE2( IndexExpr );
	  RECF(eq_expr, array );
	  RECF(eq_expr, _subscript );
	  break;
	}

	default:
	  rv_errstrm << "Unable to compare Expression (side 0): ";
	  s0p->print(rv_errstrm);  rv_errstrm << " \n";
	  return false;
  }

  MARKEQ(Expression); // mark the structs on both sides equal to each other

  return true;
}


bool RVTreeComp::eq_const(const Constant* s0pUser, const Constant* s1pUser) const
{
  CHK_EQ_NULL;
  if(DBG){s0pUser->print(rv_errstrm);rv_errstrm<<"\n";}
  const Constant *s0p = s0pUser,  *s1p = s1pUser;

  COMPF( ctype );

  switch( s0p->ctype )
  {
	case CT_Char: {
	  RETYPE2( CharConstant );
	  COMPF(ch);
	  COMPF(wide);
	  break;
	}

	case CT_Int: {
	  RETYPE2( IntConstant );
	  COMPF(lng);
	  COMPF(L);
	  break;
	}

	case CT_UInt: {
	  RETYPE2( UIntConstant );
	  COMPF(ulng);
	  COMPF(L);
	  break;
	}

	case CT_Float: {  
	  RETYPE2( FloatConstant );
	  double val0, val1;
	  
	  /* check not only the init strings but the realvalues. */
	  if( s0p->value != s1p->value ) { 
		sscanf( s0p->value.data(), "%lf", &val0 );
		sscanf( s1p->value.data(), "%lf", &val1 );
		if( val0 != val1 )
		  return false;
	  }
	  break;
	}

	case CT_String: {      
	  RETYPE2( StringConstant );
	  COMPF(buff);
	  COMPF(wide);
	  break;
	}

	case CT_Array: {          // For an array initializer
	  RETYPE2( ArrayConstant );
	  if( !eq_expr_vec( &(s0p->items), &(s1p->items) ) )
		return false;
	  break;
	}

	case CT_Enum: {            // A single enumeration constant
	  RETYPE2( EnumConstant );
	  RECF(eq_expr, value );   // we don't care of value's name
	  break;
	}

	default:
	  rv_errstrm << "Unable to compare Constant (side 0): ";
	  s0p->print(rv_errstrm);  rv_errstrm << " \n";
	  return false;
  }

  return true;
}



bool RVTreeComp::skip_unneeded_cast(PC_Expression& s0p, PC_Expression& s1p) const
  // checks for type casts which exist only on one side and
  //   are implicit on the other side.
  // can be applied only if one side is ET_CastExpr.
{
  if( s0p->etype == s1p->etype )
	return true;

  if( s0p->etype == ET_CastExpr && s1p->type ) {
	const CastExpr* ce0 = static_cast<const CastExpr*>(s0p);

	if( eq_type(ce0->castTo, s1p->type) )  /* <<=== MAYBE check higher in the exp-tree */
	  s0p = ce0->expr; /* ignore cast */
	else
	  return false; /* types would not match */
  }
  else if( s1p->etype == ET_CastExpr && s0p->type ) {
	const CastExpr* ce1 = static_cast<const CastExpr*>(s1p);

	if( eq_type(s0p->type, ce1->castTo) )  /* <<=== MAYBE check higher in the exp-tree */
	  s1p = ce1->expr; /* ignore cast */
	else
	  return false; /* types would not match */      
  }

  return true;
} 


bool RVTreeComp::eq_binary(const BinaryExpr* s0pUser, const BinaryExpr* s1pUser) const
{
  CHK_EQ_NULL;
  const BinaryExpr* s0p = s0pUser, *s1p = s1pUser;
  COMPF( bOp );

  switch( s0p->bOp ) 
  {
	case BO_Assign: {
	  RETYPE2( AssignExpr );
	  COMPF( aOp );
	  RECF(eq_expr, leftExpr() );
	  RECF(eq_expr, rightExpr() );
	  break;
	}

	case BO_Rel: {
	  RETYPE2( RelExpr );
	  COMPF( rOp );
	  RECF(eq_expr, leftExpr() );
	  RECF(eq_expr, rightExpr() );
	  break;
	}

	case BO_Member:
	case BO_PtrMember:
	  /* special treatment to union or struct members: */
	  if( !eq_member_op( s0p, s1p ) )
		return false;
	  break;
	  
	default:
	  RECF(eq_expr, leftExpr() );
	  RECF(eq_expr, rightExpr() );
  }

  return true;
}


bool RVTreeComp::eq_type_loose(FunctionDef* s0pUser, FunctionDef* s1pUser) const {  // ofer. change tag: PPE
	
	//Goal: a function that does partial matching according to names, after all else failed. An out (in) that does not match is marked as AT_Aout (AT_Ain) ("abandoned outout/input"). 
	// The idea is that later we will not include these variable in the comparison. 
	// currently this is not fully implemented,  and is not invoked (waiting to see a case where this can actually help completeness).

	if (s0pUser == NULL || s1pUser == NULL) return false;
	
	FunctionType *s0p = static_cast<FunctionType*>(s0pUser->decl->form);
	FunctionType *s1p = static_cast<FunctionType*>(s1pUser->decl->form);
	assert(s0p->type == TT_Function);
	char mapped_inputs = 0, mapped_outputs = 0;
	Decl *comp0, *comp1;
	
    RECF(eq_type, subType );
	int i, j;
	for(i = 0; i < s0p->nArgs; i++) {
		comp0 = s0p->args[i];
		assert(comp0->name);
		for(j = 0; j < s1p->nArgs; j++) {
			comp1 = s1p->args[j];
			assert(comp1->name);		
			if( comp0->name->name == comp1->name->name && eq_type(comp0->form, comp1->form )) break; // found match					
		}
		if (j == s1p->nArgs) { // did not find a match. time to change status.
			std::cout << "changing status of: " << comp0->name->name << std::endl;
			printf("@@@%d \n", unsigned(s0pUser->fnode.get_argtype(i)));
			if (s0pUser->fnode.is_out_arg(i)) {
				s0pUser->fnode.switchOff_argtype(i, AT_Out);
				s0pUser->fnode.switchOn_argtype(i, AT_Aout);
			}
			if (s0pUser->fnode.is_in_arg(i)) {
				s0pUser->fnode.switchOff_argtype(i, AT_In);
				s0pUser->fnode.switchOn_argtype(i, AT_Ain);
			}
			
			printf("@@@%d \n", unsigned(s0pUser->fnode.get_argtype(i)));
		}
		else {
				if (s0pUser->fnode.is_out_arg(i)) mapped_outputs++;
				if (s0pUser->fnode.is_in_arg(i)) mapped_inputs++;
		}
	}
	// globals ? 
	
  return mapped_inputs && mapped_outputs;  // we currently return true iff there is at least one mapped input & output. Can make a different threashold as a parameter later. 
}

	
///<summary>
/// The entry point to a set of mutually recursive functions (eq_type, eq_basetype, eq_expr, eq_function_type, ...) that together return true if the expressions pointed to by the input types have the same type. 
/// If, for example, the entry point are two functions, then recursively we compare their arguments. Their arguments can be structures/pointers, etc, and hence it needs to open it recursively.
///</summary>
bool RVTreeComp::eq_type(const Type* s0pUser, const Type* s1pUser) const
{
  CHK_EQ_NULL; 
  CHK_MARK;

  /* ignore UserType names: */
  const Type *s0p = real_type(s0pUser, "RVTreeComp::eq(Type*)");
  const Type *s1p = real_type(s1pUser, "RVTreeComp::eq(Type*)");

  COMPF( type );

  switch( s0p->type )
  {
	case TT_Base:        // a simple base type, T
	  if( !eq_basetype( static_cast<const BaseType*>(s0p), static_cast<const BaseType*>(s1p) ) )
		return false;	  
	  break;

	case TT_Pointer: {    // pointer to T
	  RETYPE2( PtrType );
	  /* we ignore the "qualifier" filed (?) */
	  if( s0p->qualifier == TQ_Volatile || s1p->qualifier == TQ_Volatile )
	rv_errstrm << "Warning: \"volatile\" qualifier may invalidate the verification !\n";
	
	  RECF(eq_type, subType);
	  break;
	}
	  
	case TT_Array: {     // an array of T
	  RETYPE2( ArrayType );
	  RECF(eq_type, subType);
	  /* should do calc_int_val(size) for both sides and compare <<=== */
	  RECF(eq_expr, size );  // instead we require a stronger syntactic equiv
	  break;
	}

	case TT_BitField: {  // a bitfield
	  RETYPE2( BitFieldType );
	  RECF(eq_type, subType);
	  /* should do calc_int_val(size) for both sides and compare <<=== */
	  RECF(eq_expr, size );  // instead we require a stronger syntactic equiv
	  break;
	}

	case TT_Function:    // <args> -> <result>
	  if( !eq_function_type( static_cast<const FunctionType*>(s0p), static_cast<const FunctionType*>(s1p) ))
		return false;
	  break;

	default:
	  rv_errstrm << "Unable to compare Type (side 0): ";
	  s0p->printType(rv_errstrm, NULL, true, 0);
	  rv_errstrm << " \n";
	  return false;
  }

  MARKEQ(Type); // mark the types as equal

  return true;
}

///<summary>
/// see explanation in eq_type
///</summary>
bool RVTreeComp::eq_basetype(const BaseType* s0pUser, const BaseType* s1pUser) const
{
  Type *ut0p = NULL;   // for real types of typedef identifiers
  Type *ut1p = NULL;
  BaseTypeSpec tm0, tm1; /* typemasks */

  CHK_EQ_NULL;
  const BaseType* s0p = s0pUser, *s1p = s1pUser;

  if(DBG){s0p->printType(rv_errstrm, NULL, true, 0);rv_errstrm<<"\n";}

  /* Note that qualifier and tag fields are not compared 
	 as they may differ between various programs even if the type itself is equal. */

  if( s0p->typemask & BT_UserType )
	ut0p = get_type_decl( s0p->typeName )->form;

  if( s1p->typemask & BT_UserType )
	ut1p = get_type_decl( s1p->typeName )->form;

  if( ut0p || ut1p )
	return eq_type( (ut0p ? ut0p : static_cast<const Type*>(s0p)), (ut1p ? ut1p : static_cast<const Type*>(s1p)) );

  /* (signed) == (signed int), (unsigned) == (unsigned int): */
  tm0 = fix_int_mask(s0p->typemask);
  tm1 = fix_int_mask(s1p->typemask);

  /* if neither of the types is a typedef or enum they should be explicitly equal: */
  if(tm0 != tm1) 
	return false;

  if ( tm0 & (BT_Struct | BT_Union)) 
  {
	if( s0p->stDefn && s1p->stDefn )
	  RECF(eq_struct_def, stDefn )
	else if( s0p->tag && s0p->tag->entry && s0p->tag->entry->uStructDef &&
			 s1p->tag && s1p->tag->entry && s1p->tag->entry->uStructDef ) {

	  /* if this is a struct of incomplete type: */
	  if( s0p->tag->entry->uStructDef == s0p || s1p->tag->entry->uStructDef == s1p )
	/* require both of them be incomplete (?) and have the same tag name: */
	return ( s0p->tag->entry->uStructDef == s0p && 
		 s1p->tag->entry->uStructDef == s1p &&
		 s0p->tag->name == s1p->tag->name );

	  /* otherwise use struct contents to decide. */
	  RECF(eq_type, tag->entry->uStructDef )
	} 
	else {
	  rv_errstrm << "Unknown (NULL ?) struct/union definition: ";
	  s0p->printType(rv_errstrm, NULL, true, 0); 
	  rv_errstrm << " or "; 
	  s1p->printType(rv_errstrm, NULL, true, 0); 
	  rv_errstrm << " \n";
	}
  }    
  
  return true;
}

///<summary>
/// Returns true if the two input functions have the same prototype. Part of a set of functions connected in mutual recursion, where the starting point is eq_type. 
///</summary>
bool RVTreeComp::eq_function_type(const FunctionType* s0pUser, const FunctionType* s1pUser) const
{
  CHK_EQ_NULL;
  if(DBG){s0pUser->printType(rv_errstrm, NULL, true, 0);rv_errstrm<<"\n";}
  Decl *comp0, *comp1;
  const FunctionType* s0p = s0pUser, *s1p = s1pUser;
  RECF(eq_type, subType );

  COMPF( nArgs );
  for(int i =0; i<s0p->nArgs; i++) {
	comp0 = s0p->args[i];
	comp1 = s1p->args[i];

	if( force_eq_comp_names ) {
	  if( comp0->name && comp1->name ) {
	if( comp0->name->name != comp1->name->name )
	  return false;
	  } 
	  // one of them is NULL - the other should be NULL too:
	  else if(comp0->name != comp1->name)
	return false;
	}

	if( !eq_type( comp0->form, comp1->form ))
	  return false;
  }

  return true;
}


bool RVTreeComp::eq_expr_vec(const ExprVector *s0pUser, const ExprVector *s1pUser) const
{
  CHK_EQ_NULL;

  const ExprVector *s0p = s0pUser, *s1p = s1pUser;

  if( s0p->size() != s1p->size() )
	return false;
  if( s0p->size() == 0 )
	return true;

  ExprVector::const_iterator  i,j;
  for (i=s0p->begin(), j=s1p->begin(); 
	   i != s0p->end(); i++,j++)
	if( !eq_expr( (*i), (*j) ) )
	  return false;

  return true;
}

///<summary>
/// see explanation in eq_type
///</summary>
bool RVTreeComp::eq_struct_def(const StructDef *s0pUser, const StructDef *s1pUser) const
{
  Decl *comp0, *comp1;
  bool ok_names;

  CHK_EQ_NULL; 
if(DBG){s0pUser->print(rv_errstrm,NULL,0);rv_errstrm<<" <-- 0 \n";
		s1pUser->print(rv_errstrm,NULL,0);rv_errstrm<<" <-- 1 \n";}

  const StructDef *s0p = s0pUser, *s1p = s1pUser;
  COMPF(_isUnion);

  /* we don't care the tag name as long as 
	 the structs/unions consist of the same field types. */ 
  
  /* Note that we ignore GccAttrib field (?) */

  /* we check equal component names only when force_eq_comp_names == true. */

  COMPF(nComponents);
  /* MAYBE we should only check struct containment (?)
	   (i.e in the loop: i<s0p->nComponents && i<s1p->nComponents
		and without COMPF(nComponents), only s0p->nComponents <= s1p->nComponents  )
  */

  /* if we closed a recursive loop: */
  if( s0p->assumeEq == s1p && s1p->assumeEq == s0p )
	return true; /* will be proved by assume-assert mechanism. */

  /* if it was related to some other type: */
  if( s0p->assumeEq != NULL || s1p->assumeEq != NULL )
	return false;  /* non compatible assumption. */ 

  /* assume the structs are equal for recursive eq(StructsDef*): */
  const_cast<StructDef*>(s0p)->assumeEq = s1p;
  const_cast<StructDef*>(s1p)->assumeEq = s0p;

  for(int i=0; i < s0p->nComponents; i++) {  
	comp0 = s0p->components[i];
	comp1 = s1p->components[i];
	
	while( comp0 && comp1 ) {

	  ok_names = true; // assume
	  if( force_eq_comp_names ) {
	if( comp0->name && comp1->name )
	  ok_names = (comp0->name->name == comp1->name->name);
	else // one of them is NULL - the other should be NULL too:
	  ok_names = (comp0->name == comp1->name);
	  }

	  if( !ok_names || !eq_type( comp0->form, comp1->form ) ) 
	  {
		  const_cast<StructDef*>(s0p)->assumeEq = const_cast<StructDef*>(s0p)->assumeEq = NULL;  // pop assumption.
	return false;
	  }
	  
	  comp0 = comp0->next;
	  comp1 = comp1->next;
	  /* both chains must end together: */
	  if( (comp0 == NULL) != (comp1 == NULL) ) {
		  const_cast<StructDef*>(s0p)->assumeEq = const_cast<StructDef*>(s1p)->assumeEq = NULL;  // pop assumption.
	return false;
	  }
	}
  }

  const_cast<StructDef*>(s0p)->assumeEq = const_cast<StructDef*>(s1p)->assumeEq = NULL;  // pop assumption.
  return true;
}


///<summary>
/// see explanation in eq_type
///</summary>
bool RVTreeComp::eq_member_op(const BinaryExpr* s0pUser, const BinaryExpr* s1pUser) const
{
  Type *st0 = NULL;   // struct or union types.
  Type *st1 = NULL;
  StructDef* strdef0 = NULL;
  StructDef* strdef1 = NULL;
  Decl* comp0 = NULL;
  Decl* comp1 = NULL;
  int ind0, ind1;

  CHK_EQ_NULL;
  if(DBG){s0pUser->print(rv_errstrm);rv_errstrm<<"\n";}
  const BinaryExpr* s0p = s0pUser, *s1p = s1pUser;
  COMPF( bOp );
  
  if( s0p->bOp != BO_Member && s0p->bOp != BO_PtrMember ) {
	rv_errstrm << "Attempt to compare non member expressions in eq_member_op() :";
	s0p->print(rv_errstrm); rv_errstrm << " \n";
	return false;
  }

  if( !s0p->leftExpr() || !s1p->leftExpr() ) {
	rv_errstrm << "Error: member expression with NULL left side, in eq_member_op().\n";
	return false;
  }

  st0 = s0p->leftExpr()->type;
  st1 = s1p->leftExpr()->type;

  if( s0p->bOp == BO_PtrMember ) {   // if its a pointer to struct/union
	
	/* check it is really pointers: */
	if( !st0 || !is_pointer(st0, "eq_member_op()", &st0) ) {
	  rv_errstrm << "PtrType expected in RVTreeComp::eq_member_op() (side 0) :";
	  s0p->print(rv_errstrm); rv_errstrm << " \n";
	  /* return false; */
	}       
	if( !st1 || !is_pointer(st1, "eq_member_op()", &st1) ) {
	  rv_errstrm << "PtrType expected in RVTreeComp::eq_member_op() (side 1) :";
	  s1p->print(rv_errstrm); rv_errstrm << " \n";
	  /* return false; */
	}
  }

  if( !eq_type(st0, st1) )
	return false;

  /* check the left sides are equal: */
  RECF(eq_expr, leftExpr() );

  const Variable *fld0 = static_cast<const Variable*>(s0p->rightExpr());
  const Variable *fld1 = static_cast<const Variable*>(s1p->rightExpr());

  if( st0 )
	strdef0 = get_struct_def(st0, "eq_member_op()");
  
  if( st1 )
	strdef1 = get_struct_def(st1, "eq_member_op()");

  if( strdef0 )
	comp0 = get_field_decl(strdef0, fld0);

  if( strdef1 )
	comp1 = get_field_decl(strdef1, fld1);

  if( (comp0 == NULL) != (comp1 == NULL) )
	return false;

  /* compare the types of the fields: */
  if( comp0 && comp1 && !eq_type(comp0->form, comp1->form) )
	return false;

  /* if left sides are equal structs: the fields must have same index in struct: */ 
  if( static_cast<const BaseType*>(st0)->typemask & BT_Struct ) {

	if( strdef0 && strdef1 ) {

	  ind0 = get_field_index( strdef0, fld0 );
	  ind1 = get_field_index( strdef1, fld1 );

	  if( ind0 < 0 || ind1 < 0 )
	return false;

	  if( ind0 != ind1 )
	return false;
	}
  } 
  else {  
	/* its a union - must compare by name (and type)
	   (we have no other way to distinguish fields in a union): */
	if( strdef0 && strdef1 ) {
	  if( !strdef0->lookup( fld0->name ) ||
	  !strdef1->lookup( fld1->name ) ||
	  fld0->name->name != fld1->name->name )
	return false;
	}
  }
  
  return true;
}

///<summary>
/// see explanation in eq_type
///</summary>
bool RVTreeComp::eq_sizeof(const SizeofExpr* s0pUser, const SizeofExpr* s1pUser) const
{
  /* Theoretically we can know sizeof value from program 
	 syntax so we don't have to have really the same expression
	 on both sides. But it is too complicated 
	 (and depends on GccAttrib) so for now we require
	 the expressions on both sides to be exactly the same.
	 !! We may use "type" field of the Expression class (check CBMC) <<=== !!
  */
  CHK_EQ_NULL;
  if(DBG) {s0pUser->print(rv_errstrm);rv_errstrm<<"\n";}
  const SizeofExpr* s0p = s0pUser, *s1p = s1pUser;
  
  if( s0p->sizeofType && s1p->sizeofType )
	RECF(eq_type, sizeofType )
  else if( s0p->expr && s1p->expr )
	RECF(eq_expr, expr )
  else
	/* neither field is non-NULL on both sides: */ 
	return false; 

  return true;
}

///<summary>
/// see explanation in eq_type
///</summary>
bool RVTreeComp::eq_stmt(const Statement* s0pUser, const Statement* s1pUser) const
{ 
  CHK_EQ_NULL;
  if(DBG){s0pUser->print(rv_errstrm,0);rv_errstrm<<"\n";}
  CHK_MARK;
  /* if they are marked equal but not to each other: */
  if( s0pUser->equalTo || s1pUser->equalTo )
	return false;

  const Statement* s0p = s0pUser, *s1p = s1pUser;
  COMPF( type );
  
  switch( s0p->type )
  {
	case ST_NullStemnt:   // The null statement.
	  break;

	case ST_DeclStemnt:
	case ST_TypedefStemnt:
	  // Ignore declrations,typedefs and their order - 
	  //   only the executable code should be equal,
	  //   vars (and their types) are compared upon occurrence in executable code.
	  //   decls may be related thru initializers which are checked as part of var equiv.
	  break;

	case ST_ExpressionStemnt: {
	  RETYPE2( ExpressionStemnt );
	  RECF(eq_expr, expression );
	  break;
	}

	case ST_IfStemnt: {
	  RETYPE2( IfStemnt );
	  RECF(eq_expr, cond );
	  RECF(eq_stmt, thenBlk );
	  RECF(eq_stmt, elseBlk );
	  break;
	}

	case ST_SwitchStemnt: {
	  RETYPE2( SwitchStemnt );
	  RECF(eq_expr, cond );
	  RECF(eq_stmt, block );
	  break;
	}
	  
	case ST_ForStemnt: {
	  RETYPE2( ForStemnt );
	  RECF(eq_expr, init );
	  RECF(eq_expr, cond );
	  RECF(eq_expr, incr );
	  RECF(eq_stmt, block );
	  break;
	}

	case ST_WhileStemnt: {
	  RETYPE2( WhileStemnt );
	  RECF(eq_expr, cond );
	  RECF(eq_stmt, block );
	  break;
	}

	case ST_DoWhileStemnt: {
	  RETYPE2( DoWhileStemnt );
	  RECF(eq_expr, cond );
	  RECF(eq_stmt, block );
	  break;
	}

	case ST_ContinueStemnt:
	case ST_BreakStemnt:
	  break;

	case ST_GotoStemnt: {
	  RETYPE2( GotoStemnt );
	  /* check or mark pointed statements as equal: */
	  mark_equal_labels(const_cast<Symbol*>(s0p->dest), const_cast<Symbol*>(s1p->dest) );
	  break;
	}
	  
	case ST_ReturnStemnt: {
	  RETYPE2( ReturnStemnt );
	  RECF(eq_expr, result );
	  break;
	}

	case ST_Block: 
	  if( !eq_block( static_cast<const Block*>(s0p), static_cast<const Block*>(s1p) ) )
		return false;
	  break;

	default:
	  rv_errstrm << "Unable to compare Statement (side 0): ";
	  s0p->print(rv_errstrm, 0);  rv_errstrm << " \n";
	  return false;
  }

  MARKEQ(Statement); // mark the statements on both sides as equal

  return true;
}


bool RVTreeComp::eq_block(const Block* s0pUser, const Block* s1pUser) const
{
  Statement *st0, *st1;
  CHK_EQ_NULL;
  if(DBG){s0pUser->print(rv_errstrm,0);rv_errstrm<<"\n";}

  st0 = s0pUser->head;
  st1 = s1pUser->head;

  /* ignore var declaration and typedef statements: */
  while( st0 && (st0->type == ST_DeclStemnt || st0->type == ST_TypedefStemnt
				 || st0->type == ST_NullStemnt) )
	st0 = st0->next;
  while( st1 && (st1->type == ST_DeclStemnt || st1->type == ST_TypedefStemnt
				 || st1->type == ST_NullStemnt) )
	st1 = st1->next;

  while( st0 && st1 ) 
  {
	if( !eq_stmt( st0, st1 ))
	  return false;

	st0 = st0->next;
	st1 = st1->next;
  }

  // if one block contains more statements than the other:
  if( st0 || st1 )
	return false;

  return true;
}


bool RVTreeComp::mark_equal_labels(Symbol* s0pUser, Symbol* s1pUser) const
/* check the statements pointed by labels on both sides are equal: */
{
  CHK_EQ_NULL;

  SymEntry *e0p = s0pUser->entry;
  SymEntry *e1p = s1pUser->entry;

  if( !e0p || !e1p || !e0p->u2LabelPosition || !e1p->u2LabelPosition )
	return false;  /* undefined label. */
  
  /* if they are already marked equal: */
  if( e0p->equalTo || e1p->equalTo )
	/* return true if they are equal to *each other*: */
	return (e0p->equalTo == e1p && e1p->equalTo == e0p);

  /* Assume here that the entries are equal to prevent infinite recursion: */
  e0p->equalTo = e1p; e1p->equalTo = e0p;

  /* check pointed statements are the same: */
  if( !eq_stmt( e0p->u2LabelPosition, e1p->u2LabelPosition ) ) {
	e0p->equalTo = e1p->equalTo = NULL;   // rollback the assumption
	return false;
  }

  /* Note that if we didn't reach the statements yet and they are equal
	 but not at the same place in the program - they will be marked to point 
	 to each other by their equalTo but later (when we reach one of them in the 
	 comparison order) we will notice that one side's equalTo doesn't
	 point to the other and the check will fail as expected.
  */

  return true;
}


bool RVTreeComp::eq_enum_idents(const SymEntry* e0p, const SymEntry* e1p) const
{
  if( !e0p || !e1p )
	return false;
  
  if( !e0p->IsEnumConst() || !e1p->IsEnumConst() )
	return false;

  if( !e0p->u2EnumDef || !e1p->u2EnumDef )
	return false;

  Location l(__LINE__,0,std::string(__FILE__));
  IntConstant start_val(0,false,l); // enum values by default start from 0.
  const Expression *base0 = &start_val;   // base constants of the relevant enum counts
  const Expression *base1 = &start_val;
  unsigned rel_ind0, rel_ind1;  // relative (to base) ident indexes - in its enum def

  if( !get_enum_val(e0p, base0, rel_ind0) || !get_enum_val(e1p, base1, rel_ind1) )
	return false;

  /* if we can explicitely calculate the enum ident value - do it */
  if( base0->etype == ET_Constant && base1->etype == ET_Constant &&
	  ( static_cast<const Constant*>(base0)->ctype == CT_Int || static_cast<const Constant*>(base0)->ctype == CT_UInt ) &&
	  ( static_cast<const Constant*>(base1)->ctype == CT_Int || static_cast<const Constant*>(base1)->ctype == CT_UInt ) )
  {
	long long v0, v1;
	if( static_cast<const Constant*>(base0)->ctype == CT_Int )
	  v0 = static_cast<const IntConstant*>(base0)->lng;
	else
	  v0 = static_cast<const UIntConstant*>(base0)->ulng;

	if( static_cast<const Constant*>(base1)->ctype == CT_Int )
	  v1 = static_cast<const IntConstant*>(base1)->lng;
	else
	  v1 = static_cast<const UIntConstant*>(base1)->ulng;

	return( (v0 + rel_ind0) == (v1 + rel_ind1) );
  }
	  
  if( !eq_expr(base0, base1) )
	return false;

  if( rel_ind0 != rel_ind1 ) 
	return false;

  return true;
}


bool RVTreeComp::get_enum_val(const SymEntry* e0p, PC_Expression& out_base, unsigned& out_rel_ind) const
{
  if( !e0p || !e0p->u2EnumDef )
	return false;

  EnumDef* def = e0p->u2EnumDef;
  out_rel_ind = 0;

  for(int i = 0; i < def->nElements; i++, out_rel_ind++) {
	if( def->values[i] ) {
	  out_base = def->values[i];
	  out_rel_ind = 0;
	}
	if( def->names[i]->name == e0p->name )
	  return true;
  }

  rv_errstrm <<"Error: can't find ident \""<< e0p->name <<"\" in its (?) enum definition:\n  ";
  def->print(rv_errstrm, NULL, 0); rv_errstrm<<"\n";
  
  return false;
}
