#ifndef RV_ARRAYS_H
#define RV_ARRAYS_H

#include <rv_gen.h>
#include <rv_treecomp.h>

class RVTreeComp;


typedef std::vector<Type*> TypeVector;

class RVArrayRef : public RVCtool {
  public:
    typedef enum { AR_NONE = 0, AR_VAR = 1, AR_COMP, AR_TYPE, AR_FUNC } ARType;

    ARType ar_type;

    FunctionDef* from_func;
    Expression* orig_expr; // the original expression of array access.
    SymEntry* entry;
    SymEntry* trg_entry;
    Type*     type;        // the whole array type
    FunctionDef* ret_func; // function that returns an array.

    Type*     token_type;     // as appears in the genereated code 
    Type*     real_item_type; // if NULL - look in entry or type

    RVArrayRef();
  
    void inVar(SymEntry* _entry, Expression* ex);
    void inVar(SymEntry* _entry, FunctionDef* from, Expression* ex);
  
    void inComp(SymEntry* _entry, FunctionDef* from, Expression* ex);
    
    void inType(Type* _type, FunctionDef* from, Expression* ex);

    void inFuncRet(FunctionDef* callee, FunctionDef* from, Expression* ex);

    Type* get_orig_type();
    Type* getArrayItemType();

    bool same_as(const RVArrayRef* other) const;

    void print(std::ostream& out, bool printLocation = false) const;
};


typedef std::vector<RVArrayRef*> ARVector;

class RVArrays : public RVGenRename
{
  protected:
    RVTreeComp typecomp;

    FunctionDef* body;
    int current_side;
    const char *where;  /* func name - for debug and error prints. */
    
    Project*   orig_parsetree[2];
    TypeVector array_item_types[2];
    ARVector   array_refs[2];

    bool add_type(Type* tp);
    Type* find_array_type(Type* tp, int side);
    Type* item_type_to_token_type(Type* tp);

    std::string array_operator_func_prefix(Type* item_type);
    std::string array_access_func_name(Type* item_type);
    std::string array_operator_func_name(Type* item_type, UnaryOp op);
    std::string array_operator_func_name(Type* item_type, BinaryOp op);
    std::string array_operator_func_name(Type* item_type, AssignOp op);
    std::string array_operator_func_name(Type* item_type, RelOp op);   

    bool equalize_parsetrees(Project* pt1, Project* pt2);

    bool replace_occurrences_of_type(Project* parsetree, const Type* replace_type, Type* token_type);

  public:
    RVArrays(RVTemp& _temps);
    virtual ~RVArrays() {}

    void clear();

    void save_parsetree(Project* _parsetree, int _side);

    void set_side(int _side) {
      current_side = _side; 
    }

    // call next func before doing collect or replace on a new function:
    void init(FunctionDef* _body, int _side, const char *_where);

    bool add_ref(RVArrayRef* ref);

    RVArrayRef* get_same_ref(const RVArrayRef* ref);
    bool has_ref(const RVArrayRef* ref);

    RVArrayRef* get_array_ref(Expression* expr);
    RVArrayRef* get_array_ref(Type* orig_expr_type);

    std::string type2name(Type* tp);
    std::string type2token_name(Type* tp);

    Expression* create_item_access(Expression* it, Expression* offset);
    Expression* create_unary_call(UnaryOp op, Expression* operand);
    Expression* create_binary_call(BinaryExpr* orig);    
    Expression* create_assign_call(AssignExpr* orig);
    Expression* create_rel_call(RelExpr* orig);

    bool gen_macros_and_typedefs();

    bool gen_common_funcs_and_vars(bool decls_only);

    bool gen_side_funcs_for_type(Type* tp, bool decls_only); 

    bool gen_funcs_for_UA_types(bool decls_only);

    bool gen_prototypes();

    bool replace_array_decls_and_types(Project* parsetree, int side);
};

extern RVArrays& rv_arrays(void);



class RVCollectArrayRefs : public RVCtool
{
  protected:
    FunctionDef* body;
    int side;
    const char *where;  /* func name - for debug and error prints. */

    bool collect_array_refs_internally;
    ARVector internal_array_refs;

    bool add_array_ref(RVArrayRef* ref);
    bool internal_ref_is_array();
    bool collect_array_unary_expr(UnaryExpr* s0p);
    bool collect_array_binary_expr(BinaryExpr* s0p);
    bool collect_array_ref_rec(Expression* expr);

    void add_argtype(int ind, ArgType type);

  public:
    RVCollectArrayRefs();
    virtual ~RVCollectArrayRefs();

    void init(FunctionDef* _body, int _side, const char *_where);

    // call next function only when sure that "expr" is really an array reference:
    bool collect_array_ref(Expression* expr);

    // call to collect refs even if they may not be arrays - check them later.
    bool collect_internally(Expression* expr);

    bool collect_array_assign(AssignExpr* s0p, bool check_sides = false);
    bool collect_array_in_symbol(Symbol* sym, Expression* orig_expr, Type* real_item_type = NULL);
    bool collect_array_in_expr_type(Expression* s0p);
    bool collect_array_in_decl_type(Decl* s0p);
    bool collect_array_in_func_ret(FunctionCall* s0p);

    ARVector& get_internal_refs() { 
      return internal_array_refs; 
    }
};

#endif  /* RV_ARRAYS_H */

