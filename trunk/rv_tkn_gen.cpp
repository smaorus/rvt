#if 0
#include <rv_consts.h> 
#include <rv_error.h>
#include <rv_macros.h>
#include <rv_treecomp.h>
#include <rv_temps.h>
#include <rv_tokens.h>
#include <rv_tkn_gen.h>

#include <stdlib.h>
#include <fstream>
#include <sstream>

// <<=== MAYBE RV_SEC_TOKEN_GEN
#define RV_SECTION RV_SEC_TOKENS



RVStrIter RVTknGen::get_str_iter(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->strdecl && rec->strdecl->form, "rec in RVTknGen::get_str_iter()");

  BaseType* tp = (BaseType*)real_type(rec->strdecl->form, m_where);
  StructDef* def = tp->stDefn;

  CHK_NULL1(is_basetype(tp, BT_Struct) && def, "StructDefs in RVTknGen::get_str_iter()");

  RVStrIter it(def);
  return it;
}

bool RVTknGen::gen_null_tkn(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_null_tkn()");
  const char* pref = NULL;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);

    temps.get_strm() << 
pref << rec->tknname <<"  "<< pref << rec->tknname <<"_NULL = { "
" INIT_TOKEN_MARKS, RVST_"<< rec->strname <<", 0, -1, -1 };\n";

    rec = rec->other_side;
  }

  temps.print("\n"); 

  return true;
}


bool RVTknGen::gen_str_pack(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_str_pack()");
  const char* pref = NULL;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);

    temps.get_strm() << 
"typedef struct {\n" <<
"  unsigned char step_choice;\n" <<
"  unsigned char marks;\n"<<
"  "<< pref << rec->strname <<" it;\n" <<
"} "<< pref << rec->strname <<"_pack;\n\n";

    rec = rec->other_side;
  }

  return true;
}


bool RVTknGen::gen_str_array(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_str_array()");
  const char* pref = NULL;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);

    temps.get_strm() << 
pref << rec->strname <<"_pack* "<< strs.gen_name_for_struct(rec->strname,NT_ARRAY,i,true) <<";\n";
    rec = rec->other_side;
  }

    temps.get_strm() << 
"int  rv_"<< rec->strname <<"_count[2] = {0,0};\n\n\n"; /* side 0 strname */

  return true;
}


bool RVTknGen::gen_tkn_comp(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_tkn_comp()");
  const char* pref = NULL;
  RVStrRec* rec0 = rec;
  RVStrRec* rec1 = rec->other_side;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);

    temps.get_strm() << 
"int "<< strs.gen_name_for_token(rec->tknname, NT_COMP, i, true) <<"("<< 
   pref << rec->tknname <<" tkn1, "<< pref << rec->tknname <<" tkn2)\n"<<
"{\n"
"  return ( tkn1.otype == tkn2.otype &&\n"
"           tkn1.realm == tkn2.realm &&\n" 
"           tkn1.onum  == tkn2.onum  &&\n"
"           tkn1.arr_ind == tkn2.arr_ind );\n"
"}\n\n\n";
    rec = rec->other_side;
  }

  /* and a common one: */
  temps.get_strm() << 
"int rv_"<< rec->tknname <<"_comp("<< 
    temps.get_side_prefix(rec0->side) << rec0->tknname <<" tkn0, "<< 
    temps.get_side_prefix(rec1->side) << rec1->tknname <<" tkn1)\n"<<
"{\n"
"  return ( tkn0.otype == tkn1.otype &&\n"
"           tkn0.realm == tkn1.realm &&\n" 
"           tkn0.onum  == tkn1.onum  &&\n"
"           tkn0.arr_ind == tkn1.arr_ind );\n"
"}\n\n\n";

  return true;
}


bool RVTknGen::gen_tkn_sub(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_tkn_sub()");
  const char* pref = NULL;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);

    temps.get_strm() << 
"int "<< strs.gen_name_for_token(rec->tknname, NT_SUB, i, true) <<"("<< 
   pref << rec->tknname <<" tkn1, "<< pref << rec->tknname <<" tkn2)\n"<<
"{\n"
"  assert( tkn1.otype == tkn2.otype &&\n"
"          tkn1.realm == tkn2.realm &&\n"
"          tkn1.onum  == tkn2.onum );\n"
"  return( tkn1.arr_ind - tkn2.arr_ind );\n"
"}\n\n\n";

    rec = rec->other_side;
  }

  return true;
}


bool RVTknGen::gen_str_equalize(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_str_equalize()");
  Decl *comp0, *comp1;
  RVStrRec* rec0 = rec;
  RVStrRec* rec1 = rec->other_side;

  temps.get_strm() <<
"void rv_"<< rec0->strname <<"_equalize("<< temps.get_side_prefix(rec0->side) << rec0->strname <<
  "* src, "<< temps.get_side_prefix(rec1->side) << rec1->strname <<"* trg)\n"
"{\n"
"  int res = 1;\n";

  RVStrIter it0 = get_str_iter(rec0);
  RVStrIter it1 = get_str_iter(rec1);
  /* LATER: tp0/1 may not be a struct <<=== */

  comp0 = it0.begin();
  comp1 = it1.begin();
  while( !it0.end() && !it1.end() ) 
  {
    std::string& name0 = comp0->name->name;
    std::string& name1 = comp1->name->name;

    if( strs.is_token(comp0->form) != strs.is_token(comp1->form) ) {
      rv_errstrm << "Internal: incompatible (token ?) types of components \""<< name0 <<
	"\" and \""<< name1 <<"\" in:\n";
      rec0->strdecl->form->printType(rv_errstrm, NULL, true, 0); rv_errstrm <<"\n";
      rec1->strdecl->form->printType(rv_errstrm, NULL, true, 0); rv_errstrm <<"\n";
      temps.get_strm() <<"  Incompatible components: "<< name0 <<" and "<< name1 <<";\n";
    }
    else if( strs.is_token(comp0->form) )
      temps.get_strm() << 
"  res = rv_"<< rec->tknname <<"_comp(src->"<< name0 <<", trg->"<< name1 <<") && res;\n";
    else /* simple value component */
      temps.get_strm() <<
"  res = (src->"<< name0 <<" == trg->"<< name1 <<") && res;\n";

    comp0 = it0.next();
    comp1 = it1.next();
  }

  temps.get_strm() <<
"  assume( res );\n"
"}\n\n\n";

  return true;
}


bool RVTknGen::gen_str_compare(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_str_compare()");
  Decl *comp0, *comp1;
  RVStrRec* rec0 = rec;
  RVStrRec* rec1 = rec->other_side;
  RVStrIter it0 = get_str_iter(rec0);
  RVStrIter it1 = get_str_iter(rec1);

  temps.get_strm() <<
"void rv_"<< rec->strname <<"_compare("<< temps.get_side_prefix(rec0->side) << rec0->strname <<
  "* src, "<< temps.get_side_prefix(rec1->side) << rec1->strname <<"* trg)\n"
"{\n";

  comp0 = it0.begin();
  comp1 = it1.begin();
  while( !it0.end() && !it1.end() )
  {
    std::string& name0 = comp0->name->name;
    std::string& name1 = comp1->name->name;

    /* already checked component token compatibility in RVTknGen::gen_str_equalize() */

    /* Note that here the assert() part should be only 
       on the simple valued components of the Str (non-pointers). */
    if( !strs.is_token(comp0->form) )
      temps.get_strm() <<
"  assert(src->"<< name0 <<" == trg->"<< name1 <<");\n";

    comp0 = it0.next();
    comp1 = it1.next();
  }
  temps.get_strm() <<
"}\n\n\n";

  return true;
}


bool RVTknGen::gen_map_to_array(Type* tkntp, int side, std::string var)
{
  CHK_NULL1(tkntp, "RVTknGen::gen_map_to_array()");

  std::string tknname = strs.get_token_name(tkntp, side);

  RVStrRec* rec = strs.get_rec_by_tkn_type(tkntp, side);
  if( !rec ) {
    rv_errstrm <<"Internal: can't find RVStrRec for token: \n";
    tkntp->printType(temps.get_strm(), NULL, true,0); rv_errstrm <<"\n";
    return false;
  }

  std::string strname0 = (side == 1 ? rec->other_side->strname : rec->strname );
  std::string null_tkn = strs.gen_name_for_token(tknname, NT_NULL, side);
  std::string count_name = std::string("rv_")+ strname0 +
    "_count["+ (side?"1":"0") +"]";

  temps.get_strm() <<
"  "<< var <<" = "<< null_tkn <<";\n"
"  "<< var <<"."<< strs.ONUM <<" = "<< count_name <<";\n"
"  "<< count_name <<"++;\n";

  return true;
}
      

bool RVTknGen::gen_init_arrays(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side && rec->side == 0, "RVTknGen::gen_init_arrays()");

  RVStrRec* rec0 = rec;
  RVStrRec* rec1 = rec->other_side;
  std::string strname0(temps.get_side_prefix(0));
  strname0 += rec0->strname;
  std::string strname1(temps.get_side_prefix(1));
  strname1 += rec1->strname;
  std::string arr0 = strs.gen_name_for_struct(rec0->strname,NT_ARRAY,0,true);
  std::string arr1 = strs.gen_name_for_struct(rec1->strname,NT_ARRAY,1,true);

  temps.get_strm() <<
"void rv_"<< rec0->strname <<"_init_arrays()\n"
"{\n"
"  int i;\n\n"
"  "<< arr0 <<" = ("<< strname0 <<"_pack*)malloc("<< 
    max_records <<" * sizeof("<< strname0 <<"_pack));\n"
"  "<< arr1 <<" = ("<< strname1 <<"_pack*)malloc("<<
    max_records <<" * sizeof("<< strname1 <<"_pack));\n\n"
"  /* the contents is curently nondet - but it still should be equal: */\n"
"  for(i = 0; i < "<< max_records <<"; i++) {\n"
"    /* init RVT marks of the structs: */\n"
"    RV_INIT_PACK_MARKS("<< arr0 <<"[i].marks);\n"
"    RV_INIT_PACK_MARKS("<< arr1 <<"[i].marks);\n\n"
"    /* equalize all components of original structs: */\n"
"    rv_"<< rec->strname <<"_equalize( &("<< arr0 <<"[i].it), &("<< arr1 <<"[i].it));\n"
"    "<< strname0 <<"_init_tokens( &("<< arr0 <<"[i].it) );\n"
"    "<< strname1 <<"_init_tokens( &("<< arr1 <<"[i].it) );\n"
"  }\n\n";

  temps.get_strm() <<
"}\n\n\n";

  return true; 
}

bool RVTknGen::gen_nondet_token(std::string tknvar)
{
  temps.get_strm() << 
"  "<< tknvar <<".onum = nondet_int();\n"  
"  "<< tknvar <<".arr_ind = nondet_int();\n";

  return true;
}

bool RVTknGen::gen_init_token_marks(std::string tknvar)
{
  temps.get_strm() << 
"  RV_INIT_TOKEN_MARKS( "<< tknvar <<".marks );\n";

  return true;
}

bool RVTknGen::gen_init_tokens(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_init_tokens()");
  const char* pref = NULL;
  Decl* comp = NULL;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);

    temps.get_strm() << 
"void "<< pref << rec->strname <<"_init_tokens("<< pref << rec->strname <<"* str)\n"
"{\n";

    RVStrIter it = get_str_iter(rec);
    FORIT(comp, it)
      if( strs.is_token(comp->form) )
	if( !gen_init_token_marks(std::string("str->") + comp->name->name) )
	  return false;

    temps.get_strm() << 
"}\n\n\n";

    rec = rec->other_side;
  }

  return true;
}
    

bool RVTknGen::gen_tkn_drf(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_tkn_drf()");
  RVStrRec* rec0 = rec;
  const char* pref = NULL;
  std::string arr;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);
    arr = strs.gen_name_for_struct(rec->strname, NT_ARRAY, rec->side, true);

    temps.get_strm() << 
pref << rec->strname <<"* "<< pref << rec->tknname <<"_drf("<< pref << rec->tknname <<"* t)\n"
"{\n"
"  /* first: set default params: */\n"
"  assume( t->realm == 0 && t->arr_ind == 0 );  /* currently unused */\n"
"  assume( t->otype == RVST_"<< rec0->strname <<" );  /* should be in enum RVStructType */\n"
"\n";

    if( i == 0 ) temps.get_strm() << 
"  /* let the token chose whether it is an alias or a new item: */\n"
"  assume( 0 <= t->onum && t->onum <= rv_"<< rec0->strname <<"_count[0] );\n\n";
    else  temps.get_strm() << 
"  /* now the token should be an existing item (not NULL): */\n"
"  assert( 0 <= t->onum && t->onum < rv_"<< rec0->strname <<"_count[1] );\n\n";

    temps.get_strm() <<
"  /* don't use freed items: */\n"
"  "<< (i? "assume": "assert") <<"( !RV_IS_FREE( "<< arr <<"[t->onum].marks ) );\n\n";

    if( i == 0 ) temps.get_strm() << 
"  /* Note: on side 0 we assume deref pointers are never NULL (onum > -1) or freed. */\n\n";
    else  temps.get_strm() << 
"  /* Note: the tokens *must* be defined before - from mallocs, \n"
"       var structs or from input structure which is equal \n"
"       on both sides and defined on side 0 . */\n\n";

    /* on side 0 it may have chosed a new item: */
    if( i == 0 ) temps.get_strm() << 
"  /* if the token decided to occupy new item: */\n"
"  if( t->onum == rv_"<< rec0->strname <<"_count[0] )\n"
"    rv_"<< rec0->strname <<"_count[0]++;\n"
"\n"
"  /* don't overflow the array: */\n"
"  assert( rv_"<< rec0->strname <<"_count[0] <= "<< max_records <<" );\n\n";

    temps.get_strm() <<
"  RV_SET_USED( t->marks );\n\n"
"  return &("<< arr <<"[t->onum].it);\n"
"}\n\n\n";

    rec = rec->other_side;
  } /* for */

  return true;
}


bool RVTknGen::gen_str_malloc(RVStrRec* rec)
  // including str_nondet() 
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_str_malloc()");
  RVStrRec* rec0 = rec;
  std::string pref, arr, fullname;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);
    arr = strs.gen_name_for_struct(rec->strname, NT_ARRAY, rec->side, true);
    fullname = pref + rec->strname;

    temps.get_strm() << 
fullname <<" "<< fullname <<"_nondet()\n"
"{ "<< fullname <<" nondet_str;\n"
"  return nondet_str;\n"
"}\n\n\n";

    temps.get_strm() << 
pref << rec->tknname <<" "<< strs.gen_name_for_struct(rec->strname, NT_MALLOC, rec->side, true) 
		     <<"(int size)\n"
"{\n"
"  "<< pref << rec->tknname <<" ret = {0, RVST_"<< rec0->strname <<", 0, 0, 0};\n"
"  int ind = rv_"<< rec0->strname <<"_count["<< rec->side <<"];\n\n"
"  /* currently we malloc only single items: */\n"
"  assert( size == sizeof("<< fullname <<") );\n\n"
"  /* the allocated memoy is independant of the other side: */\n"
"  "<< arr <<"[ind].it = "<< fullname <<"_nondet();\n"
"  "<< fullname <<"_init_tokens( &("<< arr <<"[ind].it) ); /* fix token marks */\n\n"
"  rv_"<< rec0->strname <<"_count["<< rec->side <<"]++;\n\n"
"  RV_INIT_TOKEN_MARKS( ret.marks );\n"
"  ret.onum = ind;\n\n"
"  return ret;\n"
"}\n\n\n";

    rec = rec->other_side;
  }
  
  return true;
}


bool RVTknGen::gen_str_free(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_str_free()");
  std::string pref, arr;
  RVStrRec* rec0 = rec;

  for(int i = 0; i < 2; i++) {
    pref = temps.get_side_prefix(rec->side);
    arr = strs.gen_name_for_struct(rec->strname, NT_ARRAY, rec->side, true);

    temps.get_strm() << 
"void "<< strs.gen_name_for_struct(rec->strname, NT_FREE, rec->side, true) <<
  "("<< pref << rec->tknname <<"* t)\n"
"{\n"
"  assert( t->otype == RVST_"<< rec0->strname <<" );\n\n"
"  /* "<< (i?"Check: do":"should") <<"n't free NULL or unallocated pointers: */\n"
"  "<< (i?"assert":"assume") <<"( 0 < t->onum && t->onum <= rv_"<< 
      rec0->strname <<"_count["<< rec->side <<"] );\n\n"
"  /* "<< (i?"Check: do":"should") <<"n't free twice: */\n"
"  "<< (i?"assert":"assume") <<"( !RV_IS_FREE( "<< arr <<"[t->onum].marks ) );\n\n"
"  RV_SET_FREE( "<< arr <<"[t->onum].marks );\n"
"}\n\n\n";

    rec = rec->other_side;
  }
  
  return true;
}


bool RVTknGen::gen_any_token(RVStrRec* some_rec)
{
  CHK_NULL1(some_rec && some_rec->tkndecl && some_rec->tkndecl->form, 
	    "token type in RVTknGen::gen_any_token()");
  
  BaseType* form = (BaseType*)some_rec->tkndecl->form->dup();
  form->tag = form->stDefn->tag = NULL;

  temps.get_strm() << "typedef ";
  form->printType(temps.get_strm(), NULL, true,0);
  temps.get_strm() << " Any_Token;\n\n";

  return true;
}  
  

bool RVTknGen::gen_choose_step(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_choose_step()");

  RVStrRec* rec0 = rec;
  RVStrRec* rec1 = rec->other_side;
  std::string pref0 = temps.get_side_prefix(0);
  std::string pref1 = temps.get_side_prefix(1);
  std::string fullname0 = pref0 + rec0->strname;
  std::string fullname1 = pref1 + rec1->strname;

  temps.get_strm() << 
"int rv_"<< rec->strname <<"_choose_step("<< fullname0 <<"_pack* pack0, Any_Token* out_tkn0,\n"
"\t\t\t "<< fullname1 <<"_pack* pack1, Any_Token* out_tkn1 )\n"
"{\n"
"  /* if we already reached this struct on the path: */\n"
"  if( RV_ON_PATH( pack0->marks ) ) {\n"
"    /* we should reach bith structs together - or RVT has a bug */\n"
"    assert( RV_ON_PATH( pack1->marks ) );\n"
"    return 0;\n"
"  }\n"
"\n"
"  /* if this struct has been freed: */\n"
"  if( RV_IS_FREE(pack0->marks) ) {\n"
"    /* reachability of freed structs should be permited explicitly: */\n"
"    assert( !disconnect_free_structs );\n"
"\n"
"    /* the one on the other side must be free too: */\n"
"    assert( RV_IS_FREE(pack1->marks) );\n"
"    return 0; /* shouldn't continue through free struct. */\n"
"  }\n"
"\n"
"  assume( pack0->step_choice > 0 && pack0->step_choice == pack1->step_choice );\n"
"  RV_SET_ON_PATH( pack0->marks );\n"
"  RV_SET_ON_PATH( pack1->marks );\n"
"\n"
"  switch( pack0->step_choice )\n"
"  {\n";

  Decl *comp0, *comp1;
  RVStrIter it0 = get_str_iter(rec0);
  RVStrIter it1 = get_str_iter(rec1);
  comp0 = it0.begin();
  comp1 = it1.begin();
  unsigned count = 0;
  while( !it0.end() && !it1.end() )
  {
    std::string& name0 = comp0->name->name;
    std::string& name1 = comp1->name->name;

    /* already checked component token compatibility in RVTknGen::gen_str_equalize() */

    if( strs.is_token(comp0->form) ) {
      count++;
      temps.get_strm() <<
"    case "<< count <<":\n"
"      *out_tkn0 = *(Any_Token*)&(pack0->it."<< name0 <<");\n"  // <<=== MAYBE use copy_any_tkn()
"      *out_tkn1 = *(Any_Token*)&(pack1->it."<< name1 <<");\n"
"      return 1;\n\n";
    }

    comp0 = it0.next();
    comp1 = it1.next();
  }

  temps.get_strm() << 
"    default:\n"
"      return 0;\n"
"  } /* switch */\n"
"}\n\n\n";
  
  return true;
}


bool RVTknGen::gen_check_isoequal(RVStrRecVec& all_recs)
{
  temps.get_strm() << 
"void rv_check_isoequal(Any_Token* tkn0, Any_Token* tkn1, int access_limit)\n"
"{\n"
"  short i;\n"
"  int   go_on = 1 /* true */;\n"
"  Any_Token tmp0,tmp1;\n"
"\n"
"  tmp0 = *tkn0;\n"
"  tmp1 = *tkn1;\n"
"\n"
"  for(i = 0; go_on && i < access_limit; i++)\n"
"  {\n"
"    /* check they point to same object types: */\n"
"    assert( tmp0.otype == tmp1.otype );\n"
"\n"
"    /* Check they are in the same realm: \n"
"       (otherwise we have bug in static analysis) */\n"
"    assert( tmp0.realm == tmp1.realm );\n"
"\n"
"    if( tmp0.onum < 0 ) { /* if NULL */\n"
"      assert( tmp1.onum < 0 ); /* check the other is NULL too. */\n"
"      break; /* end of this path */\n"
"    }\n"
"\n"
"    if( !RV_IS_USED( tmp0.marks ) ) { /* if unused token (never dereferenced) */\n"
"      assert( !RV_IS_USED( tmp1.marks ) ); /* check the other is unused too. */\n"
"      break; /* end of this path */\n"
"    }\n"
"\n"
"    switch( tmp0.otype )\n"
"    {\n";

  RVStrRec *rec0, *rec1;
  std::string arr0, arr1;
  std::vector<RVStrRec*>::const_iterator it;  
  FORVEC(it,all_recs) {
    CHK_NULL1((*it) && (*it)->other_side, "RVTknGen::gen_check_isoequal()");

    rec0 = (*it);
    rec1 = rec0->other_side;
    arr0 = strs.gen_name_for_struct(rec0->strname,NT_ARRAY,0,true);
    arr1 = strs.gen_name_for_struct(rec1->strname,NT_ARRAY,1,true);

    temps.get_strm() << 
"      case RVST_"<< rec0->strname <<":\n"
"        /* check that paired simple values in the structs are equal: */\n"
"        rv_"<< rec0->strname <<"_compare( &("<< arr0 <<"[tmp0.onum].it), "
      "&("<< arr1 <<"[tmp1.onum].it));\n"
"\n"
"        /* choose a step on the checked path: */\n"
"        go_on = rv_"<< rec0->strname <<"_choose_step( &("<< arr0 <<"[tmp0.onum]), &tmp0,\n"
"\t\t\t    &("<< arr1 <<"[tmp1.onum]), &tmp1 );\n"
"        break;\n\n";
  } /* FORVEC */

    temps.get_strm() << 
"      default:\n"
"        /* Error: unknown struct type: */\n"
"	assert( 0 );\n"
"    } /* switch */\n"
"  } /* for */\n\n";

    temps.get_strm() << 
"  /* Check: the limit was high enough to check \n"
"      all paths up to NULL or unused token: */\n"
"  assert( i < access_limit );\n"
"}\n\n\n\n";
  
  return true;
}
 

bool RVTknGen::gen_one_struct_stuff(RVStrRec* rec)
{
  CHK_NULL1(rec && rec->other_side, "RVTknGen::gen_all()");
  bool res = true;

  std::string str_where("RVTknGen on ");
  str_where += rec->strname;
  m_where = str_where.data();
  strs.set_where(m_where);

  if( rec->side != 0 || rec->other_side->side != 1 ) {
    rv_errstrm << "Internal: RVTknGen::gen_all() rec->side must be 0, and other_side must be 1"<<
      ", in record of: \""<< rec->strname <<"\"\n";
    return false;
  }
  
  res = gen_null_tkn(rec) && res;

  res = gen_str_pack(rec) && res;
  res = gen_str_array(rec) && res;

  res = gen_tkn_comp(rec) && res;
  res = gen_tkn_sub(rec) && res;

  res = gen_str_equalize(rec) && res;
  res = gen_str_compare(rec) && res;

  res = gen_init_tokens(rec) && res;
  res = gen_init_arrays(rec) && res;

  res = gen_tkn_drf(rec) && res;

  res = gen_str_malloc(rec) && res;
  res = gen_str_free(rec) && res;

  res = gen_choose_step(rec) && res; 

  m_where = "UNKNOWN";
  strs.set_where(m_where);
  
  return res;
}


bool RVTknGen::gen_globals()
{
  temps.get_strm() << 
"int disconnect_free_structs = 0;\n\n"
"#define INIT_TOKEN_MARKS 0\n"    // <<=== find better names
"#define RV_INIT_TOKEN_MARKS(M) (M) = INIT_TOKEN_MARKS;\n"
"\n"
"#define IS_USED_MARK 1\n"
"#define IS_FREE_MARK 2\n"
"#define ON_PATH_MARK 4\n"
"\n"
"#define RV_IS_USED(M) ((M)&IS_USED_MARK)\n"
"#define RV_SET_USED(M) (M) |= IS_USED_MARK;\n"
"#define RV_IS_FREE(M) ((M)&IS_FREE_MARK)\n"
"#define RV_SET_FREE(M) (M) |= IS_FREE_MARK;\n"
"#define RV_ON_PATH(M) ((M)&ON_PATH_MARK)\n"
"#define RV_SET_ON_PATH(M) (M) |= ON_PATH_MARK;\n"
"\n"
"#define INIT_PACK_MARKS 0\n"
"#define RV_INIT_PACK_MARKS(M) (M) = INIT_PACK_MARKS;\n\n"
;

  return true;
}


bool RVTknGen::gen_all()
  // get all_recs from strs
{
  bool ret = true;

if(DBG) rv_errstrm << "Start RVTknGen::gen_all() \n";

  RVStrRecVec& all_recs = strs.get_rec_vec();

  ret = gen_globals() && ret;

  if( all_recs.size() > 0 ) 
    ret = gen_any_token(all_recs[0]) && ret;

  RVStrRecVec::const_iterator it;
  FORVEC(it,all_recs)
    ret = gen_one_struct_stuff(*it) && ret;

  ret = gen_check_isoequal(all_recs) && ret;

if(DBG) rv_errstrm << "Finish RVTknGen::gen_all(): "<< (ret?"OK":"Failed") <<" \n";

  return ret;
}


bool RVTknGen::gen_init_all_arrays()
{
  bool ret = true;
  RVStrRec* rec0 = NULL;

  RVStrRecVec& all_recs = strs.get_rec_vec();

  temps.get_strm() << "void rv_init_all_tokenized_arrays()\n{\n";

  RVStrRecVec::const_iterator it;
  FORVEC(it,all_recs) {
    rec0 = (*it);
    temps.get_strm() << 
"  rv_"<< rec0->strname <<"_init_arrays();\n";
  }

  temps.get_strm() << "\n}\n\n\n"; 

  return ret;
}


bool RVTknGen::gen_copy_counts()
{
  bool ret = true;
  RVStrRec* rec0 = NULL;

  RVStrRecVec& all_recs = strs.get_rec_vec();

  temps.get_strm() << "\n"; 

  RVStrRecVec::const_iterator it;
  FORVEC(it,all_recs) {
    rec0 = (*it);
    temps.get_strm() << 
"  rv_"<< rec0->strname <<"_count[1] = rv_"<< rec0->strname <<"_count[0];\n";
  }

  temps.get_strm() << "\n"; 

  return ret;
}


bool RVTknGen::gen_check_counts()
{
  bool ret = true;
  RVStrRec* rec0 = NULL;
  RVStrRecVec& all_recs = strs.get_rec_vec();

  if( all_recs.size() > 0 )
    temps.print("\n  /* don't overflow the arrays: */\n");

  RVStrRecVec::const_iterator it;
  FORVEC(it,all_recs) 
  {
    rec0 = *it;

    ret = gen_assert_count_bound(rec0->strname, 0) && ret;
    ret = gen_assert_count_bound(rec0->strname, 1) && ret;

    /* also gen "assert( rv_Str_count[0] == rv_Str_count[1] );" */
    ret = gen_assert_eq_count(rec0->strname) && ret;
  }
  temps.print("\n"); 

  return ret;
}


bool RVTknGen::gen_assert_count_bound(std::string& strname, int side)
{
  temps.get_strm() <<   
"  assert( rv_"<< strname <<"_count["<< side <<"] <= "<< max_records <<" );\n";

  return true;
}

bool RVTknGen::gen_assert_eq_count(std::string& strname) 
{
  temps.get_strm() <<   
"  assert( rv_"<< strname <<"_count[0] == rv_"<< strname <<"_count[1] );\n";

  return true;
}

#endif
