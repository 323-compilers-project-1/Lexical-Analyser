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

	/*
	function add$ [x:int, y:int]
	{
	return x + y;
	}

	function sub$ [x:int, y:int]
	{
	return x - y;
	}

	%%
	int x, y, add, sub, result;

	get (x, y);
	add = add$ (x, y));
	sub = sub$ (x, y);

	put ((add + sub) + (add - sub));
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

