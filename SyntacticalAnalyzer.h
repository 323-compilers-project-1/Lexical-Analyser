#ifndef SYNTACTICALANALYZER
#define SYNTACTICALANALYZER

#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "SymbolTable.h"

using std::stack;
using std::queue;
using std::string;
using std::vector;
using std::unordered_map;
using std::ofstream;


struct productionSet
{
	string production;
	string terminal;

};


class SyntacticalAnalyzer
{

private:



	unordered_map<string, vector<string>> table;
	stack<string> tableStack;	//Needs to be initalized with $Rat18s
	queue<string> inputQ;		//Needs to be but at back of queue will be done in overloaded constructor

								//used by constructors
	void createTable();
	void print_production(stack<string> tableStack, queue<string> input, unordered_map<string, vector<string>> table, ofstream& output);

	productionSet getProductionSet(string input);





public:
	//Constructors
	SyntacticalAnalyzer();		//mainly used for error checking in main
	SyntacticalAnalyzer(queue<string> inputQ);

	void analyze();


};





#endif