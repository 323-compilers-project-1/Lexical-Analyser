// parsetreeProj2.cpp : Defines the entry point for the console application.
//

#include <queue>
#include "SyntacticalAnalyzer.h"

using namespace std;


int main()
{
	queue<string> input;

	//Function Definitions
	input.push("function");
	input.push("identifier");
	input.push("[");
	input.push("identifier");
	input.push(":");
	input.push("int");
	input.push(",");
	input.push("identifier");
	input.push(":");
	input.push("int");
	input.push("]");
	input.push("{");
	input.push("return");
	input.push("identifier");
	input.push("+");
	input.push("identifier");
	input.push(";");
	input.push("}");
	input.push("function");
	input.push("identifier");
	input.push("[");
	input.push("identifier");
	input.push(":");
	input.push("int");
	input.push(",");
	input.push("identifier");
	input.push(":");
	input.push("int");
	input.push("]");
	input.push("{");
	input.push("return");
	input.push("identifier");
	input.push("-");
	input.push("identifier");
	input.push(";");
	input.push("}");

	//Opt Declaration List
	input.push("%%");
	input.push("int");
	input.push("identifier");
	input.push(",");
	input.push("identifier");
	input.push(",");
	input.push("identifier");
	input.push(",");
	input.push("identifier");
	input.push(",");
	input.push("identifier");
	input.push(";");

	input.push("get");
	input.push("(");
	input.push("identifier");
	input.push(",");
	input.push("identifier");
	input.push(")");
	input.push(";");

	input.push("identifier");
	input.push("=");
	input.push("identifier");
	input.push("(");
	input.push("identifier");
	input.push(",");
	input.push("identifier");
	input.push(")");
	input.push(";");

	input.push("identifier");
	input.push("=");
	input.push("identifier");
	input.push("(");
	input.push("identifier");
	input.push(",");
	input.push("identifier");
	input.push(")");
	input.push(";");

	input.push("put");
	input.push("(");
	input.push("(");
	input.push("identifier");
	input.push("+");
	input.push("identifier");
	input.push(")");
	input.push("+");
	input.push("(");
	input.push("identifier");
	input.push("-");
	input.push("identifier");
	input.push(")");
	input.push(")");
	input.push(";");

	input.push("int");
	input.push("identifier");
	input.push(";");

/*
    int i;
    i = 0;
    while (i < 10)
      {
        put (i);
        i = i + 1;
      }
	*/



	SyntacticalAnalyzer sa(input);
	
	sa.analyze();
	
    return 0;
}

