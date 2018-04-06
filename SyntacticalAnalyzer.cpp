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
	tableStack.push("<Rat18s>")
	
	
	//Might not have to do this
	//tableStack.push("Rat18s");

	inputQ.push("$");

#pragma region Rat18s

	//%%
	productionSet production;
	production.production = "<Rat18s>";
	production.terminal = "%%";

	tablePos.push_back("<Opt Function Definitions>");
	tablePos.push_back("%%");
	tablePos.push_back("<Opt Declaration List>");
	tablePos.push_back("<Statement List>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//function
	production.terminal = "function";

	tablePos.push_back("<Function Definitions>");

	table.emplace(production, tablePos);
	tablePos.clear();


#pragma endregion

#pragma region Opt Function Definitions
	
	//%%
	production.production = "<Opt Function Definitions>";
	production.terminal = "%%";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Function Definitions
	
	//Function
	production.production = "<Function Definitions>";
	production.terminal = "function";

	tablePos.push_back("<Function>");
	tablePos.push_back("<Function Definitions Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region  Function Definitions Prime

	//%%
	production.production = "<Function Definitions Prime>";
	production.terminal = "%%";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//function
	production.terminal = "function";

	tablePos.push_back("<Function>");
	tablePos.push_back("<Function Definitions Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region Function

	//function
	production.production = "<Function>";
	production.terminal = "function";

	tablePos.push_back("function");
	tablePos.push_back("identifer");
	tablePos.push_back("[");
	tablePos.push_back("<Opt Parameter List>");
	tablePos.push_back("]");
	tablePos.push_back("<Opt Declaration List>");
	tablePos.push_back("<Body>");

	table.emplace(production, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region Opt Parameter List

	// ]
	production.production = "<Opt Parameter List>";
	production.terminal = "]";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// identifer
	production.terminal = "identifer";

	tablePos.push_back("<Parameter List>");

	table.emplace(production, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region Parameter List
	
	// identifer
	production.production = "<Parameter List>";
	production.terminal = "identifer";

	tablePos.push_back("<Parameter>");
	tablePos.push_back("<Parameter List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Parameter List Prime

	// ]
	production.production = "<Parameter List Prime>";
	production.terminal = "]";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// ,
	production.terminal = ",";

	tablePos.push_back(",");
	tablePos.push_back("<Parameter List>");

	table.emplace(production, tablePos);
	tablePos.clear();


#pragma endregion

#pragma region Parameter
	
	//identifer
	production.production = "<Parameter>";
	production.terminal = "identifer";

	tablePos.push_back("<IDs>");
	tablePos.push_back(":");
	tablePos.push_back("<Qualifier>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion 

#pragma region Qualifier

	//int
	production.production = "<Qualifier>";
	production.terminal = "int";

	tablePos.push_back("int");
	
	table.emplace(production, tablePos);
	tablePos.clear();

	//boolean
	production.terminal = "boolean";

	tablePos.push_back("boolean");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("real");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Body

	// {
	production.production = "<Body>";
	production.terminal = "{";

	tablePos.push_back("{");
	tablePos.push_back("<Statement List>");
	tablePos.push_back("}");

	table.emplace(production, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region Opt Declaration List

	//int
	production.production = "<Opt Declaration List>";
	production.terminal = "int";

	tablePos.push_back("<Declaration List>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//boolean
	production.terminal = "boolean";

	tablePos.push_back("<Declaration List>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("<Declaration List>");

	table.emplace(production, tablePos);
	tablePos.clear();
	
	// {
	production.terminal = "{";
	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// identifer
	production.terminal = "identifer";
	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// if
	production.terminal = "if";
	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// endif
	production.terminal = "endif";
	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// return
	production.terminal = "return";
	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// put
	production.terminal = "put";
	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// get
	production.terminal = "get";
	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// while
	production.terminal = "while";
	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();



	

#pragma endregion

#pragma region Declaration List

	//int
	production.production = "<Declaration List>";
	production.terminal = "int";

	tablePos.push_back("<Declaration>");
	tablePos.push_back("<Declaration List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//boolean
	production.terminal = "boolean";

	tablePos.push_back("<Declaration>");
	tablePos.push_back("<Declaration List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("<Declaration>");
	tablePos.push_back("<Declaration List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();




#pragma endregion

#pragma region Declaration List Prime

	// {
	production.production = "<Declaration List Prime>";
	production.terminal = "{";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// ;
	production.terminal = ";";

	tablePos.push_back = ";";
	tablePos.push_back = "<Declaration>";
	tablePos.push_back = "<Declaration List Prime>";

	table.emplace(production, tablePos);
	tablePos.clear();

	// identifer
	production.terminal = "identifer";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//if
	production.terminal = "if";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();
	
	//endif
	production.terminal = "endif";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//return
	production.terminal = "return";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//put
	production.terminal = "put";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//get
	production.terminal = "get";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//while
	production.terminal = "while";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Declaration

	//int
	production.production = "<Declaration>";
	production.terminal = "int";

	tablePos.push_back("<Qualifier>");
	tablePos.push_back("<IDs>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//boolean
	production.terminal = "boolean";

	tablePos.push_back("<Qualifier>");
	tablePos.push_back("<IDs>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("<Qualifier>");
	tablePos.push_back("<IDs>");

	table.emplace(production, tablePos);
	tablePos.clear();


#pragma endregion

#pragma region IDs

	//identifier
	production.production = "<IDs>";
	production.terminal = "identifer";

	tablePos.push_back("identifer");
	tablePos.push_back("<IDs Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();



#pragma endregion

#pragma region IDs Prime

	//;
	production.production = "<IDs Prime>";
	production.terminal = ";";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// , 
	production.terminal = ",";

	tablePos.push_back(",");
	tablePos.push_back("identifer");
	tablePos.push_back("<IDs Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// )
	production.terminal = ")";

	tablePos.push_back("<Empty>");
	
	table.emplace(production, tablePos);
	tablePos.clear();


#pragma endregion

#pragma region Statement List

	// {
	production.production = "<Statement List>";
	production.terminal = "{";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifer
	production.terminal = "identifer";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//if
	production.terminal = "if";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//endif
	production.terminal = "endif";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//return
	production.terminal = "return";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//put
	production.terminal = "put";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//get
	production.terminal = "get";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//while
	production.terminal = "while";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();




#pragma endregion

#pragma region Statement List Prime
	// {
	production.production = "<Statement List Prime>";
	production.terminal = "{";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// }
	production.production = "<Statement List Prime>";
	production.terminal = "}";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifer
	production.terminal = "identifer";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//if
	production.terminal = "if";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//endif
	production.terminal = "endif";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//return
	production.terminal = "return";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//put
	production.terminal = "put";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//get
	production.terminal = "get";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//while
	production.terminal = "while";

	tablePos.push_back("<Statement>");
	tablePos.push_back("<Statement List Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// $
	production.terminal = "$";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region statement
	production.production = "<Statement>";

	//{
	production.terminal = "{";

	tablePos.push_back("<Compound>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";

	tablePos.push_back("<Assign>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//if
	production.terminal = "if";

	tablePos.push_back("<If>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//return
	production.terminal = "return";

	tablePos.push_back("<Return>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//put
	production.terminal = "put";

	tablePos.push_back("<Print>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//get
	production.terminal = "get";

	tablePos.push_back("<Scan>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//while
	production.terminal = "while";

	tablePos.push_back("<While>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Compound
	production.production = "<Compound>"

		//{
		production.terminal = "{";

	tablePos.push_back("{");
	tablePos.push_back("<Statement List>");
	tablePos.push_back("}");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Assign
	production.production = "<Assign>";

	//identifier
	production.terminal = "identifier";

	tablePos.push_back("identifier");
	tablePos.push_back("=");
	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region If
	production.production = "<If>";

	//identifier
	production.terminal = "if";

	tablePos.push_back("if");
	tablePos.push_back("(");
	tablePos.push_back("<Condition>");
	tablePos.push_back(")");
	tablePos.push_back("<Statement>");
	tablePos.push_back("<If Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region If Prime
	production.production = "<If Prime>";

	//endif
	production.terminal = "endif";

	tablePos.push_back("endif");

	table.emplace(production, tablePos);
	tablePos.clear();

	//else
	production.terminal = "else";

	tablePos.push_back("else");
	tablePos.push_back("<Statement>");
	tablePos.push_back("endif");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Return
	production.production = "<Return>";

	//return	
	production.terminal = "return";

	tablePos.push_back("return");
	tablePos.push_back("<Return Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Return Prime
	production.production = "<Return Prime>";

	//int	
	production.terminal = "int";

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();

	//;
	production.terminal = ";";

	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";

	tablePos.push_back("<Expression>");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Print
	production.production = "<Print>";

	//put
	production.terminal = "put";

	tablePos.push_back("put");
	tablePos.push_back("(");
	tablePos.push_back("Expression");
	tablePos.push_back(")");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Scan
	production.production = "<Scan>";

	//get
	production.terminal = "get";

	tablePos.push_back("get");
	tablePos.push_back("(");
	tablePos.push_back("<IDs>");
	tablePos.push_back(")");
	tablePos.push_back(";");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region While
	production.production = "<Scan>";

	//while
	production.terminal = "while";

	tablePos.push_back("while");
	tablePos.push_back("(");
	tablePos.push_back("<Condition>");
	tablePos.push_back(")");
	tablePos.push_back("<Statement>");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Condition
	production.production = "<Condition>";

	//int
	production.terminal = "int";

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";

	tablePos.push_back("<Expression>");
	tablePos.push_back("<Relop>");
	tablePos.push_back("<Expression>");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Relop
	production.production = "<Relop>";

	//==
	production.terminal = "==";

	tablePos.push_back("==");

	table.emplace(production, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";

	tablePos.push_back("^=");

	table.emplace(production, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";

	tablePos.push_back(">");

	table.emplace(production, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";

	tablePos.push_back("<");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";

	tablePos.push_back("=<");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";

	tablePos.push_back("=>");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Expression
	production.production = "<Expression>";

	//int
	production.terminal = "int";

	tablePos.push_back("<Term>");
	tablePos.push_back("Expression Prime");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("<Term>");
	tablePos.push_back("Expression Prime");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";

	tablePos.push_back("<Term>");
	tablePos.push_back("Expression Prime");

	table.emplace(production, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";

	tablePos.push_back("<Term>");
	tablePos.push_back("Expression Prime");

	table.emplace(production, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";

	tablePos.push_back("<Term>");
	tablePos.push_back("Expression Prime");

	table.emplace(production, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";

	tablePos.push_back("<Term>");
	tablePos.push_back("Expression Prime");

	table.emplace(production, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";

	tablePos.push_back("<Term>");
	tablePos.push_back("Expression Prime");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Expression Prime
	production.production = "<Expression Prime>";

	//;
	production.terminal = ";";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//+
	production.terminal = "+";

	tablePos.push_back("+");
	tablePos.push_back("<Term>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//+
	production.terminal = "-";

	tablePos.push_back("-");
	tablePos.push_back("<Term>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Term
	production.production = "<Term>";

	//int
	production.terminal = "int";

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Term Prime
	production.production = "<Term Prime>";

	//;
	production.terminal = ";";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//+
	production.terminal = "+";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//*
	production.terminal = "*";

	tablePos.push_back("<Term Double Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// /
	production.terminal = "/";

	tablePos.push_back("<Term Triple Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Term Double Prime
	production.production = "<Term Double Prime>";

	//;
	production.terminal = ";";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//+
	production.terminal = "+";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//*
	production.terminal = "*";

	tablePos.push_back("*");
	tablePos.push_back("<Factor>");
	tablePos.push_back("Term Double Prime");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Term Triple Prime
	production.production = "<Term Triple Prime>";

	//;
	production.terminal = ";";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//)
	production.terminal = ")";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//==
	production.terminal = "==";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//^=
	production.terminal = "^=";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//>
	production.terminal = ">";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//<
	production.terminal = "<";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=<
	production.terminal = "=<";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//=>
	production.terminal = "=>";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//+
	production.terminal = "+";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// /
	production.terminal = "/";

	tablePos.push_back("<Factor>");
	tablePos.push_back("<Term Triple Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Factor
	production.production = "<Factor>";

	//int
	production.terminal = "int";

	tablePos.push_back("<Primary>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("<Primary>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";

	tablePos.push_back("<Primary>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";

	tablePos.push_back("<Primary>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//-
	production.terminal = "-";

	tablePos.push_back("-");
	tablePos.push_back("<Primary>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";

	tablePos.push_back("<Primary>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";

	tablePos.push_back("<Primary>");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

#pragma region Primary
	production.production = "<Primary>";

	//int
	production.terminal = "int";

	tablePos.push_back("int");

	table.emplace(production, tablePos);
	tablePos.clear();

	//real
	production.terminal = "real";

	tablePos.push_back("real");

	table.emplace(production, tablePos);
	tablePos.clear();

	//identifier
	production.terminal = "identifier";

	tablePos.push_back("identifier");
	tablePos.push_back("<Primary Prime>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//(
	production.terminal = "(";

	tablePos.push_back("(");
	tablePos.push_back("<Expression>");
	tablePos.push_back(")");

	table.emplace(production, tablePos);
	tablePos.clear();

	//*
	production.terminal = "*";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// /
	production.terminal = "/";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	//true
	production.terminal = "true";

	tablePos.push_back("true");

	table.emplace(production, tablePos);
	tablePos.clear();

	//false
	production.terminal = "false";

	tablePos.push_back("false");

	table.emplace(production, tablePos);
	tablePos.clear();

#pragma endregion

#pragma region Primary Prime
	production.production = "<Primary Prime>";

	//(
	production.terminal = "(";

	tablePos.push_back("(");
	ttablePos.push_back("<IDs>");
	ablePos.push_back(")");

	table.emplace(production, tablePos);
	tablePos.clear();

	//*
	production.terminal = "*";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();

	// /
	production.terminal = "/";

	tablePos.push_back("<Empty>");

	table.emplace(production, tablePos);
	tablePos.clear();
#pragma endregion

}

SyntacticalAnalyzer::SyntacticalAnalyzer(queue<string> inputQ)
{



}

#pragma endregion
