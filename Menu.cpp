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

//An expression should contain fewer than 80 characters
//Only 100 or fewer expressions may be entered

int main()
{
	char userDone = 'n';	
	
	//counts the number of expressions being used
	int count = 0;
	
	//initial size of dynamic array
	int size = 100;	
	
	//instantiates dynamic array
	Expression* expression = new Expression[size];
	
	//starts automatically
	//repeats as long as the user enters n or N
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
	

	delete [] expression;	

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
}

void enterFromKeys(Expression* tExpression, int& count, int&size)
{
		string userInput;


		cout << "Enter an expression. Make sure the expressions contains " << endl	//11/2 changed output 
			<< "only mathematical symbols, digits, and spaces." << endl;		//expression format
			
		//get expression from user	
		getline(cin, userInput);
		
		//11/2 outputs expression number and expression itself to the window -- expression doesn't currently output
		cout << endl << "Expression #" << count + 1 << ": " << tExpression[count].getString() << endl;

		//put value in new element
		tExpression[count].set(userInput);

		double the_answer = tExpression[count].getAnswer();
		
		//outputs result 
		cout << setw(4) << "";
		cout << "Result: " << (isnan(the_answer) ? "N/A" : to_string(the_answer)) << endl;
		cout << "---------------------" << endl;
		
		count++;

	return;
}

//gets user input to determine input source
bool enterInputSource(Expression* tExpression, int& count, int& size)
{
	char inputSource;
	cin >> inputSource;
	cin.get();

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

//I also need to set precision
