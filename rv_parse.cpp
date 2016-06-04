/* functions of classes: RVParse, RVRename, RVDirectives, HashTblIter  */ 

#ifdef __cplusplus
 #include <stdlib.h>
 #ifdef _MSC_VER // Dima
  #include<io.h> // ofer
 #else
  #include <unistd.h> // ofer
 #endif
 #include <string.h>
#endif  /* ! __cplusplus */

#ifdef __TURBOC__
 #pragma warn -rch
 #pragma warn -use
 #include <io.h>
 #include <stdlib.h>
#endif

#include <sstream>

#include <rv_parse.h>
#include <rv_consts.h>
#include <rv_macros.h>
#include <rv_temps.h>
#include <rv_funcpair.h>
#include <rv_loops.h>
#include <rv_error.h>
#include <rv_traversal.h>
#include <rv_etc.h>
#include <rv_commands.h>
#include "rv_propagate.h"
#include "rv_collect.h"
#include <ctool/express.h>
#include <ctool/lexer.h>
#include <ctool/decl.h>
#include <ctool/stemnt.h>

using namespace std;


#define RV_SECTION RV_SEC_PARSE


static void close_all_streams()
{
  rv_errstrm.close();
}



void fatal_error(const char msg[], bool parsing )
{
  fatal_error(msg, "", parsing);
}

void fatal_error(const char *msg, const std::string& more, bool parsing )
{
  if( parsing )
	yyerr(const_cast<char *>(msg), more);
  else
	rv_errstrm << "RVT fatal error: " << msg << more << "\n";

  close_all_streams();

   exit( 2 );         // 2 = YY_EXIT_FAILURE 
}
  
int yyparse();



/*  RVParse functions:  */
/* ==================== */

RVParse::RVParse()
{ 
  parsetree = NULL;
  in_body = false;
  in_tag_def = false;
  next_is_comp = false;
  ignore_undefined = false;
}

	
RVParse::~RVParse()
{ 
  if(parsetree != NULL) 
	delete_parsetree(parsetree);
}

bool RVParse::parse_path(const std::string& fpath, const std::string& description) {
  bool ret = true;

  std::ifstream file( fpath.data() );
  if( !file.is_open() ) {
	rv_errstrm << "Error: Unable to open "<< description <<" file: \""
		       << fpath << "\"\n";
	return false;
  }

  prvhooks = this; //Used while parsing

  ret = do_parse(&file, fpath);

  if( ret )
	ret = add_func_empty_bodies();

  file.close();

  return ret;
}

bool RVParse::do_parse(std::istream *_instream, const std::string& fname)
  /* returns true on success. */
{
  // parsing

	if (DBG) rv_errstrm << "... RVParse::do_parse() - start " << fname << "\n"; 

  if(parsetree != NULL)
	delete_parsetree(parsetree);

  parsetree=new Project;
  gProject = parsetree;

  if( ignore_undefined )
	gProject->warn_variable = false;

  parsetree->Parse_TOS =
	new ParseEnv(_instream, &rv_errstrm, fname);

  TransUnit *unit = parsetree->Parse_TOS->transUnit;
  if(unit == NULL)
	return false;
	 
  unit->contxt.EnterScope();

  parsetree->Parse_TOS->yylineno=1;
  parsetree->Parse_TOS->yyinstream = _instream;

  while(yyparse());

  bool error_happened = gProject->Parse_TOS->err_cnt != 0;

  unit->contxt.ExitScope();

  if(error_happened)
	{
	  delete unit;
	  return false;
	}

  parsetree->units.push_back(unit);

  if (DBG) rv_errstrm << "... RVParse::do_parse() - finished " << fname << " (succesfully)" << "\n"; 

  return true;
}


FunctionDef* RVParse::add_empty_body(SymEntry* se)
{
  FunctionDef* def = NULL;

  if( se && se->IsFctDecl() && !se->u2FunctionDef ) {
	const Location l(0,0,"External Function");
	def = new FunctionDef(l);
	def->decl = se->uVarDecl;
	def->fnode.external = true; 
	se->u2FunctionDef = def;
  }

  return def;
}

bool RVParse::add_func_empty_bodies(Project* pt)
{
  if( !pt ) 
	fatal_error("NULL parsetree in RVParse::add_func_empty_bodies()", false);

  ScopeTbl* scope = get_file_scope( pt );
  HashTblIter hit(scope->htab);
  SymEntry*    se;

  RVCollect wcol(true);
  FORIT(se,hit) {
	FunctionDef *def = add_empty_body(se);
	if (def != NULL)
	  wcol.init_argtypes(def);
  }
  return true;
}

bool RVParse::add_func_empty_bodies()
{ return add_func_empty_bodies(parsetree); }


bool RVParse::delete_func_empty_bodies(Project* parsetree)
{
  if( !parsetree ) 
	fatal_error("NULL parsetree in RVParse::delete_func_empty_bodies()", false);

  ScopeTbl* scope = get_file_scope( parsetree );
  HashTblIter hit(scope->htab);
  SymEntry*    se;
  
  FORIT(se,hit)
	if( se->IsFctDecl() && se->u2FunctionDef && 
	se->u2FunctionDef->fnode.external ) {
	  se->u2FunctionDef->decl = NULL;     // deleted from DeclStemnt
	  delete se->u2FunctionDef;
	  se->u2FunctionDef = NULL;
	}

  return true;
}

bool RVParse::delete_parsetree(Project* parsetree)
{
  if( !parsetree )
	return true;

  if( !delete_func_empty_bodies(parsetree) )
	return false;

  delete parsetree;

  return true;
}


Project *RVParse::take_parsetree()
{
  Project *ret = parsetree;
  parsetree = NULL;
  return ret;
}


SymEntry* RVParse::lookup_global_var(const std::string& name )
{ return RVCtool::lookup_global_var( name, parsetree ); }


SymEntry* RVParse::lookup_function(const std::string& name )
{ return RVCtool::lookup_function(name, parsetree); }


SymEntry* RVParse::lookup_symbol_in_current_contxt(std::string& name)
{
  if( !parsetree || !parsetree->Parse_TOS || !parsetree->Parse_TOS->transUnit )
	fatal_error((char *) "lookup_symbol_in_current_contxt() got NULL on path to current TransUnit.\n");
  
  Context* ctx = &parsetree->Parse_TOS->transUnit->contxt;
  if( !ctx->syms )
	fatal_error((char *) "lookup_symbol_in_current_contxt() no syms table in current Context.\n");
  
  SymEntry* se = ctx->syms->Lookup( name );
  if( se )
	return se;

  /* try to find it in tags too: */
  if( !ctx->tags )
	fatal_error((char *) "lookup_symbol_in_current_contxt() no tags table in current Context.\n");

  return ctx->tags->Lookup( name );
}


SymEntry* RVParse::lookup_symbol_in_global_contxt(std::string& name)
{
  if( !parsetree || !parsetree->Parse_TOS || !parsetree->Parse_TOS->transUnit )
	fatal_error((char *) "lookup_symbol_in_global_contxt() got NULL on path to current TransUnit.\n");
  
  ScopeTbl* scope = get_file_scope( parsetree );
  if( scope ) {
	SymEntry* se = scope->Find( name );
	if( se )
	  return se;
  }

  scope = get_file_tags( parsetree );
  if( !scope )
	return NULL;

  return scope->Find( name );
}


bool RVParse::ignore_func(const std::string& fname)
{
  static std::string rvact0(SIDE0.get_rvact_name());
  static std::string rvact1(SIDE1.get_rvact_name());

  return( fname == "__CPROVER_assume" || 
	      fname == "assert" || RvTraversal::is_alloc(fname) ||
	      fname == rvact0   || fname == rvact1 );
  
  /* note that assume() is not considered any more as special function 
	 by CBMC */
}


bool RVParse::supplied_by_rvt(const std::string& fname)
{
  return( fname == "rv_getint" ||  fname == "rv_getchar" );
}




/*  RVGlobLists functions:  */
/* ======================== */

RVGlobLists  rv_parser;

RVGlobLists::RVGlobLists()
  : RVParse()
{
  current_side = -1;
  uses_mult[0] = uses_div[0] = uses_mod[0] =
  uses_mult[1] = uses_div[1] = uses_mod[1] = false;
  side_parsetree[0] = side_parsetree[1] = NULL;
}

RVGlobLists::~RVGlobLists()
{
  if( side_parsetree[0] ) delete_parsetree(side_parsetree[0]);
  if( side_parsetree[1] ) delete_parsetree(side_parsetree[1]);
  Utils::deleteValues(m_outlineFuncNames);
}

bool RVGlobLists::do_parse(std::istream *_instream, const std::string& fname)
{
  if( current_side < 0 )
	fatal_error((char *) "RVGlobLists::do_parse(): set current_side fisrt !\n");

  if( !RVParse::do_parse(_instream, fname) )
	return false;

  side_parsetree[current_side] = take_parsetree();

  return true;
}


bool RVGlobLists::add_func_empty_bodies()
{ return RVParse::add_func_empty_bodies(side_parsetree[current_side]); }


Project* RVGlobLists::get_parsetree(const RVSide& side) const
{
  if( !side_parsetree[side.index()] )
	fatal_error((char *) "RVGlobLists::get_parsetree(): parsetree is not inited on side: ",
				side.toString().data(), false);

  return side_parsetree[side.index()];
}


ScopeTbl* RVGlobLists::get_file_scope(const RVSide& side, SymEntryType entry_type, bool exit_on_error)
{
  return RVCtool::get_file_scope(get_parsetree(side), entry_type, exit_on_error);
}


ScopeTbl* RVGlobLists::get_file_tags(const RVSide& side)
{
  return RVCtool::get_file_tags(get_parsetree(side));
}


void RVGlobLists::clear()
{
  if( parsetree ) delete_parsetree(parsetree);
  parsetree = NULL;

  if( side_parsetree[0] ) delete_parsetree( side_parsetree[0] );
  side_parsetree[0] = NULL;

  if( side_parsetree[1] ) delete_parsetree( side_parsetree[1] );
  side_parsetree[1] = NULL;

  current_side = -1;
  uses_mult[0] = uses_div[0] = uses_mod[0] =
  uses_mult[1] = uses_div[1] = uses_mod[1] = false;
}


bool RVGlobLists::is_needed(const std::string& func_name, const RVSide& side)
{
  ScopeTbl* fs = get_file_scope(side);
  SymEntry* se = fs->Lookup( func_name );
  if( !valid_function(se) ) {
	rv_errstrm << "Internal: RVGlobLists::is_needed() is unable to find function \""
			   << func_name << "\"" << " in original parse tree of side " << side.toString() << " . \n";
	return false;
  }

  return se->u2FunctionDef->fnode.is_needed;
}


///<summary>
/// Given an expression such as x *= e turns it to x = rv_mult(x, e) .
///</summary>
AssignExpr* RVGlobLists::outline_assignment(AssignOp _op, Expression *lExpr, Expression *rExpr, const Location& l) { // ofer. change tag: OUTLINE_FUNCS
	AssignExpr *ret;	
	BinaryOp bop;

	switch(_op) {
	case AO_MultEql: bop = BO_Mult;  break;  // *=
	case AO_DivEql : bop = BO_Div;   break;  // /=
	case AO_ModEql : bop = BO_Mod;   break;	 // %=
	default: assert(0);		
	}

	Expression *copy_lExpr = lExpr -> dup0(); // this duplicates lexpr. We cannot just alias lExpr (i.e., send it as both the lhs and a function argument), because it is later being destructed separately. 
	Expression *exp = outline(bop, copy_lExpr, rExpr, l);
	ret = new AssignExpr(AO_Equal, lExpr, exp, l);
	return ret;	
}

void RVGlobLists::outlineDefaultFuncName(std::string& func_name, BinaryOp _op) {
	switch(_op) {
	case BO_Mult: uses_mult[current_side] = true; break;
	case BO_Div : uses_div[current_side] = true; break;
	case BO_Mod : uses_mod[current_side] = true; break;
	default: assert(0); // supposed to get to this function only under 'mult_op' ('*', '/', '%')
	}
}

///<summary>
///Composes name for a type-specific outline function and adds necessary info
///for its declaration/definition into this->m_outlineFuncNames.
///</summary>
void RVGlobLists::outlineBaseTypesFuncName(string& func_name,
		                                   BinaryOp _op,
		                                   auto_ptr<Expression> &lExpr,
		                                   auto_ptr<Expression> &rExpr,
		                                   Type *lbt_,
		                                   Type *rbt_)
{
	Type* lbtReal = real_type(lbt_, "RVGlobLists::outlineBaseTypesFuncName");
	Type* rbtReal = real_type(rbt_, "RVGlobLists::outlineBaseTypesFuncName");
	if (!lbtReal->isBaseType() || !rbtReal->isBaseType()) {
		outlineDefaultFuncName(func_name, _op);
		return;
	}

	BaseType *lbt = static_cast<BaseType*>(lbtReal);
	BaseType *rbt = static_cast<BaseType*>(rbtReal);
	BaseTypeSpec lbtsOrig = lbt->typemask, rbtsOrig = rbt->typemask;
	lbt->typemask = fix_int_mask(lbtsOrig);
	rbt->typemask = fix_int_mask(rbtsOrig);

	std::ostringstream lTypeNameBuf, rTypeNameBuf;
	lbt->printBase(lTypeNameBuf, 0);
	rbt->printBase(rTypeNameBuf, 0);
	string lTypeName = lTypeNameBuf.str(), rTypeName = rTypeNameBuf.str();
	Utils::replaceSubstringInString(lTypeName, "const ", "");
	Utils::replaceSubstringInString(lTypeName, "volatile ", "");
	Utils::replaceSubstringInString(rTypeName, "const ", "");
	Utils::replaceSubstringInString(rTypeName, "volatile ", "");
	func_name.append("_").append(lTypeName).append("_").append(rTypeName);

	Utils::replaceCharInString(func_name, ' ', "_");
	Utils::replaceCharInString(func_name, '*', "Ptr");

	lbt->typemask = lbtsOrig;
	rbt->typemask = rbtsOrig;

	RVOutlineMapping::key_type funcName_side(current_side, func_name);
	if (m_outlineFuncNames.find(funcName_side) == m_outlineFuncNames.end()) {
		RVOutlineArgTypes* pV = new RVOutlineArgTypes(_op, lExpr.get(), rExpr.get(),
				                                      lTypeName, rTypeName);
		RVTypeProp type_prop;
		bool processed = type_prop.process(&pV->m_result);
		assert(processed);
		m_outlineFuncNames.insert(RVOutlineMapping::value_type(funcName_side, pV));
		lExpr.release();
		rExpr.release();
	}
}

///<summary>
///Makes a SymEntry for a type-specific outline function declaration and
///inserts it into the appropriate scope.
///</summary>
SymEntry *RVGlobLists::makeOutlineFuncSymEntry(const string& genOpFuncName,
		                                       const string& func_name) {
	SymEntry *orig = gProject -> Parse_TOS -> transUnit -> contxt.syms -> Lookup(genOpFuncName);
	if (orig == NULL || orig->type != FctDeclEntry)
		return NULL;
	RVOutlineMapping::iterator found =
			m_outlineFuncNames.find(RVOutlineMapping::key_type(current_side, func_name));
	if (found == m_outlineFuncNames.end())
		return NULL;

	Decl *decl = orig->uVarDecl->dup();
	if (!decl->form->isFunction())
		return NULL;

	FunctionType *ftype = static_cast<FunctionType*>(decl->form);
	if (ftype->nArgs != 2)
		return NULL;

	ftype->subType = found->second->m_result.type->dup();
	ftype->args[0]->form = found->second->m_result._leftExpr->type->dup();
	ftype->args[1]->form = found->second->m_result._rightExpr->type->dup();
	decl->name->name = func_name;

	SymEntry *newEntry = new SymEntry(orig->type, func_name, decl);
	orig->scope->Insert(newEntry);
	return newEntry;
}

///<summary>
/// Given an expression such as x = e1 * e2 turns it to x = rv_mult(e1, e2) .
///</summary>
Expression* RVGlobLists::outline(BinaryOp _op, Expression *lExprOrig, Expression *rExprOrig, const Location& l) { //change tag: OUTLINE_FUNCS
	std::string func_name;

	switch(_op) {
	case BO_Mult: func_name.append("rv_mult"); break;
	case BO_Div : func_name.append("rv_div"); break;
	case BO_Mod : func_name.append("rv_mod"); break;
	default: assert(0); // supposed to get to this function only under 'mult_op' ('*', '/', '%')
	}

	auto_ptr<Expression> lExpr(lExprOrig->dup()), rExpr(rExprOrig->dup());
	bool canTryTypeSpecific = true;

	if (lExpr->type == NULL || rExpr->type == NULL) {
		RVTypeProp type_prop;
		if (lExpr->type == NULL)
			canTryTypeSpecific &= type_prop.process(lExpr.get());
		if (rExpr->type == NULL)
			canTryTypeSpecific &= type_prop.process(rExpr.get());
	}

	string basicFuncName(func_name);
	Type *lt = lExpr->type, *rt = rExpr->type;
	canTryTypeSpecific?	outlineBaseTypesFuncName(func_name, _op, lExpr, rExpr,
				                                 lt, rt)
				      : outlineDefaultFuncName(func_name, _op);
	Symbol *sym = new Symbol;
	sym -> name = func_name;
	SymEntry *se = gProject -> Parse_TOS -> transUnit -> contxt.syms -> Lookup(sym -> name);
    if (se == NULL && canTryTypeSpecific)
        se = makeOutlineFuncSymEntry(basicFuncName, func_name);
	sym -> entry = se;		
	Variable *v = new Variable(sym, l);
	FunctionCall *fc = new FunctionCall(v, l);
	fc -> addArg(lExprOrig);
	fc -> addArg(rExprOrig);
	return fc;
}

///<summary>
/// To each side, adds the outlined functions that were used. We add the bodies (vs. just leaving the headers, which will make them uninterpreted) in case 
/// it is exclusively used at that side, or if the -refined flag is used, which means that we will need this function interpreted.
///</summary>
void RVGlobLists::add_outline_bodies(std::string side0_fname, std::string side1_fname, bool refined) {
	//1. Create general (type-unsafe) bodies for outline functions:
	if (uses_mod[0] && (refined || !uses_mod[1]))  rv_commands.outline_header("rv_mod.c", side0_fname); 
	if (uses_div[0] && (refined || !uses_div[1]))  rv_commands.outline_header("rv_div.c", side0_fname); 
	if (uses_mult[0]&& (refined || !uses_mult[1])) rv_commands.outline_header("rv_mult.c", side0_fname); 

	if (uses_mod[1] && (refined || !uses_mod[0]))  rv_commands.outline_header("rv_mod.c", side1_fname); 
	if (uses_div[1] && (refined || !uses_div[0]))  rv_commands.outline_header("rv_div.c", side1_fname); 
	if (uses_mult[1] && (refined || !uses_mult[0])) rv_commands.outline_header("rv_mult.c", side1_fname);

	if (m_outlineFuncNames.empty())
		return;

	//2. Create bodies for type-specific outline functions:
	ofstream *side_fout[2] = {NULL, NULL};
	const string* pInFname[2] = {&side0_fname, &side1_fname};
	string side_fname[2];
	RVOutlineMapping::iterator it = m_outlineFuncNames.begin();
	for (; it != m_outlineFuncNames.end(); ++it) {
		int sideNum = it->first.first;
		if (side_fout[sideNum] == NULL) {
			side_fname[sideNum] = *pInFname[sideNum] + ".tmp";
			side_fout[sideNum] = new ofstream(side_fname[sideNum].data(),
						                      ios_base::out);
		}
		defineTypeSpecificOutlineFunc(it->first.second, *it->second,
				                      *side_fout[sideNum], sideNum, refined);
	}
	for (unsigned int i = 0; i < ARRAY_LEN(side_fout); ++i) {
		if (side_fout[i] == NULL) continue;
		side_fout[i]->close();
		delete side_fout[i];
		rv_commands.outline_type_specific(side_fname[i]);
	}
}

void RVGlobLists::defineTypeSpecificOutlineFunc(const std::string& funcName,
		                                        RVOutlineArgTypes& argTypes,
		                                        std::ofstream& fout,
		                                        int sideNum,
		                                        bool refined) {
	const char *preCond = NULL, *opChar = NULL;

	//Create body (vs. just leaving the declaration, which will make funcName uninterpreted) if
    //it is exclusively used at the current side or if the -refined flag is set,
	//which means that we will need funcName interpreted:
	bool makeBody = refined ||
			        m_outlineFuncNames.find(RVOutlineMapping::key_type(1-sideNum, funcName)) == m_outlineFuncNames.end();

	if (makeBody) {
		switch (argTypes.m_result.bOp) {
		case BO_Mult: opChar = "*"; break;
		case BO_Div : preCond = "y != 0"; opChar = "/"; break;
		case BO_Mod : preCond = "y > 0"; opChar = "%"; break;
		default: assert(0); // supposed to get to this function only under 'mult_op' ('*', '/', '%')
		}
	}

	fout << "/* type-specific outlined function created by prependOutlineFunction() */\n";
	if (preCond != NULL)
		fout << "void __CPROVER_assume(_Bool);\n";

	argTypes.m_result.type->printBase(fout, 0);

	fout << funcName << '(' << argTypes.m_lTypeName << "x, " << argTypes.m_rTypeName << "y)"
	     << (makeBody? " {\n" : ";\n");
	if (preCond != NULL)
		fout << "    __CPROVER_assume(" << preCond << ");\n";
	if (makeBody)
		fout << "    return x " << opChar << " y;\n}\n";
}

RVGlobLists::RVOutlineArgTypes::RVOutlineArgTypes(BinaryOp  op,
		                                          Expression *lexpr,
		                                          Expression *rexpr,
		                                          const string& lTypeName,
		                                          const string& rTypeName)
  : m_result(op, lexpr, rexpr, NoLocation),
    m_lTypeName(lTypeName),
    m_rTypeName(rTypeName)
{}



	 
/*  RVRename functions:  */
/* ===================== */

RVRename::RVRename(int _buf_size) :
  buf_size(_buf_size), current_side(0)
{ 
  init();

  buf = new char [_buf_size];
  if( buf == NULL)
	fatal_error("RVRename::RVRename() can't allocate buffer\n", false);
  next = 0;
  buf[0] = 0;

  static_renamer = false;
}

RVRename::RVRename(Project *_parsetree, const RVSide& _side, bool _exclude_vars) :
  buf_size(1), current_side(_side)
{ 
  init();

  parsetree = _parsetree;
  
  buf = new char [buf_size];
  if( buf == NULL)
	fatal_error("RVRename::RVRename() can't allocate buffer\n", false);
  next = 0;
  buf[0] = 0;

  exclude_vars = _exclude_vars;

  static_renamer = true; 
}

void RVRename::init()
{
  outstream = NULL;
  directs = NULL;
  static_renamer = false; 
  semchk_recursive = false;
  semchk_use_uf_prefix = false;

  func_name = NULL;
  func_name_len = 0;

  exclude_vars = false;
}
	
RVRename::~RVRename()
{ 
  delete [] buf; 
  if( static_renamer )
	parsetree = NULL; /* we didn`t parse this tree - we don't delete it. */
}

void RVRename::end_body()
{ 
  semchk_use_uf_prefix = false; 
  func_name = NULL;
  func_name_len = 0;
  RVParse::end_body(); 
}

	
char* RVRename::find_nested_proto_end()
{
	int count;
	char* popen  = strchr(buf, '(');
	char* pclose = strchr(buf, ')');
	char* last   = pclose;
	if( !popen || !pclose || pclose < popen ) {
	  yyerror((char *) "bad function prototype (')' before '(' or not found)");
	  return NULL;
	}
 
	/* count nested ()s till the count is 0 (# of '('s equals # of ')'s) */   
	count = 1;
	popen = strchr(popen+1, '(');
	while( count > 0 ) {
	  if( !pclose ) {
		yyerror((char *) "bad function prototype (no closing ')')");
		return NULL;
	  }
	  if( pclose < popen || !popen ) {
		count--;
		last = pclose;
		pclose = strchr(last+1, ')');
	  } 
	  else { /* popen exists and is before pclose */
		count++;
		popen  = strchr(popen+1, '(');
	  }
	}

	return last;
}


char* RVRename::find_func_name(int& len)
{
  len = 0; // safety
  if( static_renamer ) // static renamer doesn't have buf.
	return NULL;

  char* pc = NULL;
  char* popen  = strchr(buf, '(');
  if( !popen )
	return NULL;
	
  for(pc = popen-1; pc >= buf; pc--)
	if( !isalnum(*pc) && *pc != '_' )
	  break;

  pc++; // last good char
  if( !isalpha(*pc) && *pc != '_' )  // this is not an ID start
	return NULL;

  len = popen - pc;

  return pc;
}


void RVRename::gen_semchk_proto(char* end_proto)
{
	if(DBG) rv_errstrm << "RVRename::gen_semchk_proto() \n";
  /* copy the chk0/1_ proto from buf: */
  int proto_size = end_proto - buf +1;
  char* proto_buf = new char[proto_size + 5];
  strncpy(proto_buf, buf, proto_size);
  strcpy(proto_buf + proto_size,";");
  
  /* replace semchk prefix with usual one: */
  char *prefix = strstr(proto_buf, current_side.get_semchk_prefix());
  if( !prefix )
	yyerror((char *) "Internal: can't find prefix of recursive semchked function.");
  else {
	strncpy(prefix, current_side.get_side_prefix(), RV_PREFIX_LEN);
	(*outstream) << proto_buf <<"\n\n";
  }
  delete proto_buf;
}


void RVRename::flush_buffer(Statement* st)
{
  if( outstream == NULL )
	fatal_error((char *) "RVRename::flush_buffer() - outstream == NULL \n" );

  Symbol* sym = NULL;
  FunctionDef* func = NULL;

  if( st && st->isFuncDef() ) {
	func = (FunctionDef*)st;
	if( func && func->decl && func->decl->name )
	  sym = func->decl->name;
  }
  else if( st && st->isDeclaration() ) {
	/* Function prototypes (decls) must be treated separately: */
	Decl* decl = ((DeclStemnt*)st)->decls[0];
	if( decl && !decl->isTypedef() && decl->form && decl->form->isFunction() )
	  sym = decl->name;
  }

  if( sym &&       
	  // prototypes of special funcs without bodies *are* needed:
	  !supplied_by_rvt(sym->name) && !ignore_func(sym->name) &&
	  /* if we don't need the function - don't print: */
	  !rv_parser.is_needed(sym->name, current_side) ) {
	next = 0;
	end_body();
	return; 
  }

  /* Note: we print only needed funcs: */
  if( func && sym ) {
		
	char* end_proto = find_nested_proto_end();
	std::string func_name = sym->name;
	bool is_semchk_fname = semchk_pair && (semchk_pair->side_name[current_side.index()] == func_name);
	
	if( is_semchk_fname ) {
	  if( !end_proto )
		buf[0] = 0;

	  /* recursive functions under semchk need their UF version's prototype: */
	  if( semchk_recursive && end_proto ) 
		gen_semchk_proto(end_proto);
	} /* semchk */
	else
	/* check for UFs - print only their prototypes: */
	if( rv_ufs.is_uf(sym->name, current_side) ) {
	  if( !end_proto )
		buf[0] = 0;
	  else
		strcpy(end_proto,");");  /* close the prototype */
	}
  } /* if func */

  buf[next] = 0;
  (*outstream) << buf <<"\n";

  next = 0;
  end_body();
}

void RVRename::discard_buffer()
{ next = 0; buf[next] = 0; }

void RVRename::collect(char* token_text, int token_len)
/* collect in the buffer */
{
  if( token_text == NULL || token_len == 0 ) return;

  if( next+token_len >= buf_size ) {
	yyerr((char *) "RVRename::collect() - parsed function is bigger than the buffer \n");
	fatal_error((char *) "RVRename::collect() - buffer overflow, can't continue \n");
  }
  
  strncpy( &buf[next], token_text, token_len);
  next += token_len;
}


void RVRename::insert_prefix(char *sym, int len, const char *prefix)
{
	if (DBG) rv_errstrm << "... RVRename::insert_prefix" << *sym << "\n"; 
  /* if the symbol is not where we expect it: */
  if( strncmp(&buf[next-len], sym, len) ) { 
	buf[next] = 0;
	yyerr((char *) "RVRename::insert_prefix() - symbol is not where it is expected:", &buf[next-len]);
	fatal_error((char *) "");
  }

  if( next + RV_PREFIX_LEN +1 > buf_size ) {
	buf[next] = 0;
	yyerr((char *) "RVRename::insert_prefix() - adding prefix overflows buffer:", &buf[next-len]);
	fatal_error((char *) "RVRename::insert_prefix() - buffer overflow, can't continue");
  }

  strcpy( &buf[next-len], prefix);
  strncpy( &buf[next-len+RV_PREFIX_LEN], sym, len);

  next += RV_PREFIX_LEN;
  buf[next] = 0;
}

	
void RVRename::insert_side_prefix(SymEntry* se, char *sym_name, int len, int clevel)
{
  const char* prefix = NULL;
  if (DBG) rv_errstrm << "... RVRename::insert_side_prefix" << *sym_name << "\n"; 
  /* struct/union component doesn't need prefix: */
  if( next_is_comp )
	return;

  bool is_semchk_fname = semchk_pair && (semchk_pair->side_name[current_side.index()] == sym_name);

  /* new global symbol must be defined only in FILE_SCOPE, EXTERN_SCOPE: */
  if( !se && (clevel == FILE_SCOPE || clevel == EXTERN_SCOPE) ) {
	if( is_semchk_fname ) {
	  prefix = current_side.get_semchk_prefix();
	  if( semchk_recursive ) 
		semchk_use_uf_prefix = true;
	} 
	else
	  prefix = current_side.get_side_prefix();
	  
	if( !ignore_func(sym_name) )
	  insert_prefix(sym_name, len, prefix);
  }

  if( se && is_function(se) && !in_tag_def ) {
	prefix = current_side.get_side_prefix();

	if( is_semchk_fname ) {
	  /* if not a recursive call in the body of the semchked function - 
			use the semchk version - otherwise the UF one (the default one): */
	  if( !semchk_use_uf_prefix )
		prefix = current_side.get_semchk_prefix();
	}

	if( ignore_func(se->name) )
	  return;

	/* for all other funcs: */
	insert_prefix(sym_name, len, prefix);
	return;
  }

  if( se && is_top_level(se) )
	/* At FUNCTION_SCOPE - it must be typedef or tag name to be accepted 
	 *   otherwise it is a new function param of same name,
	 * Inside function (but not tag definition) body: decide by is_top_level(se):            */
	if( clevel < FUNCTION_SCOPE || se->IsTypeDef() || 
		(se->IsTagDecl() && gProject->Parse_TOS->possibleTag) || 
		(in_body && !in_tag_def) )
	  insert_prefix(sym_name, len, current_side.get_side_prefix());

  /* all enum idents must have different names on different sides: */
  if( se && se->IsEnumConst() )
	insert_prefix(sym_name, len, current_side.get_side_prefix());
}


long get_IntConstant(Expression *cexpr)
{
  if( !cexpr || cexpr->etype != ET_Constant ||
	  ((Constant*)cexpr)->ctype != CT_Int ) {
	yyerr((char *) "get_IntConstant() received not an IntConstant!\n");
	return 0;
  }

  return ((IntConstant*)cexpr)->lng;
}


std::string* get_StringConstant(Expression *cexpr)
{
  if( !cexpr || cexpr->etype != ET_Constant ||
	  ((Constant*)cexpr)->ctype != CT_String ) {
	yyerr((char *) "get_StringConstant() received not an StringConstant!\n");
	return NULL;
  }
  
  return &(((StringConstant*)cexpr)->buff);
}

ExprVector* get_ArrayConstant(Expression *cexpr)
{
  if( !cexpr || cexpr->etype != ET_Constant ||
	  ((Constant*)cexpr)->ctype != CT_Array) {
	yyerr((char *) "get_IntConstant() received not an IntConstant!\n");
	return NULL;
  }
  
  return &(((ArrayConstant*)cexpr)->items);
}


SymEntry* RVRename::get_loop_pvar_symbol(std::string& ref_name)
{   
if(DBG){rv_errstrm<<"RVRename::"<<__FUNCTION__<<"\n";/*FDEL*/}
  ref_name = RVLoop::ref_argname(ref_name);
  SymEntry* se = lookup_symbol_in_current_contxt( ref_name );

  /* check whether its really a prototype symbol: */
  if( !se || !se->scope || se->scope->level != FUNCTION_SCOPE )
	return NULL;

  if( !func_name )
	func_name = find_func_name(func_name_len);
  if( !func_name )
	return NULL;
  
  //std::string name_str;
  //name_str.copy(func_name, func_name_len);
  //assert(strlen(func_name) == 0);
  //The following line replaces the 3 lines above
  if (func_name != NULL) *func_name = '\0';

  if( !RVLoop::is_loop_name(func_name, NO_SIDE) )
	return NULL;

  return se;
}


int RVRename::copy_with_prefix(const char* symbol, int symbol_len, char* buf, int buf_len )
/* returns number of added chars */
{
  SymEntry* se = NULL;
  const char* pref = NULL;
  int pref_len = 0;
  char symcpy[RV_MAX_IDENT+1];
  if (DBG) rv_errstrm << "... RVRename::copy_with_prefix" << *symbol << "\n"; 

  if( symbol_len > RV_MAX_IDENT ) {
	buf[0] = 0;
	yyerr((char *) "RVRename::copy_with_prefix(): symbol len is bigger than RV_MAX_IDENT : ",symbol);
	if( 6 < buf_len ) strcpy(buf, "ERROR");
	return 0;
  }

  strncpy(symcpy, symbol, symbol_len);
  symcpy[symbol_len] = 0;
  std::string name(symcpy);

  if(DBG) rv_errstrm << "\nRVRename::copy_with_prefix() converts symbol: \"" << name << "\"\n"
		  "  symbol_len=" << symbol_len <<" \n";

  if( static_renamer )  {/* static renamer doesn't know current scope */ 
	se = lookup_symbol_in_global_contxt( name );
  } else {
	se = lookup_symbol_in_current_contxt( name );
	/* check whether it changed to loop p_var  */ 
	if( !se && !exclude_vars && get_loop_pvar_symbol( name ) ) {
	  pref = LOOP_DEREF_PREFIX;
	  pref_len = RV_PREFIX_LEN;  /* needs to add reference prefix. */
	}
  }

  if( se && is_top_level(se) )
	if( !se->IsComponentDecl() &&  /* don't prefix components */
		(!exclude_vars || !(se->IsVarDecl() || se->IsParamDecl())) ) 
	  {
		//pref = current_side.get_side_prefix(); // ofer: we can change here and next line to _ufprefix but this oly works if it is the same length of buffer, because we are called from covert_ids which sends buffer and buffer length
		//pref_len = RV_PREFIX_LEN;  /* needs to add side prefix. */
	  }

  if( symbol_len + pref_len +1 > buf_len ) {
	buf[0] = 0;
	yyerr((char *) "RVRename::copy_with_prefix() - adding prefix overflows buffer:", symbol);
	if( 6 < buf_len ) strcpy(buf, "ERROR");
	return 0;
  }

  //if( pref )
	//strcpy( buf, pref );

  strncpy( &buf[pref_len], symbol, symbol_len);
  buf[ symbol_len + pref_len ] = 0;
  if(DBG) rv_errstrm << "new: " << buf << "\n";
  return symbol_len + pref_len;
}


std::string RVRename::convert_ids(const std::string& code )
{
  int len = code.size(), retlen = len*(RV_PREFIX_LEN+1)+1;
  char *pit = new char[len+1];  /* must have because code.data() is defined "const char*" */ 
  char *pc, *pafter, *pend;
  char *retbuf = new char[retlen+1]; /* (?) */
  char *pr = retbuf, *pretend = retbuf + retlen;

  strncpy( pit, code.data(), len);
  pit[len] = 0;
  pc = pit;
  pend = pc+len;

  while(pc < pend && pr < pretend) {
	if( isalpha(*pc) || *pc == '_' ) { /* if we find ID begin: */
	  /* find its end: */
	  for(pafter = pc; 
		  pafter < pend && (isalnum(*pafter) || *pafter == '_'); 
		  pafter++)
		;
	  len = copy_with_prefix(pc, pafter-pc, pr, pretend-pr);
	  pr += len;
	  pc = pafter;
	} 
	else
	  *(pr++) = *(pc++);
  }

  /* close the string: */
  if( pr < pretend )
	*pr = 0; 
  else
	retbuf[retlen] = 0;

  std::string retstr( retbuf );
  delete[] pit;
  delete[] retbuf;
  return retstr;
}


void RVRename::write_check_code( std::string* pchan, std::string* pcond, std::string* pval)
{
  if( pchan == NULL || pcond == NULL || pval == NULL ) {
	yyerr((char *)  "RVRename::write_check_code() received NULL param.\n");
	return;
  }

  if( !directs->is_channel( *pchan ) ) {
	yyerr((char *)  "RVRename::write_check_code() undefined channel:", *pchan );
	return;
  }

  std::ostringstream tmp_out;
  RVTemp temps(tmp_out);
  
  /* Convert global ids in pcond and pval by adding side prefix: */
  std::string cond_str = convert_ids(*pcond);
  std::string val_str = convert_ids(*pval);

  temps.gen_checkpoint(current_side, *pchan, cond_str, val_str);
  
  if( next + (int)tmp_out.str().size() +1 > buf_size ) {
	yyerr((char *) "RVRename::write_check_code() - adding check code overflows buffer:", tmp_out.str() );
	if( next+6 < buf_size ) strcpy(&buf[next], "ERROR");
	return;
  }

  strncpy( &buf[next], (char*)tmp_out.str().data(), tmp_out.str().size() );
  next += tmp_out.str().size();
  buf[next] = 0;
}  


void RVRename::insert_check_point(SymEntry *se)
{
  if( !se || !se->IsVarDecl() ) return;

  Decl* decl = se->uVarDecl;

if(DBG) decl->print(rv_errstrm, true);

  if( !decl || !decl->form || !decl->form->isBaseType() || 
	  ((BaseType*)(decl->form))->typemask != BT_UserType )
	return;

  ExprVector* vals = get_ArrayConstant(decl->initializer);
  BaseType* str_type = (BaseType*)decl->form;
  if( !vals || !str_type->typeName )
	return;

  std::string& name = str_type->typeName->name;
  std::string channel(RV_DEF_CHANNEL_NAME);
  std::string cond("1");
  std::string val("ERROR_VAL");

  /* If it is name of a channel - it shouldn't be used as a label: */  
  if( name == RV_CHANNEL_TYPE_NAME ) {
	yyerr((char *) "Don't use channel names for labels: ", str_type->typeName->name );
	return;
  } else
	/* If it is a name of a check point use it: label = <channel, cond, val> */
  if( name == RV_CP_TYPE_NAME ) {
	channel = *get_StringConstant((*vals)[0]);
	cond    = *get_StringConstant((*vals)[1]);
	val     = *get_StringConstant((*vals)[2]);
  } else
	/* If it is a name of a default check point (with default channel) 
		 use it: label = <cond, val> */
  if( name == RV_DEF_CP_TYPE_NAME ) {
	cond = *get_StringConstant((*vals)[0]);
	val  = *get_StringConstant((*vals)[1]);
  } 
  else
	return;

  write_check_code( &channel, &cond, &val );
}


void RVRename::process_label(const std::string& name)
{
  if( !directs )
	fatal_error((char *) "RVRename::process_label(): directs is NULL");

  SymEntry* se = directs->lookup_label(current_side, name);

  if( !se ) return;

  /* we don't use the check_points during semantic check: */
  if( semchk_pair )
	return;

  insert_check_point(se);
}


void RVRename::set_side(const RVSide& side)
{
  current_side = side;
}

void RVRename::set_output(std::ostream *_outstream)
{
  outstream = _outstream;
}

void RVRename::set_directs(RVDirectives* _dirs)
{
  directs = _dirs;
}




/*  RVDirectives functions:  */
/* ========================= */

RVDirectives::RVDirectives()
  : RVParse()
{ 
  cpTbl[0] = cpTbl[1] = NULL;
  ffTbl[0] = ffTbl[1] = NULL;
  shTbl[0] = shTbl[1] = NULL;
  chanTbl = NULL;
  active = false;
}

RVDirectives::~RVDirectives()
{ /* cpTbls are deleted as part of the parsetree */  }


bool RVDirectives::do_parse(std::istream *_instream, const std::string& fname)
{
  ignore_undefined = true;

  if( !RVParse::do_parse(_instream, fname) ) 
	return false;

  chanTbl = get_file_scope(parsetree);

if(DBG) chanTbl->Show(rv_errstrm);

  return true; 
}


ScopeTbl** RVDirectives::which_scope(std::string& func_name, int& out_side, 
					 std::string& out_scope_name, bool& out_label_scope)
{
  out_label_scope = false;

  if( func_name == RV_SIDE0_CP_BLOCK ) {
	out_side = 0; 
	out_scope_name = "cpTbl";
	return &cpTbl[out_side];
  }

  if( func_name == RV_SIDE1_CP_BLOCK ) {
	out_side = 1;
	out_scope_name = "cpTbl";
	return &cpTbl[out_side];
  }

  if( func_name == RV_SIDE0_FF_BLOCK ) {
	out_side = 0;
	out_scope_name = "ffTbl";
	return &ffTbl[out_side];
  }

  if( func_name == RV_SIDE1_FF_BLOCK ) {
	out_side = 1;
	out_scope_name = "ffTbl";
	return &ffTbl[out_side];
  }

  if( func_name == RV_SIDE0_SH_BLOCK ) {
	out_side = 0;
	out_scope_name = "shTbl";
	out_label_scope = true;
	return &shTbl[out_side];
  }

  if( func_name == RV_SIDE1_SH_BLOCK ) {
	out_side = 1;
	out_scope_name = "shTbl";
	out_label_scope = true;
	return &shTbl[out_side];
  }
  
  return NULL;
}

void RVDirectives::grab_scope( std::string& func_name )
{
  int side;
  std::string scope_name("UNKNOWN");
  bool use_label_scope;
  SymTbl   *symtbl;
  ScopeTbl *outer, *res_scope = NULL;
  
  ScopeTbl** trg_tbl = which_scope(func_name, side, scope_name, use_label_scope);
  if( !trg_tbl )
	return;
	
  if( !parsetree || !parsetree->Parse_TOS || !parsetree->Parse_TOS->transUnit ) {
	yyerr((char *) "One of the structures on the path to directive declarations is NULL in: ", func_name);
	return;
  }
  
  /* Find the outer scope of the file from the context: */
  if( use_label_scope )
	symtbl = parsetree->Parse_TOS->transUnit->contxt.labels;
  else
	symtbl = parsetree->Parse_TOS->transUnit->contxt.syms;

  if( !symtbl || !symtbl->current ) {
	yyerr((char *) "The sybmol table or its 'current' scope table is NULL in: ", func_name);
	return;
  }

  outer = symtbl->current;
  
  if( outer->nchild == 0 || !outer->children || !outer->children[outer->nchild -1] ) {
	yyerr((char *) "Can't find directive declarations scope in outer scope: ", func_name);
	return;
  }
  
  /* This function scope is the last in "outer" scope: */
  ScopeTbl *func_scope = outer->children[outer->nchild -1];

  if( use_label_scope )
	res_scope = func_scope;
  else {
	if( func_scope->nchild < 1 || !func_scope->children || !func_scope->children[0] ) {
	  yyerr((char *) "One of the scopes of directive declarations is missing: ", func_name);
	  return;
	}
	
	/* the check point declarations themselves (CPs, DCPs) are 2 scopes below the function's one: */
	res_scope = func_scope->children[0];
  }

  *trg_tbl = res_scope;

if(DBG && res_scope) {
  rv_errstrm << "Printing "<< scope_name << "[" << side <<"]  :\n";
  res_scope->Show(rv_errstrm);
}
}

bool RVDirectives::is_channel( const std::string& name )
{
  return(lookup_channel( name ) != NULL);  // ofer: to supress warning
}

bool RVDirectives::is_channel(SymEntry* se)
{
  if( !se || !se->IsVarDecl() ) return false;

  Decl* decl = se->uVarDecl;

if(DBG) decl->print(rv_errstrm, true);

 if( !decl || !decl->form || !decl->form->isBaseType() )
	return false;

  BaseType* str_type = (BaseType*)decl->form;

  if( str_type->typemask != BT_UserType || 
	  str_type->typeName->name != RV_CHANNEL_TYPE_NAME )
	return false;

  return true;
}


SymEntry* RVDirectives::lookup_channel( const std::string& name )
{
  if( !chanTbl )
	fatal_error("RVDirectives::lookup_channel() cpTbl not init!\n", false);

  SymEntry* se =  chanTbl->Lookup( name );

  if( !is_channel( se ) )
	return NULL;

  return se;
} 
  
SymEntry* RVDirectives::lookup_label( const RVSide& side, const std::string& name )
{
if(DBG) rv_errstrm << "... RVDirectives::lookup_label(" << side.toString() << "," << name <<")\n";

  if( side.isIllegalIndex() || !cpTbl[side.index()] )
	fatal_error("RVDirectives::lookup_label() cpTbl not init or wrong side value.\n", false);

  return cpTbl[side.index()]->Lookup( name );
} 

unsigned RVDirectives::get_func_flags( int side, const std::string& name )
{
if(DBG) rv_errstrm << "... RVDirectives::get_func_flags(" << side << "," << name <<")\n";

  if(side != 0 && side != 1)
	fatal_error("Internal: in RVDirectives::get_func_flags(): wrong side namber.\n", false);

  if(!ffTbl[side])
	return 0;

  SymEntry* se = ffTbl[side]->Lookup( name );
  if( !se )
	return 0;

  return get_func_flags(se);
} 

HashTblIter RVDirectives::get_channels_iter()
{
  return HashTblIter(chanTbl->htab);
}


ExprVector* RVDirectives::get_check_point_vals(SymEntry* se, std::string& type_name)
{
  Decl* decl = NULL;

  if( !se || !se->IsVarDecl() ) 
	return NULL;

  decl = se->uVarDecl;

if(DBG && decl) decl->print(rv_errstrm, true);

  if( !decl || !decl->form || !decl->form->isBaseType() || 
	  ((BaseType*)(decl->form))->typemask != BT_UserType )
	return NULL;

  ExprVector* vals = get_ArrayConstant(decl->initializer);
  BaseType* str_type = (BaseType*)decl->form;
  if( !vals || !str_type->typeName )
	return NULL;

  type_name = str_type->typeName->name;
  return vals;
}


unsigned RVDirectives::get_func_flags(SymEntry* se)
{
  Decl* decl = NULL;

  if( !se || !se->IsVarDecl() ) 
	return 0;

  decl = se->uVarDecl;

if(DBG && decl) decl->print(rv_errstrm, true);

 if( !decl || !decl->form || !is_basetype(decl->form, BT_UserType) )
	return 0;

  ExprVector* vals = get_ArrayConstant(decl->initializer);
  BaseType* str_type = (BaseType*)decl->form;
  if( !vals || !str_type->typeName || str_type->typeName->name != RV_FF_TYPE_NAME )
	return 0;
  
  unsigned flag = 0;
  Expression *exp;
  ExprVector::const_iterator it;
  FORVEC(it, (*vals)) {
	exp = (*it);
	if( !exp || exp->etype != ET_Constant || 
	!( ((Constant*)exp)->ctype != CT_Int || ((Constant*)exp)->ctype != CT_UInt ) ) {
	  rv_errstrm << "Warning: a function flag should be an integer constant. at: ";
	  if(exp) exp->location.printLocation(rv_errstrm); 
	  else rv_errstrm <<"UNKNOWN (exp == NULL)";
	  rv_errstrm <<"\n";
	}
	
	if( ((Constant*)exp)->ctype != CT_Int )
	  flag |= ((IntConstant*)exp)->lng;
	else
	  flag |= ((UIntConstant*)exp)->ulng;
  }
	
  return flag;
} 

Block* RVDirectives::get_shape_block(int side, const Type* shape_type)
{
  if( !(side == 0 || side == 1) )
	fatal_error("Internal: in RVDirectives::get_shape_block(): bad side number!\n", false);

  if( !shTbl[side] )
	return NULL;

  /* only typedef or struct/union types may have shape assumptions block: */
  if( !is_basetype(shape_type, (BT_UserType|BT_Struct|BT_Union)) )
	  return NULL;

  std::string name;
  if( is_basetype(shape_type, BT_UserType) && ((BaseType*)shape_type)->typeName )
	name = ((BaseType*)shape_type)->typeName->name;
  else {
	Type* rt = real_type(shape_type, "RVDirectives::get_shape_block()");
	if( is_basetype(rt, (BT_Struct|BT_Union)) && ((BaseType*)rt)->tag )
	  name = ((BaseType*)rt)->tag->name;
	else {
	  rv_errstrm << "Warning: in RVDirectives::get_shape_block(): "
	"unhable to find name or tag-name of Type:\n  ";
	  shape_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n\n";
	}
  }

  SymEntry* se =  shTbl[side]->Lookup( name );
	  
  if( !se || !se->IsLabelDecl() || !se->u2LabelPosition )
	return NULL;

  if( !se->u2LabelPosition->isBlock() ) {
	rv_errstrm << "Error: Shape assume block must be a code block (enclosed by '{}')\n  "
	  "preceded by shape type name or by tag name, at: ";
	se->u2LabelPosition->location.printLocation(rv_errstrm); 
	rv_errstrm << "\n  for Type: ";
	shape_type->printType(rv_errstrm, NULL, true, 0); rv_errstrm<<"\n\n";
  }

  return ((Block*)se->u2LabelPosition);
} 
  
