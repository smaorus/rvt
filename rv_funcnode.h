#ifndef RV_FUNCNODE_H
#define RV_FUNCNODE_H

class Symbol;

int compSymbol(Symbol *pa, Symbol *pb);


class SymbolVector : public std::vector<Symbol*>
{
  public:
    void remove_doubles();

    /* remove items common to this and other vectors: */ 
    void filter_common(const SymbolVector& other, bool keep_common = false);

    void unique_sort(void);  /* sort and remove doubles. */

    void add_dup(const SymbolVector& other); /* add duplicates of symbols on other */

    bool has_item(const Symbol* sym) const; /* has exactly the sym pointer. */

    Symbol* find(const std::string& name) const;

    /* find global symbol with same name or related through equalTo: */
    Symbol* find_related(Symbol* symbol, int symbol_side = -1) const;

    bool all_related(const SymbolVector& other) const;

    void print( const char *header, std::ostream& out) const;

    void delete_all(void);
};


/* Argument Types */

typedef unsigned char ArgType;

const ArgType AT_Unknown  = 0x00;
const ArgType AT_In       = 0x01;
const ArgType AT_Out      = 0x02;
const ArgType AT_Deref    = 0x04; /* is dereferenced in the function */
const ArgType AT_Array    = 0x08;
const ArgType AT_Ain	  = 0x10; /* Abandoned input */
const ArgType AT_Aout	  = 0x20; /* Abandoned output */

std::string argtype2string(ArgType at);


class FunctionDef;
class ScopeTbl;
class RVLoop;

typedef std::vector<ScopeTbl*> ScopeVector;

/* RVBlockNode
     is used by uninterpreted scopes - currently loop blocks.
     Contains in/out info for vars which are used in the block
     but defined out of the block.
*/

class RVBlockNode
{
  public:
    SymbolVector vars, pvars;  /* externally defined local vars. */
    SymbolVector labels;       /* all goto labels with dest in the block */

    RVLoop* loop_rec;
    
    ScopeVector internal_scopes;

    RVBlockNode(void);
    ~RVBlockNode(); 

    void sort_vectors(void);
    void print_vectors( std::ostream& out, bool with_headers ) const;

    /* Note: invars and outvars vectors must be sorted before using the next funcs: */
    bool is_in_var(const std::string& name) const  { return( vars.find(name) != NULL ); }
    bool is_p_var(const std::string& name) const { return( pvars.find(name) != NULL ); }

    void add_internal_scope(ScopeTbl* scp);
    SymEntry* lookup_internal_scopes(const std::string& sym_name) const; // returns NULL if not found
    SymEntry* find_from_internal_scopes(const std::string& sym_name) const;
    bool is_internal_scope(const ScopeTbl* scp) const;
};



/* RVFuncNode
     a single node in the call graph.
     Beside callers/callees info contains also 
     vectors of global symbols which are written 
     or read in the function.
*/

class RVFuncNode
{
    ArgType* argtypes;

  public:
    SymbolVector callees;
    SymbolVector callers;
    SymbolVector read;     /* global vars */
    SymbolVector written;    

    SymbolVector used_labels; /* all labels to which there is a goto */

    unsigned nArgs;
    std::vector<Symbol *>  *eq_classes;
	bool   m_bAllAliased; //Overapproximation that every pointer is aliased to every pointer - when RVCollect::mark_aliased() has encoutered a case it does not maintain

    bool   external;         /* has no body */
    bool   recursive;
    bool   loop_2_rec;
    bool   has_ellipsis_args;/* f.e. int scanf(const char *format, ...); */
    bool   subtree_has_cps;  /* function or successors has a checkpoint in their code. */
    bool   indirect;         /* may be called thru pointer */
    bool   is_needed;        /* used to mark cone of influence ... */

    unsigned func_flags;     /* set by user (see rv_funcflags.h) */    

    long   dfs_marks;

    int    loops_index;

    int    max_ellipsis_args;

    int    num_derefs_in_body_read, num_derefs_in_body_write;

    /* Note! when you add data members - update copy constructor! */

    RVFuncNode(void);
    RVFuncNode(const RVFuncNode& o); 
    ~RVFuncNode();

    void reinit_argtypes(unsigned num);
    void sort_vectors(void);

    void print_vectors( std::ostream& out, bool with_headers ) const;

    void count_args(unsigned num);
    
    ArgType get_argtype(unsigned i) const;
    void switchOn_argtype(unsigned i, ArgType type);
    void switchOff_argtype(unsigned i, ArgType type);
    bool hasAnyArgTypes(void) const;
    bool is_in_arg(unsigned i) const { return( (get_argtype(i) & AT_In) != 0 ); }
    bool is_out_arg(unsigned i) const { return( (get_argtype(i) & AT_Out) != 0 ); }

    bool has_body() const { return !external; }
    bool has_loops() const { return( loops_index >= 0 ); }

    void print(int side);

    static unsigned get_label_index(const FunctionDef* this_func, const Symbol* label);
    bool is_aliased(FunctionDef* this_func, Symbol *sym, unsigned int *the_ind, int start_ind) const;

  private:
    bool check_argtypes(unsigned i, const char *caller) const;
    void init_argtypes(unsigned i);
    void free_argtypes(void);
};



#endif /* RV_FUNCNODE_H */
