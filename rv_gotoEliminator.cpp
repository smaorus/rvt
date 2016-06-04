
#include  "rv_gotoEliminator.h"
#include <basetsd.h>

using namespace std;

template <class T> void attachVectors(vector<T>* v1, vector<T>* v2){
	for (unsigned int i = 0 ; i < v2 -> size() ; i++){
		v1 -> push_back(v2 -> at(i));
	}
}

vector<Statement*>* GotoEliminator::m_labels;
vector<IfStemnt*>* GotoEliminator::m_conditionalGotoStatements;
map<IfStemnt*, Statement*>* GotoEliminator::m_gotoStatementsToLabelVariables;
IfStemnt* GotoEliminator::m_currentGotoStatement;
map<string, SymEntry*>* GotoEliminator::m_varNamesToSymbolEntries;
int GotoEliminator::m_currentSwitchVariableIndex = 0;
int GotoEliminator::m_currenHelperBreakVariableIndex = 0;
bool GotoEliminator::m_debug = false;

bool GotoEliminator::gotoStatementExists(TransUnit* unit)
{
	return gotoStatementExistsInBlock(unit->head);
}

bool GotoEliminator::gotoStatementExistsInBlock(Statement* firstStatementInBlock){
	for (Statement *statement = firstStatementInBlock; statement; statement = statement->next)
	{
		if (statement->statementContainsBlock()){
			vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				if (gotoStatementExistsInBlock(b->at(i)->head)){
					return true;
				}
			}
		}
		if (statement->type == ST_GotoStemnt){
			return true;
		}
	}

	return false;
}

///<summary>
///This function is the only public function of the goto eliminator. It receives
///a c program as a TransUnit data structure and traverses through its functions.
///For each function it calls 'removeGotoFromFunction' to remove the goto statements
///in it.
///</summary>
///<param name="unit">Data structure representing a c program </param>
void GotoEliminator::removeGoto(TransUnit* unit, bool debug){
	m_debug = debug;
	for (Statement *statement = unit->head; statement; statement = statement->next)
	{
		if (statement -> isFuncDef()){
			statement->print(cout, 0);

			removeGotoFromFunction((FunctionDef*) statement, unit);
		}
	}
}

///<summary>
///This function receives a function and looks for goto statements in it, when
///detected, the function eliminates them.
///</summary>
///<param name="unit">Data structure representing a c program </param>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
void GotoEliminator::removeGotoFromFunction(FunctionDef* funcDef, TransUnit* unit){
	if (funcDef->head == NULL){
		return; // No empty functions
	}
	
	printDebugInfo("Removing goto statements from:", funcDef);
	m_varNamesToSymbolEntries = new map<string, SymEntry*>();
	setupGotoStatements(funcDef);

	setupLabelData(funcDef);
	
	initializeMapBetweenGotosAndLabelVariables();

	printDebugInfo("Function after setting up label variables:", funcDef);
	//Traverse through all goto statements and remove them
	for (unsigned int i = 0 ; i < m_conditionalGotoStatements -> size() ; i++){

		m_currentGotoStatement =  m_conditionalGotoStatements -> at(i);
		printDebugInfo("Removing following goto statement:", m_currentGotoStatement);

		Statement* matchingLabel = getMatchingLabel(m_currentGotoStatement);

		makeGotoStatementDirectlyRelatedToMatchingLabel(m_currentGotoStatement, matchingLabel, funcDef);
		printDebugInfo("Goto Statement should be directly related to matching label:", funcDef);

		if (!areSiblings(m_currentGotoStatement, matchingLabel, funcDef)){
			if (levelOf(m_currentGotoStatement, funcDef) > levelOf(matchingLabel, funcDef)){
				moveGotoStatementOutToLevelOf(m_currentGotoStatement, matchingLabel, funcDef);
				printDebugInfo("Moved goto statement to level of matching label:", funcDef);
			}
			else {
				if (offsetOf(m_currentGotoStatement, funcDef) > offsetOf(matchingLabel, funcDef)){
					liftGotoStatement(m_currentGotoStatement, matchingLabel, funcDef);
					printDebugInfo("Goto statement was lifted above matching label", funcDef);
				}
				moveGotoStatementIn(m_currentGotoStatement, matchingLabel, funcDef);
				printDebugInfo("Goto statement was moved into matching label level", funcDef);
			}
		}
		if (offsetOf(m_currentGotoStatement, funcDef) < offsetOf(matchingLabel, funcDef)){
			eliminateGotoStatementWithCondition(m_currentGotoStatement, funcDef);
			printDebugInfo("Removed goto statement with condition", funcDef);
		}
		else{
			eliminateGotoStatementWithDoWhile(m_currentGotoStatement, funcDef);
			printDebugInfo("Removed goto statement with do while", funcDef);
		}
	}
}

///<summary>
///This function looks for all labels and all the statements before those labels and stores them.
///Later these statements will be used for future processing.
///</summary>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
void GotoEliminator::setupLabelData( FunctionDef* funcDef )
{
	setLabelVector(funcDef);

	introduceLabelVariables(funcDef);
}

void GotoEliminator::setLabelVector( FunctionDef* funcDef )
{
	m_labels = getAllLabels(funcDef);
}

///<summary>
///This function returns a vector of all statements with labels.
///</summary>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
vector<Statement*>* GotoEliminator::getAllLabels(Block* funcDef){
	vector<Statement*>* labels = new vector<Statement*>();
	for (Statement *statement = funcDef->head; statement; statement = statement->next)
	{
		if (statement->statementContainsBlock()){
			vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				vector<Statement*>* labelsInBlock = getAllLabels(b->at(i));
				attachVectors(labels, labelsInBlock);
			}
			
		}
		if (statement -> labels.size() == 1 
			&& statement->labels.at(0)->type != LT_Case 
			&& statement->labels.at(0)->type != LT_Default){
			labels -> push_back(statement);
		}
	}

	return labels;
}

///<summary>
///This function adds a new variable for each statement. This function adds a declaration for each
///variable in the beginning of funcDef and also initializes it to false. Additionally it adds
///a statement that puts false into the variable right under its corresponding label.
///</summary>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
void GotoEliminator::introduceLabelVariables(FunctionDef* funcDef){
	addLabelVariableDeclerations(funcDef);
	addFalseAssignmentToLabelVariableAfterLabel(funcDef);
}

///<summary>
///This function adds a new variable for each statement. This function adds a declaration for each
///variable in the beginning of funcDef and also initializes it to false.
///</summary>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
void GotoEliminator::addLabelVariableDeclerations(FunctionDef* funcDef)
{
	vector<string>* newVariableNames = new vector<string>();
	for (unsigned int i = 0 ; i < m_labels -> size() ; i++){
		Statement* labelStemnt = m_labels -> at(i);
		newVariableNames -> push_back(labelStemnt-> labels[0] -> name -> name);
	}

	Location l = funcDef -> head -> location;

	DeclStemnt* declStatement = new DeclStemnt(l);

	for (unsigned int i = 0 ; i < newVariableNames -> size() ; i++){
		Symbol* symbol = new Symbol();
		symbol -> name = "rv_goto_" + newVariableNames->at(i);
		
		BaseType * type = new BaseType(BT_Bool);

		Decl* decl = new Decl();
		decl -> name = symbol;
		decl -> form = type;
		decl -> initializer = new IntConstant(0, false, l);

		symbol->entry = gProject->Parse_TOS->transUnit->contxt.syms->Insert(mk_vardecl(symbol -> name, decl));
		
		symbol->entry->scope->level = 3; //1 is general scope and 2 is file scope. 3 is function scope

		(*m_varNamesToSymbolEntries)[symbol->name] = symbol->entry;
		declStatement -> addDecl(decl);
	}
	if (declStatement->decls.size() > 0){
		funcDef -> insert(declStatement);
	}
}

///<summary>
///This function adds an expression statement which is an assignment of false to the goto 
///variable. It adds it right after the label itself.
///</summary>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
void GotoEliminator::addFalseAssignmentToLabelVariableAfterLabel(FunctionDef* funcDef){
	vector<Statement*>* newLabeledStatements = new vector<Statement*>();
	for (unsigned int i = 0 ; i < m_labels->size() ; i++){
		Statement* labeledStatement = m_labels->at(i);
		Statement* newLabeledStatement = createFalseAssignment(labeledStatement, "rv_goto_" + labeledStatement->labels[0]->name->name);

		newLabeledStatement -> labels = labeledStatement -> labels;
		labeledStatement -> labels = LabelVector();
		labeledStatement->insertBefore(newLabeledStatement, funcDef);

		m_labels->at(i) = newLabeledStatement;
	}
}

Statement* GotoEliminator::createFalseAssignment(Statement* statement, string varName){
	Location labelLocation(statement -> location.line + 1, statement -> location.column, statement -> location.file);
	return new ExpressionStemnt(varName, getMatchingSymEntry(varName), 0, labelLocation);
}

///<summary>
///This function makes sure all gotos are under an if statement. If a goto doesn't have an if statement
///around it, then a trivial if statement is created. Also updates the goto statement list.
///</summary>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
void GotoEliminator::setupGotoStatements(FunctionDef* funcDef){
	vector<GotoStemnt*>* gotoStatementsInFunction = getAllGotoStatements(funcDef);
	m_conditionalGotoStatements = ensureAllGotoStatementsAreUnderCondition(gotoStatementsInFunction, funcDef);
}

///<summary>
///This function traverses through the function and locates all goto statements.
///</summary>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
vector<GotoStemnt*>* GotoEliminator::getAllGotoStatements(Block* funcDef){

	vector<GotoStemnt*>* gotoStatements = new vector<GotoStemnt*>();
	for (Statement *statement = funcDef->head; statement; statement = statement->next)
	{
		if (statement->statementContainsBlock()){
			vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				vector<GotoStemnt*>* gotosInBlock = getAllGotoStatements(b->at(i));
				attachVectors(gotoStatements, gotosInBlock);
			}
		}
		else if (statement -> type == ST_GotoStemnt){
			gotoStatements -> push_back((GotoStemnt*)statement);
		}
	}

	return gotoStatements;
}

///<summary>
///This function traverses through all goto statements and make sure that they are single
///statements under an if statement. If a goto statement does not follow this rule, a trivial
///if statement is created surrounding the goto statement.
///</summary>
///<param name="gotoStatementsInFunction"></param>
///<param name="funcDef">Data structure that represents the current function that
///will have its goto statements removed</param>
vector<IfStemnt*>* GotoEliminator::ensureAllGotoStatementsAreUnderCondition(vector<GotoStemnt*>* gotoStatementsInFunction, FunctionDef* funcDef )
{
	vector<IfStemnt*>* conditionalGotoStatements = new vector<IfStemnt*>();

	for (unsigned int i = 0 ; i < gotoStatementsInFunction -> size() ; i++){
		GotoStemnt* currentGotoStatement = gotoStatementsInFunction -> at(i);
		
		Statement* enclosingBlock = currentGotoStatement->getEnclosingStatement(funcDef);
		
		Block* thenBlk = (Block*)((IfStemnt*)enclosingBlock)->thenBlk;
		if (enclosingBlock != NULL && enclosingBlock -> type == ST_IfStemnt && thenBlk->isStatementSingleInBlock(currentGotoStatement)){
			conditionalGotoStatements -> push_back((IfStemnt*)enclosingBlock);
		}
		else{
			IfStemnt* conditionalGotoStatement = createTrivialIfStatement(currentGotoStatement);
			currentGotoStatement->replaceWith(conditionalGotoStatement, funcDef);
			conditionalGotoStatements -> push_back(conditionalGotoStatement);
		}
	}

	return conditionalGotoStatements;
}

///<summary>
///This function returns an if statement which contains the given goto statement and has
///a trivial condition of 'true'.
///false otherwise.
///</summary>
///<param name="block">The block in question</param>
IfStemnt* GotoEliminator::createTrivialIfStatement(GotoStemnt* currentGotoStatement)
{
	Block* thenBlk = new Block(currentGotoStatement -> location);
	thenBlk -> head = new GotoStemnt(*currentGotoStatement);

	Location labelLocation(thenBlk -> location.line + 1, thenBlk -> location.column, thenBlk -> location.file);
	IntConstant* condition = new IntConstant(1, false, labelLocation);

	IfStemnt* ifStemnt = new IfStemnt(condition, thenBlk, thenBlk -> location);
	ifStemnt -> next = currentGotoStatement -> next;
	thenBlk -> head -> next = NULL;

	return ifStemnt;
}

///<summary>
///This function initializes with m_gotoStatementsToLabelVariables where the keys are 
///goto statements and values are their matching label statements.
///</summary>
void GotoEliminator::initializeMapBetweenGotosAndLabelVariables(){
	m_gotoStatementsToLabelVariables = new map<IfStemnt*, Statement*>();
	for (unsigned int i = 0 ; i < m_conditionalGotoStatements -> size() ; i++){
		
		IfStemnt* conditionalGotoStatements = m_conditionalGotoStatements -> at(i);
		GotoStemnt* gotoStatement = (GotoStemnt*)((Block*) conditionalGotoStatements -> thenBlk) -> head;
		string correspondingLabelName = gotoStatement -> dest -> name;

		for (unsigned int i = 0 ; i < m_labels -> size() ; i++){
			Label* firstLabel = m_labels -> at(i) -> labels.at(0);
			string labelName = firstLabel -> syment -> name;
			if (labelName == correspondingLabelName){
				(*m_gotoStatementsToLabelVariables)[conditionalGotoStatements] = m_labels -> at(i);
				break;
			}
		}
	}
}

vector<IfStemnt*>* GotoEliminator::getAllGotoConditionalStatements(FunctionDef* funcDef){
	return m_conditionalGotoStatements;
}

Statement* GotoEliminator::getMatchingLabel(IfStemnt* statement){
	return (*m_gotoStatementsToLabelVariables)[statement];
}

///<summary>
///This function returns true if the given statements are siblings according to the definition
///in the article.
///</summary>
///<param name="gotoStatement">First statement</param>
///<param name="matchingLabel">Second statement</param>
///<param name="funcDef">The block that encloses both statements</param>
bool GotoEliminator::areSiblings(Statement* firstStatement, Statement* secondStatement, Block* funcDef){

	for (Statement *statement = funcDef->head; statement; statement = statement->next)
	{
		if (statement == firstStatement || statement == secondStatement){
			if (statement -> next == NULL){
				return false;
			}
			for (Statement *innerStatement = statement->next; innerStatement; innerStatement = innerStatement->next)
			{
				if (innerStatement == firstStatement || innerStatement == secondStatement){
					return true;
				}
			}
			continue;
		}

		if (statement->statementContainsBlock()){
			vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				bool blockResult = areSiblings(firstStatement, secondStatement, b->at(i));
				if (blockResult){
					return true;
				}
			}
		}
	}
	return false;
}

///<summary>
///This function returns true if the given statements are directly related according to the definition
///in the article.
///</summary>
///<param name="gotoStatement">First statement</param>
///<param name="matchingLabel">Second statement</param>
///<param name="funcDef">The block that encloses both statements</param>
bool GotoEliminator::directlyRelated(IfStemnt* gotoStatement, Statement* matchingLabel, Block* funcDef){
	
	for (Statement *statement = funcDef->head; statement; statement = statement->next)
	{
		Statement* statementToLook = NULL;
		
		if (statement == gotoStatement){
			statementToLook = matchingLabel;
		}
		else if (statement == matchingLabel){
			statementToLook = gotoStatement;
		}

		if (statementToLook != NULL){
			return funcDef->statementIsInBlock(statementToLook);
		}
	}

	for (Statement *statement = funcDef->head; statement; statement = statement->next)
	{
		if (statement->statementContainsBlock()){
			vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				if (directlyRelated(gotoStatement, matchingLabel, b->at(i))){
					return true;
				}
			}
		}
	}
	return false;
}

///<summary>
///This function calculates the level of a given statement in a given function definition
///according to the definition in the paper.
///</summary>
///<param name="statementToFind">The level of this statement is calculated</param>
///<param name="funcDef">The block that encloses the statement</param>
int GotoEliminator::levelOf(Statement* statementToFind, Block* funcDef){
	if (statementToFind == NULL){
		return INT_MAX;
	}
	for (Statement *statement = funcDef->head; statement; statement = statement->next)
	{
		if (statement == statementToFind){
  				return 0;
		}
		else if (statement->statementContainsBlock()){
			vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				int levelFromBlock = levelOf(statementToFind, b->at(i));
				if (levelFromBlock != -1){
					return levelFromBlock + 1;
				}
			}
  		}
	}
	return -1;
}

///<summary>
///This function calculates the offset from the start of the function of a given statement 
///in a given function definition according to the definition in the paper.
///</summary>
///<param name="statementToFind">The offset of this statement is calculated</param>
///<param name="funcDef">The block that encloses the statement</param>
int GotoEliminator::offsetOf(Statement* statementToFind, Block* funcDef){
	if (statementToFind == NULL){
		return -1;
	}

	int offsetCount = 0;
	
	for (Statement *statement = funcDef->head; statement; statement = statement->next)
	{
		if (statement == statementToFind){
			offsetCount++;
			return offsetCount;
		}

		if (statement->statementContainsBlock()){
			vector<Block*>* blocks = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < blocks->size() ; i++){
				Block* block = blocks->at(i);
				if (block->statementIsInBlock(statementToFind)){
					return offsetCount + 1 + offsetOf(statementToFind, block);
				}
				else{
					offsetCount += block->statementCount() + 2;
				}
			}
		}
		else{
			offsetCount++;
		}
	}

	return -1;
}

///<summary>
///This function moves the goto statement out of its enclosing blocks until it becomes directly
///directed to its matching label statement.
///</summary>
///<param name="gotoStatement">The goto statement this function is moving out</param>
///<param name="matchingLabel">The label statement that will be directly related to the goto statement</param>
///<param name="funcDef">The block that encloses all the statements</param>
void GotoEliminator::makeGotoStatementDirectlyRelatedToMatchingLabel(IfStemnt* gotoStatement, Statement* matchingLabel, Block* funcDef){
	while(!directlyRelated(gotoStatement, matchingLabel, funcDef)){
		gotoStatement = moveGotoStatementOutOfEnclosingBlock(gotoStatement, funcDef);
	}
}

IfStemnt* GotoEliminator::moveGotoStatementOutOfEnclosingBlock(IfStemnt* gotoStatement, Block* funcDef){
	Statement* enclosingBlock = gotoStatement->getEnclosingStatement(funcDef);

	StatementType type = enclosingBlock -> type;
	if (type == ST_IfStemnt){
		return moveGotoStatementOutOfIfStatement(gotoStatement, (IfStemnt*) enclosingBlock, funcDef);
	}
	if (type == ST_WhileStemnt){
		return moveGotoStatementOutOfWhileStatement(gotoStatement, (WhileStemnt*) enclosingBlock, funcDef);
	}
	if (type == ST_SwitchStemnt){
		return moveGotoStatementOutOfSwitchStatement(gotoStatement, (SwitchStemnt*) enclosingBlock, funcDef);
	}
	if (type == ST_DoWhileStemnt){
		return moveGotoStatementOutOfDoWhileStatement(gotoStatement, (DoWhileStemnt*) enclosingBlock, funcDef);
	}
	if (type == ST_ForStemnt){
		return moveGotoStatementOutOfForStatement(gotoStatement, (ForStemnt*) enclosingBlock, funcDef);
	}

	return NULL;
}


IfStemnt* GotoEliminator::moveGotoStatementOutOfForStatement(IfStemnt* gotoStatement, ForStemnt* forStemnt, Block* funcDef)
{
	assignConditionToGotoVariable(gotoStatement, (Block*) forStemnt -> block);
	addConditionalBreakStatement(gotoStatement, (Block*) forStemnt -> block);
	return addGotoAfterBlockStatement(gotoStatement, forStemnt);
}

IfStemnt* GotoEliminator::moveGotoStatementOutOfWhileStatement(IfStemnt* gotoStatement, WhileStemnt* whileStemnt, Block* funcDef){
	assignConditionToGotoVariable(gotoStatement, (Block*) whileStemnt -> block);
	addConditionalBreakStatement(gotoStatement, (Block*) whileStemnt -> block);
	return addGotoAfterBlockStatement(gotoStatement, whileStemnt);
}

IfStemnt* GotoEliminator::moveGotoStatementOutOfDoWhileStatement(IfStemnt* gotoStatement, DoWhileStemnt* dowhileStemnt, Block* funcDef)
{
	assignConditionToGotoVariable(gotoStatement, (Block*) dowhileStemnt -> block);
	addConditionalBreakStatement(gotoStatement, (Block*) dowhileStemnt -> block);
	return addGotoAfterBlockStatement(gotoStatement, dowhileStemnt);
}

IfStemnt* GotoEliminator::moveGotoStatementOutOfIfStatement(IfStemnt* gotoStatement, IfStemnt* ifStemnt, Block* funcDef){
	Block* thenBlock = (Block*) ifStemnt -> thenBlk;
	Block* elseBlock = (Block*) ifStemnt -> elseBlk;
	if (thenBlock->statementIsInBlock(gotoStatement)){
		assignConditionToGotoVariable(gotoStatement, (Block*) ifStemnt -> thenBlk);
	}
	else if (elseBlock->statementIsInBlock(gotoStatement)){
		assignConditionToGotoVariable(gotoStatement, (Block*) ifStemnt -> elseBlk);
	}

	putStatemntsAfterGotoUnderCondition(gotoStatement, ifStemnt, ifStemnt->next);
	return addGotoAfterBlockStatement(gotoStatement, ifStemnt);
}

IfStemnt* GotoEliminator::moveGotoStatementOutOfSwitchStatement(IfStemnt* gotoStatement, SwitchStemnt* switchStemnt, Block* funcDef){
	assignConditionToGotoVariable(gotoStatement, (Block*) switchStemnt -> block);
	addConditionalBreakStatement(gotoStatement, (Block*) switchStemnt -> block);
	return addGotoAfterBlockStatement(gotoStatement, switchStemnt);	
}

void GotoEliminator::assignConditionToGotoVariable(IfStemnt* gotoStatement, Block* ifStemnt){
	Expression* gotoCondition = gotoStatement -> cond;
	string matchingGotoVarName = getMatchingGotoVariableName(gotoStatement);
	Variable* gotoVariable = new Variable(matchingGotoVarName, gotoStatement -> location, getMatchingSymEntry(matchingGotoVarName));

	AssignExpr* assignExpr = new AssignExpr(AO_Equal, gotoVariable, gotoCondition, gotoStatement -> location);
	ExpressionStemnt* conditionAssignmentExpr = new ExpressionStemnt(assignExpr, gotoStatement -> location);
	
	gotoStatement->insertBefore(conditionAssignmentExpr, ifStemnt);

	conditionAssignmentExpr->labels = gotoStatement->labels;
	gotoStatement->removeAllLabels();
}

void GotoEliminator::putStatemntsAfterGotoUnderCondition(IfStemnt* gotoStatementIn, IfStemnt* ifStemnt, Statement* statementAfterIfStemnt){
	////if there are no statements after goto there's nothing to put under condition
	//if (gotoStatementIn->next == NULL){
	//	//removing the goto statement after the if
	//	statementAfterIfStemnt -> next = NULL;
	//	return;
	//}

	//create an if statement condition
	string matchingGotoVarName = getMatchingGotoVariableName(gotoStatementIn);
	Variable* labelVariable = new Variable(matchingGotoVarName, gotoStatementIn -> location, getMatchingSymEntry((matchingGotoVarName)));
	UnaryExpr* unaryExpr = new UnaryExpr(UO_Not, labelVariable, gotoStatementIn -> location);

	//put all the statements after the goto statement in the new ifstemnt's thenBlk
	Block* thenBlk = new Block(gotoStatementIn -> location);
	thenBlk -> head = gotoStatementIn -> next;

	//create new goto condition if statemnt
	IfStemnt* conditionalGotoIfStemnt = new IfStemnt(unaryExpr, thenBlk
														, gotoStatementIn -> location);

	//connect the statement before the goto to to the if, check if its the first
	Block* thenBlock = (Block*) ifStemnt -> thenBlk;
	Block* elseBlock = (Block*) ifStemnt -> elseBlk;
	if (thenBlock->statementIsInBlock(gotoStatementIn)){
		gotoStatementIn->insertBefore(conditionalGotoIfStemnt, (Block*) ifStemnt -> thenBlk);
	}
	else if (elseBlock->statementIsInBlock(gotoStatementIn)){
		gotoStatementIn->insertBefore(conditionalGotoIfStemnt, (Block*) ifStemnt -> elseBlk);
	}

	//remove the old goto statement
	conditionalGotoIfStemnt -> next = NULL;
}

void GotoEliminator::addConditionalBreakStatement(IfStemnt* gotoStatement, Block* blockStatement){
	IfStemnt* newIfStemnt = createIfStatementForBreak(gotoStatement);

	gotoStatement->insertBefore(newIfStemnt, blockStatement);

	newIfStemnt -> next = gotoStatement -> next;
	return;
}

IfStemnt* GotoEliminator::createIfStatementForBreak(IfStemnt* gotoStatementIn){
	GotoStemnt* gotoStatement = (GotoStemnt*) ((Block*) gotoStatementIn -> thenBlk) -> head;

	//create break stemnt
	Statement* breakStemnt = new Statement(ST_BreakStemnt, gotoStatement -> location);

	Block* thenBlk = new Block(gotoStatement -> location);
	thenBlk -> head = breakStemnt;
	string matchingVarName = getMatchingGotoVariableName(gotoStatementIn);
	Variable* labelVariable = new Variable(matchingVarName, gotoStatement -> location, getMatchingSymEntry(matchingVarName));

	IfStemnt* ifStemnt = new IfStemnt(labelVariable, thenBlk, thenBlk -> location);
	return ifStemnt;
}

IfStemnt* GotoEliminator::addGotoAfterBlockStatement(IfStemnt* gotoStatement, Statement* blckStemnt){
	IfStemnt* newIfStemnt = createIfStatementFromLabelVars(gotoStatement);

	newIfStemnt -> next = blckStemnt -> next;
	blckStemnt -> next = newIfStemnt;

	replaceOldGotoWithNew((IfStemnt*) gotoStatement, newIfStemnt);
	return newIfStemnt;
}

IfStemnt* GotoEliminator::createIfStatementFromLabelVars(IfStemnt* gotoStatementIn){
	GotoStemnt* gotoStatement = (GotoStemnt*) ((Block*) gotoStatementIn -> thenBlk) -> head;

	Block* thenBlk = new Block(gotoStatement -> location);
	thenBlk -> head = gotoStatement;
	string matchingVarName = getMatchingGotoVariableName(gotoStatementIn);
	Variable* labelVariable = new Variable(matchingVarName, gotoStatement -> location, getMatchingSymEntry(matchingVarName));

	IfStemnt* ifStemnt = new IfStemnt(labelVariable, thenBlk, thenBlk -> location);
	
	return ifStemnt;
}

void GotoEliminator::moveGotoStatementOutToLevelOf(IfStemnt* gotoStatement, Statement* destinationStatement, FunctionDef* funcDef){
	while (levelOf(gotoStatement, funcDef) > levelOf(destinationStatement, funcDef)){
		gotoStatement = moveGotoStatementOutOfEnclosingBlock(gotoStatement, funcDef);
	}
}

void GotoEliminator::replaceOldGotoWithNew(IfStemnt* oldStatement, IfStemnt* newStatement){
	
	// updating the the goto statement list
	for (unsigned int i = 0 ; i < m_conditionalGotoStatements -> size() ; i++){
		if (m_conditionalGotoStatements -> at(i) == oldStatement){
			(*m_conditionalGotoStatements)[i] = newStatement;
		}
	}

	// updating the goto to goto variable name map
	Statement* tempVarName = (*m_gotoStatementsToLabelVariables)[oldStatement];
	m_gotoStatementsToLabelVariables -> erase(oldStatement);
	(*m_gotoStatementsToLabelVariables)[newStatement] = tempVarName;

	// updating the current goto statement
	m_currentGotoStatement = newStatement;
}

Expression* GotoEliminator::createConditionExpressionForIfStemntElseBlkInwardMove(IfStemnt* gotoStatement, Expression * oldExpr)
{
	string matchingVarName = getMatchingGotoVariableName(gotoStatement);
	Variable* gotoVariable = new Variable(matchingVarName, gotoStatement -> location, getMatchingSymEntry(matchingVarName));

	BinaryExpr* newConditionExpression = new BinaryExpr(BO_And, oldExpr, new UnaryExpr(UO_Not, gotoVariable, gotoStatement->location), gotoStatement->location);

	return newConditionExpression;
}

Expression* GotoEliminator::createConditionExpressionForIfStemntThenBlkInwardMove(IfStemnt* gotoStatement, Expression* oldExpr){
	string matchingVarName = getMatchingGotoVariableName(gotoStatement);
	Variable* gotoVariable = new Variable(matchingVarName, gotoStatement -> location, getMatchingSymEntry(matchingVarName));

	BinaryExpr* newConditionExpression = new BinaryExpr(BO_Or, oldExpr, gotoVariable, gotoStatement -> location);

	return newConditionExpression;
}

Block* GotoEliminator::encloseStatementsInBlockIncludeFirst(Statement* first, Statement* last){
	cout << "in enclose" ;
	Block* thenBlk = new Block(first -> location);

	thenBlk -> head = first;
	Statement* tempStatement = first;

	while (tempStatement -> next != last){
		tempStatement = tempStatement -> next;	
	}
	tempStatement -> next = NULL;

	return thenBlk;
}

Block* GotoEliminator::encloseStatementsInBlock(Statement* first, Statement* last){
	Block* thenBlk = new Block(first -> location);

	Statement* tempStatement = first -> next;
	if (tempStatement == last){
		thenBlk -> head = NULL;
		return thenBlk;
	}
	thenBlk -> head = tempStatement;

	while (tempStatement -> next != last){
		tempStatement = tempStatement -> next;
	}
	tempStatement -> next = NULL;

	return thenBlk;
}

void GotoEliminator::putStatemntsAfterGotoBeforeBlockUnderCondition(IfStemnt* gotoStatementIn, Statement* blockStatement, Block* funcDef){
	
	if (gotoStatementIn -> next == blockStatement){
		// the goto statement and the block statement are right next to each other, no need for ifstemnt
		// It is however important to remove the goto statement
		funcDef->removeStatement(gotoStatementIn);
		return; 
	}
	//create an if statement condition
	string matchingVarName= getMatchingGotoVariableName(gotoStatementIn);
	Variable* labelVariable = new Variable(matchingVarName, gotoStatementIn -> location, getMatchingSymEntry(matchingVarName));
	UnaryExpr* unaryExpr = new UnaryExpr(UO_Not, labelVariable, gotoStatementIn -> location);

	//put all the statements after the goto statement in the new ifstemnt's thenBlk

	Block* thenBlk = encloseStatementsInBlock(gotoStatementIn, blockStatement);

	

	IfStemnt* conditionalGotoIfStemnt = new IfStemnt(unaryExpr, thenBlk
														, gotoStatementIn -> location);

	//connect the statement before the goto to to the if, check if its the first
	gotoStatementIn->insertBefore(conditionalGotoIfStemnt, funcDef);
	//remove the old goto statement
	conditionalGotoIfStemnt -> next = blockStatement;

}

IfStemnt* GotoEliminator::createNewGotoStatementInNewBlock(IfStemnt* gotoStatement, Block* newEnclosingBlock){
	IfStemnt* newIfStemnt = createIfStatementFromLabelVars(gotoStatement);

	newEnclosingBlock -> head->insertBefore(newIfStemnt, newEnclosingBlock);

	replaceOldGotoWithNew((IfStemnt*) gotoStatement, newIfStemnt);

	return newIfStemnt;
}





Statement* GotoEliminator::getGotoStatementSiblingBlockThatEnclosesLabel(IfStemnt* gotoStatement, Statement* labelStatement, Block* funcDef){
 	Block* enclosingBlock = gotoStatement->getEnclosingBlock(funcDef);
	
	for (Statement *statement = enclosingBlock -> head; statement; statement = statement -> next)
	{
		if (statement->statementContainsBlock()){
			vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				if (b->at(i)->statementIsInBlock(labelStatement)){
					return statement;
				}
			}
		}
	}
	return NULL;
}

IfStemnt* GotoEliminator::moveGotoStatementIntoIfStatement(IfStemnt* gotoStatement, IfStemnt* ifStemnt, Block* funcDef){
	
	assignConditionToGotoVariable(gotoStatement, funcDef);
	putStatemntsAfterGotoBeforeBlockUnderCondition(gotoStatement, ifStemnt, funcDef);
	Statement* matchingLabel = getMatchingLabel(gotoStatement);
	
	Block* thenBlock = (Block*) ifStemnt -> thenBlk;
	Block* elseBlock = (Block*) ifStemnt -> elseBlk;
	if (thenBlock->statementIsInBlock(matchingLabel)){
		ifStemnt -> cond = createConditionExpressionForIfStemntThenBlkInwardMove(gotoStatement, ifStemnt -> cond);
		return createNewGotoStatementInNewBlock(gotoStatement, (Block*) ifStemnt -> thenBlk);
	}
	else if (elseBlock->statementIsInBlock(matchingLabel)){
		ifStemnt -> cond = createConditionExpressionForIfStemntElseBlkInwardMove(gotoStatement, ifStemnt -> cond);
		return createNewGotoStatementInNewBlock(gotoStatement, (Block*) ifStemnt -> elseBlk);
	}
	return NULL;
}

Block* GotoEliminator::createSwitchStatementPrecedingElseBlock(string switchVariableName, IfStemnt* gotoStatement)
{
	Block* elseBlock = new Block(gotoStatement -> location);
	elseBlock -> head = new ExpressionStemnt(switchVariableName, getMatchingSymEntry(switchVariableName), 1, gotoStatement -> location);
	return elseBlock;
}

Block* GotoEliminator::createSwitchStatementPrecedingThenBlock(string switchVariableName, IfStemnt* gotoStatement, SwitchStemnt* switchStemnt, Block* funcDef){
	AssignExpr* switchVarAssignmentExpression = new AssignExpr(AO_Equal, new Variable(switchVariableName, switchStemnt -> location, getMatchingSymEntry(switchVariableName)), switchStemnt -> cond, switchStemnt -> location);
	ExpressionStemnt* thenBlockSwitchVarAssignmentStemnt = new ExpressionStemnt(switchVarAssignmentExpression, gotoStatement -> location);
	switchStemnt->insertBefore(thenBlockSwitchVarAssignmentStemnt, funcDef);

	Block* thenBlockResult = encloseStatementsInBlock(gotoStatement, switchStemnt);
	return thenBlockResult;
}

void GotoEliminator::createSwitchStatementPrecedingBlock(IfStemnt* gotoStatement, SwitchStemnt* switchStemnt, string switchVariableName, Block* funcDef){
	//create the if statement and remove the goto
	string correspondingGotoVarName = getMatchingGotoVariableName(gotoStatement);
	UnaryExpr* condition = new UnaryExpr(UO_Not, new Variable(correspondingGotoVarName, gotoStatement -> location, getMatchingSymEntry(correspondingGotoVarName)), gotoStatement -> location);

	//creating the else block
	Block* elseBlock = createSwitchStatementPrecedingElseBlock(switchVariableName, gotoStatement);

	//creating the then block
	Block* thenBlock = createSwitchStatementPrecedingThenBlock(switchVariableName, gotoStatement, switchStemnt, funcDef);

	IfStemnt* ifStemnt = new IfStemnt(condition, thenBlock, gotoStatement -> location, elseBlock);
	ifStemnt -> next = switchStemnt;
	gotoStatement -> next = ifStemnt;
}

DeclStemnt* GotoEliminator::addSwitchVariable(IfStemnt* gotoStatement, Block* funcDef)
{
	DeclStemnt* declStatement = new DeclStemnt(gotoStatement -> location);

	vector<Decl*>* decls = new vector<Decl*>();
	Symbol* symbol = new Symbol();
	
	stringstream oss;
	oss << "rv_switch_var_" << m_currentSwitchVariableIndex++;

	symbol -> name = oss.str();
	
	BaseType * type = new BaseType(BT_Bool);
	Decl* decl = new Decl();
	decl -> name = symbol;
	decl -> form = type;
	symbol->entry = gProject->Parse_TOS->transUnit->contxt.syms->Insert(mk_vardecl(symbol -> name, decl));
	(*m_varNamesToSymbolEntries)[symbol->name] = symbol->entry;
	symbol->entry->scope->level = 3 + levelOf(gotoStatement, funcDef);
	declStatement -> addDecl(decl);

	gotoStatement->insertBefore(declStatement, funcDef);
	return declStatement;
}

IfStemnt* GotoEliminator::putGotoStatementInSwitchStatement( IfStemnt* gotoStatement, SwitchStemnt* switchStemnt, string switchVariable, Block* funcDef ){
	string matchingVarName = getMatchingGotoVariableName(gotoStatement);
	Variable* gotoVar = new Variable(matchingVarName, switchStemnt->location, getMatchingSymEntry(matchingVarName));

	IfStemnt* newGotoStatement = new IfStemnt(gotoVar, ((IfStemnt*)gotoStatement) -> thenBlk, switchStemnt->location);
	
	Statement* matchingLabel = getMatchingLabel(gotoStatement);
	Block* enclosingBlock = matchingLabel->getEnclosingBlock(funcDef);

	putNewGotoStatmentAfterMatchingCaseLabel(newGotoStatement, matchingLabel, switchStemnt, funcDef);
	
	//enclosingBlock->setBlockHead(newGotoStatement);
	return newGotoStatement;
}

void GotoEliminator::putNewGotoStatmentAfterMatchingCaseLabel(IfStemnt* newGotoStatement, Statement* matchingLabel, SwitchStemnt* switchStemnt, Block* funcDef)
{
	Statement* fatherCaseStatement = switchStemnt->getFatherCaseStatementOf(matchingLabel);
	if (fatherCaseStatement == NULL){
		throw new std::exception("Unable to find label in switch statement - something is really wrong");
	}

	if (fatherCaseStatement->type == ST_Block){
		((Block*) fatherCaseStatement)->setBlockHead(newGotoStatement);
	}
	else{
		newGotoStatement -> labels = fatherCaseStatement -> labels;
		fatherCaseStatement->removeAllLabels();
		fatherCaseStatement->insertBefore(newGotoStatement, funcDef);
	}
}

IfStemnt* GotoEliminator::moveGotoStatementInSwitchStatement(IfStemnt* gotoStatement, SwitchStemnt* switchStemnt, Block* funcDef){
	assignConditionToGotoVariable(gotoStatement, funcDef);
	//add a deceleration for the switch variable
	
	DeclStemnt* switchVariableDecleration = addSwitchVariable(gotoStatement, funcDef);
	string switchVariableName = switchVariableDecleration->decls.at(0)->name->name;

	createSwitchStatementPrecedingBlock(gotoStatement, switchStemnt, switchVariableName, funcDef);
	
	IfStemnt* newGotoStatement = putGotoStatementInSwitchStatement(gotoStatement, switchStemnt, switchVariableName, funcDef);
	
	switchVariableDecleration -> next = gotoStatement -> next;
	
	switchStemnt->cond = new Variable(switchVariableName, switchStemnt->location, getMatchingSymEntry(switchVariableName));

	replaceOldGotoWithNew((IfStemnt*)gotoStatement, newGotoStatement);
	
	return newGotoStatement;
}

void GotoEliminator::moveGotoStatementIn(IfStemnt* gotoStatement, Statement* labelStatement, Block* funcDef){
	while(levelOf(gotoStatement, funcDef) < levelOf(labelStatement, funcDef)){
		gotoStatement = moveGotoStatementInEnclosingBlock(gotoStatement, labelStatement, funcDef);
	}
}

IfStemnt* GotoEliminator::moveGotoStatementInEnclosingBlock(IfStemnt* gotoStatement, Statement* labelStatement, Block* funcDef){
	Statement* enclosingBlock = 
		getGotoStatementSiblingBlockThatEnclosesLabel(gotoStatement, labelStatement, funcDef);

	StatementType type = enclosingBlock -> type;

	if (type == ST_IfStemnt){
		return moveGotoStatementIntoIfStatement(gotoStatement, (IfStemnt*) enclosingBlock, funcDef);
	}
	if (type == ST_WhileStemnt){
		return moveGotoStatementInWhileStatement(gotoStatement, (WhileStemnt*) enclosingBlock, funcDef);
	}
	if (type == ST_SwitchStemnt){
		return moveGotoStatementInSwitchStatement(gotoStatement, (SwitchStemnt*) enclosingBlock, funcDef);
	}
	if (type == ST_DoWhileStemnt){
		return moveGotoStatementInDoWhileStatement(gotoStatement, (DoWhileStemnt*) enclosingBlock, funcDef);
	}
	if (type == ST_ForStemnt){
		return moveGotoStatementInForStatement(gotoStatement, (ForStemnt*) enclosingBlock, funcDef);
	}
	return NULL;
}

IfStemnt* GotoEliminator::moveGotoStatementInForStatement(IfStemnt* gotoStatement, ForStemnt* forStemnt, Block* funcDef)
{
	assignConditionToGotoVariable(gotoStatement, funcDef);

	putStatemntsAfterGotoBeforeBlockUnderCondition(gotoStatement, forStemnt, funcDef);

	forStemnt->cond = createConditionExpressionForIfStemntThenBlkInwardMove(gotoStatement, forStemnt->cond);

	return createNewGotoStatementInNewBlock(gotoStatement, (Block*) forStemnt -> block);
}

IfStemnt* GotoEliminator::moveGotoStatementInDoWhileStatement(IfStemnt* gotoStatement, DoWhileStemnt* doWhileStemnt, Block* funcDef)
{
	assignConditionToGotoVariable(gotoStatement, funcDef);

	putStatemntsAfterGotoBeforeBlockUnderCondition(gotoStatement, doWhileStemnt, funcDef);

	//whileStemnt -> cond = createConditionExpressionForIfStemntThenBlkInwardMove(gotoStatement, whileStemnt -> cond);

	return createNewGotoStatementInNewBlock(gotoStatement, (Block*) doWhileStemnt -> block);
}

IfStemnt* GotoEliminator::moveGotoStatementInWhileStatement(IfStemnt* gotoStatement, WhileStemnt* whileStemnt, Block* funcDef){\

	assignConditionToGotoVariable(gotoStatement, funcDef);

	putStatemntsAfterGotoBeforeBlockUnderCondition(gotoStatement, whileStemnt, funcDef);

	whileStemnt -> cond = createConditionExpressionForIfStemntThenBlkInwardMove(gotoStatement, whileStemnt -> cond);

	return createNewGotoStatementInNewBlock(gotoStatement, (Block*) whileStemnt -> block);
}
void GotoEliminator::eliminateGotoStatementWithCondition(IfStemnt* gotoStatement, Block* funcDef){
	Statement* matchingLabel = getMatchingLabel(gotoStatement);
	if (gotoStatement->next == matchingLabel){
		funcDef->removeStatement(gotoStatement);
		return;
	}
	Block* enclosingBlock = encloseStatementsInBlock(gotoStatement, matchingLabel);
	IfStemnt* newIfStemnt = 
		new IfStemnt(
			new UnaryExpr(UO_Not, ((IfStemnt*) gotoStatement) -> cond, gotoStatement -> location), 
			enclosingBlock, gotoStatement -> location);

	gotoStatement->insertBefore(newIfStemnt, funcDef);
	newIfStemnt -> next = getMatchingLabel(gotoStatement);
}


void GotoEliminator::eliminateGotoStatementWithDoWhile(IfStemnt* gotoStatement, Block* funcDef){
	Expression* doWhileCondition = gotoStatement -> cond;

	Statement* labelStatement = getMatchingLabel(gotoStatement);

	Block* doWhileBlk = encloseStatementsInBlockIncludeFirst(labelStatement, gotoStatement);

	DoWhileStemnt* doWhileStemnt = new DoWhileStemnt(doWhileCondition, doWhileBlk, labelStatement -> location);

	labelStatement->insertBefore(doWhileStemnt, funcDef);
	doWhileStemnt -> next = gotoStatement -> next;


	treatIncorrectUseOfBreakOrContinue(doWhileStemnt, funcDef);
}

void GotoEliminator::liftGotoStatement(IfStemnt* gotoStatement, Statement* matchingLabel, Block* funcDef){
	string matchingVarName = getMatchingGotoVariableName(gotoStatement);
	Variable* gotoVariable = new Variable(matchingVarName, gotoStatement -> location, getMatchingSymEntry(matchingVarName));
					
	Statement* enclosingBlock = getGotoStatementSiblingBlockThatEnclosesLabel(gotoStatement, matchingLabel, funcDef);
	
	AssignExpr* assignExpr = new AssignExpr(AO_Equal, gotoVariable, gotoStatement -> cond, gotoStatement -> location);
	ExpressionStemnt* gotoVariableAssignment = new ExpressionStemnt(assignExpr, gotoStatement -> location);


	IfStemnt* newIfStemnt = new IfStemnt(gotoVariable, (Block*)gotoStatement -> thenBlk, matchingLabel -> location);

	Statement* afterGoto = gotoStatement -> next;
	Block* block = encloseStatementsInBlockIncludeFirst(enclosingBlock, gotoStatement);
	block->setBlockHead(newIfStemnt);
	block->appendToTail(gotoVariableAssignment);

	DoWhileStemnt* doWhileStemnt = new DoWhileStemnt(gotoVariable, block, matchingLabel -> location);
	enclosingBlock->insertBefore(doWhileStemnt, funcDef);

	doWhileStemnt -> next = afterGoto;
	replaceOldGotoWithNew((IfStemnt*)gotoStatement, newIfStemnt);


	treatIncorrectUseOfBreakOrContinue(doWhileStemnt, funcDef);
}

///<summary>
///This function is called right after a new do while statement is created when lifting the 
///goto statement or when eliminating a goto with a do while. It runs through the body of the
///new do while to look for any break or continue statements that might be related to a 
///surrounding loop or switch. If nothing is done then the break or continue statement will
///be associated with the new do while. Look in paper for more details.
///</summary>
///<param name="doWhileStemnt">The newly created do while statement</param>
///<param name="funcDef">The entire function</param>
void GotoEliminator::treatIncorrectUseOfBreakOrContinue(DoWhileStemnt* doWhileStemnt, Block* funcDef)
{
	vector<Statement*>* badStatements = getIncorrectlyUsedBreakOrContinue((Block*) doWhileStemnt->block, funcDef);
	if (badStatements->size() == 0){
		return;
	}

	for (unsigned int i = 0 ; i < badStatements->size() ; i++){
		Statement* badStatement = badStatements->at(i);

		//add new variable
		string breakVariableName = addIncorrectBreakVariableDefinition(doWhileStemnt, funcDef);

		//insert before break an assignment
		ExpressionStemnt* breakAssignment = new ExpressionStemnt(breakVariableName, getMatchingSymEntry(breakVariableName), 1, badStatement->location);
		badStatement->insertBefore(breakAssignment, funcDef);

		//add an if after the do while with that variable.
		Variable* cond = new Variable(breakVariableName, badStatement->location, getMatchingSymEntry(breakVariableName));
		Block* thenBlk = new Block(doWhileStemnt->location);
		thenBlk->head = new ExpressionStemnt(breakVariableName, getMatchingSymEntry(breakVariableName), 0, doWhileStemnt->location);
		thenBlk->head->next = new Statement(badStatement->type, doWhileStemnt->location);
		IfStemnt* breakIf = new IfStemnt(cond, thenBlk, doWhileStemnt->location);
		breakIf->next = doWhileStemnt->next;
		doWhileStemnt->next = breakIf;
	}
}

vector<Statement*>* GotoEliminator::getIncorrectlyUsedBreakOrContinue(Block* blockToLook, Block* funcDef)
{
	vector<Statement*>* badStatements = new vector<Statement*>();
	
	for (Statement* statement = blockToLook->head ; statement ; statement = statement->next){
		if (statement->type == ST_BreakStemnt || statement->type == ST_ContinueStemnt){
			badStatements->push_back(statement);
			continue;
		}

		if (statement->type == ST_IfStemnt){
			vector<Block*>* b = statement->getBlockFromStatement();
			for (unsigned int i = 0 ; i < b->size() ; i++){
				vector<Statement*>* badStatementsInBlock = getIncorrectlyUsedBreakOrContinue(b->at(i), funcDef);
				attachVectors(badStatements, badStatementsInBlock);
			}
		}
	}
	return badStatements;
}

std::string GotoEliminator::addIncorrectBreakVariableDefinition(DoWhileStemnt* doWhileStemnt, Block* funcDef)
{
	DeclStemnt* declStatement = new DeclStemnt(doWhileStemnt -> location);

	vector<Decl*>* decls = new vector<Decl*>();
	Symbol* symbol = new Symbol();

	stringstream oss;
	oss << "rv_break_var_" << m_currenHelperBreakVariableIndex++;

	symbol -> name = oss.str();
	BaseType * type = new BaseType(BT_Bool);
	Decl* decl = new Decl();
	decl -> name = symbol;
	decl -> form = type;
	symbol->entry = gProject->Parse_TOS->transUnit->contxt.syms->Insert(mk_vardecl(symbol -> name, decl));
	symbol->entry->scope->level = 3 + levelOf(doWhileStemnt, funcDef);
	(*m_varNamesToSymbolEntries)[symbol->name] = symbol->entry;
	declStatement -> addDecl(decl);

	doWhileStemnt->insertBefore(declStatement, funcDef);
	return symbol -> name;
}

string GotoEliminator::getMatchingGotoVariableName(IfStemnt* gotoStatement){
	Statement* matchingLabel = getMatchingLabel(gotoStatement);
	return "rv_goto_" + matchingLabel->labels.at(0)->name->name;
}

SymEntry* GotoEliminator::getMatchingSymEntry(string varName){
	return (*m_varNamesToSymbolEntries)[varName];
}

void GotoEliminator::printDebugInfo(string description, Statement* statementToPrint){
	if (!m_debug){
		return;
	}

	cout << "\n====================================================\n";
	cout << description << "\n\n";
	if (statementToPrint){
		statementToPrint->print(cout, 0);
	}
	cout << "\n====================================================\n";
}

