//Chase Peterson

#include "Evaluator.h"

#include <stack>

//Assuming that none of the operands are more than 1 digit in length...


//October 22nd  right now this does not handle boolean expressions, will be made to


int precedence(char text)
{
	if (text == '(')
		return 0;

	if (text == '+' || text == '-')
		return 4;

	else if (text == '*' || text == '/' || text == '%')
		return 5;

	else if (text == '^')
		return 6;

	else
		return -1;

}


bool isOperand(char text)
{
	return(text == '0' || text == '1' || text == '2' || text == '3' || text == '4' || text == '5' || text == '6' || text == '7' || text == '8' || text == '9');
}

bool isOperator(char text)
{
	return(text == '+' || text == '-' || text == '*' || text == '%' || text == '/' || text == '^');
}

bool isOpen(char text)
{
	return (text == '(');
}

bool isClose(char text)
{
	return (text == ')');
}

int process(int lhs, int rhs, char oper)
{
	if (oper == '+') {
		return lhs + rhs;
	}
	if (oper == '-') {
		return lhs - rhs;
	}
	if (oper == '/') {
		return lhs / rhs;
	}
	if (oper == '*') {
		return lhs*rhs;
	}
	if (oper == '%') {
		return lhs%rhs;
	}
	if (oper == '^')
	{
		for (int i = 1; i < rhs; i++)
			lhs = lhs*lhs;

		return lhs;
	}

}


int evaluate_expression(string& input)
{
	SyntaxChecker check;
	int rhs, lhs, result;
	char oper;
	stack<int> operands;
	stack<syntax_status> operators;

	list<exprToken> expression;
	
	
	if (check.syntax_check(input, expression) != 0)
	{
		return NULL; //if the input is invalid, don't return anything
	}
	

	for (list<exprToken>::iterator itr = expression.begin(); itr != expression.end(); ++itr) 
	{
		//If it's a number push it on the operand stack
		if (isOperand(itr->number))
		{
			operands.push(itr->token);
		}
		//If it's an operator
		else if (isOperator(itr->token))
		{
			//if there are none, push it onto the stack
			if (operators.empty())
			{
				operators.push(itr->token);
			}
			//if it's precedence is lower or equal to what's on top, process the last one
			else if (precedence(itr->token) <= precedence(operators.top()))
			{
				rhs = operands.top();
				operands.pop();
				lhs = operands.top();
				oper = operators.top();
				operators.pop();
				result = process(lhs, rhs, oper);
				operands.push(result);
				operators.push(itr->token);
			}
			//if it's of higher precedence, push it on to be processed later
			else if (precedence(itr->token) > precedence(operators.top()))
			{
				operators.push(itr->token);
			}
		}
		//it's an opening parenthesis, put it in operator stack
		else if (isOpen(itr->token))
		{
			operators.push(itr->token);
		}
		//It's a closing parenthesis, process until the last opening parenthesis
		else if (isClose(itr->token))
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
