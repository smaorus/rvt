#ifndef RV_TOKENS_H
#define RV_TOKENS_H


#include <map>
#include <set>

#include <rv_ctool.h>
#include <rv_treecomp.h>


class RVRenameTree;

/* a record that concentrates all info for a single struct type: */
class RVStrRec
{
 public:
  int side;
  int otype;       /* object type index (as in enum RVStructType) */

  Type* orig_type; /* the original structure type. */

  Type* strutp;     /* its BaseType(BT_UserType). */
  Decl* strdecl;
  std::string strname;
  bool print_typedef; 

  Type* tknutp;     /* its BaseType(BT_UserType). */
  Decl* tkndecl;
  std::string tknname;

  DeclVector funcs;
  bool printed_funcs;

  RVStrRec* other_side;

  RVStrRec();

  /* rename types and decls: */
  bool rename(RVRenameTree& renamer);
};

typedef std::vector<RVStrRec*> RVStrRecVec;

class RVStructs;

class RVStrRecIndex
{
  protected:
    unsigned count;

    RVStrRecVec vec;

    std::map<std::string, RVStrRec*> by_tknname;
    std::map<Type*, RVStrRec*> by_orig_type;
    std::map<Type*, RVStrRec*> by_str_type;
    std::map<Type*, RVStrRec*> by_tkn_type;

    int my_side;

  public:
    RVStrRecIndex() { count = 0; }

    void set_side(int side) { my_side = side; }

    ~RVStrRecIndex();

    bool add(RVStrRec* rec);

    RVStrRec* get_by_tknname(std::string& tknname);
    RVStrRec* get_by_strname(std::string& strname);
    RVStrRec* get_by_orig_type(Type* orig_type);
    RVStrRec* get_by_str_type(Type* str_type);
    RVStrRec* get_by_tkn_type(Type* tkn_type);

    unsigned size() { return count; }
    RVStrRecVec& get_vec() { return vec; }
};


class SymbolVector;
class RVGlobLists;
class RVFuncPair;
class RVTemp;

typedef std::set<SymEntry*> SymEntrySet;

typedef enum { 
  NT_COMP, NT_SUB, NT_DEREF, NT_NULL,
  NT_MALLOC, NT_FREE, NT_ARRAY
} RVNameType;


class RVStructs : public RVCtool
{
  protected:
    RVGlobLists* orig_progs;
    Project*     res_parsetree[2];

    DeclVector converted[2];  // after convertion pointers ->tokens
    DeclVector str_tkn[2];    // the token struct types

    RVStrRecIndex recind[2];

    int gen_side;    // the side we currently generate for

    const char *where;  /* for debug and error prints. */

    /* Types needed in token structs: */
    EnumDef*  enum_RVStructType;
    BaseType* tp_enum_RVStructType;
    BaseType* tp_unsigned_char;
    BaseType* tp_signed_char;
    BaseType* tp_int;

    int add_enum_RVStructType(std::string& str_name);
    bool gen_token_component_types();
    SymEntry* replace_symentry(SymEntry* newent, ScopeTbl* in_scope = NULL);

    /* Type search funcs: */
    Decl* find_user_type_decl(Type* strtp, Project* pt);
    Type* get_same_type(Type* tp, Project* tree);
    Type* related_side0_type(Type* side1tp, Type* origtp1 = NULL);
    bool  search_type_tag(Type* tp, BaseType** out_strdef, std::string* out_tagname);
    bool  search_typedef(Type* tp, Decl** out_decl, std::string* out_type_name);
    
    /* gen struct typedef and tag names: */
    std::string make_struct_name_and_tag(Type* strtp, RVStrRec* rec = NULL);

    /* generation funcs: */
    StructDef* convert_struct(StructDef* strdef);
    Decl* mk_func_decl(FunctionType* ftp, RVNameType nt, 
                       std::string& name_base, bool tkn_base, RVStrRec* rec);
    bool add_new_func_decls(RVStrRec* rec);
    Decl* gen_struct_token_typedef(Decl* strdecl);
    bool process_one_struct(Decl* strdecl);
    bool process_all_structs();
    bool process_all_vars();
    bool process_all_funcs();

  public:
    static const char* TKN_SUFFIX;

    static const int tkn_suffix_len;

    static const char* MARKS;
    static const char* OTYPE;
    static const char* REALM;
    static const char* ONUM;
    static const char* ARR_IND;

    static const char* USER_TYPE_PREFIX;
    static const char* TAG_PREFIX;
    static const char* STR_ENUM_NAME;
    static const char* STR_ENUM_PREFIX;

    DeclVector  globals_mapped_to_array[2];
    SymEntrySet tokenized_var_entries[2];

    RVStructs(RVGlobLists* _orig_progs, Project* parsetree_copy[2]);
    virtual ~RVStructs();

    Project* get_res_parsetree(int side) { return res_parsetree[side]; }

    RVStrRecVec& get_rec_vec() { return recind[0].get_vec(); }

    bool process_all(int side);

    /* add side/semchk prefixes. */
    //bool rename_all(int side, RVFuncPair* semchk_pair, bool semchk_recursive);

    bool print_tkns(RVTemp& temps, int side);

    bool print_all(RVTemp& temps);

    void add_tokenized_var(Decl* what, int side);
    bool is_tokenized_var_entry(SymEntry* ent, int side);

    void set_global_where(int side);
    void set_where(const char* _where) { where = _where; }


    /* Query Functions: */
    /*==================*/
    bool is_aggregate(Type* tp);
    bool is_aggregate_pointer(Type* tp, Type** pstrtype = NULL);

    /* the next 3 functions use tag names for structs and tokens: */
    bool is_token(Type* tp);
    std::string get_token_name(Type* token_type, int side);
    std::string get_struct_name(Type* struct_type, int side);

    /* textual conversion: */
    static std::string name_token2struct(std::string& token_name);
    static std::string name_struct2token(std::string& struct_name);

    Type* get_struct_type(std::string& struct_name, int side);
    Type* get_token_type(std::string& token_name, int side);    
    
    Type* type_struct2token(Type* strtp, int side);
    
    RVStrRec* get_rec_by_tkn_type(Type* tkntp, int side)
      { return recind[side].get_by_tkn_type(tkntp); }

    // find function or var Decl in file scope.
    SymEntry* get_glob_decl(std::string& name, int side, bool is_func = true);
    bool replace_glob_vector(SymbolVector& vec, int side);

    /* various function and array names: */
    std::string gen_name_for_token(std::string& token_name, RVNameType nt, 
				   int side = -1, bool side_pref = false);
    std::string gen_name_for_struct(std::string& struct_name, RVNameType nt,
				    int side = -1, bool side_pref = false);

    /* convert struct var symbol to its corresponding var token: */
    std::string get_struct_var_name(std::string& struct_var_name);

    // DEBUG
};


/*=================*/

#include <rv_walk.h>
#include <rv_propagate.h>

class RVStructs;

class RVTokenizer : public RVWalk
{
  protected: 
    RVTreeComp comp;
    RVTypeProp prop;

    RVStructs& strs;

    FunctionDef* body;

    int current_side;
    Block* current_block;

    Location* last_Stemnt_location;

  public:
    RVTokenizer(RVStructs& _strs, int side);

    virtual ~RVTokenizer() {}

    bool process_func(FunctionDef* _body);

    Expression* gen_token_compare(Expression* tkn1, Expression* tkn2, const Location& l);
    Expression* gen_token_rel(Expression* tkn1, Expression* tkn2, RelOp rOp, const Location& l);
    Expression* gen_compare_null(Expression* tkn, Type* orig_type, const Location& l);
    Expression* gen_null_token_expr(Type* strtp, int side, Location& l);

    FunctionCall* gen_func_call(Type* tkntype, RVNameType nt, int side, const Location& l);
    FunctionCall* gen_func_call(FunctionCall* fc, Type* strtype, 
                                RVNameType nt, int side = -1);

    /* check for array indexing: a[i]  and p+i ... */
    virtual bool process(Expression* it);
    virtual bool process(Statement* it);         // save DeclStemnt's location. 

    virtual bool process_binary(BinaryExpr* it); // rep ->

    virtual bool try_replace(Expression** pit);  // malloc() call, unary, binary
    virtual bool try_replace(Decl** pit);        // rep Str and Str* var decl
    virtual bool try_replace(Type** pit);        // rep symbol types

    bool try_replace_binary(BinaryExpr** pit);   // rep =malloc(), RelExp
    bool try_replace_unary(UnaryExpr** pit);     // &, !tkn
    bool try_replace_rel(RelExpr** pit);         // ==, != <, >, <=, >=, == between str poi

    bool try_replace_funccall(FunctionCall** pit, Type* struct_type); // malloc

    Expression* gen_token_deref(Expression* it, bool object_pointer = true);

    /* ignore: */
    virtual bool process(Label* it)   { return true; }
    virtual bool process(EnumDef* it) { return true; }
};


#endif /* RV_TOKENS_H */
