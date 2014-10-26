//Gretchen Gilbreath
//October 25, 2014
//Project 2
//CS 303 FS 2014 UMKC

#pragma once
#include"Evaluator.h"
#include<iostream>
//#include<list>
using namespace std;


class Expression
{
public:
	//default constructor
	Expression(){ answer = 0; }
	Expression(std::string inputString);
	~Expression();
	void evaluate();
	void set(string hString);
	//int getAnswer();
	//void showResult();
	friend std::ostream& operator<<(std::ostream& os, Expression mExpression);
	//friend std::istream& operator>>(std::istream& is, Expression mExpression);
private:
	bool error;
	string exprString;
	string errorMessage;
	int answer;

};


//Problems:
//1. Would it be at all practical to represent each expression by a list, so that it could be output more neatly if called? It didn't look 
//		like the list implemented could be accessible by other classes, and I didn't want the program to call syntax_check twice (once for 
//		the evaluator class, once for the expression class) in order to get a list.
//2. Should I change the menu class to add the expressions dynamically?
//3. Will I be able to access the errors through the Evaluator class? If not, it might be practical to either coordinate the evaluator and
//		syntax check classes through the wrapper class, or to write some getError and getList functions through the Evaluator class
//4. Is the menu class sufficient? 
//5. Is there a convenient way to set the result of the expression as a string, so that I can output either the result, or an error message
//		in the same function?
//6. ********Currently, no error is output if there is an error.
