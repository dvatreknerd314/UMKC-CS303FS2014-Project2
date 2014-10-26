//Gretchen Gilbreath
//October 25, 2014
//Project 2
//CS 303 FS 2014 UMKC

#include "Expression.h"

//
Expression::Expression(std::string inputString)
{
	exprString = inputString;
}

//destructor
Expression::~Expression()
{
}

//overloaded << operator for returning expressions
std::ostream& operator<<(std::ostream& os, Expression mExpression)
{
	os << mExpression.exprString;

	if (!mExpression.error)
		os << mExpression.answer;
	else
		os << mExpression.errorMessage;

	return os;
}

/*
//overloaded >> operator for entering expressions
std::istream& operator>>(std::istream& is, Expression mExpression)
{
	is >> mExpression.exprString;

	return is;
}
*/

//function that allows the user to set the string
void Expression::set(string hString)
{
	exprString = hString;
}

//evaluates the eexpression, doesn't return the error
void Expression::evaluate()
{
	Expression tempExpr;
	answer = tempExpr.evaluate_expression(exprString);
	
	//sets error to true if there is an error
	if (answer == NULL)
	{
		error = true;
	}
}
