// David Allen
// 10-16-14
// Project 2
// CS 303 FS 2014 UMKC

// Program notes:
// Must evaluate an infix expression for the following operators:
// +	-	*	/	()	^	!	%	>	>=	<	<=	&&	||	==	!=

// This variable is used to determine what kind of token we just processed.
// PLUS: +
// MINUS: -
// MULT: *
// DIV: /
// MOD: %
// POWER: ^
// NOT: !
// GT: >
// GE: >=
// LT: <
// LE: <=
// AND: &&
// OR: ||
// EQ: ==
// NE: !=
// NONE: No characters have been processed (initial value)
// DIGIT: 0-9
// Parenthesis are not given a status as they are handled differently

// Binary operators require two values on either side, syntax check will be similar

#include <stdio.h>
#include <iostream>
#include "syntax_checker.h"
using namespace std;

SyntaxChecker::SyntaxChecker() {
	reset_variables();
}

bool SyntaxChecker::check_binary_ops(syntax_status& the_status, char the_operator) {
	if (the_status != DIGIT) {
		string the_output = "";
		switch (the_operator) {
		case '<':
			the_output = "< or <=";
			break;
		case '>':
			the_output = "> or >=";
			break;
		case ')': break;
		case '&':
		case '|':
		case '=':
			the_output = the_operator + the_operator;
			break;
		default:
			the_output = the_operator;
		}
		if (the_operator == ')') {
			cout << "No valid expression contained within the parenthesis" << endl;
		}
		else {
			cout << "No valid left hand side argument for the " << the_output << " operator." << endl;
		}
		return 0;
	}
	working_on_number = 0;
	space = 0;
	return 1;
}

bool SyntaxChecker::check_number(syntax_status& the_status, bool working) {
	if (the_status == DIGIT && !working) {
		cout << "Unexpected number or parenthetical value, expected an operator." << endl;
		return 0;
	}
	space = 0;
	return 1;
}

int SyntaxChecker::syntax_check(string the_input) {
	reset_variables();
	for (int i = 0; i < the_input.length(); i++) {
		switch (the_input[i]) {
			case '+':
				if (!check_binary_ops(the_status, the_input[i])) {return 19;}
				the_status = PLUS;
				break;
			case '-':
				the_status = MINUS;
				break;
			case '*':
				if (!check_binary_ops(the_status, the_input[i])) {return 18;}
				the_status = MULT;
				break;
			case '/':
				if (!check_binary_ops(the_status, the_input[i])) {return 17;}
				the_status = DIV;
				working_on_number = 0;
				space = 0;
				break;
			case '%':
				if (!check_binary_ops(the_status, the_input[i])) {return 16;}
				the_status = MOD;
				working_on_number = 0;
				space = 0;
				break;
			case '^':
				if (!check_binary_ops(the_status, the_input[i])) {return 15;}
				the_status = POWER;
				working_on_number = 0;
				space = 0;
				break;
			case '>':
				if (!check_binary_ops(the_status, the_input[i])) {return 14;}
				the_status = GT;
				working_on_number = 0;
				space = 0;
				break;
			case '<':
				if (!check_binary_ops(the_status, the_input[i])) {return 13;}
				the_status = LT;
				working_on_number = 0;
				space = 0;
				break;
			case '!':
				// This sets a flag that distinguishes the NE operator from the NOT operator
				working_on_number = 0;
				space = 0;
				if (the_status == DIGIT)
					quantity_before_not = 1;
				else
					quantity_before_not = 0;
				the_status = NOT;
				break;
			case '=':
				// If space is true, this begins a binary operator. Otherwise it may end a binary operator.
				if (space) {
					if (!check_binary_ops(the_status, the_input[i])) {return 10;}
					// This lets the function know we have seen a beginning equal sign
					quantity_before_equal = 1;
				}
				// This handles situations in which there are no spaces but we start the == operator
				else if (the_status == DIGIT) {
					quantity_before_equal = 1;
				}
				// If we're in the latter half of the != operator
				else if (the_status == NOT) {
					// Make sure we have necessary operators for the != operator
					if (!quantity_before_not) {
						cout << "No valid left hand side operand for the != operator." << endl;
						return 11;
					}
					else {
						the_status = NE;
					}
				}
				// If we're in the latter half of the >= operator
				else if (the_status == GT) {
					the_status = GE;
				}
				// If we're in the latter half of the <= operator
				else if (the_status == LT) {
					the_status = LE;
				}
				// These last two statements make sure operands are present for the == operator
				else if (quantity_before_equal) {
					the_status = EQ;
					!quantity_before_equal;
				}
				else {
					cout << "Unrecognized token encountered: ===" << endl;
					return 12;
				}
				break;
			case '&':
				if (begin_and) {
					the_status = AND;
					!begin_and;
				}
				else {
					if (!check_binary_ops(the_status, the_input[i])) {return 9;}
					!begin_and;
				}
				break;
			case '|':
				if (begin_or) {
					the_status = OR;
					!begin_or;
				}
				else {
					if (!check_binary_ops(the_status, the_input[i])) {return 8;}
					!begin_or;
				}
				break;
			case ' ':
				space = 1;
				// Reset all multi-character token flags
				working_on_number = quantity_before_not = quantity_before_equal = begin_or = begin_and = 0;
				break;
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (!check_number(the_status, working_on_number)) {return 7;}
				working_on_number = 1;
				the_status = DIGIT;
				break;
			case '(':
				if (!check_number(the_status, working_on_number)) {return 6;}
				working_on_number = 0;
				paren_count++;
				break;
			case ')':
				if (!check_binary_ops(the_status, the_input[i])) {return 5;}
				paren_count--;
				if (paren_count < 0) {
					cout << "Too many closing parenthesis." << endl;
					return 4;
				}
				break;
			default:
				cout << "Unrecognized token encountered: " << the_input[i] << endl;
				return 3;
		}
	}
	if (the_status != DIGIT && the_status != NONE) {
		cout << "Missing right hand operand." << endl;
		return 2;
	}
	else if (paren_count) {
		cout << "Missing closing parenthesis." << endl;
		return 1;
	}
	return 0;
}

void SyntaxChecker::reset_variables() {
	the_status = NONE;
	quantity_before_not = quantity_before_equal = working_on_number = begin_and = begin_or = paren_count = 0;
	space = 1;
}