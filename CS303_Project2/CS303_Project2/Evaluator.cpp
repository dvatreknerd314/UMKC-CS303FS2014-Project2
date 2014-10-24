//Chase Peterson

#include "Evaluator.h"

#include <stack>

//Assuming that none of the operands are more than 1 digit in length...


//October 22nd  right now this does not handle boolean expressions, will be made to


int precedence(string text)
{
	if (text == "LPAREN")
		return 0;

	else if (text == "EQ" || text == "NE")
		return 1;

	else if (text == "AND" || text == "OR")
		return 2;

	else if (text == "GT" || text == "GE" || text == "LT" || text == "LE")
		return 3;

	else if (text == "PLUS" || text == "MINUS")
		return 4;

	else if (text == "MULT" || text == "DIV" || text == "MOD")
		return 5;

	else if (text == "POWER")
		return 6;

	else
		return -1;

}



bool isOperator(string text)
{
	return(text == "PLUS" || text == "MINUS" || text == "MULT" || text == "MOD" || text == "DIV" || text == "POWER"
		|| text == "GT" || text == "LT" || text == "GE" || text == "LE" || text == "NE" || text == "EQ" ||text == "OR" || text == "AND");
}

bool isOpen(string text)
{
	return (text == "LPAREN");
}

bool isClose(string text)
{
	return (text == "RPAREN");
}

int process(int lhs, int rhs, string oper)
{
	if (oper == "PLUS") {
		return lhs + rhs;
	}
	if (oper == "MINUS") {
		return lhs - rhs;
	}
	if (oper == "DIV") {
		return lhs / rhs;
	}
	if (oper == "MULT") {
		return lhs*rhs;
	}
	if (oper == "MOD") {
		return lhs%rhs;
	}
	if (oper == "POWER")
	{
		for (int i = 1; i < rhs; i++)
			lhs = lhs*lhs;
		return lhs;
	}
	if (oper == "GT") {
		return(lhs > rhs);
	}
	if (oper == "LT") {
		return(lhs < rhs);
	}
	if (oper == "LE") {
		return(lhs <= rhs);
	}
	if (oper == "GE") {
		return(lhs >= rhs);
	}
	if (oper == "EQ") {
		return(lhs == rhs);
	}
	if (oper == "NE") {
		return(lhs != rhs);
	}
	if (oper == "AND") {
		return(lhs && rhs);
	}
	if (oper == "OR") {
		return(lhs || rhs);
	}
}

bool isNot(string text) {
	return text == "NOT";
}


int evaluate_expression(string& input)
{
	SyntaxChecker check;
	int rhs, lhs, result;
	string oper;
	stack<int> operands;
	stack<string> operators;

	list<exprToken> expression;
	
	
	if (check.syntax_check(input, expression) != 0)
	{
		return NULL; //if the input is invalid, don't return anything
	}
	

	for (list<exprToken>::iterator itr = expression.begin(); itr != expression.end(); ++itr) 
	{
		//If it's a number push it on the operand stack
		if (itr->isANumber)
		{
			operands.push(itr->number);
			if (isNot(operators.top())) {
				result = !operands.top();
				operands.pop();
				operands.push(result);
			}
		}
		//If it's an operator
		else if (isOperator(itr->toString()))
		{
			//if there are none, push it onto the stack
			if (operators.empty())
			{
				operators.push(itr->toString());
			}
			//if it's precedence is lower or equal to what's on top, process the last one
			else if (precedence(itr->toString()) <= precedence(operators.top()))
			{
				rhs = operands.top();
				operands.pop();
				lhs = operands.top();
				oper = operators.top();
				operators.pop();
				result = process(lhs, rhs, oper);
				operands.push(result);
				operators.push(itr->toString());
			}
			//if it's of higher precedence, push it on to be processed later
			else if (precedence(itr->toString()) > precedence(operators.top()))
			{
				operators.push(itr->toString());
			}
		}
		//it's an opening parenthesis, put it in operator stack
		else if (isOpen(itr->toString()))
		{
			operators.push(itr->toString());
		}
		//It's a closing parenthesis, process until the last opening parenthesis
		else if (isClose(itr->toString()))
		{
			while (!isOpen(operators.top()))
			{
				rhs = operands.top();
				operands.pop();
				lhs = operands.top();
				operands.pop();
				oper = operators.top();
				operators.pop();
				operands.push(process(lhs, rhs, oper));
			}
			operators.pop(); //dump the last opening parenthesis, we're done with it
			if (isNot(itr->toString())) {
				result = !operands.top();
				operands.pop();
				operands.push(result);
			}
		}
		else if (isNot(itr->toString()))
		{
			operators.push(itr->toString());
		}

	}

	while(!operators.empty())
	{
		rhs = operands.top();
		operands.pop();
		lhs = operands.top();
		operands.pop();
		oper = operators.top();
		operators.pop();
		operands.push(process(lhs, rhs, oper));
	}
	return operands.top();


}
