/* Functions to generate func and structs for Regresion Verification tool output */

#include <sstream>
#include <rv_error.h>
#include <rv_consts.h>
#include <rv_temps.h>
#include "rv_side.h"

using namespace std;


const std::string uf_retvar("retval");
const std::string rv_counter_type("int");

const char* RVTemp::RV_CHANNEL_UT = "RVChannel";
const char* RVTemp::RV_CHANNEL_TAG = "rv_channel";
const char* RVTemp::NULL_TEXT = "(void*)0";

static RVDischarger dummyDischarcher;

RVTemp::RVTemp(void)
  : glob_fstream(foutstream),
    outstreamP(NULL), declarationsStreamP(NULL),
    assertStreamP(NULL), codePartStreamP(NULL),
    max_records(32)
{
}

RVTemp::RVTemp(std::ostream& strm)
  : glob_fstream(strm),
    outstreamP(&glob_fstream), declarationsStreamP(&glob_fstream),
    assertStreamP(&glob_fstream), codePartStreamP(&code_uf_stream),
    max_records(32)
{
}

RVTemp::~RVTemp() {
    flush();
	discharge(dummyDischarcher);
}

bool RVTemp::open(RVDischarger& discharger,
		          const std::string& filename,
		          std::ios_base::openmode openmode)
{
	if (outstreamP != NULL) {
		rv_errstrm << "RVTemp::open(" << filename << ") called when outstream != NULL\n";
		discharge(dummyDischarcher);
	}

	foutstream.open(filename.data(), openmode);
	bool opened = foutstream.is_open();
	if (opened) {
		outstreamP = declarationsStreamP = assertStreamP = &glob_fstream;
		codePartStreamP = &code_uf_stream;
		discharger.addDischargee(*this);
	}
	return opened;
}

void RVTemp::discharge(RVDischarger& discharger) {
	if (outstreamP != NULL) {
        outstreamP->flush();
		foutstream.close();
		outstreamP = declarationsStreamP = assertStreamP = NULL;
	}
}

void RVTemp::close(RVDischarger& discharger) {
	discharge(discharger);
	discharger.removeDischargeeByPtr(this);
}

void RVTemp::flush(void) {
	glob_fstream.flush();
}

void RVTemp::do_indent(int indent)
{
  std::string blank(indent << 1, ' ');
  print(blank);
}

void RVTemp::print(const std::string& str)
{
  *outstreamP << str;
  if (rv_debug_flags) flush();
}

void RVTemp::print(const std::string& str, RVErrStrm& strm)
{
  strm << str;
  if (rv_debug_flags) flush();
}

///<summary>
// By default the stream assertStreamP is simply an alias to outstream. In gen_main we want the assertions to be at the end of the code. 
// Hence we call this function to temporarily map it to assert_main_stream. This affects gen_assert_eq (in rv_temps.cpp). 
///</summary>
void RVTemp::separate_assert_stream() {
  assertStreamP = &assert_main_stream;
}

///<summary>
/// Same as unite_uf_stream, but also unites assertStreamP.
///</summary>
void RVTemp::unite_assert_stream() {	
  glob_fstream << "  /* Declarations: */\n" << decl_uf_stream.str() << "\n" << code_uf_stream.str() << "  /* Assertions: */\n" << assert_main_stream.str() << "\n"; 
  std::string emptyString;
  decl_uf_stream.str(emptyString); //resetting the stream
  code_uf_stream.str(emptyString);
  assert_main_stream.str(emptyString);
  declarationsStreamP = outstreamP = assertStreamP = &glob_fstream;
}

///<summary>
/// Inside the old uf code generation (not the cbmc macros), in case there are unbounded structures, there are declarations of new auxliary variables.
/// Since these variables should be global, then we should generate them before the code of the UF.
/// We do this by having two streams: declarations_stream collects declarations in rv_temps; out_stream collects the rest of
/// the code. Outside of the Uf generation, these two stream pointers point to the same ofstream (rv_outstrm sent in main to the constructor of RVTemp)
/// Inside UF generation, we separate them to two streams with this function, and flush them in the end into rv_stream in the right order with unite_uf_streams. 
/// Inside the cbmc_uf code, it is used in a similar way: there we need to gather the declarations and print them before the rest of the code. 
///</summary>
void RVTemp::separate_uf_streams() {
  declarationsStreamP = &decl_uf_stream;
  outstreamP = codePartStreamP = &code_uf_stream;
}

///<summary>

///</summary>
void RVTemp::separate_protect_streams() {
  declarationsStreamP = &decl_uf_stream;
  outstreamP = codePartStreamP = &protect_null_deref_stream;
}


///<summary>
/// See documentation of separate_uf_streams.
///</summary>
void RVTemp::unite_uf_streams() {
  glob_fstream << "  /* Declarations: */\n" << decl_uf_stream.str() << "\n" << protect_null_deref_stream.str() << "\n" << code_uf_stream.str();
  std::string emptyString;
  decl_uf_stream.str(emptyString); //resetting the stream
  code_uf_stream.str(emptyString);
  protect_null_deref_stream.str(emptyString);
  declarationsStreamP = outstreamP = &glob_fstream;
  codePartStreamP = &code_uf_stream;
}
     
void RVTemp::gen_nondet_arr_sz(int sz)
{
  (*outstreamP) <<
   "void nondet_init_array_" << sz 
	  << "(int side)\n" << "{\n    int tmp[" << sz 
	  << "];" <<  "\n    if (side == 0) {\n    " << "    __CPROVER_array_copy(nondet_side0_" 
	  << sz << ",tmp);\n    " << "} else {\n    " << "    __CPROVER_array_copy(nondet_side1_"  <<  sz <<
	   ",tmp);\n" << "    }\n" << "}\n" ;
}

///<summary>
/// declarations common to all semantic check are included in this file. 
///</summary>
void RVTemp::include_rv_declarations() {
	(*outstreamP) << "#include \"rv_declarations.h\"\n";
}

void RVTemp::gen_assert_proto(void)
{
  (*outstreamP) << "\nvoid assert(_Bool);\n";
} 

void RVTemp::gen_cbmc_func_headers()
{
  gen_assert_proto();
  (*outstreamP) <<
"void __CPROVER_assume(_Bool);\n"
"void assume(_Bool assumption)\n"
"{ __CPROVER_assume(assumption); }\n\n"
"_Bool nondet_Bool();\n"
"int nondet_int();\n"
"long nondet_long();\n\n"
"void* malloc(unsigned int);\n\n";
} // obselete: can be reused to regenerate inputs.h

void RVTemp::gen_channel_def()
{
  (*outstreamP) << "\n"
"typedef struct "<< RV_CHANNEL_TAG <<" {\n" <<
"  unsigned index0,index1;\n" <<
"  " << RVRECORD << " records[" << max_records << "];\n" <<
"} "<< RV_CHANNEL_UT <<";\n";
}

void RVTemp::gen_channel(const std::string& channel)
{
  (*outstreamP) <<
""<< RV_CHANNEL_UT <<"  " << channel <<";\n";
}

void RVTemp::gen_RVCHECK()
{
  (*outstreamP) <<
"\nvoid RVSAVE("<< RV_CHANNEL_UT <<"* CHANNEL, int COND, " << RVRECORD << " VAL) \n" <<
"  { if(COND) { \n" <<
"      (CHANNEL)->records[(CHANNEL)->index0] = (VAL); \n" <<
"      (CHANNEL)->index0++; \n" <<
"  } }\n\n" <<
"\nvoid RVCHECK("<< RV_CHANNEL_UT <<"* CHANNEL, int COND, " << RVRECORD << " VAL) \n" <<
"  { if(COND) { \n" <<
"      assert((CHANNEL)->index1 < (CHANNEL)->index0); \n" <<
"      assert((CHANNEL)->records[(CHANNEL)->index1] == (VAL)); \n" <<
"      (CHANNEL)->index1++; \n" <<
"  } }\n\n";
}

void RVTemp::gen_checkpoint(const RVSide& side, const std::string& channel, const std::string& cond, const std::string& val)
{
  (*outstreamP) << 
	"{" << side.get_rvact_name() <<"(&" << channel << ",(" << cond << "),"
			  "("<< RVRECORD <<")(" << val << "));}";
}
 
void RVTemp::gen_rv_init_head()
{
  (*outstreamP) << 
"\nvoid rv_init()\n" <<
"{\n";
}
	
void RVTemp::gen_channel_init(const std::string& channel)
{
  (*outstreamP) << 
"  /* init channel " << channel << " */\n" <<
"  (" << channel << ").index0 = 0;\n" <<
"  (" << channel << ").index1 = 0;\n";
}

void RVTemp::gen_close_func()
{
  (*outstreamP) << 
"}\n\n";
}

void RVTemp::gen_main_head()
{
  (*outstreamP) << 
"\nint main()\n" <<
"{\n" <<
"  _Bool equal = 1;\n";  // used if there are globals to compare in the end of main. 
}

void RVTemp::gen_retval_declarations(const std::string& ret_type0, const std::string& ret_type1)
{
 std::string location(__FUNCTION__);
 gen_var_decl(ret_type0, uf_retvar + "0", location);
 gen_var_decl(ret_type1, uf_retvar + "1", location);  
}

void RVTemp::gen_rv_check_head()
{
  (*outstreamP) << 
"\nvoid rv_check()\n" <<
"{\n";
}

void RVTemp::gen_channel_compares(const std::string& channel)
{
  (*outstreamP) << 
"  /* Check channel " << channel << ": */\n" << 
"  /* check the sequences are of same length: */\n" <<
"  assert( (" << channel << ").index0 == (" << channel << ").index1 );\n";
}


/* basic operation generation functions: */
/*=======================================*/

void RVTemp::gen_call_head(const std::string* ret_var, const std::string& func)
{
  if( ret_var )	(*outstreamP) << "  " << *ret_var << " = ";
  (*outstreamP) << (ret_var ? "": "  ") << func << "(";
}

void RVTemp::gen_var_decl(const std::string& type_text, const std::string& var, std::string& by/*=""*/, bool pointer/*=false*/)
{
  (*declarationsStreamP) << "  " << type_text << (pointer ? "*" : " ") << var << ";"<< BY(by);
}

void RVTemp::gen_var_decl_text(const std::string& type_text, std::string& by/*=""*/)
{
  (*declarationsStreamP) << "  " << type_text << ";"<<BY(by);
}


void RVTemp::gen_alloc(const std::string& var, const std::string& type_text, std::string& by/*=""*/)
{
	// ofer: remove #if 0 after the cbmc bug is solved, which complains about illegal dreference although we do malloc. (Daniel is aware of this bug).
#if 0

  (*outstreamP) <<
	var << " = (" << type_text << "*)" << 
	"malloc( sizeof("<< type_text <<") );\n";
#else
	gen_safe_alloc(var, type_text, by);
#endif

}

///<summary>
/// Allocation without malloc (we use it because cbmc currently has problems handling malloc). 
/// Instead it introduces dummy variables and takes their address. 
/// e.g. instead of x = (int **)malloc(sizeof(int *)) it prints
/// int rv_D0_0;
/// int *rv_D0_1 = &rv_D0_0;
/// x = &rv_D0_1;
/// The D0 is actually Dc where 'c' is a static counter used to avoid name collisions. 
///</summary>
void RVTemp::gen_safe_alloc(const std::string& var, const std::string& type_text, std::string& by)
{
	by.append("/ "); by.append(__FUNCTION__);
	static const std::string sVoid("void");
	static unsigned int counter = 0;
	unsigned int i, len = type_text.size();
	for ( i = len - 1; i; --i) { // count the number of '*' in type_txt (e.g. 2 in "int **")
		if (type_text[i] != '*') break;
	}
	std::string old, curr, basetype = type_text;
	basetype.resize(i);  // makes "int **" into "int".
	for (unsigned int j = 0; j < len - i; j++) {
        string declEnding = ";";
		// Storing the declaration of the dummy variable in declarations_stream. During UF generation (*declarations_stream )= declarations_stream 
		// This will be printed in the global scope, before the rest of the text. 
        if (j == 0 && basetype == sVoid) {
            (*declarationsStreamP) << "  char ";
            declEnding = string("[") + Utils::itoa(RV_VOID_PTR_SIZE) + "]; /* this buffer substitutes a variable of type void. We assume that nothing bigger than RV_VOID_PTR_SIZE bytes is assigned to that void* pointer */";
        }
        else
		    (*declarationsStreamP) << "  " << basetype << " ";
		for (unsigned int k  = 0; k < j ; ++k) (*declarationsStreamP) << '*';
		curr = "rv_D";
		std::stringstream s;
		s << counter << "_" << j;
		curr.append(s.str());
		(*declarationsStreamP) << curr << declEnding << BY(by);
		if (j)  
            (*outstreamP) << "  " << curr << " = &" << old << ";"<< BY(by);
		old = curr;
	}
	 (*outstreamP) << "  " << var << " = &" + old + ";"<<BY(by);

  counter++;
}

///<summary>
/// The difference between this one and gen_local_copy is that we separate the declaration from the 
/// the assignment, because we want the declarations to appear before the assignments.
///</summary>
void RVTemp::gen_local_copy_uf(const std::string& type_text, const std::string& local_name, const std::string& old_name,  std::string& by/*=""*/, bool pointer/*=false*/)
{
	//DIMAXXX - remoive SeparatedStreams assert(SeparatedStreams);
	decl_uf_stream << "  " << type_text << (pointer ? "*" : " ") << local_name << ";" << BY(by); // declaration
	(*codePartStreamP) << "  " << local_name << " = " << old_name << ';' << BY(by); // assignment
}

void RVTemp::gen_assert_eq(const std::string& var0, const std::string& var1, std::string& by, bool pointer /*=false*/)
{
  //(*outstream) << 
	(*assertStreamP) <<
	"  assert( " << (pointer?"*":"") << var0 << " == "<< (pointer?"*":"") << var1 << " );"<< BY(by);
}

void RVTemp::gen_assert_neq(const std::string& var0, const std::string& var1, std::string& by, bool pointer /*=false*/)
{
  (*outstreamP) << 
	"  assert( " << (pointer?"*":"") << var0 << " != "<< (pointer?"*":"") << var1 << " );"<< BY(by);
}

void RVTemp::gen_eq_null(const std::string& var, std::string& by)
{
  (*outstreamP) << "  " << var << " = (void*)0;"<< BY(by);
}

void RVTemp::gen_copy_val(const std::string& v0, const std::string& v1, std::string& by /*=""*/, bool pointer /*=false*/)
{
  (*outstreamP) << "  " << (pointer?"*":"") << v0 << " = " << (pointer?"*":"") << v1 << ";" << BY(by);
}


void RVTemp::gen_save_val_arr(const std::string& item, const std::string& var, int array_size, const array_item *the_arr, std::string& by)
{
  (*outstreamP) << "  RVT_COPY_ARRAY(" << item << "," << var << ", " << array_size << ");"<< BY(by) ;
}

void RVTemp::gen_memcpy(const std::string& item, const std::string& var, int array_size, std::string& by) {
	(*outstreamP) << "  memcpy(" << item << ", " << var << ", " << array_size << ");" << BY(by);
}

void RVTemp::gen_memcmp(const std::string& item, const std::string& var, int array_size, std::string& by) {
	(*assertStreamP) << "  assert(!memcmp(" << item << ", " << var << ", " << array_size << "));" << BY(by);
}

void RVTemp::gen_nondet_value(const std::string& var, const std::string& type_text, bool pointer, bool is_long, std::string& by)
{
  (*outstreamP) << "    " <<
	(pointer ? "*" : "") << var << " = (" << type_text << ")" << 
	(is_long ? "nondet_long()" : "nondet_int()") << ";"<< BY(by);  
}

void RVTemp::gen_nondet_save_val_arr(const std::string& item, const std::string& var, const std::string& type_text, int array_size, bool is_long, const array_item *the_arr, std::string& by)
{
  (*outstreamP) << "  RVT_NONDET_ARRAY(" << item << "," << array_size << ");"<< BY(by);
  (*outstreamP) << "  RVT_COPY_ARRAY("   << var << "," << item << ", " << array_size << ");" << BY(by);
}

void RVTemp::gen_compare_val_arr(const std::string& item, const std::string& var,  int arr_sz, bool first_compare, const array_item *the_arr, std::string& by)
{
  (*outstreamP) << "  RVT_COMP_ARRAY(equal," << item << "," << var << "," << arr_sz << ");"<< BY(by);
}

void RVTemp::gen_nondet_value_arr(const std::string& var, const std::string& type_text, int arr_sz, bool is_long, const array_item *the_arr, std::string& by)
{
  (*outstreamP) << "  RVT_NONDET_ARRAY(" << var << "," << arr_sz << ");"<< BY(by);
}

void RVTemp::gen_assert_eq_arr(const std::string& var0, const std::string& var1, int arr_sz, const array_item *the_arr, std::string& by)
{
  (*outstreamP) << "  RVT_ASSERT_EQ_ARRAY(" << var0 << "," << var1 << "," << arr_sz << " );"<< BY(by);
}

void RVTemp::gen_nondet_save_val(const std::string& item, const std::string& var, const std::string& type_text, bool pointer, bool is_long, std::string& by)
{
  (*outstreamP) << "  " <<
	(pointer ? "*" : "") << item << " = " <<
	(pointer ? "*" : "") << var << " = (" << type_text << ")" <<
	(is_long ? "nondet_long()" : "nondet_int()") << ";" << BY(by);
}

void RVTemp::gen_compare_val(const std::string& item, const std::string& var, bool pointer, bool first, std::string& by)
{
  (*outstreamP) << 
	"    equal = "<< (first ? "(" : "equal && (") <<
	(pointer?"*":"") << item << " == " << (pointer?"*":"") << var <<");" << BY(by);
}

void RVTemp::gen_if_eq_null(const std::string& var, bool equal, std::string& by)
{
  (*outstreamP) <<
	"  if( "<< var <<" "<< (equal?"=":"!") <<"= (void*)0 ) {" << BY(by);
}

void RVTemp::gen_nondet_if(std::string& by)
{
  (*outstreamP) <<
	"  if( nondet_Bool() ) {" << BY(by);
}




/* UF generation code: */
/*=====================*/

const char* RVTemp::uf_item_prefix(bool in) { //static
	return(in ? "in_" : "out_");
}

std::string RVTemp::uf_array_name(const std::string& ufname) { //static
  return "rv_UF_" + ufname + "_array";
}

std::string RVTemp::uf_count_name(const std::string& ufname,
		                          const RVSide& side) //static
{
  return "rv_UF_" + ufname + "_count[" + side.toString() +"]";
}

std::string RVTemp::uf_array_size_name(const std::string& ufname) { //static
  return "rv_UF_K_" + ufname;
}

std::string RVTemp::uf_array_size_name_definition(const std::string& ufname,
		                                          unsigned nRecords,
		                                          const char *comment) { //static
  std::ostringstream def;
  def << "#define " << uf_array_size_name(ufname) << " " << nRecords;
  if (comment)
	  def << " /* " << comment << " */";
  return def.str();
}

void RVTemp::gen_uf_struct_head(const std::string& ufname) {
  (*outstreamP) <<
"\ntypedef struct rv_UF_" << ufname << "_struct_tag {\n";
}

void RVTemp::gen_uf_struct_tail(const std::string& ufname)
{
  (*outstreamP) <<
"} rv_UF_" << ufname << "_struct;\n";
}

void RVTemp::gen_uf_array(const std::string& ufname)
{
  (*outstreamP) << 
    uf_array_size_name_definition(ufname, max_records) <<
    "\nrv_UF_" << ufname << "_struct " << uf_array_name(ufname)
             << "[" << uf_array_size_name(ufname) << "];\n" <<
    rv_counter_type << " rv_UF_" << ufname << "_count[2] = {0,0};\n\n" ;
}

void RVTemp::gen_uf_head(const std::string& ret_type, const std::string* ret_var)
{
  (*outstreamP) <<
"\n{\n";
  if( ret_var )
	(*outstreamP) <<
"  " << ret_type << " " << *ret_var << ";\n\n";
}

void RVTemp::gen_uf_inc_count(const std::string& ufname, int side)
{
  (*outstreamP) <<
	"  " << uf_count_name(ufname, side) << "++;\n";
}

void RVTemp::gen_uf_tail(const std::string *retvar)
{
  if( retvar )
	(*outstreamP) << 
"\n  return " << *retvar << ";";

  (*outstreamP) << 
"\n}\n\n";
}

void RVTemp::gen_uf_search_head(const std::string& ufname, int look_back)
{
  (*outstreamP) <<
"  _Bool found = 0;\n" <<
"  _Bool equal = 1;\n" <<
"  " << rv_counter_type << " found_ind = -1;\n";
 
  if( look_back > 1 ) {
	(*outstreamP) << 
"  " << rv_counter_type << " rv_uf_ind = " << uf_count_name(ufname,1) <<"+"<< look_back-1 <<";\n" <<
"  " << rv_counter_type << " rv_uf_cnt = 0;\n" <<
"  if( rv_uf_ind > " << uf_count_name(ufname,0) <<"-1 )\n" <<
"    rv_uf_ind = " << uf_count_name(ufname,0) <<"-1;\n" <<
"  for(; rv_uf_cnt < " << 2*look_back-1 << " && rv_uf_ind >= 0; ++rv_uf_cnt, ++rv_uf_ind) {\n";

  } else
  if( look_back == 1 ) {
	/* look only at the same index on side 0 (if exists): */
	(*outstreamP) << 
"  " << rv_counter_type << " rv_uf_ind = " << uf_count_name(ufname,1) <<";\n" <<
"  if( " << uf_count_name(ufname,0) << " && rv_uf_ind > " << uf_count_name(ufname,0) << "-1 )\n" <<
"    rv_uf_ind = " << uf_count_name(ufname,0) <<"-1;\n" <<
"// Make sure that side0 was called at least once \n" <<
"  if( " << uf_count_name(ufname,0)  << ")\n" <<
"  {\n";
  } else
  if( look_back == 0 ) { 
	/* search all values of side 0: */
	(*outstreamP) << 
"  " << rv_counter_type << " rv_uf_ind = " << uf_count_name(ufname,0) << "-1;\n" <<
"  for(; rv_uf_ind >= 0; rv_uf_ind--) {\n";
  }
}

void RVTemp::gen_uf_search_tail(const std::string& on_found)
{
  (*outstreamP) << 
"    if( equal ) { \n"
"      found = 1;\n" <<
"      found_ind = rv_uf_ind;\n" <<
on_found <<
"    }\n" <<
"  }\n\n" <<
"  if( found ) /* input values were found among the saved values */\n"
"  {\n";
}

void RVTemp::gen_uf_side_comment(int side) {
	print("\n /*** CBMC-UF side ");
	*outstreamP << side;
	print(": ***/ \n");
}


/* UA (uninterpreted arrays) generation code: */
/*============================================*/

void RVTemp::gen_INIT_UA_STRUCT_macro()
{
  (*outstreamP) <<
"#define INIT_UA_STRUCT(AUP, START_EQ, DATA_PREF)   \\\n"
"{                                                  \\\n"
"  int new_next = 0;                                \\\n"
"  /* Check: ther is more place in these UA data arrays: */ \\\n"
"  assert( DATA_PREF ## next < DATA_PREF ## bound ); \\\n"
"  (AUP)->assume_start_equal = (START_EQ);      \\\n"
"  (AUP)->next_place[0] = (AUP)->start_place[0] = DATA_PREF ## next; \\\n"
"  (AUP)->next_place[1] = (AUP)->start_place[1] = DATA_PREF ## next; \\\n"
"  new_next = DATA_PREF ## next + "<< max_records <<"; \\\n"
"  if( new_next > DATA_PREF ## bound )          \\\n"
"    new_next = DATA_PREF ## bound;             \\\n"
"  DATA_PREF ## next = new_next;                \\\n"
"  (AUP)->place_bound[0] = (AUP)->place_bound[1] = new_next; \\\n"
"  (AUP)->first = DATA_PREF ## first;           \\\n"
"  (AUP)->s0_data  = DATA_PREF ## s0_data;      \\\n"
"  (AUP)->s0_index = DATA_PREF ## s0_index;     \\\n"
"  (AUP)->s1_data  = DATA_PREF ## s1_data;      \\\n"
"  (AUP)->s1_index = DATA_PREF ## s1_index;     \\\n"
"}\n\n";

  (*outstreamP) <<
"#define INIT_UA_TOKEN(AUT, AUP) \\\n"
"{                    \\\n"
"  (AUT).a = (AUP);   \\\n"
"  (AUT).i = 0;       \\\n"
"}\n\n";
}

std::string RVTemp::ua_data_arrays_prefix(const std::string& uaname)
{
  std::string prefix(RV_AU_DATA_PREFIX);
  prefix += uaname;
  prefix += "_";
  return prefix;
}

void RVTemp::gen_ua_data_arrays(const std::string& uaname,
								const std::string& s0_item_type,
								const std::string& s1_item_type)
{
  std::string prefix = ua_data_arrays_prefix(uaname);

  /* max_records UAs - each with up to max_records items: */
  int size = max_records * max_records;

  (*outstreamP) << "\n"
"  int "<< prefix <<"next = 0, "<< prefix <<"bound = "<< size <<";\n"
"  "<< s0_item_type <<" "<< prefix <<"first["<< size <<"];\n"
"  "<< s0_item_type <<" "<< prefix <<"s0_data["<< size <<"];\n"
"  int "<< prefix <<"s0_index["<< size <<"];\n"
"  "<< s1_item_type <<" "<< prefix <<"s1_data["<< size <<"];\n"
"  int "<< prefix <<"s1_index["<< size <<"];\n\n";
}


void RVTemp::gen_ua_struct_def(const std::string& uaname, const std::string& s0_item_type, const std::string& s1_item_type)
{
  (*outstreamP) <<
"typedef struct rv_UA_"<< uaname <<"_struct_tag\n"
"{\n"
"  _Bool assume_start_equal;\n"
"  int start_place[2];\n"
"  int next_place[2];\n"
"  int place_bound[2];\n"
"  "<< s0_item_type <<"* first;  // - indeces in s0_index\n\n"
"  "<< s0_item_type <<"* s0_data;\n"
"  int* s0_index;\n\n"
"  "<< s1_item_type <<"* s1_data;\n"
"  int* s1_index;\n\n"
"} rv_UA_"<< uaname <<"_struct;\n\n"
"typedef rv_UA_"<< uaname <<"_struct* rv_UA_"<< uaname <<"_poi;\n\n"
"typedef struct rv_UA_"<< uaname <<"_token_tag \n"
"{\n"
"  rv_UA_"<< uaname <<"_poi a;\n"
"  int i;\n"
"} rv_UA_"<< uaname <<"_token;\n\n";
}

void RVTemp::gen_ua_new_array_func(const std::string& uaname, bool decls_only)
{
  (*outstreamP) <<
"rv_UA_"<< uaname <<"_token rvua_"<< uaname <<"_new_UA(_Bool start_eq)";

  if(decls_only) {
	(*outstreamP) << ";\n\n";
	return;
  }

  std::string data_prefix = ua_data_arrays_prefix(uaname); 

  (*outstreamP) <<
"\n{\n"
"  rv_UA_"<< uaname <<"_poi a = \n"
"    (rv_UA_"<< uaname <<"_poi)malloc(sizeof(rv_UA_"<< uaname <<"_struct));\n"
"  rv_UA_"<< uaname <<"_token t;\n\n"
"  INIT_UA_STRUCT(a, start_eq, data_prefix);\n\n"
"  INIT_UA_TOKEN(t, a);\n\n"
"  return t;\n"
"}\n\n";
}

void RVTemp::gen_ua_init_func(const std::string& uaname, int side, bool decls_only)
{
  (*outstreamP) <<
"void rvuas"<< side <<"_"<< uaname <<"_init_UA(rv_UA_"<< uaname <<"_token t)";

  if(decls_only) {
	(*outstreamP) << ";\n\n";
	return;
  }
 
  (*outstreamP) <<
"\n{\n  rv_UA_"<< uaname <<"_poi a = t.a;\n"
"  a->next_place["<< side <<"] = a->start_place["<< side <<"];\n}\n\n";
}

void RVTemp::gen_ua_clear_func(const std::string& uaname, int side, bool decls_only)
{
  (*outstreamP) <<
"void rvuas"<< side <<"_"<< uaname <<"_clear_UA(rv_UA_"<< uaname <<"_token t, _Bool set_eq)";

  if(decls_only) {
	(*outstreamP) << ";\n\n";
	return;
  }
 
  std::string data_prefix = ua_data_arrays_prefix(uaname); 

  (*outstreamP) <<
"\n{\n  rv_UA_"<< uaname <<"_poi a = t.a;\n"
"  INIT_UA_STRUCT(a, set_eq, data_prefix);\n}\n\n";
}

void RVTemp::gen_ua_val_func(const std::string& uaname, const std::string& item_type, int side, bool decls_only)
{
  (*outstreamP) <<
item_type<<" rvuas"<< side <<"_"<< uaname <<"_array_val("
		   <<"rv_UA_"<< uaname <<"_token t, int index)";

  if(decls_only) {
	(*outstreamP) << ";\n\n";
	return;
  }

  (*outstreamP) << 
"\n{\n  rv_UA_"<< uaname <<"_poi a = t.a;\n"
"  return a->s"<< side <<"_data[ rvuas"<< side <<"_"<< uaname <<"_UA_ind(t, index) ];\n}\n\n";
}

void RVTemp::gen_ua_s0_ind_func_head(const std::string& uaname, int look_back, bool decls_only)
{
  (*outstreamP) << 
"int rvuas0_"<< uaname <<"_UA_ind(rv_UA_"<< uaname <<"_token t, int index)";

  if(decls_only) {
	(*outstreamP) << ";\n";
	return;
  }
 
  (*outstreamP) <<
"\n{\n"
"  rv_UA_"<< uaname <<"_poi a = t.a;\n"
"  int place = a->next_place[0]-1; // last used place\n";

  if( look_back )
	(*outstreamP) <<
"  int cnt = 0;\n";

	(*outstreamP) <<
"  index += t.i;   // add token's offset \n\n";

  if( look_back )
	(*outstreamP) <<
"  for(; cnt < "<< look_back <<" && place >= 0; ++cnt, --place)\n";
  else // look_back == 0
	(*outstreamP) <<
"\n  for(; place >= 0; place--)\n";

  (*outstreamP) <<
"    if( index == a->s0_index[place] )\n"
"      return place;\n\n"				
"  /* first time we see this index - insert in new places: */\n"
"  place = a->next_place[0];\n\n"
"  /* Check: Enough place in the UA. */\n"
"  assert( place < a->place_bound[0] );\n\n";
  // here comes NONDET_SAVE() in the generated code.
}

void RVTemp::gen_ua_s0_ind_func_tail()
{
  (*outstreamP) <<
"  /* remember the indices: */\n"
"  a->s0_index[place] = index;\n\n"
"  a->next_place[0] = place+1;\n\n"
"  return place;\n}\n\n";
}

void RVTemp::gen_ua_s1_ind_func_head(const std::string& uaname, int look_back, bool decls_only)
{
  (*outstreamP) <<
"int rvuas1_"<< uaname <<"_UA_ind(rv_UA_"<< uaname <<"_token t, int index)";

  if(decls_only) {
	(*outstreamP) << ";\n";
	return;
  }
 
  (*outstreamP) <<
"\n{\n"
"  _Bool found = 0;\n"
"  rv_UA_"<< uaname <<"_poi a = t.a;\n"
"  int first_pl;\n"
"  int array_pl = a->next_place[1]-1;\n";

  if( look_back )
	(*outstreamP) <<
"  int cnt = 0;\n\n";

	(*outstreamP) <<
"  index += t.i;   // add token's offset \n\n";

  if( look_back )
	(*outstreamP) <<
"  for(; cnt < look_back && array_pl >= 0; ++cnt, --array_pl)\n";
  else // look_back == 0
	(*outstreamP) <<
"\n  for(; array_pl >= 0; array_pl--)\n";

  (*outstreamP) <<
"\n    if( index == a->s1_index[array_pl] )\n"
"      return array_pl;\n";

  (*outstreamP) <<
"  /* first time we see this index on side 1: */\n"
"  array_pl = a->next_place[1]; /* new place */\n"
"  /* Check: Enough place in the UA. */\n"
"  assert( array_pl < a->place_bound[1] );\n\n";

  (*outstreamP) <<
"  /* If we assume they are equal at start of execution (in-args equality)\n"
"       then try to find it in firsts of side 0: */\n"
"  if( a->assume_start_equal ) {\n";
  if( look_back )
	(*outstreamP) <<
"    first_pl = a->next_place[1] + look_back-1;";
  else
	(*outstreamP) <<
"    first_pl = a->next_place[1] -1;\n";

	(*outstreamP) <<
"    if( first_pl > a->next_place[0]-1 )\n"
"      first_pl = a->next_place[0]-1;\n";

  if( look_back ) {
	(*outstreamP) <<
"    for(cnt = 0; cnt < 2*look_back-1 && first_pl >= 0; ++cnt, --first_pl)\n";
  } else { // look_back == 0
	(*outstreamP) <<
"    for(; first_pl >= 0; first_pl--)\n";  
  }
  
  (*outstreamP) <<
"      if( index == a->s0_index[first_pl] ) {\n"
"	 found = 1;\n"
"	 break;\n"
"      }\n"
"  }\n\n"
"  if( found )\n"
"  {\n";
  // here comes FETCH()-else-NONDET() in the generated code.
}

void RVTemp::gen_ua_s1_ind_func_tail()
{
  (*outstreamP) << 
"  }\n\n"
"  /* remember index of the new array item: */\n"
"  a->s1_index[array_pl] = index;\n\n"
"  a->next_place[1] = array_pl+1;\n\n"
"  return array_pl;\n}\n\n";
}

void RVTemp::gen_ua_access_macro(const std::string& func_name, const std::string& uaname, int side)
{
  (*outstreamP) << 
"#define "<< func_name <<"(AUT, INDEX)   \\\n"
"    (AUT).a->s"<< side <<"_data[ rvuas"<< side <<"_"<< uaname <<"_UA_ind((AUT), (INDEX)) ]\n\n";
}

void RVTemp::gen_ua_unary_func(UnaryOp op, const std::string& func_name, const std::string& uaname, bool decls_only)
{
  (*outstreamP) << 
"rv_UA_"<< uaname <<"_token "<< func_name <<"(rv_UA_"<< uaname <<"_token* pt)";

  if(decls_only) {
	(*outstreamP) << ";\n";
	return;
  }

  (*outstreamP) << "\n{\n";

  if( op == UO_PostInc || op == UO_PostDec )
	(*outstreamP) << 
"  rv_UA_"<< uaname <<"_token orig =  *pt;\n"; 


  if( op == UO_PreInc || op == UO_PostInc )
	(*outstreamP) << 
"  pt->i++;\n";
  else
  if( op == UO_PreDec || op == UO_PostDec )
	(*outstreamP) << 
"  pt->i--;\n";

  if( op == UO_PostInc || op == UO_PostDec )
	(*outstreamP) << 
"  return orig;\n}\n\n";
  else
	(*outstreamP) << 
"  return *pt;\n}\n\n";
}

void RVTemp::gen_ua_binary_func(BinaryOp op, const std::string& func_name, const std::string& uaname, bool decls_only)
{
  (*outstreamP) << 
"rv_UA_"<< uaname <<"_token "<< func_name <<"(rv_UA_"<< uaname <<"_token t, int offset)";

  if(decls_only) {
	(*outstreamP) << ";\n";
	return;
  }
 
  (*outstreamP) << "\n{\n";

  if( op == BO_Plus )
	(*outstreamP) << 
"  t.i += offset;\n";
  else  
  if( op == BO_Minus )
	(*outstreamP) << 
"  t.i -= offset;\n";

	(*outstreamP) << 
"  return t;\n}\n\n";
}

void RVTemp::gen_ua_assign_func(AssignOp op, const std::string& func_name, const std::string& uaname, bool decls_only)
{
  (*outstreamP) << 
"rv_UA_"<< uaname <<"_token "<< func_name <<"(rv_UA_"<< uaname <<"_token* pt, int offset)";

  if(decls_only) {
	(*outstreamP) << ";\n";
	return;
  }
 
  (*outstreamP) << "\n{\n";

  if( op == AO_PlusEql )
	(*outstreamP) << 
"  pt->i += offset;\n";
  else  
  if( op == AO_MinusEql )
	(*outstreamP) << 
"  pt->i -= offset;\n";
	
  (*outstreamP) << 
"  return *pt;\n}\n\n";
}

void RVTemp::gen_ua_rel_func(RelOp op, const std::string& func_name, const std::string& uaname, bool decls_only)
{
  std::string token("rv_UA_");
  token += uaname + "_token";

  (*outstreamP) << 
"_Bool "<< func_name <<"("<< token <<" tl,"<< token <<" tr)";

  if(decls_only) {
	(*outstreamP) << ";\n";
	return;
  }
 
  (*outstreamP) <<
"\n{\n"
"  // Check: we compare items of the same array:\n"
"  assert( tl.a == tr.a );\n\n";

  (*outstreamP) << 
"  return( tl.i "; 
  PrintRelOp(*outstreamP, op);  
  (*outstreamP) << " tr.i );\n}\n\n";
}

void RVTemp::gen_ua_assert_eq_head(const std::string& uaname, bool decls_only)
{
  (*outstreamP) << 
"void rvua_"<< uaname <<"_assert_eq(rv_UA_"<< uaname <<"_poi a)";

  if(decls_only) {
	(*outstreamP) << ";\n\n";
	return;
  } 

  (*outstreamP) << 
"\n{\n"
"  _Bool found;\n"
"  int index;\n"
"  int s0_pl, s1_pl, cnt;\n\n"
"  for(s1_pl = 0; s1_pl < a->next_place[1]; ++s1_pl)\n  {\n"
"    /* chose from where to start: */\n"
"    s0_pl = s1_pl + look_back-1;\n"
"    if( s0_pl > a->next_place[0]-1 )\n"
"      s0_pl = a->next_place[0]-1;\n\n"
"    /* Check array boundaries: */\n"
"    assert( a->start_place[1] <= s1_pl && s1_pl < a->place_bound[1] );\n\n"
"    /* try to find it on side 0: */\n"
"    found = 0;\n"
"    index = a->s1_index[s1_pl];\n"
"    for(cnt = 0; cnt < 2*look_back-1 && s0_pl >= 0; ++cnt, --s0_pl)\n    {\n"
"      /* Check array boundaries: */\n"
"      assert( a->start_place[0] <= s0_pl && s0_pl < a->place_bound[0] );\n\n"
"      if( index == a->s0_index[s0_pl] ) {\n"
"        found = 1;\n"
"        break;\n"
"      }\n"
"    }\n\n"
"    /* Check the index exists on side 0: */\n"
"    assert( found );\n\n"
"    /* Check the item values are the same: */\n";
  
  /* Here would come: "ASSERT_EQ( a->s0_data[s0_pl], a->s1_data[s1_pl] );" */
}

void RVTemp::gen_ua_assert_eq_middle()
{
  (*outstreamP) << 
"  }\n\n"
"  /* Check also all side 0 indices are on side 1 : */\n"
"  for(s0_pl = 0; s0_pl < a->next_place[0]; ++s0_pl)\n  {\n"
"    /* chose from where to start: */\n"
"    s1_pl = s0_pl + look_back-1;\n"
"    if( s1_pl > a->next_place[1]-1 )\n"
"      s1_pl = a->next_place[1]-1;\n\n"
"    /* Check array boundaries: */\n"
"    assert( a->start_place[0] <= s0_pl && s0_pl < a->place_bound[0] );\n\n"
"    /* try to find it on side 1: */\n"
"    found = 0;\n"
"    index = a->s0_index[s0_pl];\n"
"    for(cnt = 0; cnt < 2*look_back-1 && s1_pl >= 0; ++cnt, --s1_pl)\n    {\n"
"      /* Check array boundaries: */\n"
"      assert( a->start_place[1] <= s1_pl && s1_pl < a->place_bound[1] );\n\n"
"      if( index == a->s1_index[s1_pl] ) {\n"
"        found = 1;\n"
"        break;\n"
"      }\n"
"    }\n\n"
"    /* Check the index exists on side 0: */\n"
"    assert( found );\n\n"
"    /* Check the item values are the same: */\n";

  /* Here would come: "ASSERT_EQ( a->s0_data[s0_pl], a->s1_data[s1_pl] );" 
	 and this is the end of the _assert_eq() func. */
}

void RVTemp::gen_nondet_ua_value(const std::string& uaname, const std::string& var, bool pointer, const RVSide& side, bool set_eq)
{
  (*outstreamP) <<
	"rvuas"<< side.toString() <<"_"<< uaname <<"_clear_UA("<< (pointer ? "*" : "") << var << ", "
		   << (set_eq ? 1: 0) <<");\n";  
}

void RVTemp::gen_ua_assert_eq(const std::string& uaname, const std::string& var, bool pointer /*=false*/)
{
  (*outstreamP) <<
	"rvua_"<< uaname <<"_assert_eq("<< var << (pointer ? "->" : ".") <<"a);\n";
}

void RVTemp::gen_ua_new_array_call(const std::string& uaname, const std::string& var, bool pointer, bool set_eq)
{
  (*outstreamP) <<
(pointer ? "*" : "") << var << " = rvua_"<< uaname <<"_new_UA("<< (set_eq ? 1: 0) <<");\n";  
}

///<summary>
/// initial lines of the final reach-equivalence check function
///</summary>
void RVTemp::get_reach_equivalence_check_start(void)
{
	print("  /* check reach-equivalence of the inputs for each uninterpreted function: */\n");
	*outstreamP << "  " << rv_counter_type << " i;\n";
}

///<summary>
/// code for checking reach-equivalence of all the inputs of the given UF data array
///</summary>
///<param name="ufname">the name of the UF pair whose reach-equivalence is to be checked</param>
void RVTemp::gen_reach_equiv_over_uf_array(const std::string& ufname)
{
	*outstreamP << "\n  /* checking reach-equivalence of all the inputs of array "
			   << uf_array_name(ufname) << " : */\n";
	*outstreamP << "  for (i = " << uf_count_name(ufname, SIDE0) << " - 1; i >= 0; --i)\n";
	*outstreamP << "    assert( " << uf_array_name(ufname) << "[i].reach_equiv_flag );\n";
}
