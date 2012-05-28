#if 0
#ifndef RV_TOKEN_GEN_H
#define RV_TOKEN_GEN_H

#include <rv_gen.h>


class RVStructs;
class RVStrRec;

class RVTknGen : public RVGen
{
  protected:
    RVStructs& strs;

    unsigned max_records;

    //bool gen_rv_defines();  /* including RV_TKN_NULL, Any_Token <<=== IMP */

    /* create sym_scope (create_last_scope()) for each proto <<=== DO (??)
             and add it the params of the func. */
    //bool gen_func_scope(Decl* func_decl);

    /* each func generates for both sides at once: */
    bool gen_null_tkn(RVStrRec* rec);

    bool gen_str_pack(RVStrRec* rec);
    bool gen_str_array(RVStrRec* rec); // including rv_Str_count

    bool gen_tkn_comp(RVStrRec* rec);
    bool gen_tkn_sub(RVStrRec* rec);

    bool gen_str_equalize(RVStrRec* rec);
    bool gen_str_compare(RVStrRec* rec);

    bool gen_init_arrays(RVStrRec* rec);
    bool gen_init_tokens(RVStrRec* rec);

    bool gen_tkn_drf(RVStrRec* rec);

    bool gen_str_malloc(RVStrRec* rec); /* including str_nondet() */
    bool gen_str_free(RVStrRec* rec);

    bool gen_any_token(RVStrRec* some_rec);

    bool gen_choose_step(RVStrRec* rec);

    bool gen_check_isoequal(std::vector<RVStrRec*>& all_recs);

    bool gen_assert_count_bound(std::string& strname, int side);
    bool gen_assert_eq_count(std::string& strname);

    bool gen_globals();
    bool gen_init_all_arrays();

  public:
    RVTknGen(RVTemp& _temps, RVStructs& _strs) 
      : RVGen(_temps), strs(_strs) 
      { max_records = temps.get_max_records(); }

    virtual ~RVTknGen() {}

    RVStrIter get_str_iter(RVStrRec* rec);

    bool gen_one_struct_stuff(RVStrRec* rec);

    bool gen_all();

    bool gen_copy_counts();

    bool gen_map_to_array(Type* tkntp, int side, std::string var);

    bool gen_check_counts();

    bool gen_nondet_token(std::string tknvar);
    bool gen_init_token_marks(std::string tknvar);
};


#endif /* RV_TOKEN_GEN_H */
#endif
