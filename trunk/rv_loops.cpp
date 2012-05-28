#include <sstream>
#include <ctool/stemnt.h>
#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_ctool.h> 
#include <rv_loops.h>
#include <rv_temps.h>
#include <rv_replace.h>
#include <rv_traversal.h>
#include "rv_dataflow.h"
#include "rv_etc.h"
#include "rv_glob.h"

#define RV_SECTION RV_SEC_LOOPS



/*  RVLoop code: */
/* ============= */

RVLoop::RVLoop(Statement* _block, FunctionDef *_orig_func, RVLoop* _parent)
{
if(DBG){rv_errstrm<<"RVLoop::"<<__FUNCTION__<<"\n";/*FDEL*/}
  block = _block;
  orig_func = _orig_func;
  parent = _parent;

  name = NULL;
  proto = NULL;
  proto_scope = NULL; 
  retarg = NULL;
  new_loop_code = NULL;
  nested_count = 0;

  has_break = has_continue = false;
}

RVLoop::~RVLoop()
{
  if( name ) delete name;
  if( retarg ) delete retarg;
  used_labels.delete_all();
  // if( new_loop_code ) delete new_loop_code;  <<=== OPEN ??
  /* proto is deleted with the parsetree */
  if( proto_scope ) delete proto_scope;
}


int RVLoop::inc_nested_count()
{ 
  return ++nested_count;
}

std::string RVLoop::ref_argname(std::string& name)
{
  std::string ret(LOOP_REF_PREFIX);
  return ret + name;
}
  

SymEntry* RVLoop::add_proto_arg(Symbol* base, bool pointer, Type* type)
{
if(DBG){rv_errstrm<<"RVLoop::"<<__FUNCTION__<<"\n";/*FDEL*/}
  std::string argname;
  Symbol *org_sym;

  if( !base || !proto || !proto_scope )
	fatal_error("RVLoop::add_proto_arg(): base, proto or proto_scope is NULL.\n",false);

  /* gen argname */

  if( pointer ) {
	int arr_sz;

	argname = ref_argname(base->name);

	// YL for arrays depends of type of analysis
	if (RVGlob::getArrHooks().find_sym(base , &arr_sz, &org_sym, rv_loops.the_side) != -1) {
		rv_errstrm << base->name << "RVLoop::add_proto_arg() is array\n";
		Type *new_type = type->isPointer()? static_cast<PtrType*>(type)->subType
				                          : NULL;
		ArrayType* ptr = new ArrayType((Expression *) 0);
		ptr->subType = new_type;
		type = ptr;
	}  else {
	 // end YL
		/* gen type PtrType with subType ... */;
		PtrType* ptr = new PtrType();
		ptr->subType = type;
		type = ptr;
	}
	// end for arrays
  } 
  else
	argname = base->name;

  /* gen Symbol */
  Symbol* sym = new Symbol();
  sym->name = argname;

  /* gen Decl: */
  Decl* decl = new Decl(type);
  decl->name = sym;

  //
  // Bug fix, when the decleration of the type is static, 
  // and you pull it out, the word "static" can not appear
  // inside the function definition
  //

  if (decl->storage == ST_Static) {
	  decl->storage = ST_None;
  }


  
  SymEntry* entry = mk_paramdecl(argname, decl);
  sym->entry = entry;
  
   /* add entry to proto_scope */
  proto_scope->Insert(entry);
  proto->addArg(decl);

  return entry;
}


static std::string add_num(std::string name, int i)
{
  std::ostringstream ret;
  ret << name << i;
  return ret.str();
}


Symbol* RVLoop::create_name(std::string parent_name, int cnt)
{
if(DBG){rv_errstrm<<"RVLoop::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( name )
	return name;

  /* decide its name - add "rvlp_" to the func name (once): */
  std::string lname = std::string(parent ? "" :LOOP_PREFIX) + parent_name;
  switch( block->type ) {
	case ST_WhileStemnt:   lname = add_num(lname+"_while", cnt); break;
	case ST_ForStemnt:     lname = add_num(lname+"_for", cnt); break;
	case ST_DoWhileStemnt: lname = add_num(lname+"_do_while", cnt); break;
	default:
	  rv_errstrm <<"RVLoop::create_name(): bad LoopType "<< block->type <<" at: ";
	  block->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
	  fatal_error("\n",false);
  }
  
  /* gen its symbol: */
  name = new Symbol();
  name->name = lname;

  return name;
}


bool RVLoop::is_loop_name(const std::string& name, const RVSide& side)
{
  std::string header(LOOP_PREFIX);
  if( name.compare(0, header.size(), header) == 0 )
	return true;

  if( side.isIllegalIndex() )
	return false;

  std::string with_pref = side.get_side_prefix() + header;
  if( name.compare(0, with_pref.size(), with_pref) == 0 )
	return true;

  with_pref = side.get_semchk_prefix() + header;
  if( name.compare(0, with_pref.size(), with_pref) == 0 )
	return true;

  /* MAYBE check also tail <<=== */

  return false;
}


FunctionType* RVLoop::create_proto(ScopeTbl* file_scope, int side)
{
if(DBG){rv_errstrm<<"RVLoop::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( proto )
	return proto;

  proto = new FunctionType();
  proto_scope = new ScopeTbl();  // MAYBE use create_last_scope()  <<=== 
  proto_scope->level = FUNCTION_SCOPE;

  /* make func_sym entry and add to file_scope (?) <<=== DECIDE */

  block->bnode.sort_vectors();

  filterOutInterimPvars(side);

  if(DBG) {
	  rv_errstrm << "Loop " << name->name << ":\n";
	  block->bnode.print_vectors(rv_errstrm, true);
  }

  /* for each bnode.vars */
  SymbolVector::const_iterator j;
  FORVEC(j, block->bnode.vars)
	add_proto_arg(*j, false, get_symbol_type(*j, "RVLoop::create_proto()"));

  FORVEC(j, block->bnode.pvars)
	add_proto_arg(*j, true, get_symbol_type(*j, "RVLoop::create_proto()"));

  /* gen "pretval" with type from orig_body: */
  Type* ftype = orig_func->decl->form;

  if( !ftype->isFunction() || !((FunctionType*)ftype)->subType ) {
	rv_errstrm << "RVLoop::create_proto(): can't get type of orig_func: "
		   << *orig_func->FunctionName() << " \n";
	proto = NULL;
	return NULL;
  }

  /* add retvar to the proto (if doesn't return void) */

  if( !is_basetype( ((FunctionType*)ftype)->subType, BT_Void) ) {
	retarg = mk_symbol(LOOP_RETVAR, NULL);

	retarg->entry = add_proto_arg(retarg, true, ((FunctionType*)ftype)->subType);
	retarg->name = retarg->entry->name; // "p_" may have been added
  }
  else
	retarg = NULL; // no return value.

  proto->subType = new BaseType(BT_Char | BT_UnSigned);

  return proto;
}


Symbol* RVLoop::dup_caller_symbol(RVLoop *caller, Symbol* orig, bool& is_ref)
{
  if( !orig || !orig->entry || !orig->entry->scope )
	fatal_error("RVLoop::dup_caller_symbol() got bad orig Symbol.",false);

  /* if there is no caller - take the symbol as is: */
  if( !caller ) {
	is_ref = false;
	return orig->dup0();
  }

  int orig_level = orig->entry->scope->level;

  if( !caller->block || !caller->name || !caller->proto || !caller->proto_scope )
	fatal_error("RVLoop::dup_caller_symbol() got bad caller loop record.",false);

  SymEntry* se  = NULL;
  Symbol*   ret = NULL;
  std::string p_name = ref_argname(orig->name);
  Symbol* caller_p_arg = caller->block->bnode.pvars.find(orig->name);
  if( !caller_p_arg || !caller_p_arg->entry || !caller_p_arg->entry->scope ||
	  caller_p_arg->entry->scope->level != orig_level )
	caller_p_arg = NULL;
	
  Symbol* caller_arg   = caller->block->bnode.vars.find(orig->name);
  if( !caller_arg || !caller_arg->entry || !caller_arg->entry->scope ||
	  caller_arg->entry->scope->level != orig_level )
	caller_arg = NULL;
  
  if( caller_p_arg && caller_arg ) {
	rv_errstrm << "Internal: "<< orig->name <<" is contained both - in vars and pvars"
		   << " of bnode of loop "<< caller->name->name <<" \n";
rv_errstrm << "Loop " << caller->name->name << ":\n";
caller->block->bnode.vars.print("input vars: " , rv_errstrm);
caller->block->bnode.pvars.print("ref vars: ", rv_errstrm);
  }

  if( caller_p_arg ) {
	se = caller->proto_scope->Lookup( p_name );
	if( se && se->uVarDecl )
	  ret = se->uVarDecl->name;
	is_ref = true;
  }
  else if( caller_arg ) {
	se = caller->proto_scope->Lookup( orig->name );
	if( se && se->uVarDecl )
	  ret = se->uVarDecl->name;
	is_ref = false;
  }

  if( !ret ) {  
	/* Look in caller's internal scopes: */
	if( caller->block->bnode.is_internal_scope( orig->entry->scope ) )
	  se = orig->entry;
	else
	  se = caller->block->bnode.lookup_internal_scopes( orig->name );
	if( se && se->uVarDecl )
	  ret = se->uVarDecl->name;
	is_ref = false;
  }
  
  if( !ret ) { /* orig should be a global var. <<=== */
	if( !is_global_var(orig->entry) ) {
	  rv_errstrm << "Internal: "<< orig->name <<"(needed by \""<< name->name <<"\")"
	" is not a global symbol,\n  but is not defined in caller's (\""<<
	caller->name->name <<"\") prototype arguments or internal scope !\n  at: ";
	  block->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
	}
	ret = orig;
	is_ref = false;
  }

  if( !ret ) {
	rv_errstrm << "Internal: RVLoop::dup_caller_symbol(): can't find symbol "
		   << orig->name <<" (needed by \""<< name->name <<"\") in caller's (\""
		   << caller->name->name <<"\") or global scopes !\n  at: ";
	block->location.printLocation( rv_errstrm ); rv_errstrm << " \n";    
	fatal_error("Can't find loop argument: ",orig->name, false);
  }
  
  return ret->dup0();
}


void RVLoop::add_call_args(FunctionCall* call, RVLoop* from_loop, Location& l)
{
  bool      is_ref;
  Symbol*   arg_sym;
  Variable* var;
  SymbolVector::const_iterator j;

  FORVEC(j, block->bnode.vars) {
	arg_sym = dup_caller_symbol(from_loop, (*j), is_ref);
	if( is_ref )  /* must deref it: */
	  call->addArg(mk_deref(arg_sym, l));
	else {
	  var = new Variable(arg_sym, l);
	  call->addArg(var);
	}
  }

  FORVEC(j, block->bnode.pvars) {
	arg_sym = dup_caller_symbol(from_loop, (*j), is_ref);	
		if( !is_ref )  /* must take address */
	  call->addArg(mk_addrof(arg_sym, l));
	else {
	  var = new Variable(arg_sym, l);
	  call->addArg(var);
	}
  }
}


Block* RVLoop::gen_loop_call_switch_body(RVLoop* from_loop, Location& l)
{
  unsigned ind = 0;
  Statement* st = NULL;
  
  Block* blk = new Block(l);

  Statement* from_blk = NULL;
  if( from_loop && from_loop->block )
	from_blk = from_loop->block;
  else
	from_blk = orig_func;

  SymbolVector& dest_labels = from_blk->bnode.labels;

  SymbolVector::const_iterator i;
  FORVEC(i, used_labels) 
  {
	ind = RVFuncNode::get_label_index(orig_func, (*i));
	if( ind == 0 ) {
	  rv_errstrm<<"Warning: bad label index "<< ind <<" of label \""<< *(*i) <<
	"\" in function \""<< *orig_func->FunctionName() <<"\"\n";
	  continue;
	}

	/* for labels in the caller block gen: "case <ind>: goto <(*i)>;" */
	if( dest_labels.find( (*i)->name ) ) // the dest is in the caller block
	  st = new GotoStemnt((*i)->dup(), l);
	else {
	  if( !from_loop )
	rv_errstrm << "Internal: unable to find label \""<< *(*i) <<
	  "\" location in function \""<< *orig_func->FunctionName() <<"\" !\n"
	  "  The label is probably a terget of a jump into a loop body "
	  "from outside it.\n  This behaviour is unsupported.\n";
	  continue;
	}
	  
	Label* case_lab = new Label(new UIntConstant(ind, false, l));

	st->addLabel(case_lab);

	blk->add(st);
  }
	
  return blk;
}


const char* RVLoop::LTC_VAR_NAME = "rv_ltc_val";


/// <summary>
/// Creates a call to the function that replaced the loop.  
// It creates the call to this function from the original caller function (e.g. f()).  
/// in that case it is a switch statement in case the loop contained a return statement. 
/// </summary>
Statement* RVLoop::create_call(Expression* init, Symbol* retsym, bool loop_has_return)
{
	if(DBG){rv_errstrm<<"RVLoop::"<<__FUNCTION__<<"\n";/*FDEL*/}

	Location& l = block->location;

	Block* blk = new Block(l);
	Expression* sw_val = NULL;

	FunctionCall* call = new FunctionCall(new Variable(name->dup0(), l), l);

	add_call_args(call, false, l);

	/* add retvar arg if needed: */
	if( retsym ) {
		/* pass "pretval" or "p_retval" to the call: */	
		call->addArg(mk_addrof(retsym->dup0(), l));
	} 	

	sw_val = call;

	/* gen init ";" before the loop call (but after decls of this block) */
	if( init )
		blk->add(new ExpressionStemnt(init, l));

	if (loop_has_return) {
		Block* sw_blk = gen_loop_call_switch_body(false, l);

		/* add "case LTC_RETURN: return <value-or-LTC_RETURN>;" if needed */
		Label* ltc_return_lab = new Label(new UIntConstant(LTC_RETURN, false, l));

		Expression* res = NULL;
		if( retsym ) res = new Variable(retsym->dup(), l);

		ReturnStemnt* ret = new ReturnStemnt(res, l);
		ret->addLabel(ltc_return_lab);
		sw_blk->add(ret); // ofer: this adds the 'case 123: return rvretval';

		Statement* default_st = NULL;

		if( default_st ) {
			default_st->addLabel(new Label(LT_Default));
			sw_blk->add(default_st);
		}

		/* for case of standard loop termination gen "case 0: break;" */
		Statement* brk_st = new Statement(ST_BreakStemnt, l);
		brk_st->addLabel(new Label(new UIntConstant(0, false, l)));
		sw_blk->add(brk_st);

		SwitchStemnt* sw_st = new SwitchStemnt(sw_val, sw_blk, l); 
		blk->add(sw_st); 
	}
	else blk-> add(new ExpressionStemnt(sw_val, l)); // ofer: just a function call in case the loop did not include a return statement.

	return blk;
}





/// <summary>
/// Creates a call to the function that replaced the loop. This function is called from multiple places. 
/// The generated call will be from a loop: it can be a recursive call, or a call from a nesting loop.
/// in that case it is a switch statement in case the loop contained a return statement. 
/// </summary>
Statement* RVLoop::create_call_from_loop(Expression* init, RVLoop* from_loop, Symbol* retsym, bool loop_has_return)
{
if(DBG){rv_errstrm<<"RVLoop::"<<__FUNCTION__<<"\n";/*FDEL*/}

assert(from_loop);  
Location& l = block->location;

  Block* blk = new Block(l);
  Expression* sw_val = NULL;
  Symbol* ltc_sym = NULL;

  FunctionCall* call = new FunctionCall(new Variable(name->dup0(), l), l);
  
  add_call_args(call, from_loop, l);

  /* add retvar arg if needed: */
  if( retsym ) {
	  /* pass "pretval" or "p_retval" to the call: */	
	  /* its "p_retval" which is a reference already: */
	  Variable* var = new Variable(retsym->dup0(), l);
	  call->addArg(var);
  }

  bool recursive_call = (from_loop == this); // this means that we were called to create the recursive call. 

  if( recursive_call ) {
	/* gen init ";" before the loop call */
	if( init )
	  blk->add(new ExpressionStemnt(init, l));

	/* gen "return loop_call(args);" */
	ReturnStemnt* ret = new ReturnStemnt(call, l);
	blk->add(ret);
  }
  else { /* inside other loop  */	
	  /* save the LTC result of the call in rv_ltc_val */ 
	  Decl* ltc_decl = new Decl(proto->subType);
	  ltc_sym = mk_symbol(LTC_VAR_NAME, mk_vardecl(LTC_VAR_NAME, ltc_decl));
	  ltc_decl->name = ltc_sym;
	  DeclStemnt* ltc_decl_st = new DeclStemnt(l);
	  ltc_decl_st->addDecl(ltc_decl);
	  blk->add(ltc_decl_st);

	  Variable* ltc_var = new Variable(ltc_sym->dup(), l);
	  sw_val = new AssignExpr(AO_Equal, ltc_var, call, l);
	
	

	/* gen init ";" before the loop call (but after decls of this block) */
	if( init )
	  blk->add(new ExpressionStemnt(init, l));

	if (loop_has_return) {
		Block* sw_blk = gen_loop_call_switch_body(from_loop, l);

		/* add "case LTC_RETURN: return <value-or-LTC_RETURN>;" if needed */
		Label* ltc_return_lab = new Label(new UIntConstant(LTC_RETURN, false, l));

		Expression* res = NULL;
		res = new UIntConstant(LTC_RETURN, false, l);
	
		ReturnStemnt* ret = new ReturnStemnt(res, l);
		ret->addLabel(ltc_return_lab);
		sw_blk->add(ret); // ofer: this adds the 'case 123: return rvretval';

		Statement* default_st = NULL;

		/* in loop: just return unrecognized LTC codes: */
		default_st = new ReturnStemnt(new Variable(ltc_sym->dup(), l), l);
	

		if( default_st ) {
			default_st->addLabel(new Label(LT_Default));
			sw_blk->add(default_st);
		}

		/* for case of standard loop termination gen "case 0: break;" */
		Statement* brk_st = new Statement(ST_BreakStemnt, l);
		brk_st->addLabel(new Label(new UIntConstant(0, false, l)));
		sw_blk->add(brk_st);

		SwitchStemnt* sw_st = new SwitchStemnt(sw_val, sw_blk, l); 
		blk->add(sw_st); 
	}
	else blk-> add(new ExpressionStemnt(sw_val, l)); // ofer: just a function call in case the loop did not include a return statement.
	
  }

  return blk;
}



void RVLoop::replace_vars_by_pointers()
/* replace outvars in the loop code to pointer formal arguments,
   also replace "continue" and "break" by gotos: */
{
  RVReplaceInLoops rv_replace_in_loops;
  rv_replace_in_loops.replace(this);
  new_loop_code = rv_replace_in_loops.get_res();
}


void RVLoop::print_proto(std::ostream& out)
{
if(DBG){rv_errstrm<<"RVLoop::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !proto )
	fatal_error("RVLoop::print_proto(): proto is NULL, loop: ",
		(name ? name->name.data() : "UNPRINTABLE"), false);
	
  proto->printType(out, name, true, 0);
}

Expression* RVLoop::get_cond()
{
  if( !block )
	fatal_error("RVLoop::get_cond(): block is NULL.\n",false);

  switch( block->type ) 
  {
	case ST_ForStemnt:     return ((ForStemnt*)block)->cond;
	case ST_WhileStemnt:   return ((WhileStemnt*)block)->cond;
	case ST_DoWhileStemnt: return ((DoWhileStemnt*)block)->cond;
	default:
	  rv_errstrm << "RVLoop::get_cond(): bad loop statement type "<< block->type <<" at: ";
	  block->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
	  fatal_error("\n",false);
	  return NULL; 
  }
}

Statement* RVLoop::get_body()
{
  if( !block )
	fatal_error("RVLoop::get_body(): block is NULL.\n",false);

  switch( block->type ) 
  {
	case ST_ForStemnt:     return ((ForStemnt*)block)->block;
	case ST_WhileStemnt:   return ((WhileStemnt*)block)->block;
	case ST_DoWhileStemnt: return ((DoWhileStemnt*)block)->block;
	default:
	  rv_errstrm << "RVLoop::get_body(): bad loop statement type "<< block->type <<" at: ";
	  block->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
	  fatal_error("\n",false);
	  return NULL; 
  }
}



/// <summary>
/// Creates the recursive function that replaces the loop. 
/// </summary>
bool RVLoop::gen_loop_func(RVTemp& temps)
{
if(DBG){rv_errstrm<<"RVLoop::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !block )
	fatal_error("RVLoop::gen_loop_func(): block is NULL.\n",false);

  Expression* cond = NULL;
  Expression* incr = NULL;
  Statement*  body = NULL;

  /* Put the proto: */
  print_proto(temps.get_strm());

  /* open func body block. */
  temps.print("\n{\n");

  /* Add local vardef statements (?) <<=== */
  declareInterimVars(temps);

  /* Replace subsequent loops by the right calls,
	 and replace var-names by pointers (for pvars): */
  replace_vars_by_pointers();
  if( !new_loop_code )
	fatal_error("RVLoop::gen_loop_func(): can't generate new_loop_code.\n",false);

  switch( new_loop_code->type ) {

	case ST_ForStemnt: {
	  ForStemnt* it = (ForStemnt*)new_loop_code;
	  /* init - stays in caller's scope. */ 
	  cond = it->cond;
	  incr = it->incr;
	  body = it->block;
	  break;
	}

	case ST_WhileStemnt: {
	  WhileStemnt* it = (WhileStemnt*)new_loop_code;
	  cond = it->cond;
	  body = it->block;
	  break;
	}

	case ST_DoWhileStemnt: {
	  DoWhileStemnt* it = (DoWhileStemnt*)new_loop_code;
	  cond = it->cond;
	  body = it->block;
	  break;
	}

	default:
	  fatal_error("RVLoop::gen_loop_func(): bad loop statement type", false);
  }

  /* check condition (for ST_ForStemnt/ST_WhileStemnt) with replaced var-names. */
  if( cond &&
	  ( block->type == ST_ForStemnt || 
		block->type == ST_WhileStemnt )) {
	temps.print("  if( !(");
	cond->print(temps.get_strm());
	temps.print(") )\n");
	temps.print(add_num("    return ",LTC_NORMAL)+";\n\n");
  }

  if( body )
	printBlock(temps.get_strm(),1,body);

  temps.print("\n");

  /* generate l_continue:, <INC> and l_break: */
  
  if( has_continue )
	temps.print(std::string(" ")+LOOP_CONTINUE+":;\n");
  
  switch( new_loop_code->type ) 
  {
	case ST_ForStemnt: {
	  if( incr ) {
	temps.print("  ");
	incr->print(temps.get_strm());
	temps.print(";\n");
	  }
	  break;
	}

	case ST_DoWhileStemnt:
	  if( cond ) {
	temps.print("  if( ");
	cond->print(temps.get_strm());
	temps.print(" )\n");
	  }
	  break;
	  
	default:; /* do nothing */
  }
  
  
#ifndef LOOPS_NOT_RECURSIVE  
  //ofer: creates the recursive call. The 'true' is ignored inside the function from this location. 
	  Statement* call_code = create_call_from_loop(NULL, this, retarg, true); 
	  call_code->print(temps.get_strm(),1);
#endif

  if( has_break )
	temps.print(std::string(" ") + LOOP_BREAK +":;\n");

  temps.print(add_num("  return ",LTC_NORMAL)+";\n}\n\n");

  return true;
}  

///<summary>
///Prints out the declarations of the variables which are used inside the
///loop only, and that's why they are extracted from the loop function
///argument list
///<seealso cref="RVLoop::filterOutInterimPvars()" />
///</summary>
void RVLoop::declareInterimVars(RVTemp& temps) const {
	if (interimVars.empty())
		return;

	SymbolVector::const_iterator it = interimVars.begin();
	for (; it != interimVars.end(); ++it) {
		/* gen Decl: */
		Decl decl(get_symbol_type(*it, "RVLoop::declareInterimVars()"));
		decl.name = (*it)->dup0();

		//Stream it out:
		temps.do_indent(1);
		decl.print(temps.get_strm(), true);
		temps.print("; /* was originally declared outside but is used inside the loop only */\n");
	}
}


class RVForLoopUninitializer {
	RVLocalBackup<Expression*> *backup;

public:
	RVForLoopUninitializer(Statement *block) : backup(NULL)
	{
	    if (block->type == ST_ForStemnt) {
	    	ForStemnt *forLoop = static_cast<ForStemnt*>(block);
	    	backup = new RVLocalBackup<Expression*>(forLoop->init, NULL);
	    }
	}

	void clean(void) {
		if (backup != NULL) {
            delete backup;
            backup = NULL;
        }
	}

    ~RVForLoopUninitializer() {
        clean();
    }
};


///<summary>
///Local variables that are used inside loops are part of the interface
///of the loop function, even if they are written-to before being read.
///The problem is that these variables are local and hence receive a
///nondet value and hence make the UF representing the loop to return
///different values. cil introduces such temp. variables, and it ruins
///proofs (see function 'simplify' in gcd.c).
///This method finds such variables and stores them in the field <i>interimVars</i>.
///</summary>
void RVLoop::filterOutInterimPvars(int side) {
  if (block->bnode.pvars.empty())
	  return;

  RVForLoopUninitializer svInit(block); //May temporarily zero block->init out
  RVUninitVarAnalysis uninitAnal(block);
  std::ostringstream loopName;
  if (name != NULL)
	  loopName << name->name << "_side" << side;
  uninitAnal.uniqueName(loopName.str());
  if (!uninitAnal.run())
	  return;

  RVLiveVarsAnalysis *pLiveVar = NULL;
  SymbolVector uninitVars, pvars, liveVars;
  uninitAnal.getUninitializedVars(uninitVars);
  svInit.clean();
  SymbolVector::const_iterator j;
  FORVEC(j, block->bnode.pvars) {
	  if (!uninitVars.find((*j)->name)) {
		  if (pLiveVar == NULL) {
			  pLiveVar = new RVLiveVarsAnalysis(orig_func);
			  pLiveVar->uniqueName(loopName.str()).run();
		  }
		  if (pLiveVar->getLiveVarsAtEndOfLoop(liveVars, block) &&
			  !liveVars.find((*j)->name))
		  {
			  interimVars.push_back(*j);
			  continue;
		  }
	  }

	  pvars.push_back(*j);
  }

  if (pLiveVar != NULL)
	  delete pLiveVar;

  if (pvars.size() != block->bnode.pvars.size())
	  block->bnode.pvars.swap(pvars);
}



/* RVLoops code: */
/* ============= */

RVLoops rv_loops;

RVLoops::~RVLoops()
{
  clear();
}

void RVLoops::clear()
{
  iterator i;
  FORVEC(i, THIS)
	if( (*i) != NULL ) {
	  delete (*i);
	  (*i) = NULL;
	}

  resize(0);
}


RVLoop* RVLoops::add_loop(Statement* block, FunctionDef *orig_func, RVLoop* parent)
{
if(DBG){rv_errstrm<<"RVLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  RVLoop* ret = new RVLoop(block, orig_func, parent);
  push_back(ret);
  block->bnode.loop_rec = ret;
  return ret;
}


bool RVLoops::print_protos(RVTemp& temps, FunctionDef* caller, ScopeTbl* file_scope)
{
if(DBG){rv_errstrm<<"RVLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !caller->fnode.has_loops() )
	return true;

  int from = caller->fnode.loops_index;
  
  if( from >= (int)size() ) {
	rv_errstrm << "RVLoops::print_protos(): bad loop index: "<< from <<" >= size()="
		   << size() << " \n";
	fatal_error("\n",false);
  }
  
  for(unsigned i = from; i < size() && THIS[i]->orig_func == caller; i++) {
	RVLoop* lp = THIS[i];
	if( !lp->name ) {
	  rv_errstrm << "RVLoops::print_protos(): NULL name of loop at ";
	  lp->block->location.printLocation( rv_errstrm ); rv_errstrm << " \n";
	  fatal_error("\n",false);
	}

	/* generate the prototype for the loop: */
	lp->create_proto(file_scope, the_side);
	lp->print_proto(temps.get_strm());
	temps.print(";\n\n");

if(DBG){ rv_errstrm<<"Loop \""<< *lp->name <<"\" ";
 lp->used_labels.print(" uses the labels: ", rv_errstrm); }

	lp->used_labels.unique_sort();

	/* collect all goto labels used in the function: */
	caller->fnode.used_labels.add_dup(lp->used_labels);
  }

  // LATER: make all_labels order coinside on both sides     <<=====
  caller->fnode.used_labels.unique_sort();

if(DBG){ rv_errstrm<<"Function \""<< *caller->FunctionName() <<"\" ";
 caller->fnode.used_labels.print(" uses the labels: ", rv_errstrm); }

  temps.print("\n");
  return true;
}

  

/// <summary>
/// Creates the functions corresponding to the loops that were originally called from "caller"
/// </summary>
/// <param name="temps">an RVTemp object, which stores the created functions</param>
/// <param name="caller">The function for which we create the callees</param>
bool RVLoops::gen_loop_funcs(RVTemp& temps, FunctionDef* caller)
{
if(DBG){rv_errstrm<<"RVLoops::"<<__FUNCTION__<<"\n";/*FDEL*/}
  if( !caller->fnode.has_loops() )
	return true;

  int from = caller->fnode.loops_index;
  
  if( from >= (int)size() ) {
	rv_errstrm << "RVLoops::gen_loop_funcs(): bad loop index: "<< from <<" >= size()="
		   << size() << " \n";
	fatal_error("\n",false);
  }
  
  bool ret = true;
  for(unsigned i = from; i < size() && THIS[i]->orig_func == caller; i++)
	ret = THIS[i]->gen_loop_func(temps) && ret;

  temps.print("\n");
  return ret;
}

