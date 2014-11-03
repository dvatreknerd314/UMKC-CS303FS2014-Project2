//Chris Yuhas
//CS 303
//Checks to see that wrong input generates an error for the syntax checker
#include "Constants.h"
#include "syntax_checker.h"
#include <iostream>
using namespace std;

int main()
{
	SyntaxChecker ans;
	string num;
	cout << "Enter equeation: ";
	cin >> num;
	ans.syntax_check(num);
	system("pause");
	return 0;

}