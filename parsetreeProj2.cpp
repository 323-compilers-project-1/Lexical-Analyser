
// LexicalAnalyzer.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
// LexicalAnalyzer.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "SyntacticalAnalyzer.h"
#include "SymbolTable.h"
#include <queue>
#include <algorithm>

using namespace std;

//special case implementations
/*
1. (fahr <= num)
for this special case we could check if the word starts and ends with a seprerator (someting i think we would want for the parser in Proj 2)
after we checked this condtion we could output the first seperator as token and lexeme
*/

struct Token
{
	string token;
	string lexeme;
};

//Daniels Functions
string get_source_string(string file_name);
string find_word_to_lex(string source, int & iter);
void skip_comments(string source, int & iter);
void skip_white_space(string source, int & iter);

//Carlos's function
bool isSeperator(char to_lex);
bool isOperator(char to_lex);
char isLang(char lex_char);
bool isKeyword(string word);
list<string> split_lex_word(string lex);
list<Token> lexer(string lexWord);

const int KEYWORD_LIST_SIZE = 10;
const string keyword_list[KEYWORD_LIST_SIZE] = { "function", "if", "endif", "else", "return", "put", "get", "while", "true", "false" };

const int SIZE_ONE_OPERATOR_LIST_SIZE = 12;
const int SIZE_TWO_OPERATOR_LIST_SIZE = 4;
const int SEPERATOR_LIST_SIZE = 9;
const char seperator_list[SEPERATOR_LIST_SIZE] = { ',', ';', '{', '}','(', ')', '[', ']' };
const char size_one_operator_list[SIZE_ONE_OPERATOR_LIST_SIZE] = { '=', '+',  '-', '*', '/',':', '=', '^', '>', '<', '%', '!' };
const string size_two_operator_list[10] = { "==", "^=", "=>", "=<" };

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

int main()
{
	cout << "Enter name of source file to parse: ";
	string file_name;
	cin >> file_name;

	string source_string = get_source_string(file_name);

	int source_iter = 0;
	string word_to_lex;

	queue<string> inputQ;
	vector<string> symIds;
	list<string> lexemes;
	vector<string>::iterator it;


	while (source_iter <  source_string.length())
	{
		word_to_lex = find_word_to_lex(source_string, source_iter);
		skip_white_space(source_string, source_iter);
		list<Token> tokenList;

		

		try
		{
			tokenList = lexer(word_to_lex);



			while (tokenList.size() > 0)
			{
				
				Token tmp = tokenList.front();
				lexemes.push_back(tmp.lexeme);
				char dSign = '$';
				if (tmp.token == "identifier" || (tmp.lexeme).back() == dSign)
				{
					if (tmp.lexeme != "int") //need to add the vect for all identifiers here
					{
						inputQ.push(tmp.token);

						//add queue for lexmes of identifiers to keep track of when they were used project 3

						if (tmp.lexeme == "integer" || tmp.lexeme == "boolean")
						{
							symIds.push_back(tmp.lexeme);
						}

						it = find(symIds.begin(), symIds.end(), tmp.lexeme);

						if (it == symIds.end())
						{
							
							symIds.push_back(tmp.lexeme);
						}
						else if(it != symIds.end() && tmp.lexeme == "integer" || tmp.lexeme == "boolean")
						{
							/*int i = distance(symIds.begin(), it);
							if (symIds[i] == tmp.lexeme)
							{
								cout << "cannot declare the same var " << tmp.lexeme << endl;
							} */
							
							vector<string>::iterator check;

							for (list<Token>::iterator i = tokenList.begin(); i != tokenList.end(); i++)
							{
								string tmp = i->lexeme;
								check = find(symIds.begin(), symIds.end(), tmp);

								if (check != symIds.end())
								{
									cout << "cannot declare things twice" << endl;
									break;

								}
							
							
							
							}


								



						}
							
						
					}
					else
						inputQ.push("int");
				}
				else if (tmp.token == "integer")
				{
					inputQ.push("int");
				}
				else if (tmp.token == "real")
				{
					inputQ.push(tmp.token);
				}
				else
					inputQ.push(tmp.lexeme);

				tokenList.pop_front();
			}


		}
		catch (...)
		{
			ofstream output_file;
			output_file.open("Error Log", ios::out | std::ofstream::trunc);
			output_file << "Compiler Error: Check Source for Syntax Errors";
			output_file.close();
			exit(1);
		}

	}

	//hard coding the removal of integer from symIds


	SymbolTable sm(symIds, lexemes);
	//sm.printSymbolTable();

	SyntacticalAnalyzer sa(inputQ);

	sm.printSymbolTable();

	sa.analyze();

	return 0;
}

list<Token> lexer(string lexWord)
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

	list<string> lexStrings;
	lexStrings = split_lex_word(lexWord);
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
				lexStrings.pop_front();
			}
			if (isOperator(word[0]))
			{
				lex.token = "Operator";
				lex.lexeme = word;
				tokenList.push_back(lex);
				lexStrings.pop_front();
			}
			if (isdigit(word[0]))
			{
				lex.token = "integer";
				lex.lexeme = word;
				tokenList.push_back(lex);
				lexStrings.pop_front();
			}
			if (isalpha(word[0]))
			{
				lex.token = "identifier";
				lex.lexeme = word;
				tokenList.push_back(lex);
				lexStrings.pop_front();
			}
		}

		bool operator_found = false;
		if (word.size() == 2)
		{
			if (word == "%%")
			{
				lex.token = "Operator";
				lex.lexeme = word;
				tokenList.push_back(lex);
				lexStrings.pop_front();
				operator_found = true;
			}
			if (!operator_found)
			{
				for (int i = 0; i < SIZE_TWO_OPERATOR_LIST_SIZE; i++)
				{
					if (word == size_two_operator_list[i])
					{
						lex.token = "Operator";
						lex.lexeme = word;
						tokenList.push_back(lex);
						lexStrings.pop_front();
						operator_found = true;
					}
				}
			}
		}
		if (word.size() > 1 && !operator_found)
		{
			//Starting state
			int state = 1;
			int stIndex = 0;

			//FSM implemenation
			for (int i = 0; i < word.size(); i++)
			{
				char currChar = isLang(word[i]);
				switch (currChar)
				{
				case 'l':
					state = fsm[stIndex][1];
					stIndex = state - 1;
					break;
				case 'd':
					state = fsm[stIndex][2];
					stIndex = state - 1;
					break;
				case '$':
					state = fsm[stIndex][3];
					stIndex = state - 1;
					break;
				case '.':
					state = fsm[stIndex][4];
					stIndex = state - 1;
					break;
				default:
					throw "token_error";
					break;
				}
			}

			if (state == 2 || state == 4 || state == 6)
			{
				if (isKeyword(word))
				{
					lex.token = "KeyWord";
					lex.lexeme = word;
					tokenList.push_back(lex);
					lexStrings.pop_front();
				}
				else
				{
					lex.token = "identifier";
					lex.lexeme = word;
					tokenList.push_back(lex);
					lexStrings.pop_front();
				}

			}
			else if (state == 3)
			{
				lex.token = "integer";
				lex.lexeme = word;
				tokenList.push_back(lex);
				lexStrings.pop_front();
			}
			else if (state == 8)
			{
				lex.token = "real";
				lex.lexeme = word;
				tokenList.push_back(lex);
				lexStrings.pop_front();
			}


		}

		//need to check
		//lexStrings.pop_front();
	}
	return tokenList;
}

//Function that determines if a characters is part of language/FSM
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
	string word = "";
	string number = "";
	string op = "";

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
			if (isOperator(lex[i + 1]) || isSeperator(lex[i + 1]) || lex[i + 1] == ' ')
			{
				lexWord.push_back(word);
				word.clear();

			}

		}
		else if (isdigit(lex[i]) || lex[i] == '.')
		{
			number.push_back(lex[i]);
			if (isOperator(lex[i + 1]) || isSeperator(lex[i + 1]) || lex[i + 1] == ' ')
			{
				lexWord.push_back(number);
				number.clear();

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

bool isKeyword(string word)
{
	for (int i = 0; i < KEYWORD_LIST_SIZE; i++)
	{
		if (word == keyword_list[i])
		{
			return true;

		}

	}
	return false;
}

//boolean function that checks to see if to_lex is an operator
bool isOperator(char to_lex)
{
	for (int i = 0; i < SIZE_ONE_OPERATOR_LIST_SIZE; i++)
	{
		if (to_lex == size_one_operator_list[i])
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
//Function that takes in an input filename and outputs all source code into one string
string get_source_string(string file_name)
{
	ifstream source_file_reader;
	source_file_reader.open(file_name);

	if (!source_file_reader)
	{
		cerr << "Unable to open " + file_name;
		exit(1);
	}

	string source_string;

	source_string.reserve(source_file_reader.tellg());
	source_string.assign((istreambuf_iterator<char>(source_file_reader)), istreambuf_iterator<char>());
	source_file_reader.close();
	return source_string;

}

//Finds word to lex from source string
//Uses skip comments and white space comments
string find_word_to_lex(string source, int & iter)
{
	string word;
	while (source[iter] != ' ' && source[iter] != '\n' && source[iter] != '\t' && iter < source.length())
	{
		if (source[iter] == '!')
		{
			skip_comments(source, iter);
		}
		word += source[iter];
		iter++;
	}
	return word;
}

//Function that skips white space takes in iter from main and find_word_to_lex
void skip_white_space(string source, int & iter)
{
	while ((source[iter] == ' ' || source[iter] == '\n' ||
		source[iter] == '\t') && iter <  source.length())
	{
		iter++;
	}
}

//Function that skips comments takes in iter from main and find_word_to_lex
void skip_comments(string source, int & iter)
{
	iter++;
	while (source[iter] != '!')
	{
		iter++;
	}
	iter++;
	skip_white_space(source, iter);
}