#include "syntax_checker.h"
#include "Evaluator.h"
#include <iostream>
#include <fstream>
#include <list>
using namespace std;
/*
int main() {
	string the_input;
	ifstream test_file("test_input.txt");
	SyntaxChecker syntaxChecker;
	list<exprToken> theList;
	while (!test_file.eof()) {
		getline(test_file, the_input);
		cout << "Evaluating " << the_input << " : ";
		if (!syntaxChecker.syntax_check(the_input, theList))
		{
			for (list<exprToken>::iterator i = theList.begin(); i != theList.end(); i++)
			{
				cout << (*i).toString() << " ";
			}
			cout << endl;
			cout << "Evaluates to: " << evaluate_expression(the_input);
			cout << endl;
		}
		theList.clear();
	}
	test_file.close();
	return 0;
}

*/