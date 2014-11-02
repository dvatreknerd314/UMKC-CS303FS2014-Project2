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
	//void evaluate();
	void set(string hString);
	double getAnswer();
	string getString();
	//void showResult();
	//friend std::ostream& operator<<(std::ostream& os, Expression mExpression);
	//friend std::istream& operator>>(std::istream& is, Expression mExpression);
private:
	//bool error;
	string exprString;
	//string errorMessage;
	int answer;

};


//Problems:
//1. Would it be at all practical to represent each expression by a list, so that it could be output more neatly if called? It didn't look 
//		like the list implemented could be accessible by other classes, and I didn't want the program to call syntax_check twice (once for 
//		the evaluator class, once for the expression class) in order to get a list.
//2. Should I change the menu class to add the expressions dynamically?
//6. Is it fine that none of the error messages are output through the wrapper class?
