#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_parse.h>
#include <rv_funcpair.h>
#include <rv_loops.h>
#include <rv_collect.h>
#include <rv_funcdfs.h>
#include <rv_arrays.h>
#include <rv_indfunc.h>
#include <rv_traversal.h>
#include "rv_glob.h"

#define RV_SECTION RV_SEC_COLLECT


/* RVCollectBase functions: */
/* ======================== */

RVCollectBase::RVCollectBase()
{
  walk_goto_trg = false;
  top_loops_cnt = 0;
  first_decl_in_block = false;
  array_ref_collector = NULL;
}


void RVCollectBase::start_func()
{
  if( !body || !body->decl || !body->decl->name )
    fatal_error("RVCollectBase::start_func(): body is NULL or invalid.",false);
  set_where( body->FunctionName()->name.data() );  
  top_loops_cnt = 0;

  if( array_ref_collector ) {
    array_ref_collector->init(body, side, where);
    rv_arrays().init(body, side, where);
  }
}

bool RVCollectBase::process(Statement* s0p)
{
  bool in_loop_block = false;
  RVLoop* loop_rec = NULL;

  if(DBG){rv_errstrm<<"RVCollectBase::"<<__FUNCTION__<<"(Statement*)\n";/*FDEL*/}

  CHK_NULL("RVCollectBase::process(Statement*)");

  /* for debug open this one
  rv_errstrm << "\nRVCollectBase::process(Statement) \n"; 
  s0p->print(rv_errstrm,0) ;
  rv_errstrm << "\nAFTER .... RVCollectBase::process(Statement)\n"; 
  */

  switch( s0p->type )
  {
    case ST_TypedefStemnt:
    case ST_DeclStemnt: {
      RETYPE( DeclStemnt );

      if( first_decl_in_block ) {
	/* Connect last loop block(s) to their scope: */
	ScopeTbl* scp = get_scope(s0p, "RVCollectBase::process(Statement*)");

	/* if it's the first decl in the function - save the scope: */ 
	body->bnode.add_internal_scope(scp);

	/* all the lstack which this is their first symbol scope: */
	for(int i = lstack.size()-1; i >= 0; i--)
	  lstack[i]->bnode.add_internal_scope(scp);

	first_decl_in_block = false;
      }

      /* should process the initializers: */
      unsigned decls_size = s0p->decls.size();
      for(unsigned i = 0; i < decls_size; i++)
	PROC( decls[i] );
      break;
    }

    case ST_ForStemnt: // ofer: here we meet the loops for the first time. They are put in the loops list.
    case ST_WhileStemnt:
    case ST_DoWhileStemnt: {
      /* add to "lstack" vector: */
      lstack.push_back(s0p);

      /* if we didn't collect this loop yet. */
      if( s0p->bnode.loop_rec == NULL ) {

	/* if its the first loop of the function: */
	if( !body->fnode.has_loops() )
	  body->fnode.loops_index = rv_loops.get_next_index();
	
	RVLoop* parent = NULL;
	if( lstack.size() > 1 )
	  parent = (*(lstack.end()-2))->bnode.loop_rec; // previous loop on lstack

	/* add the loop to the rv_loops list. */
	loop_rec = rv_loops.add_loop(s0p, body, parent);
      }
      else
	loop_rec = s0p->bnode.loop_rec;

      in_loop_block = true;
      break;
    }

    default:
      in_loop_block = false; 
  }

  /* add name to this loop if needed: */
  if( in_loop_block && loop_rec && loop_rec->name == NULL ) {

    if( lstack.size() == 0 )
      fatal_error("RVCollectBase::process(Statement*): empty loops stack - can't add name.\n",false);

    int loop_cnt; /* in its scope. */
    RVLoop* parent = NULL; 
    std::string parent_name = body->FunctionName()->name;
    if( lstack.size() > 1 ) {
      parent = loop_rec->parent;
      if( !parent || !parent->name ) {
	rv_errstrm << "Internal: Loop parent or its name is NULL. at loop: \n";
	s0p->print(rv_errstrm, 0);  rv_errstrm << " \n";
	return false;
      }

      parent_name = parent->name->name;
      loop_cnt = parent->inc_nested_count();
    }
    else
      loop_cnt = ++top_loops_cnt;

    loop_rec->create_name(parent_name, loop_cnt);

if(DBG && loop_rec && loop_rec->name)
  {rv_errstrm << "New loop func name: " << loop_rec->name->name <<"\n";}

  } /* in_loop_block ... */

  bool res = go(s0p);

  if( in_loop_block ) {
    /* POP the loop from lstack array: */
    lstack.pop_back();	
    in_loop_block = false;
  }

  return res;
}

bool RVCollectBase::process(Decl* s0p)
{
  CHK_NULL("RVCollectBase::process()");
  
  /* we are only interested in local var initializers: */
  if( !is_global_var( s0p->name ) )
    TRY_REP_PROC( initializer );

  return true;
}

bool RVCollectBase::process_block(Block* it)       
{ 
  first_decl_in_block = true;

  return go_block(it); 
}


Symbol* RVCollectBase::get_pointer_in_offset_expr(Expression* s0p)
{
  BinaryExpr* bop;
  Symbol *lsym, *rsym;  

  /* if it is a direct var: */
  Symbol *sym = try_var2symbol( s0p );
  if( sym && ( sym->entry->uVarDecl->form->isPointer() || 
	       sym->entry->uVarDecl->form->isArray() ) )
    return sym;

  if( s0p->etype != ET_BinaryExpr )
    return NULL;
  
  bop = (BinaryExpr*)s0p;
  
  if( bop->bOp != BO_Plus && bop->bOp != BO_Minus ) 
    return NULL;

  try_collect_non_offset_expr(bop->leftExpr());
  try_collect_non_offset_expr(bop->rightExpr());

  lsym = get_pointer_in_offset_expr(bop->leftExpr());
  rsym = get_pointer_in_offset_expr(bop->rightExpr());

  if( lsym && rsym ) {
    rv_errstrm << "Warning: found pointers on both sides of dereference-"
      "with-offset expression. in : " << where << ", ";
    s0p->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
  }

  /* ! Note: We should also check whether we have a constant offset of 0
         and then it is a single item use and not an array. <<===
	 Also should check it in other places !
  */

  if( lsym )
    return lsym;
  
  return rsym;
}


void RVCollectBase::add_callees( Symbol *sym, int num_args )
{
  if( !sym || !body ) {
    fatal_error("RVCollectBase::add_callees() received NULL !\n",false);
    return;
  }

  if( RVParse::ignore_func(sym->name) ) {
      // for debug rv_errstrm << "ignoring " << sym->name << "\n";
    return;
  }

  /* add caller pointer to the called function body - if possible: */
  if( parsetree && 
	  !RVParse::supplied_by_rvt(sym->name) ) {

		  SymEntry *funcse = lookup_function( sym->name, parsetree );
		  if( !funcse || !valid_function(funcse) ) {
			  rv_errstrm << "In function \""<< *body->FunctionName() <<" (side " << side << "):" << 
				  " unable to find called function: \"" << sym->name << "\" in parse tree.\n";
		  }
		  else {
			  Symbol *fname = body->FunctionName();
			  funcse->u2FunctionDef->fnode.callers.push_back( fname->dup() );

			  if(DBG) rv_errstrm << "callee \""<< funcse->name <<"\" has "<< num_args <<" args!\n";

			  funcse->u2FunctionDef->fnode.count_args( num_args );
		  } 
  }

if(DBG) rv_errstrm<<"add_callees( "<<sym->name<<" )\n";
  body->fnode.callees.push_back( sym->dup() );
}

void RVCollectBase::add_read( Symbol *sym )
{
  if( !sym || !body ) {
    fatal_error("RVCollectBase::add_read() received NULL !\n",false);
    return;
  }

  if(DBG) rv_errstrm << "add_read( " << sym->name << " )\n";
  body->fnode.read.push_back( sym->dup() );
}

void RVCollectBase::add_written( Symbol *sym )
{
  if( !sym || !body ) {
    fatal_error("RVCollectBase::add_written() received NULL !\n",false);
    return;
  }

if(DBG) rv_errstrm<<"add_written( "<<sym->name<<" )\n";
  body->fnode.written.push_back( sym->dup() );
}

void RVCollectBase::add_argtype(int ind, ArgType type)
{
  if( !body ) {
    fatal_error("RVCollectBase::add_argtype() received bad function body", false);
    return;
  }

  body->fnode.switchOn_argtype(ind, type);
}  

///<summary>
///This method inserts a symbol into either vars (read-only) or pvars (written-to)
///of all the loops nesting the current location of the traversal.
///</summary>
void RVCollectBase::add_scope_vartype(Symbol* sym, bool is_written)
{
  bool is_array = false;
  if(DBG){rv_errstrm<<"RVCollectBase::"<<__FUNCTION__<<"\n";/*FDEL*/}

  if( !sym || !body || !sym->entry ) {
    fatal_error("RVCollectBase::add_scope_vartype() received NULL !\n",false);
    return;
  }

  SymEntry* entry = sym->entry;
  if( !entry->IsVarDecl() && !entry->IsParamDecl() ) /* collect only vars */
    return;

  /* we collect only func params and locals - not globals: */
  if( is_global_var( entry ) )
    return;

  ScopeTbl* scp = entry->scope;
  if( !scp ) {
    rv_errstrm << "RVCollectBase::add_scope_vartype(): symbol \""<< *sym <<
      "\" has NULL scope. In function: \""<< *body->FunctionName() <<"\" \n";
    fatal_error("RVCollectBase::add_scope_vartype(): NULL scope.\n", false);
  }

  Statement* blk = NULL;
  for(int i = lstack.size()-1; i >= 0; --i) 
  {
	  blk = lstack[i];

	  if(DBG && blk->bnode.loop_rec)
	  {rv_errstrm<<"check scope of: \""<< blk->bnode.loop_rec->name->name <<"\"\n";}

	  /* if internal to this block - don't collect as var/pvar */
	  if( blk->bnode.is_internal_scope(scp) )
		  continue;

	  if(DBG) {

		  /* check it is really external scope: */
		  if( blk->bnode.internal_scopes.size() > 0 ) {

			  ScopeTbl* blkscp = blk->bnode.internal_scopes[0];
			  if( blkscp && blkscp->parent )
				  if( blkscp->parent->Find(sym->name) != entry )
				  {
					  rv_errstrm<<"add_scope_vartype() can't find the scope of "<< sym->name <<
							  " which should be external to loop block at ";
					  blk->location.printLocation(rv_errstrm); rv_errstrm <<" \n";
					  fatal_error("RVCollectBase::add_scope_vartype(): can't find the right scope.\n",false);
				  }
		  }

		  rv_errstrm<<"add_scope_vartype() of \""<< sym->name <<"\" to "<<
				  (is_written?" pvars ":"vars") << " of loop block at ";
		  blk->location.printLocation(rv_errstrm); rv_errstrm <<" \n";
	  } /* DBG */

	  /* if it is output or struct - pass it by reference: */
	  Type* tp = real_type(entry->uVarDecl->form, where);


	  // YL if it is an array no need to pass it as pvar
	  //
	  int arr_sz;
	  Symbol *org;
	  if (RVGlob::getArrHooks().find_sym(sym , &arr_sz, &org, side) != -1) {
		  //rv_errstrm << sym->name << " : add_scope_vartype() is array\n";
		  is_array = true;
	  }
	  if ((!is_array) && (is_written || is_basetype(tp, (BT_Struct|BT_Union)) ))  /* <<=== CHK */
	  {
		  //rv_errstrm << "is_array : " << is_array << " " <<  sym->name << " : add_scope_vartype() is pvar\n";
		  blk->bnode.pvars.push_back( sym->dup() );
	  }
	  else blk->bnode.vars.push_back( sym->dup() );
  }
}

void RVCollectBase::add_label_to_block( Symbol *sym )
{
  Statement* blk = NULL;
  if( lstack.size() > 0 )
    blk = *(lstack.end()-1); // last (closest) loop block
  else
    blk = body;

  if( !sym || !blk ) {
    fatal_error("RVCollectBase::add_label_to_block() got NULL !\n",false);
    return;
  }

if(DBG){ rv_errstrm<<"add_label_to_block(): \""<< sym->name;
 if(blk->bnode.loop_rec && blk->bnode.loop_rec->name)
   rv_errstrm<<"\" to block \""<< *blk->bnode.loop_rec->name; rv_errstrm<<"\" \n";}

  blk->bnode.labels.push_back( sym->dup() );
}

void RVCollectBase::set_array_ref_collector(RVCollectArrayRefs* arc)
{
  array_ref_collector = arc;
}

bool RVCollectBase::collect_array_ref(Expression* expr)
{
  if( !array_ref_collector )
    return true;

  return array_ref_collector->collect_array_ref(expr);
}

bool RVCollectBase::try_collect_non_offset_expr(Expression* expr)
  // Used to collect the non-offset base of an pointer with offset expression.
{
  if( !array_ref_collector )
    return true;

  // ignore offset expressions:
  if( expr->etype == ET_BinaryExpr && 
      ( ((BinaryExpr*)expr)->bOp == BO_Plus || 
	((BinaryExpr*)expr)->bOp == BO_Minus ) )
    return true;
  
  return array_ref_collector->collect_array_ref(expr);
}



  
/* RVCollect functions: */
/* ==================== */

RVCollect::RVCollect(bool part_equiv_check)
  : m_bPartEquivCheck(part_equiv_check)
{
  init();
}

void RVCollect::init()
{
  omega_deref_bound = 0;   
  left = right = false;
}

bool RVCollect::collect( FunctionDef *_body, Project *_parsetree, 
			 RVDirectives* _directs, int _side)
{
  body  = _body;
  side  = _side;
  parsetree = _parsetree;
  directs = _directs;
  symbol_already_collected = NULL;
  next_symbol_is_unused = false;

  RVCollectBase::start_func();

  // if we should collect array refs - save their parse-tree:
  if( array_ref_collector )
    rv_arrays().save_parsetree(parsetree, side);

if(DBG) rv_errstrm <<"RVCollect collects info in function: "<<where<<" (side "<<side<<")\n";

  if( !init_argtypes( body ) )
    return false;

if(DBG) rv_errstrm <<"RVCollect after init_argtypes info in function: "<<where<<" (side "<<side<<")\n";

  if( !body->fnode.has_body() ) {
    bool ret = collect_bodyless();
    if(DBG) {
         rv_errstrm <<"RVCollect calling collect_bodyless : "<<where<<" (side "<<side<<")\n";
         unsigned kkk;
         for (kkk=0;kkk < body->fnode.nArgs;kkk++)
             rv_errstrm << "argtype (side : " << side << ") (ind : " << kkk << ") " << (unsigned int) body->fnode.get_argtype(kkk) << "\n";
    }
    return ret;
  } else {
    bool ret = RVWalk::process( body );
    if(DBG) {
        rv_errstrm <<"RVCollect calling RVWalk:process : "<<where<<" (side "<<side<<")\n";
         unsigned kkk;
         for (kkk=0;kkk < body->fnode.nArgs;kkk++)
             rv_errstrm << "argtype (side : " << side << ") (ind : " << kkk << ") " << (unsigned int) body->fnode.get_argtype(kkk) << "\n";
    }

    if( omega_deref_bound < body -> fnode.num_derefs_in_body_read ) { // ofer: added 'read'
		omega_deref_bound = body->fnode.num_derefs_in_body_read;
if(DBG) { rv_errstrm << "Info: omega_deref_bound = "<< omega_deref_bound <<
    " for \""<< body->FunctionName() <<"\" (side "<<side<<")\n"; }
    }
    return ret;
  }
}


bool RVCollect::init_argtypes( FunctionDef *func )
{
  CHK_NULL1(func, "func in RVCollect::init_argtypes()"); 
  bool ret = true;
  FunctionType* proto = static_cast<FunctionType *>(func->decl->form);

  if( !func->fnode.hasAnyArgTypes() ) { // don't init twice.
    Type* lasttp = RVIndirectFuncs::fix_func_proto(proto);
    int nArgs = proto->nArgs;

    if( lasttp && is_basetype(lasttp,BT_Ellipsis) ) {  // mark ellipsis arg
      func->fnode.has_ellipsis_args = true;
      nArgs--; // the last one doesn't count.
      if( func->fnode.has_body() ) {
	    fatal_error("RVCollect::init_argtypes(): functions with ellipsis arguments are supported only bodyless", false);
	    func->print(rv_errstrm, 0); rv_errstrm <<" (side "<< side <<")\n";
      }
    }

    func->fnode.reinit_argtypes( nArgs );
  }

  return ret;
}


bool RVCollect::collect_bodyless()
{
  /* For safety we assume that all pointer args are AT_Out|AT_In and all others are AT_In.
  // ofer: the exception is 'const' pointers, e.g. "const char *format" that is used in printf. In that case we only mark it as read/deref
     We assume bodyless funcs doesn't read/write to any globals.
     What about AT_Array ? Should we assume it too for pointers ?  <<==== 
   */
  
  FunctionType* proto = (FunctionType*)body->decl->form;
  for(int i = 0; i < proto->nArgs; i++) {
    Type *argType = real_type(proto->args[i]->form, where); //Dima, Rev# 264
    if( is_pointer(argType, where) )
	{
		PtrType *pt = static_cast<PtrType*>(argType); 
		BaseType *bt = static_cast<BaseType*>(pt->subType);
		if (bt->qualifier == TQ_Const)  // ofer
			add_argtype(i, AT_In|AT_Deref);
		else add_argtype(i, AT_In|AT_Out|AT_Deref);
	}
    else if (!is_basetype(argType,BT_Void)) //Dima, Rev# 141
      add_argtype(i, AT_In);
  }
  return true;
}


bool RVCollect::process(Statement* s0p)
{
  LabelVector::const_iterator i;

  CHK_NULL("RVCollect::process(Statement*)");

  /* check whether there is a check point on this statement: */
  FORVEC(i, s0p->labels) 
    if( (*i)->type == LT_Goto ) {
      add_label_to_block( (*i)->name );

	  if( directs->is_active() && directs->lookup_label(side, (*i)->name->name) )
	body->fnode.subtree_has_cps = true;
    }

  if( s0p->type == ST_GotoStemnt && lstack.size() > 0 ) {
    RVLoop* loop_rec = (*(lstack.end()-1))->bnode.loop_rec;
    
    /* collect the labels to where the loop may goto: */
    if( loop_rec )
      loop_rec->used_labels.push_back( ((GotoStemnt*)s0p)->dest->dup() );
  }

  return RVCollectBase::process( s0p );
}


bool RVCollect::process(Expression* s0p)
{
  Variable* var = NULL;
  Symbol*   sym = NULL;
  bool is_deref   = false;
  bool is_array   = false;

  CHK_NULL("RVCollect::process(Expression*)");

  switch( s0p->etype ) 
  {
    case ET_Variable: {

      var = (Variable*)s0p;
      sym = var->name;
      if( !sym ) {
	var->location.printLocation(rv_errstrm); rv_errstrm << ": NULL variable symbol.\n";
	fatal_error("NULL symbol in variable in: ", where,false);
      }
      
      /* We assume all vars are read except those on left side of AO_Equal: */
      collect_symbol(sym, true, false);
      return true; /* finished with this expr. */
    }

    case ET_FunctionCall: { 
      FunctionCall* call = (FunctionCall*)s0p;
      Expression* func = call->function;
      if( func && func->etype == ET_Variable && valid_function(((Variable*)func)->name) )
		add_callees( ((Variable*)func)->name, call->args.size() );
      else
	/* if indirect call expr - process it as any usage expr: */
	if( !process(func) )
	  return false;
      
      /* For each call arg: */
      ExprVector::const_iterator  i;
      FORVEC(i,call->args) {

	/* If it's a variable passed direcly to callee by value or reference:
	     don't add any ArgType to this var
  	     - RVPropArgTypes will add its ArgType according to callee: */
	if( (*i)->etype == ET_Variable ||
	    ( (*i)->etype == ET_UnaryExpr && ((UnaryExpr*)(*i))->uOp == UO_AddrOf ) )
	  next_symbol_is_unused = true;
	
	/* otherwise just process it. <<=== MUST FIX THIS */
	if( !process(*i) )
	  return false;
      }

      return true;
    }    

    case ET_UnaryExpr: { /* special collect only in case of UO_Deref */
      RETYPE( UnaryExpr );
      switch( s0p->uOp ) 
      {
	case UO_Deref:
	  if( !process_deref(s0p->operand(), true, false) ) /* we assume read. */
	    return false;
	  break;

        case UO_PreInc:         // ++x
        case UO_PreDec:         // --x
        case UO_PostInc:        // x++
        case UO_PostDec: {      // x--
	  if( !collect_array_ref(s0p->operand()) )
	    return false;

	  sym = get_assigned_symbol( s0p->operand(), &is_deref, &is_array );

	  if( sym ) {
	    collect_symbol(sym, true, true, is_deref, is_array);
	    return true; /* we have finished with this var */
	  }
	  break;
        }

        default:;
      }
      break;
    }

    case ET_IndexExpr: {   // x[y]...[]
      RETYPE( IndexExpr );
      if( !collect_array_ref(s0p->array) )
	return false;
      if( !process_deref(s0p->array, true, false, true) ) /* we assume read. */
	return false;
      break;
    }

    default:;
  }

  return go(s0p);
}

bool RVCollect::process(Decl* s0p)
{
  CHK_NULL("RVCollectBase::process()");

  /* we are only interested in local var initializers: */
  if( !is_global_var( s0p->name ) ) {
    TRY_REP_PROC( initializer );
    if (s0p->initializer != NULL)
        mark_aliased(s0p->name, NULL, s0p->initializer, false);
  }

  return true;
}

void RVCollect::mark_aliased(Symbol* sym, Expression *leftExpr, Expression *rightExpr, bool pointer_deref) {
	static const char *where_ = "RVCollect::mark_aliased";
	int  ind = -1;

	if(!(sym && body && body->decl && body->decl->form && body->decl->form->isFunction()))
		fatal_error(std::string(where_).append(": received wrong symbol, or body is not a function").data(), false);

	if (!RVCtool::is_pointer(sym->entry->uVarDecl->form, where_)) return;
	Type *rightType = rightExpr->type;
	if (RVCtool::is_basetype(rightType) || rightType->type == TT_BitField) return;
	//Yet the two filters above are not complete, for instance: (void*)0x8A = (void*)0x76;

	//Check that the destination is a flat variable (no derefs, etc.):
	if (leftExpr != NULL)
		sym = try_var2symbol( leftExpr );
	Symbol* sym_right = try_var2symbol( rightExpr );
	if (sym && sym_right) { // we now maintain only the simplest case of p = q, where both p and q are pointers
		assert(sym_right->entry->uVarDecl->form->isPointer() || sym_right->entry->uVarDecl->form->isArray());
		ind = get_general_arg_index( (FunctionType*)body->decl->form, sym_right );

		// It may be it is not a parameter, but the right hand side was already
		// put to a parameter.
		//

		if (ind == -1) {
			unsigned int the_ind;
			FunctionDef *func = (FunctionDef *) body;
			SymbolVector::const_iterator i;

			if (func->fnode.is_aliased(func,sym_right,&the_ind,-1)) {
				int tmp_ind = the_ind;
				ind = (int) the_ind;
				// If it is already there no need to put it there again.
				FORVEC_IN(j, func->fnode.eq_classes[ind])
				if( func->fnode.eq_classes[ind][j]->entry == sym->entry ) tmp_ind = -1;

				ind = tmp_ind;
			}
		}
	}
	else 
		body->fnode.m_bAllAliased = true; //we encountered a case when pointer aliasing cannot be easily checked - assume every pointer is aliased to every pointer

	if (ind != -1) {            
		body->fnode.eq_classes[ind].push_back(sym);		  
	}    
}


bool RVCollect::process_binary(BinaryExpr* it)
{
  Symbol* sym = NULL;
  
  bool pointer_deref = false;
  bool is_array     = false;
  bool is_written   = false;
  bool is_read      = false;  

  CHK_NULL1(it, "RVCollect::process_binary()");

  switch( it->bOp ) 
  {
    case BO_Assign: {
      AssignExpr *ass = (AssignExpr*)it;
      sym = get_assigned_symbol( ass->leftExpr(), &pointer_deref, &is_array );
	  
      mark_aliased(sym, ass->leftExpr(), ass->rightExpr(), pointer_deref);

      if( !sym ) break;

      is_written = true;
      
      if( ass->aOp != AO_Equal )
	      is_read = true; /* only direct assign doesn't depend on prev value. */ 

      // if we have a case of indexing - collect the pointer as array ref. 
      if( ass->aOp == AO_PlusEql || ass->aOp == AO_MinusEql )
	     if( !collect_array_ref(ass->leftExpr()) ) return false;

      collect_symbol( sym, is_read, is_written, pointer_deref, is_array );
     
      /* don't collect this symbol when you process the right side: */
      symbol_already_collected = sym;
	  left = true;
	  right = false;
      if( !process(ass->leftExpr()) ) return false;
      left = false;
	  right = true;
	  bool res = process( ass->rightExpr() );
	  right = false;
      return res;
    }

    case BO_Plus:        // +
    case BO_Minus:       // -
      // This may be an array offset expression. 
      // In such a case get_pointer_in_offset_expr() will collect the array ref.
      get_pointer_in_offset_expr(it);
      break;

	case BO_Mult: break;

    case BO_PtrMember: {  /* collect pointer dereferences: */
      /* collect it as read - written instances are done in process_binary() BO_Assign */
      if( !process_deref( it->leftExpr(), true, false ) )
	return false;

      return process( it->rightExpr() );
    }

    default:;
  }

  return go_binary(it);
}


bool RVCollect::process_deref(Expression* it, bool is_read, bool is_written, bool is_array)
{
  Symbol* sym = try_var2symbol( it );      
  if( sym ) { /* if direct var - just collect it: */
    collect_symbol( sym, is_read, is_written, true, is_array);
    symbol_already_collected = sym;
  }
  else { /* otherwise check whether we have deref of array item: */
    sym = get_pointer_in_offset_expr( it );
    if( sym )
      collect_symbol( sym, is_read, is_written, true, true );
  }

  /* count the numner of derefs in the function body: */
  if (right) 
	  body->fnode.num_derefs_in_body_read++;  
  if (left) 
	  body->fnode.num_derefs_in_body_write++;  

  return process(it);
}


Symbol* RVCollect::get_assigning_symbol(Expression* s0p)
{
  CHK_NULL("RVCollect::get_assigning_symbol()");

  switch( s0p->etype ) 
  {
    case ET_Variable:
      return try_var2symbol( s0p );
      
    case ET_UnaryExpr: {
      RETYPE( UnaryExpr );
      Symbol* sym = try_var2symbol( s0p->operand() );
      /* if simple var - we have only deref - no array use. */
      if(sym) return sym;
      return NULL;
    }

    /* need to add binary expression */
      
    case ET_CastExpr: {      // (type) x
      RETYPE(CastExpr);
      /* just ignore the cast in assignments (?) */
      return get_assigning_symbol( s0p->expr); 
    }

    default:
      return NULL;
  }
}

///<summary>
/// Used for marking variables as being written-to. Returns the assigned symbol.
/// Also updates pderef (is it a deref expression) and parray (is it a pointer to an array).
///</summary>
Symbol* RVCollect::get_assigned_symbol(Expression* s0p, bool* pderef, bool* parray)
{
  CHK_NULL("RVCollect::get_assigned_symbol()");

  switch( s0p->etype ) 
  {
    case ET_Variable:
      return try_var2symbol( s0p );
      
	case ET_UnaryExpr: {
		RETYPE( UnaryExpr );
		if( s0p->uOp == UO_Deref ) {
			Symbol* sym = try_var2symbol( s0p->operand() ); // retrieve symbol of the unary expression if it is at the root. 
			if( pderef )
				*pderef = true;
			if(sym)  /* if simple var - we have only deref - no array use. */
				return sym;
			if (s0p ->operand()->etype==ET_UnaryExpr) {
				UnaryExpr *u = (UnaryExpr*)s0p ->operand();
				if (u->uOp == UO_Deref) 
					return get_assigned_symbol(s0p->operand(), pderef, parray); // ofer: calling recursively with one less deref, in case of derf chain (e.g. **p)
			}			
            else if (s0p ->operand()->etype==ET_CastExpr)
                return get_assigned_symbol(s0p->operand(), pderef, parray);

			/* else we probably have an array here, e.g. *(a + 2) = ...: */
			if( parray )
				*parray = true;
			return get_pointer_in_offset_expr( s0p->operand() );
		}
		return NULL;
					   }
      
    case ET_BinaryExpr: {
      RETYPE( BinaryExpr );
      switch( s0p->bOp )
      {
        case BO_PtrMember:   // x->y
	  if( pderef )
	    *pderef = true;
        case BO_Member:      // x.y
	  /* recourse as the expression can be f.e. "(*in_poi).f1" */
	  return get_assigned_symbol( s0p->leftExpr(), pderef, parray); 

        case BO_Comma:       // x,y
	  return get_assigned_symbol( s0p->rightExpr(), pderef, parray); 
	
        default:
	  /* any other BinaryExpr can't be left side of assignment. */
	  return NULL; 			  
      }
      return NULL;
    }

    case ET_CastExpr: {      // (type) x
      RETYPE(CastExpr);
      /* just ignore the cast in assignments (?) */
      return get_assigned_symbol( s0p->expr, pderef, parray); 
    }

    case ET_IndexExpr:{     // x[y]...[]
      RETYPE(IndexExpr);
      if( !collect_array_ref(s0p->array) )
	return false;
      if( parray )
	*parray = true;
      if( pderef )
	*pderef = true;
      if (s0p->array->etype == ET_CastExpr)
          return get_assigned_symbol(s0p->array, pderef, parray);
      return get_pointer_in_offset_expr( s0p->array );
    }

    default:
      return NULL;
  }
}


///<summary>
/// updates fnode with the properties of the input symbol sym (e.g., if it is global, then updates
/// the lists fnode.read, fnode.written. If it is a param, then updates the attributes of the param
/// in a list maintained by fnode); In the end calls add_scope_vartype in order to propagate this information
/// into nesting loops.
///</summary>
void RVCollect::collect_symbol(Symbol* sym, bool is_read, bool is_written, 
			       bool is_deref, bool is_array)
{
  int ind = -1;

  if( !sym || !body ) {
    fatal_error("RVCollect::collect_symbol() received NULL !\n",false);
    return;
  }

  if( !sym->entry )
    return;

  if( symbol_already_collected == sym ) {
    /* we already collected it thru BO_Assign: */
    symbol_already_collected = NULL;
    return;
  }

  if( sym->entry->IsFctDecl() )
    rv_indirect_funcs.add_func(sym, side);

  /* If *unused* symbol - leave its ArgType untouched: 
       (but still add it to block vars!) */
  if( next_symbol_is_unused ) {      
    //is_read = is_written = is_deref = is_array = false;
    is_written = is_deref = is_array = false;
    next_symbol_is_unused = false;
    if(DBG) rv_errstrm << "Debug: symbol \""<< sym->name << "\" is next_symbol_is_unused\n"; 
  }

  bool is_global = is_global_var( sym->entry ) || is_static_var( sym->entry);
  bool is_param  = sym->entry->IsParamDecl();

  if(DBG) rv_errstrm << "Debug: symbol \""<< sym->name << "\" is " <<
	  (is_read ? "read, " :"") << (is_written ? "written, ":"") <<
	  (is_deref ? "deref, " :"") << (is_array ? "array, ":"") <<
	  (is_param ? "function param" :"") << (is_global ? "used global":"") << 
	  " variable.\n";
  
  Type* form = get_symbol_type(sym, where);
  bool  pointer = is_pointer(form, where);
  if (pointer) is_written = true; // here we overaproximate: we mark every pointer as written to. The only consequence of thisa overapproximation is run-time, since there will be redundant assertions (asserting that a read-only variable hasn't change).

  if( is_global ) {
    if( is_read || m_bPartEquivCheck )
	  add_read( sym ); //Submission #101 (see change_tags.txt)
    if( is_written )
      add_written( sym );
  } 
  else if( is_param ) {
    ArgType atype = 0;
    
  if( body && body->decl && body->decl->form && body->decl->form->isFunction() )
      ind = get_arg_index( (FunctionType*)body->decl->form, sym );

    if( ind < 0 ) {
      rv_errstrm <<"Error: unable to find the index of \""<< *sym <<
	"\" param in the prototype of function: "<< 
	(body && body->decl ? body->FunctionName()->name :"UNKNOWN") <<
	" in "<< where <<"\n";
      return;
    }

    if( is_read )
      atype |= AT_In;
    
    /* only pointer arguments (*p) can be marked AT_Out, AT_Deref and AT_Array */
    if( pointer ) 
    {
      /* can output thru param only by write to deref pointer. */
      if( is_written && is_deref ) 
	atype |= AT_Out;
      if( is_deref )
	atype |= AT_Deref;
      if( is_array )
	atype |= AT_Array;
    }

    if (atype != 0)
      add_argtype(ind, atype);
  } else {
      // not global and not is_param
      // Need to find out, if it is derefed, and aliased to a parameter
     if (is_deref && is_written) {
         FunctionDef   *func = NULL;
         unsigned int  the_ind;
         FunctionType* proto ;
         int           start_ind = -1;

         if( body && body->decl && body->decl->form && body->decl->form->isFunction() )
        	 func = (FunctionDef *) body;
         proto = (FunctionType*)func->decl->form; 

         while (func->fnode.is_aliased(func,sym,&the_ind,start_ind)) {
             // for debug left here
			 if (DBG) {
				 rv_errstrm << "sym->name is deref && is_written : " << sym->name 
					 << "the_ind : " << the_ind << "\n";
				 rv_errstrm << "name of arg " << proto->args[the_ind]->name->name << "\n";
			 }

             add_argtype(the_ind,AT_Out);
             start_ind = the_ind;
         }
     }
  }
  add_scope_vartype(sym, is_written);
}





/* RVPropArgTypes functions: */
/* ========================= */

RVPropArgTypes::RVPropArgTypes(RVArgTypesDfs* _dfs)
{
  argtype_for_next_var = 0;
  dfs = _dfs;
}

void RVPropArgTypes::set_params(Project *_parsetree, int _side)
{
  parsetree = _parsetree;
  side = _side;
}


void RVPropArgTypes::go_sons(FunctionDef* it)
{
  if( !it )
    fatal_error("RVPropArgTypes::go_sons() received NULL ",false);

  body = it;

  RVCollectBase::start_func();

  if( !RVWalk::process( it ) )
    rv_errstrm << "Warning: RVPropArgTypes::go_sons(): failed to process function: "<< where <<" \n";
}


bool RVPropArgTypes::ignore_function_call(FunctionCall* call)
{
  if( !call || !call->function || call->function->etype != ET_Variable )
    return false;
  
  Variable *var = (Variable*)call->function;
  if( !var->name )
    return false;

  std::string& name = var->name->name;
  
  if( RVParse::ignore_func(name) || RVParse::supplied_by_rvt(name) ) {
    return true;
  }

  return false;
}


bool RVPropArgTypes::process(Expression* s0p)
{
  Symbol* sym = NULL;
  FunctionDef*  func = NULL;
  FunctionCall* call = NULL;
  int ind;

  if(!s0p || !dfs)
    fatal_error("RVPropArgTypes::process(): s0p or dfs is NULL", false);

  /* when debugging need to add
  rv_errstrm << "\nRVPropArgTypes::process(Expression) type:" << nameOfExpressionType(s0p->etype) << "\n";
  s0p->print(rv_errstrm) ;
  rv_errstrm << "\nAFTER .... RVPropArgTypes::process(Expression)\n"; 
  */


  switch( s0p->etype ) 
  {
    case ET_Variable:
      if( argtype_for_next_var  ) {
	     sym = try_var2symbol( s0p );
	     if( sym ) add_symbol_argtype(argtype_for_next_var, sym);
	     argtype_for_next_var = 0;
      }
      break;

    case ET_FunctionCall: {    
      bool isFuncPtr = false;
      call = static_cast<FunctionCall*>(s0p);

      Type* ftp = real_type(call->function->type, where);

      if (!ftp || !ftp->isFunction()) {
    	  ftp = getFunctionFromFuncPtr(ftp);
    	  isFuncPtr = ftp != NULL;
      }
      
      sym = try_var2symbol(call->function);

      if( sym && parsetree ) {
	    SymEntry* entry = lookup_function(sym->name, parsetree);
	    func = (entry ? entry->u2FunctionDef : NULL);
      }

      /*
      rv_errstrm << "RVPropArgTypes:: " << "(side : " << side << " of "<< *func->FunctionName() << "\n  ";
      */

      if( ignore_function_call(call) ) break;

      if( !func ) {
    	  if (!isFuncPtr) {
    		  std::string err(__FUNCTION__);
    		  err += " can't get function \"";
    		  err += sym ? sym->name : "UNPRINTABLE";
    		  err += "\" body from its symbol. in call:\n";
    		  fatal_error(err.data(), false);
    	  }
      }
      else {
	      if( func->fnode.has_body() ) {
              //rv_errstrm << "dfsin into " << *func->FunctionName() << "\n";
	          dfs->go(func);
          }
	      if( func->fnode.subtree_has_cps && body )  /* propagate subtree_has_cp here */
	         body->fnode.subtree_has_cps = true;
          
      }

      ExprVector::const_iterator  i;

      for (ind = 0, i=call->args.begin(); i != call->args.end(); i++, ind++) {
	      /* copy-up ArgType of the arg */
	      if( func ) add_argtype_from_callee( (*i), func, ind);
	
	      /* must process into arg exprs - may be more calls in them: */
	      if( !process(*i) ) return false;
      }
      return true;
    }
      
    case ET_BinaryExpr: {
      RETYPE( BinaryExpr );

      
      if (s0p->rightExpr()->etype == ET_FunctionCall) {
          // YL this is a problem that was fixed 17.01.2010
          // when you have a function call inside the expression
          // you need to check the function.
          break;
      } else {
          if( s0p->bOp == BO_Assign && array_ref_collector )
	     array_ref_collector->collect_array_assign((AssignExpr*)s0p, true);
         return true; // check inside - the expr may contain function calls.
      }
    }

    default:;
  }

  return go(s0p);
}


void RVPropArgTypes::add_argtype_from_callee(Expression* s0p, FunctionDef* func, int ind)
{
  Symbol* sym = NULL;
  ArgType at = 0;
  RVArrayRef* actual_ref = NULL;
  RVArrayRef* formal_ref = NULL;
  FunctionType* proto;
  Decl* formal_decl;

if(DBG) {
  rv_errstrm << "RVPropArgTypes::add_argtype_from_callee() #"<< 
    ind <<"(side : " << side << " of "<< *func->FunctionName() <<", arg:\n  ";
  s0p->print(rv_errstrm); rv_errstrm<<"\n  at: ";
  s0p->location.printLocation(rv_errstrm); rv_errstrm << " \n";
}

  if( func->fnode.has_ellipsis_args && ind >= (int)func->fnode.nArgs ) {
    /* for ellipsis arguments decide argtype by actual argument type: */
    Type* argtp = s0p->type ? real_type(s0p->type, where) : NULL;
    if( argtp && (argtp->isPointer() || argtp->isArray()) )
      at = AT_In|AT_Out|AT_Deref;  // assume all posible AT_ for safety. (what about AT_Array ? <<===)
    else
      at = AT_In;
  }
  else {
    at = func->fnode.get_argtype(ind);

    if( array_ref_collector ) { 
      // we should collect array stuff:

      if( !func->decl || !func->decl->form || !func->decl->form->isFunction() )
	fatal_error("Unable to get callee function type: ", func->FunctionName()->name, false);
      
      proto = (FunctionType*)func->decl->form;
      formal_decl = proto->args[ind];
      
      actual_ref = rv_arrays().get_array_ref(s0p); 
      formal_ref = rv_arrays().get_array_ref(formal_decl->form);
      
      if (formal_ref && actual_ref) {
	RVTreeComp typecomp(false, true);

	// check whether the arrays are of the same type:
	if( !typecomp.eq_type(actual_ref->getArrayItemType(), formal_ref->getArrayItemType()) ) {
	  rv_errstrm << "Warning: different array item types of actual and formal arguments \n   "
	    "in call to: " << func->FunctionName() << ". Formal reference: ";
	  formal_ref->print(rv_errstrm); rv_errstrm << "\n  Actual reference: ";
	  actual_ref->print(rv_errstrm); rv_errstrm << "\n";
	}
      }
      else if(formal_ref)
	collect_array_ref(s0p);
      else if(actual_ref)
	array_ref_collector->collect_array_in_decl_type(formal_decl);

    } /* array_ref_collector */
  } /* non ellipsis arg */

  switch( s0p->etype ) 
  {
    case ET_Variable:
      sym = try_var2symbol(s0p);
      if( !sym ) 
	break;      

      add_symbol_argtype(at, sym); 
      break;

    case ET_UnaryExpr: {
      RETYPE( UnaryExpr );
      switch(s0p->uOp) {
	case UO_AddrOf:
	  /* mark first var in expression to set its argtype info: */
	  argtype_for_next_var = at;
	  break;

	case UO_Deref:
	  add_argtype_from_callee(s0p->operand(), func, ind);
	  break;

        default:;
      }
      break;
    }
	
    case ET_BinaryExpr: {
      RETYPE( BinaryExpr );
      switch( s0p->bOp )
      {
        case BO_Member:
        case BO_PtrMember:
	  add_argtype_from_callee(s0p->leftExpr(), func, ind); 
	  break;

        case BO_Plus:
        case BO_Minus:
	  sym = get_pointer_in_offset_expr( s0p );
	  if( !sym )
	    break;
	  /* copy ArgType to sym */
	  add_symbol_argtype(at, sym);
	  break;

        default:;
      }
      break;
    }

    default:;
  }
}


void RVPropArgTypes::add_symbol_argtype(ArgType at, Symbol* sym)
{
  int  ind = -1;
  bool is_written = ((at & AT_Out) != 0);

  if( !sym->entry )
    return;

  bool is_param = sym->entry->IsParamDecl();

if(DBG) { 
  rv_errstrm << "Debug: symbol \""<< sym->name << "\" is "
	     << (at&AT_In ? "read, " :" ") << (at&AT_Out ? "written, ":" ")
	     << (at&AT_Deref ? "deref, " :" ") << (at&AT_Array ? "array, ":" ")
	     << (is_param ? "func param" :"var") <<" (by propagation).\n";
}

  if( is_global_var( sym->entry ) || is_static_var( sym->entry) ) {
    if( at & AT_In )
      add_read( sym );
    if( at & AT_Out )
      add_written( sym );
  } 
  else if( is_param ) {

    /* get index in the *caller* prototype: */
    if( body && body->decl && body->decl->form && body->decl->form->isFunction() )
      ind = get_arg_index( (FunctionType*)body->decl->form, sym );

    /* can output/deref/array param only if it is pointer: */
    if( !is_pointer( get_symbol_type(sym, where), where) )
      add_argtype(ind, (at & AT_In));
    else
      add_argtype(ind, at);
  }

  add_scope_vartype(sym, is_written);
}
