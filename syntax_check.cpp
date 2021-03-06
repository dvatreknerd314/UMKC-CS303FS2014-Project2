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
#include <list>
#include <iomanip>
using namespace std;

SyntaxChecker::SyntaxChecker() {
	reset_variables();
}

// This function checks to see if an appropriate token exists before a binary operator
bool SyntaxChecker::check_binary_ops(syntax_status& the_status) {
	// If this is the case, we do not have an appropriate value as the left hand side operand for the operator
	if (the_status != DIGIT) {
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
		return 0;
	}
	// We just encountered a number or parenthetical value, so we didn't encounter a space.
	space = 0;
	return 1;
}

// This is designed for testing whether syntax_check's error codes are right
int SyntaxChecker::syntax_check(string the_input) { 
	list<exprToken> aList;
	return syntax_check(the_input, aList);
}

// This function will go through all of the_input and check to see if it's a valid expression
int SyntaxChecker::syntax_check(string the_input, list<exprToken>& theList) {
	// Temporary exprToken for adding to theList
	exprToken tempToken;
	// This makes sure all the variables needed for parsing are reset
	reset_variables();
	// Traverse the entire expression
	for (int i = 0; i < the_input.length(); i++) {
		switch (the_input[i]) {
			case '+':
				// Return an error code for invalid LHS for + operator if such is true
				if (!check_binary_ops(the_status)) {
					return return_error(i, the_input, the_input[i], 19);
				}
				
				// This checks to see if + is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}
				
				// No problems were caused
				
				
				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}

				// Set the_status
				the_status = PLUS;
				break;





			case '-':
				// This checks to see if - is interrputing &&, ==, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}

				if (the_status == NONE)
					the_status = NEG;
				// If we interrupted a number, add its exprToken to theList
				// This means - is a binary operator in this instance
				else if (the_status == DIGIT)
				{
					if (currentNum >= 0)
					{
						tempToken.isANumber = true;
						tempToken.number = currentNum;
						currentNum = -1;
						theList.push_back(tempToken);
					}
					the_status = MINUS;
				}
				else
				{
					if (the_status != NONE && ((!theList.back().isANumber && theList.back().token != LPAREN) || theList.back().isANumber) )
					{
						tempToken.isANumber = false;
						tempToken.token = the_status;
						theList.push_back(tempToken);
					}
					the_status = NEG;
				}
				// Check to see if we just completed an operator
				// This means - is a unary operator in this instance
				
				// No problems were caused, set the status
				working_on_number = 0;
				space = 0;
				break;





			case '*':
				// Return an error code for invalid LHS for * operator if such is true
				if (!check_binary_ops(the_status)) {
					return return_error(i, the_input, the_input[i], 18);
				}
				
				// This checks to see if * is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}
				
				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}
				
				// No problems were caused, set the status
				the_status = MULT;
				break;





			case '/':
				// Return an error code for invalid LHS for / operator if such is true
				if (!check_binary_ops(the_status)) {
					return return_error(i, the_input, the_input[i], 17);
				}
				
				// This checks to see if / is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}
				
				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}
				
				// Set the status
				the_status = DIV;
				break;





			case '%':
				// Return an error code for invalid LHS for % operator if such is true
				if (!check_binary_ops(the_status)) {
					return return_error(i, the_input, the_input[i], 16);
				}
				
				// This checks to see if % is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}
				
				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}
				
				// Set the status
				the_status = MOD;
				break;





			case '^':
				// Return an error code for invalid LHS for ^ operator if such is true
				if (!check_binary_ops(the_status)) {
					return return_error(i, the_input, the_input[i], 15);
				}
				// This checks to see if ^ is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}
				
				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}
				
				// Set the status
				the_status = POWER;
				break;





			case '>':
				// Return an error code for invalid LHS for > operator if such is true
				if (!check_binary_ops(the_status)) {
					return return_error(i, the_input, the_input[i], 14);
				}
				
				// This checks to see if > is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}
				
				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}
				
				// Set the status
				the_status = GT;
				break;





			case '<':
				// Return an error code for invalid LHS for < operator if such is true
				if (!check_binary_ops(the_status)) {
					return return_error(i, the_input, the_input[i], 13);
				}
				
				// This checks to see if < is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}
				
				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}
				
				// Set the status
				the_status = LT;
				break;





			case '!':
				// This checks to see if ! is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}
				
				// Reset some flags
				working_on_number = 0;
				space = 0;
				
				// Sets a flag in case this is the start of the != operator
				if (the_status == DIGIT)
					quantity_before_not = 1;
				else
					quantity_before_not = 0;

				// If we interrupted a number, add its exprToken to theList
				// This makes ! the beginning of !=
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}
				/* Otherwise, add the previous operator's token to theList if there was
				   a previously unadded operator */
				else if (the_status != NONE && the_status != DIGIT && the_input[i - 1] != '(')
				{
					tempToken.isANumber = false;
					tempToken.token = the_status;
					theList.push_back(tempToken);
				}
					
				// No problems up to here, set the status
				the_status = NOT;
				break;





			case '=':
				// Having a space before an equal sign forces the equal sign to start ==.
				if (space) {
					// Return an error code for invalid LHS operand for the == operator if such is true.
					if (!check_binary_ops(the_status)) {
						return return_error(i, the_input, the_input[i], 10);
					}
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
						return return_error(i, the_input, NULL, 11);
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
				else if (check_binary_ops(the_status)) {
					// If we interrupted a number, add its exprToken to theList
					if (currentNum >= 0) // No right parenthesis before this
					{
						tempToken.isANumber = true;
						tempToken.number = currentNum;
						currentNum = -1;
						theList.push_back(tempToken);
					}
					// Set the status
					the_status = SINGLEEQ;
				}
				else {
					return return_error(i, the_input, the_input[i], 10);
				}
				space = 0;
				break;





			case '&':
				// We've encountered the first &, this is the second to form &&
				if (the_status == SINGLEAND) {
					the_status = AND;
				}
				else {
					// Return an error code for invalid LHS for && operator if such is true
					if (!check_binary_ops(the_status)) {
						return return_error(i, the_input, the_input[i], 9);
					}
					// If we interrupted a number, add its exprToken to theList
					if (currentNum >= 0) // No right parenthesis before this
					{
						tempToken.isANumber = true;
						tempToken.number = currentNum;
						currentNum = -1;
						theList.push_back(tempToken);
					}
					// Set the status
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
					if (!check_binary_ops(the_status)) {
						return return_error(i, the_input, the_input[i], 8);
					}
					// If we interrupted a number, add its exprToken to theList
					if (currentNum >= 0) // No right parenthesis before this
					{
						tempToken.isANumber = true;
						tempToken.number = currentNum;
						currentNum = -1;
						theList.push_back(tempToken);
					}
					// Set the status
					the_status = SINGLEOR;
				}
				break;





			case ' ':
				space = 1;
				// This checks to see if a space is interrupting ==, &&, or ||
				the_error_code = multichar_token_unfinished(the_status);
				if (the_error_code) {
					return return_error(i, the_input, NULL, the_error_code);
				}

				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
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
				if (!check_number(the_status, working_on_number)) {
					return return_error(i, the_input, NULL, 7);
				}
				else {
				// This checks to see if a number is interrupting ==, &&, or ||
					the_error_code = multichar_token_unfinished(the_status);
					if (the_error_code) {
						return return_error(i, the_input, NULL, the_error_code);
					}
				}

				// If we haven't added a previous operator to theList, do so
				if (the_status != NONE && !working_on_number && the_input[i-1] != '(')
				{
					tempToken.isANumber = false;
					tempToken.token = the_status;
					theList.push_back(tempToken);
				}

				// Sets a flag indicating this might be part of a multi-digit number
				working_on_number = 1;
				
				// Set the current number to either 10*current + new digit or new digit if we haven't encountered a digit yet.
				currentNum = (10 * currentNum * (currentNum >= 0)) + (the_input[i] - 48);

				// No problems were caused, set the status
				the_status = DIGIT;
				break;





			case '(':
				// If we have a number or parenthetical value preceeding this with no operator, generate the error code
				if (!check_number(the_status, working_on_number)) {
					return return_error(i, the_input, NULL, 6);
				}
				else {
				// This checks to see if ( is interrupting ==, &&, or ||
					the_error_code = multichar_token_unfinished(the_status);
					if (the_error_code) {
						return return_error(i, the_input, NULL, the_error_code);
					}
				}
				// If working_on_number was for some reason not set to 0, do so
				// UNNECCESSARY LINE MAYBE?
				working_on_number = 0;
				// If we're not starting the expression, we're definitely ending an operator,
				// so add the operator to theList
				if (the_status != NONE)
				{
					tempToken.isANumber = false;
					tempToken.token = the_status;
					theList.push_back(tempToken);
				}

				// Add the opening parenthesis to theList
				tempToken.isANumber = false;
				tempToken.token = LPAREN;
				theList.push_back(tempToken);

				// Increment the parenthesis count
				paren_count++;
				break;





			case ')':
				// Decrement the parenthesis count
				paren_count--;
				// If there are too many closing parenthesis, error
				if (paren_count < 0) {
					return return_error(i, the_input, '3', 4);
				}
				// Return an error code for invalid end of enclosed expression if such is true
				// This will also error if we have an incomplete dual character operator
				if (!check_binary_ops(the_status)) {
					return return_error(i, the_input, the_input[i], 5);
				}
				
				// If we interrupted a number, add its exprToken to theList
				if (currentNum >= 0) // No right parenthesis before this
				{
					tempToken.isANumber = true;
					tempToken.number = currentNum;
					currentNum = -1;
					theList.push_back(tempToken);
				}
				
				// Add the closing parenthesis to the list
				tempToken.isANumber = false;
				tempToken.token = RPAREN;
				theList.push_back(tempToken);
				break;
			default:
				return return_error(i, the_input, '3', 3);
		}
	}
	
	// Checks for the very last token of the expression
	
	// We've ended with an operator, inside or outside a closing parenthesis.
	if (the_status != DIGIT && the_status != NONE) {
		return return_error(the_input.length()-1, the_input, NULL, 2);
	}
	
	// We have more opening parenthesis than closing, so error
	else if (paren_count) { return return_error(the_input.length()-1, the_input, NULL, 1); }

	// If our last token was a number and not a closing parenthesis, add the
	// number to theList
	if (currentNum >= 0) // No right parenthesis before this
	{
		tempToken.isANumber = true;
		tempToken.number = currentNum;
		currentNum = -1;
		theList.push_back(tempToken);
	}

	return 0;
}

void SyntaxChecker::reset_variables() {
	the_status = NONE;
	quantity_before_not = working_on_number = paren_count = the_error_code = 0;
	space = 1;
	currentNum = -1;
}

// This gets the specific error code for each double character operator if such is unfinished
int SyntaxChecker::multichar_token_unfinished(syntax_status& the_status) {
	int error_code = 0;
	if (the_status == SINGLEEQ) { error_code = 12; }
	else if (the_status == SINGLEAND) { error_code = 20; }
	else if (the_status == SINGLEOR) { error_code = 21; }
	return error_code;
}

int SyntaxChecker::return_error(int index, string expression, char token, int force_code) {
	int error_code = 0;

	cout << setw(4) << "";
	cout << left << setw(10) << "Error: ";
	
	error_code = force_code;
	switch (force_code) {
		case 1:
			cout << "Missing closing parenthesis at index " << index << endl;
			break;
		case 2:
			cout << "Missing right-hand operand at index " << index << endl;
			break;
		case 3:
			cout << "Unrecognized token encountered at index " << index << endl;
			break;
		case 4:
			cout << "Too many closing parenthesis at index " << index << endl;
			break;
		default:
		case 12:
		case 21:
		case 20:
			cout << "Incomplete multi-character operator found at index " << index << endl;
			break;
		case 11:
			cout << "No valid left hand side operand for the != operator" << endl << setw(4) << "" << left << setw(10) << "" << "at character " << index << endl;
			break;
		case 6:
		case 7:
			cout << "Unexpected number or parenthetical value" << endl << setw(14) << "" << "at character " << index << ", expected an operator" << endl;
			break;
		case 5:
			cout << "No valid expression contained within the parenthesis" << endl << setw(14) << "" << "ending at character " << index << endl;
			break;
		case 8:
		case 9:
		case 10:
			cout << "No valid left hand side operator for the " << token << token << " operator" << endl << setw(14) << "" << "at character " << index << endl;
			break;
		case 13:
		case 14:
			cout << "No valid left hand side operator for the " << token << " or " << token << "= operator" << endl << setw(14) << "" << "at character " << index << endl;
			break;
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			cout << "No valid left hand side operator for the " << token << " operator at character " << index << endl;
			break;
	}
	cout << setw(4) << "";
	cout << left << setw(10) << "Input: ";
	cout << expression << endl;

	cout << setw(4) << "";
	cout << left << setw(10) << "Location: ";
	for (int i = 0; i < index; i++)
	{
		cout << "_";
	}
	cout << "^" << endl;
	

	return error_code;
}