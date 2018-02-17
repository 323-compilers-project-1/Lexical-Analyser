#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void fake_lexer(string to_lex);
string get_source_string(string file_name);
void skip_white_space(string source, int & iter);
void skip_comments(string source, int & iter);
string find_word_to_lex(string source, int & iter);

const string keyword_list[13] = {"function", "int", "boolean", "real", "if", "endif", "else", "return", "put", "get", "while", "true", "false" };
const char operator_list[12] = { '=', '+',  '-', '*', '/', ':', '==', '^=', '>', '<', '=>', '=<'};

void main() 
{
	cout << "Enter name of source file to parse: ";
	string file_name;
	cin >> file_name;
	cout << endl << endl;

	string source_string = get_source_string(file_name);

	int source_iter = 0;
	while (source_iter <  source_string.length()) 
	{
		string word_to_lex;
		word_to_lex = find_word_to_lex(source_string, source_iter);
		skip_white_space(source_string, source_iter);
		fake_lexer(word_to_lex);
	}
	skip_white_space(source_string, source_iter);
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
	while (source[iter] != ' ' && source[iter] != '\n' &&
		source[iter] != '\t' && iter < source.length()) 
	{
		if (source[iter] == '!') 
		{
			skip_comments(source, iter);
		}
		skip_white_space(source, iter);
		word += source[iter];
		iter++;
	}
	return word;
}


void skip_white_space(string source, int & iter) 
{
	while ((source[iter] == ' ' || source[iter] == '\n' ||
		source[iter] == '\t') && iter <  source.length()) 
	{
		iter++;
	}
}


void skip_comments(string source, int & iter) 
{
	iter++;
	while (source[iter] != '!') 
	{
		iter++;
	}
	iter++;
}