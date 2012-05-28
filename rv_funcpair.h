#ifndef RV_FUNCPAIR_H
#define RV_FUNCPAIR_H

#include <list>
#include <set>
#include <rv_ctool.h>
#include <rv_tuple.h>
#include <rv_parse.h>
#include <ctool/stemnt.h>
#include "rv_dbg.h"


class Location;
class SymEntry;
class Project;
class RVSide;


/* Equality decision params (for decide_equality() and decide_equality()): */
struct RVDecisionParams
{
  bool allow_different_callees; /* = allow semchk even if callee(s) equality is unknown */
  bool extern_funcs_are_ufs;    /* assume external functions (without body) are UFs 
				     if they have the same prototype */
  bool allow_cps_in_ufs;        /* convert funcs to UFs even if they or their subtrees
				    contain check-points (CPs). These CPs are checked by 
				    access check during semchks*/
  bool allow_ubs;               /* allow UnBounded Structures in UFs */
  const std::set<int>* pIdsOfUfs_0;  /* verbous indices of the functions on side 0 to be converted to UFs */
  const std::set<int>* pIdsOfUfs_1;  /* verbous indices of the functions on side 1 to be converted to UFs */

  /*-------- If you are adding a new field, please, initialize it in the c-tor ---------*/

  RVDecisionParams(void);

  friend std::ostream& operator<< (std::ostream& out, const RVDecisionParams& rvdec);

  bool isSymEntryAmongIds(const SymEntry *se, const RVSide& side) const;

private:
  void print(std::ostream& out) const;
};


/* RVFuncPair - 
     a record for a single pair of functions on different sides,
     which should have identical prototype and name.
     These functions may become later uninterpreted.
     Includes the function name, pointers to function bodies,
     equality status, whether they should be converted to UF,
     and their origin (file or autodetected).
*/

class RVFuncPair : public FunctionDef, public RVCtool
{  
  protected:
    void init();

    unsigned    nArgs;
    ArgType*    united_argtypes;
	bool abandone_retval;

    bool ok_uf_struct_param(BaseType *tp, const char *where, bool allow_ubs);
    bool ok_uf_param(Symbol *sym, Type *tp, const char *where, bool allow_ubs);

  public:
    typedef enum { UNKNOWN=0, FUF, AUF, REL, AUTODETECT } OriginType;

    std::string name;
    std::string side_name[2];
   
    FunctionDef *side_func[2];  /* function bodies */

    OriginType  origin;

    bool        are_related;  /* have same prototype and globals. */

    bool        equal_syntax;

    // DIMA_DEL bool        needs_semantic_check;  /* should do semantic check on it */
    // DIMA_DEL bool        done_semantic_check;   /* have done a semantic check */
    bool        equal_semantics;
    
    // DIMA_DEL bool        side0_fully_equal;
    // DIMA_DEL bool        equal_if_mscc;         /* equal if all other funcs in its MSCC are */
    //bool        equal_with_subtree;

    // DIMA_DEL bool        has_check_successor;   /* has any "syntactically different, check now" successors. */

    bool        make_uf;

    // DIMA_DEL int         check_sons;  /* number of sons which need semanic check (pairs counted twice) */
    // DIMA_DEL int         diff_sons;   /* number of different sons (pairs counted twice) */

    /* Note! when you add data members - update copy constructor and init()! */

    RVFuncPair(std::string ufname, std::string s0name, std::string s1name, Location& loc);
    RVFuncPair(std::string ufname, Location& loc);
    RVFuncPair(const RVFuncPair& o);

    ~RVFuncPair();

    void set_body( FunctionDef* def, int side );
    bool connect2bodies( Project *sides[2] );
    void compare_syntax();

    /* for a arg or global used in a func get related one on other side: */
    Symbol* related_other_side_global(Symbol* glob, int other_side, bool in);
    Decl*   side_arg(int arg_num, int _side);

    SymEntry* mk_side_entry(std::string _side_name);

    ArgType get_united_argtype(unsigned i);
    bool    unite_argtypes();

    bool has_ok_params(bool warn_output_only_funcs, bool ignore_globals, 
		       bool allow_ubs = false);

    bool has_cps_in_subtrees();

    bool can_be_uf(RVDecisionParams& params);
    bool can_compare_semantically(bool allow_ubs);

    // void passed_semantic_check(bool check_result);

    bool decide_equality(FunctionDef* check_son, FunctionDef* diff_son, 
			 int side, RVDecisionParams& params);

    bool decide_uf(std::ostream* print_results_to, 
		           const RVDecisionParams& params, const RVFuncPair* main_pair);

    bool equal_with_mscc();
    void set_equal_semantics(bool v) { equal_semantics = v; }
    bool is_equal_semantics(void) const { return equal_semantics; }

    bool valid_pair(void) const { return are_related; }
    bool have_bodies(); // both sides
    bool no_bodies();   // both sides

    bool is_auto()  { return( origin == AUTODETECT ); } /* was autodetected */
    bool is_uf()    { return make_uf; }
    bool is_needed();  /* is needed for current code generation */
    unsigned get_func_flags(int side = -1);

    bool has_united_argtypes() { return(united_argtypes != NULL); }

	bool abandone_output(int i); 

    static bool eq_globals(FunctionDef* f0, FunctionDef* f1,
			   bool try_relate_by_func_expr = false);
    void print(std::ostream& out) const;
    bool parse_uf_qualifiers(const std::list<std::string>& tokens,
    		                 const std::list<Location>& uflocs);
    friend std::ostream& operator<< ( std::ostream& out, const RVFuncPair& pair );

  private:
    bool isIdFoundInAnySet(const std::set<int>& ids_0, const std::set<int>& ids_1) const;
	void reallocUnitedArgTypes(unsigned int nTypes);
};

typedef std::vector<RVFuncPair*> RVFuncPairVec;



/* RVFuncPairList -
     the collection of all paired functions between the sides.
     Reads and writes auf file, detects related funcs,
     collects their bodies, and decides which functions
     are converted to UFs.
*/

class RVFuncPairList : public RVCtool
{
  protected:
    //bool use_auf;
    HashTbl  sideTbl[2]; /* hash of RVFuncPairs by the name on each side. */

    std::string main_name;
    RVFuncPair* main_pair;

  public:
    RVFuncPairList();
    ~RVFuncPairList();

    RVFuncPair* lookup(const std::string& name, const RVSide& side) const;
    /* return only valid pairs: */
    RVFuncPair* lookup_valid(const std::string& name, const RVSide& side) const;
    /* return only valid pairs where both side functions has bodies (not external): */
    RVFuncPair* lookup_have_bodies(const std::string& name, int side);

    RVFuncPair* new_pair(std::string ufname, std::string s0name, 
			 std::string s1name, Location& loc, 
			 RVFuncPair::OriginType orig);    

    void add_rec( SymEntry *rec, int side );
    bool del_pair(RVFuncPair*  pfp);
    bool del_pair(SymEntry *se0,SymEntry *se1);

    /* connect all pairs to the bodies of the functions on both sides. */ 
    bool connect_all( Project *sides[2] );

    /* syntactic compare between the sides of each pair: */
    void compare_syntax_of_all_aufs();

    bool decide_ufs_fname(const std::string& flname,
		                  const RVDecisionParams& params, const RVFuncPair* main_pair);

    void visitAllFunctions(RVGlobLists& parser, bool extern_funcs_are_ufs);

    bool are_related( std::string& name0, std::string& name1 );
    bool are_related( Expression *s0p, Expression *s1p );

    bool is_uf(const std::string& fname, const RVSide& side) const;

    RVFuncPair* first_to_check(bool allow_different_callees, RVDecisionParams& params);

    RVBoolStatus read_fuf_file(const std::string& flname);
    RVBoolStatus read_auf_file(const std::string& flname);
    RVBoolStatus read_rel_file(const std::string& flname);

    //void set_use_auf(bool _use_auf);
    void set_main_name(std::string& name);

    RVFuncPair* get_main_pair();
   
    RVFuncPair* getFuncPairById(int id, int side, bool mustFind) const;

    bool isFuncPairSemanticallyEqual(int id, int side) const;

    HashTblIter get_func_pair_iter(int side);

    void prepareDecompositionData(Project *side0, // In
						 		  Project *side1, // In
								  std::list<Edge>& edges0, std::list<Edge>& edges1, /*Out*/
                                  std::list<Match>& mapf, /*Out*/
                                  std::list<int>& syntacticEquivList0, /*Out*/
								  std::vector<std::string>& names0, /*Out*/
								  std::vector<std::string>& names1, /*Out*/
								  std::list<int>& loopFuncs0, /*Out*/
								  std::list<int>& loopFuncs1 /*Out*/);
	 
  protected:
    bool check_callees(RVFuncPair* pfp, int side, bool allow_different_callees);
    void buildEdgeList(ScopeTbl* fs0, 
		               ScopeTbl* fs1, 
		               std::list<Edge>& side0, 
					   std::list<Edge>& side1);
	void buildNameList(ScopeTbl* fs0, 
		               ScopeTbl* fs1, 
		               std::vector<std::string>& names0, /*Out*/
					   std::vector<std::string>& names1, /*Out*/
					   std::list<int>& loopFuncs0, /*Out*/
					   std::list<int>& loopFuncs1 /*Out*/);
    void appendCallEdges(ScopeTbl* fs, int side, std::list<Edge>& edges) const;
	void appendFuncNames(ScopeTbl* fs, 
		                 int side, 
		                 std::vector<std::string>& names, /*Out*/
						 std::list<int>& loopFuncs /*Out*/) const;
								 
	bool funcNodeFilterForBuildingEdgeList(const SymEntry* se) const;
	void addFuncName(const SymEntry *func, int side, std::vector<std::string>& names) const;

  private:
    bool detect_equal_prototypes(ScopeTbl* fs0, ScopeTbl* fs1, bool extern_funcs_are_ufs);
	void preDetectEqualPrototypes(ScopeTbl* fs0, ScopeTbl* fs1);
	void preDetectEqualPrototypesOnSide(ScopeTbl* fs, int side);
	RVBoolStatus read_uf_file(const std::string& fname, RVFuncPair::OriginType orig);
    void decide_ufs_fstrm(std::ostream* print_results_to,
		                  const RVDecisionParams& params, const RVFuncPair* main_pair);
};

extern RVFuncPairList rv_ufs;

#endif /* RV_FUNCPAIR_H */

