/* ctool parse tree interfaces: */
#ifndef RV_CTOOL_H
#define RV_CTOOL_H

#include <ctool/symbol.h>
#include <ctool/parseenv.h>
#include <ctool/project.h>

/*
  RVCtool 
    contains static interface functions to the parse tree classes 
    of ctool library.
*/

class RVCtool
{
  public:
	static bool is_unary_change(UnaryExpr *exp); 
    static bool is_top_level(const SymEntry *se);
    static ScopeTbl* get_root_scope(Project* pt, SymEntryType entry_type = VarDeclEntry);
    static ScopeTbl* get_file_scope(Project* pt, SymEntryType entry_type = VarDeclEntry,
                                    bool exit_on_error = true);
    static ScopeTbl* get_file_tags(Project* pt);

    static bool is_global_decl( SymEntry *se );
    static bool is_global_var( SymEntry *se );
    static bool is_static_var( SymEntry *se );
    static bool is_function(const SymEntry *se );
    static bool valid_function(const SymEntry *se );
    static bool function_has_body( SymEntry *se );

    static bool is_global_var( Symbol *sym );
    static bool is_static_var( Symbol *sym );
    static bool is_function(const Symbol *sym );
    static bool valid_function(const Symbol *sym );
    static bool function_has_body( Symbol *sym );

    static SymEntry* lookup_global_var(const std::string& name, Project *pt);
    static SymEntry* lookup_function(const std::string& name, Project *pt);

    static Type* real_type(const Type *tp, const char *where);
    static bool  is_pointer(const Type *tp, const char *where, Type **ret_subType = NULL);
    static bool  is_pointer2pointer(const Type *tp);
    static BaseType *get_ptr_base(Type *tp);
    static bool  is_basetype(const Type *tp, BaseTypeSpec specific = BT_BaseMask);
    static bool  is_const_null(const Expression* exp);
    static BaseTypeSpec fix_int_mask(BaseTypeSpec mask);  // to BT_Int
    static bool isDirectPointerToFunction(Type* tp, FunctionType **ppFuncType = NULL);

    static int sizeof_type(const Type* tp );
    static int sizeof_base_type(BaseTypeSpec typemask);
    static Type* get_symbol_type(Symbol* sym, const char *where);
    static Type* get_symbol_type(SymEntry* se, const char *where);
    static int get_field_index(StructDef *def, const Variable *fld);
    static Decl* get_field_decl(StructDef *def, Symbol *sym);
    static Decl* get_field_decl(StructDef *def, const Variable *fld);
    static int get_arg_index(FunctionType *def, Symbol *arg);
    static int get_general_arg_index(FunctionType *def, Symbol *arg);
    static Decl* get_type_decl(Symbol* var_or_typedef);      
    static StructDef* get_struct_def(const Type* s0p, const char *where);
    static ScopeTbl* get_scope(DeclStemnt* s0p, const char *where);
    static Statement* get_glob_stemnt(Project* pt);
    static FunctionDef* try_get_function(Statement* st);
    static Symbol* try_var2symbol(Expression* expr);

    // removes symbol entry from a scope and returns it.
    static SymEntry* ScopeTbl_remove(ScopeTbl* scope, const std::string& name );

    static Symbol* mk_symbol(const std::string& name, SymEntry* ent);
    static Expression* mk_deref(Symbol* sym, const Location& l);
    static Expression* mk_addrof(Symbol* sym, const Location& l);
    static Decl* mk_global_decl(Project* pt, Type* form, const std::string& symname,
				SymEntryType entry_type = FctDeclEntry);
    static FunctionCall* mk_func_call(Symbol* sym, const Location& l);
    static FunctionCall* mk_func_call(const std::string& name, 
				      SymEntry* ent, const Location& l);

    static void add_strdef_component(StructDef* strdef, std::string name, Type* tp);
    static Decl* add_func_param(FunctionType* ftp, std::string param_name, Type* tp, 
                                ScopeTbl* proto_scope = NULL);
    static ScopeTbl* create_last_scope(Project* pt, int level, ScopeTbl* parent = NULL,
                                       SymEntryType entry_type = VarDeclEntry);
    static ScopeTbl* get_func_param_scope(FunctionDef* func);
    static ScopeTbl* get_func_local_scope(FunctionDef* func,  Project* parsetree = NULL);

    static SymEntry* get_same_symbol(ScopeTbl* orig_base_scp, SymEntry* orig,
				     ScopeTbl* trg_base_scp, const char* trg_prefix = NULL);


    static std::string get_where(Statement* st);
};


class RVStrIter 
{
  protected:
    StructDef* str;
    int ind; /* component index */
    Decl* comp;

  public:
    RVStrIter(StructDef* _str);

    Decl* begin();
    bool  end();
    Decl* next();
};


class HashTblIter 
{
  protected:
    HashTbl* ht;
    int slot;
    SymEntry* curr;

  public:
    HashTblIter(HashTbl* _ht);

    SymEntry* begin();
    bool end() const;
    SymEntry* next();
};


class HashTblConstIter
{
  protected:
    const HashTbl* ht;
    int slot;
    SymEntry* curr;

  public:
    HashTblConstIter(const HashTbl* _ht);

    const SymEntry* begin();
    bool end() const;
    const SymEntry* next();
};


#define BT_STD_INT (BT_Signed|BT_Int)

#endif /* RV_CTOOL_H */
