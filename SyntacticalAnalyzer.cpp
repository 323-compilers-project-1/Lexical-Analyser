#include "SyntacticalAnalyzer.h"
#include <unordered_map>
#include <string>


using namespace std;

/*
struct producitonSet
{
string production;
string lexeme;

};


Class data
unordered_map<producitonSet, vector<string>> table;
stack<string> tableStack;	//Needs to be initalized with $Rat18s
queue<string> inputQ;		//Needs to be but at back of queue will be done in overloaded constructor

*/


#pragma region Constructors

SyntacticalAnalyzer::SyntacticalAnalyzer()
{
	vector<string> tablePos;
	//Initializing Stack
	tableStack.push("$");
	
	
	//Might not have to do this
	//tableStack.push("Rat18s");

	inputQ.push("$");

	productionSet production;
	production.production = "Rat18s";
	production.lexeme = "%%";

	tablePos.push_back("<Opt Function Definitions>");
	tablePos.push_back("%%");






}

SyntacticalAnalyzer::SyntacticalAnalyzer(queue<string> inputQ)
{



}

#pragma endregion
