#ifndef RV_SUM_H
#define RV_SUM_H
#include <string.h>
#include <map>
#include <sstream>
#include <fstream>
#include <vector>
#include "rv_funcpair.h"
#include "rv_commands.h"

using std::string;
using std::map;
using std::fstream;

class RVSummarizer
{

private:
	map<string, string> func_to_summary;
public:

	RVSummarizer(const string& func, const string& file_path, RVCommands* rv_commands, int side);
	~RVSummarizer(void);
	string getSummary( string name );

private:

	void convertSummarizerResults( const string& func );
	void addLineToMap( const std::string& line );
	
};




#endif