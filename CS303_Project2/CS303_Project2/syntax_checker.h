#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H

#include <string>
using namespace std;

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
// SINGLEEQ: =
// SINGLEAND: &
// SINGLEOR: |
// Parenthesis are not given a status as they are handled differently

/* 
   Single character versions of double character operators (==, &&, and ||) are not supported, but the tokens for such
   are used to correctly process double character operators and determine if a double character operator has been
   prematurely terminated.
*/
enum syntax_status {PLUS,MINUS,MULT,DIV,MOD,POWER,NOT,GT,GE,LT,LE,AND,OR,EQ,NE,NONE,DIGIT,SINGLEEQ, SINGLEAND, SINGLEOR};

class SyntaxChecker
{
	public:
		SyntaxChecker();
		int syntax_check(string the_input);
	
	private:
		syntax_status the_status;
		bool quantity_before_not, space, working_on_number;
		int paren_count, the_error_code;
		
		void reset_variables();
		bool check_binary_ops(syntax_status& the_status, char the_operator);
		bool check_number(syntax_status& the_status, bool working);
		int multichar_token_unfinished(syntax_status& the_status);
};



#endif 