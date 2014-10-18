#include "syntax_checker.h"
#include <iostream>
#include <fstream>
using namespace std;

int main() {
	string the_input;
	ifstream test_file("test_input.txt");
	SyntaxChecker syntaxChecker;
	while (!test_file.eof()) {
		getline(test_file, the_input);
		cout << "Evaluating " << the_input << " : ";
		if (!syntaxChecker.syntax_check(the_input))
			cout << "No syntax problems" << endl;
	}
	test_file.close();
	return 0;
}