#include "stdafx.h"
#include "AsmTable.h"
#include <algorithm>
//#include "SymbolTable.h"


AsmTable::AsmTable(SymbolTable sm)
{
}

#pragma region ASM TABLE generation

list<string> AsmTable::getLine()
{
	list<string>::iterator it = lexemes.begin();

	list<string>::iterator end;

	end = find(this->lexemes.begin(), this->lexemes.end(), ";");

	if (end != this->lexemes.end())
	{
		list<string> tmp(it, ++end);

		lexemes.erase(it, ++end);

		return tmp;
	}
	else
	{
		list<string> tmp;
		return tmp;
	}
}


void AsmTable::makeAsmTable()
{
	list<string> lineMarker;
	string delimiters[] = { ";", ")", "{", "}" };





}


#pragma endregion

AsmTable::~AsmTable()
{
}
