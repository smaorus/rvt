#include <rv_consts.h> 
#include <rv_error.h>
#include <rv_macros.h>
#include <rv_tokens.h>
#include <rv_replace.h>
#include <rv_propagate.h>
#include <rv_temps.h>
#include <rv_tkn_gen.h>
#include <string.h>

#define RV_SECTION RV_SEC_TOKENS


// DEBUG <<=== DEL
bool bla(std::string bb)
{if(DBG) rv_errstrm<<bb<<"\n"; return false;}


/* RVStrRec */
/*==========*/

RVStrRec::RVStrRec()
{
  side = otype = -1;
  strdecl = tkndecl = NULL;
  tknutp = strutp = NULL;
  printed_funcs = print_typedef = false;
  other_side = NULL;
}


bool RVStrRec::rename(RVRenameTree& ren)
{
  bool ret = true;

  ret = ren.process(strutp) && ren.process(strdecl) && ren.process(strdecl->name) && ret;
  ret = ren.process(tknutp) && ren.process(tkndecl) && ren.process(tkndecl->name) && ret;
  ret = ren.process(funcs) && ret;

  /* !Note: we keep strname and tknname in their original format 
        (to be consistant with RVStrRecIndex::by_tknname index).
      And we don't rename orig_type.
   */
    
  return ret;
}


/* RVStrRecIndex */
/*===============*/

RVStrRecIndex::~RVStrRecIndex()
{
  std::vector<RVStrRec*>::iterator i;
  FORVEC(i, vec)
    delete (*i);
}

bool RVStrRecIndex::add(RVStrRec* rec)
{
  CHK_NULL1(rec, "RVStrRecIndex::add()");

  if( rec->tknname == "" )
    rec->tknname = RVStructs::name_struct2token(rec->strname);
  
  if( get_by_tknname(rec->tknname) ) {
    rv_errstrm << "Error: RVStrRecIndex::add(): two RVStrRecs with same Token name: \""<<
      rec->tknname <<"\", on side "<< my_side;
    if( rec->strdecl ) {
      rv_errstrm << ", for type: \n";
      rec->strdecl->print(rv_errstrm,true); 
    }
    rv_errstrm << " \n";
    
    return false;
  }

  vec.push_back(rec);
  by_tknname.insert( std::pair<std::string, RVStrRec*>(rec->tknname, rec) );
  by_orig_type.insert( std::pair<Type*, RVStrRec*>(rec->orig_type, rec) );
  by_str_type.insert( std::pair<Type*, RVStrRec*>(rec->strdecl->form, rec) );
  by_tkn_type.insert( std::pair<Type*, RVStrRec*>(rec->tkndecl->form, rec) );
  
  count++;
  return true;
}

RVStrRec* RVStrRecIndex::get_by_tknname(std::string& tknname)
{
  std::map<std::string, RVStrRec*>::iterator i;
  i = by_tknname.find(tknname);
  if( i == by_tknname.end() )
    return NULL;
  return (*i).second;
}

RVStrRec* RVStrRecIndex::get_by_strname(std::string& strname)
{
  std::string tknname = RVStructs::name_struct2token(strname);
  return get_by_tknname(tknname);
}

RVStrRec* RVStrRecIndex::get_by_orig_type(Type* orig_type)
{
  std::map<Type*, RVStrRec*>::iterator i;
  i = by_orig_type.find(orig_type);
  if( i != by_orig_type.end() )
    return (*i).second;

  /* if the type is not original - find a simmilar one: */
  RVTreeComp comp(false, true);
  RVStrRecVec::const_iterator j;
  FORVEC(j, vec)
    if( comp.eq_type((*j)->orig_type, orig_type) ) {   
      /* add this type pointer to the index: */
      by_orig_type.insert( std::pair<Type*, RVStrRec*>(orig_type, (*j)) );
      return (*j);
    }
  
  return NULL;
}

RVStrRec* RVStrRecIndex::get_by_str_type(Type* str_type)
{
  std::map<Type*, RVStrRec*>::const_iterator i;
  i = by_str_type.find(str_type);
  if( i != by_str_type.end() )
    return (*i).second;

  /* if the type is not original - find a simmilar one: */
  RVTreeComp comp(false, true);
  RVStrRecVec::const_iterator j;
  FORVEC(j, vec) {
if(DBG) rv_errstrm<<"*";    
    if( comp.eq_type((*j)->strdecl->form, str_type) )  {
      by_str_type.insert( std::pair<Type*, RVStrRec*>(str_type, (*j)) );
if(DBG) rv_errstrm<<"SAAACA\n";          
      return (*j);
    }
  }
  
if(DBG) rv_errstrm<<"BAABAA\n";
  return NULL;
}

RVStrRec* RVStrRecIndex::get_by_tkn_type(Type* tkn_type)
{
  std::map<Type*, RVStrRec*>::const_iterator i;
  i = by_tkn_type.find(tkn_type);
  if( i != by_tkn_type.end() )
    return (*i).second;

  /* if the type is not original - find a simmilar one: */
  RVTreeComp comp(false, true);
  RVStrRecVec::const_iterator j;
  FORVEC(j, vec)
    if( comp.eq_type((*j)->tkndecl->form, tkn_type) ) {  // MAYBE use tagname instead StructDef <<===
      /* add this type pointer to the index: */
      by_tkn_type.insert( std::pair<Type*, RVStrRec*>(tkn_type, (*j)) );
      return (*j);
    }

  return NULL;
}




/* RVStructs */
/*===========*/

const char* RVStructs::TKN_SUFFIX = "_tkn";

const int   RVStructs::tkn_suffix_len = strlen(TKN_SUFFIX);

const char* RVStructs::MARKS = "marks";
const char* RVStructs::OTYPE = "otype";
const char* RVStructs::REALM = "realm";
const char* RVStructs::ONUM  = "onum";
const char* RVStructs::ARR_IND = "arr_ind";

const char* RVStructs::USER_TYPE_PREFIX = "ut_";
const char* RVStructs::TAG_PREFIX       = "tg_";
const char* RVStructs::STR_ENUM_PREFIX  = "RVST_";
const char* RVStructs::STR_ENUM_NAME    = "RVStructType";


RVStructs::RVStructs(RVGlobLists* _orig_progs, Project* parsetree_copy[2])
{ 
  orig_progs = _orig_progs;
  res_parsetree[0] = parsetree_copy[0];
  res_parsetree[1] = parsetree_copy[1];

  recind[0].set_side(0);
  recind[1].set_side(1);

  gen_side = -1; 
  where = "UNKNOWN"; 
  enum_RVStructType = NULL;
  tp_int = tp_unsigned_char = 
    tp_signed_char = tp_enum_RVStructType = NULL; 
}

RVStructs::~RVStructs()
{
  RVParse::delete_parsetree(res_parsetree[0]);
  RVParse::delete_parsetree(res_parsetree[1]);
  /* all types (tp_...) are deleted thru their respective parsetrees. */
}


void RVStructs::set_global_where(int side)
{
  if( side )
    set_where("Global Scope Side 1");
  else
    set_where("Global Scope Side 0");
}


std::string RVStructs::gen_name_for_token(std::string& token_name, RVNameType nt, 
					  int side /*=-1*/, bool side_pref/*=false*/)
{
  if( side != 0 && side != 1 ) {
    rv_errstrm << "RVStructs::gen_name_for_token( "<< token_name <<" ) got bad side value: "
               << side <<"\n";
    return "BAD_SIDE";
  }

  std::string pref("");
  if( side_pref )
    pref = (side ? RV_SIDE1_PREFIX : RV_SIDE0_PREFIX);

  switch( nt ) 
  {
    case NT_COMP: return(pref + token_name + "_comp");
    case NT_SUB:  return(pref + token_name + "_sub");
    case NT_DEREF:return(pref + token_name + "_drf");
    case NT_NULL: return(pref + token_name + "_NULL");
    default: 
      rv_errstrm << "RVStructs::gen_name_for_token( "<< token_name <<" ) got bad RVNameType: "
                 << nt <<"\n";
      return "BAD_NAME_TYPE";
  }
}


std::string RVStructs::gen_name_for_struct(std::string& struct_name, RVNameType nt,
					   int side /*=-1*/, bool side_pref/*=false*/)
{
  std::string pref("");
  if( side_pref )
    pref = (side ? RV_SIDE1_PREFIX : RV_SIDE0_PREFIX);
  
  std::string ret("BAD_NAME");
  
  if( ( (nt == NT_MALLOC || nt == NT_FREE || nt == NT_ARRAY ) && (side != 0 && side != 1)) ) {
    rv_errstrm << "RVStructs::gen_name_for_struct( "<< struct_name <<" ) got bad side value: "
               << side <<"\n";
    return "BAD_SIDE";
  }

  switch( nt ) 
  {
    case NT_MALLOC: return(pref + struct_name + "_malloc");
    case NT_FREE:   return(pref + struct_name + "_free");
    case NT_ARRAY:  return(pref + struct_name + "_array");
    default: 
      rv_errstrm << "RVStructs::gen_name_for_struct( "<< struct_name <<" ) got bad RVNameType: "
                 << nt <<"\n";
      return "BAD_NAME_TYPE";      
  }
}


bool RVStructs::is_aggregate(Type* tp)
{
  tp = real_type(tp, where);

//if(DBG){rv_errstrm<<"RVStructs::is_aggregate():\n";
// tp->printType (rv_errstrm, NULL, true, 0); rv_errstrm<<" \n";}

   bool res = is_basetype(tp, (BT_Struct | BT_Union));

   res = !is_token(tp) && res; // tokens doesn't count.

   return res;
}


bool RVStructs::is_aggregate_pointer(Type* tp, Type** pstrtype)
{
  Type* strtp = NULL;
  bool ret = 
    is_pointer(tp, where, &strtp) && is_aggregate(strtp);

//if(DBG) rv_errstrm<<"RVStructs::is_aggregate_pointer() returns "<< ret <<"\n";

  /* Note: changes pstrtype value only when really a struct pointer: */
  if( ret && pstrtype )
    *pstrtype = strtp;
  return ret;
}


Type* RVStructs::related_side0_type(Type* side1tp, Type* origtp1 /*= NULL*/)
{
  CHK_NULL1(side1tp, "side1tp in RVStructs::related_side0_type()");

  SymEntry* ent = NULL;
  RVStrRec* rec = NULL;

bla("PFPFPF");

  Type* ret = NULL; //side1tp->equalTo;  // <<=== BIG PROBLEM after convert_struct()
  if( ret )
    return ret;

bla("HUHU");

  // Try to find it thru Tuple - take the type on the other side:
  if( !ret ) {
    rec = recind[1].get_by_str_type(side1tp);
    if( rec && rec->other_side && rec->other_side->strdecl )
      ret = rec->other_side->strdecl->form;
  }

  // Try to find it thru the orig_progs:
  if( !ret && origtp1 && origtp1->equalTo ) {
    /* find the side 0 equivalent in the new code: */
    rec = recind[0].get_by_orig_type(origtp1->equalTo);
    if( rec )
      ret = rec->strdecl->form;
  }

  /* try to find by same tag name: */
  if( !ret && is_basetype(side1tp, (BT_Struct|BT_Union)) && ((BaseType*)side1tp)->tag ) {
    std::string& tag_name = ((BaseType*)side1tp)->tag->name;
    ScopeTbl* tag_scope = get_file_tags(res_parsetree[0]);
    if( tag_scope && tag_name != "" && (ent = tag_scope->Lookup(tag_name)) )
      ret = get_symbol_type(ent, where);
  }
  
  /* try to find by user type name: */
  if( !ret && is_basetype(side1tp) && ((BaseType*)side1tp)->typeName ) {
    std::string& sym_name = ((BaseType*)side1tp)->typeName->name;
    ScopeTbl* sym_scope = get_file_scope(res_parsetree[0]);
    if( sym_scope && sym_name != "" && (ent = sym_scope->Lookup(sym_name)) )
      ret = get_symbol_type(ent, where);
  }
  
  RVTreeComp comp(false, false);    // component names *may* differ ! 
  if( ret && comp.eq_type(ret, side1tp) ) {
    side1tp->equalTo = ret;
    ret->equalTo = side1tp;
bla("OKOKOKOK");
  }
  else {
    rv_errstrm << "Error: related_side0_type() unable to find related side 0 type of \""<<
      ( (side1tp->isBaseType() && ((BaseType*)side1tp)->tag) ? 
	((BaseType*)side1tp)->tag->name.data() : "UNKNOWN" ) <<
      "\" on side 1. in \""<< where <<"\" the side 1 type is: \n";
    side1tp->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
  }

bla("ULAULA");

  return ret;
}


Type* RVStructs::get_same_type(Type* tp, Project* tree)
{
  CHK_NULL1(tp && tree, "tp or tree in RVStructs::get_same_type()");

  if( !is_basetype(tp, (BT_UserType|BT_Struct|BT_Union|BT_Enum)) ) {
    rv_errstrm << "Warning: unable to relate type to original one in: \""<< where <<"\" type:\n";
    tp->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
    return NULL;
  }

  RVTreeComp comp(false, true); // force equal component names
  Decl* decl = NULL;
  Type* ret = NULL;
  ScopeTbl* scp = NULL;
  SymEntry* ent = NULL;
  BaseType* bt = (BaseType*)tp;

  /* first try by type name: */
  if( bt->typeName ) {
    scp = get_file_scope(tree);
    if( scp && (ent = scp->Find(bt->typeName->name)) && 
	(ret = get_symbol_type(ent, where)) && comp.eq_type(ret, tp) )
      return real_type(ret, where);
  }

  /* then by tag name (if struct): */
  if( bt->tag ) {
    scp = get_file_tags(tree);
    if( scp && (ent = scp->Find(bt->tag->name)) && 
	(ret = get_symbol_type(ent, where)) && comp.eq_type(ret, tp) )
      return real_type(ret, where);
  }
  
  /* else try by struct form: */
  if( (bt->typemask & (BT_Struct|BT_Union)) ) {
    if( (decl = find_user_type_decl(bt, tree)) && 
	(ret = decl->form) && comp.eq_type(ret, tp) )
      return real_type(ret, where);
  }
	
  rv_errstrm << "Internal: RVStructs::get_same_type() failed to find (in \""<<
    where <<"\") type: \n";
  bt->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
  
  return NULL;
}


Decl* RVStructs::find_user_type_decl(Type* strtp, Project* pt) 
{
  CHK_NULL1(strtp, "strtp in RVStructs::find_user_type_decl()");

  /* searches only struct types: */
  if( !is_basetype(strtp, (BT_Struct|BT_Union)) )
    return NULL;


  StructDef* strdef = ((BaseType*)strtp)->stDefn;
  if( !strdef ) {
    SymEntry* ent = NULL;
    BaseType* tagtp = NULL;
    ScopeTbl* tag_scope = get_file_tags(pt);

    if( tag_scope && ((BaseType*)strtp)->tag )
      ent = tag_scope->Find(((BaseType*)strtp)->tag->name);
    if( ent )
      tagtp = ent->uStructDef;
    if( tagtp )
      strdef = tagtp->stDefn;
  }
  if( !strdef ) {
    rv_errstrm<<"Error: can't find components of struct directly (stDefn) or using tag name:\n";
    strtp->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
    return NULL;
  }

  RVTreeComp comp(false, true);   // require equal component names
  DeclVector::const_iterator j;
  BaseType* itemtp;
  Statement* st = get_glob_stemnt(pt);

bla("KKK");
  for(; st; st = st->next) 
    if( st->isDeclaration() )
      FORVEC(j, ((DeclStemnt*)st)->decls) {
bla("SSS");
if(DBG){(*j)->print(rv_errstrm, true); rv_errstrm<<";\n";}
        if( (*j)->isTypedef() && !bla("WWW") ) {
bla("LLL");          
          itemtp = (BaseType*)get_symbol_type((*j)->name, where);
bla("JJJ");          
          /* if it is struct def and it equals strdef up to component names: */
          if( is_basetype(itemtp, (BT_Struct | BT_Union)) && !bla("UUU") &&
              (itemtp->stDefn == strdef || bla("HHH") || comp.eq_struct_def(itemtp->stDefn, strdef)) )
            return (*j);
        }
    }
bla("ZZZ");
  return NULL;
}


bool RVStructs::search_type_tag(Type* tp, BaseType** out_strdef, std::string* out_tagname)
  // returns true when finds the tag name
{
  Symbol* tag = NULL;

  if( !tp || !is_aggregate(tp) )
    return false;

  tp = real_type(tp, where);

  if( is_basetype(tp, (BT_Struct|BT_Union)) ) {
    if( out_strdef )
      *out_strdef = (BaseType*)tp;
    if( (tag = ((BaseType*)tp)->tag) && (tag->name != "") && tag->entry ) {
      if( out_tagname )
	*out_tagname = tag->name;
      return true;
    }
  }

  return false;
}

bool RVStructs::search_typedef(Type* tp, Decl** out_decl, std::string* out_type_name)
  // returns true when finds.
{
  Symbol* sym = NULL;
  SymEntry* ent = NULL;
  Decl* decl = NULL;

  /* Only for structs: */
  if( !tp || !is_aggregate(tp) )
    return false;

  /* if the type itself is user-type - return its name and decl: */
  if( is_basetype(tp, BT_UserType) && (sym = ((BaseType*)tp)->typeName) &&
      (ent = sym->entry) && ent->IsTypeDef() && (decl = ent->uVarDecl) &&
      decl->isTypedef() ) {
    if( out_decl )
      *out_decl = decl;
    if( out_type_name )
      *out_type_name = sym->name;
    return true;
  }

  /* otherwise search its user-type: */
  if( is_basetype(tp, (BT_Struct|BT_Union)) &&
      (decl = find_user_type_decl(tp, res_parsetree[gen_side])) )
  {    

if(DBG){rv_errstrm<<"Found user_type_dec:\n";
 decl->print(rv_errstrm, true); rv_errstrm<<";\n";}

    if( out_decl )
      *out_decl = decl;
    if( out_type_name )
      *out_type_name = decl->name->name;
    return true;
  }

  return false;
}


std::string RVStructs::make_struct_name_and_tag(Type* strtp, RVStrRec* rec /*= NULL*/)
  // returns the name of the user-type
{
  if( !strtp ) 
    fatal_error((char *) "strtp is NULL in RVStructs::make_struct_name_and_tag", false);

  std::string tagname("");
  std::string strname("");;
  BaseType* tag_type = NULL;
  Decl* user_type_decl = NULL;

  bool has_tag = search_type_tag(strtp, &tag_type, &tagname);
  bool has_typedef = search_typedef(strtp, &user_type_decl, &strname);

  if( !has_tag && !has_typedef ) {
    rv_errstrm << "Internal: can't find tag definition or user type declaration for:\n";
    strtp->printType(rv_errstrm, NULL, true, 0); 
    rv_errstrm << " \n  in: \""<< where <<"\", side "<< gen_side <<" \n";
    return "NO_TYPE_NAME";
  }
 
  if( !has_typedef )
    strname = USER_TYPE_PREFIX + tagname;

  /* if we have the record - we add the missing definition: */
  if( rec ) {

    if( !has_tag && tag_type ) {
      tagname = TAG_PREFIX + strname;

      Symbol* tag = mk_symbol(tagname, mk_tag(tagname, tag_type));
      tag_type->tag = tag;

      /* add it to tag scope */
      ScopeTbl* tag_scope = get_file_tags(res_parsetree[gen_side]);
      if( !tag_scope )
	tag_scope = create_last_scope(res_parsetree[gen_side], FILE_SCOPE, NULL, TagEntry);
      tag_scope->Insert( tag->entry );
      tag->entry->scope = tag_scope;
    }

    ScopeTbl* scope = get_file_scope(res_parsetree[gen_side]);
    Symbol* sym = NULL;
    SymEntry* ent = NULL;

    if( !has_typedef ) {
      if( !tag_type || !is_basetype(tag_type, (BT_Struct|BT_Union)) ) {
	rv_errstrm << "Internal: if we dont have typedef of: \n";
	strtp->printType(rv_errstrm, NULL, true, 0); 
	rv_errstrm << "  we at least must have tag declaration !!, in: \""
		   << where <<"\" side "<< gen_side <<"\n";
	fatal_error((char *) "make_struct_name_and_tag(): No typedef or tag definition !", false);
      }

      BaseType *decltp = (BaseType*)tag_type->dup();
      decltp->stDefn = NULL; // keep only the tag - don't print all components.

      user_type_decl = new Decl(decltp);
      sym = mk_symbol(strname, mk_typedef(strname, user_type_decl));
      user_type_decl->name = sym;
      user_type_decl->storage = ST_Typedef;
      
      /* add it to symbol scope */
      scope->Insert( sym->entry );
      sym->entry->scope = scope;

      /* the typedef is new - we need to print it */
      rec->print_typedef = true;
    }
    
    /* Set the official declaration of this type to user_type_decl: */
    rec->strdecl = user_type_decl;

    /* gen BaseType(BT_UserType) for strname symbol: */
    if( !sym ) {
      if( (ent = scope->Find( strname )) )
	sym = mk_symbol(strname, ent);
      if( !sym )
	fatal_error((char *) "make_struct_name_and_tag() can't get struct symbol: ", strname, false);
    }
    rec->strutp = new BaseType(BT_UserType);
    ((BaseType*)rec->strutp)->typeName = sym;

  } /* rec */

  return strname;
}


int RVStructs::add_enum_RVStructType(std::string& str_name)
{
  CHK_NULL1(enum_RVStructType, "enum_RVStructType in RVStructs::add_enum_RVStructType()");

  std::string ename = STR_ENUM_PREFIX + str_name;  

  Symbol* comp_sym = mk_symbol(ename, mk_enum_const(ename, NULL /*enumVal*/));
  comp_sym->entry->u2EnumDef = enum_RVStructType;
  
  enum_RVStructType->addElement(comp_sym);
  
  return enum_RVStructType->nElements -1;
}


bool RVStructs::gen_token_component_types()
{
  Location l(__LINE__,0,__FILE__);

  if( !tp_int ) 
  {
    /* create enum RVStructType: */
    enum_RVStructType = new EnumDef();
    Symbol* esym = mk_symbol(STR_ENUM_NAME, mk_tag(STR_ENUM_NAME,NULL));
    enum_RVStructType->tag = esym;
    tp_enum_RVStructType = new BaseType(enum_RVStructType);  /* copies the tag */
    esym->entry->uStructDef = tp_enum_RVStructType;
    esym->entry->scope = NULL;

    /* add NO_STRUCT=0 as first item in the enum: */
    std::string ename(STR_ENUM_PREFIX);
    ename += "NO_STRUCT";
    IntConstant* enumVal = new IntConstant(0, false, l);
    Symbol* comp_sym = mk_symbol(ename, mk_enum_const(ename, enumVal));
    comp_sym->entry->u2EnumDef = enum_RVStructType;
    comp_sym->entry->scope = NULL;
    enum_RVStructType->addElement(comp_sym);
  
    tp_unsigned_char = new BaseType(BT_Char | BT_UnSigned);
    tp_signed_char = new BaseType(BT_Char | BT_Signed);
    tp_int = new BaseType(BT_Int);
  }

  return true;
}


SymEntry* RVStructs::replace_symentry(SymEntry* newent, ScopeTbl* in_scope /* = NULL */)
{
  CHK_NULL1(newent, "newent in RVStructs::replace_symentry()");

  if( !in_scope )
    in_scope = newent->scope;
  CHK_NULL1(in_scope, "in_scope in RVStructs::replace_symentry()");

  SymEntry* oldent = ScopeTbl_remove(in_scope, newent->name);
  in_scope->Insert( newent );
  newent->scope = in_scope;

  return oldent;
}


Decl* RVStructs::gen_struct_token_typedef(Decl* strdecl)
{
  static std::string decl_where;
  CHK_NULL1(strdecl && strdecl->name && strdecl->name->entry, 
            "strdecl in RVStructs::gen_struct_token_typedef");

  decl_where = "Declaration (1) of " + strdecl->name->name;
  set_where(decl_where.data());

if(DBG){rv_errstrm<<"gen_struct_token_typedef() on "<<where<<"\n";}

  Decl* tkn_decl = NULL;
  SymEntry* tkn_ent = NULL;
  Type* strtp = strdecl->form;  // MAYBE get_symbol_type(strdecl->name,) ? <<=== 

  // if the struct doesn't have tag - add it a tag at the top scope (?): 
  ScopeTbl* tag_scope = get_file_tags(res_parsetree[gen_side]);
  if( !tag_scope )
    tag_scope = create_last_scope(res_parsetree[gen_side], FILE_SCOPE, NULL, TagEntry);

  // gen token name (from tag or user type name)
  std::string str_name = make_struct_name_and_tag(strtp);
  std::string tkn_utname  = name_struct2token(str_name);  // user type name 
  std::string tkn_tagname = TAG_PREFIX + tkn_utname;      // tag name

  // if already generated it - do nothing. 
  if( tag_scope && (tkn_ent = tag_scope->Lookup(tkn_tagname)) ) {
    tkn_decl = tkn_ent->uVarDecl;
    return tkn_decl;
  }

  // gen standard token struct def { OTYPE, ... }
  StructDef* tkndef = new StructDef( false );
  tkndef->tag = mk_symbol(tkn_tagname, mk_tag(tkn_tagname, NULL));

  BaseType* tmp_enum_otype = (BaseType*)tp_enum_RVStructType->dup0();
  tmp_enum_otype->enDefn = NULL;  // keep only the tag name - not all vals.

  add_strdef_component(tkndef, MARKS, tp_unsigned_char);
  add_strdef_component(tkndef, OTYPE, tmp_enum_otype);
  add_strdef_component(tkndef, REALM, tp_unsigned_char);
  add_strdef_component(tkndef, ONUM,  tp_signed_char);
  add_strdef_component(tkndef, ARR_IND, tp_int);

  BaseType* tkntp = new BaseType(tkndef);  /* copies the tag */
  tkndef->tag->entry->uStructDef = tkntp;
  tag_scope->Insert(tkndef->tag->entry);

  // create the token typedef decl 
  tkn_ent = mk_typedef(tkn_utname, NULL);
  Symbol* tkn_sym = mk_symbol(tkn_utname, tkn_ent); 
  tkn_decl = new Decl(tkntp);
  tkn_decl->name = tkn_sym;
  tkn_decl->storage = ST_Typedef;
  tkn_ent->uVarDecl = tkn_decl;

  str_tkn[gen_side].push_back(tkn_decl);

  ScopeTbl* sym_scope = get_file_scope(res_parsetree[gen_side]);
  sym_scope->Insert(tkn_ent);

if(DBG){rv_errstrm<<"gen_struct_token_typedef() result:\n";
 tkn_decl->print(rv_errstrm, true); rv_errstrm<<";\n";}

  return tkn_decl;
}


StructDef* RVStructs::convert_struct(StructDef* strdef)
  // converst struct in-place - all pointer types become Tokens.
{
  Decl* decl = NULL;
  std::string strname,tknname;
  Type *strtp, *tkntp;

  RVStrIter it(strdef);
  FORIT(decl,it)
    if( is_aggregate_pointer(decl->form, &strtp) ) {
      tkntp = type_struct2token(strtp, gen_side);
      decl->form = tkntp;
    }   
    
  return strdef;
}    


Decl* RVStructs::mk_func_decl(FunctionType* ftp, RVNameType nt, 
                              std::string& name_base, bool tkn_base, RVStrRec* rec)
{
  if( !ftp || !rec )
    fatal_error((char *) "In RVStructs::mk_func_decl(): ftp or rec is NULL.", false);

  std::string fname;

  if( tkn_base )
    fname = gen_name_for_token(name_base, nt, gen_side);
  else {
    fname = gen_name_for_struct(name_base, nt, gen_side);
  }

  Decl* decl = mk_global_decl(res_parsetree[gen_side], ftp, fname);

  // Add all decls to type's rec:
  rec->funcs.push_back(decl);

if(DBG){rv_errstrm<<"mk_func_decl() result:\n";
 decl->print(rv_errstrm, true); rv_errstrm<<";\n";}

  return decl;
}


bool RVStructs::add_new_func_decls(RVStrRec* rec)
{
  CHK_NULL1(rec, "rec in RVStructs::add_new_func_decls()");

  bool ret = true;
  ScopeTbl* proto_scope = NULL; /* protos don't need scopes <<=== (?) */
  std::string fname;
  Type* tkntp = NULL;
  PtrType* tknptrtp = NULL;

  Type* strtp = rec->strutp;
  PtrType* strptrtp = new PtrType();
  strptrtp->subType = strtp;

  tkntp = rec->tknutp;
  tknptrtp = new PtrType();
  tknptrtp->subType = tkntp;

  // Generate prototypes (decls) for funcs:

  // NT_COMP:
  FunctionType* comptp = new FunctionType();
  comptp->subType = tp_int;

  add_func_param(comptp, "tkn1", tkntp, proto_scope);
  add_func_param(comptp, "tkn2", tkntp, proto_scope);
  mk_func_decl(comptp, NT_COMP, rec->tknname, true, rec);
  

  // NT_SUB
  FunctionType* subtp = (FunctionType*)comptp->dup0();
  mk_func_decl(subtp, NT_SUB, rec->tknname , true, rec);


  // NT_DEREF
  FunctionType* drftp = new FunctionType();
  drftp->subType = new PtrType();
  ((PtrType*)drftp->subType)->subType = strtp;

  add_func_param(drftp, "ptkn", tknptrtp, proto_scope);
  mk_func_decl(drftp, NT_DEREF, rec->tknname , true, rec);


  // NT_MALLOC 
  FunctionType* mlctp = new FunctionType();
  mlctp->subType = tkntp;

  add_func_param(mlctp, "size", tp_int, proto_scope);
  mk_func_decl(mlctp, NT_MALLOC, rec->strname, false, rec);


  // NT_FREE
  FunctionType* freetp = new FunctionType();
  freetp->subType = new BaseType(BT_Void);

  add_func_param(freetp, "tkn", tknptrtp, proto_scope);
  mk_func_decl(freetp, NT_FREE, rec->strname, false, rec);

  return ret;
}


bool RVStructs::process_one_struct(Decl* strdecl)
  // Decl replace is done in-place
{
  static std::string decl_where;
  bool ret = true;
  RVStrRec* rec = NULL;

  if( !strdecl || !is_aggregate(strdecl->form) ) {
    rv_errstrm << "Internal: NULL or non-struct type Decl (in "
               << where <<", side "<< gen_side <<") ";
    if(strdecl) { strdecl->print(rv_errstrm,true); rv_errstrm << "\n"; }
    return false;
  }

  decl_where = "Declaration (2) of " + strdecl->name->name;
  set_where(decl_where.data());

  BaseType* strtp = (BaseType*)real_type(strdecl->form, where);

  /* don't process twice the same struct type: */
  if( (rec = recind[gen_side].get_by_str_type(strtp)) ) {

if(DBG){rv_errstrm<<"process_one_struct() second time on:\n";
 strtp->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<" \n";}

    return true;
  }

  rec = new RVStrRec;
  rec->side = gen_side;
  
  /* find/make struct typedef name and set rec->strdecl: */
  rec->strname = make_struct_name_and_tag(strdecl->form, rec);

  Type* orig_type = get_same_type(strtp, orig_progs->get_parsetree(gen_side));
  rec->orig_type = orig_type;

  StructDef* strdef = strtp->stDefn;
  convert_struct(strdef);

  // insert the result to converted[gen_side]
  converted[gen_side].push_back(rec->strdecl);
  
  rec->tknname = name_struct2token(rec->strname); 
  rec->tknutp = get_token_type(rec->tknname, gen_side);

  ScopeTbl* sym_scope = get_file_scope(res_parsetree[gen_side]);
  SymEntry* tkn_ent = sym_scope->Lookup(rec->tknname);  
  if( !tkn_ent || !tkn_ent->uVarDecl ) {
    rv_errstrm << "Inernal: unable to find SymEntry of token type \""<< rec->tknname <<
      "\" of struct type: ";
    strdecl->print(rv_errstrm,true); rv_errstrm << "\n";
    delete rec;
    return false;
  }
  rec->tkndecl = tkn_ent->uVarDecl;

  if( gen_side == 0 ) {
    // add it to enum_RVStructType
    rec->otype = add_enum_RVStructType(rec->strname);
  } 
  else { /* side 1 */
    /* connect this record to its side 0 counterpart: */
    Type* side0tp = related_side0_type(strtp, orig_type);

if(DBG){rv_errstrm<<"Related type:\n";
 if(side0tp) side0tp->printType (rv_errstrm, NULL, true, 0); rv_errstrm<<" \n";}


    RVStrRec* rec0 = recind[0].get_by_str_type(side0tp);

    if( !rec0 ) {
      rv_errstrm << "Error: in \""<< where <<"\", unable to find related"
	" side 0 type record (RVStrRec) to side 1 type:\n";
      strdecl->print(rv_errstrm,true); rv_errstrm << "\n";
      delete rec;
      return false;
    }

    if( rec0->other_side ) {
      rv_errstrm << "Internal: RVStructs (in \""<< where <<"\") related two "
	"side 0 types to side 1 type:\n";
      strdecl->print(rv_errstrm,true); rv_errstrm << "\n";
      delete rec;
      return false;
    }

    // connect the recs to each other:
    rec->other_side = rec0;
    rec0->other_side = rec;
    rec->otype = rec0->otype;
  }

  // index the record:
  recind[gen_side].add(rec);
  
  ret = add_new_func_decls(rec) && ret;

if(DBG){rv_errstrm<<"process_one_struct() result:\n";
 strdecl->print(rv_errstrm, true); rv_errstrm<<";\n";}

  return ret;
}



bool RVStructs::process_all_structs()
{
  bool ret = true;

if(DBG) rv_errstrm << "Start RVStructs::process_all_structs() \n";

  ret = gen_token_component_types() && ret;

  Statement* first_st = get_glob_stemnt(res_parsetree[gen_side]);
  Statement* st = NULL;
  DeclVector::const_iterator j;

  // first generate tokens for the structs:
  // for each Decl in res_parsetree[gen_side]
  for(st = first_st; st; st = st->next) 
    if( st->isDeclaration() )
      FORVEC(j, ((DeclStemnt*)st)->decls)
        // if its struct or struct-user-type def.
        if( is_aggregate((*j)->form) )
          ret = gen_struct_token_typedef(*j) && ret;
           
  // now convert struct defs to use tokens instead pointers:
  for(st = first_st; st; st = st->next) 
    if( st->isDeclaration() )  {
      FORVEC(j, ((DeclStemnt*)st)->decls)
        // if its struct or struct-user-type def.
        if( is_aggregate((*j)->form) )
          ret = process_one_struct(*j);
    }

  /* MAYBE just process all res_parsetree[gen_side]->typeList instead <<=== 
       the problem is Type::link is private. 
  */

if(DBG) rv_errstrm << "Finish RVStructs::process_all_structs() \n";

  return ret;
}


bool RVStructs::process_all_vars()
{
  bool ret = true;
  std::string decl_where;
  
if(DBG) rv_errstrm << "Start RVStructs::process_all_vars() \n";

  RVTokenizer tokenizer(THIS, gen_side);
  set_global_where(gen_side);
  tokenizer.set_where(where);

  Statement* first_st = get_glob_stemnt(res_parsetree[gen_side]);
  Statement* st = NULL;
  DeclStemnt* dst = NULL;
  DeclVector::const_iterator j;

  for(st = first_st; st; st = st->next) 
    // process only var declarations
    if( st->isDeclaration() ) {
      
      dst = (DeclStemnt*)st;
      if( dst->decls.size() > 0 && dst->decls[0] && dst->decls[0]->name ) {
        decl_where = "Declaration (3) of " + dst->decls[0]->name->name;
        set_where(decl_where.data());
        tokenizer.set_where(where);
      }

      ret = tokenizer.process(dst) && ret;

      // worn of use of arrays:
      FORVEC(j, dst->decls)
        if( real_type((*j)->form, where)->isArray() ) {
          rv_errstrm << "Warning: Array as function argument or global is currently unsupported \n"
                     << "  in: \"" << where <<"\" at: ";
          st->location.printLocation(rv_errstrm); rv_errstrm <<"\n";
        }
    }

  set_global_where(gen_side); // for safety - as decl_where is local

if(DBG) rv_errstrm << "Finish RVStructs::process_all_vars() \n";

  return ret;
}


bool RVStructs::process_all_funcs()
{
  RVTypeProp  type_prop;
  RVTokenizer tokenizer(THIS, gen_side);
  RVRenameTree renamer(res_parsetree[gen_side], gen_side);
  bool ret = true;

if(DBG) rv_errstrm << "Start RVStructs::process_all_funcs() \n";

  /* Note: the func names are checked thru rv_parser.is_needed() -
       the original parsed version: */ 
  renamer.remove_unneeded_funcs();
 
  Statement *first_st = get_glob_stemnt(res_parsetree[gen_side]);

  /* process all needed funcs: */
  for(Statement* st = first_st; st; st = st->next) 
    if( st->isFuncDef() ) 
    {
      FunctionDef* func = (FunctionDef*)st;
      set_where( func->FunctionName()->name.data() );
      tokenizer.set_where(where);
      ret = tokenizer.process_func(func) && ret;
    } /* if */

if(DBG) rv_errstrm << "Finish RVStructs::process_all_funcs() \n";
  return ret;
}


bool RVStructs::process_all(int side)
{
  bool ret = true;

if(DBG) rv_errstrm << "Start RVStructs::process_all("<<side<<") \n";

  gen_side = side;

  CHK_NULL1(res_parsetree[gen_side], "res_parsetree[gen_side] in RVStructs::do_all()");
  
  ret = process_all_structs() && ret;

  ret = process_all_vars() && ret;
  
  ret = process_all_funcs() && ret;
  
  gen_side = -1; /* prevent query funcs from using it. */

if(DBG) rv_errstrm << "Finish RVStructs::process_all("<< side <<") \n";
  return ret;
}


bool RVStructs::rename_all(int side, RVFuncPair* semchk_pair, bool semchk_recursive)
{
  RVRenameTree renamer(res_parsetree[side], side);

  bool ret = true;

if(DBG) rv_errstrm << "Start RVStructs::rename_all("<< side <<") \n";

  gen_side = side;

  renamer.set_semchk_pair(semchk_pair, semchk_recursive);

  ret = renamer.rename_all() && ret;

  /* rename token names and tags: */
  ret = renamer.process(str_tkn[side]) && ret;

  /* rename all special func declarations: */
  RVStrRecVec::const_iterator recit;
  FORVEC(recit, recind[side].get_vec())
    (*recit)->rename(renamer);

  gen_side = -1; /* prevent query funcs from using it. */

if(DBG) rv_errstrm << "Finish RVStructs::rename_all("<< side <<"): "<<(ret?"OK":"Failed")<<" \n";

  return ret;
}


bool RVStructs::print_tkns(RVTemp& temps, int side)
{
  DeclVector::const_iterator i;
  FORVEC(i, str_tkn[side]) {
    (*i)->print(temps.get_strm(),true,0);
    temps.print(";\n\n");
  }

  return true;
}


bool RVStructs::print_all(RVTemp& temps)
{
if(DBG) rv_errstrm << "Start RVStructs::print_all() \n";

  bool ret = true; 
  DeclVector::const_iterator di;
  DeclVector::const_iterator fi;
  RVStrRec* rec = NULL;

  tp_enum_RVStructType->printType(temps.get_strm(), NULL, true, 0);
  temps.print(";\n\n");

  for(int side = 0; side<2; side++) 
  {
    /* print all tiken typedefs: */
    ret = print_tkns(temps, side) && ret;
    
    Statement* first_st = get_glob_stemnt(res_parsetree[side]);
    for(Statement* st = first_st; st; st = st->next) {
      st->print(temps.get_strm(),0);
      temps.print("\n\n");
      
      /* if it is a declaration of Tokenized struct: */
      if( st->isDeclaration() ) {
	DeclVector& vec = ((DeclStemnt*)st)->decls;
	
	FORVEC(di, vec) 
	  if( !bla("GUGU") && is_aggregate((*di)->form) &&    // <<=== MAYBE is_token()
	      (rec = recind[side].get_by_str_type((*di)->form)) && // <<=== MAYBE _tkn_type()
	      !rec->printed_funcs ) {

	    if( rec->print_typedef ) {
	      rec->strdecl->print(rv_errstrm, true, 0);
	      temps.print(";\n");
	    }

	    /* print its funcs: */
	    FORVEC(fi, rec->funcs) {
	      (*fi)->print(temps.get_strm(),true,0);
	      temps.print(";\n");
	    }
	    rec->printed_funcs = true;
	  } /* if is_token */
      } /* if( st-> ) */
    } /* for st */
  } /* for side */
  temps.print("\n");

if(DBG) rv_errstrm << "Finish RVStructs::print_all() \n";
  return true;
}


/* RVStructs Query Functions: */

/* the next 3 functions use tag names for structs and tokens: */

bool RVStructs::is_token(Type* tp)
{
  CHK_NULL1(tp, "tp in RVStructs::is_token()");

  BaseType* btp = (BaseType*)real_type(tp, where);

//if(DBG){rv_errstrm<<"IKN btp: "; btp->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";}

  if( !is_basetype(btp, BT_Struct) || !btp->tag || !btp->stDefn )
    return false;

  std::string tknname = btp->tag->name;
  if( tknname.rfind(TKN_SUFFIX, tknname.size(), tkn_suffix_len) != 
      tknname.size() -  tkn_suffix_len ) {
//if(DBG) rv_errstrm << "RVStructs::is_token(): \""<< tknname <<"\" is *not* a token.\n";
    return false;
  }

  /* check it is well structured: */
  RVTreeComp comp;
  Decl* d = NULL;
  StructDef* def = btp->stDefn;
  if( def->nComponents != 5 ||
      !(d = def->components[0]) || d->name->name!=MARKS || !comp.eq_type(d->form,tp_unsigned_char) ||
      !(d = def->components[1]) || d->name->name!=OTYPE || !comp.eq_type(d->form,tp_enum_RVStructType) ||
      !(d = def->components[2]) || d->name->name!=REALM || !comp.eq_type(d->form,tp_unsigned_char) ||
      !(d = def->components[3]) || d->name->name!=ONUM  || !comp.eq_type(d->form,tp_signed_char) ||
      !(d = def->components[4]) || d->name->name!=ARR_IND || !comp.eq_type(d->form,tp_int) ) 
  {
    rv_errstrm << "Error: the next type has RV token name but not token structure: \n";
    tp->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
    return false;
  }

  return true;
}
  

std::string RVStructs::get_token_name(Type* token_type, int side)
{
  CHK_NULL1(token_type, "token_type in RVStructs::get_token_name()");

  if( is_basetype(token_type, BT_UserType) && ((BaseType*)token_type)->typeName )
    return ((BaseType*)token_type)->typeName->name;

  RVStrRec* rec = recind[side].get_by_tkn_type(token_type);
  if( rec )
    return rec->tknname;
  
  rv_errstrm <<"Internal: Can't get name of token type. in: \""<<where<<"\" on side "<<side<<":\n";
  token_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
  return "BAD_TOKEN";
}


std::string RVStructs::get_struct_name(Type* struct_type, int side)
{
  CHK_NULL1(struct_type, "struct_type in RVStructs::get_struct_name()");

  if( !is_aggregate(struct_type) ) {
    rv_errstrm <<"Internal: Bad struct type. in: \""<<where<<"\" on side "<<side<<":\n  ";
    struct_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";
    return "BAD_STRUCT";
  }

  if( is_basetype(struct_type, BT_UserType) && 
      ((BaseType*)struct_type)->typeName )
    return ((BaseType*)struct_type)->typeName->name;

  // try to find its rec:
  RVStrRec* rec = recind[side].get_by_str_type(struct_type);
  if( rec )
    return rec->strname;

  // generate its name from tag or typedef name:
  return make_struct_name_and_tag(struct_type);
}


// textual conversion:
std::string RVStructs::name_token2struct(std::string& token_name)
{
  if( token_name.rfind(TKN_SUFFIX, token_name.size(), tkn_suffix_len) != 
      token_name.size() -  tkn_suffix_len ) {
    rv_errstrm <<"Internal: Bad token name \""<< token_name <<"\".\n";
    return "BAD_TOKEN_NAME";
  }

  return token_name.substr(0, token_name.size() -  tkn_suffix_len);
}


std::string RVStructs::name_struct2token(std::string& struct_name)
{
  return struct_name + TKN_SUFFIX;
}


Type* RVStructs::type_struct2token(Type* strtp, int side)
{
  // First try to find the right tupple (RVStrRec): 
  RVStrRec *rec = recind[side].get_by_str_type(strtp);
  if( rec && rec->tknutp )
    return rec->tknutp;

  std::string strname = get_struct_name(strtp, side);
  std::string tknname = name_struct2token(strname);
  return get_token_type(tknname, side);
}


Type* RVStructs::get_struct_type(std::string& struct_name, int side)
{
  CHK_NULL1(res_parsetree[side], "RVStructs::get_struct_type()");

  ScopeTbl* scope = get_file_scope(res_parsetree[side]);
  
  SymEntry* ret = NULL;
  if( !scope || !(ret = scope->Find(struct_name)) || !ret->uStructDef ) {
    rv_errstrm << "Error: unable to find struct type of: "<< struct_name 
               <<", needed in: \""<< where <<"\" \n";
    return NULL;
  }

  return ret->uStructDef;
}


Type* RVStructs::get_token_type(std::string& token_name, int side)
{
  CHK_NULL1(res_parsetree[side], "RVStructs::get_token_type()");

  ScopeTbl* scope = get_file_scope(res_parsetree[side]);
  
  SymEntry* ent = NULL;
  Type* ret = NULL;
  if( !scope || !(ent = scope->Find(token_name)) || 
      !(ret = get_symbol_type(ent, where)) || !is_token(ret) ) {
    rv_errstrm << "Error: unable to find valid token type of: "<< token_name 
               <<", needed in: \""<< where <<"\" \n";
    return NULL;
  }

  /* we don't need the whole struct type - just the user-name */
  if( ent->IsTypeDef() ) {
    ret = new BaseType(BT_UserType);
    ((BaseType*)ret)->typeName = mk_symbol(token_name, ent);
  }

  return ret;
}


SymEntry* RVStructs::get_glob_decl(std::string& name, int side, bool is_func/*= true*/)
  // in res_parsetree[side] file scope
{
  CHK_NULL1(res_parsetree[side], "RVStructs::get_glob_decl()");  
  ScopeTbl* scope = get_file_scope(res_parsetree[side]);  
  SymEntry* ent = scope->Find(name);

bla("GGD");

  if( !ent || bla("GGD_1") || !ent->uVarDecl || bla("GGD_2") ||
      !( is_func && ent->IsFctDecl() && !bla("GGD_3") || !is_func && ent->IsVarDecl() && !bla("GGD_4")) ) {
    rv_errstrm << "Error: unable to find valid declaration of "<< (is_func?"function":"") <<
      ": \""<< name <<"\", needed in: \""<< where <<"\" on side "<< side <<"\n";
    return NULL;
  }

  return ent;
}


bool RVStructs::replace_glob_vector(SymbolVector& vec, int side)
{
  bool ret = true;
  std::string pref = RVTemp::get_side_prefix(side);
  std::string name;
  Type* strtp;
  SymEntry* ent = NULL;
  Symbol* sym = NULL;
  SymbolVector tmp;

  SymbolVector::iterator i;
  FORVEC(i, vec) {
    strtp = get_symbol_type(*i, where);
    
    if( is_aggregate(strtp) ) // global structs should be tokens mapped to array.
      name = pref + get_struct_var_name( (*i)->name );
    else
      name = pref + (*i)->name;    

    ent = get_glob_decl(name, side, false);
    if( !ent ) {
      ret = false;
      continue;
    }
    sym = mk_symbol(name, ent);
    tmp.push_back(sym);
  }

  vec = tmp;  // check for memory leaks <<===

  return ret;
}


std::string RVStructs::get_struct_var_name(std::string& struct_var_name)
{
  return struct_var_name + TKN_SUFFIX;
}


void RVStructs::add_tokenized_var(Decl* what, int side)
{ 
  if( !what || !what->name )
    fatal_error((char *) "RVStructs::add_tokenized_var() received null what or its name.", false);

  SymEntry* ent = what->name->entry;
  if( is_tokenized_var_entry(ent, side) )
    return;

  if( is_top_level(ent) )
    globals_mapped_to_array[side].push_back( what ); 

  tokenized_var_entries[side].insert(ent);
}

bool RVStructs::is_tokenized_var_entry(SymEntry* ent, int side)
{
  return( tokenized_var_entries[side].find(ent) != tokenized_var_entries[side].end() );
}


/* RVTokenizer */
/*=============*/

RVTokenizer::RVTokenizer(RVStructs& _strs, int side)
  : RVWalk(), strs(_strs), current_side(side)
{
  current_block = NULL;
  last_Stemnt_location = NULL;
  body = NULL;
}


bool RVTokenizer::process_func(FunctionDef* _body)
{
if(DBG){rv_errstrm<<"RVTokenizer::"<<__FUNCTION__<<"\n";/*FDEL*/}

  body = _body; 

  if( !body || !body->FunctionName() || !body->decl )
    fatal_error((char *) "RVTokenizer::process_func(): body or its item is NULL\n", false);

  set_where( body->FunctionName()->name.data() );
  prop.set_where(where);
  strs.set_where(where);

  return process(body);
}


Expression* RVTokenizer::gen_token_compare(Expression* tkn1, Expression* tkn2, const Location& l)
{
  CHK_NULL1(tkn1 && tkn2, "RVTokenizer::gen_token_compare");

  prop.process(tkn1);
  prop.process(tkn2);

  Type* t1 = tkn1->type;
  Type* t2 = tkn2->type;

  if( !t1 || !strs.is_token(t1) || !t2 || !strs.is_token(t2) ) {
    rv_errstrm << "Error: NULL or non-token (pointer) types in compare expression, at: ";
    l.printLocation(rv_errstrm); rv_errstrm <<"\n  Left  type: ";
    if(t1) t1->printType(rv_errstrm, NULL, true, 0); else rv_errstrm <<"NULL";
    rv_errstrm <<"\n  Right type: ";
    if(t2) t2->printType(rv_errstrm, NULL, true, 0); else rv_errstrm <<"NULL"; rv_errstrm<<"\n";
  }

  FunctionCall* ret = gen_func_call(t1, NT_COMP, current_side, l);
  ret->args.push_back(tkn1);
  ret->args.push_back(tkn2);

  prop.process(ret);

  return ret;
}


Expression* RVTokenizer::gen_token_rel(Expression* tkn1, Expression* tkn2, 
				       RelOp       rOp,  const Location& l)
// works with NT_SUB and implement <, >, <=, >= 
{
  CHK_NULL1(tkn1 && tkn2, "RVTokenizer::gen_token_rel");  

  prop.process(tkn1);
  prop.process(tkn2);

  Type* t1 = tkn1->type;
  Type* t2 = tkn2->type;

  if( !t1 || !t2 || !comp.eq_type(t1,t2) ) {
    rv_errstrm << "Error: NULL or incompatible token (pointer) types in \"";
    PrintRelOp(rv_errstrm, rOp); rv_errstrm <<"\" expression, at: ";
    l.printLocation(rv_errstrm); rv_errstrm <<"\n  Left  type: ";
    if(t1) t1->printType(rv_errstrm, NULL, true, 0); else rv_errstrm <<"NULL";
    rv_errstrm <<"\n  Right type: ";
    if(t2) t2->printType(rv_errstrm, NULL, true, 0); else rv_errstrm <<"NULL"; rv_errstrm<<"\n";
  }

  /* gen: "rvs0/1_Str_tkn_sub(tkn1,tkn2) [rOp] 0": */
  IntConstant* zero = new IntConstant(0, false, l);
  FunctionCall* sub = gen_func_call(t1, NT_SUB, current_side, l);
  sub->args.push_back(tkn1);
  sub->args.push_back(tkn2);
  
  RelExpr* rel = new RelExpr(rOp, sub, zero, l);
  
  prop.process(rel);
  
  return rel;
}
  

Expression* RVTokenizer::gen_compare_null(Expression* tkn, 
					  Type* orig_type, 
					  const Location& l)
{
  CHK_NULL1(tkn && orig_type, "RVTokenizer::gen_compare_null");
  
  Symbol* fld_sym = new Symbol();  /* will be replaced by the real token symbol */
  fld_sym->name = strs.ONUM;
  Decl* fld_decl = NULL;

  prop.process(tkn);

  Type* t1 = tkn->type;
  if( !t1 || !strs.is_token(t1) ) {
    rv_errstrm << "Error: non token (pointer) type in compare with NULL, at: ";
    l.printLocation(rv_errstrm); rv_errstrm <<"\n  Type: ";
    if(t1) t1->printType(rv_errstrm, NULL, true, 0); else rv_errstrm <<"NULL";
    rv_errstrm <<"\n";
  }
  else {
    StructDef* strdef = get_struct_def(orig_type, where);
    fld_decl = get_field_decl(strdef, fld_sym);
  }

  if( fld_decl ) { /* replace fld_sym by the decl one: */
    delete fld_sym;
    fld_sym = fld_decl->name->dup0();
  }

  /* make (tkn.onum < 0): */
  Variable* var = new Variable(fld_sym, l);
  BinaryExpr* mem = new BinaryExpr(BO_Member, tkn, var, l);
  IntConstant* zero = new IntConstant(0, false, l);
  RelExpr* eq = new RelExpr(RO_Less, mem, zero, l);

  prop.process(eq);
  
  return eq;
}


Expression* RVTokenizer::gen_null_token_expr(Type* strtp, int side, Location& l)
{
  std::string strname = strs.get_struct_name(strtp, side);
  std::string tknname = strs.name_struct2token(strname);
  std::string nullname = strs.gen_name_for_token(tknname, NT_NULL, side);
  
  SymEntry* nullent = strs.get_glob_decl(nullname, side, false /*not func*/);
  if( !nullent ) return NULL;

  Symbol* nullsym = mk_symbol(nullname, nullent);
  Variable* nullvar = new Variable(nullsym, l);

  return nullvar;
}


FunctionCall* RVTokenizer::gen_func_call(Type* tkntype, RVNameType nt, 
                                         int side, const Location& l)
{
  CHK_NULL1(tkntype, "tkntype in RVTokenizer::gen_func_call()");
  
  if( !strs.is_token(tkntype) ) {
    rv_errstrm << "Internal: RVTokenizer::gen_func_call(): non-token (pointer) type, in: \"";
    rv_errstrm << where <<"\"\n  Type: ";
    if(tkntype) tkntype->printType(rv_errstrm, NULL, true, 0); else rv_errstrm <<"NULL";
    rv_errstrm <<"\n";
    return NULL;
  }

  std::string tname = strs.get_token_name(tkntype, current_side);
  std::string fname = strs.gen_name_for_token(tname, nt, side);
  SymEntry* fent = strs.get_glob_decl(fname, side);
  if( !fent || !fent->uVarDecl || !fent->uVarDecl->name ) {
    rv_errstrm << "Internal error: can't get Decl of function \""<< fname
               << "\" needed in \"" << where <<"\". \n";
    return NULL;
  }
  
  Decl* fdecl = fent->uVarDecl;
  Symbol* fsym = fdecl->name->dup0();
  Variable* fvar = new Variable(fsym, l);
  FunctionCall* ret = new FunctionCall(fvar, l);
  return ret;
}


FunctionCall* RVTokenizer::gen_func_call(FunctionCall* fc, Type* strtp, 
                                         RVNameType nt, int side)
{
  CHK_NULL1(fc && strtp, "fc or strtp in RVTokenizer::gen_func_call()");

  std::string strname = strs.get_struct_name(strtp, current_side);
  std::string newname = strs.gen_name_for_struct(strname, nt, side);
  
  SymEntry* fent = strs.get_glob_decl( newname, side );
  if( !fent || !fent->uVarDecl || !fent->uVarDecl->name ) {
    rv_errstrm << "Internal error: can't get Decl of function \""<< newname
               << "\" needed in \"" << where <<"\". \n";
    return NULL;
  }
  
  Decl* newdecl = fent->uVarDecl;
  Symbol* newsym = newdecl->name->dup0();
  Variable* newvar = new Variable(newsym, fc->function->location);
  FunctionCall* ret = new FunctionCall(newvar, fc->location);
  return ret;  
}


bool RVTokenizer::process(Statement* s0p)
  // save Stemnt's location. 
{
  CHK_NULL("RVTokenizer::process(Statement*)");
  bool ret = true;

  last_Stemnt_location = &(s0p->location);

  /* keep block pointer in current_block: */
  if( s0p->type == ST_Block ) 
  {
    Block* save_block = current_block;
    current_block = (Block*)s0p;
    
    ret = go(s0p) && ret;
    
    current_block = save_block;
  }
  else
    ret = go(s0p) && ret;

  return ret;
}


bool RVTokenizer::process(Expression* s0p)
  // just checks array indexing and retypes cast exprs
{
  CHK_NULL("RVTokenizer::process(Expression*)");

  if(DBG) {
    rv_errstrm << "RVTokenizer::process(Expression*):\n";
    s0p->print(rv_errstrm); rv_errstrm<<" \n";
    s0p->location.printLocation(rv_errstrm);
    rv_errstrm <<",  in function: \""<< where <<"\"\n\n";
  }  

  bool is_array_item = false;

  switch( s0p->etype ) {

    case ET_Variable:
      /* do nothing here */
      return true;

    case ET_IndexExpr:  // x[y]...[]
      is_array_item = true;
      break;

    case ET_CastExpr: {   // rep pointer cast by token cast
      RETYPE( CastExpr );
      Type* strtp = NULL;
      Type* casttp = NULL;
      if( strs.is_aggregate_pointer(s0p->castTo, &casttp) ) {
        
        if( !strs.is_aggregate_pointer(s0p->type, &strtp) ||
            !comp.eq_type(casttp,strtp) ) {
          rv_errstrm << "Warning: dangerous casting in \""<< where <<"\" at: ";
          s0p->location.printLocation(rv_errstrm);
          rv_errstrm << "\n  From: "; strtp->printType(rv_errstrm, NULL, true, 0);
          rv_errstrm << "\n  To: "; casttp->printType(rv_errstrm, NULL, true, 0);
          rv_errstrm << "\n";
          return go(s0p);
        }

        bool rep_res = false;
        if( s0p->expr->etype == ET_FunctionCall )
          rep_res = try_replace_funccall( (FunctionCall**)&(s0p->expr), s0p->castTo);
        else
          rep_res = try_replace( &(s0p->expr) );
        if( rep_res && !process( s0p->expr ) )    
          return false;
        
        prop.process( s0p->expr ); // set its new type
        s0p->castTo = s0p->expr->type; // MAYBE should be *converted* casttp <<==== ? 
        return true;
      }
      break;
    }

    case ET_BinaryExpr: {
      RETYPE( BinaryExpr );
      if( s0p->bOp == BO_Minus || s0p->bOp == BO_Plus )
        /* check whether it is pointer +/- something: */
        if( (s0p->type && is_pointer(s0p->type, where, NULL)) || 
            (s0p->leftExpr()->type && 
             is_pointer(s0p->leftExpr()->type, where, NULL)) || /* DEL <<=== */
            (s0p->bOp == BO_Plus && s0p->rightExpr()->type && 
             is_pointer(s0p->rightExpr()->type, where, NULL))   /* DEL <<=== */
          )
          is_array_item = true;
      break;
    }
    default:;
  }    

  if( is_array_item ) {
    rv_errstrm << "Warning: currently array items can't be tokenized !\n";
    s0p->location.printLocation(rv_errstrm);
    rv_errstrm <<",  in function: \""<< where <<"\"\n";
    return false;
  }
  
  return go(s0p);
}
    

bool RVTokenizer::process_binary(BinaryExpr* it)
{
  CHK_NULL1(it, "RVTokenizer::process_binary()");

  if( it->bOp == BO_PtrMember ) 
  {
    /* replace pst->comp by rvs0/1_Str_tkn_drf(&pst)->comp : */
    Type* oldtp = it->leftExpr()->type;
    Type* strtp = NULL;
    if( !strs.is_aggregate_pointer(oldtp, &strtp) ) {
      rv_errstrm << "Error: pointer deref of unrecognized struct type: \n";
      if( oldtp ) {oldtp->printType(rv_errstrm, NULL, true, 0); rv_errstrm << " \n";}
      it->location.printLocation(rv_errstrm); rv_errstrm << "\n";
      return true;
    }
      
    /* prepare token on the left side: */
    if( !go_binary( it ) )
      return false;
      
    prop.process(it->_leftExpr);

    Type* tkntp = it->leftExpr()->type;
    if( !tkntp ) {
      rv_errstrm << "Error: RVTokenizer::process_binary(): token (?) type is NULL in \""
                 << where <<" \n";
      return false;
    }

    FunctionCall* newfc = gen_func_call(tkntp, NT_DEREF, current_side, it->location);
    if( !newfc )                // USE gen_token_deref() <<===
      return false;
    
    UnaryExpr* addr = new UnaryExpr(UO_AddrOf, it->leftExpr(), it->location);
    newfc->args.push_back( addr );
    it->_leftExpr = newfc;

    prop.process(it);

    return true; 
  }

  return go_binary( it );
}


bool RVTokenizer::try_replace(Type** pit)
  // rep symbol types
{
  CHK_NULL1(pit && *pit,"RVTokenizer::try_replace(Type**)");

  Type* strtp = NULL;
  Type* tokentp = NULL;

  /* replace pointers to structs by their tokens: */
  if( strs.is_aggregate_pointer(*pit, &strtp) )
  {
    tokentp = strs.type_struct2token(strtp, current_side);

    *pit = tokentp;
    /* don't delete - types are deleted thru global type list */
    
    return false; /* don't process the token type */
  }
      
  return true;
}


bool RVTokenizer::try_replace(Decl** pit)
  // rep Str and Str* var decl
{
  CHK_NULL1(pit && *pit,"RVTokenizer::replace_var_decl(Decl**)");  

  Location& l = *last_Stemnt_location;
  Decl* it = *pit;
  Type* strtp = it->form;
  bool pointer = strs.is_aggregate_pointer(it->form, &strtp);

  // if it is token or *not* struct var or pointer to struct decl (local or global):
  if( !strs.is_aggregate(it->form) && !pointer )
    return true;  // just do the usual.

  // find related token type (see try_replace(Type**))
  Type* tkntp = strs.type_struct2token(strtp, current_side);

  if( pointer ) {
    // replace Decl type ("form") to the token type:
    it->form = tkntp;

    if( it->initializer ) {
      bool rep_res = false;
      if( it->initializer->etype == ET_FunctionCall )
        rep_res = try_replace_funccall( (FunctionCall**)&(it->initializer), strtp);
      else
        rep_res = try_replace( &(it->initializer) );
      if( rep_res && !process( it->initializer ) )
        return false;  /* THROW <<=== */
    }
  } 
  else if( it->name && !it->isTypedef() ) {  // If it is struct *var*:

    // convert var name to token name:
    Symbol* oldsym = it->name;
    std::string var_name = strs.get_struct_var_name(oldsym->name);
    ScopeTbl* scope = it->name->entry->scope;
    Expression* orig_init = it->initializer;    // <<=== USE

    if( scope->level != FUNCTION_SCOPE ) {

if(DBG) {rv_errstrm<<"Tokenized var: "<< it->name->name <<" \n";}
      /* first save the symbol (with orig name) to recognize later
  	   that we should replace it by (*rvs0/1_Str_tkn_drf(&rvt_st1)): */
      strs.add_tokenized_var(it, current_side);

      it->name = new Symbol();  // set Decl's symbol and type
      it->name->name = var_name;
      it->form = tkntp;
    
      if( scope->level >= BLOCK_SCOPE ) {

        // add initializer: malloc(one struct)
        Symbol* fsym = new Symbol();
        fsym->name = "malloc";

        ScopeTbl* glob_scope = get_file_scope(strs.get_res_parsetree(current_side));
        SymEntry* fent = glob_scope->Find( fsym->name );
        if( !fent ) {
          rv_errstrm << "Warning: can't find \"malloc\" prototype. "
            "\n  needed to replace \""<< oldsym->name <<"\" variable by token variable. "
            "in: \"" << where <<" at: ";          
          l.printLocation(rv_errstrm); rv_errstrm <<"\n";
        }
        else
          fsym->entry = fent;
        
        Variable* fvar = new Variable(fsym, l);
        FunctionCall* fcall = new FunctionCall(fvar, l);
        fcall->args.push_back(new SizeofExpr(strtp, l));
        it->initializer = fcall;
        
        /* now replace it by the our token malloc: */
        if( try_replace_funccall( (FunctionCall**)&(it->initializer), strtp) &&
            !process( it->initializer ) )
          return false;  /* THROW <<=== */

	/* ALSO: if it had orig_init - need to gen a it 
	     as the first assign statement of the block   <<=== FIN */

        /* Note: type prop is done in try_replace_funccall. */
      } /* BLOCK_SCOPE */

      // replace var symbol in the relevant scope:
      SymEntry* syment = ScopeTbl_remove(scope, oldsym->name);
      if( !syment )
        fatal_error((char *) "RVTokenizer::try_replace(Decl**): "
                    "Can't find symbol in its scope: ", oldsym->name, false);
      
      syment->name = var_name;
      it->name->entry = syment;
      scope->Insert( syment );
      syment->scope = scope;

      delete oldsym; // <<=== ??
    } /* FUNCTION_SCOPE */

  } /* struct var decl */

  return false; // doesn't need farther processing.
}


bool RVTokenizer::try_replace(Expression** pit)
// malloc() call, &, tokenized var use
{
  CHK_NULL1(pit && *pit,"RVTokenizer::try_replace(Expression**)");
  
  switch( (*pit)->etype )
  {
    case ET_Variable: {
      Variable* it = (Variable*)*pit;
      Expression* res = NULL;

bla("HHHHHHHHHHHHHHHHHHH");
      /* replace tokenized  vars by *rvs0/1_Str_tkn_drf(&tkn_var) */
      if( strs.is_tokenized_var_entry(it->name->entry, current_side) ) 
      {
	/* make sure we have the right token type: */
	prop.process(it);

	res = gen_token_deref(it, false);
	if( res ) {
if(DBG) {rv_errstrm<<"Replaced by:\n"; res->print(rv_errstrm); rv_errstrm<<"\n\n";}
          *pit = res;
	  return false; // no need to process the result.
	}
      }
      return true;
    }

    case ET_UnaryExpr:
      return try_replace_unary( (UnaryExpr**)pit );

    case ET_BinaryExpr:
      return try_replace_binary( (BinaryExpr**)pit );

    case ET_FunctionCall:
      /* check for "free(struct pointer)" - replace by rvs0/1_Str_free() <<=== FIN */
      /* if it is malloc() 
  	   rv_errstrm << "Internal: malloc() shouldn't get here !!"; */
      return true;

    default:
      return true;
  }
}


bool RVTokenizer::try_replace_binary(BinaryExpr** pit)
  // rep =malloc(), ==
{
  CHK_NULL1(pit && *pit,"RVTokenizer::try_replace_binary()");

  switch( (*pit)->bOp ) 
  {
    case BO_Rel:
      return try_replace_rel( (RelExpr**)pit );

    case BO_Assign: {
      AssignExpr* aexp = (AssignExpr*)*pit;
      Type* strtp = NULL;
      if( aexp->rValue()->etype == ET_FunctionCall &&
          strs.is_aggregate_pointer(aexp->lValue()->type, &strtp) ) {

        if( try_replace_funccall( (FunctionCall**)&aexp->_rightExpr, strtp ) )
          process( aexp->rValue() );
        if( try_replace( &aexp->_leftExpr ) )
          process( aexp->lValue() );
        return false;
      }
      else if( is_const_null(aexp->rValue()) &&
	       strs.is_aggregate_pointer(aexp->lValue()->type, &strtp) ) 
      {
	Expression* null_tkn = gen_null_token_expr(strtp, current_side, aexp->rValue()->location);
	if( !null_tkn )
	  return false; // THROW <<===
	delete aexp->_rightExpr;
	aexp->_rightExpr = null_tkn;

        if( try_replace( &aexp->_leftExpr ) )
          process( aexp->lValue() );

	return false;
      }
      return true;
    }

    default:
      return true;
  }
}


bool RVTokenizer::try_replace_unary(UnaryExpr** pit)   
  // rep &st1, !pst1
{
  CHK_NULL1(pit && *pit,"RVTokenizer::try_replace_unary()");  

  UnaryExpr* it = *pit;

  switch( (*pit)->uOp ) 
  {
    case UO_AddrOf: {

      UnaryExpr* drf = NULL;
      /* iteratively skip "&*": */
      while( (drf = (UnaryExpr*)it->operand()) && 
	     drf->etype == ET_UnaryExpr && drf->uOp == UO_Deref ) 
      {
        *pit = (UnaryExpr*)drf->operand();
        drf->_operand = NULL;
        delete it; /* delete "&*" pair */
	it = (UnaryExpr*)*pit;

	/* continue the loop only if its an UO_AddrOf expression: */
	if( it->etype != ET_UnaryExpr || it->uOp != UO_AddrOf )
	  break;
      }
          
      // if its a struct variable - replace it by its token (which maps to array):
      if( strs.is_aggregate(it->operand()->type) &&
	  it->operand()->etype == ET_Variable && ((Variable*)it->operand())->name ) 
      {
	Variable* var = (Variable*)it->operand();
        Symbol* strsym = var->name;
	
	if( !strs.is_tokenized_var_entry(strsym->entry, current_side) )
	{
          rv_errstrm << "Internal: address (&) of a struct varible which wasn't tokenized: \n  ";
          it->print(rv_errstrm); rv_errstrm << "\n  in \""<< where <<"\", at: ";
          it->location.printLocation(rv_errstrm); rv_errstrm << "\n";
	  return false;  /* THROW <<=== */
        }

        std::string tkn_name = strs.get_struct_var_name(strsym->name);
        SymEntry* tknse = strsym->entry->scope->Find( tkn_name );
        if( !tknse || !strs.is_token(tknse->uVarDecl->form) ) {
          rv_errstrm << "Internal: can't find token variable related to: \n  ";
          it->print(rv_errstrm); rv_errstrm << "\n  in \""<< where <<"\", at: ";
          it->location.printLocation(rv_errstrm); rv_errstrm << "\n";
          return true;
        }
        
        var->name = mk_symbol(tkn_name, tknse);  // replace Variable symbol by tknsym
        delete strsym;

	// remove the '&' before the token var
        *pit = (UnaryExpr*)var;
        it->_operand = NULL;
        delete it;

	prop.process(*pit);

	return false; // don't process the token var.
      }

      return true;  // process it if its not a direct var reference.
    } /* case UO_AddrOf */

    case UO_Not: {
      Type* strtp = NULL;
      Expression* exp = it->operand();
      Location l = exp->location;
      if( strs.is_aggregate_pointer(it->type, &strtp) ) {

        /* replace the pointer by token: */
        if( try_replace( &exp ) && !process(exp) )
          return false;
        
        Expression* res = gen_compare_null(exp, strtp, l);
        *pit = (UnaryExpr*)res;
        it->_operand = NULL;
        delete it;
        return false; // we already processed exp
      }
      break;
    }

    default:;
  }

  return true;
}    

bool RVTokenizer::try_replace_rel(RelExpr** pit)
  // <, >, <=, >= == between str poi
{
  CHK_NULL1(pit && *pit, "RVTokenizer::try_replace_rel()");  

  RelExpr* s0p = *pit;

  switch( (*pit)->rOp ) 
  {
    case RO_NotEqual:       // !=
    case RO_Equal: {        // ==
      Expression* res = NULL;
      Expression* single = NULL;
      Type *ltp, *rtp, *orig_type;
      if( strs.is_aggregate_pointer(s0p->leftExpr()->type, &ltp) || 
          strs.is_aggregate_pointer(s0p->rightExpr()->type, &rtp) )
      {
        TRY_REP_PROC( _rightExpr );
        TRY_REP_PROC( _leftExpr );

        if( is_const_null(s0p->leftExpr()) ) {
          single = s0p->_rightExpr;
          orig_type = rtp;
        } else if( is_const_null(s0p->rightExpr()) ) {
          single = s0p->_leftExpr;
          orig_type = ltp;
        }

        if( single )
          res = gen_compare_null(single, orig_type, s0p->location);
        else
          res = gen_token_compare(s0p->_leftExpr, s0p->_rightExpr, s0p->location);
        
        *pit = (RelExpr*)res;
        s0p->_leftExpr = s0p->_rightExpr = NULL;
        delete s0p;     
        return false;
      } 
      return true;
    }

    case RO_Less:           // < 
    case RO_LessEql:        // <=
    case RO_Grtr:           // > 
    case RO_GrtrEql: {      // >=
      if( strs.is_aggregate_pointer(s0p->leftExpr()->type) && 
          strs.is_aggregate_pointer(s0p->rightExpr()->type) ) 
      { 
        TRY_REP_PROC( _leftExpr );
        TRY_REP_PROC( _rightExpr );
        Expression* res = gen_token_rel(s0p->leftExpr(), s0p->rightExpr(),
                                        s0p->rOp, s0p->location);
        if( !res ) 
          return false;  /* THROW <<=== */
        
        *pit = (RelExpr*)res;
        s0p->_leftExpr = s0p->_rightExpr = NULL;
        delete s0p;
        return false;
      }
      return true;
    }
  }
  return true;
}


bool RVTokenizer::try_replace_funccall(FunctionCall** pit, Type* struct_type)
{
  CHK_NULL1(pit && *pit && struct_type, "RVTokenizer::try_replace_funccall()");

  FunctionCall* fc = *pit;
  Symbol* fsym = NULL;
  Type* strtp = NULL;
  Type* argtp = NULL;
  
  if( fc->function->etype != ET_Variable || 
      !(fsym = ((Variable*)fc->function)->name) || !is_function(fsym) ) {
    rv_errstrm << "Internal: Indirect function calls must be replaced by now. Problem at: ";
    (*pit)->location.printLocation( rv_errstrm );
    rv_errstrm << " .\n";       
    return true;
  }

  std::string fname = fsym->name;
  if( fname == "malloc" 
      /* || fname == "calloc"/"realloc"/"free" <<=== TOO */ ) 
  {    
    FunctionCall* newfc = gen_func_call(fc, struct_type, NT_MALLOC, current_side);
    if( !newfc )
      return true;
    
    /* process args and copy them: <<=== ONLY ONE ? */
    newfc->args.resize(fc->args.size());
    for(unsigned i = 0; i < fc->args.size(); i++) {
      newfc->args[i] = fc->args[i];
      fc->args[i] = NULL;
      if( try_replace( &(newfc->args[i]) ) && !process(newfc->args[i]) )
        continue; /* failed processing - process() should emit error */
    }
    
    prop.process(newfc);
    fc->args.resize(0);
    *pit = newfc;
    delete fc;  /* <<=== CHECK */
    return false; // don't process args.
  }
  else {   /* For other func calls - replace malloc() args: */

    bool should_process;
    for(unsigned i = 0; i < fc->args.size(); i++) {
      should_process = true;

      /* If the arg is FunctionCall: */
      if( fc->args[i] && fc->args[i]->etype == ET_FunctionCall ) {
	
	Decl* fdecl = fsym->entry->uVarDecl;
	FunctionType* ftype = (FunctionType*)fdecl->form;
	Decl* argdecl = ftype->args[i];
	if( !argdecl || !argdecl->form ) {
	  rv_errstrm << "Error: function \""<< fname <<"\" argument number "<< i <<
	    " type or Decl is NULL, while provcessing its call in: "<< where <<" \n";
	  return false; // THROW <<===
	}
	argtp = argdecl->form;

	/* if we expect struct pointer - it may be malloc() or NULL: */
	if( strs.is_aggregate_pointer(argtp, &strtp) ) {

	  if( fc->args[i]->etype == ET_FunctionCall ) {
	    if( try_replace_funccall( (FunctionCall**)&(fc->args[i]), strtp) )
	      process( fc->args[i] );
	    should_process = false;
	  }
	  else if( is_const_null( fc->args[i] ) ) {
	    Expression* null_tkn = gen_null_token_expr(strtp, current_side, fc->args[i]->location);
	    if( !null_tkn )
	      return false; // THROW <<===
	    delete fc->args[i];
	    fc->args[i] = null_tkn;
	    should_process = false; /* don't process the null_token */
	  }
	}
      } /* if ET_FunctionCall */

      if( should_process && try_replace( &(fc->args[i]) ) )
	process( fc->args[i] );
    } /* for */

    return false; /* we have just processed the args */
  } 

  return true;
}

 
Expression* RVTokenizer::gen_token_deref(Expression* it, bool object_pointer /*= true*/ )
{
  CHK_NULL1(it, "RVTokenizer::replace_token_deref()");
  Expression* ret = NULL;
  Location& l = it->location;

  Type* tkntp = it->type;
  if( !tkntp || !strs.is_token(tkntp) ) {
    rv_errstrm << "Error: RVTokenizer::gen_token_deref(): Bad token type in \""
	       << where <<" \n";
    return false;
  }
  
  FunctionCall* newfc = gen_func_call(tkntp, NT_DEREF, current_side, l);
  if( !newfc )
    return false;
    
  UnaryExpr* addr = new UnaryExpr(UO_AddrOf, it, l);
  newfc->args.push_back( addr );
  
  if( object_pointer )
    ret = newfc;
  else
    /* otherwise return the object itself: */
    ret = new UnaryExpr(UO_Deref, newfc, l);
    
  prop.process(ret);

  return ret;
}
