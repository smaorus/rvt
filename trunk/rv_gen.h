#ifndef RV_GEN_H
#define RV_GEN_H

#include <rv_parse.h>
#include <rv_funcnode.h>
#include <rv_traversal.h>
#include <rv_genctx.h>
#include <rv_semchecker.h>
#include <vector>
#include <list>

class RVTemp;
class SymbolVector;
class RVArrayRef;
class RVMain;
class RVGenCtx;
class RVRenameTree;


#define COPY_VAL COPY_S0_to_S1
class RVGen : public RVCtool
{
  public:
	typedef enum {
	  NO_OP=0,
	  NONDET, //Single lane; used to assign nondet() to globals in main() and (in -mt only) to the outputs of UF1 when the corresponding call was not found on side 0
	  NONDET_SAVE, //Two lanes; used in -mt only to form: lane0 = lane1 = nondet().
	  COMPARE, //Two lanes; used in -mt only to compare the input arg/global of UF1 to those recorded for side 0.
	  COPY_S1_to_S0, // Two lanes; make arguments equal by copying side 1 to side 0
	  COPY_S0_to_S1, // Two lanes; copy value returned by S0 in the UF, to side 1
	  ASSERT_EQ, // Two lanes; assert outputs are equal
	  ASSIGN_NULL, // As many lanes as in ALLOC; Assign NULL to a pointer
	  ALLOC,	// Single lane; Allocate memory
	  ADD		// Single lane; Used in gen_side0/1_cbmc_uf to collect the list of arguments of a function - does not generate code directly
	} ItemOp;

	RVGen(RVTemp& _temps);
	virtual ~RVGen();

	void set_ubs_depth(int k) { ubs_depth = k; }

	virtual std::string convert_type(std::string type_text, const RVSide& side);

	static unsigned item_lane() { return 0; }

	void set_read_only_globals(SymbolVector vec[2]);
	bool ignore_in_global(Symbol* sym, int side);

	void set_look_back(int _look_back)
	  { look_back = _look_back; }

	void setMain(RVSemChecker *pMain) { m_pSemChecker = pMain; }

	static void add_prefix_to_type(const char* prefix, Type* form);

  protected:
	RVTemp&    temps;
	int        indent;
	int        local_count;

	int        look_back;

	const char *m_where;  /* func name - for debug and error prints. */
	RVSide     current_side;
	bool       first_compare; 

	int        ubs_depth;
	bool dont_alloc_root;

	SymbolVector read_only_globals[2];

	RVSemChecker* m_pSemChecker;

	virtual std::string item_prefix();

	bool unnamed_arg(Decl* decl0, Decl* decl1, int arg_index, bool warn = false);

	void gen_decl(Type* print_type, const char* prefix, Symbol* orig_sym, std::string& by);
	void gen_decl_w_side(Type* print_type, const char* symPrefix, Symbol* orig_sym, std::string& by);
	void gen_decl_low(Type* print_type, const char* prefix, Symbol* orig_sym, const RVSide* pSide, std::string& by);

	bool protect_pointer(ItemOp op, int depth, RVGenCtx& ctx, bool& out_continue, std::string& by);
	bool localize_and_alloc_pointer(ItemOp op, int depth, RVGenCtx& ctx, std::string& by);

	virtual bool gen_single_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth = -1);
	virtual bool gen_simple_component_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth = -1);
	virtual bool gen_struct_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth = -1);
	virtual bool gen_item_or_struct_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth = -1);

	void add_side_prefix_to_type(Type* form) const;

	ArrayType *ptr_2_array_types(Symbol *sym, PtrType *pt_type, int sz) const;
	void gen_ptr2array_decl(Type *arrType, Type *ptrType, Symbol *arr, std::string& by);

	bool isProcessingRoot(int depth) const;

	bool is_aggregate;
	
	struct vars{
		std::string name;
		std::string type;		
		bool is_pointer;
		bool is_aggregate;	
		bool is_array;
		int  array_size;
	} tmp_var;

	std::vector<struct vars> m_vars;

};



/*
  RVGenRename
	base type for renaming global ids before generation.
*/

class RVGenRename : public RVGen
{
  protected:
	RVRename*   ren[2];
	RVRenameTree *m_apRenTree[2];

  public:
	RVGenRename(RVTemp& _temps);    
	RVGenRename(RVTemp& _temps, Project* _sides[2]);
	virtual ~RVGenRename();

	void set_rens(Project* _sides[2], RVRenameTree *apRenTree[2]);
	virtual std::string convert_type(std::string type_text, int side);

  private:
	void init_ren(Project* prj, const RVSide& side);
};



/*
  RVUFGen
	generator of Uninterpreted Functions. Also genertes their arrays
	for saving input/output data.
*/
class RVFuncPair;
class RVArrayRef;
class RVTextFileBuffer;
class RVFuncCallCountAnalysis;

class RVUFGen : public RVGenRename
{
  protected:
		
    RVFuncPair *pfp;
    std::vector<std::string> UF_names, array_out_names, array_in_names;
    std::string uf_strname[2];
    std::list<std::string> uf_name_list;

    Decl *related_side0_global(Symbol *glob, bool in);
    Decl *related_side0_arg(int arg_num);
    RVArrayRef *try_get_ua_ref(Decl *decl);
    Type *try_get_ua_token_type(Decl *decl);
    Type *try_get_ua_item_type(Decl *decl);
    bool gen_uf_item_decl(Decl *decl, bool in, bool out, unsigned  & rNumUfStructItems);
    virtual std::string item_prefix();
    bool is_in_arg(unsigned  i);
    bool is_out_arg(unsigned  i);
	bool is_Aout_arg(unsigned i);
    void gen_no_aliasing_assertions(FunctionType *proto);
    bool gen_uf_array();
    virtual void gen_reach_equiv_flag(unsigned & ) {}

    void gen_side0_cbmc_uf(int counter);
    void gen_side1_cbmc_uf(int counter);

    bool gen_side0_uf();
    bool gen_side1_uf(bool seq_equiv_to_cps);
    virtual void gen_one_uf_in_both_sides(bool seq_equiv_to_cps);
    virtual bool gen_input_found_case(const FunctionType *proto1, const std::string& item_pref, const SymbolVector *vec, const std::string *pretvar);
    virtual bool gen_input_not_found_case(const FunctionType *proto1, const SymbolVector *vec, const std::string *pretvar, bool gen_seq_equiv_code);
    virtual std::string get_on_found_action(unsigned look_back_, const std::string& item_pref) const;

	virtual void generate_channel_inits(void);
	virtual void generate_channel_compares(void);
	
	void arr_save_in(int counter, unsigned int max_records, int i, std::string& arr_save_decl, std::string *arr_save_assign);
	void arr_out(int counter, unsigned int max_records, int i, std::string arr_p, std::string& arr_out_decl, std::string *arr_out_save_assign, std::string& arr_P_out);
	std::string arr_out_name(int counter, int call_counter, std::string name, int side);
    virtual bool determineK(RVFuncCallCountAnalysis& a,
    		                SymEntry* const startFunc,
     		                RVTextFileBuffer& ofBuf) const;

public:
    RVUFGen(RVTemp &_temps);
    virtual ~RVUFGen() {}

    void gen_ufs(bool seq_equiv_to_cps);
    void gen_dummies(bool in);
    void gen_one_uf(RVFuncPair *pfp, bool seq_equiv_to_cps);
	void generate_aux();
	virtual void determineLoopBackDepths(const std::string& ofpath, RVMain& main) const;
};



class RVReUfGen : public RVUFGen {
public:
	RVReUfGen(RVTemp& _temps);
	virtual ~RVReUfGen() {}

protected:
	virtual void gen_reach_equiv_flag(unsigned &rNumUfStructItems);
    virtual bool gen_input_found_case(const FunctionType *proto1, const std::string& item_pref, const SymbolVector *vec, const std::string *pretvar);
    virtual bool gen_input_not_found_case(const FunctionType *proto1, const SymbolVector *vec, const std::string *pretvar, bool gen_seq_equiv_code);
    virtual std::string get_on_found_action(unsigned look_back_, const std::string& item_pref) const;
	virtual void generate_channel_inits(void);
	virtual void generate_channel_compares(void);
    virtual void gen_one_uf_in_both_sides(bool seq_equiv_to_cps);
};

#include <rv_funcdfs.h>


class RVMainGen : public RVGenRename
{
  protected:
	const std::string& main_name;
	RVFuncPair   *main_pair;
	FunctionType *proto0, *proto1;  // may be tokenized prototypes

	Project *sides[2];    
	RVGlobDfs globdfs[2];
	const char* arg_prefix[2]; /* when different args (output/struct)
				  are needed */	

	bool has_retvar;

	bool is_in_arg(unsigned i);
	bool is_out_arg(unsigned i);
	bool is_aggregate_arg(unsigned i);
		
	std::string get_type_text(Decl* decl, int side);
	std::string get_type_text(Type* form, int side);
	void gen_pointer_declaration(char side, Decl *decl);
	void gen_arg_decl();
	void gen_arg_alloc();
	void gen_arg_alloc_side(FunctionType *proto, const RVSide& side);

	FunctionType* get_main_proto(int side);

	virtual bool gen_struct_op(ItemOp op, RVGenCtx& ctx, std::string& by, int depth = -1);

	bool gen_equal_nondet_globals();
	bool gen_main_call(const RVSide& side, bool check_output);
	bool old_gen_args_equality(int nItems, Decl **items0, Decl **items1, bool before); //temporary
	bool gen_args_equality(int nItems, Decl **items0, Decl **items1, bool before);
	bool gen_globals_check_output();

  public:
	RVMainGen(RVTemp& _temps, Project* _sides[2], const std::string& _main_name);
	virtual ~RVMainGen() {}

	bool check_mains(bool semchk);
	void gen_main(bool reach_eq_chk);


	RVFuncPair* get_main_pair() { return main_pair; }
};


class RVSemCheckException {
public:
	RVSemCheckException(const char *msg) : m_msg(msg) {}
	const char *getMsg(void) const { return m_msg; }
private:
	const char *m_msg;
};

#endif  /* RV_GEN_H */
