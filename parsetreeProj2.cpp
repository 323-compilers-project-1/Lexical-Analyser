// parsetreeProj2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <queue>
#include "SyntacticalAnalyzer.h"

using namespace std;


int main()
{
	queue<string> input;
	input.push("%%");
	input.push("a");
	input.push("+");
	input.push("b");
	input.push(";");

	//SyntacticalAnalyzer sa(input);
	
	//sa.analyze();
	
    return 0;
}

