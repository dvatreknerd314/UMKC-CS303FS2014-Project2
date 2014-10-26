//Gretchen Gilbreath
//October 25, 2014
//Project 2
//CS 303 FS 2014 UMKC

#include<iostream>
#include<fstream>
#include<string>
#include"Expression.h"
using namespace std;

void enterFromFile(Expression* tExpression, int& count);
void enterFromKeys(Expression* tExpression, int& count);
bool enterInputSource(Expression* tExpression, int& count);

//I assumed up to 100 characters could be entered in an expression
//Only 50 or fewer expressions may be entered

int main()
{
	//returns whether the expression was successfully entered
	bool expressionSuccess = false;
	//instantiates 50 expression objects
	Expression tExpression[50];
	//counts the number of expressions being used
	int count = 0;

	//user menu choice message
	cout << "To enter an expression manually, type 'A'. To retrieve an expression or expressions from a file," 
		<< " type 'B'. Enter 'E' to exit the program.\n";

	//looks for input as long as nothing has been input successfully
	while (!expressionSuccess)
	{
		expressionSuccess = enterInputSource(tExpression, count);
	}

	
	cout << "Results: \n";

	for (int i = 0; i < count; i++)
	{
		//cout << "Expression #" << i << ":  " << tExpression[i] << endl << "   Result: " << tExpression[i] << endl;
	
		cout << "Expression #" << i << ":  " << tExpression[i].getString() << endl << "   Result: " << tExpression[i].getAnswer() << endl;
	}


	system("pause");


	return 0;
}

void enterFromFile(Expression* tExpression, int& count)
{
	ifstream fin;
	string fileName;


	cout << "Enter the name of the file to open.\n";
	cin >> fileName;
	fin.open(fileName);

	while (!fin.good())
	{
		cout << "Invalid file name. Please re-enter the file name, or type 'M' to return to the main menu.\n";

		cin >> fileName;

		if (fileName == "m" || fileName == "M")
		{
			return;
		}
		fin.open(fileName);
	}


	//allows user to enter up to 100 characters
	char fileInput[100];

	//goes through file as long as there is information available
	while (!fin.eof() && count < 50)
	{
		fin.getline(fileInput, 100);
		tExpression[count].set(string(fileInput));
		count++;
	}


	fin.close();
	//don't forget to grab the expression.
}

void enterFromKeys(Expression* tExpression, int& count)
{
	char yOrN = 'y';

	do
	{
		string userInput;

		cout << "Enter an expression. Make sure the expressions contains only mathematical symbols, digits, and spaces.\n";

		cin >> userInput;

		tExpression[count].set(userInput);
		count++;

		cout << "Would you like to enter another expression? Enter Y for YES or N for NO.\n";
		cin >> yOrN;

	} while (yOrN == 'y' || yOrN == 'Y');

	return;
}

bool enterInputSource(Expression* tExpression, int& count)
{
	char inputSource;
	cin >> inputSource;


	switch (inputSource)
	{
	case 'A':
	case 'a': enterFromFile(tExpression, count); return true;  break;
	case 'B':
	case 'b': enterFromKeys(tExpression, count); return true; break;
	case 'E':
	case 'e': return true;  break;	//exit from here
	default: cout << "Invalid option. Please choose again.\n"; break;
	}

}
