#include "rv_summarizer.h"



std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}


RVSummarizer::RVSummarizer(const string& func, const string& file_path, RVCommands* rv_commands, int side)
{
	rv_commands->runSummarizer(func, file_path, side);
	convertSummarizerResults(func);
}


RVSummarizer::~RVSummarizer(void)
{
}

void RVSummarizer::convertSummarizerResults( const string& func )
{
	string fileName(func + ".sumres");
	std::ifstream infile(fileName);


	std::string line;
	while (std::getline(infile, line))
	{
		addLineToMap(line);
	}
}

void RVSummarizer::addLineToMap( const std::string& line )
{
	std::vector<string> splittedLine = split(line, ':');
	func_to_summary[splittedLine[0]] = splittedLine[1];
}

string RVSummarizer::getSummary( string name )
{
	if (func_to_summary.find( name ) != func_to_summary.end()){
		return func_to_summary[name];
	}
	else return "1";
}
