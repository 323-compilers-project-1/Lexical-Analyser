#include "stdafx.h"
#include "SyntacticalAnalyzer.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <exception>
#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <fstream>
#include "SymbolTable.h"

using namespace std;


#pragma region Constructors

void SyntacticalAnalyzer::createTable()
{


#pragma region Rat18s

	vector<string> tablePos;
	productionSet production;

	//%%
	production.production = "<Rat18s>";
	production.terminal = "%%";
	string table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Opt Function Definitions>");
	tablePos.push_back("%%");
	tablePos.push_back("<Opt Declaration List>");
	tablePos.push_back("<Statement List>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//function
	production.terminal = "function";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Opt Function Definitions>");
	tablePos.push_back("%%");
	tablePos.push_back("<Opt Declaration List>");
	tablePos.push_back("<Statement List>");

	table.emplace(table_key, tablePos);
	tablePos.clear();


#pragma endregion

#pragma region Opt Function Definitions

	//%%
	production.production = "<Opt Function Definitions>";
	production.terminal = "%%";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//%%function
	production.terminal = "function";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Function Definitions>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Function Definitions

	//Function
	production.production = "<Function Definitions>";
	production.terminal = "function";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Function>");
	tablePos.push_back("<Function Definitions Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region  Function Definitions Prime

	//%%
	production.production = "<Function Definitions Prime>";
	production.terminal = "%%";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//function
	production.terminal = "function";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Function>");
	tablePos.push_back("<Function Definitions Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Function

	//function
	production.production = "<Function>";
	production.terminal = "function";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("function");
	tablePos.push_back("identifier");
	tablePos.push_back("[");
	tablePos.push_back("<Opt Parameter List>");
	tablePos.push_back("]");
	tablePos.push_back("<Opt Declaration List>");
	tablePos.push_back("<Body>");

	table.emplace(table_key, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region Opt Parameter List

	// ]
	production.production = "<Opt Parameter List>";
	production.terminal = "]";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Parameter List>");

	table.emplace(table_key, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region Parameter List

	// identifier
	production.production = "<Parameter List>";
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Parameter>");
	tablePos.push_back("<Parameter List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Parameter List Prime

	// ]
	production.production = "<Parameter List Prime>";
	production.terminal = "]";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// ,
	production.terminal = ",";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back(",");
	tablePos.push_back("<Parameter List>");

	table.emplace(table_key, tablePos);
	tablePos.clear();


#pragma endregion

#pragma region Parameter

	//identifier
	production.production = "<Parameter>";
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<IDs>");
	tablePos.push_back(":");
	tablePos.push_back("<Qualifier>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion 

#pragma region Qualifier

	//int
	production.production = "<Qualifier>";
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("int");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//boolean
	production.terminal = "boolean";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("boolean");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("real");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Body

	// {
	production.production = "<Body>";
	production.terminal = "{";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("{");
	tablePos.push_back("<Statement List>");
	tablePos.push_back("}");

	table.emplace(table_key, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region Opt Declaration List

	//int
	production.production = "<Opt Declaration List>";
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Declaration List>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//boolean
	production.terminal = "boolean";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Declaration List>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Declaration List>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// {
	production.terminal = "{";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// identifier
	production.terminal = "identifier";
	tablePos.push_back("<Empty>");
	table_key = production.production + "," + production.terminal;

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// if
	production.terminal = "if";
	tablePos.push_back("<Empty>");
	table_key = production.production + "," + production.terminal;

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// endif
	production.terminal = "endif";
	tablePos.push_back("<Empty>");
	table_key = production.production + "," + production.terminal;

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// return
	production.terminal = "return";
	tablePos.push_back("<Empty>");
	table_key = production.production + "," + production.terminal;

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// put
	production.terminal = "put";
	tablePos.push_back("<Empty>");
	table_key = production.production + "," + production.terminal;

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// get
	production.terminal = "get";
	tablePos.push_back("<Empty>");
	table_key = production.production + "," + production.terminal;

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// while
	production.terminal = "while";
	tablePos.push_back("<Empty>");
	table_key = production.production + "," + production.terminal;

	table.emplace(table_key, tablePos);
	tablePos.clear();





#pragma endregion

#pragma region Declaration List

	//int
	production.production = "<Declaration List>";
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Declaration>");
	tablePos.push_back("<Declaration List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//boolean
	production.terminal = "boolean";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Declaration>");
	tablePos.push_back("<Declaration List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Declaration>");
	tablePos.push_back("<Declaration List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();




#pragma endregion

#pragma region Declaration List Prime

	// {
	production.production = "<Declaration List Prime>";
	production.terminal = "{";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// ;
	production.terminal = ";";

	tablePos.push_back(";");
	table_key = production.production + "," + production.terminal;

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//if
	production.terminal = "if";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//endif
	production.terminal = "endif";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//return
	production.terminal = "return";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//put
	production.terminal = "put";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//get
	production.terminal = "get";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//while
	production.terminal = "while";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Declaration

	//int
	production.production = "<Declaration>";
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Qualifier>");
	tablePos.push_back("<IDs>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// {
	production.terminal = "{";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//boolean
	production.terminal = "boolean";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Qualifier>");
	tablePos.push_back("<IDs>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Qualifier>");
	tablePos.push_back("<IDs>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
	/*#pragma region added not sure if works
	//;
	production.terminal = ";";
	table_key = production.production + "," + production.terminal;
	tablePos.push_back("<Empty>");
	table.emplace(table_key, tablePos);
	tablePos.clear();
	#pragma endregion*/

#pragma endregion

#pragma region IDs

	//identifier
	production.production = "<IDs>";
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("identifier");
	tablePos.push_back("<IDs Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region IDs Prime

	//:
	production.production = "<IDs Prime>";
	production.terminal = ":";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// , 
	production.terminal = ",";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back(",");
	tablePos.push_back("identifier");
	tablePos.push_back("<IDs Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// )
	production.terminal = ")";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//;
	production.production = "<IDs Prime>";
	production.terminal = ";";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();


#pragma endregion

#pragma region Statement List

	// {
	production.production = "<Statement List>";
	production.terminal = "{";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// }
	production.terminal = "}";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//if
	production.terminal = "if";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//endif
	production.terminal = "endif";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//return
	production.terminal = "return";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//put
	production.terminal = "put";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//get
	production.terminal = "get";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//while
	production.terminal = "while";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();




#pragma endregion

#pragma region Statement List Prime
	// {
	production.production = "<Statement List Prime>";
	production.terminal = "{";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// }
	production.production = "<Statement List Prime>";
	production.terminal = "}";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//if
	production.terminal = "if";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//endif
	production.terminal = "endif";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//return
	production.terminal = "return";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//put
	production.terminal = "put";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//get
	production.terminal = "get";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//while
	production.terminal = "while";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// $
	production.terminal = "$";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region statement
	production.production = "<Statement>";

	//{
	production.terminal = "{";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Compound>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Assign>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//if
	production.terminal = "if";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<If>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//return
	production.terminal = "return";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Return>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//put
	production.terminal = "put";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Print>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//get
	production.terminal = "get";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Scan>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//while
	production.terminal = "while";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Scan>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Compound
	production.production = "<Compound>";

	//{
	production.terminal = "{";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("{");
	tablePos.push_back("<Statement List>");
	tablePos.push_back("}");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Assign
	production.production = "<Assign>";

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("identifier");
	tablePos.push_back("=");
	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region If
	production.production = "<If>";

	//identifier
	production.terminal = "if";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("if");
	tablePos.push_back("(");
	tablePos.push_back("<Condition>");
	tablePos.push_back(")");
	tablePos.push_back("<Statement>");
	tablePos.push_back("<If Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region If Prime
	production.production = "<If Prime>";

	//endif
	production.terminal = "endif";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("endif");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//else
	production.terminal = "else";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("else");
	tablePos.push_back("<Statement>");
	tablePos.push_back("endif");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Return
	production.production = "<Return>";

	//return	
	production.terminal = "return";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("return");
	tablePos.push_back("<Return Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Return Prime
	production.production = "<Return Prime>";

	//int	
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//;
	production.terminal = ";";

	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Print
	production.production = "<Print>";

	//put
	production.terminal = "put";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("put");
	tablePos.push_back("(");
	tablePos.push_back("<Expression>");
	tablePos.push_back(")");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Scan
	production.production = "<Scan>";

	//get
	production.terminal = "get";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("get");
	tablePos.push_back("(");
	tablePos.push_back("<IDs>");
	tablePos.push_back(")");
	tablePos.push_back(";");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region While
	production.production = "<Scan>";

	//while
	production.terminal = "while";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("while");
	tablePos.push_back("(");
	tablePos.push_back("<Condition>");
	tablePos.push_back(")");
	tablePos.push_back("<Statement>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Condition
	production.production = "<Condition>";

	//int
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Relop
	production.production = "<Relop>";

	//==
	production.terminal = "==";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("==");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("^=");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back(">");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("=<");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("=>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Expression
	production.production = "<Expression>";

	//int
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term>");
	tablePos.push_back("<Expression Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term>");
	tablePos.push_back("<Expression Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term>");
	tablePos.push_back("<Expression Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term>");
	tablePos.push_back("<Expression Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term>");
	tablePos.push_back("<Expression Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term>");
	tablePos.push_back("<Expression Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term>");
	tablePos.push_back("<Expression Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Expression Prime
	production.production = "<Expression Prime>";

	//;
	production.terminal = ";";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//+
	production.terminal = "+";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("+");
	tablePos.push_back("<Term>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//+
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("-");
	tablePos.push_back("<Term>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Term
	production.production = "<Term>";

	//int
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Term Prime
	production.production = "<Term Prime>";

	//;
	production.terminal = ";";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//+
	production.terminal = "+";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//*
	production.terminal = "*";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term Double Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// /
	production.terminal = "/";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term Triple Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// ;
	production.terminal = ";";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Term Triple Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Term Double Prime
	production.production = "<Term Double Prime>";

	//;
	production.terminal = ";";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//+
	production.terminal = "+";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//*
	production.terminal = "*";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("*");
	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Double Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	///
	production.terminal = "/";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("/");
	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Triple Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Term Triple Prime
	production.production = "<Term Triple Prime>";

	//;
	production.terminal = ";";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//+
	production.terminal = "+";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// /
	production.terminal = "/";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("/");
	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Triple Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// *
	production.terminal = "*";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("/");
	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Double Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Factor
	production.production = "<Factor>";

	//int
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Primary>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Primary>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Primary>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Primary>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("-");
	tablePos.push_back("<Primary>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Primary>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Primary>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Primary
	production.production = "<Primary>";

	//int
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("int");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("real");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("identifier");
	tablePos.push_back("<Primary Prime>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("(");
	tablePos.push_back("<Expression>");
	tablePos.push_back(")");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//*
	production.terminal = "*";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// /
	production.terminal = "/";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("true");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("false");

	table.emplace(table_key, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Primary Prime
	production.production = "<Primary Prime>";

	//(
	production.terminal = "(";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("(");
	tablePos.push_back("<IDs>");
	tablePos.push_back(")");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//*
	production.terminal = "*";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	// /
	production.terminal = "/";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();



	//ADDED
	//+
	production.terminal = "+";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//;
	production.terminal = ";";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//int
	production.terminal = "int";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";
	table_key = production.production + "," + production.terminal;

	tablePos.push_back("<Empty>");

	table.emplace(table_key, tablePos);
	tablePos.clear();
#pragma endregion
}



SyntacticalAnalyzer::SyntacticalAnalyzer()
{
	vector<string> tablePos;
	//Initializing Stack
	this->tableStack.push("$");
	tableStack.push("<Rat18s>");


	//Might not have to do this
	//tableStack.push("Rat18s");

	this->inputQ.push("$");

	this->createTable();

}

SyntacticalAnalyzer::SyntacticalAnalyzer(queue<string> inputQ)
{
	vector<string> tablePos;
	//Initializing Stack
	this->tableStack.push("$");
	tableStack.push("<Rat18s>");


	//Might not have to do this
	//tableStack.push("Rat18s");
	this->inputQ = inputQ;
	this->inputQ.push("$");

	this->createTable();
}

#pragma endregion


#pragma  region Table Traversing

productionSet SyntacticalAnalyzer::getProductionSet(string input)
{
	string output;

	productionSet production;

	//reading until comma
	int i = 0;
	while (input[i] != ',')
	{
		output.push_back(input[i]);
		i++;

	}
	//moving past the comma
	i++;
	production.production = output;
	output.clear();

	while (i < input.size())
	{
		output.push_back(input[i]);
		i++;

	}
	production.terminal = output;
	output.clear();

	return production;
}


//called in main performs all output and stack manipuliation
void SyntacticalAnalyzer::analyze()
{
	//creating iterator in order to use find functions for map
	unordered_map<string, vector<string>>::const_iterator got;

	productionSet production;

	ofstream output_file;
	output_file.open("output.txt", ios::out | std::ofstream::trunc);

	// while loop starting here in order to traverse through array based on input
	//this handles $ to end the syntactical analyzer if there is an error we will use continue or break to end loop and out put corresponding ms
	while (this->tableStack.top() != "$")
	{
		//Simply outputs first
		productionSet production;
		production.production = tableStack.top();
		production.terminal = inputQ.front();
		if (this->tableStack.top() == "<Rat18s>")
		{
			print_production(tableStack, inputQ, table, output_file);
			this->tableStack.pop();
		}
		else if (this->tableStack.top() == this->inputQ.front())
		{
			cout << this->tableStack.top() << endl;
			output_file << this->tableStack.top() << endl;
			this->tableStack.pop();
			this->inputQ.pop();
			continue;
		}
#pragma region pushing to stack	
		production.terminal = this->inputQ.front();

		string prod = production.production + "," + production.terminal;

		got = table.find(prod);
		//production = getProductionSet(got->first);
		if (got == table.end())
		{
			cout << prod << " not found" << endl;
			output_file << prod << " not found" << endl;
			return;
		}

		vector<string> cellVector = got->second;

		int cellSize = cellVector.size();

		//if the string vector is empty we simply pop off the an item in the stack
		if (cellVector[0] == "<Empty>")
		{
			//might need to output rule here   
			//Yep - Daniel
			cout << tableStack.top() << " => <Empty>" << endl;
			output_file << tableStack.top() << " => <Empty>" << endl;
			this->tableStack.pop();
			continue;
		}
		else
		{
			if (cellVector.front() == this->inputQ.front())
			{
				print_production(tableStack, inputQ, table, output_file);
				this->tableStack.pop();
				for (int i = cellVector.size(); i > 0; i--)
				{
					tableStack.push(cellVector.back());
					cellVector.pop_back();
				}
				continue;
			}
			//this handles pushing thing from the table to the stack in proper order
			for (int i = cellVector.size(); i > 0; i--)
			{
				if (tableStack.top() != "$" && i == cellSize)
				{
					print_production(tableStack, inputQ, table, output_file);
					tableStack.pop();	//pops production that it finds
				}

				tableStack.push(cellVector.back());
				cellVector.pop_back();
			}

		}



#pragma endregion



	}

	if (tableStack.top() == inputQ.front())
	{
		cout << "Correct syntax" << endl;
		output_file << "Correct syntax" << endl;
	}
	else
	{
		cout << "Incorrect input" << endl;
		output_file << "Incorrect input" << endl;
	}

	output_file.close();

}

#pragma endregion

void SyntacticalAnalyzer::print_production(stack<string> tableStack, queue<string> input, unordered_map<string, vector<string>> table, ofstream& output)
{
	productionSet production;
	production.production = tableStack.top();
	production.terminal = input.front();
	{
		cout << tableStack.top() << " => ";
		output << tableStack.top() << " => ";
		string prod = production.production + "," + input.front();
		vector<string> to_prod = table[prod];
		for (int i = 0; i < to_prod.size(); i++)
		{
			cout << to_prod[i];
			output << to_prod[i];
		}
		cout << endl;
		output << endl;
	}
}