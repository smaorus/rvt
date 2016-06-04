#ifndef RV_COMMANDS_H
#define RV_COMMANDS_H

#include <iostream>
#include <map>
#include <vector>
#include <string>

#define FRAMA_PARSER_PATH "C:/NewRVT/tools/scripts/FramacDecoder.exe"
#define FRAMA_SCRIPT_NAME "frama"
#define FRAMA_PARSED_FILE "frama_out_parsed.txt"

class RVCommands
{
	friend class RVRelativePath;

  public:
	typedef enum { UNKNOWN = -1, SUCCESS = 0, FAIL, TIMEOUT, UNCOMPILABLE, ILLEGAL_ID, IO_ERROR} ResCode;

  protected:	
	static const char* res_code_names[4];
	static const char* unitrv_res_code_names[4];
	static const char* unitrv_mutual_termination_res_code_names[4];
	static const std::string NO_ARG;

	std::string pathDelim;
	std::string rvtLoc;
	ResCode result;

	int  exec(const std::string& cmd) const;
	int  runScript(const std::string &script,
			       const std::string& arg1 = NO_ARG,
			       const std::string& arg2 = NO_ARG,
			       const std::string& arg3 = NO_ARG,
			       const std::string& arg4 = NO_ARG,
			       const std::string& arg5 = NO_ARG,
			       const std::string& arg6 = NO_ARG);

	std::string unixStylePath(const std::string &path) const;
	std::string unsafeCygpath(const std::string &path) const;
	bool fileExists(const std::string &unixPath, bool hasToBeDir) const;
	bool isAbsolutePath(const std::string& path) const;
	static const std::string c99GccOption(bool c99);

  public:
	RVCommands(void);

	void mkdir(const std::string& dir);

	bool runSummarizer(const std::string& funcName, const std::string& filePath, int size);

	std::vector<std::string>* runFrama();

	bool cpp(const std::string& in_file_name, const std::string& out_file_name);
	bool outline_header(const std::string& prefix_file, const std::string& in_file_name);
	bool outline_type_specific(const std::string& prefix_file);
	void check_syntax(const std::string in_file0, const std::string in_file1, bool c99);
	bool cil(const std::string in_file, const std::string out_file); 
	/* the check itself - returns true on success. */
	bool run_sem_check(const std::string& dir, const std::string& fname, int K = 0, int timeout = 0, bool abortIfUnknownCbmcErr = true, bool c99 = false, bool is_unitrv = false, bool is_mutual_check = false);

	ResCode get_result_code( bool is_unitrv, bool is_mutual_check, char * res );

	bool run_outline_mod(const std::string& fname);
	int  run_minisat(const std::string& opbFile, const std::string& assignmentFile);

	ResCode get_result(void);

	void setPathDelim(const std::string& delimiter);
	void setRvtLoc(const std::string& location);

	std::string combineFilePath(const std::string &dir,
			                    const std::string &filename,
			                    const char *ext = NULL) const;
};


extern RVCommands rv_commands;
extern const char *Slash, *BackSlash;


#endif  /* RV_COMMANDS_H */
