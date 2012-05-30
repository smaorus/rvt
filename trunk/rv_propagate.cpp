#include <sstream>
#include <rv_consts.h>
#include <string>
#include <rv_error.h>
#include <rv_macros.h>
#include <rv_treecomp.h>
#include <rv_propagate.h>
#include "rv_side.h"
#include "rv_parse.h"
#include "rv_etc.h"

using namespace std;

#define RV_SECTION RV_SEC_PROPAGATE


/*  RVEnumDefCorrector  */
/* ==================== */
/* class RVEnumDefCorrector - corrects enum entries for which no value is
 *                            assigned. It assigns a proper constant value.
 */
class RVEnumDefCorrector : public RVWalk {
public:
	RVBoolStatus correctEnumDefs(Project*);
	virtual bool process(EnumDef* s0p);
    virtual bool process_basetype(BaseType* s0p);

	virtual bool process(Statement* s0p) { return go(s0p); }
	virtual bool process(Symbol* s0p) { return s0p == NULL || go(s0p); }
	virtual bool process(Expression* s0p) { return go(s0p); }
    virtual bool process(Type* s0p) { return go(s0p); }
    virtual bool process(StructDef* s0p) { return go(s0p); }
    virtual bool process_function_type(FunctionType* it) { return true; }

    virtual bool try_replace(Symbol**)   { return true; }
    virtual bool try_replace(Expression**){ return true; }
};

bool RVEnumDefCorrector::process(EnumDef* s0p) {
	static const char *where_ = "RVEnumDefCorrector::go(EnumDef*)";
	CHK_NULL(where_);

	for(int i=0; i < s0p->nElements; i++) {
		if (s0p->values[i] == NULL) {
			if (i == 0)
				s0p->values[i] = new IntConstant(0, false, NoLocation);
			else {
				if (s0p->values[i-1]->etype == ET_Constant) {
					Expression *c = s0p->values[i-1]->dup();
					switch(static_cast<Constant *>(c)->ctype) {
					case CT_Char:
						++static_cast<CharConstant *>(c)->ch;
						break;
					case CT_Int:
						++static_cast<IntConstant *>(c)->lng;
						break;
					case CT_UInt:
						++static_cast<UIntConstant *>(c)->ulng;
						break;
					default:
						fatal_error("Enum value is neither char, int nor uint constant", false);
					}

					s0p->values[i] = c;
				}
				else
					fatal_error("Enum value is not a constant", false);
			}
		}

		if (s0p->names[i]->entry->uEnumValue == NULL)
		    s0p->names[i]->entry->uEnumValue = s0p->values[i];
	}

	return true;
}

bool RVEnumDefCorrector::process_basetype(BaseType* s0p) {
	static const char* where_ = "RVEnumDefCorrector::process_basetype";
	CHK_NULL(where_);
	if(DBG) {s0p->printType(rv_errstrm, NULL, true, 0);rv_errstrm<<"\n";}

	Type* realtp = real_type(s0p, where_);
	if( realtp != s0p )
		return process(realtp);

	if( (s0p->typemask & (BT_Struct|BT_Union)) && s0p->stDefn )
		PROC( stDefn )
	else if( (s0p->typemask & BT_Enum) && s0p->enDefn )
		PROC( enDefn );

	/* Don't process tags - processed at their the type declaration statement. */
	return true;
}

RVBoolStatus RVEnumDefCorrector::correctEnumDefs(Project* pt) {
	CHK_NULL_BOOL(pt, "pt in RVEnumDefCorrector::correctEnumDefs()");
	RVBoolStatus ret(true);
	Statement* first_st = get_glob_stemnt(pt);
	decl_to_symbol = false;

	for(Statement* st = first_st; st; st = st->next)
		ret.assign( process(st) && ret , __FUNCTION__, DBG);

	return ret;
}


/* RVTypeProp functions: */
/*=======================*/

const BaseTypeSpec RVTypeProp::ArithMask = (BT_Bool|BT_Char|BT_Short|BT_Int|BT_Int64|BT_Int32|
						BT_Int16|BT_Int8|BT_Long|BT_LongLong|
						BT_Signed|BT_UnSigned|BT_Enum|BT_Float|BT_Double);


const BaseTypeSpec RVTypeProp::IntMask = (BT_Bool|BT_Char|BT_Short|BT_Int|BT_Int64|BT_Int32|
					  BT_Int16|BT_Int8|BT_Long|BT_LongLong|
					  BT_Signed|BT_UnSigned|BT_Enum);

RVTypeProp::RVTypeProp(const char *_where)
  : RVWalk(true), m_inTypedef(false), m_project(NULL)
{
	set_where(_where);
}

RVBoolStatus RVTypeProp::process_all(Project* pt, const RVSide& side) {
  if(DBG) rv_errstrm << "Start RVTypeProp::process_all() \n";

  CHK_NULL_BOOL(pt, "pt in RVTypeProp::process_all()");

  set_where("RVTypeProp::process_all()");
  m_project = pt;

  RVBoolStatus ret(true);
  Statement* first_st = get_glob_stemnt(pt);
  
  for(Statement* st = first_st; st; st = st->next)
      ret.assign( processStatement(st, side) && ret , __FUNCTION__, DBG);

  if(DBG) rv_errstrm << "Finish RVTypeProp::process_all() \n";
  m_project = NULL;
  m_newFuncPtrSubstitutions.clear();

  RVEnumDefCorrector().correctEnumDefs(pt);

  return ret;
}

bool RVTypeProp::processStatement(Statement* st, const RVSide& side) {
	std::string decl_where;

	if( st->isDeclaration() || st->isTypedef() ) {
	  DeclStemnt* dst = static_cast<DeclStemnt*>(st);
	  if( dst->decls.size() > 0 && dst->decls[0] && dst->decls[0]->name ) {
		decl_where = "Declaration of " + dst->decls[0]->name->name +
	                 " on side " + side.toString();
		set_where(decl_where.data());
	  }
	}
	else if( st->isFuncDef() ) {
	  FunctionDef* fst = static_cast<FunctionDef*>(st);
	  if( fst->decl && fst->decl->name )  {
		decl_where = fst->decl->name->name + " on side " + side.toString();
		set_where(decl_where.data());
	  }
	}

	return process(st);
}

bool RVTypeProp::process(Statement* s0p)    
{
  /* for Decls we need to process their form (if enum) and initializer: */
  if( s0p->type == ST_DeclStemnt || s0p->type == ST_TypedefStemnt ) {
	RETYPE( DeclStemnt );
	for(unsigned i = 0; i < s0p->decls.size(); i++)
	  PROC( decls[i] );
	return true;
  }

  return RVWalk::process(s0p); // otherwise just process it
}


bool RVTypeProp::process(Expression* s0p) {
	CHK_NULL("RVTypeProp::process(Expression*)");

	if (DBG) {
		s0p->print(rv_errstrm);
		rv_errstrm << "\n";/*DEL*/
	}

	switch (s0p->etype) {
	case ET_VoidExpr: // No value
		return true;

	case ET_Constant:
		if (!process_const((Constant*) s0p))
			return false;
		break;

	case ET_Variable: {
		RETYPE( Variable );
		if (!s0p->name || !s0p->name->entry) {
			rv_errstrm << "Error: RVTypeProp::process(): symbol "
					<< (s0p->name ? s0p->name->name.data() : "UNKNOWN")
					<< " has no hash entry (?).\n at: ";
			s0p->location.printLocation(rv_errstrm);
			rv_errstrm << "\n";
		}

		SymEntry* se = s0p->name->entry;

		/* if we don't know the exact value of the constant: */
		if (se && se->IsEnumConst() && !se->uEnumValue)
			s0p->type = enum_type(se, s0p->location);
		else
			s0p->type = get_symbol_type(s0p->name, where);
		break;
	}

	case ET_FunctionCall: {
		RETYPE( FunctionCall );
		PROC( function );
		PROC( args );

		if (s0p->function) {
			Type* ftp = real_type(s0p->function->type, where);

			if (!ftp || !ftp->isFunction())
				ftp = getFunctionFromFuncPtr(ftp);

			if (!ftp || !ftp->isFunction()) {
				rv_errstrm << "Warning: not FunctionType type of a call:\n  ";
				s0p->print(rv_errstrm);
				rv_errstrm << "\n  at: ";
				s0p->location.printLocation(rv_errstrm);
				rv_errstrm << "\n  type: ";
				ftp->printType(rv_errstrm, NULL, true, 0);
				rv_errstrm << "\n";
				break;
			}
			s0p->type = ((FunctionType*) ftp)->subType;
		}
		break;
	}

	case ET_AssignExpr:
	case ET_RelExpr:
		rv_errstrm
				<< "Internal: ET_AssignExpr or ET_RelExpr was unused in ctool "
				<< "- unexpected Expression::etype = " << s0p->etype << " .\n";
		return false;

	case ET_UnaryExpr: {
		if (!process_unary((UnaryExpr*) s0p))
			return false;
		break;
	}

	case ET_BinaryExpr:
		if (!process_binary((BinaryExpr*) s0p))
			return false;
		break;

	case ET_TrinaryExpr: { // x ? y : z
		RETYPE( TrinaryExpr );
		TRY_PROC( condExpr() );
		TRY_PROC( trueExpr() );
		TRY_PROC( falseExpr() );

		Type* ltp = s0p->trueExpr() ? s0p->trueExpr()->type : NULL;
		Type* rtp = s0p->falseExpr() ? s0p->falseExpr()->type : NULL;

		RVTreeComp comp(false, true);
		if (ltp == rtp || comp.eq_type(ltp, rtp)) // if they are the same type
			s0p->type = ltp;
		/* if one operand is pointer and the other is NULL: */
		else if (is_pointer(ltp, where) && is_const_null(s0p->falseExpr()))
			s0p->type = ltp;
		else if (is_const_null(s0p->trueExpr()) && is_pointer(rtp, where))
			s0p->type = rtp;
		else // otherwise they may be converted to a common Arithmetic type.
		if (!ArithOpTypeConv(s0p, ltp, rtp))
			return false;

		break;
	}

	case ET_CastExpr: { // (type) x
		RETYPE( CastExpr );
		TRY_PROC( expr );
		s0p->type = s0p->castTo;
		break;
	}

	case ET_SizeofExpr: { // sizeof(type) -or- sizeof(expr)
		RETYPE( SizeofExpr );
		TRY_PROC( expr );
		BaseType* bt = new BaseType(BT_Int | BT_UnSigned);
		// bt->qualifier = TQ_Const; - not always - because of variable-length arrays
		s0p->type = bt;
		break;
	}

	case ET_IndexExpr: { // x[y]...[]
		RETYPE( IndexExpr );
		PROC( array );
		PROC( _subscript );

		Type* atp = real_type(s0p->array->type, where);
		if (atp) {
			if (atp->isPointer())
				s0p->type = ((PtrType*) atp)->subType;
			else if (atp->isArray())
				s0p->type = ((ArrayType*) atp)->subType;
			else {
				rv_errstrm << "Error: bad array type: ";
				atp->printType(rv_errstrm, NULL, true, 0);
				rv_errstrm << "\n  at: ";
				s0p->location.printLocation(rv_errstrm);
				rv_errstrm << "\n";
			}
		}
		break;
	}

	default:
		rv_errstrm << "Unrecognized Expression: ";
		s0p->print(rv_errstrm);
		rv_errstrm << " \n";
		return false;
	}

	if (!s0p->type) {
		rv_errstrm << "Warning: unable to determine the type of: \n  ";
		s0p->print(rv_errstrm);
		rv_errstrm << "\n  at: ";
		s0p->location.printLocation(rv_errstrm);
		rv_errstrm << "\n";
	}

	//if(DBG) { rv_errstrm<<"Type: ";
	//if( s0p->type ) s0p->type->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";/*DEL*/}

	return true;
}

bool RVTypeProp::CheckIntTypes(BinaryExpr* s0p, const char* op_name)
{
  Type* ltp = real_type(s0p->leftExpr()->type, where);
  Type* rtp = real_type(s0p->rightExpr()->type, where);

  if( !is_basetype(ltp, IntMask) || !is_basetype(rtp, IntMask) ) {
	rv_errstrm << "Error: operands of "<< op_name <<" must be of ineger type:\n  ";
	s0p->print(rv_errstrm); rv_errstrm<<"\n  at: ";	
	s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
	rv_errstrm<<"  left  type: "; ltp->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";
	rv_errstrm<<"  right type: "; rtp->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";
	return false;
  }

  return true;
}


bool RVTypeProp::process_binary(BinaryExpr* s0p)
{
  Type *ltp = NULL; 
  Type *rtp = NULL; 

  PROC( leftExpr() );

  /* right side type of member operation is detected in process_member_op(): */
  if( s0p->bOp != BO_Member && s0p->bOp != BO_PtrMember ) {
	PROC( rightExpr() );

	ltp = s0p->leftExpr()->type;
	rtp = s0p->rightExpr()->type;
	
	if( !ltp || !rtp ) {
	  rv_errstrm << "Error: unknown (NULL) operand type, in: \n  ";
	  s0p->print(rv_errstrm); rv_errstrm<<"\n  at: ";	
	  s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
	  return true;  // <<=== MAYBE false;
	}
  }

  switch( s0p->bOp ) 
  {
	case BO_Minus:       // -
	case BO_Plus: {      // +
	  Type  *lsubt, *rsubt; /* subType for each side if pointer */
	  bool left_is_pointer  = is_pointer(ltp, where, &lsubt);
	  bool right_is_pointer = is_pointer(rtp, where, &rsubt);

	  if( left_is_pointer && right_is_pointer ) {
	if( s0p->bOp == BO_Minus )
	  s0p->type = new BaseType(BT_Int | BT_Signed);
	else {
	  rv_errstrm << "Error: invalid two pointer operands to binary '+', at:";
	  s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
	  return false;
	}
	break;
	  }

	  ltp = real_type(ltp, where);
	  rtp = real_type(rtp, where);

	  if( left_is_pointer && is_basetype(rtp, IntMask) ) {
	s0p->type = ltp;
	break;
	  } 
	  else if( right_is_pointer && is_basetype(ltp, IntMask) ) {
	s0p->type = rtp;
	break;
	  }

	  if( !ArithOpTypeConv(s0p, ltp, rtp) )
	return false;
	  break;
	}

	case BO_Mod:         // %
	  if( !CheckIntTypes(s0p,"'%'") )
	break;
	  /* fall thru */
	case BO_Mult:        // *
	case BO_Div:         // /
	  if( !ArithOpTypeConv(s0p, ltp, rtp) )
	return false;
	  break;

	case BO_BitAnd:      // &
	case BO_BitXor:      // ^
	case BO_BitOr:       // |
	  if( !CheckIntTypes(s0p,"bitwise operation") )
	break;
	  if( !ArithOpTypeConv(s0p, ltp, rtp) )
	return false;
	  break;

	case BO_And:         // &&
	case BO_Or:          // ||
	case BO_Rel:
	  s0p->type = new BaseType(BT_Bool);
	  break;

	case BO_Comma:       // x,y 
	  s0p->type = rtp;
	  break;

	case BO_Member:
	case BO_PtrMember:
	  /* special treatment to union or struct members: */
	  if( !process_member_op( s0p ) )
		return false;
	  break;
	  
	case BO_Shl:         // <<
	case BO_Shr:         // >>
	  if( !CheckIntTypes(s0p,"bitwise shift operation") )
	break;
	  /* fall thru */      
	case BO_Assign:
	  s0p->type = ltp;
	  break;

	default:
	  rv_errstrm << "Unrecognized Binary Expression: ";
	  s0p->print(rv_errstrm);  rv_errstrm << " \n";
	  return false;
  }

  return true;
}


bool RVTypeProp::process_unary(UnaryExpr* s0p)
{
  PROC( operand() );

  switch( s0p->op() )
  {
	case UO_Plus:           // +
	case UO_Minus:          // -
	case UO_BitNot:         // ~
	case UO_PreInc:         // ++x
	case UO_PreDec:         // --x
	case UO_PostInc:        // x++
	case UO_PostDec:        // x--
	  s0p->type = s0p->operand()->type;
	  break;

	case UO_Not:            // !
	  s0p->type = new BaseType(BT_Bool);
	  break;

	case UO_AddrOf: {       // &
	  PtrType* ret = new PtrType();
	  ret->subType = s0p->operand()->type;
	  s0p->type = ret;
	  break;
	}

	case UO_Deref: {        // *
	  Type* otp = real_type(s0p->operand()->type, where);
	  if( otp ) {
	if( otp->isPointer() )
	  s0p->type = ((PtrType*)otp)->subType;
	else if( otp->isArray() )
	  s0p->type = ((ArrayType*)otp)->subType;
	else if( otp->isFunction() )  
	  s0p->type = otp;  // (*pf)(arg) is the same as op(arg)
	else {
	  rv_errstrm << "Error: bad deref operand type: ";
	  otp->printType(rv_errstrm, NULL, true, 0);
	  rv_errstrm<<"\n  at: "; s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
	}
	  }
	  break;
	}

	default:
	  rv_errstrm << "Unrecognized Unary Expression: ";
	  s0p->print(rv_errstrm);  rv_errstrm << " \n";
	  return false;
  }

  return true;
}


bool RVTypeProp::process_const(Constant* s0p)
{
  CHK_NULL("RVTypeProp::process_const()"); 

  /* if it already has type: */
  if( s0p->type )
	return true;

if(DBG){s0p->print(rv_errstrm);rv_errstrm<<"\n";/*DEL*/}

  BaseType* bt = NULL; 

  switch( s0p->ctype )
  {
	case CT_Char:
	  bt = new BaseType(BT_Char | BT_UnSigned);
	  bt->qualifier = TQ_Const;
	  s0p->type = bt;
	  break;

	case CT_Int: {
	  RETYPE( IntConstant );
	  bt = new BaseType((s0p->L ? BT_Long : BT_Int) | BT_Signed);
	  bt->qualifier = TQ_Const;      
	  s0p->type = bt;
	  break;
	}

	case CT_UInt: {
	  RETYPE( UIntConstant );
	  bt = new BaseType((s0p->L ? BT_Long : BT_Int) | BT_UnSigned);
	  bt->qualifier = TQ_Const;
	  s0p->type = bt;
	  break;
	}

	case CT_Float:
	  bt = new BaseType(BT_Double);
	  bt->qualifier = TQ_Const;
	  s0p->type = bt;
	  break;

	case CT_String: {
	  PtrType* ret = new PtrType(TQ_Const);
	  ret->subType = new BaseType(BT_Char);
	  s0p->type = ret;
	  break;
	}

	case CT_Enum: {
	  RETYPE( EnumConstant );
	  SymEntry* se = s0p->name->entry;
	  s0p->type = enum_type(se, s0p->location);
	  break;
	}

	case CT_Array: {          // For an array initializer
	  RETYPE( ArrayConstant );
	  PROC( items );
	  if( s0p->items.size() > 0 && s0p->items[0] && s0p->items[0]->type ) {
	UIntConstant* size = new UIntConstant( s0p->items.size(), false, s0p->location);
	ArrayType* ret = new ArrayType( size );
	ret->subType = s0p->items[0]->type;
	s0p->type = ret;
	  }
	  break;
	}

	default:
	  rv_errstrm << "Unable to walk Constant: ";
	  s0p->print(rv_errstrm);  rv_errstrm << " \n";
	  return false;
  }
	
  return true;
}


bool RVTypeProp::process(ExprVector& s0p)
{
  ExprVector::const_iterator  i;
  FORVEC(i,s0p)
	if( !process(*i) )
	  return false;

  return true;
}

bool RVTypeProp::process(Decl* s0p) {
	if (s0p->isTypedef())
		m_inTypedef = true;
	bool result = go(s0p);
	m_inTypedef = false;
	return result;
}

static const string RVT_FuncPtrSubst("rvt_FuncPtrSubst_");

bool RVTypeProp::isPointerToFunctionSubstitutingType(Type *typePtr) {
	if (!typePtr->isBaseType() ||
		!isDirectPointerToFunction(real_type(typePtr, "RVTypeProp::isPointerToFunctionSubstitutingType")))
		return false;
	BaseType *bt = static_cast<BaseType*>(typePtr);
	return bt->typeName != NULL &&
		   bt->typeName->name.find(RVT_FuncPtrSubst) == 0;
}

bool RVTypeProp::try_replace(Type** s0p) {
	if (s0p == NULL || *s0p == NULL || m_inTypedef)
		return true;

	FunctionType *fTypePtr = NULL;
	if (isDirectPointerToFunction(*s0p, &fTypePtr)) {
		ostringstream buf;
		Symbol dummy;
		fTypePtr = static_cast<FunctionType*>(fTypePtr->dup());
		for (int i = 0; i < fTypePtr->nArgs; ++i)
			fTypePtr->args[i]->name = NULL;
		fTypePtr->printType(buf, &dummy, true, 0);
		dummy.name = buf.str();
		dummy.name.insert(0, RVT_FuncPtrSubst);
		Utils::replaceCharInString(dummy.name, ' ', "_");
		Utils::replaceCharInString(dummy.name, ',', "");
		Utils::replaceCharInString(dummy.name, '(', "");
		Utils::replaceCharInString(dummy.name, ')', "");
		Utils::replaceCharInString(dummy.name, '*', "ptr");

		RVFuncPtrSubstitutionMap::iterator found = m_newFuncPtrSubstitutions.find(dummy.name);
		if (found != m_newFuncPtrSubstitutions.end())
			*s0p = found->second;
		else {
			Decl *typedefDecl = mk_global_decl(m_project, *s0p, dummy.name, TypedefEntry);
			BaseType *substType = new BaseType(BT_UserType);
			substType->typeName = typedefDecl->name->dup();
			const Location l(0, 0, "Function Pointer Substitution");
			TypedefStemnt *declStmt = new TypedefStemnt(l);
			declStmt->addDecl(typedefDecl);
			m_project->Parse_TOS->transUnit->insert(declStmt);
			m_newFuncPtrSubstitutions[dummy.name] = substType;
			*s0p = substType;
		}
	}
	return true;
}

bool RVTypeProp::process_member_op(BinaryExpr* s0p)
{
  Type *st0 = NULL;   // struct or union types.
  Variable *fld = NULL;
  StructDef* strdef = NULL;
  Decl* fld_decl = NULL;

  CHK_NULL("RVTypeProp::process_member_op(BinaryExpr*)"); 
if(DBG){s0p->print(rv_errstrm);rv_errstrm<<"\n";/*DEL*/} 

  st0 = real_type(s0p->leftExpr()->type, where);

  if( s0p->bOp == BO_PtrMember ) {   // if its an arrow (->) operation
	if( !st0 || !is_pointer(st0, where, &st0) ) {
	  rv_errstrm << "Warning: PtrType expected in RVTypeProp::process_member_op():";
	  s0p->print(rv_errstrm); rv_errstrm << " \n";
	  return false;
	}
  }

  if( st0 && !(strdef = get_struct_def(st0, where)) )
	return false;

  fld = (Variable*)s0p->rightExpr();
  fld_decl = get_field_decl(strdef, fld);
  if( !fld_decl )
	return false;

  CHK_NULL1(fld_decl->form, "field type in RVTypeProp::process_member_op()");

if(DBG){rv_errstrm<<"Set field type to: "; 
 fld_decl->form->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";} 

  /* fix components and result types: */
  s0p->type = fld->type = fld_decl->form;

  /* fix the SymEntry of fld to Decl's one: */
  if( !fld->name->entry || !fld->name->entry->IsComponentDecl() ) {
	fld->name->entry = mk_component(fld->name->name, fld_decl, strdef);
	fld->name->entry->scope = NULL;
  }

  return true;
}

Type* RVTypeProp::enum_type(SymEntry* se, Location& location)
{
  if( !se || !se->IsEnumConst() || !se->u2EnumDef ) {
	rv_errstrm << "Error: unknown enum definition of enum constant \""<<
	  se->name <<"\" .\n  at: ";
	location.printLocation(rv_errstrm); rv_errstrm<<"\n";
	return NULL;
  }
  
  BaseType* bt = new BaseType( se->u2EnumDef->dup() );
  bt->qualifier = TQ_Const;
  return bt;
}


bool RVTypeProp::ArithOpTypeConv(Expression* s0p, Type* ltp, Type* rtp)
  // after ANSI C99 standard documentation (pages 44-45).
{
  CHK_NULL1(s0p && ltp && rtp, "RVTypeProp::ArithOpTypeConv()");

  ltp = real_type(ltp, where);
  rtp = real_type(rtp, where);

  if( is_basetype(ltp, ArithMask) && is_basetype(rtp, ArithMask) ) {
	
	BaseTypeSpec lmask = ((BaseType*)ltp)->typemask;
	BaseTypeSpec rmask = ((BaseType*)rtp)->typemask;
	BaseTypeSpec mask = ArithOpTypeConvMask(lmask, rmask, s0p->location);
	
	if( mask == lmask ) 
	  s0p->type = ltp;
	else if( mask == rmask )
	  s0p->type = rtp;
	else
	  s0p->type = new BaseType(mask);
	return true;
  }

  rv_errstrm << "Warning: incompatible types of left and right parts of arithmetic expession:\n  ";
  s0p->print(rv_errstrm); rv_errstrm<<"\n";
  rv_errstrm<<"  left  type: "; ltp->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";
  rv_errstrm<<"  right type: "; rtp->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";
  rv_errstrm<<"  at: "; s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
  return false;
}


BaseTypeSpec RVTypeProp::ArithOpTypeConvMask(BaseTypeSpec ltm, BaseTypeSpec rtm, Location& l)
{
  if( !(ltm & ArithMask) ) {
	rv_errstrm << "Warning: ArithOpTypeConvMask(): non arithmetic type mask "
		   << ltm << " on left side of expression in \""<< where <<"\" at: ";
	l.printLocation(rv_errstrm); rv_errstrm<<"\n";
	return rtm;
  }

  if( !(rtm & ArithMask) ) {
	rv_errstrm << "Warning: ArithOpTypeConvMask(): non arithmetic type mask "
		   << rtm << " on right side of expression in \""<< where <<"\" at: ";
	l.printLocation(rv_errstrm); rv_errstrm<<"\n";
	return ltm;
  }
  
  bool left_is_float  = (ltm & (BT_Double | BT_Float)) != 0;
  bool right_is_float = (rtm & (BT_Double | BT_Float)) != 0;
  int  left_size  = sizeof_base_type(ltm);
  int  right_size = sizeof_base_type(rtm);

  if( (ltm & BT_Bool) && (rtm & BT_Bool) ) 
	return (BT_Int|BT_UnSigned);
  else if( ltm & BT_Bool )
	return rtm;
  else if( rtm & BT_Bool )
	return ltm;

  ltm = fix_int_mask(ltm);
  rtm = fix_int_mask(rtm);

  if( ltm == rtm )
	return ltm;

  if( left_is_float && right_is_float ) 
	return((right_size > left_size) ? rtm : ltm);
  else if( left_is_float )
	return ltm;
  else if( right_is_float )
	return rtm;

  if( left_size == right_size ) {
	/* if int type sizes are equal - convert to the unsigned: (ANSI C99) */
	if( rtm & BT_UnSigned )
	  return rtm;
	return ltm;
  }

  /* otherwise take the bigger one: */
  return((right_size > left_size) ? rtm : ltm);
}





bool RVTypePropIgnoreNondet::process(Expression* s0p) {
  CHK_NULL("RVTypePropIgnoreNondet::process(Expression*)");

  if (s0p->etype == ET_FunctionCall) {
	  RETYPE( FunctionCall );
	  if (s0p->function->etype == ET_Variable &&
	  	  ignored(static_cast<Variable*>(s0p->function)) ) 
      {
        return RVTypeProp::process(s0p->args);
      }
  }

  return RVTypeProp::process(s0p);
}

bool RVTypePropIgnoreNondet::ignored(const Variable* fv) {
  static const string nondetPrefix("nondet_");
  return fv->name->entry == NULL &&
		 (Utils::stringBeginsWith(fv->name->name, nondetPrefix) ||
		  RVParse::ignore_func(fv->name->name) );
}






void RVDequalifier::dequalify(Project *pt, const RVSide& side) {
	decl_to_symbol = true;
	RVBoolStatus ret(true);
	Statement* first_st = get_glob_stemnt(pt);

	for(Statement* st = first_st; st; st = st->next)
		ret.assign( RVWalk::process(st) && ret , __FUNCTION__, DBG);
}

bool RVDequalifier::try_replace(Type** s0p) {
	if (s0p == NULL || *s0p == NULL)
		return true;

	if ((*s0p)->isBaseType() &&
		static_cast<BaseType*>(*s0p)->qualifier != TQ_None)
	{
		*s0p = (*s0p)->dup();
		static_cast<BaseType*>(*s0p)->qualifier = TQ_None;
	}
	return true;
}
