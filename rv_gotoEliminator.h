#include    <iostream>
#include    <cstring>
#include    <string>
#include    <cstdlib>
#include    <cassert>
#include    <ctool/ctdemo.h>
#include    <ctool/ctool.h>
#include    <ctool/PrintTraversal.h>
#include 	<vector>
#include	<set>
#include <sstream>
#include <map>
#include <time.h>
using namespace std;

#ifndef     GOTO_H
#define     GOTO_H

///The algorithm which is implemented here is based on the paper here:
///http://www.google.com/url?sa=t&rct=j&q=taming%20control%20flow&source=web&cd=1&ved=0CDAQFjAA&url=http%3A%2F%2Fciteseerx.ist.psu.edu%2Fviewdoc%2Fdownload%3Fdoi%3D10.1.1.42.1485%26rep%3Drep1%26type%3Dpdf&ei=-TyVT4T_BPHP4QTzp93QDw&usg=AFQjCNGUjoBZn9_qACHS3SCYvS9IUVDDAQ

class GotoEliminator{

private:
	static vector<IfStemnt*>* m_conditionalGotoStatements;
	static map<IfStemnt*, Statement*>* m_gotoStatementsToLabelVariables;
	static map<string, SymEntry*>* m_varNamesToSymbolEntries;
	static vector<Statement*>* m_labels;
	static IfStemnt* m_currentGotoStatement;
	static int m_currentSwitchVariableIndex;
	static int m_currenHelperBreakVariableIndex;
	static bool m_debug;

	static void printVector(std::vector<std::string>* v);
	
	static void removeGotoFromFunction(FunctionDef* funcDef, TransUnit* unit);
	static void setupLabelData( FunctionDef* funcDef );
	static void setLabelVector( FunctionDef* funcDef );
	static void introduceLabelVariables(FunctionDef* funcDef);

	static void addLabelVariableDeclerations( FunctionDef* funcDef );

	static SymEntry* getMatchingSymEntry(string varName);
	static vector<Statement*>* getAllLabels(Block* funcDef);
	static Statement* createFalseAssignment(Statement* statement, string varName);
	static void setupGotoStatements(FunctionDef* funcDef);
	static vector<IfStemnt*>* ensureAllGotoStatementsAreUnderCondition(vector<GotoStemnt*>* gotoStatementsInFunction, FunctionDef* funcDef );
	static IfStemnt* createTrivialIfStatement(GotoStemnt* currentGotoStatement);

	static void createSwitchStatementPrecedingBlock(IfStemnt* gotoStatement, SwitchStemnt* switchStemnt, string switchVariable, Block* funcDef);
	static Block* createSwitchStatementPrecedingElseBlock(string switchVariableName, IfStemnt* gotoStatement);
	static DeclStemnt* addSwitchVariable( IfStemnt* gotoStatement, Block* funcDef );
		
	static vector<GotoStemnt*>* getAllGotoStatements(Block* funcDef);
	static vector<IfStemnt*>* getAllGotoConditionalStatements(FunctionDef* funcDef);
	static Statement* getMatchingLabel(IfStemnt* statement);
	static bool directlyRelated(IfStemnt* gotoStatement, Statement* matchingLabel, Block* funcDef);
	static int levelOf(Statement* statement, Block* funcDef);
	static int offsetOf(Statement* statement, Block* funcDef);
	static bool areSiblings(Statement* firstStatement, Statement* secondStatement, Block* funcDef);
	static void makeGotoStatementDirectlyRelatedToMatchingLabel(IfStemnt* gotoStatement, Statement* matchingLabel, Block* funcDef);
	static IfStemnt* moveGotoStatementOutOfEnclosingBlock(IfStemnt* gotoStatement, Block* funcDef);
	static IfStemnt* moveGotoStatementOutOfIfStatement(IfStemnt* gotoStatement, IfStemnt* ifStemnt, Block* funcDef);
	static IfStemnt* moveGotoStatementOutOfWhileStatement(IfStemnt* gotoStatement, WhileStemnt* ifStemnt, Block* funcDef);
	static IfStemnt* moveGotoStatementOutOfSwitchStatement(IfStemnt* gotoStatement, SwitchStemnt* enclosingBlock, Block* funcDef);
	static void assignConditionToGotoVariable(IfStemnt* gotoStatement, Block* ifStemnt);
	static void putStatemntsAfterGotoUnderCondition(IfStemnt* gotoStatement, IfStemnt* ifStemnt, Statement* statementAfterIfStemnt);
	static IfStemnt* addGotoAfterBlockStatement(IfStemnt* gotoStatement, Statement* blckStemnt);
	static void addConditionalBreakStatement(IfStemnt* gotoStatement, Block* blockStatement);
	static void initializeMapBetweenGotosAndLabelVariables();
	static Block* encloseStatementsInBlock(Statement* first, Statement* last);
	static Block* encloseStatementsInBlockIncludeFirst(Statement* first, Statement* last);
	static IfStemnt* createIfStatementForBreak(IfStemnt* gotoStatement);
	static IfStemnt* createIfStatementFromLabelVars(IfStemnt* gotoStatement);
	static void replaceOldGotoWithNew(IfStemnt* oldStatement, IfStemnt* newStatement);
	static void moveGotoStatementIn(IfStemnt* gotoStatement, Statement* labelStatement, Block* funcDef);
	static IfStemnt* moveGotoStatementIntoIfStatement(IfStemnt* gotoStatement, IfStemnt* ifStemnt, Block* funcDef);
	static IfStemnt* moveGotoStatementInWhileStatement(IfStemnt* gotoStatement, WhileStemnt* whileStemnt, Block* funcDef);
	static IfStemnt* moveGotoStatementInSwitchStatement(IfStemnt* gotoStatement, SwitchStemnt* ifStemnt, Block* funcDef);
	static Statement* getGotoStatementSiblingBlockThatEnclosesLabel(IfStemnt* gotoStatement, Statement* labelStatement, Block* funcDef);
	static IfStemnt* moveGotoStatementInEnclosingBlock(IfStemnt* gotoStatement, Statement* labelStatement, Block* funcDef);
	static Expression* createConditionExpressionForIfStemntThenBlkInwardMove(IfStemnt* statement, Expression* oldExpr);
	static Expression* createConditionExpressionForIfStemntElseBlkInwardMove(IfStemnt* statement, Expression * oldExpr);
	static void putStatemntsAfterGotoBeforeBlockUnderCondition(IfStemnt* gotoStatement, Statement* blockStatement, Block* funcDef);
	static IfStemnt* createNewGotoStatementInNewBlock(IfStemnt* gotoStatement, Block* newEnclosingBlock);
	static void eliminateGotoStatementWithCondition(IfStemnt* gotoStatement, Block* funcDef);
	static void eliminateGotoStatementWithDoWhile(IfStemnt* gotoStatement, Block* funcDef);
	static void liftGotoStatement(IfStemnt* gotoStatement, Statement* matchingLabel, Block* funcDef);

	static string getMatchingGotoVariableName( IfStemnt* gotoStatement );

	static void moveGotoStatementOutToLevelOf(IfStemnt* gotoStatement, Statement* destinationStatement, FunctionDef* funcDef);

	static Block* createSwitchStatementPrecedingThenBlock(string switchVariableName, IfStemnt* gotoStatement, SwitchStemnt* switchStemnt, Block* funcDef);
	static IfStemnt* putGotoStatementInSwitchStatement(IfStemnt* gotoStatement, SwitchStemnt* switchStemnt, string switchVariable, Block* funcDef);
	
	static void addFalseAssignmentToLabelVariableAfterLabel(FunctionDef* funcDef);

	static IfStemnt* moveGotoStatementInDoWhileStatement(IfStemnt* gotoStatement, DoWhileStemnt* param2, Block* funcDef);
	static IfStemnt* moveGotoStatementOutOfDoWhileStatement(IfStemnt* gotoStatement, DoWhileStemnt* param2, Block* funcDef);
	static void putNewGotoStatmentAfterMatchingCaseLabel(IfStemnt* newGotoStatement, Statement* matchingLabel, SwitchStemnt* switchStemnt, Block* funcDef);
	static IfStemnt* moveGotoStatementInForStatement(IfStemnt* gotoStatement, ForStemnt* param2, Block* funcDef);
	static IfStemnt* moveGotoStatementOutOfForStatement( IfStemnt* gotoStatement, ForStemnt* param2, Block* funcDef );
	static void treatIncorrectUseOfBreakOrContinue( DoWhileStemnt* doWhileStemnt, Block* funcDef );
	static bool gotoStatementExistsInBlock(Statement* firstStatementInBlock);

	static void printDebugInfo(string description, Statement* statementToPrint);
public:
	static void removeGoto(TransUnit* unit, bool debug);
	static vector<Statement*>* getIncorrectlyUsedBreakOrContinue( Block* block, Block* funcDef );
	static string addIncorrectBreakVariableDefinition(DoWhileStemnt* doWhileStemnt, Block* funcDef);
	static bool gotoStatementExists( TransUnit * side_parsetree );
};

#endif
 	