#ifndef RV_INDFUNC_H
#define RV_INDFUNC_H

#include <map>
#include <rv_funcnode.h>
#include <rv_walk.h>

class RVTemp;  

/* a class of funcs with the same FunctionType: */
class RVFuncClass : public RVCtool
{
  public:
    int side;
    FunctionType* type;
    SymbolVector funcs;
    SymbolVector defs; /* typedefs for this type. */

    std::string class_name;

    RVFuncClass(Type* _type, int _side);
    ~RVFuncClass();

    void sort_symbol_vectors();

    BaseType* get_enum_tp();
    Decl*     get_hub_decl(Project* pt);

    //bool change_all_defs();
    bool gen_hub_func(RVTemp& temps, Project* pt, bool with_body);

    /* convert func name to its index name in the ind_enum */
    std::string func_ind_name(std::string& func_name);

    Symbol* get_enum_sym(std::string& func_name);

    void print_info(bool pr_funcs, bool pr_type, bool pr_defs);

    static const char* TYPE_PREFIX;
    static const char* ENUM_PREFIX;
    static const char* HUB_SUFFIX;
    static const char* FI_ARG_NAME;

  protected:
    BaseType* tp_func_ind_enum; // must get thru get_enum_tp()

    Decl* hub_decl;    /* prtotype of hub function for this class */

    int add_enum_func_ind(EnumDef* def, std::string& func_name);
};

typedef std::vector<RVFuncClass*> RVFuncClassVec;



class RVIndirectFuncs : public RVWalk
{
    Project* parsetree;
    int side;

    bool fix_decl_types;

    void sort_all(int _side);
    bool one_pass();
    bool fix_func_call(Expression* expr);
    bool fix_func_pointer_decl(Decl* decl);
    bool add_hub_decls();

  public:
    RVFuncClassVec classes[2];  // for each side.

    std::map<Type*, RVFuncClass*> by_type[2];

    RVIndirectFuncs();
    virtual ~RVIndirectFuncs() {}

    void set_params(Project* _parsetree, int _side);

    bool add_func(Symbol* sym, int side);

    bool process_all(Project* _parsetree, int _side);

    virtual bool process(Expression* expr); // only FunctionCalls
    virtual bool process(Statement* s0p);   // DeclStemnts, TypedefStemnt
    virtual bool try_replace(Expression** pexpr);
    virtual bool process_function_type(FunctionType* s0p);
    virtual bool process(StructDef *s0p);
    virtual bool process_basetype(BaseType* s0p);

    /* replace func pointers by func index enums */
    virtual bool process(Decl* it);  

    /* just process these: */
    virtual bool process(SymEntry* it)  { return go(it); }
    virtual bool process(Type* it)  { return go(it); }
    virtual bool process(EnumDef* it)  { return go(it); }

    /* ignore the next parts of the code: */
    virtual bool process(Symbol* it) { return true; }
    virtual bool process_const(Constant* it) { return true; }
    virtual bool process(Label* it)   { return true; }

    RVFuncClass* get_by_type(Type* type, int side);
    RVFuncClass* get_by_func(Symbol* func_sym, int side, Location& l);

    bool find_func_pointer_typedefs(Project* pt, int side);

    /* gen func index enums: */
    bool gen_all_func_ind_enums(RVTemp& temps, Project* pt, int side);

    /* generation funcs: */
    bool gen_all_class_hubs(RVTemp& temps, Project* pt, int side, bool with_body);

    void print_info(int _side, bool pr_funcs, bool pr_type, bool pr_defs);

    static bool is_func_pointer(Type* type);
    static Type *fix_func_proto(Type *proto);
};

extern RVIndirectFuncs rv_indirect_funcs;




class RVEllipsisFix : public RVCtool
{
    Project* parsetree;
    int side;

    Type* ellipsis_arg_type;

    const char *where;
    
    /* list of old ellipsis func DeclStemnts */
    DeclStemnt *old_head, *old_tail;

    void save_old_ellipsis_decl(DeclStemnt* st);

    bool add_arg_typecasts(ExprVector& args, int first_opt_arg);

  public:
    RVEllipsisFix();

    void set_params(Project* _parsetree, int _side);

    bool replace_ellipsis_func_decl(Statement** pst);
    
    bool fix_func_call(Expression* expr);

    bool delete_old_decls();

    static std::string get_ellipsis_func_name(std::string& orig, int num_add_args);
};

extern RVEllipsisFix rv_ellipsis_fix;



#include <rv_treecomp.h>

class RVDetachPointerValue : public RVWalk
{
    RVTreeComp typecomp;

    Project* parsetree;
    int side;

    bool only_fix_types;

    /* we assume that each relevant type has its typedef - so we can name it */
    SymbolVector typesyms[2];
    HashTbl new_typedecls[2];
    DeclVector all_fix_funcs;
    
    Type* value_type;
    Type* uchar_type;

    static const char* detach_comp_names[2];

    /* component indexes in the detach struct: */
    typedef enum { P_COMP = 0 /* pointer */, 
		   V_COMP = 1 /* numeric value */ } CompInd;

    /* various functions we can call in the target code to fix constructs: */
    typedef enum { EQ_FUNC, REL_FUNC, IS_TRUE_FUNC } FixFunc;

    /* returns old types from typesym SymEntry after it was fixed. */
    Type* get_old_type(Symbol* typesym);
    SymEntry*  get_new_entry(std::string& typesym_name);
    StructDef* get_new_structdef(std::string& typesym_name);

    Symbol* find_typesym(Type* type);
    Symbol* find_expr_typesym(Expression* s0p);

    Expression* mk_member_op(Expression* orig, Symbol* typesym, CompInd comp_ind);

    Type* create_detach_struct(Symbol* sym, Type* old_type);
    Decl* create_fix_func_decl(std::string& typesym_name, FixFunc func_ind, Type* argtp);
    bool  create_all_fix_func_decls(std::string& typesym_name, Type* new_type);
    bool  try_replace_by_component(Expression** pexpr, CompInd comp_ind);
    SymEntry* find_fix_func_entry(std::string& typesym_name, FixFunc func_ind);
    Expression* gen_fix_func_call(Expression* pl, Expression* pr, 
				  FixFunc func_ind, unsigned rel_ind);
    bool one_pass();

    bool try_fix_member_op_type(Expression* s0p);;

    bool gen_det_eq_func(RVTemp& temps, std::string& typesym_name);
    bool gen_det_rel_func(RVTemp& temps, std::string& typesym_name);
    bool gen_det_2bool_func(RVTemp& temps, std::string& typesym_name);
    
  public:
    RVDetachPointerValue();
    virtual ~RVDetachPointerValue() {}
    
    void set_params(Project* _parsetree, int _side);

    void add_pointer_type(std::string typedef_name, int _side);

    bool process_all(Project* _parsetree, int _side);

    bool gen_all_fix_funcs(RVTemp& temps);

    bool connect_types(); /* find old and create new types */
    //void set_new_types(); /* set new types into typedef Decls */

    virtual bool process(Statement* s0p);
    virtual bool process(Expression* s0p) { return go(s0p); }

    virtual bool try_replace(Expression** pexpr);
    virtual bool try_replace(Type** ptp);

    /* ignore the next parts of the code: */
    virtual bool process(Symbol* it) { return true; }
    virtual bool process(Label* it)   { return true; }
    virtual bool process(LabelVector& it) { return true; }
    virtual bool process(EnumDef* it)    { return true; }
    
    virtual bool process_const(Constant* it) { return true; }

    static std::string get_fix_func_name(std::string& typesym_name, FixFunc func_ind);

    static unsigned get_rel_ind(RelOp op);
  
    /* The next funcs chosses .p or .v according to operation.
       They return true on success. */
    bool fix_unary(UnaryExpr** pexpr);
    bool fix_binary(BinaryExpr** pexpr);
    bool fix_assign(AssignExpr** pexpr);
    bool fix_rel(RelExpr** pexpr);

    bool fix_boolean(Expression** pexpr);
};

extern RVDetachPointerValue rv_detach_pointer_value;



#endif /* RV_INDFUNC_H */
