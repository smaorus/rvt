#pragma once
#include <string>
#include <rv_walk.h>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <limits>
#include <cmath>
#include <basetsd.h>
#include "rv_temps.h"
#include "rv_commands.h"

using std::string;
using std::vector;
using std::map;
using std::stringstream;

#define FRAMA_MAX_INT INT_MAX 
#define FRAMA_MIN_INT (INT_MIN + 1)

typedef struct FramaInterval{
	int bottom;
	int top;

} FramaInterval;

class RVMockIntervalReplacer:
	public RVWalk
{

private:
	Project* parseTree;
	int returnCount;
	bool foundFunction( Statement* st, string funcName );

	virtual bool try_replace(Expression** it);
	std::map<string, FramaInterval> functionToInterval;
	std::map<string, FramaInterval> prevFunctionToInterval;

	string currFuncName;

public:
	RVMockIntervalReplacer(Project* _tree);
	~RVMockIntervalReplacer(void);

	void updateReturnValueOfFunction(string funcName, int bottom, int top);
	void insertInitialReturnValueOfFunction(string funcName, int bottom, int top);
	FramaInterval getIntervalOf(string funcName);
	void replaceRecursiveCalls();
	void print( RVTemp* mtemps );
	bool didIntervalsChange();
};


const std::string framacIntervalFunction = "Frama_C_interval";
const std::string framacInputFileName = "frama.c";

class RVRecursiveFunctionLocator:
	public RVWalk
{

private:
	Project* parseTree;
	Statement* currStmnt;
	string currName;
	bool wasFound;

public:
	RVRecursiveFunctionLocator(Project* _tree);
	~RVRecursiveFunctionLocator(void);
	bool finished();
	string nextRecursiveFunction();
	virtual bool process(Expression* it);
};






class RVFramaSum
{
private:
	Project* parseTree;
	RVTemp* mtemps;
	RVMockIntervalReplacer* replacer;
	RVCommands* rv_commands;
	bool noValueAnalysis;

	std::vector<std::string> split(const std::string &s, char delim);
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

	int lieCounter;
	bool isFirstRound;

	void assembleRecursiveFunction();
	bool haventReachedFixedPointYet();
	void replaceCallsWithIntervals();
	void runFrama();

public:
	RVFramaSum(Project* _tree, RVTemp* temps, RVCommands* rv_commands);
	~RVFramaSum(void);

	void start(bool frama);
	std::string getIntervalCondition(std::string s);

	RVFramaSum intersectWith(RVFramaSum sum);
};

