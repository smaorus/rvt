#include <string.h>
#include <sstream>
#include <stack>
#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_temps.h>
#include <rv_funcpair.h>
#include <rv_loops.h>
#include <rv_indfunc.h>
#include <rv_parse.h>
#include <rv_arrays.h>
#include <rv_replace.h>

#define RV_SECTION RV_SEC_REPLACE


/* RVRenameTree functions: */
/* ======================= */

BaseType* RVRenameTree::channel_type = NULL; 


RVRenameTree::RVRenameTree(Project* _tree, const RVSide& _side)
  : RVWalk(/*decl_to_symbol =*/ true), parsetree(_tree), side(_side)
{
  directs = NULL;

  body = NULL;
  current_block = NULL;

  semchk_pair = NULL;
  semchk_recursive = false;
  semchk_use_uf_prefix = false;
  semchk_uf_sym = NULL;
  semchk_func = NULL;

  rvact_scope = NULL;
  rvact_decl  = NULL;
  rvact_call  = NULL;
  current_func_name = "";

  def_rvact_vals = NULL;
  m_bSymbolForTypeName = false;
}

RVRenameTree::~RVRenameTree()
{
  // delete rvact_scope; // ?? <<===
  delete rvact_decl;  // ?? <<===
  delete rvact_call;  

  if( def_rvact_vals ) {
	for(int i = 0; i < 3;i++)
	  delete def_rvact_vals[i];
	delete [] def_rvact_vals;
  }

  if (semchk_uf_sym) {
	  delete semchk_uf_sym;
	  semchk_uf_sym = NULL;
  }
}



bool  RVRenameTree::print_uf_rec_decl(const std::string& fname, std::ostream& out)
{
	  RVFuncPair*  pfp;
	  FunctionDef *func;
	  FunctionType *ft;
	  Decl         *args_i;
	  std::string  prefix;
	 
	  int          i;
	  bool        ret = true;

	  prefix = "rvs" + side.toString() + "_";
	  pfp = rv_ufs.lookup_have_bodies(fname , side.index());

	  if (!pfp) {
		  return false;
	  }

	  func = pfp->side_func[side.index()];

	  if (!func) {
		  return false;
	  }

	  ft = (FunctionType *) func->decl->form;

	  // Need to add the rvs_0/1 to the struct name in the UF
	  //

	  for (i=0;i<ft->nArgs;i++) {
		  args_i = ft->args[i];
		  if ( args_i->form->isPointer()) {
			  BaseType *bt = get_ptr_base(args_i->form);

			  if (bt && bt ->typemask & BT_UserType)
				  changeBaseTypeName(bt, prefix + bt->typeName->name);
		  }
	  }

	  func->decl->form->printBase(out,  0);
	  out << "rvs" << side.toString() << "_rec_UF" << fname;
	  func->decl->form->printAfter(out);
	  out  << ";\n";

	  return ret;
}

void RVRenameTree::prependPrefix(std::string& name, const std::string prefix) {
	name = prefix + name;
}

void RVRenameTree::changeBaseTypeName(BaseType *bt,
		                              const std::string& newName) const {
	assert(bt != NULL && bt->typeName != NULL);
	//if(DBG) rv_errstrm<<"TypeName: "<< it->typeName->name <<" \n";
    changeSymbolName(bt->typeName, newName);
	//if(DBG) rv_errstrm<<"  renamed to "<<it->typeName->name <<" \n";
}

void RVRenameTree::changeSymbolName(Symbol* sym,
		                            const std::string& newName) const {
	static unsigned int counter = 0;
	assert(sym != NULL);
	if (strncmp(newName.data(), "rvs", strlen("rvs")) == 0)
		++counter;
    if (sym->name.compare("list_t") == 0)
        ++counter;
	sym->name = newName;
}

void RVRenameTree::copyFromEntryName(Symbol* sym) const {
	changeSymbolName(sym, sym->entry->name);
};

void RVRenameTree::copyFromEntryNameCond(Symbol* sym) const {
    copyFromEntryName(sym);
}
void RVRenameTree::update_symbol(Symbol* sym, SymEntry* new_se) const {
	sym->entry = new_se;
	copyFromEntryName(sym);
}

bool  RVRenameTree::is_recursive_func(const std::string& fname) const {
	//DIMA_DEL
	//return recursive_func_lst.find(fname) != recursive_func_lst.end();
	return false;
}

void RVRenameTree::set_semchk_pair(RVFuncPair* pair, bool recursive)
{
  semchk_pair = pair;
  if( pair && recursive )
	semchk_recursive = true;
}

void RVRenameTree::set_directs(RVDirectives* _dirs)
{
  directs = _dirs;
}


std::string RVRenameTree::add_prefix(std::string& name, const char* prefix)
{
  std::string ret(prefix);
  return ret + name;
}


bool RVRenameTree::rename_globs(HashTbl* ht, const RVDecisionParams& params,
		                        bool tags /* = false */)
  /* RVTemp::get_side_prefix(side)  or 
	 RVTemp::get_semchk_prefix(side) or */
{
  SymEntry* se;
  HashTblIter hit(ht);
  HashTbl new_ht;

  while( (se = hit.begin()) ) { // processes first entry and remove it
	  const char* prefix = side.get_side_prefix();
	  bool do_rename = false;

	  if( is_top_level(se) ) {
	      do_rename = true;
	      if( !tags && is_function(se) ) {
			  // if it is a func undergoing semchk - add semchk special prefix.
		  	  if( semchk_pair && (semchk_pair->side_name[side.index()] == se->name) )
				  prefix = side.get_semchk_prefix();
#ifdef CBMC_UF
			  else
			  {
				  std::cout << "checking: " << se->name << " side" << side << std::endl;
				if (params.isSymEntryAmongIds(se, side))  
					prefix = UFPREFIX;
			  }
#endif
			  // Don't rename things such as __CPROVER_assume()/assert()...
			  if (RVParse::ignore_func(se->name))
			      do_rename = false;
	      }

	      if(DBG && do_rename) {
	    	  rv_errstrm<<"Prefix: "<<prefix<<"\n";
	    	  se->Show(rv_errstrm); rv_errstrm<<"\n";
	      }
	  } /* is_top_level() */

	  /* move the entry to the new hash table with a new name (if needed): */
	  ht->Delete(se);
	
	  if( do_rename )
		  prependPrefix(se->name, prefix);

	  new_ht.Insert(se);
  } /* while(se = hit.begin()) */

  /* move the contents of new_ht to the old one: */ 
  delete [] ht->tab;
  *ht = new_ht;

  /* make new_ht empty: */
  new_ht.tsize = 0; 
  new_ht.tab = NULL;

  return true;
}


bool RVRenameTree::rename_all_globs(const RVDecisionParams& params)
{
  bool ret = true;
  ScopeTbl* scope = NULL;

if(DBG) rv_errstrm << "Start RVRenameTree::rename_all_globs() \n";

  ScopeTbl* root = get_root_scope(parsetree);
  CHK_NULL1(root, "root symbol scope in RVRenameTree::rename_all_globs()");

  if( root->htab )
	ret = rename_globs(root->htab, params) && ret;

  for(int i = 0; i < root->nchild; i++) {
	scope = root->children[i];
	if( scope && scope->htab )
	  ret = rename_globs(scope->htab, params) && ret;
  }
   
if(DBG) rv_errstrm << "Finish RVRenameTree::rename_all_globs() \n";
  return true;
}


bool RVRenameTree::rename_all_tags(const RVDecisionParams &params)
{
  bool ret = true;
  ScopeTbl* scope = NULL;

if(DBG) rv_errstrm << "Start RVRenameTree::rename_all_tags() \n";

  ScopeTbl* root = get_root_scope(parsetree, TagEntry);
  CHK_NULL1(root, "root tag scope in RVRenameTree::rename_all_tags()");

  if( root->htab )
	ret = rename_globs(root->htab, params, true) && ret;

  for(int i = 0; i < root->nchild; i++) {
	scope = root->children[i];
	if( scope && scope->htab )
	  ret = rename_globs(scope->htab, params, true) && ret;
  }
   
if(DBG) rv_errstrm << "Finish RVRenameTree::rename_all_tags() \n";
  return true;
}


bool RVRenameTree::rename_all(const RVDecisionParams& params)
{
  CHK_NULL1(parsetree, "parsetree in RVRenameTree::rename_all()");
  bool ret = true;

  rv_arrays().set_side(side.index());

  /* we will generate check points only if directs where supplied: */
  if( directs )
	ret = create_rvact_proto() && ret;

  Decl *ufProto = NULL;
  ret = create_semchk_uf_proto(&ufProto) && ret;

  ret = rename_all_globs(params) && ret;
  ret = rename_all_tags(params) && ret;

  if (ret && ufProto != NULL)
      ret = process(ufProto);

  Statement* first_st = get_glob_stemnt(parsetree);
  for(Statement* st = first_st; st; st = st->next) 
	if( st->isFuncDef() )
	  ret = process_func((FunctionDef*)st) && ret;
	else
	  if( !process(st) ) {  // for other decls.
		ret = false;
		if(DBG) { rv_errstrm <<"Error: Failed to rename Decl: \n  ";
				  st->print(rv_errstrm, 0);
				  rv_errstrm << "\n"; }
	  }
  return ret;
}


bool RVRenameTree::print_all(RVTemp& temps, bool print_decls/*=true*/, bool print_funcs/*=true*/) const
{
  CHK_NULL1(parsetree, "parsetree in RVRenameTree::print_all()");

  Type* ftp = NULL;
  Statement* first_st = get_glob_stemnt(parsetree);
  for(Statement* st = first_st; st; st = st->next) {

	/* print UF prototype before recursive semchked func: */
	if( semchk_pair && semchk_recursive && semchk_uf_sym &&
	st->isFuncDef() && ((FunctionDef*)st) == semchk_func ) {
	  ftp = get_symbol_type(semchk_uf_sym, semchk_uf_sym->name.data());
	  ftp->printType(temps.get_strm(), semchk_uf_sym, true, 0);
	  temps.print(";\n");
	}

	// print the right class of global components:
	if( (st->isFuncDef() ? print_funcs : print_decls) )
	  { 
		  st->print(temps.get_strm(),0);
		  temps.print("\n");
	}
  }
	
  return true;
}


bool RVRenameTree::create_rvact_proto()
{
  CHK_NULL1(parsetree, "parsetree in RVRenameTree::create_rvact_proto()");

if(DBG) rv_errstrm << "Start RVRenameTree::create_rvact_proto() \n";

  if( !channel_type ) {
	/* create: typedef struct rv_channel { ?? } RVChannel; */
	std::string ut_name = RVTemp::RV_CHANNEL_UT;
	std::string tag_name = RVTemp::RV_CHANNEL_TAG;
	channel_type = new BaseType( BT_Struct );
	channel_type->tag = mk_symbol(tag_name, mk_tag(tag_name, NULL));
	channel_type->typeName = mk_symbol(ut_name, mk_typedef(ut_name, NULL));
	/* SHULD I add the SymEntries to somewhere ? <<=== */
  }

  FunctionType* ftp = new FunctionType();
  ftp->subType = new BaseType(BT_Void);
  rvact_scope = create_last_scope(parsetree, FUNCTION_SCOPE);

  PtrType* chptrtp = new PtrType();
  chptrtp->subType = channel_type;
  add_func_param(ftp, "CHANNEL", chptrtp, rvact_scope);
  add_func_param(ftp, "COND", new BaseType(BT_Int), rvact_scope);
  add_func_param(ftp, "VAL", new BaseType(BT_Long|BT_UnSigned), rvact_scope);

  rvact_decl = new Decl(ftp);
  std::string fname = side.get_rvact_name();
  Symbol* fsym = mk_symbol(fname, mk_fctdecl(fname, rvact_decl));
  rvact_decl->name = fsym;

  ScopeTbl* sym_scope = get_file_scope(parsetree);
  sym_scope->Insert(fsym->entry);

  Location tmploc(__LINE__,0,__FILE__);
  Variable* fvar = new Variable(fsym, tmploc);
  rvact_call = new FunctionCall(fvar, tmploc);

  /* create deault values for RVSAVE/RVCHECK calls: */
  def_rvact_vals = new Expression*[3];
  Symbol* chsym = mk_symbol(RV_DEF_CHANNEL_NAME, NULL);
  def_rvact_vals[0] = new Variable(chsym, tmploc);
  def_rvact_vals[1] = new IntConstant(1, false, tmploc);
  Symbol* errsym = mk_symbol("ERROR_VAL", NULL);
  def_rvact_vals[2] = new Variable(errsym,tmploc);

if(DBG) rv_errstrm << "Finish RVRenameTree::create_rvact_proto() \n";
  return true;
}


bool RVRenameTree::create_semchk_uf_proto(Decl** ppUfDecl)
{
  assert(ppUfDecl != NULL);
  *ppUfDecl = NULL;

  if( !semchk_pair || !semchk_recursive )
	return true;  // unneeded

  if(DBG) rv_errstrm << "Start RVRenameTree::create_semchk_uf_proto() \n";

  const char* semchk_uf_prefix = side.get_side_ufprefix();

  ScopeTbl* sym_scope = get_file_scope(parsetree);
  std::string fname = semchk_pair->side_name[side.index()];
  SymEntry* orig_ent = sym_scope->Lookup( fname );
  Decl* orig_decl = orig_ent->uVarDecl;
  FunctionDef* orig_st = orig_ent->u2FunctionDef;

  if(DBG && orig_ent) { rv_errstrm<<"Prepare semchked: "; orig_ent->Show(rv_errstrm); }

  if( !orig_ent || !orig_ent->IsFctDecl() || !orig_decl || !orig_st ) {
	rv_errstrm << "Error: unable to find semchked function: \""<<
	  semchk_pair->side_name[side.index()] << "\" on side " << side.toString() <<"\n";
	return false;
  }

  Decl* uf_decl = *ppUfDecl = orig_decl->dup0();

  /* Replace its symbol by a new one whose name is with the UF prefix,
	 but don't add it to any scope - so its name will stay right. */
  fname = add_prefix(fname, semchk_uf_prefix);
  semchk_uf_sym = mk_symbol(fname, mk_fctdecl(fname, uf_decl));
  semchk_uf_sym->entry->scope = NULL;
  delete uf_decl->name;
  uf_decl->name = semchk_uf_sym;

  if(DBG) rv_errstrm << "Finish RVRenameTree::create_semchk_uf_proto() \n";
  return true;
}


// deletes unneeded function bodies - but keeps their decls.
// 

bool RVRenameTree::remove_unneeded_funcs()
{
  bool ret = true;
  bool ignored, needed, is_uf;
  Statement *prev = NULL;
  Statement *tmpst = NULL;
  DeclStemnt *dst = NULL;
  Symbol    *sym = NULL;
  SymEntry  *ent = NULL;
  Decl      *decl = NULL;
  FunctionDef *func = NULL;

  if(DBG) rv_errstrm << "Start RVRenameTree::remove_unneeded_funcs() \n";

  Statement *st = get_glob_stemnt(parsetree);
  TransUnit *tu = parsetree->Parse_TOS->transUnit;
  ScopeTbl  *scp = get_file_scope(parsetree);

  CHK_NULL1(st && tu && scp, "st or tu or scp in RVRenameTree::remove_unneeded_funcs()");

  while( st ) {    
	sym = NULL;
	func = NULL;
	if( st && st->isFuncDef() ) {
	  func = (FunctionDef*)st;
	  if( func && (decl = func->decl) && func->decl->name )
	  sym = func->decl->name;
	}

	if( !sym ) {
	  prev = st;
	  st = st->next;
	  continue;
	}
	
	ignored = RVParse::supplied_by_rvt(sym->name) || RVParse::ignore_func(sym->name);
	needed  = rv_parser.is_needed(sym->name, side.index());
	is_uf   = rv_ufs.is_uf(sym->name, side.index());

	/* Note: prototypes of special funcs without bodies and UFs *are* needed: */

	/* delete bodies of UF or unneeded funcs which are not ignored: */
	if( (is_uf || !needed) && !ignored ) 
	{
	/* disconnect func body from its symbol: */
	ent = scp->Find(sym->name);
	if( !ent || !valid_function(ent) ) {
	  rv_errstrm << "Error: can't find SymEntry of function \""<<sym->name<<"\"in file scope\n";
	  ret = false;
	  st = st->next;
	  continue;
	}
	ent->u2FunctionDef = NULL; // invalidates the func - ensures we don't use it.

	if( is_uf ) {
	  /* replace its body by its declaration: */
	  dst = new DeclStemnt(st->location);
	  dst->addDecl(decl);

	  dst->next = st->next;
	  st->next = NULL;
	  if( prev ) 
		prev->next = dst;
	  else
		tu->head = dst;
	  tmpst = dst;
	}
	else { // just remove it
	  if( prev ) 
		prev->next = st->next;
	  else
		tu->head = st->next;
	  if( tu->tail == st )
		tu->tail = prev;
	  tmpst = st->next;
	}

	if( func )
	  func->decl = NULL; // it stays in the SymEntry.
	delete st; // ?? we delete the body anyway
	st = tmpst;
	}
	else {  /* we didn't remove or replaced anithing: */
	  prev = st;
	  st = st->next;
	}
  }

if(DBG) rv_errstrm << "Finish RVRenameTree::remove_unneeded_funcs() \n";

  return ret;
}


bool RVRenameTree::process_func(FunctionDef *_body)
{
  CHK_NULL1(_body, "RVRenameTree::process_func()");
 bool ret = true;

  body = _body;
  std::string orig_fname = body->FunctionName()->name;
  set_where( orig_fname.data() );

  current_func_name = orig_fname;

  rv_arrays().init(body, side.index(), where);

  if(DBG) rv_errstrm << "Start RVRenameTree::process_func() on \""<< where <<"\"\n";
  
  semchk_use_uf_prefix = false;  // for the func name in the decl
  ret = process(body->FunctionName()) && ret; // is not processed thru decl
  ret = process(body->decl) && ret;

  if( semchk_pair && (semchk_pair->side_name[side.index()] == orig_fname) ) {
	semchk_func = body;
	/* use UF version for recursive calls inside the body: */
	if( semchk_recursive )
	  semchk_use_uf_prefix = true; 
  }

  ret = process_block(body) && ret; // process body only

  semchk_use_uf_prefix = false; 

if(DBG) rv_errstrm << "RVRenameTree::process_func() on \""<< where <<"\": "
		   << (ret?"success":"failed") <<" \n";

  return ret; 
}


Expression* RVRenameTree::gen_check_point_code(ExprVector& vals, std::string& type_name)
{
  Expression* channel = NULL;
  Expression* cond    = NULL;
  Expression* val     = NULL;

  Location* pl = vals[0] ? &(vals[0]->location) : NULL;
  
  /* If it is name of a channel - it shouldn't be used as a label: */  
  if( type_name == RV_CHANNEL_TYPE_NAME ) {
	rv_errstrm << "Error: don't use channel names for labels: "<< type_name <<
	  " (in function: "<< where <<") \n";
	  return NULL;
  } 
  /* If it is a name of a check point use it: label = <channel, cond, val> */
  else if( type_name == RV_CP_TYPE_NAME ) {
	if( vals[0] ) channel = vals[0]->dup();
	if( vals[1] ) cond    = vals[1]->dup();
	if( vals[2] ) val     = vals[2]->dup();
  }
  /* If it is a name of a default check point (with default channel) 
	 use it: label = <cond, val> */
  else if( type_name == RV_DEF_CP_TYPE_NAME ) {
	if( vals[0] ) cond = vals[0]->dup();
	if( vals[1] ) val  = vals[1]->dup();
  } 
  else {
	rv_errstrm << "Error: unrecognized check point type: "<< type_name <<" at: ";
	if( pl ) pl->printLocation(rv_errstrm); else rv_errstrm <<"UNKNOWN";
	rv_errstrm <<" \n";
	return NULL;
  }

  /* set the default values - if needed */
  if( !channel ) channel = def_rvact_vals[0]->dup();
  if( !cond ) cond = def_rvact_vals[1]->dup();
  if( !val )  val  = def_rvact_vals[2]->dup();

  CHK_NULL1(rvact_call, "RVRenameTree::gen_check_point_code()");
  FunctionCall* ret = (FunctionCall*)rvact_call->dup();
  // Note: don't process channel name - it's OK as is.
  ret->args.push_back(new UnaryExpr(UO_AddrOf, channel, *pl));

  if( try_replace(&cond) && !process(cond) )
	ret = false;
  ret->args.push_back(cond);

  if( try_replace(&val) && !process(val) )
	ret = false;
  ret->args.push_back(val);

  return ret;
}


bool RVRenameTree::try_replace(Statement** pit)
  // insert RVCHECK/RVSAVE() 
{
  CHK_NULL1(pit && *pit, "RVRenameTree::try_replace(Statement**)");

  /* if no directs was supplied - no rvact to add: */
  if( !directs )
	return true;

  CHK_NULL1(rvact_scope && rvact_decl && rvact_call, 
		"rvact things ion RVRenameTree::try_replace(Statement**)");

  Block* block = NULL;
  LabelVector& vec = (*pit)->labels;
  LabelVector::const_iterator i;

  FORVEC(i, vec) 
	if( (*i)->type == LT_Goto && (*i)->name ) 
	{
	  SymEntry* se = directs->lookup_label(side, (*i)->name->name);
	  if( !se )
	continue;

	  std::string type_name;
	  ExprVector* vals = RVDirectives::get_check_point_vals(se, type_name);
	  if( !vals ) {
	rv_errstrm << "Error: bad check point declaration of "<< se->name <<
	  " which is used in \""<< where <<"\" on side "<< side.toString() <<"\n";
	if( se->uVarDecl )
	  se->uVarDecl->print(rv_errstrm,true,2); rv_errstrm << "\n";
	  }
	  
	  Expression* rvact = gen_check_point_code(*vals, type_name);

	  if( !block ) {
	block = new Block((*pit)->location);

	/* process the old statement before insretion: */
	if( !process(*pit) ) 
	  return false;

	/* insert the old stemnt (*pit) as its last one (Block::insert() adds to head): */
	block->insert(*pit);
	  }
	  block->insert(new ExpressionStemnt(rvact, (*pit)->location));
	}
  
  if( block ) { // we have added rvact before the Statement:
	block->labels = vec;
	(*pit)->labels.resize(0);
	*pit = block;
	return false;
  }

  return true;    
}


bool RVRenameTree::fix_loop_pvars(Variable** pit)
{
  int i;
  SymEntry* se = NULL;

  std::string& old_name = (*pit)->name->name;
  std::string ref_name = RVLoop::ref_argname(old_name);

  if( current_block && current_block->bnode.internal_scopes.size() > 0 ) {
	se = current_block->bnode.lookup_internal_scopes(old_name);
	/* if we found the symbol as is - just update its entry: */
	if( se ) {
	  update_symbol((*pit)->name, se);
	  return false; // all OK
	}
  }

  /* try it from the function level: */
  if( body ) {
	se = body->bnode.lookup_internal_scopes(old_name);
	if( !se )
	  se = body->bnode.lookup_internal_scopes(ref_name);   // try the rvp_ name 

	/* check that it is really a prototype symbol: */
	if( se && se->scope && se->IsParamDecl() && 
	se->scope->level == FUNCTION_SCOPE ) 
	{
	  update_symbol((*pit)->name, se);
	  return false; // all OK
	}
  }

  if( !body || !body->decl || !body->decl->form ||
	  !body->decl->form->isFunction() ) 
	return true; // safety

  /* check that we are really in a loop function: */
  if( !RVLoop::is_loop_name(body->FunctionName()->name, side) )
	return true;
  
  FunctionType* proto = (FunctionType*)body->decl->form;
  for(i = 0; i < proto->nArgs; i++) {
	if( !proto->args[i] || !proto->args[i]->name )
	  continue;
	
	Symbol* found_sym = proto->args[i]->name;
	if( found_sym->name == ref_name ) {
	  se = found_sym->entry;
	  break;
	}
  }

  if( !se ) // if still not found:
	return true;
  
  /* add "*rvp_" (LOOP_DEREF_PREFIX) to the Variable: */
  Symbol* newsym = mk_symbol(ref_name, se);
  Expression* res = RVLoopReplaceBase::mk_deref(newsym, (*pit)->location);
  delete *pit;
  *pit = (Variable*)res;
  return false; // all OK
}


bool RVRenameTree::fix_symbol_entry(Symbol* sym)
{
  ScopeTbl* scope = NULL;
  if(DBG) rv_errstrm << "RVRename::" << __FUNCTION__ << " \n";

  /* try to fix unconnected symbols - mainly for rvact symbols: */
  if( !sym || sym->entry )
	return true;

  SymEntry* se = NULL;

  std::string new_name = side.get_side_prefix();
  new_name += sym->name;
	
  if( parsetree ) {    
	scope = get_file_scope(parsetree, VarDeclEntry, false);
	
	if( scope ) {
	  se = scope->Find(sym->name);
	  if( !se )
	se = scope->Find(new_name);
	}
  
	if( se ) {
	  update_symbol(sym, se);
	  return true; // success
	}
  
	/* try to find it in the tags: */
	scope = get_file_scope(parsetree, TagEntry, false);
	if( scope )
	  se = scope->Find(new_name);

	if( se ) {
	  update_symbol(sym, se);
	  return true; // success
	}
  }

  if( current_block && current_block->bnode.internal_scopes.size() > 0 ) {
	se = current_block->bnode.find_from_internal_scopes(sym->name);
	if( !se )
	  se = current_block->bnode.find_from_internal_scopes(new_name);

	if( se ) {
	  update_symbol(sym, se);
	  return true; // success
	}   
  }    

  return false;
}

bool RVRenameTree::is_outlined(BinaryOp    bOp)
{
  bool ret = false;

  switch( bOp ) 
  {
	case BO_Mult: {
	  ret =  true;
	  break;
	}
	case BO_Div: {
	  ret =  true;
	  break;
	}
	case BO_Mod: {
	  ret =  true;
	  break;
	}
	case BO_Shl: {
	  ret =  true;
	  break;
	}
	case BO_Shr: {
	  ret =  true;
	  break;
	}
	default:
	  ret = false;
  }
  return ret;
}


std::string RVRenameTree::get_outlined_name(BinaryOp    bOp)
{
  std::string ret = "";

  switch( bOp ) 
  {
	case BO_Mult: {
	  ret = "mul";
	  break;
	}
	case BO_Div: {
	  ret = "div";
	  break;
	}
	case BO_Mod: {
	  ret = "mod";
	  break;
	}
	case BO_Shl: {
	  ret = "shl";
	  break;
	}
	case BO_Shr: {
	  ret = "shr";
	  break;
	}
	default:
	  ret = "";
  }
  return ret;
}


bool RVRenameTree::try_replace(Expression** pit)
{  
  CHK_NULL1(pit && *pit, "RVRenameTree::try_replace(Expression**)");

  Symbol* sym = NULL;
  Expression* new_ex = NULL;

  if( (*pit)->etype == ET_FunctionCall ) {
	  FunctionCall *tcall;
	  Symbol       *fsymbol;
	  Variable     *func_var_exp;

	  tcall = (FunctionCall *) (*pit);
	  func_var_exp = (Variable *) tcall->function;
	  fsymbol = func_var_exp->name;

	  // In case the recursive function call is not the lower most level, 
	  // We need to replace it with a UF
	  // Otherwise the code that will be generated will contain a recursion
	  // which will make the cbmc results weird ...
	  
	  if (is_recursive_func(fsymbol->name ) && (current_func_name == fsymbol->name)) {
		  Decl         *tmp_decl;
		  std::string  the_name;
		  RVFuncPair*  pfp   = rv_ufs.lookup_have_bodies(current_func_name, side.index());

		  if (DBG) rv_errstrm << "in recursion found call to " << fsymbol->name << "\n";

		  if (!pfp) {
			  rv_errstrm << "FATAL : recursive function that does not match : " << fsymbol->name << "\n";
		  }

		  the_name = "rec_UF" + current_func_name;
		  the_name = side.toString() + "_" + the_name;
		  the_name = "rvs" + the_name;

		  tmp_decl = rv_parser.mk_global_decl(parsetree, body->decl->form->dup0(), the_name ,FctDeclEntry);
		  tcall    = rv_parser.mk_func_call(tmp_decl->name,(*pit)->location);
		  
		  // Arguments are same as the original
		  tcall->args = ((FunctionCall *) (*pit))->args;

		  if (DBG) rv_errstrm << "func call " << (*tcall) << "\n";
		  (*pit) = tcall;
	  }
  }

  if( (*pit)->etype == ET_Variable && (sym = ((Variable*)(*pit))->name) )
  {
	if( !sym->entry )
	  fix_symbol_entry(sym);

	/* if was still unable to find its entry: */
	if( !sym->entry && !fix_loop_pvars((Variable**)pit) )
	  return false; // replaced - its OK
  }
  else if( (*pit)->etype == ET_UnaryExpr ) {
	UnaryExpr* s0p = (UnaryExpr*)(*pit);

	switch(s0p->uOp) {
	  case UO_PreInc:         // ++x
	  case UO_PreDec:         // --x
	  case UO_PostInc:        // x++
	  case UO_PostDec:        // x--
	// If it is a pointer inc/dec - convert it to our array function:
	if( is_pointer(s0p->operand()->type, where) )
	  new_ex = rv_arrays().create_unary_call(s0p->uOp, s0p->operand());
	if( new_ex ) {
	  s0p->_operand = NULL;
	  delete *pit;
	  *pit = new_ex;
	}
	break;

	  case UO_Deref:          // *
	// just replace it by the UA array item itself:
	if( is_pointer(s0p->operand()->type, where) )
	  new_ex = rv_arrays().create_item_access(s0p->operand(), NULL);
	if( new_ex ) {
	  s0p->_operand = NULL;
	  delete *pit;
	  *pit = new_ex;
	}
	break;	
	
	  default: /* ignore */;
	}
	return true; // process internal expr
  }
  else if( (*pit)->etype == ET_BinaryExpr ) {
	BinaryExpr* s0p = (BinaryExpr*)(*pit);
	Expression* new_ex = NULL;

	switch(s0p->bOp) {  
	  case BO_Plus:        // +
	  case BO_Minus:       // -
	if( is_pointer(s0p->type, where) )
	  new_ex = rv_arrays().create_binary_call(s0p);
	if( new_ex ) {
	  s0p->_leftExpr = NULL;
	  s0p->_rightExpr = NULL;
	  delete *pit;
	  *pit = new_ex;
	}
	break;

	  case BO_Rel: {
	RETYPE( RelExpr );
	if( is_pointer(s0p->leftExpr()->type, where) || 
		is_pointer(s0p->rightExpr()->type, where) )
	  new_ex = rv_arrays().create_rel_call(s0p);
	if( new_ex ) {
	  s0p->_leftExpr = NULL;
	  s0p->_rightExpr = NULL;
	  delete *pit;
	  *pit = new_ex;
	}
	break;
	  }

	  case BO_Assign: {
	RETYPE( AssignExpr );
	if( (s0p->op() == AO_PlusEql || s0p->op() == AO_MinusEql) &&
		is_pointer(s0p->leftExpr()->type, where) )
	  new_ex = rv_arrays().create_assign_call(s0p);
	if( new_ex ) {
	  s0p->_leftExpr = NULL;
	  s0p->_rightExpr = NULL;
	  delete *pit;
	  *pit = new_ex;
	}
	break;
	  }

	  default: /* ignore */;
	}
	return true; // process internal expr
  }
  else if( (*pit)->etype == ET_IndexExpr ) {
	IndexExpr *s0p = (IndexExpr*)(*pit);
	if( is_pointer(s0p->array->type, where) )
	  new_ex = rv_arrays().create_item_access(s0p->array, s0p->_subscript);
	if( new_ex )
	  *pit = new_ex;
  }

  return true;
}


bool RVRenameTree::process_block(Block* it)       
{ 
  /* remember the scope: */
  Block* save_block = current_block;

  current_block = it;
  bool ret = go_block(it); 
  current_block = save_block;

  return ret;
}


bool RVRenameTree::process(SymbolVector& vec)
{
  bool ret = true;
  
  SymbolVector::const_iterator i;
  FORVEC(i, vec)
	ret = process(*i) && ret;

  return ret;
}


bool RVRenameTree::process(Symbol* it)
  // copy it->name from entry 
{
  if( !it )
	return true;

  /* 
  Add (or just copy from SymEntry):
	 RVTemp::get_side_prefix(side)  (is also UF prefix) or 
	 RVTemp::get_semchk_prefix(side) or
	 (LOOP_DEREF_PREFIX is added in try_replace(Expression**) )
  */

  if( semchk_pair && (semchk_pair->side_name[side.index()] == it->name) ) {
	/* if it is a recursive call in the body of the semchked function -
	   use the UF symbol (the default one): */
	if( semchk_use_uf_prefix ) {
	  it->name = semchk_uf_sym->name;
	  it->entry = semchk_uf_sym->entry;
	  return true;
	}
  }


  //else
  if( it && it->entry ) 
	  m_bSymbolForTypeName? copyFromEntryNameCond(it)
			              : copyFromEntryName(it);
	  
  return true;
} 


bool RVRenameTree::process_basetype(BaseType* it)  // fix tag names 
{
  if( it && it->tag ) {
	if( it->tag->entry ) {
		//if(DBG) rv_errstrm<<"Tag: "<< *it->tag <<" \n";
		copyFromEntryNameCond(it->tag);
		//if(DBG) rv_errstrm<<"  renamed to "<< *it->tag <<" \n";
	}
  }
	
  if( it && it->typeName && it->typeName->entry ) {
	//if(DBG) rv_errstrm<<"TypeName: "<< it->typeName->name <<" \n";
	changeBaseTypeName(it, it->typeName->entry->name);
	//if(DBG) rv_errstrm<<"  renamed to "<<it->typeName->name <<" \n";

	/* get to its real type: */
	Type* rtp = get_symbol_type(it->typeName, where);
	if( rtp && !process(rtp) )
	  return false;
  }

  if( it->stDefn && !process(it->stDefn) )
	return false;

  if( it->enDefn && !process(it->enDefn) )
	return false;

  return true;
}


bool RVRenameTree::process(EnumDef* s0p) {
  if( s0p && s0p->tag && s0p->tag->entry )
	copyFromEntryNameCond(s0p->tag);

  bool bSymbolForTypeNameOld = m_bSymbolForTypeName;
  m_bSymbolForTypeName = true;
  for(int i = 0; i < s0p->nElements; i++) {
	PROC( names[i] );
	TRY_REP_PROC( values[i] );
  }
  m_bSymbolForTypeName = bSymbolForTypeNameOld;

  return true;
}


bool RVRenameTree::process(StructDef *s0p)
{
  Decl  *comp0;

  CHK_NULL("RVRenameTree::process(StructDef*)"); 

  /* prevent infinite recursion in recursive structs: */
  if( s0p->assumeEq == s0p )
	return true;
  s0p->assumeEq = s0p;

  if( s0p && s0p->tag ) {
    if(DBG) rv_errstrm<<"StructDef Tag: "<<s0p->tag->name<<" \n";
	if( s0p->tag->entry ) {
	  copyFromEntryNameCond(s0p->tag);
      if(DBG) rv_errstrm<<"  renamed to "<<s0p->tag->name<<" \n";
	}
  }

  for(int i=0; i < s0p->nComponents; i++) {  
	comp0 = s0p->components[i];
	while( comp0 ) {

if(DBG) rv_errstrm <<"RVRenameTree::process(StructDef*): processing \""<<comp0->name->name<<"\" \n";

	  if( !process(comp0) ) {
	s0p->assumeEq = NULL; // pop DFS mark
	return false;
	  }
	  comp0 = comp0->next;
	}
  }
	  
  s0p->assumeEq = NULL; // pop DFS mark
  return true;
}

bool RVRenameTree::process(Decl* s0p) {
	CHK_NULL("RVRenameTree::go(Decl*)");
	bool ret = true;

	if( s0p->name != NULL) {
		bool bSymbolForTypeNameOld = m_bSymbolForTypeName;
		m_bSymbolForTypeName = s0p->form != NULL && s0p->form->isBaseType();
		ret = process( s0p->name );
		m_bSymbolForTypeName = bSymbolForTypeNameOld;
	}

	if (s0p->form != NULL)
		ret = process(s0p->form) && ret;

	TRY_REP_PROC( initializer );

	return true;
}

void RVRenameTree::discharge(RVDischarger&) {
	delete_parsetree();
}


/* RVLoopReplaceBase functions: */
/* ============================ */

RVLoopReplaceBase::RVLoopReplaceBase()
{
  walk_goto_trg = false;
  break_from_switch = false;
}


void RVLoopReplaceBase::copy(LabelVector& dest, const LabelVector& src)
{
  LabelVector::const_iterator  j;

  FORVEC(j, src)
	dest.push_back((*j)->dup());
}


bool RVLoopReplaceBase::process(Statement* s0p)
{
if(DBG){rv_errstrm<<__FUNCTION__<<"\n";/*FDEL*/}
  CHK_NULL("RVLoopReplaceBase::process(Statement*)");

  bool ret = true;
  bool has_been_processed = false;
  bool save_break_from_switch = break_from_switch;

  switch( s0p->type )
  {
	case ST_TypedefStemnt:
	case ST_DeclStemnt: { 
	  /* these need special treatment because we ignore simbols: */
	  RETYPE( DeclStemnt );
	  unsigned i;
	  for(i = 0; i<s0p->decls.size(); i++)
	TRY_REP_PROC( decls[i]->initializer );

	  has_been_processed = true;
	  break;
	}

	case ST_SwitchStemnt:
	  break_from_switch = true;
	  break;

	case ST_ForStemnt:
	case ST_WhileStemnt:
	case ST_DoWhileStemnt: {
	  /* these 3 cases shouldn't happen: */
	  break_from_switch = false;
	  rv_errstrm << "Internal: RVLoopReplaceBase::process(Statement*): "
	"for, while or do-while loops should have been replaced, at: ";
	  s0p->location.printLocation(rv_errstrm); rv_errstrm <<" \n";
	  fatal_error("\n",false);
	  break;
	}

	case ST_ContinueStemnt:
	  rv_errstrm << "Warning: RVLoopReplaceBase::process(Statement*): \"continue\" "
	"statement - should have been replaced by now !\n";
	  break;

	/* just let RVWalk process all other statements: */
	case ST_NullStemnt:   // The null statement.
	case ST_ExpressionStemnt:
	case ST_IfStemnt:
	case ST_BreakStemnt:
	case ST_GotoStemnt: /* don't touch - may be result of try_replace() */
	case ST_ReturnStemnt:
	case ST_Block:      /* done in go_block( (Block*)s0p ) */
	  break;

	default:
	  rv_errstrm << "Unable to process Statement: ";
	  s0p->print(rv_errstrm, 0);  rv_errstrm << " \n";
	  return false;
  }

  if( !has_been_processed )
	ret = go(s0p) && ret;

  break_from_switch = save_break_from_switch;
  return ret;
}



/* RVReplaceInLoops functions: */
/* =========================== */

RVReplaceInLoops::RVReplaceInLoops()
  : RVLoopReplaceBase()
{
  loop = NULL;
  scope = NULL;
  res = NULL;
}


bool RVReplaceInLoops::replace_parts(Statement* s0p)
{
if(DBG){rv_errstrm<<"RVReplaceInLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  CHK_NULL("RVReplaceInLoops::replace_parts()");

  switch( s0p->type ) {

	case ST_ForStemnt: {
	  RETYPE( ForStemnt );
	  /* init - don't proccess init - stays in caller's scope. */
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

	default:
	  rv_errstrm << "RVReplaceInLoops::replace_parts(): bad loop statement type "
		 << s0p->type <<" at: ";
	  s0p->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
	  return false;       
  }
  
  return true;
}


bool RVReplaceInLoops::replace(RVLoop* _loop)
{
if(DBG){rv_errstrm<<"RVReplaceInLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
 
  loop = _loop;

  if( !loop || !loop->block || !loop->proto_scope || !loop->name )
	fatal_error("RVReplaceInLoops::replace(): loop or its item is NULL\n",false);

  scope = loop->proto_scope;
  break_from_switch = false;

  set_where( loop->name->name.data() );

if(DBG) rv_errstrm <<"RVReplaceInLoops replaces in loop: "<<where<<" \n";

  res = loop->block;

  return replace_parts(res);
}


Statement* RVReplaceInLoops::get_res()
{ 
if(DBG){rv_errstrm<<"RVReplaceInLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  Statement* tmp = res; 
  res = NULL; 
  loop = NULL;
  scope = NULL;
  return tmp; 
}





/// <summary>
/// Ofer: Checks whether the body of while/for/do-while includes a return statement. 
/// If yes then the calling function should have a switch statement, accounting for the case that the loop returned without terminating 
/// (in this case the calling function should return as well).
/// </summary>
static bool jumpsOutOfLoop(Statement *loop_statement) {
	
	StatementType t = loop_statement->type;
	assert( t == ST_WhileStemnt || t == ST_ForStemnt || t == ST_DoWhileStemnt); 
	Statement *st = NULL;		
	std::stack<Statement *> stack;

	stack.push(loop_statement);
	while (!stack.empty()) {
		Statement *top = stack.top();
		stack.pop();	
		switch(top->type) {
			case ST_ForStemnt: stack.push(((ForStemnt *)top) -> block); break;
			case ST_WhileStemnt: stack.push(((WhileStemnt *)top) -> block) ; break;
			case ST_DoWhileStemnt: stack.push(((DoWhileStemnt *)top) -> block) ; break;
			case ST_Block: {
				Block* bl;
				bl = (Block *) top;
				for (st = bl->head; st != NULL; st = st -> next) 
					stack.push(st);
				break;		
						   }

			case ST_IfStemnt: {
				IfStemnt *s1 = (IfStemnt *) top;							
				stack.push((Block*)(s1 -> thenBlk));
				if (s1 -> elseBlk != NULL) stack.push((Block*)(s1 -> elseBlk));
				break;	
							  }
							  
			case ST_SwitchStemnt: {
				SwitchStemnt *s1 = (SwitchStemnt *) top;
				stack.push(s1 ->block);
				break;
								  }
			
			case ST_ReturnStemnt:
			case ST_GotoStemnt:
				return true;
								  			
			default: break;
			}
		}	
	return false;
}

/// <summary>
/// Given a loop statement inside another (nesting) loop, replaces it with a call to the function that replaced it. 
/// </summary>
bool RVReplaceInLoops::replace_by_call(Statement** pst, Expression* init)
{
if(DBG){rv_errstrm<<"RVReplaceInLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !(*pst)->bnode.loop_rec ) {
	rv_errstrm << "RVReplaceInLoops::replace_by_call(): block at ";
	(*pst)->location.printLocation(rv_errstrm);
	rv_errstrm << " has NULL loop_rec. \n";
	return true; /* process it anyway - so it will be easier to find the problem. */
  }
    

  bool loop_has_return = jumpsOutOfLoop(*pst);
  
  Statement* rep = (*pst)->bnode.loop_rec->create_call_from_loop(init, loop, loop->retarg, loop_has_return);

  copy(rep->labels, (*pst)->labels);
  /* don't delete (*pst) because it is the loop code itself */
  *pst = rep;

  return false;
}


Statement* RVReplaceInLoops::find_containing_block(Symbol* label)
  /* finds the loop block (or function body) where the label appears - 
	   but only if it is the current one or contains it. */
{
  CHK_NULL1(label && loop,"RVReplaceInLoops::find_containing_block()");
  RVLoop* lp = loop;
  
  for(; lp; lp = lp->parent)
	if( lp->block && lp->block->bnode.labels.find(label->name) )
	  return lp->block;

  /* if not found in enclosing loops - lookup in the original function body: */
  if( loop->orig_func && loop->orig_func->bnode.labels.find(label->name) )
	return loop->orig_func;

  return NULL;
}


Block* RVReplaceInLoops::make_loop_return_block(Expression* result, 
						unsigned termination_code, Location& l)
{
  CHK_NULL1(loop, "RVReplaceInLoops::make_loop_return_block()");
  Symbol* tmp = NULL;
  Expression* exp = NULL;

  /* make "{*p_retval = result; return <loop-termination-code>;}": */

  Block* blk = new Block(l);
  if( loop->retarg && result ) {
	tmp = loop->retarg->dup();
	exp = mk_deref(tmp, l);
	exp = new AssignExpr(AO_Equal, exp, result, l); 
	
	ExpressionStemnt* st1 = new ExpressionStemnt(exp, l);
	blk->add(st1);
  }
  
  /* gen return of the right loop termination code: */
  IntConstant* ltc_ret = new IntConstant(termination_code, false, l);
  ReturnStemnt* st2 = new ReturnStemnt(ltc_ret, l);
  blk->add(st2);

  return blk;
}
		

bool RVReplaceInLoops::try_replace(Statement** pst)
{
if(DBG){rv_errstrm<<"RVReplaceInLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !pst || *pst == NULL )
	return false;

  Symbol*     tmp = NULL;
  Statement*  rep = NULL;

  switch( (*pst)->type ) 
  {
	case ST_ContinueStemnt:
	  /* replace by "goto l_continue;" */
	  tmp = new Symbol();
	  tmp->name = LOOP_CONTINUE;
	  rep = new GotoStemnt(tmp, (*pst)->location);
	  copy(rep->labels, (*pst)->labels);
	  delete *pst; /* ?? <<=== */
	  *pst = rep;
	  loop->has_continue = true;
	  return false;

	case ST_BreakStemnt:
	  /* if its a loop break: */
	  if( !break_from_switch ) {
	/* replace by "goto l_break;" : */
	tmp = new Symbol();
	tmp->name = LOOP_BREAK;
	rep = new GotoStemnt(tmp, (*pst)->location);
	copy(rep->labels, (*pst)->labels);
	delete *pst; /* ?? <<=== */
	*pst = rep;  
	loop->has_break = true;
	return false;
	  }
	  return true;

	case ST_GotoStemnt: {     // FIN <<====
	  GotoStemnt* gtst = (GotoStemnt*)*pst;
	  Location& l = gtst->location;

	  Statement* dest_blk = find_containing_block(gtst->dest);
	  if( !dest_blk ) {
	rv_errstrm << "Error: can't find label \""<< *gtst->dest <<"\" in the same block "
	  "or an enclosing block of a ";
	gtst->print(rv_errstrm,0); rv_errstrm<<"\n  at: ";
	gtst->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
	rv_errstrm << "  This goto statement probably jumps into a loop body from outside it.\n"
	  "  This behaviour is unsupported.\n";

	return false; // THROW <<===
	  }

	  CHK_NULL1(loop && loop->orig_func, "orig_func in RVReplaceInLoops::try_replace()");

	  if( dest_blk == loop->block ) // if its in current block:
	return true; // leave goto as is.

	  /* replace by "{return <label-symbol-index>;}": */
	  FunctionDef* orig_func = loop->orig_func;
	  unsigned ind = RVFuncNode::get_label_index(orig_func, gtst->dest);
	  if( ind == 0 ) {
	rv_errstrm<<"Bad label index "<< ind <<" of label \""<< *gtst->dest <<"\" at ";
	gtst->location.printLocation(rv_errstrm); rv_errstrm<<"\n";
	return false;
	  }
	
	  rep = make_loop_return_block(NULL, ind, l);

	  copy(rep->labels, (*pst)->labels);
	  delete *pst; /* ?? <<=== */
	  *pst = rep;
	  return false;
	}

	case ST_ReturnStemnt: {
	  ReturnStemnt* s0p = (ReturnStemnt*)*pst;
	  Location& l = s0p->location;

	  /* must process return expression for caller's scope: */
	  TRY_REP_PROC( result ); 

	  /* replace by "{*p_retval = data; return LTC_RETURN;}": */
	  // ofer: This adds the 'return 123' if we are inside a loop and there is a return statement. This way we catch if one loop returns and the other doesn't. 
	  // note that this is for the check of the equivalence of the loops. Unrelated to the way '123' is used inside the UF later on if these loops are indeed equal. 

	  rep = make_loop_return_block(s0p->result, LTC_RETURN, l);

	  copy(rep->labels, (*pst)->labels);
	  s0p->result = NULL;
	  delete *pst; /* ?? <<=== */
	  *pst = rep;
	  return false;
	}

	case ST_ForStemnt: {
	  ForStemnt* s0p = (ForStemnt*)*pst;
	  /* must process init of callee for caller's scope: */
	  TRY_REP_PROC( init ); 
	  return replace_by_call(pst, s0p->init);
	}

	case ST_WhileStemnt:
	case ST_DoWhileStemnt:
	  return replace_by_call(pst, NULL);

	default:
	  return true;
  }
}


bool RVReplaceInLoops::process_member_op(BinaryExpr* s0p)
{
if(DBG){rv_errstrm<<"RVReplaceInLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  CHK_NULL("RVReplaceInLoops::process_member_op()");
  
  /* don't replace component symbols - process only left side: */
  REP_PROC( _leftExpr );
  
  return true;
}


bool RVReplaceInLoops::try_replace(Expression** pexpr)
{
if(DBG){rv_errstrm<<"RVReplaceInLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !pexpr || *pexpr == NULL )
	return false;

  std::string name;

  if( (*pexpr)->etype == ET_Variable && 
	  loop->block->bnode.pvars.find( name = ((Variable*)(*pexpr))->name->name ) ) 
  {
	name = RVLoop::ref_argname(name);

	SymEntry* ent = scope->Lookup(name);
	if( !ent ) {
	  rv_errstrm << "Internal: RVReplaceInLoops::try_replace(Expression**): can't find \""<< 
	name <<" in proto_scope of "<< where <<" \n";
	  fatal_error("\n",false);
	}

	
	Symbol* tmp = new Symbol();
	tmp->name = name;
	tmp->entry = ent;
	Expression* rep = mk_deref(tmp, (*pexpr)->location);
	*pexpr = rep;
	return false; /* replaced - don't process */
  }

  return true;
}



/* RVReplaceLoopCalls functions: */
/* ============================= */

RVReplaceLoopCalls::RVReplaceLoopCalls()
{
  body   = NULL;
  retvar = NULL;
}


bool RVReplaceLoopCalls::create_retvar()
{
if(DBG){rv_errstrm<<"RVReplaceLoopCalls::"<<__FUNCTION__<<"\n";/*FDEL*/}

  Type* type = ((FunctionType*)body->decl->form)->subType;
  if( is_basetype( type, BT_Void) ) {
	/* no return value is needed: */
	retvar = NULL;
	return true;
  }

  /* add LOOP_RETVAR var Decl to the head of the Block: */ 
  retvar = new Symbol();
  retvar->name = LOOP_RETVAR;

  Decl* decl = new Decl(type);
  decl->name = retvar;
  decl->initializer = new UIntConstant(0, false, body->location);

  SymEntry* entry = mk_vardecl(retvar->name, decl);
  retvar->entry = entry;

  ScopeTbl* scp = get_func_local_scope(body, parsetree);

  if( scp ) 
	scp->Insert(entry);
  else {
	entry->scope = NULL;
	rv_errstrm << "Warning: RVReplaceLoopCalls::create_retvar(): can't get local scope "
	  "of function: \""<< where <<"\" \n";
  }

  DeclStemnt* declst = new DeclStemnt(body->location);
  declst->addDecl(decl);
  
  /* put it as the first statement of the func: */ 
  declst->next = body->head;
  body->head = declst;

  return true;
}

/// <summary>
/// Scans the input function for loops. Enters each of them to the vector RVLoops. Creates the call to them in _body.
/// </summary>
/// <param name="_body">The body of the function being processed. </param>
/// <param name="_parsetree">the parsetree. </param>
bool RVReplaceLoopCalls::replace(FunctionDef* _body, Project* _parsetree /*= NULL*/)
{
if(DBG){rv_errstrm<<"RVReplaceLoopCalls::"<<__FUNCTION__<<"\n";/*FDEL*/}
  body = _body;
  parsetree = _parsetree;

  if( !body )
	fatal_error("RVReplaceLoopCalls::replace(): loop or its item is NULL\n",false);

  set_where( body->FunctionName()->name.data() );

  if( !body->fnode.has_loops() )
	return true;

if(DBG) rv_errstrm <<"RVReplaceLoopCalls on func: "<<where<<" \n";

   if( !create_retvar() )	return false; //ofer: retvar is only used if there is a return <value> statement inside a loop

  bool ret = process( body );

if(DBG) rv_errstrm <<"RVReplaceLoopCalls::replace() finished func: "<<where<<" \n";

  return ret; 
}







/// <summary>
/// Replaces a loop statement in a function to a call to the new loop function that replaced that loop. 
/// for example, f() {i = 0; while(x < i) x++;} will be replaced by 
/// f(){i = 0; Loop_while(...)} or by 
/// f(){i = 0; switch(Loop_while(...)) {... } // in case the loop contained a return statement. 
/// </summary>
bool RVReplaceLoopCalls::replace_by_call(Statement** pst, Expression* init)
{
if(DBG){rv_errstrm<<"RVReplaceLoopCalls::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !(*pst)->bnode.loop_rec ) {
	rv_errstrm << "RVReplaceLoopCalls::replace_by_call(): block at ";
	(*pst)->location.printLocation(rv_errstrm);
	rv_errstrm << " has NULL loop_rec. \n";
	fatal_error("\n",false);
	return true; /* process it anyway - so it will be easier to find the problem. */
  }

  
  bool loop_has_return = jumpsOutOfLoop(*pst);   // ofer: here we find whether the loop contains a return or goto statement and send it to create_call  

  Statement* rep = (*pst)->bnode.loop_rec->create_call(init, retvar, loop_has_return);

  copy(rep->labels, (*pst)->labels);
  /* don't delete (*pst) because it is the loop code itself */

if(DBG) {
  rv_errstrm<<"Old code:\n";
  (*pst)->print(rv_errstrm,1); rv_errstrm<<"\n";
  rv_errstrm<<"New code:\n";
  rep->print(rv_errstrm,1); rv_errstrm<<"\n\n";
}

  *pst = rep;

  return false; /* replaced - don't process */
}


bool RVReplaceLoopCalls::try_replace(Statement** pst)
{
if(DBG){rv_errstrm<<"RVReplaceLoopCalls::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !pst || *pst == NULL )
	return false;

  switch( (*pst)->type ) 
  {
	case ST_ForStemnt: {
	  ForStemnt* fst = (ForStemnt*)*pst;
	  return replace_by_call(pst, fst->init);
	}

	case ST_WhileStemnt:
	case ST_DoWhileStemnt:
	  return replace_by_call(pst, NULL);

	default:
	  return true;
  }
}





/*  RVReplaceType  */
/* =============== */

RVReplaceType::RVReplaceType(const Type* _from, Type* _into)
  : from(from), into(into)
{
  if( !_from || !_into )
	fatal_error("RVReplaceType::RVReplaceType() got NULL Type");
  real_from = real_type(from, "RVReplaceType::RVReplaceType()");
}

bool RVReplaceType::replace_all(Project* _tree, int _side)
{
  CHK_NULL1(_tree, "_tree is NULL or bad _side in RVReplaceType::replace_all()");
  bool ret = true;

  parsetree = _tree;
  side = _side;

  Statement* first_st = get_glob_stemnt(parsetree);

  for(Statement* st = first_st; st; st = st->next) 
	if( st->isFuncDef() )
	  ret = process_func((FunctionDef*)st) && ret;
	else {
	  set_where("Global declaration");
	  if( !process(st) ) {  // for other decls.
		ret = false;
	  }
	}

  return ret;  
}


bool RVReplaceType::process_func(FunctionDef *_body)
{
  CHK_NULL1(_body, "body in RVReplaceType::process_func()");
  bool ret = true;

  body = _body;
  std::string orig_fname = body->FunctionName()->name;
  set_where( orig_fname.data() );

  body->equalTo = NULL;

  ret = RVWalk::process(body->decl) && ret;
  ret = process_block(body) && ret; // process body only

  return ret; 
}
 
bool RVReplaceType::try_replace(Type** it)
{
  if( !it || *it == NULL )
	return false;
  
  if( *it == from || *it == real_from ) {
	*it = into;
	return false; // don't process the new type
  }
 
  return true;
}
