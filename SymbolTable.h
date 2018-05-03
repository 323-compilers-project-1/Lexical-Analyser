#pragma once

#include <stack>
#include <queue>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <list>

using std::stack;
using std::queue;
using std::string;
using std::vector;
using std::unordered_map;
using std::ofstream;
using std::list;






struct symTableInput
{
	string id;
	int memAddrs;
	string type;

};

class SymbolTable
{
private:
	vector<string>::iterator it;
	

	int stackAddress; //stack address assoicated with actionStack 

	//functions used by constuctors
	void createSymbolTable();
	void removeInt();
	void removeBool();
	

public:
	vector<symTableInput> symbolTable;

	
	//stack<int> actionstack;

	vector<string> symId;

	list<string> lexemes;


	//constructors
	SymbolTable();
	void printSymbolTable();
	SymbolTable(vector<string> symId, list<string> lex);

	
	


	~SymbolTable();
};

