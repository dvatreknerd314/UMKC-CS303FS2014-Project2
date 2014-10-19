// David Allen
// 10-16-14
// Project 2
// CS 303 FS 2014 UMKC

// Program notes:
// Must evaluate an infix expression for the following operators:
// +	-	*	/	()	^	!	%	>	>=	<	<=	&&	||	==	!=

#include <stdio.h>
#include <iostream>
#include "syntax_checker.h"
#include <string>
using namespace std;

SyntaxChecker::SyntaxChecker() {
	reset_variables();
}

// This function checks to see if an appropriate token exists before a binary operator
bool SyntaxChecker::check_binary_ops(syntax_status& the_status, char the_operator) {
	// If this is the case, we do not have an appropriate value as the left hand side operand for the operator
	if (the_status != DIGIT) {
		// Modify the output to fit the appropriate operator
		string the_output = "";
		switch (the_operator) {
		case '<': // This runs for both < and <= but we don't know which is being handled yet
			the_output = "< or <=";
			break;
		case '>': // This runs for both > and >= but we don't know which is being handled yet
			the_output = "> or >=";
			break;
		case ')': break;
		case '&':
		case '|':
		case '=':
			// This should hopefully prevent the operator ascii values from being added
			the_output = "11";
			the_output[0] = the_operator;
			the_output[1] = the_operator;
			break;
		default:
			the_output = "[";
			the_output[0] = the_operator;
		}
		// This is called to make sure we have a right hand operand or a single number within the parenthesis
		if (the_operator == ')') {
			cout << "No valid expression contained within the parenthesis" << endl;
		}
		else {
			cout << "No valid left hand side argument for the " << the_output << " operator." << endl;
		}
		return 0;
	}
	// We just checked an operator, so we're not constructing a number and have not encountered a space.
	working_on_number = 0;
	space = 0;
	return 1;
}

bool SyntaxChecker::check_number(syntax_status& the_status, bool working) {
	// We've processed a number but we're not adding more digits to the same number, rather working on a separate one
	if (the_status == DIGIT && !working) {
		cout << "Unexpected number or parenthetical value, expected an operator." << endl;
		return 0;
	}
	// We just encountered a number or parenthetical value, so we didn't encounter a space.
	space = 0;
	return 1;
}

// This function will go through all of the_input and check to see if it's a valid expression
int SyntaxChecker::syntax_check(string the_input) {
	// This makes sure all the variables needed for parsing are reset
	reset_variables();
	for (int i = 0; i < the_input.length(); i++) {
		switch (the_input[i]) {
			case '+':
				// Return an error code for invalid LHS for + operator if such is true
				if (!check_binary_ops(the_status, the_input[i])) {return 19;}
				
				// This checks to see if + is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// No problems were caused, set the status
				the_status = PLUS;
				break;
			case '-':
				// This checks to see if - is interrputing &&, ==, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// No problems were caused, set the status
				the_status = MINUS;
				break;
			case '*':
				// Return an error code for invalid LHS for * operator if such is true
				if (!check_binary_ops(the_status, the_input[i])) {return 18;}
				
				// This checks to see if * is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// No problems were caused, set the status
				the_status = MULT;
				break;
			case '/':
				// Return an error code for invalid LHS for / operator if such is true
				if (!check_binary_ops(the_status, the_input[i])) {return 17;}
				
				// This checks to see if / is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// No problems were caused, set the status
				the_status = DIV;
				break;
			case '%':
				// Return an error code for invalid LHS for % operator if such is true
				if (!check_binary_ops(the_status, the_input[i])) {return 16;}
				
				// This checks to see if % is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// No problems were caused, set the status
				the_status = MOD;
				break;
			case '^':
				// Return an error code for invalid LHS for ^ operator if such is true
				if (!check_binary_ops(the_status, the_input[i])) {return 15;}
				// This checks to see if ^ is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// No problems were caused, set the status
				the_status = POWER;
				break;
			case '>':
				// Return an error code for invalid LHS for > operator if such is true
				if (!check_binary_ops(the_status, the_input[i])) {return 14;}
				
				// This checks to see if > is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// No problems were caused, set the status
				the_status = GT;
				break;
			case '<':
				// Return an error code for invalid LHS for < operator if such is true
				if (!check_binary_ops(the_status, the_input[i])) {return 13;}
				
				// This checks to see if < is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// No problems were caused, set the status
				the_status = LT;
				break;
			case '!':
				// This checks to see if ! is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// Reset some flags
				working_on_number = 0;
				space = 0;
				
				// Sets a flag in case this is the start of the != operator
				if (the_status == DIGIT)
					quantity_before_not = 1;
				else
					quantity_before_not = 0;
					
				// No problems up to here, set the status
				the_status = NOT;
				break;
			case '=':
				// Having a space before an equal sign forces the equal sign to start ==.
				if (space) {
					// Return an error code for invalid LHS operand for the == operator if such is true.
					if (!check_binary_ops(the_status, the_input[i])) {return 10;}
					// This lets the function know we have seen a beginning equal sign
					the_status = SINGLEEQ;
				}
				// The next four possibilities check for any operator that ends in =
				// First is the latter half of the == operator
				else if (the_status == SINGLEEQ) {
					the_status = EQ;
				}
				// If we're in the latter half of the != operator
				else if (the_status == NOT) {
					// Make sure we have necessary operands for the != operator
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
				// We've encountered the first &, this is the second to form &&
				if (the_status == SINGLEAND) {
					the_status = AND;
				}
				else {
					// Return an error code for invalid LHS for && operator if such is true
					if (!check_binary_ops(the_status, the_input[i])) {return 9;}
					the_status = SINGLEAND;
				}
				break;
			case '|':
				// We've encountered the first |, this is the second to form ||
				if (the_status == SINGLEOR) {
					the_status = OR;
				}
				else {
					// Return an error code for invalid LHS for || operator if such is true
					if (!check_binary_ops(the_status, the_input[i])) {return 8;}
					the_status = SINGLEOR;
				}
				break;
			case ' ':
				space = 1;
				// This checks to see if a space is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					cout << "Incomplete multi-character operator found." << endl;
					return the_error_code;
				}
				
				// Reset flags for operations that will have been interrupted with a space
				working_on_number = quantity_before_not = 0;
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
				// If we have a number or parenthetical value preceeding this with no operator, generate the error code
				if (!check_number(the_status, working_on_number)) {return 7;}
				else {
				// This checks to see if a number is interrupting ==, &&, or ||
					the_error_code = multichar_token_unfinished(the_status);
					if (the_error_code) {
						cout << "Incomplete multi-character operator found." << endl;
						return the_error_code;
					}
				}
				// Sets a flag indicating this might be part of a multi-digit number
				working_on_number = 1;
				
				// No problems were caused, set the status
				the_status = DIGIT;
				break;
			case '(':
				// If we have a number or parenthetical value preceeding this with no operator, generate the error code
				if (!check_number(the_status, working_on_number)) {return 6;}
				else {
				// This checks to see if ( is interrupting ==, &&, or ||
					the_error_code = multichar_token_unfinished(the_status);
					if (the_error_code) {
						cout << "Incomplete multi-character operator found." << endl;
						return the_error_code;
					}
				}
				// If working_on_number was for some reason not set to 0, do so
				// UNNECCESSARY LINE MAYBE?
				working_on_number = 0;
				
				// Increment the parenthesis count
				paren_count++;
				break;
			case ')':
				// Decrement the parenthesis count
				paren_count--;
				// If there are too many closing parenthesis, error
				if (paren_count < 0) {
					cout << "Too many closing parenthesis." << endl;
					return 4;
				}
				// Return an error code for invalid end of enclosed expression if such is true
				// This will also error if we have an incomplete dual character operator
				if (!check_binary_ops(the_status, the_input[i])) {return 5;}
				break;
			default:
				cout << "Unrecognized token encountered: " << the_input[i] << endl;
				return 3;
		}
	}
	
	// Checks for the very last token of the expression
	
	// We've ended with an operator, inside or outside a closing parenthesis.
	if (the_status != DIGIT && the_status != NONE) {
		cout << "Missing right hand operand." << endl;
		return 2;
	}
	
	// We have more opening parenthesis than closing, so error
	else if (paren_count) {
		cout << "Missing closing parenthesis." << endl;
		return 1;
	}
	return 0;
}

void SyntaxChecker::reset_variables() {
	the_status = NONE;
	quantity_before_not = working_on_number = paren_count = the_error_code = 0;
	space = 1;
}

// This gets the specific error code for each double character operator if such is unfinished
int SyntaxChecker::multichar_token_unfinished(syntax_status& the_status) {
	int error_code = 0;
	if (the_status == SINGLEEQ) { error_code = 12; }
	else if (the_status == SINGLEAND) { error_code = 20; }
	else if (the_status == SINGLEOR) { error_code = 21; }
	return error_code;
}