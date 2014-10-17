#include "syntax_checker.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	char temp_string[500];
	ifstream test_file;
	test_file.open("./test_input.txt");
	test_file.getline(temp_string, 500);
	test_file.close();
	string the_input(temp_string);
	SyntaxChecker syntaxChecker;
	syntaxChecker.syntax_check(the_input);
	
	return 0;
}