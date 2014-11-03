//Gretchen Gilbreath
//October 25, 2014
//More edits: November 2, 2014
//Project 2
//CS 303 FS 2014 UMKC

#include "Expression.h"
#include "Evaluator.h"


Expression::Expression()
{
	
}

Expression::Expression(std::string inputString)
{
	exprString = inputString;
}

//destructor
Expression::~Expression()
{
}

double Expression::getAnswer()
{
	return answer;
}

//function that allows the user to set the string
void Expression::set(string hString)
{
	exprString = hString;
	answer = evaluate_expression(exprString);
}

string Expression::getString()
{
	return exprString;
}

ostream& operator <<(ostream& os, const Expression& expression)
{
	for (int i = 0; i < expression.exprString.size(); i++)
	{
		if (expression.exprString[i] != ' ')
			os << i;
	}
	return os;
}

istream& operator>>(istream& is, Expression mExpression)
{
	is >> mExpression.exprString;

	mExpression.answer = evaluate_expression(mExpression.exprString);

	return is;
}

Expression Expression::operator= (Expression& rhs)
{
	Expression tempExp;
	tempExp.exprString = rhs.exprString;
	tempExp.answer = evaluate_expression(exprString);
	return tempExp;
}
