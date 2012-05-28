#include <rv_error.h>
#include <rv_consts.h> 
#include <rv_macros.h>
#include <rv_ctool.h>
#include <rv_treecomp.h>
#include <rv_funcnode.h>

#include <ctool/symbol.h>
#include <ctool/stemnt.h>
#include <algorithm>
#include <vector>
#include <sstream>

#define RV_SECTION RV_SEC_FUNCNODE


static int compSymbolName(const Symbol *pa, const Symbol *pb)
{  
// if(DBG) rv_errstrm << "compSymbolName("<<pa->name<<", "<<pb->name<<") \n"; 
  return (pa->name < pb->name);
}


/* SymbolVector code: */
/* ================== */

void SymbolVector::print(const char *header, std::ostream& out) const
{
  if( header )
    out << header;
  
  SymbolVector::const_iterator  j;
  for (j=begin(); j != end(); j++)
    if( (*j) != NULL )
      out << (*j)->name << ", ";
    else
      out << "UNPRINTABLE, ";

  out << "\n";
}


void SymbolVector::unique_sort(void)
{
  if( !empty() ) {
    sort(begin(), end(), compSymbolName);
    remove_doubles();
  }
}


void SymbolVector::remove_doubles(void)
{
  SymbolVector tmp;
  Symbol*      last = NULL;

  SymbolVector::const_iterator  j;
  for (j=begin(); j != end(); j++)
    if( !last || (*j)->name != last->name ) {
      tmp.push_back(*j);
      last = *j;
    }
    else
      delete(*j); // ??

  *this = tmp;
}


void SymbolVector::filter_common(const SymbolVector& other, bool keep_common /*=false*/)
/* remove items common to this and other vectors: */ 
{
  SymbolVector tmp;

  SymbolVector::const_iterator  j;
  for (j=begin(); j != end(); j++)
    if( (other.find((*j)->name)!= NULL) == keep_common )
      tmp.push_back(*j);
    else
      delete(*j); // ??

  *this = tmp;
}


void SymbolVector::add_dup(const SymbolVector& other)
{
  int i = size();
  resize(size() + other.size());

  SymbolVector::const_iterator j;
  for(j = other.begin(); j != other.end(); j++, i++)
    THIS[i] = (*j)->dup();
}


Symbol* SymbolVector::find(const std::string& name) const
{
  Symbol  key;
  int s = 0, e = size(), i;

  key.name = name;
  while( s < e ) {
    i = (s + e)/2;
    if( key.name == at(i)->name )
      return at(i);
    if( compSymbolName(&key, at(i)) )
      e = i;
    else
      s = i+1;
  }
  return NULL;
}


bool SymbolVector::has_item(const Symbol* sym) const
{
  const_iterator i;
  FORVEC(i, THIS)
    if( (*i) == sym )
      return true;
  return false;
}


Symbol* SymbolVector::find_related(Symbol* symbol, int symbol_side /*= -1*/) const
/* find global symbol with same name or related thru equalTo: */
{
  RVTreeComp  comp;
  SymEntry*   se;

  const std::string& symbol_name = symbol->name;
  std::string other_name = symbol_name;  // on other side - first assume the same

  /* fix the prefix of other side name if needed: */
  if( symbol_side >= 0 &&
      !other_name.compare(0, RV_PREFIX_LEN, (symbol_side? RV_SIDE1_PREFIX: RV_SIDE0_PREFIX)) )
    other_name  = std::string(symbol_side? RV_SIDE0_PREFIX: RV_SIDE1_PREFIX) +
      other_name.substr(RV_PREFIX_LEN);

  Symbol *ret = find(other_name);
  if( ret )
    return ret;

  /* otherwise check equal global by expression tree: */
  if( symbol->entry && (se = symbol->entry->equalTo) &&
      se->equalTo == symbol->entry )
  {
    other_name = se->name;
    if( symbol_side >= 0 &&  // if we need side prefix but other_name doesn't have it:
    other_name.compare(0, RV_PREFIX_LEN, (symbol_side? RV_SIDE0_PREFIX: RV_SIDE1_PREFIX)) )
      other_name.insert(0, symbol_side? RV_SIDE0_PREFIX: RV_SIDE1_PREFIX);

    if( (ret = find(other_name)) )
    {
      if( se->uVarDecl && symbol->entry->uVarDecl &&
      comp.eq_type( RVCtool::get_symbol_type(symbol, "SymbolVector::find_related()"),
           se->uVarDecl->form )           &&
      comp.eq_expr( symbol->entry->uVarDecl->initializer, se->uVarDecl->initializer ) )
    return ret;
      else
    rv_errstrm <<"Warning: SymbolVector::find_equal(): globals "<< symbol_name <<" and "<<
      other_name <<" are related on opposite sides but have different type definitions.\n";
    }
  }

if(DBG) rv_errstrm << "find_equal() can't find equal to symbol: "<< symbol->name <<" \n";
  
  return NULL;
}

bool SymbolVector::all_related(const SymbolVector& other) const
{
  const_iterator j;

  FORVEC(j,(*this))
    if( !other.find_related(*j) )
      return false;

  return true;
}

void SymbolVector::delete_all(void)
{
  SymbolVector::iterator i;
  FORVEC(i, THIS) delete (*i);
  resize(0);
}



/* ArgType code: */
/* ============= */

std::string argtype2string(ArgType at)
{
  if( at == 0 )
    return "NONE";

  std::string ret("");

  if( at & AT_Unknown )
    ret += "Unknown ";
  if( at & AT_In )
    ret += "In ";
  if( at & AT_Out )
    ret += "Out ";
  if( at & AT_Deref )
    ret += "Deref ";
  if( at & AT_Array )
    ret += "Array ";

  return ret;
}



/*  RVBlockNode code: */
/* ================== */

RVBlockNode::RVBlockNode(void)
{ 
  loop_rec = NULL;
}

RVBlockNode::~RVBlockNode()
{
  vars.delete_all();
  pvars.delete_all();
  labels.delete_all();
}
  
void RVBlockNode::sort_vectors(void)
{
  vars.unique_sort();
  pvars.unique_sort();
  labels.unique_sort();

  /* if we need a var by reference - we don't need it by value: */
  vars.filter_common(pvars);
}  

void RVBlockNode::print_vectors( std::ostream& out, bool with_headers ) const
{
  vars.print( (with_headers ? "input vars: " : NULL), out);
  pvars.print( (with_headers ? "ref vars (out/struct): " : NULL), out);
  labels.print( (with_headers ? "goto labels: " : NULL), out);
}


void RVBlockNode::add_internal_scope(ScopeTbl* scp)
{
  internal_scopes.push_back(scp);
}

SymEntry* RVBlockNode::lookup_internal_scopes(const std::string& sym_name) const
{
  SymEntry* res = NULL;

  /* lookup at the last encountered scope first: */
  for(int i = internal_scopes.size()-1; i >= 0; --i)
    if( (res = internal_scopes[i]->Lookup(sym_name)) )
      return res;

  return NULL;
}

SymEntry* RVBlockNode::find_from_internal_scopes(const std::string& sym_name) const
{
  SymEntry* res = NULL;

  /* search from the last encountered scope first: */
  for(int i = internal_scopes.size()-1; i >= 0; --i)
    if( (res = internal_scopes[i]->Find(sym_name)) )
      return res;

  return NULL;
}

bool RVBlockNode::is_internal_scope(const ScopeTbl* scp) const
{
  ScopeVector::const_iterator i;
  FORVEC(i, internal_scopes) 
    if( scp == (*i) )
      return true;

  return false;
}



/*  RVFuncNode code:  */
/* ================== */

RVFuncNode::RVFuncNode(void)
{ 
  nArgs = 0; 
  argtypes = NULL;
  eq_classes = NULL;
  external = false;  // by default
  recursive = false;
  has_ellipsis_args = false;
  subtree_has_cps = false;
  indirect = false;
  is_needed = false;
  loop_2_rec = false;
  m_bAllAliased = false;
  func_flags = 0;  
  dfs_marks = 0; 
  loops_index = -1;
  max_ellipsis_args = 0;
  num_derefs_in_body_read = 0;
  num_derefs_in_body_write = 0;
}

RVFuncNode::RVFuncNode(const RVFuncNode& o)
{
  callees = o.callees;
  callers = o.callers;
  read = o.read;
  written = o.written;

  used_labels = o.used_labels;

  argtypes = NULL;
  
  if( o.argtypes ) {
    init_argtypes(o.nArgs);
    for(unsigned i=0; i<nArgs; i++) {
      argtypes[i] = o.argtypes[i];
      eq_classes[i] = o.eq_classes[i];
    }
  }

  external = o.external;
  recursive = o.recursive;
  has_ellipsis_args = o.has_ellipsis_args;
  subtree_has_cps = o.subtree_has_cps;
  indirect = o.indirect;
  is_needed = o.is_needed;
  func_flags = o.func_flags;
  loop_2_rec = o.loop_2_rec;  
  dfs_marks = o.dfs_marks;
  loops_index = o.loops_index;
  max_ellipsis_args = o.max_ellipsis_args;
  
  num_derefs_in_body_read = o.num_derefs_in_body_read; // supposed to count the depth of access to ubs, but it doesn't work currently. It counts the number of derefs, but it's not what we need. see todo list.  
  num_derefs_in_body_write = o.num_derefs_in_body_write;
  m_bAllAliased = o.m_bAllAliased;
}

RVFuncNode::~RVFuncNode()
{
  callees.delete_all();
  callers.delete_all();
  read.delete_all();
  written.delete_all();
  used_labels.delete_all();
  free_argtypes();
}

void RVFuncNode::free_argtypes(void) {
  if( argtypes )
    free(argtypes);
  if( eq_classes )
    delete[] eq_classes;
  nArgs = 0;
}

void RVFuncNode::init_argtypes(unsigned num) {
  nArgs = num;
  /* argtypes are cleared to have AT_Unknown value at the begining */
  argtypes = static_cast<ArgType*>(calloc(nArgs, sizeof(ArgType)));
  eq_classes = new std::vector<Symbol *>[nArgs];
}

void RVFuncNode::reinit_argtypes(unsigned num) {
  if( argtypes ) {
    if (num == 0 && 0 == nArgs)
      return;
    fatal_error("Error: RVFuncNode::reinit_argtypes(): argtypes where "
                "already initialized.\n", false);
    free_argtypes();
  }
  init_argtypes(num);
}

bool RVFuncNode::check_argtypes(unsigned i, const char *caller) const {
    if (argtypes != NULL && i >= 0 && i < nArgs)
        return true;

    if (has_ellipsis_args && i >= nArgs)
        return false; //just skip accessing the index without reporting an error

    std::ostringstream err;
    err << "Error in " << caller << ": ";
    if( argtypes == NULL)
        err << "argtypes == NULL.\n";
    else
        err << "index " << i << " is out of range [0, " << nArgs <<").\n";

    fatal_error(err.str().data(), false);
    return false;
}

ArgType RVFuncNode::get_argtype(unsigned i) const
{
  return check_argtypes(i, "RVFuncNode::get_argtype")? argtypes[i] : 0;
}

void RVFuncNode::switchOn_argtype(unsigned ind, ArgType type) {
    if( !check_argtypes(ind, "RVFuncNode::switchOn_argtype()") )
        return;

    if(DBG) rv_errstrm << "RVFuncNode::switchOn_argtype(" << ind << ", "
                       << argtype2string(type) <<")\n";
    argtypes[ind] |= type;
}

void RVFuncNode::switchOff_argtype(unsigned ind, ArgType type) {
    if( !check_argtypes(ind, "RVFuncNode::switchOff_argtype()") )
        return;

    if(DBG) rv_errstrm << "RVFuncNode::switchOff_argtype(" << ind << ", "
                       << argtype2string(type) <<")\n";
    argtypes[ind] &= ~type;
}

bool RVFuncNode::hasAnyArgTypes(void) const {
    return nArgs > 0 && argtypes != NULL;
}

///<summary>
/// Finds if a symbol sym is aliased to one of the parameters of a function this_func. If yes updates the index 'the_ind'
///</summary>
bool RVFuncNode::is_aliased(FunctionDef* this_func, Symbol *sym, unsigned int *the_ind , int from_ind) const
{
//    SymbolVector::const_iterator i;
    unsigned int ind;
    unsigned int start_ind;

    assert(from_ind >= -1 && from_ind < (int)nArgs);
    if (from_ind >= (int)nArgs - 1)
        return false;

    start_ind = (unsigned int) (from_ind+1);

    if (this_func->fnode.m_bAllAliased) {
        assert(this_func->decl->form->isFunction());
        while (start_ind < nArgs) {
            FunctionType *ft = static_cast<FunctionType*>(this_func->decl->form);
            if (ft->args[start_ind]->form->isPointer()) {
                (*the_ind) = start_ind;
                return true;
            }
            ++start_ind;
        }
        return false;
    }

    for (ind = start_ind ; ind < nArgs; ind++) {
        if (this_func->fnode.eq_classes->empty()) break; // ofer
        for(unsigned int j = 0; j < this_func->fnode.eq_classes[ind].size(); ++j) {
            if (this_func->fnode.eq_classes[ind][j]->entry == sym->entry) {
                //if( (*i)->entry == sym->entry ) {
                (*the_ind) = ind;
                return true;
            }
        }
    }
    return false;
}


void RVFuncNode::print_vectors( std::ostream& out, bool with_headers ) const
{
  callees.print( (with_headers ? "callees: " : NULL), out);
  callers.print( (with_headers ? "callers: " : NULL), out);
  read.print( (with_headers ? "directly read globals: " : NULL), out);
  written.print( (with_headers ? "directly written globals: " : NULL), out);
}

void RVFuncNode::sort_vectors(void)
{
  callees.unique_sort();
  callers.unique_sort();
  read.unique_sort();
  written.unique_sort();
}

void RVFuncNode::count_args(unsigned num)
{
  if( has_ellipsis_args ) {
    if( num < nArgs  )
      fatal_error("Error: too few arguments to a function with ellipsis. \n", false);
    if( (int)num - (int)nArgs > max_ellipsis_args )
      max_ellipsis_args = num - nArgs;
  }
  else if( num != nArgs  ) {
    rv_errstrm << "Error: wrong number of arguments ("<< num <<") in call, "
           << nArgs <<" arguments where expected.\n";
    fatal_error("Error: wrong number of arguments in a function call. \n", false);
  }
}


unsigned RVFuncNode::get_label_index(const FunctionDef* this_func, const Symbol* label)
  /* returns 0 on failure */
{
  CHK_NULL1(this_func && label,
        "this_func or label in RVFuncNode::get_label_index()");

  unsigned ind = 1;  /* Note: label indexes atrtr from 1 ! */
  SymbolVector::const_iterator i;
  FORVEC(i, this_func->fnode.used_labels) {
    if( (*i)->name == label->name )
      break;
    ind++;
  }

  if( i == this_func->fnode.used_labels.end() ) {
    rv_errstrm << "Internal: unable to find label \""<< *label <<
      "\" in the vector of labels used in function \""<< *this_func->FunctionName() <<"\" !\n";
    return 0;
  }

  return ind;
}

