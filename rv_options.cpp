/*
 * rv_options.cpp
 *
 *  Created on: Feb 10, 2011
 *      Author: edima
 */

#include <string>
#include <fstream>
#include <string.h>

#include <rv_options.h>
#include <rv_commands.h>
#include <rv_error.h>
#include <rv_consts.h>
#include "rv_glob.h"
#include "rv_msg.h"

using namespace std;

RV_LOC_MSGS_ENG_BEGIN
	{0,	"Usage: %0s [options] <side0_name>.c <side1_name>.c \n"
		"A regression verification tool.\n"
		"Options:\n"
		"  -d <dir>          Work in directory <dir>\n"
		"  -o <output_name>  Use <output_name> as base name for all generated files (default: \"\")\n"
		"  -main <func_name> Function name of the call graph root (default \"main\")\n"
		"  -refined          Equal functions stay interpreted if they are non-recursive\n"
		"  -fuf <uf_file>    Force uninterpreted functions specified in <uf_file>\n"
		"  -nofuf            No file specifying uninterpreted functions is used\n"
		"  -rel <rel_file>   Relate functions/globals as specified in <rel_file>\n"
		"  -noauf            Don't auto detect equal functions and replace them by UFs\n"
		"  -noextufs         Don't assume pairs of external functions are UFs\n"
		"  -sccps            check CPs in semchks - not only at the end\n"
		"  -nosem            Don't use also semantic check to detect equal functions\n"
		"  -semsing          Do semantic check to a single function at a time\n"
		"  -K <bound>        Unwind bound for equivalence check (default=0 means unbounded)\n"
		"  -norec2uf         During semchk, do not convert recursive calls to calls to UFs.\n"
		"  -array2ua         Convert arrays to uninterpreted arrays.\n"
		"  -kac              Keep all code even if found to be unreachable from main \n"
		"  -dk <k>           Unwind structures to depth k (default=1) \n"
		"  -lb <num>         Number of calls the UFs will look back to compare inputs (default=1)\n"
		"  -r  <num>         Number of records in channels and UF value arrays (default=32)\n"
		"  -timeout <seconds> Timeout for semchk execution\n"
		"  -mt               Check mutual termination\n"
		"  -completeness <#> Completeness level (0 - 2). Default is 0. "
		"  -cil              preprocess with cil\n"
	    "  -c99              C99 compliance"
		"  -nooutline_funcs  don't replace arithmetic operators with outline functions\n"
	    "  -continue_on_fail    keep running even if CBMC returns an uninterpretable result.\n"
		"  -debug <section(s)>  Emit debug prints to stderr. <section(s)> code in octal\n"
		"  -directives <directives file name>  Directives file with channel and check point definitions\n"
		"  <side0 file name> <side1 file name>  Names of the source file for each side\n"
		"\n"
		"Currently only one file per side is supported.\n"
		"Use cil to merge multiple files. \n\n"
		"Debug info codes (for -debug):\n"
		"  main      000001\n"
		"  parse     000002\n"
		"  commands  000004\n"
		"  funcpair  000010\n"
		"  collect   000020\n"
		"  replace   000040\n"
		"  treecomp  000100\n"
		"  funcdfs   000200\n"
		"  funcnode  000400\n"
		"  loops     001000\n"
		"  gen       002000\n"
		"  propagate 004000\n"
		"  arrays    020000\n"
		"  callgraph 040000\n"
		"  graph     100000\n"
		"  decompose 200000\n"
	},
	{1, "After -d a dir name is expected.\n"},
	{2, "After -o a base name is expected.\n"},
	{3, "After -main a function name is expected.\n"},
	{4, "After -fuf an uninterpreted functions file name is expected.\n"},
	{5, "After -rel a file name of related functions/globals is expected.\n"},
	{6, "After -directives expecting name of the directives file.\n"},
	{7, "After %0s a positive decimal number is expected.\n"},
	{8, "After -dk a decimal number is expected.\n"},
	{9, "After -delta_dk a non-negative decimal number is expected.\n"},
	{10, "After -timeout a positive decimal number (seconds) is expected.\n"},
	{11, "After -debug an octal combination of debug flags is expected (see below).\n"},
	{12, "After -completeness a number in the range 0 - 2 is expected.\n"},
	{13, "Unrecognized flag: %0s.\n"},
	{14, "Previously mentioned -nofuf option is ignored.\n"},
	{15, "Previously mentioned -fuf %0s option is ignored.\n"},
	{16, "After -break a string upon which a breakpoint will be raised is expected."},
RV_LOC_MSGS_ENG_END("rv_options.cpp");

RVOptions::RVOptions(int argc, char* const argv[])
{
#ifdef _MSC_VER
	m_pathDelim = BackSlash;
#else
	m_pathDelim = Slash;
#endif
	m_bOk = parse_options(argc, argv);
	if (!m_bOk) print_help(argv[0]);
	//else  print_options();
}

void RVOptions::print_options(void) {
	*m_pLog <<  "\n\nRVT  PARAMS                "  << std::endl;
	*m_pLog <<  "-------------------------------"  << std::endl;
	*m_pLog << " base_dir                : " <<  base_dir << std::endl ;
	*m_pLog << " semchk_dir              : " <<  semchk_dir << std::endl;
	*m_pLog << " base_name               : " <<  base_name << std::endl;
	*m_pLog << " direct_fname            : " <<  direct_fname << std::endl;
	*m_pLog << " side0_fname             : " <<  side0_fpath << std::endl;
	*m_pLog << " side1_fname             : " <<  side1_fpath << std::endl;
	switch (m_fufSet) {
	case AUTOSET:
		*m_pLog << " fuf_fname               : " << "(Auto-set) " << fuf_fname << std::endl;
		break;
	case BY_USER:
		*m_pLog << " fuf_fname               : " << fuf_fname << std::endl;
		break;
	case SET_NO:
		*m_pLog << " fuf_fname               : not given" << std::endl;
		break;
	case UNSET:
		break;
	default:
		fatal_error("Unsupported value of m_fufSet");
	}
	if (rel_fname != "")
	*m_pLog << " rel_fname               : " <<  rel_fname << std::endl;
	//if (detach_typedef != "")
	//rv_log << " detach_typedef          : " <<  detach_typedef << std::endl;
	*m_pLog << " main_name               : " <<  main_name << std::endl;
	*m_pLog << " delta_dk                : " <<  delta_dk  << std::endl;
	*m_pLog << " semchk_timeout          : " <<  semchk_timeout  << std::endl;
    *m_pLog << " outline_funcs           : " <<  RVGlob::flags(RVGlob::GLBL_OUTLINE) << std:: endl;
	// rv_log << " use_auf                 : " <<  use_auf << std:: endl;
	*m_pLog << " use_sem                 : " <<  use_sem << std:: endl;
	*m_pLog << " dk                      : " <<  dk << std:: endl;
	*m_pLog << " ufs_look_back           : " <<  ufs_look_back << std::endl;
	*m_pLog << " max_records             : " <<  max_records << std::endl;
	*m_pLog << " K                       : " <<  K << std::endl;	
	*m_pLog << " keep_all_code           : " <<  keep_all_code << std::endl;
	*m_pLog << " semchk_recursive        : " <<  semchk_recursive << std::endl;
	*m_pLog << " arrays_to_uas           : " <<  arrays_to_uas << std::endl;
	*m_pLog << " test_ctool              : " <<  test_ctool << std::endl;
	*m_pLog << " omega_total_bound       : " <<  omega_total_bound << std::endl;
	*m_pLog << " ubs_depth_k             : " <<  ubs_depth_k << std::endl;
	*m_pLog << " rv_debug_flags          : " <<  rv_debug_flags << std::endl;
	*m_pLog << " refined                 : " <<  refined << std::endl;
	*m_pLog << " run_cil                 : " <<  run_cil << std::endl;
	*m_pLog << " mutual_term_check       : " <<  mutual_term_check << std::endl;
	*m_pLog << " m_bAbortIfUnknownCbmcErr: " <<  m_bAbortIfUnknownCbmcErr << std::endl;
	*m_pLog << " m_c99                   : " <<  m_c99 << std::endl;
	*m_pLog << "-------------------------------"  << std::endl;

	*m_pLog <<  std::endl  << std::endl;
	*m_pLog << decision_params;
}


void RVOptions::print_help(const char *prog_name) const
{
	rv_errstrm << string(RVLocMsg<0>(prog_name));
}


static bool stringEndsWith(const string& str, const string &suffix)
{
	size_t suffixLen = suffix.length();
	return str.length() >= suffixLen &&
		   !str.compare(str.length() - suffixLen, suffixLen, suffix);
}


bool RVOptions::parse_options(int argc, char* const argv[])
{
  // char *last_dot;
  int optc = argc - 2; /* without <side0_name> and <side1_name> */
  bool lb_set = false;

  if( argc < 3 )
	return false;

  for(int i = 1; i < optc; i++) {
	if( !strcmp(argv[i],"-d") ) {
	  if( ++i >= optc ) {
		rv_errstrm << RVLocMsg<1>();
		return false;
	  }
	  base_dir = argv[i];
	} else
	if( !strcmp(argv[i],"-o") ) {
	  if( ++i >= optc ) {
		rv_errstrm << RVLocMsg<2>();
		return false;
	  }
	  base_name = argv[i];
	} else
	if( !strcmp(argv[i],"-main") ) {
	  if( ++i >= optc ) {
		rv_errstrm << RVLocMsg<3>();
		return false;
	  }
	  main_name = argv[i];
	} 
	 else
		if( !strcmp(argv[i],"-refined") ) {
			refined = true;
		}
		else
		if( !strcmp(argv[i],"-cil") ) {
			run_cil = true;
		}
		else
	if( !strcmp(argv[i],"-fuf") ) {
	  if( ++i >= optc ) {
		rv_errstrm << RVLocMsg<4>();
		return false;
	  }
	  if (m_fufSet == SET_NO)
		  rv_errstrm << RVLocMsg<14>();
	  fuf_fname = argv[i];
	  m_fufSet = BY_USER;
	}
	else if (!strcmp(argv[i],"-nofuf") ) {
		if (m_fufSet == BY_USER)
			rv_errstrm << RVLocMsg<15>(fuf_fname);
		fuf_fname.clear();
		m_fufSet = SET_NO;
	}
	else if( !strcmp(argv[i],"-rel") ) {
	  if( ++i >= optc ) {
		rv_errstrm << RVLocMsg<5>();
		return false;
	  }
	  rel_fname = argv[i];
	} else	
	if( !strcmp(argv[i],"-nooutline_funcs") ) {
		RVGlob::flags(RVGlob::GLBL_OUTLINE, 0);
		RVGlob::flags(RVGlob::GLBL_OUTLINE_NOW, 0);
	}
	else
	if( !strcmp(argv[i],"-semsing") )
	  decision_params.allow_different_callees = false;
	else
	if( !strcmp(argv[i],"-extufs") )
	  decision_params.extern_funcs_are_ufs = true;
	else
	if( !strcmp(argv[i],"-noextufs") )
	  decision_params.extern_funcs_are_ufs = false;
	else
	if( !strcmp(argv[i],"-sccps") )
	  decision_params.allow_cps_in_ufs = true;
	else
	if( !strcmp(argv[i],"-sem") )
	  use_sem = true;
	else
	if( !strcmp(argv[i],"-nosem") )
	  use_sem = false;
	else
	if( !strcmp(argv[i],"-K") ) {
	  if( ++i >= optc || sscanf(argv[i],"%d",&K) < 1 || K < 0) {
		rv_errstrm << RVLocMsg<7>("-K");
		return false;
	  }
	}
	else
	if( !strcmp(argv[i],"-rec2uf") )
	  semchk_recursive = true;
	else
	if( !strcmp(argv[i],"-norec2uf") )
	  semchk_recursive = false;
	else
	if( !strcmp(argv[i],"-array2ua") )
	  arrays_to_uas = true;
	else
	if( !strcmp(argv[i],"-noarray2ua") )
	  arrays_to_uas = false;
	else
	if( !strcmp(argv[i],"-kac") )
	  keep_all_code = true;
	else
	if( !strcmp(argv[i],"-dk") ) {
	  if( ++i >= optc || sscanf(argv[i],"%d",&dk) < 1 || dk <= 0 ) {
		rv_errstrm << RVLocMsg<8>();
		return false;
	  }
	  ubs_depth_k = dk; // by default - strategies may change
	}
	else
	if( !strcmp(argv[i],"-lb") ) {
	  if( ++i >= optc || sscanf(argv[i],"%d",&ufs_look_back) < 1 ) {
		rv_errstrm << RVLocMsg<7>("-lb");
		return false;
	  }
	  lb_set = true;
	}
	else
	if( !strcmp(argv[i],"-r") ) {
	  if( ++i >= optc || sscanf(argv[i],"%d",&max_records) < 1 || max_records <= 0) {
		rv_errstrm << RVLocMsg<7>("-r");
		return false;
	  }
	}
	else
	if( !strcmp(argv[i],"-delta_dk") ) {
	  if( ++i >= optc || sscanf(argv[i],"%d",&delta_dk) < 1 || delta_dk <= 0 ) {
		rv_errstrm << RVLocMsg<9>();
		return false;
	  }
	}
	else
	if( !strcmp(argv[i],"-timeout") ) {
	  if( ++i >= optc || sscanf(argv[i],"%d",&semchk_timeout) < 1 || semchk_timeout < 1) {
		rv_errstrm << RVLocMsg<10>();
		return false;
	  }
	}	
	else
	if( !strcmp(argv[i],"-debug") ) {
	  unsigned fresh_debug_flags = 0;
	  if( ++i >= optc || sscanf(argv[i],"%o",&fresh_debug_flags) < 1 ) {
		rv_errstrm << RVLocMsg<11>();
		return false;
	  }
	  rv_debug_flags |= fresh_debug_flags;
	}
	else
	if( !strcmp(argv[i],"-completeness") ) {
	  int int_completeness;
	  if( ++i >= optc || sscanf(argv[i],"%d",&int_completeness) < 1 || int_completeness < 0 || int_completeness > 2) {
		rv_errstrm << RVLocMsg<12>();
		return false;
	  }
	  else
		completeness = int_completeness;
	}	
	else
	if( !strcmp(argv[i],"-directives") ) {
	  if( ++i >= optc ) {
		rv_errstrm << RVLocMsg<6>();
		return false;
	  }
	  direct_fname = argv[i];
	  accessDirectives().activate();
	}
	else
	if( !strcmp(argv[i],"-test_ctool") )
	  test_ctool = true;
	else if ( !strcmp(argv[i],"-mt") ) {
		mutual_term_check = true;
		if (!lb_set) ufs_look_back = 0;
		if (m_fufSet == UNSET) {
			fuf_fname = "rv_pe.fuf";
			m_fufSet = AUTOSET;
		}
	}
	else if (!strcmp(argv[i], "-continue_on_fail"))
		m_bAbortIfUnknownCbmcErr = false;
	else if (!strcmp(argv[i], "-c99"))
		m_c99 = true;
	else if (!strcmp(argv[i], "-break")) {
		char buf[RV_MAX_LINE];
		if( ++i >= optc || sscanf(argv[i],"%s",buf) < 1 ) {
			rv_errstrm << RVLocMsg<16>();
			return false;
		}
		breakOnSeq(buf);
	}
	else
	  if( argv[i][0] == '-' ) {
		rv_errstrm << RVLocMsg<13>(argv[i]);
		return false;
	  }
  } /* for */

  detectRvtPath(argv[0]);

  /* dependencies: */

  //direct_fname = argv[argc-3]; // ofer: moved to options
  side0_fpath  = argv[argc-2];
  side1_fpath  = argv[argc-1];

   /* if the last char is not '/' or '\\' : */
  if (!stringEndsWith(base_dir, m_pathDelim))
	base_dir += m_pathDelim;

  if (!isStringFieldInitialized(semchk_dir))
	  semchk_dir.assign(base_dir + "semchks" + m_pathDelim);

  return true;
}


int RVOptions::detectPathDelimiter(const char *arg0) {
	//Problem: under Windows build our executable can run both under cmd and sh
	//They require different path delimiters.
	//This method tries heuristically to detect what is the calling shell:
	int lastDelimPos = -1;
	unsigned int slashCount = 0, backSlashCount = 0, count = 0;
	int lastSlashPos = -1, lastBackSlashPos = -1;
	for (const char *p = arg0; *p != '\0'; ++p, ++count) {
		if (*p == *BackSlash) { ++backSlashCount; lastBackSlashPos = count; }
		else if (*p == *Slash) { ++slashCount; lastSlashPos = count; }
	}
	if (slashCount > backSlashCount) {
		m_pathDelim.assign(Slash);
		lastDelimPos = lastSlashPos;
	}
	else if (slashCount < backSlashCount || !m_pathDelim.compare(BackSlash)) {
		m_pathDelim.assign(BackSlash);
		lastDelimPos = lastBackSlashPos;
	}
	else
		lastDelimPos = lastSlashPos;
	return lastDelimPos;
}


void RVOptions::detectRvtPath(const char *arg0)
{
	int lastDelimPos = detectPathDelimiter(arg0);
	rv_commands.setPathDelim(m_pathDelim);
	if (lastDelimPos >= 0)
		rv_commands.setRvtLoc(string(arg0, lastDelimPos + 1));
}


int RVOptions::getErrorStatus(void) const {
	return 1;
}


bool RVOptions::readyToRun(void) const {
	return m_bOk;
}


bool RVOptions::isStringFieldInitialized(const string &field) const {
	return !field.empty() && field.compare(UNINITED);
}
