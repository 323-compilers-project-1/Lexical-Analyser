// parsetreeProj2.cpp : Defines the entry point for the console application.
//

#include <queue>
#include "SyntacticalAnalyzer.h"

using namespace std;


int main()
{
	queue<string> input;
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
	input.push(";");
	input.push(")");
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




	SyntacticalAnalyzer sa(input);
	
	sa.analyze();
	
    return 0;
}

