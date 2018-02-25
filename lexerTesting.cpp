// lexerTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>

using namespace std;

//Carlos's function
bool isSeperator(char to_lex);
bool isOperator(char to_lex);
char isLang(char lex_char);
list<string> split_lex_word(string lex);
//list<Token> lexer(string lexWord);
const int KEYWORD_LIST_SIZE = 13;
const string keyword_list[KEYWORD_LIST_SIZE] = { "function", "int", "boolean", "real", "if", "endif", "else", "return", "put", "get", "while", "true", "false" };
//

const int OPERATOR_LIST_SIZE = 12;
const int SEPERATOR_LIST_SIZE = 9;
const char operator_list[OPERATOR_LIST_SIZE] = { '=', '+',  '-', '*', '/', ':', '=', '^', '>', '<', '%', '!'};
const char seperator_list[SEPERATOR_LIST_SIZE] = { ',', ';', '{', '}','(', ')', '[', ']', ':' };

const int colSize = 5;

//my temp fsm will change when needed
const int fsm[][colSize] = {			//row number
	{ 1, 2,  3, NULL, NULL },		// 1
	{ 2, 4, 5, 6, NULL },			// 2
	{ 3, NULL, 3, NULL, 7 },		// 3
	{ 4, 4, 5, 6, NULL },			// 4
	{ 5, 4, 5, 6, NULL },			// 5
	{ 6, NULL, NULL, NULL, NULL },	// 6
	{ 7, NULL, 8, NULL, NULL },		// 7
	{ 8, NULL, 8, NULL, NULL },		// 8
};

struct Token
{
	string token;
	string lexeme;
};


int main()
{
	string lexWord = "%% <= >= == = > < != ^=";
	list<string> test = split_lex_word(lexWord);
	while (test.size() != 0)
	{
		string tmp = test.front();
		test.pop_front();
		cout << tmp<< endl;

	}

	return 0;
}

char isLang(char lex_char)
{
	if (isdigit(lex_char))
	{
		return 'd';
	}
	else if (isalpha(lex_char))
	{
		return 'l';
	}
	else if (lex_char == '.')
	{
		return '.';

	}
	else if (lex_char == '$')
	{
		return '$';

	}
	else
	{
		//char passed isnt part of language can be used for exception handling
		return '\0';

	}


}

list<string> split_lex_word(string lex)
{
	//case [fahr:int]

	//list that will hold the list of strings for the lexer to parse
	list<string> lexWord;

	//was gunna use this for error checking
	//int sep_count = 0;
	int op_count = 0;

	string word = "";
	string number = "";
	string op ="";

	for (unsigned int i = 0; i < lex.size(); i++)
	{
		if (isSeperator(lex[i]))
		{
			//creating a string to put into string list
			//sep_count++;
			string sep(1, lex[i]);
			lexWord.push_back(sep);
		}
		else if (isOperator(lex[i]))
		{
			//need to make special case for 2 ops next to each other
			//creating a string to put into string list
			op.push_back(lex[i]);
			if (isOperator(lex[i + 1]))
			{
				op.push_back(lex[i + 1]);
				//fix this
				i++;
				lexWord.push_back(op);
				op.clear();
			}
			else
			{
				lexWord.push_back(op);
				op.clear();
			}
		}
		else if (isalpha(lex[i]) || lex[i] == '$')
		{
			//this is assuming that 
			word.push_back(lex[i]);
			if (isOperator(lex[i + 1]) || isSeperator(lex[i + 1]))
			{
				lexWord.push_back(word);
				word.clear();

			}

		}
		else if (isdigit(lex[i]))
		{
			number.push_back(lex[i]);
			if (isOperator(lex[i + 1]) || isSeperator(lex[i + 1]))
			{
				lexWord.push_back(word);
				word.clear();

			}
			else if (lex[i + 1] == '.')
			{
				number.push_back(lex[i + 1]);
			}

		}
	}
	//I added this just to check if the strings got cleared
	if (word != "")
	{
		lexWord.push_back(word);
	}

	if (number != "")
	{
		lexWord.push_back(number);
	}
		

	return lexWord;
}


//boolean function that checks to see if to_lex is an operator
bool isOperator(char to_lex)
{
	for (int i = 0; i < OPERATOR_LIST_SIZE; i++)
	{
		if (to_lex == operator_list[i])
		{
			return true;

		}

	}
	return false;

}
//Function that checks if a characater is a seperator
bool isSeperator(char to_lex)
{

	for (int i = 0; i < SEPERATOR_LIST_SIZE; i++)
	{
		if (to_lex == seperator_list[i])
		{
			return true;

		}

	}
	return false;

}
/*list<Token> lexer(string lexWord)
{
	//Get word from main
	//parse the word using check_for_operators_and_pass_to_lexer(word_to_lex)

	//split this into an array or linked list of token items
	//check token for digit or letter if so pass fsm
	//then cjeck token for length one operator from operator list
	// then check token for length two operator from op list
	// if token length 3 or more pass to FSM

	//need function that does the transition;
	//Would be it okay to hard code this?
	//Current transition function ideas
	//Determine the current state
	//from that state identify possible state transitions 
	//continue until the word has been read fully.

	list<string> lexStrings = split_lex_word(lexWord);
	list<Token> tokenList;
	while (lexStrings.size() != 0)
	{
		string word = lexStrings.front();
		Token lex;
		//This handles seperators/operators of length one bypasses FSM
		if (word.size() == 1)
		{
			if (isSeperator(word[0]))
			{
				lex.token = "Seperator";
				lex.lexeme = word;
				tokenList.push_back(lex);
				continue;
			}
			if (isOperator(word[0]))
			{
				lex.token = "Operator";
				lex.lexeme = word;
				tokenList.push_back(lex);
				continue;
			}
		}




		//need to check 
		//lexStrings.pop_front();
	}




}*/
/*void fake_lexer(string to_lex)
{
	//Get word from main
	//parse the word using check_for_operators_and_pass_to_lexer(word_to_lex)

	//split this into an array or linked list of token items
	//check token for digit or letter if so pass fsm
	//then cjeck token for length one operator from operator list
	// then check token for length two operator from op list
	// if token length 3 or more pass to FSM

	int iter = 0;

	//Special case for Seperators at both ends of string if we solve this special case first it will be easier to solve other cases
	if (isSeperator(to_lex[iter]) && isSeperator(to_lex[to_lex.length() - 1]))
	{
		//need to create struct token that holds two strings to do output
		cout << "Seperator \t" << to_lex[iter] << endl;
		iter++;

		//then checks to see if next char is digit or letter
		if (isdigit(to_lex[iter]) || isalpha(to_lex[iter]))
		{
			int state = 1;
			int stateArray[colSize];
			for (iter; iter < to_lex.size(); iter++)
			{
				//need function that does the transition;
				//Would be it okay to hard code this?
				//Current transition function ideas
				//Determine the current state
				//from that state identify possible state transitions 
				//continue until the word has been read fully.


			}


			//go to FSM
		}
		cout << "Seperator \t" << to_lex[to_lex.length() - 1] << endl;

	}
	else if (isdigit(to_lex[iter]) || isalpha(to_lex[iter]))
	{
		int state = 1;
		for (iter; iter < to_lex.size(); iter++)
		{
			//need function that does the transition;
			//Would be it okay to hard code this?
			//Current transition function ideas
			//Determine the current state
			//from that state identify possible state transitions 
			//continue until the word has been read fully.


		}

	}
	return;
}*/