#include "stdafx.h"
#include "AsmTable.h"
#include <algorithm>
//#include "SymbolTable.h"


AsmTable::AsmTable(SymbolTable sm)
{
	this->sm = sm;
	this->lexemes = sm.lexemes;

}

#pragma region ASM TABLE generation

list<string> AsmTable::getLine(char delimiter)
{
	list<string>::iterator it = lexemes.begin();

	list<string>::iterator end;

	end = find(this->lexemes.begin(), this->lexemes.end(), delimiter);

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
	





}


#pragma endregion

AsmTable::~AsmTable()
{
}
