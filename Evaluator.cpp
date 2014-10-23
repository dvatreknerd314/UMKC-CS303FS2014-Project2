//Chase Peterson




#include "Evaluator.h"
#include "syntax_checker.h"
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
	
	int rhs, lhs, result;
	char oper;
	stack<int> operands;
	stack<char> operators;

	
	SyntaxChecker check;
	if (check.syntax_check(input) != 0)
	{
		return NULL; //if the input is invalid, don't return anything
	}

	for (int i = 0; i < input.length(); i++) 
	{
		//If it's a number push it on the operand stack
		if (isOperand(input[i]))
		{
			int ia = input[i] - '0';
			operands.push(ia);
		}
		//If it's an operator
		else if (isOperator(input[i]))
		{
			//if there are none, push it onto the stack
			if (operators.empty())
			{
				operators.push(input[i]);
			}
			//if it's precedence is lower or equal to what's on top, process the last one
			else if (precedence(input[i]) <= precedence(operators.top()))
			{
				rhs = operands.top();
				operands.pop();
				lhs = operands.top();
				oper = operators.top();
				operators.pop();
				result = process(lhs, rhs, oper);
				operands.push(result);
				operators.push(input[i]);
			}
			//if it's of higher precedence, push it on to be processed later
			else if (precedence(input[i]) > precedence(operators.top()))
			{
				operators.push(input[i]);
			}
		}
		//it's an opening parenthesis, put it in operator stack
		else if (isOpen(input[i]))
		{
			operators.push(input[i]);
		}
		//It's a closing parenthesis, process until the last opening parenthesis
		else if (isClose(input[i]))
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
