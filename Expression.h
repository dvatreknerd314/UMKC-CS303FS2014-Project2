//Gretchen Gilbreath
//October 25, 2014
//Project 2
//CS 303 FS 2014 UMKC

#pragma once
#include"Evaluator.h"
#include<iostream>
using namespace std;


class Expression
{
public:
	//default constructor
	Expression();
	Expression(std::string inputString);
	~Expression();
	//void evaluate();
	void set(string hString);
	double getAnswer();
	string getString();
	friend ostream& operator <<(ostream& os, const Expression& expression);
	friend istream& operator >>(istream& is, Expression mExpression);
	Expression operator= (Expression& rhs);
private:
	//bool error;
	string exprString;
	//string errorMessage;
	double answer;

};

