#include "rv_framasum.h"


RVRecursiveFunctionLocator::RVRecursiveFunctionLocator(Project* _tree)
	: RVWalk(true), parseTree(_tree){

		currStmnt = get_glob_stemnt(parseTree);
}

RVRecursiveFunctionLocator::~RVRecursiveFunctionLocator(){

}

bool RVRecursiveFunctionLocator::finished()
{

	return currStmnt == NULL;
}

string RVRecursiveFunctionLocator::nextRecursiveFunction()
{
	for(; currStmnt; currStmnt = currStmnt->next) {
		if (currStmnt->isFuncDef()){
			currName = ((FunctionDef*) currStmnt)->FunctionName()->name;
			wasFound = false;
			process_block((FunctionDef*) currStmnt);
			//if (wasFound){
			if (true){
				currStmnt = currStmnt->next;
				return currName;
			}
		}
	}
	return "";
}

bool RVRecursiveFunctionLocator::process(Expression* it){
	if (it->etype == ET_FunctionCall){
		FunctionCall* fc = (FunctionCall*) it;
		string name = ((Variable*) fc->function)->name->name;
		if (name.compare(currName) == 0) wasFound = true;

	}
	go(it);
	return true;
}

RVMockIntervalReplacer::RVMockIntervalReplacer(Project* _tree)
		: RVWalk(true), returnCount(0), parseTree(_tree){
}


RVMockIntervalReplacer::~RVMockIntervalReplacer(void){

}

void RVMockIntervalReplacer::replaceRecursiveCalls(){
	
	for(Statement* currStmnt = get_glob_stemnt(parseTree); currStmnt; currStmnt = currStmnt->next) {
		if (currStmnt->isFuncDef()){
			if (functionToInterval.find(((FunctionDef*) currStmnt)->FunctionName()->name) != functionToInterval.end()){
				currFuncName = ((FunctionDef*) currStmnt)->FunctionName()->name;
				process((FunctionDef*) currStmnt);
			}
		}
	}
}

bool RVMockIntervalReplacer::try_replace(Expression** it){

	if ((*it) -> etype == ET_FunctionCall ){
		FunctionCall* fc = (FunctionCall*) *it;
		string name = ((Variable*) fc->function)->name->name;
		if (name.compare(currFuncName) != 0 && name.compare(framacIntervalFunction) != 0) return true;
		
		Symbol* symbolFuncName = new Symbol();
		symbolFuncName -> name = framacIntervalFunction;
		Expression* framaName = new Variable(symbolFuncName, (*it)->location);
		
		IntConstant* top = new IntConstant(functionToInterval[currFuncName].top, false, (*it)->location);
		IntConstant* bottom = new IntConstant(functionToInterval[currFuncName].bottom, false, (*it)->location);

		
		FunctionCall* framaCall = new FunctionCall(framaName, (*it)->location);
		framaCall->addArg(bottom);
		framaCall->addArg(top);
		*it = framaCall;
	}
	return true;
}


bool RVMockIntervalReplacer::foundFunction( Statement* st, string funcName )
{
	return st->isFuncDef() && ((FunctionDef*) st)->FunctionName()->name.compare(funcName) == 0;
}

void RVMockIntervalReplacer::insertInitialReturnValueOfFunction(string funcName, int bottom, int top){
	
	FramaInterval prevInterval;
	prevInterval.bottom = bottom;
	prevInterval.top = top;

	prevFunctionToInterval[funcName] = prevInterval;
	
	FramaInterval interval;
	interval.bottom = bottom;
	interval.top = top;

	functionToInterval[funcName] = interval;
}

void RVMockIntervalReplacer::updateReturnValueOfFunction(string funcName, int bottom, int top)
{
	if (functionToInterval.find(funcName) == functionToInterval.end()) return;

	FramaInterval prevInterval;
	prevInterval.bottom = functionToInterval[funcName].bottom;
	prevInterval.top = functionToInterval[funcName].top;

	prevFunctionToInterval[funcName] = prevInterval;

	FramaInterval interval;
	interval.bottom = bottom;
	interval.top = top;

	functionToInterval[funcName] = interval;

}

void RVMockIntervalReplacer::print( RVTemp* mtemps )
{
	for(Statement* currStmnt = get_glob_stemnt(parseTree); currStmnt; currStmnt = currStmnt->next) {
		currStmnt->print(mtemps->get_strm(), 0);
	}
}

FramaInterval RVMockIntervalReplacer::getIntervalOf(string funcName){
	if (functionToInterval.find(funcName) != functionToInterval.end()){
		return functionToInterval[funcName];
	}

	FramaInterval g;
	g.bottom = FRAMA_MIN_INT;
	g.top = FRAMA_MAX_INT;
	return g;
}

bool RVMockIntervalReplacer::didIntervalsChange()
{
	typedef map<string, FramaInterval>::iterator it_type;
	for(it_type iterator = functionToInterval.begin(); iterator != functionToInterval.end(); iterator++) {
		FramaInterval curr = iterator->second;
		FramaInterval old = prevFunctionToInterval[iterator->first];

		if (curr.bottom != old.bottom || curr.top != old.top) return true;
	}

	return false;
}





RVFramaSum::RVFramaSum(Project* _tree, RVTemp* _temps, RVCommands* _rv_commands)
	: parseTree(_tree), mtemps(_temps), rv_commands(_rv_commands), lieCounter(0), isFirstRound(true){
		replacer = new RVMockIntervalReplacer(_tree);
}

RVFramaSum::~RVFramaSum(void)
{
}

void RVFramaSum::start(bool frama = true){
	if (frama){
		noValueAnalysis = false;
	}
	else{
		noValueAnalysis = true;
		return;
	}

	isFirstRound = true;

	assembleRecursiveFunction();

	while (haventReachedFixedPointYet()){
		replaceCallsWithIntervals();

		runFrama();
		/*updateRecursiveFunctionIntervals();*/
		lieCounter++;
		isFirstRound = false;
	}
}


void RVFramaSum::assembleRecursiveFunction(){
	RVRecursiveFunctionLocator* locator = new RVRecursiveFunctionLocator(parseTree);
	string funcName;
	while (!(funcName = locator->nextRecursiveFunction()).empty()){
		replacer->insertInitialReturnValueOfFunction(funcName, FRAMA_MIN_INT, FRAMA_MAX_INT);
	}

}

bool RVFramaSum::haventReachedFixedPointYet()
{
	return isFirstRound || replacer->didIntervalsChange();
}

void RVFramaSum::replaceCallsWithIntervals()
{
	replacer->replaceRecursiveCalls();
}


std::vector<std::string> &RVFramaSum::split(const std::string &s, char delim, std::vector<std::string> &elems) {
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}


std::vector<std::string> RVFramaSum::split(const std::string &s, char delim) {
	std::vector<std::string> elems;
	split(s, delim, elems);
	return elems;
}



void RVFramaSum::runFrama()
{
	RVDischarger discharger;
	if (!mtemps->open(discharger, framacInputFileName, false, std::ios_base::out )) {
		throw "Unable to open file";
	}

	replacer->print(mtemps);
	mtemps->flush();
	mtemps->close(discharger);

	vector<string>* result = rv_commands->runFrama();

	for (int i = 0 ; i < result->size() ; i++){
		std::string line = result->at(i);
		vector<string> splitted = split(line, '|');
		vector<string> splittedInterval = split(splitted[1], ',');
		int bottom = stoi(splittedInterval[0]);
		int top = stoi(splittedInterval[1]);
		replacer->updateReturnValueOfFunction(splitted[0], bottom, top);
	}

}

string RVFramaSum::getIntervalCondition(std::string s){

	if (noValueAnalysis) return "1";

	FramaInterval interval = replacer->getIntervalOf(s);
	stringstream ss;
	ss << "retval <= " << interval.top << " && retval >= " << interval.bottom;


	return ss.str();
}
