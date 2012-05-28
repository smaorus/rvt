/* Functions for various DFSs on the call graph. */
#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_parse.h>
#include <rv_funcpair.h>
#include <rv_funcdfs.h>
#include <rv_funcnode.h>
#include <rv_collect.h>

#include <ctool/stemnt.h>

#define RV_SECTION RV_SEC_FUNCDFS


long RVFuncDfs::runs_counter = 0;

void RVFuncDfs::new_run(FunctionDef* root)
{
  /* OnStack nodes are marked by runs_counter value while
	 FinishedNodes are marked by runs_counter+1 value */
  runs_counter +=2;
  go(root);
} 


bool RVFuncDfs::isNew(RVFuncNode* node)  /* first time we meet this node. */
{ return(node->dfs_marks < runs_counter); }

bool RVFuncDfs::isNew(FunctionDef* func)
{ return isNew( &(func->fnode) ); }

bool RVFuncDfs::isOnStack(RVFuncNode* node)  /* DFS has found a cycle */
{ return(node->dfs_marks == runs_counter); }

bool RVFuncDfs::isOnStack(FunctionDef* func)
{ return isOnStack( &(func->fnode) ); }
  
bool RVFuncDfs::isFinished(RVFuncNode* node) /* finished it and its whole subtree */
{ return(node->dfs_marks == runs_counter+1); }

bool RVFuncDfs::isFinished(FunctionDef* func)
{ return isFinished( &(func->fnode) ); }


void RVFuncDfs::go(FunctionDef* it)
{
  if( !it )
	return;

  FuncVector sons;
  
  if( isOnStack(it) || isFinished(it) ) {
	revisit(it);
	return;
  }

  before_sons(it);

  it->fnode.dfs_marks = runs_counter;  /* mark it OnStack */

  go_sons(it, sons);

  it->fnode.dfs_marks++;  /* mark it as Finished */

  after_sons(it, sons);
}


SymbolVector& RVFuncDfs::get_potential_sons(FunctionDef* it)
{
  return it->fnode.callees;
  // Note: some of these may be ignored by ignore_son().
}


bool RVFuncDfs::ignore_son(Symbol* func_sym)
{
  /* ignore functions that can't have bodies: */
  return func_sym &&
	(RVParse::ignore_func(func_sym->name) || RVParse::supplied_by_rvt(func_sym->name));
}


void RVFuncDfs::go_sons(FunctionDef* it, FuncVector &ret_sons)
{
  SymbolVector& syms = get_potential_sons(it);
  Symbol* sym;
  FunctionDef* son;
  
  for (unsigned i = 0; i < syms.size(); i++) {
	
	son = NULL;
	sym = syms[i];
	if( !sym || !sym->entry || !(son = sym->entry->u2FunctionDef) ) {

	  if( ignore_son(sym) )
        continue;
	  
	  /* try to find the function on the parsetree: */
	  if( sym && parsetree ) {
		SymEntry* entry = lookup_function(sym->name, parsetree);
		son = (entry ? entry->u2FunctionDef : NULL);
	  }
	  if( !son ) {
		rv_errstrm << "Warning: RVFuncDfs::go_sons() can't get function \"" << 
		  (sym ? sym->name : "UNPRINTABLE") << "\" body from its symbol.\n";
		continue;
	  }
	}

	if( son )
	  ret_sons.push_back(son);

	if( son == it )
	  it->fnode.recursive = true;

	go(son);   
  }
}


/* RVPropagateEquality code */
/* ======================== */

//RVPropagateEquality::RVPropagateEquality(Project* _sides[2], std::string& root_name,
//					 RVDecisionParams& _params) : params(_params)
//{
//  sides[0] = _sides[0];
//  sides[1] = _sides[1];
//
//  SymEntry* se0 = lookup_function(root_name, sides[0]);
//  SymEntry* se1 = lookup_function(root_name, sides[1]);
//
//  if( !se0 || !se1 )
//	fatal_error((char *) "RVPropagateEquality::RVPropagateEquality(): can't find root function: ", root_name);
//
//  roots[0] = se0->u2FunctionDef;
//  roots[1] = se1->u2FunctionDef;
//
//  side = 0;
//  set_parsetree(sides[side]);
//  new_run(roots[side]);
//
//  side = 1;
//  set_parsetree(sides[side]);
//  new_run(roots[side]);
//
//  /* try not to check main - as it will be checked later by CBMC 
//	   on <base_name>.rv.c file. Check it only when forced: */
//  RVFuncPair* main_pair = rv_ufs.lookup(root_name, 0);  
//  if( main_pair && !params.chk_main )
//	main_pair->needs_semantic_check = false;
//}
//
//
//void RVPropagateEquality::after_sons(FunctionDef* it, FuncVector& sons)
//{
//  unsigned i;
//  FunctionDef* son = NULL;
//  FunctionDef* check_son = NULL;
//  FunctionDef* diff_son = NULL;
//  
//  RVFuncPair* son_pair = NULL;
//  RVFuncPair* pair = rv_ufs.lookup(it->decl->name->name, side);
//  if( !pair )
//	return;
//
//if(DBG) rv_errstrm<<"RVPropagateEquality checks func: "<< it->decl->name->name <<" \n";
//
//  if( side == 0 ) { 
//	pair->side0_fully_equal = false; /* we just now gona check it. */
//	pair->check_sons = 0;
//	pair->diff_sons = 0;
//  }
//
//  /* propagate inequality */
//  for(i = 0; i < sons.size(); i++) {
//	son = sons[i];
//
//	/* ignore recursive call or missing body: */
//	if( son == it )
//	  continue;
//
//	son_pair = NULL;
//	if( son && son->decl && son->decl->name ) {
//	  std::string& name = son->decl->name->name;
//
//	  /* ignore assume(), assert(), rv_getint(), ... */
//	  if( ignore_son(son->decl->name) ) 
//	continue;
//	  son_pair = rv_ufs.lookup(name, side);
//	}
//
//	if( !son_pair ) {
//	  pair->diff_sons++;
//	  diff_son = son;
//	  continue;
//	}
//
//	/* On side 0 we check only unpaired sons 
//		 - because se still don't know the equality values for the pairs: */
//	if( side == 0 ) {
//	  /* if we can't find paired call on side 1: */
//	  if( !pair->side_func[1]->fnode.callees.find(son_pair->side_name[1]) ) {
//	pair->diff_sons++;
//	diff_son = son;
//	continue;
//	  }	
//	} 
//	else { /* pairs are checked on side 1: */ 
//	  if( son_pair->equal_with_subtree || /* this is the good case */
//	  /* funcs in the same MSCC are checked in parallel - ignore: */
//	  son->fnode.mscc == it->fnode.mscc )
//	continue;
//	  else {
//	if( son_pair->needs_semantic_check || son_pair->has_check_successor ) {
//	  pair->check_sons++;
//	  check_son = son;
//	} else {
//	  pair->diff_sons++;
//	  diff_son = son;
//	}
//	continue;
//	  }
//	}
//  } /* for */
//
//  pair->decide_equality(check_son, diff_son, side, params);
//}
//
//
//void RVPropagateEquality::revisit(FunctionDef* it)
//{
//  /* if we found a cycle in the call graph and it isn't a simple recursive func: */
//  if( isOnStack(it) && !it->fnode.recursive ) {
//if(DBG) 
//	rv_errstrm << "RVPropagateEquality: Function \"" << it->decl->name->name 
//		   << "\" is mutually recursive.\n";
//  }
//}




/* RVArgTypesDfs code */
/* ================== */

void RVArgTypesDfs::propagate_argtypes(Project* _sides[2], std::string& root_name)
{
  sides[0] = _sides[0];
  sides[1] = _sides[1];

  SymEntry* se0 = lookup_function(root_name, sides[0]);
  SymEntry* se1 = lookup_function(root_name, sides[1]);

  if( !se0 || !se1 )
	fatal_error("RVArgTypesDfs::propagate_argtypes(): can't find root function: ", root_name);

  roots[0] = se0->u2FunctionDef;
  roots[1] = se1->u2FunctionDef;

  if(DBG) 
	rv_errstrm << "RVArgTypesDfs::propogate_argtyes(0) \"" << root_name << "\n";

  side = 0;
  set_parsetree(sides[side]);
  new_run(roots[side]);

  if(DBG) 
	rv_errstrm << "RVArgTypesDfs::propogate_argtyes(1) \"" << root_name << "\n";

  side = 1;
  set_parsetree(sides[side]);
  new_run(roots[side]);
}


void RVArgTypesDfs::go_sons(FunctionDef* it, FuncVector &ret_sons)
{
  if( !it )
	fatal_error("RVArgTypesDfs::go_sons(): NULL FunctionDef", false);

  RVPropArgTypes prop(this);
  prop.set_params(this->parsetree, this->side);

  prop.go_sons( it );
}



/* RVGlobDfs */
/*===========*/

void RVGlobDfs::collect(Project* pt, FunctionDef* start, std::string& func_name, int _side)
{
  if( !start || !pt )
	fatal_error("RVGlobDfs::collect(): NULL FunctionDef or parsetree", false);

  set_parsetree(pt);

  read.add_dup(start->fnode.read);
  written.add_dup(start->fnode.written);

  new_run(start);

  sort_vectors();

if(DBG) {
  rv_errstrm << "Globals used by \""<< func_name <<"\" (side "<< _side <<") and its successors: \n";
  read.print("read globals: ", rv_errstrm);
  written.print("written globals: ", rv_errstrm);
}
}


void RVGlobDfs::after_sons(FunctionDef* it, FuncVector& sons)
{
  unsigned rsize = read.size();
  unsigned wsize = written.size();
  unsigned rind = rsize;
  unsigned wind = wsize;
  RVFuncNode* node;

  FuncVector::const_iterator i;
  FORVEC(i,sons) {
	node = &(*i)->fnode;
	rsize += node->read.size();
	wsize += node->written.size();
  }

  read.resize(rsize);
  written.resize(wsize);

  SymbolVector::const_iterator j;
  FORVEC(i,sons) {
	node = &(*i)->fnode;
	for(j = node->read.begin(); j != node->read.end(); j++, rind++)
	  read[rind] = (*j)->dup();
	for(j = node->written.begin(); j != node->written.end(); j++, wind++)
	  written[wind] = (*j)->dup();
  }
}
  

void RVGlobDfs::sort_vectors()
{
  read.unique_sort();
  written.unique_sort();
}

bool RVGlobDfs::equal_vectors(RVGlobDfs& other)
{
  if( read.size() != other.read.size() ||
	  written.size() != other.written.size() )
	return false;

  return( read.all_related(other.read) && other.read.all_related(read) &&
	  written.all_related(other.written) && other.written.all_related(written) );
}



/* RVMarkNeededDfs */
/*=================*/

RVMarkNeededDfs::RVMarkNeededDfs(Project* _sides[2], const std::string& root_name) {
  sides[0] = _sides[0];
  sides[1] = _sides[1];

  std::string name0(root_name);
  std::string name1(root_name);

  RVFuncPair* root_pair = rv_ufs.lookup(root_name, 0);
  if( root_pair ) {
	name0 = root_pair->side_name[0];
	name1 = root_pair->side_name[1];
  }
  else
	rv_errstrm<<"Warning: RVMarkNeededDfs::RVMarkNeededDfs() is unable to find RVFuncPair \""<<
	  root_name <<"\" .";

  SymEntry* se0 = lookup_function(name0, sides[0]);
  if( !se0 )
	fatal_error("RVMarkNeededDfs::RVMarkNeededDfs(): can't find side 0 root function: ", name0);

  SymEntry* se1 = lookup_function(name1, sides[1]);
  if( !se1 )
	fatal_error("RVMarkNeededDfs::RVMarkNeededDfs(): can't find side 1 root function: ", name1);

  roots[0] = se0->u2FunctionDef;
  roots[1] = se1->u2FunctionDef;

  mark_side(0);
  mark_side(1);
}


void RVMarkNeededDfs::mark_side(int _side)
{
  side = _side;

  SymEntry*    se = NULL;

  /* first assume all functions as unneeded: */
  ScopeTbl* fs = get_file_scope(sides[side]);
  HashTblIter hit(fs->htab);
  for(se = hit.begin(); !hit.end(); se = hit.next())
	if( valid_function(se) )
	  se->u2FunctionDef->fnode.is_needed = false;
  
  /* then mark the needed ones: */
  set_parsetree(sides[side]);
  new_run(roots[side]);

  mark_indirect_func_subtrees();  
}


void RVMarkNeededDfs::mark_indirect_func_subtrees()
{
  SymEntry*    se = NULL;
  FunctionDef* func = NULL;

  ScopeTbl* fs = get_file_scope(sides[side]);
  HashTblIter hit(fs->htab);
  for(se = hit.begin(); !hit.end(); se = hit.next())
	if( valid_function(se) ) {
	  func = se->u2FunctionDef;
	  if( func->fnode.indirect )	
		new_run(func);
	}
}


void RVMarkNeededDfs::before_sons(FunctionDef* it)
{
  it->fnode.is_needed = true;
}


void RVMarkNeededDfs::go_sons(FunctionDef* it, FuncVector &ret_sons)
{
  /* find the relevant funcpair */
  RVFuncPair* pair = rv_ufs.lookup(it->FunctionName()->name, side);

  /* process sons only of non UFs */
  if( !pair || !pair->valid_pair() || !pair->is_uf() )
	RVFuncDfs::go_sons(it, ret_sons);
}

