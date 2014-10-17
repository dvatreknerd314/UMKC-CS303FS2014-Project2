#include "syntax_checker.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	string the_input;
	ifstream test_file("test_input.txt");
	getline(test_file, the_input);
	test_file.close();
	SyntaxChecker syntaxChecker;
	syntaxChecker.syntax_check(the_input);
	
	return 0;
}