//Gretchen Gilbreath
//October 25, 2014
//Project 2
//CS 303 FS 2014 UMKC

#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include"Expression.h"
using namespace std;

void enterFromFile(Expression* tExpression, int& count, int& size);
void enterFromKeys(Expression* tExpression, int& count, int& size);
bool enterInputSource(Expression* tExpression, int& count, int& size);

//I that fewer than 80 characters would be entered in an expression
//Only 50 or fewer expressions may be entered

int main()
{
	//returns whether the expression was successfully entered
	//bool expressionSuccess = false;	//11/2 don't need
	
	char userDone = 'n';	//11/2 added
	
	//counts the number of expressions being used
	int count = 0;
	
	//initial size of dynamic array
	int size = 1000;	// 11/2
	 	
	//instantiates 1000 expression objects
//	Expression tExpression[1000];	// 11/2
	
	//instantiates dynamic array
	Expression* expression = new Expression[size];


	//user menu choice message
//	cout << "To enter an expression manually, type 'B'. To retrieve an expression or expressions from a file," 	//11/2changed format
//		<< " type 'A'. Enter 'E' to exit the program.\n";

	//looks for input as long as nothing has been input successfully
	/*// 11/2 no longer needed
	while (!expressionSuccess)
	{
		expressionSuccess = enterInputSource(tExpression, count);
	}
	*/
	
		//gets expressions from user or from file		// 11/2 added
	while (userDone == 'N' || userDone == 'n')
	{
		//asks for user input
		cout << "To enter an expression manually, type 'A'." << endl
			<< "To retrieve from a file, type 'B'."
			<< endl << "Enter 'E' to exit the program.\n";
		enterInputSource(expression, count, size);

		cout << "Are you done entering expressions? Y or N" << endl;
		cin >> userDone;

	}
	
	
//	cout << "Results: \n";	//11/2

/*	11/2 now in enterFromFile and enterFromKeys
	for (int i = 0; i < count; i++)
	{
		//cout << "Expression #" << i << ":  " << tExpression[i] << endl << "   Result: " << tExpression[i] << endl;
		cout << "Expression #" << i << ":  " << tExpression[i].getString() << endl;
		double the_answer = tExpression[i].getAnswer();
		cout << "   Result: " << (isnan(the_answer) ? "N/A" : to_string(the_answer)) << endl;
		cout << "---------------------" << endl;
	}
	*/
	
	delete [] expression;	// 11/2 deletes dynamic array

	system("pause");


	return 0;
}

void enterFromFile(Expression* tExpression, int& count, int& size)
{
	//input file
	ifstream fin;
	//user given name of input file
	string fileName;


	cout << "Enter the name of the file to open.\n";
	
	//get file name from user and open it
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


	//allows user to enter up to 80 characters
	char fileInput[80];

	//goes through file as long as there is information available
	while (!fin.eof())
	{
		fin.getline(fileInput, 80);
		
		//outputs expression and result new to errors
		cout << endl << "Expression #" << count + 1 << ":  " << tExpression[count].getString() << endl;	//11/2
		
		//inputs expression and calculates answer
		tExpression[count].set(string(fileInput));
		
		double the_answer = tExpression[count].getAnswer();
		
		//outputs result 
		cout << setw(4) << "";
		cout << "Result: " << (isnan(the_answer) ? "N/A" : to_string(the_answer)) << endl;
		cout << "---------------------" << endl;


		count++;
	}


	fin.close();
	//don't forget to grab the expression.
}

void enterFromKeys(Expression* tExpression, int& count, int&size) //11/2 added)
{
//	char yOrN = 'y';	//see below

//11/2 	do			//see below
//11/2	{
		string userInput;

//11/2		cout << "Enter an expression. Make sure the expressions contains only mathematical symbols, digits, and spaces.\n";

		cout << "Enter an expression. Make sure the expressions contains " << endl	//11/2 changed output 
			<< "only mathematical symbols, digits, and spaces." << endl;		//expression format
		
		//get expression from user	
		cin >> userInput;
		
		//11/2 outputs expression number and expression itself to the window -- expression doesn't currently output
		cout << endl << "Expression #" << count + 1 << ": " << tExpression[count].getString() << endl;

		
		//put value in new element
		tExpression[count].set(userInput);

		double the_answer = tExpression[count].getAnswer();
		
		//outputs result 
		cout << setw(4) << "";
		cout << "Result: " << (isnan(the_answer) ? "N/A" : to_string(the_answer)) << endl;
		cout << "---------------------" << endl;
		
		
		cout << setw(4) << "";		// 11/2 outputs result next to errors
		cout << "Result: " << tExpression[count].getAnswer() << endl << endl;	//11/2
		
		count++;

/*11/2 commented out this stuff
		cout << "Would you like to enter another expression? Enter Y for YES or N for NO.\n";
		cin >> yOrN;

	} while (yOrN == 'y' || yOrN == 'Y');
*/

	return;
}

bool enterInputSource(Expression* tExpression, int& count, int& size)//added 11/2)
{
	char inputSource;
	cin >> inputSource;


	switch (inputSource)
	{
	case 'A':
	case 'a': enterFromKeys(tExpression, count, size); return true; break;
	case 'B':
	case 'b': enterFromFile(tExpression, count, size); return true;  break;
	case 'E':
	case 'e': return true;  break;	//exit from here
	default: cout << "Invalid option. Please choose again.\n"; break;
	}

}

// 11/2: need to output string expression with results. as of now, expression doesn't output.
// also make array dynamic
