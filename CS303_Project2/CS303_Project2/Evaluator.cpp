//Chase Peterson

#include "Evaluator.h"

#include <stack>

//Assuming that none of the operands are more than 1 digit in length...


//October 22nd  right now this does not handle boolean expressions, will be made to


int precedence(syntax_status token)
{
	if (token == LPAREN)
		return 0;

	else if (token == EQ || token == NE)
		return 1;

	else if (token == AND || token == OR)
		return 2;

	else if (token == GT || token == GE || token == LT || token == LE)
		return 3;

	else if (token == PLUS || token == MINUS)
		return 4;

	else if (token == MULT || token == DIV || token == MOD)
		return 5;

	else if (token == POWER)
		return 6;

	else
		return -1;

}



bool isOperator(syntax_status text)
{
	return(text == PLUS || text == MINUS || text == MULT || text == MOD || text == DIV || text == POWER
		|| text == GT || text == LT || text == GE || text == LE || text == NE || text == EQ ||text == OR || text == AND);
}

bool isOpen(syntax_status text)
{
	return (text == LPAREN);
}

bool isClose(syntax_status text)
{
	return (text == RPAREN);
}

int process(int lhs, int rhs, syntax_status oper)
{
	if (oper == PLUS) {
		return lhs + rhs;
	}
	if (oper == MINUS) {
		return lhs - rhs;
	}
	if (oper == DIV) {
		return lhs / rhs;
	}
	if (oper == MULT) {
		return lhs*rhs;
	}
	if (oper == MOD) {
		return lhs%rhs;
	}
	if (oper == POWER)
	{
		int the_result = lhs;
		bool neg = 0;
		int exp = rhs;
		if (rhs < 0)
		{
			neg = 1;
			exp = -rhs;
		}

		for (int i = 1; i < exp; i++)
			the_result = the_result*lhs;

		if (!rhs)
			the_result = 1;
		else if (neg)
		{
			the_result = 1 / the_result;
		}
		return the_result;
	}
	if (oper == GT) {
		return(lhs > rhs);
	}
	if (oper == LT) {
		return(lhs < rhs);
	}
	if (oper == LE) {
		return(lhs <= rhs);
	}
	if (oper == GE) {
		return(lhs >= rhs);
	}
	if (oper == EQ) {
		return(lhs == rhs);
	}
	if (oper == NE) {
		return(lhs != rhs);
	}
	if (oper == AND) {
		return(lhs && rhs);
	}
	if (oper == OR) {
		return(lhs || rhs);
	}
}

bool isNot(syntax_status text) {
	return text == NOT;
}

bool isNegative(syntax_status token) {
	return token == NEG;
}

bool isUnary(syntax_status token) {
	return isNot(token) || isNegative(token);
}

int evaluate_expression(string& input)
{
	SyntaxChecker check;
	int rhs, lhs, result;
	syntax_status oper;
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
		if (itr->isANumber)
		{
			operands.push(itr->number);
			while (!operators.empty() && isUnary(operators.top()))
			{
				if (isNot(operators.top()))
					result = !operands.top();
				else if (isNegative(operators.top()))
					result = -operands.top();
				operands.pop();
				operators.pop();
				operands.push(result);
			}
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
				operands.pop();
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
			while (!operators.empty() && isUnary(operators.top()))
			{ 
				if (isNot(operators.top()))
					result = !operands.top();
				else if (isNegative(operators.top()))
					result = -operands.top();
				operands.pop();
				operators.pop();
				operands.push(result);
			}
		}
		else if (isUnary(itr->token))
		{
			operators.push(itr->token);
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
