#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <assert.h>

#include <rv_consts.h>
#include <rv_error.h>
#include <rv_commands.h>
#include <rv_macros.h>

#define RV_SECTION RV_SEC_COMMANDS

using namespace std;

const char *Slash = "/", *BackSlash = "\\";


class RVRelativePath {
public:
	RVRelativePath(size_t nSteps, ...)
	  : m_relPath(rv_commands.rvtLoc)
	{
		va_list vl;
		va_start(vl, nSteps);
		for (size_t i=0; i < nSteps; ++i) {
			const char *step = va_arg(vl, const char *);
			m_relPath.append(step).append(Slash);
   	    }
		va_end(vl);
	}

	std::string combineRelativePath(const std::string& file) const
	{
		return m_relPath + file;
	}

private:
	std::string m_relPath;
};


RVCommands rv_commands;

const char* RVCommands::unitrv_res_code_names[4] = {
	"PROGRAMS ARE EQUIVALENT",
	"PROGRAMS ARE NOT EQUIVALENT",
	"NOT FINISHED",
	"UNCOMPILABLE"
};

const char* RVCommands::unitrv_mutual_termination_res_code_names[4] = {
	"PROGRAMS ARE MUTUALLY TERMINATING",
	"PROGRAMS ARE NOT MUTUALLY TERMINATING",
	"NOT FINISHED",
	"UNCOMPILABLE"
};

const char* RVCommands::res_code_names[4] = {
  "VERIFICATION SUCCESSFUL",
  "VERIFICATION FAILED",
  "NOT FINISHED",
  "UNCOMPILABLE"
};

const std::string RVCommands::NO_ARG("###NO_ARG```");


RVCommands::RVCommands(void)
  : rvtLoc("."), result(UNKNOWN)
{
}

vector<string>* RVCommands::runFrama(){

	runScript(FRAMA_SCRIPT_NAME);
	exec(FRAMA_PARSER_PATH);
	std::ifstream infile(FRAMA_PARSED_FILE);
	std::string line;
	vector<string>* result = new vector<string>();
	while (std::getline(infile, line))
	{
		result->push_back(line);
	}


	return result;
}

int RVCommands::runScript(const std::string& script,
	  				      const std::string& arg1,
						  const std::string& arg2,
						  const std::string& arg3,
						  const std::string& arg4,
						  const std::string& arg5,
						  const std::string& arg6)
// for scripts only (this is why we need the tcsh in Windows)
{
	static const RVRelativePath ScriptsLocation(3, "..", "tools", "scripts");
	std::string cmd(ScriptsLocation.combineRelativePath(script));

	if (arg1 != NO_ARG) {
		cmd.append(" ").append(arg1);
		if (arg2 != NO_ARG) {
			cmd.append(" ").append(arg2);
			if (arg3 != NO_ARG) {
				cmd.append(" ").append(arg3);
				if (arg4 != NO_ARG) {
					cmd.append(" ").append(arg4);
					if (arg5 != NO_ARG) {
						cmd.append(" ").append(arg5);
						if (arg6 != NO_ARG) {
							cmd.append(" ").append(arg6);
						}
					}
				}
			}
		}
	}

	char rvtPlatform[RV_MAX_IDENT] = "RVT_PLATFORM=";

#ifdef _MSC_VER
	if (script == "semchk_unitrv"){
		static const RVRelativePath ScriptsLocation(3, "..", "tools", "scripts");
		std::string cmdtcsh(ScriptsLocation.combineRelativePath("tcsh.bat"));
		//cmd = cmdtcsh + " -c \"" + cmd + " \"";
		cmd = "C:/NewRVT/tools/scripts/tcsh.bat -c \"" + cmd + " \"";
		//cmd = "tcsh -c \"" + cmd + " \"";
	}
	else{
		cmd = "tcsh -c \"" + cmd + " \"";
	}
	
    strcat(rvtPlatform, "windows");
#elif defined LINUX || defined __LINUX__ || defined __linux__
    strcat(rvtPlatform, "linux");
#else
    strcat(rvtPlatform, "cygwin");
#endif
	
    putenv(rvtPlatform);
	//exec()
	return exec(cmd);

}


int  RVCommands::exec(const std::string& cmd) const
{
  if (DBG) rv_errstrm <<"Executes: "+cmd+" \n";
  rv_errstrm.flush();
  int res = system(cmd.data());
  cout.flush();
  cerr.flush(); 
  return res;		
}


void RVCommands::mkdir(const std::string& dir)
{
  std::string command("rv_mkdir"), unixDir(unixStylePath(dir));
  int ret = runScript(command, unixDir);

  if(DBG) rv_errstrm <<"RVCommands::mkdir(): ret = "<< ret <<" \n";

  if( ret != 0 || !fileExists(unixDir, true) )
	  fatal_error("Failed mkdir command ", false);
}


bool RVCommands::runSummarizer(const std::string& funcName, const std::string& filePath, int side){
	
	std::stringstream ss;
	ss << "C:/NewRVT/tools/scripts/summarize.bat " << filePath << " " << funcName << " " << side;
	std::string cmd = ss.str();
	
	int result = exec(cmd);
	if (result != 0) fatal_error("Failed summarizer command ", false);



	return 0;
	
}

bool RVCommands::cpp(const std::string& in_file_name,
		             const std::string& out_file_name)
{
  std::string script("rv_cpp");
  int ret = runScript(script, unixStylePath(in_file_name), unixStylePath(out_file_name));
  		       
  if(DBG)  rv_errstrm <<"RVCommands::cpp: ret = "<< ret <<" \n";

  if( ret != 0 )  fatal_error("Failed cpp command ", false);

  return true;
}


bool RVCommands::outline_header(const std::string& prefix_file, const std::string& in_file_name)
{
  std::string script("rv_outline");
  
  int ret = runScript(script, unixStylePath(prefix_file), unixStylePath(in_file_name));
  	
  if(DBG)  rv_errstrm <<"RVCommands::outline_header: ret = "<< ret <<" \n";

  if( ret != 0 )  fatal_error("Failed outline_header command ", false);

  return true;
}


bool RVCommands::outline_type_specific(const std::string& prefix_file)
{
  std::string script("rv_outline_type_specific");

  int ret = runScript(script, unixStylePath(prefix_file));

  if(DBG)  rv_errstrm <<"RVCommands::outline_type_specific: ret = "<< ret <<" \n";

  if( ret != 0 )  fatal_error("Failed outline_header command ", false);

  return true;
}




///<summary>
/// Checks syntax of input file with gcc (running the script rv_gcc)
///</summary>
void RVCommands::check_syntax(const std::string in_file0,
		                      const std::string in_file1,
		                      bool c99) {
	string script("rv_gcc");
	int ret = runScript(script, unixStylePath(in_file0), c99GccOption(c99));
	if (ret) fatal_error("*** Syntax problems on side 0 ***", false);//rv_errstrm << " (exit code " << ret << "). May lead to problems later on. ***\n";
	ret = runScript(script, unixStylePath(in_file1), c99GccOption(c99));
	if (ret) fatal_error("*** Syntax problems on side 1 ***", false);//rv_errstrm << " (exit code " << ret << "). May lead to problems later on. ***\n";

}


bool RVCommands::cil(const std::string in_file, const std::string out_file) {
#ifdef _MSC_VER
	string cmd = "cilly.asm.exe --noPrintLn --rmUnusedInlines  --dosimpleMem  --docanonicalize  --noInsertImplicitCasts --out " + out_file + " " + in_file;	//--decil
	if (system(cmd.data())) fatal_error("failed to execute cil\n", false);
	return true;
#else

  std::string script("rv_cil");
  int ret = runScript(script, unixStylePath(in_file));

  if(DBG)  rv_errstrm <<"RVCommands::cil: ret = "<< ret <<" \n";

  if( ret != 0 )
	  fatal_error("failed to execute cil\n ", false);

  return true;
#endif
}




RVCommands::ResCode RVCommands::get_result(void)
{
  return result;
}


bool RVCommands::run_sem_check( const std::string& dir, 
								const std::string& fname, 
								int K /*= 0*/, int timeout /*= 0*/, 
								bool abortIfUnknownCbmcErr /*= true*/, 
								bool c99 /*= false*/, 
								bool is_unitrv /*= false*/, bool is_mutual_check /*= false*/ )
{
  result = UNKNOWN;  
  std::ostringstream com_strm;

  com_strm << K;  
  int ret=-1;
  if (is_unitrv){
	  std::string command("semchk_unitrv"); 
	  ret = runScript(command, unixStylePath(dir), fname, RV_SEMCHK0_PREFIX + fname, RV_SEMCHK1_PREFIX + fname, "1", is_mutual_check? "--mutual --unwind 6" : NO_ARG);
  }
  else{
	  std::string command("semchk");
	  ret = runScript(command, unixStylePath(dir), fname,
		  com_strm.str(), "0",
		  DBG? "1" : "0", c99GccOption(c99));
  }

  if( ret != 0 )
	  fatal_error("Failed to execute semantic check command", false);
  
  std::ifstream res_file( combineFilePath(dir, fname, ".res").data() );
  if( !res_file.is_open() )
	  fatal_error("Unable to open file", false);

  char res[50]; 
  res_file.getline(res, ARRAY_LEN(res));
  res_file.close();

  if(DBG) rv_errstrm << "Semchk result: \"" << res <<"\" \n";

  result = get_result_code(is_unitrv, is_mutual_check, res);

  switch (result) {
	  case UNKNOWN      : rv_errstrm << "*** RVT Error:  Unexpected result of semantic check command. Assuming not equal. \n";
			              break;
	  case SUCCESS      : return true;
	  case FAIL         : return false;
	  case TIMEOUT      : rv_errstrm << "*** RVT Warning:  Time-out. \n";
	                      break;
	  case UNCOMPILABLE : rv_errstrm << "*** RVT Error:  Uncompilable. \n";
                          break;
	  default :           break;
  }

  if (abortIfUnknownCbmcErr)
      fatal_error("CBMC has failed for an unknown reason. Set -continue_on_fail command line option to overrule this abort.", false);
  return false;
}


int RVCommands::run_minisat(const string& opbFile, const string& assignmentFile) {
    return runScript("rv_minisat", unixStylePath(opbFile), unixStylePath(assignmentFile));
}

const std::string RVCommands::c99GccOption(bool c99) {
	return c99 ? "-std=c99" : " ";
}

void RVCommands::setPathDelim(const std::string& delimiter) {
	pathDelim.assign(delimiter);
}


void RVCommands::setRvtLoc(const std::string& location) {
	string unixPath = unixStylePath(location);
	rvtLoc.assign(fileExists(unixPath, true) ? 
		              unixPath : unsafeCygpath(location));
}


static bool replaceAndInsertInString(string& str, const string& pattern,
								     const char *substitution, // NULL if no wish to replace
		                             int nInserts = 0, const char *insertion = NULL)
{
	const size_t Over = INT_MAX;
	bool patFound = false;

	for (size_t found = str.rfind(pattern);
		 found != string::npos && found != Over;
		 found = found == 0 ? Over : str.rfind(pattern, found-1))
	{
		patFound = true;
		if (substitution != NULL)
			str.replace(found, pattern.length(), substitution);
		for (int i = 0; i < nInserts; ++i)
			str.insert(found, insertion);
	}

	return patFound;
}


std::string RVCommands::unixStylePath(const std::string &path) const {
	string result(path);

	if (!pathDelim.compare(Slash)) {
		replaceAndInsertInString(result, " ", NULL, 1, BackSlash);
		return result;
	}

	static const char *tempDir = getenv("TEMP");
	static map<string, string> cache;

	//Avoid running a shell command if the given path has once been converted:
	map<string, string>::const_iterator it = cache.find(path);
	if (it != cache.end())
		return it->second;
	
	//The given path is being converted for the first time:
	string tripleBackSlashPath(path);
	if (!replaceAndInsertInString(tripleBackSlashPath, BackSlash, NULL, 2, BackSlash))
		return result; //If path contains no delimiters, there is no need to convert it

	std::ostringstream com_strm, tempFilePath;
	tempFilePath << tempDir << BackSlash << "rvtmp" << rand();
	com_strm << "cmd /c sh -c \"cygpath -u \'" << tripleBackSlashPath << "\' 2> /dev/null \" > " << tempFilePath.str();
	if (exec(com_strm.str()) == 0) {
		char unixPathBuf[8196];
		ifstream reader(tempFilePath.str().data(), ifstream::in);
		reader.getline(unixPathBuf, 8195);
		reader.close();
		remove(tempFilePath.str().data());
		result.assign(unixPathBuf);
	}
	else
		result.assign(unsafeCygpath(path));

	replaceAndInsertInString(result, " ", NULL, 1, BackSlash);

	cache.insert(map<string, string>::value_type(path, result));
	return result;
}


//This method runs if cygpath -u ... failed
std::string RVCommands::unsafeCygpath(const std::string &path) const {
	string result(path);

	replaceAndInsertInString(result, BackSlash, Slash);
	if (path.length() >= 2 && isalpha(path.at(0)) && path.at(1) == ':') {
		result.replace(0, 2, 1, tolower(path[0])); //C: replaced with c
		result.insert(0, "/cygdrive/");
	}

	return result;
}


bool RVCommands::fileExists(const std::string& unixPath, bool hasToBeDir) const 
{
	return true;
	const int successStatus = 253;
	std::ostringstream com_strm;
	com_strm << "tcsh -c \"if (-" << (hasToBeDir? "d \'" : "e \'") << unixPath
			 << "\' ) exit(" << successStatus << ")\"";
	int errorlevel = exec(com_strm.str());
	return errorlevel == successStatus || errorlevel == successStatus << 8;
}


bool RVCommands::isAbsolutePath(const std::string& path) const {
	string unixPath = unixStylePath(path);
	return unixPath.compare(0, strlen(Slash), Slash) == 0;
}


string RVCommands::combineFilePath(const string &dir, const string &filename, const char *ext  /*=NULL*/) const
{
	string combinedFilePath = isAbsolutePath(filename) ? filename : dir + filename;
	return ext == NULL ? combinedFilePath : combinedFilePath.append(ext);
}

RVCommands::ResCode RVCommands::get_result_code( bool is_unitrv, bool is_mutual_check, char * res )
{
	ResCode r;
	const char** matching_code_name_list;
	if (is_unitrv){
		if (is_mutual_check){
			matching_code_name_list = unitrv_mutual_termination_res_code_names;
		}
		else{
			matching_code_name_list = unitrv_res_code_names;
		}
	}
	else{
		matching_code_name_list = res_code_names;
	}
	
	for(int i = 0; i<=UNCOMPILABLE; ++i)
		if( strncmp(res, matching_code_name_list[i], strlen(matching_code_name_list[i])) == 0 )
			r = (ResCode)i;

	return r;

}

