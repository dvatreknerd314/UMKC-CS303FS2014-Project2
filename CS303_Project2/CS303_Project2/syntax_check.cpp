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
			the_output += the_operator + the_operator;
			break;
		default:
			the_output += the_operator;
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
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				the_status = PLUS;
				break;
			case '-':
				the_status = MINUS;
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				break;
			case '*':
				if (!check_binary_ops(the_status, the_input[i])) {return 18;}
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				the_status = MULT;
				break;
			case '/':
				if (!check_binary_ops(the_status, the_input[i])) {return 17;}
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				the_status = DIV;
				working_on_number = 0;
				space = 0;
				break;
			case '%':
				if (!check_binary_ops(the_status, the_input[i])) {return 16;}
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				the_status = MOD;
				working_on_number = 0;
				space = 0;
				break;
			case '^':
				if (!check_binary_ops(the_status, the_input[i])) {return 15;}
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				the_status = POWER;
				working_on_number = 0;
				space = 0;
				break;
			case '>':
				if (!check_binary_ops(the_status, the_input[i])) {return 14;}
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				the_status = GT;
				working_on_number = 0;
				space = 0;
				break;
			case '<':
				if (!check_binary_ops(the_status, the_input[i])) {return 13;}
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				the_status = LT;
				working_on_number = 0;
				space = 0;
				break;
			case '!':
				// This sets a flag that distinguishes the NE operator from the NOT operator
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				working_on_number = 0;
				space = 0;
				if (the_status == DIGIT)
					quantity_before_not = 1;
				else
					quantity_before_not = 0;
				the_status = NOT;
				break;
			case '=':
				// Having a space before an equal sign forces the equal sign to start ==.
				if (space) {
					if (!check_binary_ops(the_status, the_input[i])) {return 10;}
					// This lets the function know we have seen a beginning equal sign
					the_status = SINGLEEQ;
				}
				// The next four possibilities check for any operator that ends in =
				// First is latter half of the == operator
				else if (the_status == SINGLEEQ) {
					the_status = EQ;
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
				// These last two statements make sure operands are present for the == operator if there are no spaces
				else if (check_binary_ops(the_status, the_input[i])) {
					the_status = SINGLEEQ;
				}
				else { return 10; }
				space = 0;
				break;
			case '&':
				if (the_status == SINGLEAND) {
					the_status = AND;
				}
				else {
					if (!check_binary_ops(the_status, the_input[i])) {return 9;}
					the_status = SINGLEAND;
				}
				break;
			case '|':
				if (the_status == SINGLEOR) {
					the_status = OR;
				}
				else {
					if (!check_binary_ops(the_status, the_input[i])) {return 8;}
					the_status = SINGLEOR;
				}
				break;
			case ' ':
				space = 1;
				// Reset all multi-character token flags
				
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
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
				else {
					the_error_code = multichar_token_unfinished(the_status);
					if (the_error_code) {
						cout << "Incomplete multi-character operator found." << endl;
						return the_error_code;
					}
				}
				working_on_number = 1;
				the_status = DIGIT;
				break;
			case '(':
				if (!check_number(the_status, working_on_number)) {return 6;}
				else {
					the_error_code = multichar_token_unfinished(the_status);
					if (the_error_code) {
						cout << "Incomplete multi-character operator found." << endl;
						return the_error_code;
					}
				}
				working_on_number = 0;
				paren_count++;
				break;
			case ')':
				paren_count--;
				if (paren_count < 0) {
					cout << "Too many closing parenthesis." << endl;
					return 4;
				}
				if (!check_binary_ops(the_status, the_input[i])) {return 5;}
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
	quantity_before_not = quantity_before_equal = working_on_number = begin_and = begin_or = paren_count = the_error_code = 0;
	space = 1;
}

int SyntaxChecker::multichar_token_unfinished(syntax_status& the_status) {
	int error_code = 0;
	if (the_status == SINGLEEQ) { error_code = 12; }
	else if (the_status == SINGLEAND) { error_code = 20; }
	else if (the_status == SINGLEOR) { error_code = 21; }
	return error_code;
}