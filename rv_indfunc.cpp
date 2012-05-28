#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_parse.h>
#include <rv_treecomp.h> 
#include <rv_propagate.h>
#include <rv_temps.h> 
#include <rv_indfunc.h>

#include <sstream>

#include <ctool/stemnt.h>

#define RV_SECTION RV_SEC_REPLACE  /* ?? */



static std::string add_num(std::string name, int i)
{
  std::ostringstream ret;
  ret << name << i;
  return ret.str();
}


const char* RVFuncClass::TYPE_PREFIX = "enFI_";
const char* RVFuncClass::ENUM_PREFIX = "FI_";
const char* RVFuncClass::HUB_SUFFIX  = "_hub";
const char* RVFuncClass::FI_ARG_NAME = "func_index";


RVFuncClass::RVFuncClass(Type* _type, int _side)
{
  type = (FunctionType*)real_type(_type, "RVFuncClass::RVFuncClass()");
  if( !type || !type->isFunction() ) {
    if( type ) {
      rv_errstrm << "RVFuncClass::RVFuncClass(): bad type:\n  ";
      type->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";
    }
    fatal_error("Internal: attempt to create RVFuncClass with non-function type !\n", false);
  }

  side = _side;
  tp_func_ind_enum = NULL;
  hub_decl = NULL;
}

RVFuncClass::~RVFuncClass()
{
  funcs.delete_all();
  defs.delete_all();
  delete hub_decl;
  /* the types are deleted with the parsetree */
}


void RVFuncClass::sort_symbol_vectors()
{
  funcs.unique_sort();
  defs.unique_sort();
}


std::string RVFuncClass::func_ind_name(std::string& func_name)
{ return std::string(ENUM_PREFIX) + func_name; }


int RVFuncClass::add_enum_func_ind(EnumDef* def, std::string& func_name)
{
  CHK_NULL1(def, "def in RVFuncClass::add_enum_func_ind()");

  std::string ename = func_ind_name(func_name);

  Symbol* comp_sym = mk_symbol(ename, mk_enum_const(ename, NULL /*enumVal*/));
  comp_sym->entry->u2EnumDef = def;
  
  def->addElement(comp_sym);
  
  return def->nElements -1;
}


BaseType* RVFuncClass::get_enum_tp()
{
  if( tp_func_ind_enum )        // <<==== PROBLEM if funcs are added later. 
    return tp_func_ind_enum;

  if( defs.size() > 0 )
    class_name = defs[0]->name;
  else
    class_name = funcs[0]->name;

  std::string type_name(TYPE_PREFIX);  // enum func index
  type_name += class_name;
  std::string tag_name = std::string("tg_") + type_name;

  /* create base: EnumDef and BaseType */
  EnumDef* enum_func_ind = new EnumDef();
  Symbol* esym = mk_symbol(tag_name, mk_tag(tag_name, NULL));
  enum_func_ind->tag = esym;
  tp_func_ind_enum = new BaseType(enum_func_ind);  /* copies the tag */
  esym->entry->uStructDef = tp_func_ind_enum;
  esym->entry->scope = NULL;

  /* set NO_FUNCTION as 0 enum value - for safety: */
  std::string no_func = class_name + "_NO_FUNCTION";
  add_enum_func_ind(enum_func_ind, no_func);

  /* add func index enums: */
  SymbolVector::const_iterator i;
  FORVEC(i, funcs)
    add_enum_func_ind(enum_func_ind, (*i)->name);

  return tp_func_ind_enum;
}


Symbol* RVFuncClass::get_enum_sym(std::string& func_name)
{
  BaseType* enum_type = get_enum_tp();
  if( !enum_type || !enum_type->enDefn )
    return false;

  std::string fi_name = func_ind_name(func_name);

  EnumDef* def = enum_type->enDefn;
  for(int i = 0; i < def->nElements; i++)
    if( def->names[i]->name == fi_name )
      return def->names[i];

  rv_errstrm << "Internal: RVFuncClass::get_enum_sym() can't find function index for \""<<
    func_name <<"\".\n";
  return NULL;
}


Decl* RVFuncClass::get_hub_decl(Project* pt)
{
  static const char *where_ = "RVFuncClass::get_hub_decl()";
  CHK_NULL1(this && type && pt, where_);

  if( hub_decl )
    return hub_decl;

  SymEntry* ent;
  Decl* decl;

  FunctionType* proto = (FunctionType*)type->dup();

  /* create scope for the new function params: */
  ScopeTbl* proto_scope = create_last_scope(pt, FUNCTION_SCOPE);

  /* fix proto to have all arg names */
  for(int i = 0; i < proto->nArgs; i++) 
  {
    decl = proto->args[i];
    if( !decl->name || decl->name->name == "" ) {
      delete decl->name;
      decl->name = mk_symbol(add_num("unnamed",i), NULL);
    }

    ent = mk_paramdecl(decl->name->name, decl);
    decl->name->entry = ent;
    proto_scope->Insert(ent);
  }

  Type* enum_type = get_enum_tp();
  if( !enum_type )
    return false;

  BaseType* new_type = (BaseType*)enum_type->dup();
  new_type->enDefn = NULL;  // keep only the tag name - not all enum def.
  Decl* ind_decl = new Decl(new_type);  // index param decl.
  ind_decl->name = mk_symbol(FI_ARG_NAME, mk_paramdecl(FI_ARG_NAME, ind_decl));
  proto->addArg(ind_decl);
  if( proto_scope )
    proto_scope->Insert(ind_decl->name->entry);

  /* gen func decl: */
  std::string hub_name = class_name + HUB_SUFFIX;
  hub_decl = mk_global_decl(pt, proto, hub_name);
  RVParse::add_empty_body(hub_decl->name->entry);  // make it valid function

  /* save and return: */
  return hub_decl;
}


bool RVFuncClass::gen_hub_func(RVTemp& temps, Project* pt, bool with_body)
{
  CHK_NULL1(this && type && pt, "in RVIndirectFuncs::gen_class_hub_func()");

  get_hub_decl(pt);
  if( !hub_decl )
    return false;
    
  FunctionType* proto = (FunctionType*)hub_decl->form;
  hub_decl->print(temps.get_strm(), true, 0);

  if( !with_body ) {
    temps.print(";\n\n");
    return true;
  }
  
  temps.get_strm() <<
"\n{\n"
"  switch( "<< FI_ARG_NAME <<" ) {\n";

  /* for esch func in funcs: */
  int i;
  SymbolVector::const_iterator j;
  FORVEC(j, funcs) {
    temps.get_strm() <<
"    case "<< func_ind_name((*j)->name) <<": return "<< (*j)->name <<"(";
    for(i = 0; i < proto->nArgs -1; i++) // print args without the FI_arg. 
      temps.get_strm() << (i?", ":"") << proto->args[i]->name->name;
    temps.get_strm() << ");\n";
  }
  
  temps.get_strm() <<
"    /* Check: the func index is valid: */\n"
"    default: __CPROVER_assume (0);\n"
"  }\n\n";

  Type* rettp = real_type(proto->subType, "RVFuncClass::gen_hub_func()");
  /* if it has a non-void return value: */
  if( !is_basetype(rettp, BT_Void) ) {
    temps.get_strm() <<
"  /* prevent \"no return value\" warning: */\n"
"  { ";

    Symbol* dummy = mk_symbol("dummy", NULL);
    proto->subType->printType(temps.get_strm(), dummy, true, 0);
    temps.get_strm() <<"; return dummy; }\n";
  }

  temps.get_strm() <<
"}\n\n\n";

  return true;
}


//bool RVFuncClass::change_all_defs()
//{
//  bool ret = true;
//  Type* enum_type = get_enum_tp();
//  if( !enum_type )
//    return false;
//
//  Decl* decl;
//
//  /* change all defs Decls to be of enum_type: */
//  SymbolVector::const_iterator i;
//  FORVEC(i, defs) {
//    if( !(*i) || !(*i)->entry || !(*i)->entry->IsTypeDef() || 
//	!(decl = (*i)->entry->uVarDecl) || !decl->form || !decl->isTypedef() ) {
//      rv_errstrm <<"Error: RVFuncClass::change_all_defs(): symbol \""<<
//	((*i)?(*i)->name.data():"UNKNOWN") <<"\" was expected to be typedef.\n";
//      ret = false;
//    }
//    decl->form = enum_type;
//  }
//
//  return ret;
//}


void RVFuncClass::print_info(bool pr_funcs, bool pr_type, bool pr_defs)
{
  if( pr_funcs )
    funcs.print("  Functions: ", rv_errstrm);
  if( pr_type ) {
    rv_errstrm <<"  Type: ";
    if( type )
      type->printType(rv_errstrm, NULL, true, 0);
    else
      rv_errstrm <<" NULL";
    rv_errstrm <<"\n";
  }
  if( pr_defs )
    defs.print("  Typedefs: ", rv_errstrm);	
  rv_errstrm <<"\n";    
}



/* RVIndirectFuncs */
/*=================*/


RVIndirectFuncs rv_indirect_funcs;

RVIndirectFuncs::RVIndirectFuncs()
{
  parsetree = NULL;
  side = -1; 
  fix_decl_types = false;
}

void RVIndirectFuncs::set_params(Project* _parsetree, int _side)
{
  parsetree = _parsetree; 
  side = _side; 
}

bool RVIndirectFuncs::add_func(Symbol* sym, int side)
{ 
  if( !sym || !valid_function(sym) )
    return false;

  FunctionDef* func = sym->entry->u2FunctionDef;

  if( func->fnode.has_ellipsis_args && func->fnode.has_body() ) {
    rv_errstrm <<"Warning: indirect function calls to functions with ellipsis arguments "
      "are not supported !\n  function: ";
    func->decl->print(rv_errstrm, true, 0); rv_errstrm<<"\n";
  }

  Type* type = func->decl->form;
  RVFuncClass* cls = get_by_type(type, side);

  if( !cls ) {  // open a new one.
    type = type->dup();  // subsequently this function type may change.
    cls = new RVFuncClass(type, side);
    classes[side].push_back(cls);
    by_type[side].insert( std::pair<Type*, RVFuncClass*>(type, cls) );
  }

  cls->funcs.push_back( sym->dup() );

  func->fnode.indirect = true;

if(DBG){ rv_errstrm<<"RVIndirectFuncs::add_func() added \""<< *sym <<"\" to RVFuncClass:\n  ";
 func->decl->print(rv_errstrm, true, 0); rv_errstrm<<"\n";
}

  return true; 
}


void RVIndirectFuncs::sort_all(int _side)
{
  RVFuncClassVec::const_iterator i;
  FORVEC(i, classes[_side])
    (*i)->sort_symbol_vectors();
}

bool RVIndirectFuncs::one_pass()
{
  /* safety check: */
  if( !RVCtool::get_glob_stemnt(parsetree) )
    return false;
  
  bool ret = true;
  Statement** pst = &(parsetree->Parse_TOS->transUnit->head);

if(DBG) rv_errstrm<<"Start RVIndirectFuncs::one_pass() on side "<<side<<" with fix_decl_types =  "<<
	  (fix_decl_types?"true":"false")<<", #classes = "<< classes[side].size()<<" .\n";

  /* fix ellipsis func decls: */
  for(; *pst; pst = &((*pst)->next) ) {
    if( (*pst)->isDeclaration() )
      ret = rv_ellipsis_fix.replace_ellipsis_func_decl(pst) && ret;

    set_where(get_where(*pst).data());

    if( !process(*pst) ) {
      rv_errstrm<<"Error: RVIndirectFuncs::one_pass() failed processing function at: ";
      (*pst)->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
      ret = false;
    }
  }

  return ret;
}


bool RVIndirectFuncs::add_hub_decls()
{
  bool ret = true;
  Decl* hub_decl = NULL;
  DeclStemnt* st = NULL;
  Location l(__LINE__, 0, __FILE__);

  /* safety check: */
  if( !RVCtool::get_glob_stemnt(parsetree) )
    return false;

  Statement** ptail = &(parsetree->Parse_TOS->transUnit->tail);

  RVFuncClassVec::const_iterator i;
  FORVEC(i, classes[side]) {
    hub_decl = (*i)->get_hub_decl(parsetree);
    if( !hub_decl ) {
      ret = false;
      continue;
    }
    
    st = new DeclStemnt(l);
    st->addDecl(hub_decl);

    /* append the decl at the tail: */
    (*ptail)->next = st;
    st->next = NULL;
    *ptail = st;
  }

  return ret;
}


bool RVIndirectFuncs::process_all(Project* _parsetree, int _side)
{
  CHK_NULL1( _parsetree && (_side >= 0), "RVIndirectFuncs::process_all()")
  set_params(_parsetree, _side);
  rv_ellipsis_fix.set_params(_parsetree, _side);

  bool ret = true;

if(DBG) rv_errstrm<<"Start RVIndirectFuncs::process_all() on side "<<side<<
	" with #classes = "<< classes[side].size() <<" .\n";

  sort_all(side); 

  /* in the first pass just fix function calls: */
  fix_decl_types = false;
  ret = one_pass() && ret;

  // ret = find_all_funcs_for_each_class(parsetree, side) && ret; <<=== FIN  (??)

  ret = find_func_pointer_typedefs(parsetree, side) && ret;

if(DBG) {rv_errstrm << "Indirect Function classes on side "<< side <<" :\n";
 print_info(side, true, true, true); }

  sort_all(side); // functions may have been added

  /* in the second pass fix also Decls of func pointers: */
  fix_decl_types = true;
  ret = one_pass() && ret;

  ret = add_hub_decls() && ret;

  rv_ellipsis_fix.delete_old_decls();

  return ret;
}  


bool RVIndirectFuncs::process(Statement* s0p)
{
  if(DBG){rv_errstrm<<"RVIndirectFuncs::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !s0p )
    return true;

  switch( s0p->type )
  {
    case ST_TypedefStemnt:
    case ST_DeclStemnt: {
      RETYPE( DeclStemnt );
      for(unsigned i = 0; i<s0p->decls.size(); i++)
	TRY_PROC( decls[i] );  // get to Decl - skip the symbol. 
      break;
    }

    case ST_ExpressionStemnt: {
      RETYPE( ExpressionStemnt );
      /* remove unused casts - makes problem to CBMC: */
      if( s0p->expression && s0p->expression->etype == ET_CastExpr )
	s0p->expression = ((CastExpr*)s0p->expression)->expr;
      break;
    }

    case ST_Block:
      if( s0p->isFuncDef() ) {
	RETYPE( FunctionDef );
	PROC( decl );
      }
      break;

    default:; // do nothing 
  }
  
  return go(s0p);
}
  

bool RVIndirectFuncs::process(Expression* s0p)
{
if(DBG){rv_errstrm<<"RVIndirectFuncs::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !s0p )
    return true;

  if( s0p->etype == ET_FunctionCall ) {
    RETYPE( FunctionCall );
    /* fix indirect func calls to direct calls to the right hub function: */
    if( !fix_func_call(s0p) )
      return false;
    
    /* try to fix calls to funcs with ellipsis args: */
    if( !rv_ellipsis_fix.fix_func_call(s0p) )
      return false;
    
    /* don't replace direct function calls: */
    if( s0p->function->etype != ET_Variable )
      REP_PROC( function );
    
    /* process the args anyway: */
    return go( s0p->args );
  }

  return go(s0p);
}
 

bool RVIndirectFuncs::try_replace(Expression** pexpr)
{
if(DBG){rv_errstrm<<"RVIndirectFuncs::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !pexpr || *pexpr == NULL )
    return false;

  Expression* expr = *pexpr;

  /* replace non-function-call uses of functions by their enum indexes */
  if( expr->etype == ET_Variable ) {
    if( valid_function( ((Variable*)expr)->name ) )
    {
      Symbol* func_sym = ((Variable*)expr)->name;
      RVFuncClass* cls = get_by_func(func_sym, side, expr->location);
      if( !cls )
	return false; // THROW <<===
      
      Symbol* enum_sym = cls->get_enum_sym(func_sym->name);
      if( !enum_sym )
	return false; // THROW <<===
      
      *pexpr = (Expression*)new EnumConstant(enum_sym->dup(), NULL, expr->location);
    }
    return false; // no need to process a var farther
  }

  return true;
}
    

bool RVIndirectFuncs::process(Decl* s0p)
{
if(DBG){rv_errstrm<<"RVIndirectFuncs::"<<__FUNCTION__<<"\n";/*FDEL*/}
 
  if( !s0p )
    return true;
   
  if( !fix_decl_types ) {
    /* process only the initializer expression: */
    TRY_REP_PROC( initializer );
    return true;
  }

  /* "register" storage can make problem with taking address of a var: */
  if( s0p && s0p->storage == ST_Register )
    s0p->storage = ST_None;

  /* replace func pointers by func index enums: */
  if( !fix_func_pointer_decl(s0p) )
    return false;

  /* typedefs are processes at their respective TypedefStemnts - skip: */
  if( s0p->form && is_basetype(s0p->form, BT_UserType)  )
    return true;

  return go(s0p);
}


bool RVIndirectFuncs::process_function_type(FunctionType* s0p)
{
  CHK_NULL("RVIndirectFuncs::go_function_type()"); 
if(DBG){s0p->printType(rv_errstrm, NULL, true, 0);rv_errstrm<<"\n";}

  PROC( subType );

  /* process argument decls not thru their symbols - as we ignore symbols: */
  for(int i =0; i<s0p->nArgs; i++)
    if( s0p->args[i] )
      PROC( args[i] );

  return true;
}


bool RVIndirectFuncs::process(StructDef *s0p)
{
  CHK_NULL("RVIndirectFuncs::process(StructDef*)");

  /* prevent infinite recursion in recursive structs: */
  if( s0p->assumeEq == s0p )
    return true;
  s0p->assumeEq = s0p;

  /* Don't process tags - processed at their the type declaration statement. */

  Decl  *comp0;
  for(int i=0; i < s0p->nComponents; i++) {  
    comp0 = s0p->components[i];
    while( comp0 ) {
if(DBG) rv_errstrm <<"RVIndirectFuncs::process(StructDef*): processing \""<<
	  comp0->name->name<<"\" \n";
      if( !process(comp0) ) { // process the Decls themselves
	s0p->assumeEq = NULL;
	return false;
      }
      comp0 = comp0->next;
    }
  }

  s0p->assumeEq = NULL;
  return true;
}


bool RVIndirectFuncs::process_basetype(BaseType* s0p)
{
  CHK_NULL("RVIndirectFuncs::process_basetype()"); 
if(DBG){s0p->printType(rv_errstrm, NULL, true, 0);rv_errstrm<<"\n";}

 Type* realtp = real_type(s0p, "RVIndirectFuncs::process_basetype()");
 if( realtp != s0p )
   return process(realtp);
 
  if( (s0p->typemask & (BT_Struct|BT_Union)) && s0p->stDefn )
    PROC( stDefn )
  else if( (s0p->typemask & BT_Enum) && s0p->enDefn )
    PROC( enDefn );

  /* Don't process tags - processed at their the type declaration statement. */

  return true;
}


bool RVIndirectFuncs::is_func_pointer(Type* type)
{
  return( type && type->isPointer() &&
	  ((PtrType*)type)->subType &&
	  ((PtrType*)type)->subType->isFunction() );
}


RVFuncClass* RVIndirectFuncs::get_by_type(Type* type, int side)
{
  CHK_NULL1(type, "type in RVIndirectFuncs::get_by_type()");

  std::map<Type*, RVFuncClass*>::const_iterator i;
  i = by_type[side].find(type);
  if( i != by_type[side].end() )
    return (*i).second;
  
  /* if the type is not original - find a simmilar one: */
  RVTreeComp comp(false, false);
  RVFuncClassVec::const_iterator j;
  FORVEC(j, classes[side])
    if( comp.eq_type((*j)->type, type) ) {
      /* add this type pointer to the index: */
      by_type[side].insert( std::pair<Type*, RVFuncClass*>(type, (*j)) );
      return (*j);
    }

  return NULL;
}


RVFuncClass* RVIndirectFuncs::get_by_func(Symbol* func_sym, int side, Location& l)
{
  CHK_NULL1(func_sym, "RVIndirectFuncs::get_by_func()");
  
  if( !valid_function(func_sym) ) {
    rv_errstrm << "Internal: RVIndirectFuncs::get_by_func(): \""<< *func_sym <<
      "\" is not a function (?).\n  at: ";
    l.printLocation(rv_errstrm); rv_errstrm<<"\n";
    return NULL;
  }
  
  Type* type = get_symbol_type(func_sym, "RVIndirectFuncs::get_by_func()");
  RVFuncClass* cls = get_by_type(type, side);
  if( !cls ) {
    rv_errstrm << "Internal: unable to find function class to match function:\n  ";
    if(type) type->printType(rv_errstrm, func_sym, true, 0); rv_errstrm<<"\n";
    l.printLocation(rv_errstrm); rv_errstrm<<"\n";
    return NULL;
  }

  Symbol* found = cls->funcs.find(func_sym->name);
  if( !found || found->entry != func_sym->entry ) {
    rv_errstrm << "Internal: the next function doesn't appear in the class of its type:\n  ";
    if(type) type->printType(rv_errstrm, func_sym, true, 0); rv_errstrm<<"\n";
    l.printLocation(rv_errstrm); rv_errstrm<<"\n";
    return NULL;
  }

  return cls;
}


bool RVIndirectFuncs::find_func_pointer_typedefs(Project* pt, int side)
{
  CHK_NULL1(pt, "RVIndirectFuncs::find_func_pointer_typedefs()");

  if( classes[side].size() == 0 )
    return true; // func pointers are not used

  ScopeTbl* scope = get_file_scope(pt);
  CHK_NULL1(scope && scope->htab, 
	    "symbol scope in RVIndirectFuncs::find_func_pointer_typedefs()");

  SymEntry *se;
  Type* form;
  RVFuncClass* cls;
  HashTblIter hit(scope->htab);

  /* add typedefs of function pointers to their respective func classes */
  FORIT(se, hit)
    if( se && se->IsTypeDef() && se->uVarDecl ) 
    {
      form = real_type(se->uVarDecl->form, "RVIndirectFuncs::find_func_pointer_typedefs()");
      
      if( is_func_pointer(form) ) {
	  cls = get_by_type(((PtrType*)form)->subType, side);
	  if( cls && se->uVarDecl->name )
	    cls->defs.push_back( se->uVarDecl->name->dup() );
      }
    }

  return true;
}


bool RVIndirectFuncs::gen_all_func_ind_enums(RVTemp& temps, Project* pt, int side)
{
  bool ret = true;
  BaseType* enum_tp;

if(DBG) rv_errstrm<<"Start RVIndirectFuncs::gen_all_func_ind_enums() on side "<<side<<
	" with #classes = "<< classes[side].size() <<" .\n";

  RVFuncClassVec::const_iterator i;
  FORVEC(i, classes[side]) {
    enum_tp = (*i)->get_enum_tp();
    if( !enum_tp )
      ret = false;
    else {
      enum_tp->printType(temps.get_strm(), NULL, true, 0); 
      temps.print(";\n\n");
    }
  }

  return ret;
}


bool RVIndirectFuncs::gen_all_class_hubs(RVTemp& temps, Project* pt, int side, bool with_body)
{
  bool ret = true;

if(DBG){rv_errstrm<<"Start RVIndirectFuncs::gen_all_class_hubs() on side "<<side<<
	  " with #classes = "<< classes[side].size() <<" .\n";}

  temps.print("\nvoid __CPROVER_assume(_Bool);\n");
  temps.print("\n/* Hub functions for indirect function calls: */\n");

  RVFuncClassVec::const_iterator i;
  FORVEC(i, classes[side])
    ret = (*i)->gen_hub_func(temps, pt, with_body) && ret;  

  return ret;
}


void RVIndirectFuncs::print_info(int _side, bool pr_funcs, bool pr_type, bool pr_defs)
{
  RVFuncClassVec::const_iterator i;

  FORVEC(i, classes[_side])
    (*i)->print_info(pr_funcs, pr_type, pr_defs);
}
 

bool RVIndirectFuncs::fix_func_pointer_decl(Decl* decl)
{
  CHK_NULL1(decl, "RVIndirectFuncs::fix_func_pointer_decl()");

  Type* type = real_type(decl->form, "RVIndirectFuncs::fix_func_pointer_decl()");
  if( !is_func_pointer(type) )
    return true;  // ignore

  type = ((PtrType*)type)->subType;
  RVFuncClass* cls = get_by_type(type, side);
  if( !cls ) {
    rv_errstrm << "Warning: unable to find function class to match declaration of"
      " function pointer:\n  ";
    decl->print(rv_errstrm, true, 0); rv_errstrm << "\n";

if(DBG) print_info(side, true, true, false);
 
    return true; // false; <<==== DECIDE - but then we should collect all func typedefs
  }
    
  BaseType* new_type = cls->get_enum_tp();
  if( new_type ) {
    new_type = (BaseType*)new_type->dup();
    new_type->enDefn = NULL;  // keep only the tag name - not all enum def.
    decl->form = new_type;
  }

  return true;
}


bool RVIndirectFuncs::fix_func_call(Expression* expr)
{
  if( !expr || expr->etype != ET_FunctionCall )
    return true;

  Symbol* func_sym = NULL;  
  FunctionCall* call = (FunctionCall*)expr;
  CHK_NULL1(call->function, "function expression in RVIndirectFuncs::fix_func_call()");

  Expression* called = call->function;
  if( called->etype == ET_Variable ) {
    func_sym = ((Variable*)called)->name;
    if( get_symbol_type(func_sym,"RVIndirectFuncs::fix_func_call()")->isFunction() )
      return true;  // this is a direct function call.
  }
  
  Type* type = real_type(called->type, "RVIndirectFuncs::fix_func_call()");
  bool func_pointer = is_func_pointer(type);

  /* function type itself or its pointer */
  if( !type || !(type->isFunction() || func_pointer) ) {
    rv_errstrm << "Error: NULL or wrong type of indirect function pointer:\n  ";
    expr->print(rv_errstrm); rv_errstrm<<"\n  at: ";
    expr->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
    if( type ) {
      rv_errstrm<<"  called type: ";
      type->printType(rv_errstrm,  NULL, true, 0); rv_errstrm<<"\n";
    }
    return false;
  }

  if( func_pointer ) {
    type = ((PtrType*)type)->subType;
    fix_func_proto(type);
  }

  /* use get_by_type() to get the right func class */
  RVFuncClass* cls = get_by_type(type, side);
  if( !cls ) {
    rv_errstrm << "Internal: can't find function class to match indirect function call by"
      " function pointer:\n  ";
    expr->print(rv_errstrm);rv_errstrm<<"\n  at: ";
    expr->location.printLocation(rv_errstrm); rv_errstrm<<"\n  of type: ";
    type->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";
    return false;
  }

  /* get hub func symbol */
  Decl* hub_decl = cls->get_hub_decl(parsetree);
  if( !hub_decl || !hub_decl->name ) {
    rv_errstrm << "Internal: can't create hub function declaration or symbol for type:\n  ";
    type->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n";      
    return false;
  }

  /* replace the called to call to the hub function: */
  Symbol* hub_sym = hub_decl->name;
  call->function = new Variable(hub_sym->dup(), called->location);

  /* the expression which is passed as indirect function call is now
     the functiomn index code - use it as the last argument to the hub function: */

  // remove the deref before the FI code value (if exists)
  if( called->etype == ET_UnaryExpr && ((UnaryExpr*)called)->uOp == UO_Deref && !func_pointer ) 
  {
    UnaryExpr* old = (UnaryExpr*)called;
    called = old->operand();
    old->_operand = NULL;
    delete old;
  }
    
  call->addArg(called);

  return true;
}
    
Type *RVIndirectFuncs::fix_func_proto(Type *proto_) {
	if ( proto_ == NULL || !proto_->isFunction() )
		return NULL;
	FunctionType *proto = static_cast<FunctionType *>(proto_);
	Type* lasttp = proto->nArgs > 0 && proto->args[proto->nArgs-1] ?
			proto->args[proto->nArgs-1]->form : NULL;

	if( lasttp && is_basetype(lasttp,BT_Void) ) {
		assert( proto->nArgs == 1 );
		proto->nArgs = 0;  /* int f1(void) - means no args. */
	}

	return lasttp;
}

/* RVEllipsisFix functions: */
/* ======================== */

RVEllipsisFix rv_ellipsis_fix;

RVEllipsisFix::RVEllipsisFix()
{ 
  parsetree = NULL;
  side = -1; 
  where = "UNKNOWN"; 
  ellipsis_arg_type = NULL;
  old_head = old_tail = NULL;
}

void RVEllipsisFix::set_params(Project* _parsetree, int _side)
{
  parsetree = _parsetree; 
  ellipsis_arg_type = new BaseType(BT_Long); // make it in the current parsetree.
  side = _side; 
}

void RVEllipsisFix::save_old_ellipsis_decl(DeclStemnt* st)
{
    if( !old_head )
      old_head = st;
    if( old_tail )
      old_tail->next = st;
    old_tail = st;
    st->next = NULL;
}

bool RVEllipsisFix::delete_old_decls()
{
  CHK_NULL1(parsetree, "parsetree in RVEllipsisFix::delete_old_decls()");

  ScopeTbl* file_scope = get_file_scope(parsetree);
  DeclStemnt *st = old_head;
  DeclStemnt *prev = NULL;
  SymEntry *ent = NULL;

  while( st ) {
    prev = st;
    st = (DeclStemnt*)st->next;

    if(DBG) {rv_errstrm << "Delete decl: "; prev->print(rv_errstrm, 0); rv_errstrm << "\n";}

    /* all the next parts are deleted separately: */
    ent = ScopeTbl_remove(file_scope, prev->decls[0]->name->name);
    ent->u2FunctionDef->decl = NULL;  // deleted from DeclStemnt
    delete ent->u2FunctionDef;  // because of add_func_empty_bodies()
    delete ent;
    delete prev;
  }

  old_head = old_tail = NULL;

  return true;
}


std::string RVEllipsisFix::get_ellipsis_func_name(std::string& orig, int num_add_args)
{
  std::ostringstream tmp;
  tmp << orig << "_" << num_add_args;
  return tmp.str();
}


bool RVEllipsisFix::replace_ellipsis_func_decl(Statement** pst)
{
  CHK_NULL1(parsetree, "parsetree in RVEllipsisFix::replace_ellipsis_func_decl()");

  if( !pst || !*pst || !(*pst)->isDeclaration() )
    return true;
  DeclStemnt* dst = (DeclStemnt*)*pst;
  if( dst->decls.size() != 1 || !dst->decls[0]->name || 
      !dst->decls[0]->form || dst->decls[0]->isTypedef() )
    return true;
  FunctionType* form = (FunctionType*)dst->decls[0]->form;
  if( !form->isFunction() || form->nArgs == 0 )
    return true;

  Symbol* func_sym = dst->decls[0]->name;
  if( !func_sym || !valid_function(func_sym) ) {
    rv_errstrm << "Warning: bad (or NULL) function entry of definition at:\n  ";
    dst->print(rv_errstrm, 0); rv_errstrm << "\n";
    return false;
  }

  std::string where_str = func_sym->name+" (side "+(side?"1":"0")+" decl)";
  where = where_str.data();

  FunctionDef* func = func_sym->entry->u2FunctionDef;

  /* check last arg is really ellipsis: */
  if( !form->args[form->nArgs -1] || 
      !is_basetype(form->args[form->nArgs -1]->form, BT_Ellipsis) )
    return true;
  if( !func->fnode.has_ellipsis_args ) {
    rv_errstrm << "Internal: function \""<< func_sym->name <<"\" has ellipsis arguments -"
      " but is not marked as such. (side "<< side <<")\n";
    return false;
  }

if(DBG) rv_errstrm<<"RVEllipsisFix::replace_ellipsis_func_decl() on "<< *func_sym <<"\n";

  Decl* tmp_decl = NULL;
  SymEntry* tmp_ent = NULL;
  FunctionType* tmp_tp = (FunctionType*)form->dup();
  tmp_tp->nArgs--;  // remove the ellipsis mark.
  delete tmp_tp->args[tmp_tp->nArgs]; // ??
  
  /* if any args left - remove them from their function scope */
  ScopeTbl* old_scope = NULL;
  if( tmp_tp->nArgs > 0 && tmp_tp->args[0]->name && 
      tmp_tp->args[0]->name->entry )
    old_scope = tmp_tp->args[0]->name->entry->scope;
  
  if( old_scope )
    for(int j = 0; j < tmp_tp->nArgs; j++)
      if( tmp_tp->args[j]->name )
	ScopeTbl_remove(old_scope, tmp_tp->args[j]->name->name);  

  ScopeTbl* file_scope = get_file_scope(parsetree);
  DeclStemnt *last = NULL, *first = NULL;
  FunctionType* new_tp = NULL;
  std::string new_name;
  Decl* arg_decl = NULL;

  /* gen several proto decls with <func_name>_n(formal args, long, long, ) */
  for(int add_opt_args = 0; add_opt_args <= func->fnode.max_ellipsis_args; add_opt_args++) 
  {
    new_tp = (FunctionType*)tmp_tp->dup();
    tmp_decl = new Decl(new_tp);
    new_name = get_ellipsis_func_name(func_sym->name, add_opt_args);
    tmp_ent = mk_fctdecl(new_name, tmp_decl);
    tmp_ent->scope = NULL;
    tmp_decl->name = mk_symbol(new_name, tmp_ent);
    
    /* create a prototype scope and add all args to it:*/
    ScopeTbl* new_scope = create_last_scope(parsetree, FUNCTION_SCOPE);    
    for(int j = 0; j < new_tp->nArgs; j++) {
      arg_decl = new_tp->args[j];
      arg_decl->name->entry = mk_paramdecl(arg_decl->name->name, arg_decl);
      new_scope->Insert(arg_decl->name->entry);
    }
      
    /* add new funcs to file scope. */
    file_scope->Insert(tmp_ent);

    /* as ellipsis function is bodyless - add it an empty body */
    RVParse::add_empty_body(tmp_ent);

    /* create the decl statement: */
    DeclStemnt* new_st = new DeclStemnt(dst->location);
    new_st->addDecl(tmp_decl);

    /* add it to list */
    if( !first )
      first = new_st;
    if( last )
      last->next = new_st;
    last = new_st;

if(DBG){rv_errstrm<<"  Added: "; new_st->print(rv_errstrm,0); rv_errstrm<<"\n";} 

    /* if its the last one: */
    if( add_opt_args == func->fnode.max_ellipsis_args )
      break;

    std::ostringstream arg_name;
    arg_name << "opt_arg_" << add_opt_args;
    /* add another long var to the tmp_tp - for the next proto */
    add_func_param(tmp_tp, arg_name.str(), ellipsis_arg_type);
  }
    
  /* connect it into the TransUnit  */
  last->next = dst->next;
  dst->next = NULL;
  *pst = first;
  
  // keep the old DeclStemnt for now - FunctionCalls may use its symbol and decl
  save_old_ellipsis_decl(dst);

  return true;
}


bool RVEllipsisFix::add_arg_typecasts(ExprVector& args, int first_opt_arg)
{
  for(unsigned i = first_opt_arg; i < args.size(); i++)
    if( args[i] )
      args[i] = new CastExpr(ellipsis_arg_type, args[i], args[i]->location);

  return true;
}


bool RVEllipsisFix::fix_func_call(Expression* expr)
{
  if( !expr || expr->etype != ET_FunctionCall )
    return true;
  
  FunctionCall* call = (FunctionCall*)expr;
  if( !call->function || call->function->etype != ET_Variable ) 
    return true;

  Variable* var = (Variable*)call->function;
  Symbol* sym = var->name;
  if( !valid_function(sym) ) {
    rv_errstrm << "Error: invalid function call:\n  ";
    expr->print(rv_errstrm);  rv_errstrm << " \n  at: ";
    expr->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
    return false;
  }

  FunctionDef* body = sym->entry->u2FunctionDef;
    
  if( !body->fnode.has_ellipsis_args )
    return true;

  int num_explicit_args = body->fnode.nArgs;
  int num_opt_args = call->args.size() - num_explicit_args;

  if( num_opt_args < 0 || num_opt_args > body->fnode.max_ellipsis_args ) {
    rv_errstrm << "Internal: RVEllipsisFix::fix_func_call() "
      "unexpected number of optional arguments (RVCollect was wrong):\n  ";
    expr->print(rv_errstrm);  rv_errstrm << " \n  at: ";
    expr->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
    return false;
  }

  std::string new_name = get_ellipsis_func_name(sym->name, num_opt_args);

  ScopeTbl* file_scope = get_file_scope(parsetree);
  SymEntry* new_ent = file_scope->Lookup(new_name);

  if( !new_ent ) {
    rv_errstrm << "Internal: RVEllipsisFix::fix_func_call() "
      "unable to find function symbol \""<< new_name <<"\" to replace call:\n  ";
    expr->print(rv_errstrm);  rv_errstrm << " \n  at: ";
    expr->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
    return false;
  }

  var->name = mk_symbol(new_name, new_ent);

  if( !add_arg_typecasts(call->args, num_explicit_args) )
    return false;

  return true;
}





//
///* RVDetachPointerValue */
///*======================*/
//
//RVDetachPointerValue rv_detach_pointer_value;
//
//const char* RVDetachPointerValue::detach_comp_names[2] = { "p", "v" };
//
//
//RVDetachPointerValue::RVDetachPointerValue()
//  : RVWalk(true), typecomp(false, true)
//{
//  parsetree = NULL;
//  side = -1; 
//  where = "UNKNOWN"; 
//  only_fix_types = false;
//  value_type = uchar_type = NULL;
//}
//
//void RVDetachPointerValue::add_pointer_type(std::string typedef_name, int _side)
//{
//  typesyms[_side].push_back(mk_symbol(typedef_name, NULL));
//}
//
//void RVDetachPointerValue::set_params(Project* _parsetree, int _side)
//{
//  parsetree = _parsetree; 
//  side = _side; 
//  
//  /* Note: we assume pointers are of bit-width of int ! */
//  value_type = new BaseType(BT_Int | BT_Signed);
//  uchar_type = new BaseType(BT_Char | BT_UnSigned);
//}
//
//
//bool RVDetachPointerValue::one_pass()
//{
//  bool ret = true;
//  Statement* st = RVCtool::get_glob_stemnt(parsetree);
//
//if(DBG) rv_errstrm<<"RVIndirectFuncs starts processing code of side "<<side<<" .\n";
//
//  /* process all code: */
//  for(; st; st = st->next) {
//    set_where(get_where(st).data());
//
//    ret = process( st ) && ret;
//  }
//
//if(DBG) rv_errstrm<<"RVIndirectFuncs finished processing code of side "<<side<<" .\n";
//
//  return ret;
//}
//
//
//bool RVDetachPointerValue::process_all(Project* _parsetree, int _side)
//{
//  CHK_NULL1( _parsetree && (_side >= 0), "RVDetachPointerValue::process_all()")
//  set_params(_parsetree, _side);
//
//  bool ret = true;
//
//if(DBG) rv_errstrm<<"Start RVDetachPointerValue::process_all() on side "<<side<<
//	" with #typesyms = "<< typesyms[side].size() <<" .\n";
//
//  ret = connect_types() && ret;
//
//  only_fix_types = false;
//  ret = one_pass() && ret;
//
//  only_fix_types = true;
//  ret = one_pass() && ret;
//
//if(DBG) rv_errstrm<<"Finished RVDetachPointerValue::process_all() on side "<<side<<"\n";
//
//  return ret;
//}
//
//
//Type* RVDetachPointerValue::create_detach_struct(Symbol* sym, Type* old_type)
//{
//  CHK_NULL1(sym && old_type, "RVDetachPointerValue::create_detach_struct()");
//
//  if( !real_type(old_type,where)->isPointer() ) {
//    if( old_type ) {
//      rv_errstrm <<"Error: Bad type for detach: ";
//      old_type->printType(rv_errstrm, NULL, true, 0); 
//    }
//    rv_errstrm<<"  Symbol: "<< *sym <<"\n";      
//    fatal_error("Error: RVDetachPointerValue::create_detach_struct(): attempt "
//		"to create value detach structure to non-pointer type: ", sym->name, false);
//    return NULL;
//  }
//
//  Decl*   comp;
//  StructDef* strdef = new StructDef();
//
//  /* create the pointer part: */
//  comp = new Decl(old_type);
//  comp->name = mk_symbol(detach_comp_names[0], mk_component(detach_comp_names[0], comp, strdef));
//  strdef->addComponent(comp);
//
//  /* create the bits value part: */
//  comp = new Decl(value_type);
//  comp->name = mk_symbol(detach_comp_names[1], mk_component(detach_comp_names[1], comp, strdef));
//  strdef->addComponent(comp);
//
//  BaseType* ret = new BaseType(strdef);
//
//  /* create a tag for the struct: */
//  std::string tagname = "tg_" + sym->name;
//  Symbol* tag = mk_symbol(tagname, mk_tag(tagname, ret));
//  ret->tag = tag;
//
//  /* add it to tag scope */
//  ScopeTbl* tag_scope = get_file_tags(parsetree);
//  if( !tag_scope )
//    fatal_error("RVDetachPointerValue::create_detach_struct(): can't get tag scope to put: ",
//		tagname, false);
//
//  tag_scope->Insert( tag->entry );
//  tag->entry->scope = tag_scope;
//
//  return ret;
//}
//
//
//std::string RVDetachPointerValue::get_fix_func_name(std::string& typesym_name, FixFunc func_ind)
//{
//  static const char* func_suffixes[3] = { "eq", "compare", "2bool" };
//  if( func_ind > 3 )
//    fatal_error("Bad func_ind in RVDetachPointerValue::get_fix_func_name()");
//
//  return typesym_name + "_det_" + func_suffixes[func_ind];
//}  
//
//
//Decl* RVDetachPointerValue::create_fix_func_decl(std::string& typesym_name, 
//						 FixFunc func_ind, Type* argtp)
//{
//  FunctionType* functp = new FunctionType();
//  functp->subType = uchar_type;
//
//  add_func_param(functp, "pl", argtp);
//  if( func_ind != IS_TRUE_FUNC )
//     add_func_param(functp, "pr", argtp);
//  if( func_ind == REL_FUNC )
//     add_func_param(functp, "rel_code", uchar_type);
//
//  std::string fname = get_fix_func_name(typesym_name, func_ind);
//  Decl* decl = mk_global_decl(parsetree, functp, fname);
//
//  /* add it an empty body for now (bodies are printed separately): */
//  RVParse::add_empty_body(decl->name->entry);
//
//  all_fix_funcs.push_back(decl);
//
//  return decl;
//}
//
//
//bool RVDetachPointerValue::create_all_fix_func_decls(std::string& typesym_name, Type* new_type)
//{
//  PtrType* argtp = new PtrType();
//  argtp->subType = new_type;
//
//  return 
//    create_fix_func_decl(typesym_name, EQ_FUNC, argtp) &&
//    create_fix_func_decl(typesym_name, REL_FUNC, argtp) &&
//    create_fix_func_decl(typesym_name, IS_TRUE_FUNC, argtp);
//}
//
//
//bool RVDetachPointerValue::connect_types()
//  /* connect typesyms to their types and create their detached Decls */
//{
//  if( !parsetree )
//    fatal_error("NULL parsetree in RVDetachPointerValue::connect_types()", false);
//
//  where = (std::string("RVDetachPointerValue::connect_types() on side ") + (side?"1":"0")).data();
//
//  bool ret = true;
//  Type* orig_type = NULL;
//  SymEntry* ent = NULL;
//  Type* new_form = NULL;
//  Decl* new_decl = NULL;
//  SymEntry* new_ent = NULL;
//  SymbolVector& vec = typesyms[side];
//  ScopeTbl* scope = get_file_scope(parsetree);
//
//  vec.unique_sort();
//
//  int ind = 0;
//  SymbolVector::const_iterator i;
//  FORVEC(i, vec) {
//    std::string name = (*i)->name;
//
//    ent = scope->Lookup(name);
//
//    if( !ent || !ent->IsTypeDef() || !(orig_type = get_symbol_type(ent, where)) ||
//	!real_type(orig_type, where)->isPointer() )
//      fatal_error("Error: unable to find valid pointer typedef for value detach operation: ",
//		  name, false);
//
//    (*i)->entry = ent;
//
//    new_form = create_detach_struct((*i), orig_type);
//    new_decl = new Decl(new_form);
//    new_ent = mk_typedef(name, new_decl);
//    new_decl->name = mk_symbol(name, new_ent);
//
//    new_typedecls[side].Insert(new_ent);
//
//    if( !create_all_fix_func_decls(name, new_form) ) {
//      rv_errstrm << "Internal: failed to create fix function prototypes for "
//	" value detach operation of  pointer typedef: "<< name <<" \n";
//      ret = false;
//    }
//
//    ind++;
//  }
//
//  return ret;
//}
//
//
//void RVDetachPointerValue::set_new_types()
//  /* Replace old typesym Decls by the new ones. */
//{
//  SymEntry* new_ent = NULL;
//  Decl* decl = NULL;
//  SymbolVector& vec = typesyms[side];
//
//  SymbolVector::const_iterator i;
//  FORVEC(i, vec) {
//    new_ent = get_new_entry((*i)->name);
//    decl = (*i)->entry->uVarDecl;
//
//    /* set the new form as the official one: */
//    decl->form = new_ent->uVarDecl->form;
//
//    /* delete unneeded constructs: */
//    new_ent->uVarDecl->form = NULL;
//    delete new_ent->uVarDecl;
//    new_ent->uVarDecl = NULL;
//    delete new_ent;
//  }
//}
//
//
//SymEntry* RVDetachPointerValue::get_new_entry(std::string& typesym_name)
//{
//  SymEntry* ent = new_typedecls[side].Lookup( typesym_name );
//  if( !ent )
//    fatal_error("RVDetachPointerValue::get_new_entry() didn't collect (?) typedef: ",
//		typesym_name, false);
//
//  return ent;
//}
//
//
//StructDef* RVDetachPointerValue::get_new_structdef(std::string& typesym_name)
//{
//  StructDef* ret = NULL;
//  SymEntry* ent = get_new_entry(typesym_name);
//
//  Type* tp = get_symbol_type(ent, "RVDetachPointerValue::get_new_structdef()");
//  if( !is_basetype(tp, BT_Struct) || !(ret = ((BaseType*)tp)->stDefn) ||
//      ret->nComponents != 2 || !ret->components ) {
//    fatal_error("Internal: bad struct type of a pointer typedef which was detached"
//		" of its bit-value. symbol: ", typesym_name, false);
//    return NULL;
//  }
//  
//  return ret;
//}
//
//
//Type* RVDetachPointerValue::get_old_type(Symbol* typesym)
//{
//  StructDef* strdef = get_new_structdef(typesym->name);
//  Type* form = NULL;
//
//  if( !strdef || !strdef->components || !strdef->components[0] ||
//      !(form = strdef->components[0]->form) || !real_type(form,where)->isPointer() ) {
//    fatal_error("Internal: can't get old type for detached from bit-value typedef symbol: ",
//		typesym->name, false);
//    return NULL;
//  }
//    
//  return strdef->components[0]->form;
//}
//
//
//Symbol* RVDetachPointerValue::find_typesym(Type* type)  
//{
//  Type* tp = real_type(type, where);
//  if( !tp || !tp->isPointer() )
//    return NULL;
//
//  SymbolVector& vec = typesyms[side];
//  SymbolVector::const_iterator i;
//  FORVEC(i, vec)
//    if( typecomp.eq(tp, get_old_type(*i)) )
//      return (*i);
//
//  return NULL;
//}
//
//
//Symbol* RVDetachPointerValue::find_expr_typesym(Expression* s0p)
//{
//  if( !s0p )
//    return NULL;
//
//  if( !s0p->type ) {
//    rv_errstrm << "Warning: RVDetachPointerValue: expression has no type: \n  ";
//    s0p->print(rv_errstrm); rv_errstrm<<"\n  at: ";
//    s0p->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
//    rv_errstrm <<"  (check type propogation)\n"; 
//    return NULL;  // maybe THROW <<===
//  }
//
//  return find_typesym(s0p->type);
//}
//
//
//Expression* RVDetachPointerValue::mk_member_op(Expression* orig, Symbol* typesym,
//					       CompInd comp_ind)
//{
//  CHK_NULL1(orig && typesym, "RVDetachPointerValue::mk_member_op()");
//
//  StructDef* strdef = get_new_structdef(typesym->name);
//  if( !strdef || !strdef->components || 
//      !strdef->components[0] || !strdef->components[comp_ind]->name )
//    return NULL;
//
//  Location& l = orig->location;
//  Variable* var = new Variable(strdef->components[comp_ind]->name->dup(), l);
//
//  BinaryExpr* ret = new BinaryExpr(BO_Member, orig, var, l);
//  ret->type = strdef->components[comp_ind]->form;
//
//  return ret;
//}
//
//
//bool RVDetachPointerValue::try_replace_by_component(Expression** pexpr, CompInd comp_ind)
//{
//  Expression* expr = *pexpr;
//  Symbol* typesym = find_expr_typesym(expr);
//  if( !typesym )  // not a type we should bother of
//    return true;  // do nothing.
//
//  Expression* res = mk_member_op(expr, typesym, comp_ind);
//  if( !res )
//    return false;
//
//  *pexpr = res;
//  return true;
//}
//
//
//bool RVDetachPointerValue::try_replace(Type** ptp)
//{
//  if( !ptp || !*ptp )
//    return true;
//
//  Type* s0p = *ptp;
//
//  /* replace type of old pointers which should be detached by their detach struct: */
//  if( only_fix_types ) {
//    Symbol* typesym = find_typesym(s0p);
//    if( typesym ) {
//rv_errstrm<<"UUU: Replaces type: "<< *typesym <<"\n";
//
//      SymEntry* ent = get_new_entry(typesym->name);
//      Type* tp = get_symbol_type(ent, "RVDetachPointerValue::try_replace(Type**)");
//      *ptp = tp;
//    }
//  }
//
//  return true; // try process subtypes.
//}
//    
//
//bool RVDetachPointerValue::process(Statement* s0p)
//{
//  if( !go(s0p) ) // process its contents first
//    return false;
//
//  if( only_fix_types ) // 2nd pass
//    return true;
//
//  /* try to fix places where boolean value is needed: */
//  switch( s0p->type )
//  {
//    case ST_IfStemnt: {
//      RETYPE( IfStemnt );
//      return fix_boolean( &s0p->cond );
//    }
//
//    case ST_ForStemnt: {
//      RETYPE( ForStemnt );
//      return fix_boolean( &s0p->cond );
//    }
//
//    case ST_WhileStemnt: {
//      RETYPE( WhileStemnt );
//      return fix_boolean( &s0p->cond );
//    }
//
//    case ST_DoWhileStemnt: {
//      RETYPE( DoWhileStemnt );
//      return fix_boolean( &s0p->cond );
//    }
//
//    default:;
//  }
//
//  return true;
//}
//
//
//static const BaseTypeSpec NumericMask = (BT_Char|BT_Short|BT_Int|BT_Int64|BT_Int32|
//					 BT_Int16|BT_Int8|BT_Long|BT_LongLong|
//					 BT_Signed|BT_UnSigned|BT_Float|BT_Double);
//
//
//bool RVDetachPointerValue::try_replace(Expression** pexpr)
//{
//if(DBG){rv_errstrm<<"RVIndirectFuncs::"<<__FUNCTION__<<"\n";/*FDEL*/}
//  if( !pexpr || *pexpr == NULL )
//    return false;
//
//  Expression* s0p = *pexpr;
//
//  if( only_fix_types ) {
//    if( !try_fix_member_op_type(s0p) )
//      return false; // THROW <<=== 
//
//    return false; // don't process expressions - only types.
//  }
//
//  bool ret = true;
//
//  switch( s0p->etype )
//  {
//    case ET_VoidExpr:            // No value
//    case ET_Constant:
//    case ET_Variable:
//    case ET_FunctionCall:
//      return true;
//      
//    case ET_AssignExpr:
//    case ET_RelExpr: 
//      rv_errstrm << "Internal: ET_AssignExpr or ET_RelExpr was unused in ctool " <<
//        "- unexpected Expression::etype = " << s0p->etype << " .\n";
//      return false;
//
//    case ET_UnaryExpr:
//      if( !fix_unary( (UnaryExpr**)pexpr ) )
//	return false; // THROW <<=== 
//      return false; // no further processing is needed.
//
//    case ET_BinaryExpr:
//      if( !fix_binary( (BinaryExpr**)pexpr ) )
//	return false; // THROW <<=== 
//      return false; // no further processing is needed.
//      
//    case ET_TrinaryExpr: {          // x ? y : z
//      RETYPE( TrinaryExpr );
//      if( !fix_boolean( &s0p->_condExpr ) )
//	return false; // THROW <<=== 
//      return false; // no further processing is needed.
//    }
//
//    case ET_CastExpr: {           // (type) x
//      RETYPE( CastExpr );
//      Type* castTo = real_type( s0p->castTo, where );
//      if( is_basetype(castTo, BT_Bool) )  // is like if( expr )
//	ret = fix_boolean( &s0p->expr );
//      else if( is_basetype(castTo, NumericMask) ) // <<=== MAYBE: fix_boolean() ?
//	ret = try_replace_by_component( &s0p->expr, V_COMP);
//      if( !ret )
//	return false; // THROW <<=== 	
//      return false; // no further processing is needed.
//    }
//
//    case ET_SizeofExpr: {         // sizeof(type) -or- sizeof(expr)
//      RETYPE( SizeofExpr );
//      /* if it is one of pointer expressions we should treat: */
//      if( s0p->expr && find_expr_typesym(s0p->expr) ) {  
//	rv_errstrm << "Warning: RVDetachPointerValue: one thing that detachment can't keep "
//	  " the same is the sizeof the resulting struct :\n  ";
//	s0p->print(rv_errstrm); rv_errstrm<<"\n  at: ";
//	s0p->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
//      }
//      return true;
//    }
//      
//    case ET_IndexExpr: {          // x[y]...[]
//      RETYPE( IndexExpr );
//      if( !try_replace_by_component( &s0p->array, P_COMP) )
//	return false; // THROW <<=== 
//      return false; // no further processing is needed.
//    }
//
//    default:
//      rv_errstrm << "Internal: RVDetachPointerValue::try_replace(): unable to process Expression: ";
//      s0p->print(rv_errstrm);  rv_errstrm << " \n";
//      return false; // THROW <<=== 
//  }
//}
//
//
//bool RVDetachPointerValue::fix_unary(UnaryExpr** pexpr)
//{
//  UnaryExpr* s0p = *pexpr;
//
//  REP_PROC( _operand );
//
//  switch( s0p->op() ) 
//  {
//    case UO_BitNot:    // ~
//      if( !try_replace_by_component( &s0p->_operand, V_COMP ) )
//	return false;
//      s0p->type = s0p->operand()->type;
//      return true;      
//
//    case UO_Not:       // !
//      if( !fix_boolean( &s0p->_operand ) )
//	return false;
//      s0p->type = new BaseType(BT_Bool);
//      return true;
//
//    case UO_Plus:      // +
//    case UO_Minus:     // -
//    case UO_PreInc:    // ++x  
//    case UO_PreDec:    // --x
//    case UO_PostInc:   // x++
//    case UO_PostDec:   // x--
//    case UO_Deref:     // *
//      return try_replace_by_component( &s0p->_operand, P_COMP );
//      /* in this case the expression type stays the same. */
//
//    case UO_AddrOf:    // &
//      /* take the whole struct */
//      return true;
//  }
//
//  return true;
//}
//
//
//bool RVDetachPointerValue::fix_binary(BinaryExpr** pexpr)
//{
//  BinaryExpr* s0p = *pexpr;
//
//  REP_PROC( _leftExpr );
//  REP_PROC( _rightExpr );
//
//  switch( s0p->op() ) 
//  {
//    case BO_Plus:        // +
//      /* pointer + displacement = array indexing: */
//      return try_replace_by_component( &s0p->_leftExpr, P_COMP ) && 
//	try_replace_by_component( &s0p->_leftExpr, P_COMP );
//      /* Note: the case of both '+' operands are pointers is prevented 
// 	   by RVTypeProp::process_binary(). */
//
//    case BO_Minus: {     // -
//      /* it may be difference between pointers  <<=== Works on CBMC ?! */
//      return try_replace_by_component( &s0p->_leftExpr, P_COMP ) && 
//	try_replace_by_component( &s0p->_leftExpr, P_COMP );
//    }
//
//    case BO_Mult:        // *
//    case BO_Div:         // /
//    case BO_Mod:         // %
//    case BO_Shl:         // <<
//    case BO_Shr:         // >>
//      if( find_expr_typesym( s0p->leftExpr() ) || 
//	  find_expr_typesym( s0p->rightExpr() ) ) {
//	rv_errstrm << "Warning: RVDetachPointerValue: awkward operation on pointer argument(s):\n  ";
//	s0p->print(rv_errstrm); rv_errstrm<<"\n  at: ";
//	s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
//	return false;
//      }
//
//    case BO_BitAnd:      // &
//    case BO_BitXor:      // ^
//    case BO_BitOr:       // |
//      /* do on the numeric value: */
//      return try_replace_by_component( &s0p->_leftExpr, V_COMP ) && 
//	try_replace_by_component( &s0p->_leftExpr, V_COMP );
//
//    case BO_And:         // &&
//    case BO_Or:          // ||
//      return fix_boolean( &s0p->_leftExpr ) && fix_boolean( &s0p->_rightExpr );
//
//    case BO_Comma:       // x,y
//    case BO_Member:      // x.y
//    case BO_PtrMember:   // x->y
//      /* leave as is */
//      return true;
//
//    case BO_Assign:      // An AssignExpr
//      return fix_assign( (AssignExpr**)pexpr );
//
//    case BO_Rel:          // A RelExpr
//      return fix_rel( (RelExpr**)pexpr );
//  }
//
//  return true;
//}
//
//
//bool RVDetachPointerValue::fix_assign(AssignExpr** pexpr)
//{
//  /* Note: We assume _leftExpr and _rightExpr where already processed ! */
//
//  AssignExpr* s0p = *pexpr;
//
//  switch( (*pexpr)->op() ) 
//  {
//    case AO_Equal:          //  =
//      /* as is */
//      return true;
//
//    case AO_PlusEql:        // +=
//    case AO_MinusEql:       // -=
//      /* pointer + displacement = array indexing: */
//      return try_replace_by_component( &s0p->_leftExpr, P_COMP );
//
//    case AO_MultEql:        // *=
//    case AO_DivEql:         // /=
//    case AO_ModEql:         // %=
//    case AO_ShlEql:         // <<=
//    case AO_ShrEql:         // >>=
//      if( find_expr_typesym( s0p->leftExpr() ) || 
//	  find_expr_typesym( s0p->rightExpr() ) ) {
//	rv_errstrm << "Warning: RVDetachPointerValue: awkward operation on pointer argument(s):\n  ";
//	s0p->print(rv_errstrm); rv_errstrm<<"\n  at: ";
//	s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
//	return false;
//      }
//
//    case AO_BitAndEql:      // &=
//    case AO_BitXorEql:      // ^=
//    case AO_BitOrEql:       // |=
//      /* do on the numeric value: */
//      return try_replace_by_component( &s0p->_leftExpr, V_COMP ) && 
//	try_replace_by_component( &s0p->_leftExpr, V_COMP );
//  }
//
//  return true;
//}
//
//
//SymEntry* RVDetachPointerValue::find_fix_func_entry(std::string& typesym_name, FixFunc func_ind)
//{
//  CHK_NULL1(parsetree, "RVDetachPointerValue::find_fix_func_entry()")
//  std::string fname = get_fix_func_name(typesym_name, func_ind);
//
//  ScopeTbl* scope = get_file_scope(parsetree);
//  SymEntry* func_ent = scope->Lookup(fname);
//  if( !func_ent ) 
//    rv_errstrm <<"Internal: unable to find declaration fix function \""<< fname <<
//      "\" (in RVDetachPointerValue::find_fix_func_entry()).\n";
//    
//  return func_ent;
//}
//
//
//Expression* RVDetachPointerValue::gen_fix_func_call(Expression* pl, Expression* pr, 
//						    FixFunc func_ind, unsigned rel_ind)
//{
//  CHK_NULL1(pl && (func_ind == IS_TRUE_FUNC || pr), "RVDetachPointerValue::gen_fix_func_call()"); 
//
//  Location& l = pl->location;
//  Symbol* typesym1 = find_expr_typesym(pl);
//  Symbol* typesym2 = NULL;
//  if( pr ) 
//    typesym2 = find_expr_typesym(pr);
//
//  if( !typesym1 && !typesym2 ) // niether is a type we should bother of
//    return NULL; // do nothing.
//
//  if( pr && ( (typesym1 != typesym2) || !typecomp.eq(pl->type, pr->type) ) )
//  {
//    rv_errstrm <<"Error: RVDetachPointerValue attempts to fix operation between different "
//      "pointer types.\n  at: ";
//    l.printLocation(rv_errstrm);
//    if( pl->type ) { 
//      rv_errstrm <<"\n  Left type: "; pl->type->printType(rv_errstrm, NULL, true, 0); }
//    if( pr->type ) { 
//      rv_errstrm <<"\n  Right type: "; pr->type->printType(rv_errstrm, NULL, true, 0); }
//     rv_errstrm<<"\n";
//  }
//
//  SymEntry* func_ent = find_fix_func_entry(typesym1->name, func_ind);
//  if( !func_ent )
//    return NULL;
//
//  Symbol* func_sym = mk_symbol(func_ent->name, func_ent);
//  FunctionCall* call = new FunctionCall(new Variable(func_sym, l), l);
//
//  call->args.push_back(new UnaryExpr(UO_AddrOf, pl, l));
//  if( pr )
//    call->args.push_back(new UnaryExpr(UO_AddrOf, pr, l));
//  if( func_ind == REL_FUNC )
//    call->args.push_back(new UIntConstant(rel_ind, false, l));
//  
//  call->type = uchar_type;
//
//  return call;
//}
//
//
//unsigned RVDetachPointerValue::get_rel_ind(RelOp op)
//{
//  switch( op ) {
//    case RO_Less:    return 0;  // < 
//    case RO_LessEql: return 1;  // <=
//    case RO_Grtr:    return 2;  // > 
//    case RO_GrtrEql: return 3;  // >=
//    default:
//      fatal_error("RVDetachPointerValue::get_rel_ind(): bad RelOp");
//      return 0;
//  }
//}
//
//bool RVDetachPointerValue::fix_rel(RelExpr** pexpr)
//{
//  /* Note: We assume _leftExpr and _rightExpr where already processed ! */
//
//  /* Note: we can't use macros to fix the next operatins because 
//       of possible side effects. */
//
//  RelExpr* s0p = *pexpr;
//
//  Expression* res = NULL;
//  bool make_not = false;
//
//  switch( s0p->op() ) 
//  {
//    case RO_NotEqual:       // !=
//      make_not = true;  // fallthru
//    case RO_Equal: {        // ==
//      Symbol* typesym1 = find_expr_typesym(s0p->leftExpr());
//      Symbol* typesym2 = find_expr_typesym(s0p->rightExpr());
//      
//      if( !typesym1 && !typesym2 )
//	return true; // do nothing
//
//      bool left_is_null  = is_const_null(s0p->leftExpr());
//      bool right_is_null = is_const_null(s0p->rightExpr());
//
//      if( left_is_null )  // check !(expr) on the other side
//	res = gen_fix_func_call(s0p->rightExpr(), NULL, IS_TRUE_FUNC, 0);
//      else if( right_is_null )
//	res = gen_fix_func_call(s0p->leftExpr(), NULL, IS_TRUE_FUNC, 0);	
//      else
//	res = gen_fix_func_call(s0p->leftExpr(), s0p->rightExpr(), EQ_FUNC, 0);
//
//      if( res == NULL )
//	return true; // no need to replace - or gen_fix_func error
//
//      if( left_is_null || right_is_null )
//	make_not = !make_not; // (expr == NULL) is equivalent to !(expr)
//
//      if( make_not ) {
//	res = new UnaryExpr(UO_Not, res, s0p->location);
//	res->type = new BaseType(BT_Bool);
//      }
//
//      *pexpr = (RelExpr*)res;
//      s0p->_leftExpr = s0p->_rightExpr = NULL;
//      delete s0p;
//      return true;
//    }
//
//    case RO_Less:           // < 
//    case RO_LessEql:        // <=
//    case RO_Grtr:           // > 
//    case RO_GrtrEql: {      // >=
//      unsigned rel_ind = get_rel_ind( s0p->op() );
//      res = gen_fix_func_call(s0p->leftExpr(), s0p->rightExpr(), REL_FUNC, rel_ind);
//      
//      if( res == NULL )
//	return true; // no need to replace - or gen_fix_func error
//
//      *pexpr = (RelExpr*)res;
//      s0p->_leftExpr = s0p->_rightExpr = NULL;
//      delete s0p;
//      return true;
//    }
//  }
//
//  return true;
//}
//
//
//bool RVDetachPointerValue::fix_boolean(Expression** pexpr)
//{
//  CHK_NULL1(pexpr, "RVDetachPointerValue::fix_boolean()");
//  if( !*pexpr )
//    return true; // probably empty condition in for() or while() statement.
//
//  Expression* res = gen_fix_func_call(*pexpr, NULL, IS_TRUE_FUNC, 0);
//  if( res == NULL )
//    return true; // no need to replace - or gen_fix_func error
//
//  *pexpr = res;  
//  return true;
//}
//
//
//bool RVDetachPointerValue::try_fix_member_op_type(Expression* s0p)
//{
//  if( !s0p || s0p->etype != ET_BinaryExpr || ((BinaryExpr*)s0p)->op() != BO_Member )
//    return true;
//
//  /* check it is some .p or .v expression */
//  Variable* var = (Variable*)((BinaryExpr*)s0p)->rightExpr();
//  if( var->etype != ET_Variable || !var->name )
//    return true;
//
//  std::string comp_name = var->name->name;
//  if( comp_name != detach_comp_names[0] && comp_name != detach_comp_names[1] )
//    return true;
//
//  RVTypeProp prop(where);
//
//rv_errstrm<<"Did RVTypeProp at: ";
//s0p->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
// 
//  return prop.process(s0p);
//}
//
//
//bool RVDetachPointerValue::gen_all_fix_funcs(RVTemp& temps)
//{
//  bool ret = true;
//
//  /* generate the bodies of 3 fix funcs for each typesym */
//  SymbolVector& vec = typesyms[side];
//  SymbolVector::const_iterator i;
//  FORVEC(i, vec) {
//    ret = gen_det_eq_func(temps, (*i)->name);
//    ret = gen_det_rel_func(temps, (*i)->name);
//    ret = gen_det_2bool_func(temps, (*i)->name);
//  }
//
//  return ret;
//}
//
//
//bool RVDetachPointerValue::gen_det_eq_func(RVTemp& temps, std::string& typesym_name)
//{  
//  SymEntry* ent = find_fix_func_entry(typesym_name, EQ_FUNC);
//  if( !ent )
//    return false;
//
//  ent->uVarDecl->print(temps.get_strm(), true, 0);
//
//  temps.get_strm() <<
//"\n{\n"
//"  return( pl->p == pr->p && pl->v == pr->v );\n"
//"}\n\n";
//
//  return true;
//}
//
//
//bool RVDetachPointerValue::gen_det_rel_func(RVTemp& temps, std::string& typesym_name)
//{  
//  SymEntry* ent = find_fix_func_entry(typesym_name, REL_FUNC);
//  if( !ent )
//    return false;
//
//  ent->uVarDecl->print(temps.get_strm(), true, 0);
//
//  temps.get_strm() <<
//"\n{\n"
//"  unsigned char not = 0;\n"
//"  unsigned char ret;\n\n"
//"  /* we assume that the numeric value is in the LS bits of the original pointer */\n"    
//"  switch( rel_code ) {\n"
//"    case 3: not = 1; /* >= (fallthru) */"
//"    case 0: ret = (pl->p < pr->l || (pl->p == pr->p && pl->v < pr->v)); break; /* < */\n"
//"    case 1: not = 1; /* <= (fallthru) */"
//"    case 2: ret = (pl->p > pr->l || (pl->p == pr->p && pl->v > pr->v)); break; /* > */\n"
//"    /* Check: the relation code is valid: */\n"
//"    default: assert( 0 );\n"
//"  }\n"
//"  return(not ? !ret : ret);\n"
//"}\n\n";
//
//  return true;
//}
//
//
//bool RVDetachPointerValue::gen_det_2bool_func(RVTemp& temps, std::string& typesym_name)
//{
//  SymEntry* ent = find_fix_func_entry(typesym_name, IS_TRUE_FUNC);
//  if( !ent )
//    return false;
//
//  ent->uVarDecl->print(temps.get_strm(), true, 0);
//
//  temps.get_strm() <<
//"\n{\n"
//"  return( pl->p == ((void*)0) && pl->v == 0 );\n"
//"}\n\n";
//
//  return true;
//}
