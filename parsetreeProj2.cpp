// parsetreeProj2.cpp : Defines the entry point for the console application.
//

// lexerTesting.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <queue>
#include <cctype>
#include "SyntacticalAnalyzer.h"

using namespace std;

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
queue<string> tokenToProductionList(list<Token> tokenList);
list<string> split_lex_word(string lex);
list<Token> lexer(string lexWord);
const int KEYWORD_LIST_SIZE = 13;
const string keyword_list[KEYWORD_LIST_SIZE] = { "function", "int", "boolean", "real", "if", "endif", "else", "return", "put", "get", "while", "true", "false" };
//

const int OPERATOR_LIST_SIZE = 12;
const int SEPERATOR_LIST_SIZE = 9;
const char operator_list[OPERATOR_LIST_SIZE] = { '=', '+',  '-', '*', '/', ':', '=', '^', '>', '<', '%', '!' };
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



int main()
{
	cout << "Enter name of source file to parse: ";
	string file_name;
	cin >> file_name;

	string source_string = get_source_string(file_name);

	int source_iter = 0;
	string word_to_lex;

	string output_name;
	cout << "Output File Name: ";
	cin >> output_name;
	ofstream output_file;
	output_file.open(output_name, ios::out | std::ofstream::trunc);

	while (source_iter <  source_string.length())
	{
		word_to_lex = find_word_to_lex(source_string, source_iter);
		skip_white_space(source_string, source_iter);
		list<Token> tokenList;

		try
		{
			tokenList = lexer(word_to_lex);
		}
		catch (...)
		{
			output_file << "Compiler Error: Check Source for Syntax Errors";
			output_file.close();
			exit(1);
		}

		SyntacticalAnalyzer sa(tokenToProductionList(tokenList));

		sa.analyze();

		/*while (tokenList.size() != 0)
		{
		Token tmp = tokenList.front();
		tokenList.pop_front();
		output_file << tmp.token + "\t" + tmp.lexeme + "\n";

		}*/
	}

	output_file.close();
	return 0;
}

queue<string> tokenToProductionList(list<Token> tokenList)
{
	Token tmp;

	queue<string> inputQ;
	
	while(tokenList.size() > 0)
	{
		tmp = tokenList.front();
		if (tmp.token == "Identifier")
		{
			inputQ.push("identifier");

		}
		else
			inputQ.push(tmp.lexeme);

		tokenList.pop_front();

	}

	return inputQ;

}

#pragma region Lexer Analyzer
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
				lexStrings.pop_front();
				continue;
			}
			if (isOperator(word[0]))
			{
				lex.token = "Operator";
				lex.lexeme = word;
				tokenList.push_back(lex);
				lexStrings.pop_front();
				continue;
			}
		}
		else if (word.size() == 2)
		{

			if (isOperator(word[0]))
			{
				if (word == "%%")
				{
					lex.token = "Main\t";
					lex.lexeme = word;
					tokenList.push_back(lex);
					lexStrings.pop_front();
					continue;
				}
				else
				{
					lex.token = "Operator";
					lex.lexeme = word;
					tokenList.push_back(lex);
					lexStrings.pop_front();
				}

			}

		}
		else if (word.size() >= 3)
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
					cout << "Character is not part of language" << endl;
					break;
				}
			}

			if (state == 2 || state == 4 || state == 6)
			{
				if (isKeyword(word))
				{
					lex.token = "KeyWord\t";
					lex.lexeme = word;
					tokenList.push_back(lex);
					lexStrings.pop_front();
				}
				else
				{
					lex.token = "Identifier";
					lex.lexeme = word;
					tokenList.push_back(lex);
					lexStrings.pop_front();
				}

			}
			else if (state == 3)
			{
				lex.token = "Integer";
				lex.lexeme = word;
				tokenList.push_back(lex);
				lexStrings.pop_front();
			}
			else if (state == 8)
			{
				lex.token = "Real\t";
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
#pragma endregion
