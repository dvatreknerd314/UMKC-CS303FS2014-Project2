//Chase Peterson

#include "Evaluator.h"
#include <math.h>
#include <stack>

//The following assumes that syntax_checker will handle all syntax checking.


//precedence takes a token and returns it's precendence level
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


//This will return if the operator in question is a +, -, *, %, /, ^, >, <, >=, <=, !=, ==, ||, or &&
bool isOperator(syntax_status text)
{
	return(text == PLUS || text == MINUS || text == MULT || text == MOD || text == DIV || text == POWER
		|| text == GT || text == LT || text == GE || text == LE || text == NE || text == EQ || text == OR || text == AND);
}

//This returns true if the operator is a "("
bool isOpen(syntax_status text)
{
	return (text == LPAREN);
}

//This returns true if the operator is a ")"
bool isClose(syntax_status text)
{
	return (text == RPAREN);
}

//This processes a an operator with a rhs and lhs argument
int process(double lhs, double rhs, syntax_status oper)
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
		return (int)lhs%(int)rhs;
	}
	if (oper == POWER)
	{
		return pow(lhs, rhs);
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

//Is the character "!"
bool isNot(syntax_status text) {
	return text == NOT;
}

//Is the character "-" but not for a minus operator
bool isNegative(syntax_status token) {
	return token == NEG;
}

//This covers both isNegative and isNot
bool isUnary(syntax_status token) {
	return isNot(token) || isNegative(token);
}

//Takes an expression in a string and evalutates in, boolean or arithmentic
double evaluate_expression(string& input)
{
	SyntaxChecker check; //Here's our checker object
	double rhs, lhs, result; //Some doubles we will need
	syntax_status oper; //this is for passing into the function process
	stack<double> operands; //Operand stack
	stack<syntax_status> operators; //Operator stack

	list<exprToken> expression; //Here's the list we need to pass into syntax_check

	//Here we pass in the expression to see if it passes the test
	if (check.syntax_check(input, expression) != 0) //this also populates the list of tokens
	{
		return numeric_limits<double>::quiet_NaN(); //if the input is invalid, return NaN
	}

	//Iterate through the list of tokens
	for (list<exprToken>::iterator itr = expression.begin(); itr != expression.end(); ++itr)
	{
		//If it's a number push it on the operand stack
		if (itr->isANumber)
		{
			operands.push(itr->number);
			//If there is a negative or not on top of the stack, process it now
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
			
			//Now if there is a ! or - on top of the operator stack we need to evaluate it
			//for the expression that was inside the parenthesis
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
		//If we have a - or ! we need to put it in the operand stack regardless of any precedence
		else if (isUnary(itr->token))
		{
			operators.push(itr->token);
		}

	}
	//After we finish going through the list, we need to evaluate any remaining operators
	while (!operators.empty())
	{
		rhs = operands.top();
		operands.pop();
		lhs = operands.top();
		operands.pop();
		oper = operators.top();
		operators.pop();
		operands.push(process(lhs, rhs, oper));
	}
	//The top of the operand stack is the solution
	return operands.top();


}
