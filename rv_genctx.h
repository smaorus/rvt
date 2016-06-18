#ifndef RV_GENCTX
#define RV_GENCTX

#include <memory>

class Symbol;
class RVTemp;
class SymbolVector;
class RVArrayRef;
class RVGen;
class RVSide;

///<summary>
/// When generating the code, we either make an assignment (x=y), check equivalence (x==y), assign nondetvalue, assume, etc. 
/// Each of these operations is an element of ItemOp.
/// The operation is done in a context of one or two elements (x,y in the example above).
/// Each element is called a 'lane', ane RVGenCtx has a vector 'lanes' which maintains each of them. It maintains other information, such as if this is an input or global.
/// The first elements ('x') is known by the name 'item' and the second by the name 'var'.
/// The information about the context (the lanes) is given through different constructors. 
/// When generating side 0 UF, for example, we assign x = <uf prefix>_x;  hence 'x' is the name on both sides, i.e., the item and the var, and hence we need a constructor
/// with parameters corresponding to the item only. When generating side 1, we can have x1 = <uf prefix>_x  (because x1 on side 1 was mapped to x on side 0), hence we 
/// need separate data on the item and the var.
///</summary>
class RVGenCtx : public RVCtool
{
  protected:
	class Lane {
	  public:
		Type* tp;  // item type (subType for pointers and arrays)
		TypeType typetype; // to know when it is pointer or array
		std::string name;
		RVSide side;
		std::string pref;
		bool  localized;
		RVArrayRef* ua_ref;
		std::string old_full_name;
		bool is_array;
		int array_size;
		array_item *the_arr;

		Lane(Type* _tp, TypeType _tt, 
			 std::string _name, const RVSide& _side,
			 std::string _pref , bool is_array, 
			 int arr_sz, array_item *the_arr) :
			 tp(_tp), typetype(_tt), 
			 name(_name), side(_side),
			 pref(_pref), localized(false), 
			 ua_ref(NULL), old_full_name(_name),
			 is_array(is_array),array_size(arr_sz),
			 the_arr(the_arr)
		{ /* nothing */ }
	};

  protected:
	std::vector<Lane> lanes;
	bool input;
	bool m_unitrv;
	RVGenCtx* my_parent; // ofer: if we expand a (possibly recursive) structure, then the root is NULL and the others are the contexts of their parents in this structure.  seems to be NULL unless the context is a field in a struct. 

	int 
		my_comp_num, // ofer: component = field (?). Hence this is the field index in case it is a field of a struct 
		my_item_num; // ofer: if the field is a pointer, this is the depth into the list (?)

	const char *where;
	const RVSide& m_side;
	const RVGen* m_pRenamer;
	
	static unsigned local_var_count; // Note! - non reentrant
	
  private:
	void add_lane(Lane& l);

  protected:
    virtual RVGenCtx* cloneCtx(void) const;

	void check_lane(unsigned lane, const char* caller) const;
	void check_inited(const char* caller) const;

	Decl* find_comp(unsigned lane, unsigned comp_num, unsigned item_num);
	static std::string expand_name(const std::string& parent_name, Decl* comp, bool is_pointer);

    std::string get_print_type_with_side(Type *, const RVSide&, Symbol *sname) const;

  public:
	RVGenCtx(const char *_where, bool in, bool unitrv, const RVGen* pRenamer = NULL, const RVSide& = NO_SIDE);

	/* to add a UF action pair: */
	RVGenCtx(Symbol * sym,
			 Type* item_tp,
			 const std::string& item,
			 const std::string& item_pref,
			 Type* var_tp,
			 const std::string& var,
			 const RVSide& var_side,
			 bool in,
			 bool global,
			 const char *_where,
			 const RVGen* pRenamer,
			 bool unitrv);
	
	/* for side0 UFs: */
	RVGenCtx(Symbol * sym,
			 Type* side0_tp,
			 const std::string& side0_name,
			 const std::string& item_pref,
			 bool in,
			 bool global,
			 const char *_where,
			 const RVGen* pRenamer,
			 bool unitrv);

	/* to add a UF action pair: */
	void init_uf_ctx(Symbol *sym,Type* item_tp, const std::string& item, const std::string& item_pref, Type* var_tp, const std::string& var, const RVSide& var_side, bool in, bool global, const char *_where);

	const char* get_prefix( bool global, Symbol * sym, const RVSide &var_side );


	void add_lane(Symbol *sym, Type* tp, const std::string& name, const RVSide& side = NO_SIDE, const std::string& prefix = std::string(""));

	unsigned var_lane() const;

	std::auto_ptr<RVGenCtx> dup_for_struct_item(unsigned comp_num, unsigned item_num);
	// for pointer-to-pointer items:
	std::auto_ptr<RVGenCtx> create_derefed_ctx(void);

	bool localize_lanes();

	unsigned get_width() const { return lanes.size(); }
	RVGenCtx* parent() const  { return my_parent; }

	bool is_input() const { return input; }
	bool is_aggregate(void) const; /* struct or union */
	bool is_union() const;
	bool is_pointer2pointer() const;
	bool is_long() const;
	void throw_on_void_pointer(void) const;

	unsigned get_size() const;

	std::string get_print_type(unsigned lane) const ;
	static std::string get_print_type_basic(const Type *print_type, Symbol *sname);

	Type* get_nominal_type(unsigned lane) const;
	Type* get_real_type(unsigned lane) const;
	bool isFuncPtrSubstitution(unsigned lane, Type **ppRealType = NULL) const;
	bool is_pointer(unsigned lane) const;
	bool var_is_pointer() const;
	bool is_array(unsigned lane) const;
	bool is_new_array(unsigned lane) const;
	array_item *get_arr_item(unsigned lane) const;
	int  new_array_size(unsigned lane) const;
	bool is_ua(unsigned lane) const;    // uninterpreted array
	const std::string& get_name(unsigned lane) const;
	const RVSide& get_side(unsigned lane) const;
	std::string get_prefix(unsigned lane) const;
	bool is_localized(unsigned lane) const;	
	int get_nComponents();
	std::string get_full_name(unsigned lane) const; /* with prefix */
	std::string get_old_full_name(unsigned lane) const;

	RVArrayRef* get_ua_ref(unsigned lane) const;

	bool check_out_arg(unsigned lane) const;

	static void reset_local_var_count() { local_var_count = 0; }
	
	void set_unitrv( bool unitrv );
	bool was_variable_declared_globally_for_both_sides( Symbol* sym );

};

#endif
