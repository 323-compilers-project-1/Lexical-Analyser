#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void fake_lexer(string to_lex);
string get_source_string(string file_name);
string find_word_to_lex(string source, int & iter);
void skip_comments(string source, int & iter);
void skip_white_space(string source, int & iter);
void check_for_operators_and_pass_to_lexer(string &word);
void check_for_operators_at_front(string &word);
void check_for_operators_at_back(string &word);

const int KEYWORD_LIST_SIZE = 13;
const int OPERATOR_LIST_SIZE = 20;
const string KEYWORD_LIST[KEYWORD_LIST_SIZE] = {"function", "int", "boolean", "real", "if", "endif", "else", "return", "put", "get", "while", "true", "false" };
const char OPERATOR_LIST[OPERATOR_LIST_SIZE] = { '=', '+',  '-', '*', '/', ':', '(', ')', '[', ']', '{', '}', '==', '^=', '>', '<', '=>', '=<', ';', ','};

void main() 
{
	cout << "Enter name of source file to parse: ";
	string file_name;
	cin >> file_name;
	cout << endl << endl;

	string source_string = get_source_string(file_name);

	int source_iter = 0;
	string word_to_lex;
	while (source_iter <  source_string.length()) 
	{
		word_to_lex = find_word_to_lex(source_string, source_iter);
		skip_white_space(source_string, source_iter);
		if (word_to_lex.size() == 1)
		{
			fake_lexer(word_to_lex);
		}
		else 
		{
			check_for_operators_and_pass_to_lexer(word_to_lex);
		}
	}
}




void fake_lexer(string to_lex) 
{
	cout << to_lex << endl;
}


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


void skip_white_space(string source, int & iter) 
{
	while ((source[iter] == ' ' || source[iter] == '\n' || source[iter] == '\t') && iter <  source.length()) 
	{
		iter++;
	}
}


void check_for_operators_and_pass_to_lexer(string &word)
{
	check_for_operators_at_front(word);
	check_for_operators_at_back(word);
}


void check_for_operators_at_front(string &word)
{
	if (word.size() > 1)
	{
		bool start_of_word = false;
		int word_iter = 0;
		while (!start_of_word && word_iter < word.size())
		{
			bool found_op = false;
			for (int op_iter = 0; op_iter < OPERATOR_LIST_SIZE; op_iter++)
			{
				if (word[word_iter] == OPERATOR_LIST[op_iter])
				{
					string op_to_lex = word.substr(word_iter, word_iter + 1);
					word = word.substr(word_iter + 1, word.size());
					found_op = true;
					fake_lexer(op_to_lex);
					word_iter++;
				}
			}
			if (!found_op)
			{
				start_of_word = true;
			}
		}
	}
}

void check_for_operators_at_back(string &word)
{
	if (word.size() > 1)
	{
		vector<string> found_ops_vect;
		bool end_of_word = false;
		int word_iter = word.size() - 1;
		if (word[word_iter] == '$')
		{
			end_of_word = true;
		}
		while (!end_of_word && word_iter > 0)
		{
			bool found_op = false;
			for (int op_iter = 0; op_iter < OPERATOR_LIST_SIZE; op_iter++)
			{
				if (word[word_iter] == OPERATOR_LIST[op_iter])
				{
					string op_to_lex = word.substr(word_iter, word.size());
					word = word.substr(0, word_iter);
					found_op = true;
					found_ops_vect.push_back(op_to_lex);
					word_iter--;
				}
			}
			if (!found_op)
			{
				end_of_word = true;
			}
		}
		fake_lexer(word);
		for (int i = 0; i < found_ops_vect.size(); i++)
		{
			fake_lexer(found_ops_vect[i]);
		}
	}
}