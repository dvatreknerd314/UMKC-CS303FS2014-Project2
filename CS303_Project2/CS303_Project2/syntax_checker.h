#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H

#include <string>
#include <list>
#include "Constants.h"
using namespace std;

/* This struct is set up as follows:
  bool isANumber:
  	Tells whether a particular instance of an exprToken should
  	be accessed as an int or a syntax_status
  union:
  	Allows exprToken to work as both an int and a syntax_status
  string toString():
  	Converts the current exprToken into a string.  If anyone
	knows of a way to output the name of an enumerated type
	in C++ please let me know! 
*/
struct exprToken {
	// Should we access this as an int or a syntax_status
	bool isANumber;
	
	union {
		int number;
		syntax_status token;
	};
	
	// Convert to string function
	string toString() {
		if (isANumber)
			return to_string(number);
		else {
			switch (token) {
			case PLUS:	return "PLUS"; break;
			case MINUS: return "MINUS"; break;
			case MULT: return "MULT"; break;
			case DIV: return "DIV"; break;
			case MOD: return "MOD"; break;
			case POWER: return "POWER"; break;
			case NOT: return "NOT"; break;
			case GT: return "GT"; break;
			case LT: return "LT"; break;
			case GE: return "GE"; break;
			case LE: return "LE"; break;
			case EQ: return "EQ"; break;
			case NE: return "NE"; break;
			case AND: return "AND"; break;
			case OR: return "OR"; break;
			case LPAREN: return "LPAREN"; break;
			case RPAREN: return "RPAREN"; break;
				// These should not output
			case DIGIT: return "DIGIT"; break;
			case SINGLEAND: return "SINGLEAND"; break;
			case SINGLEOR: return "SINGLEOR"; break;
			case SINGLEEQ: return "SINGLEEQ"; break;
			case NONE: return "NONE"; break;
			}
		}
	}

};

class SyntaxChecker
{
	public:
		SyntaxChecker();
		int syntax_check(string the_input, list<exprToken>& theList);
		int syntax_check(string the_input);
	
	private:
		syntax_status the_status;
		bool quantity_before_not, space, working_on_number;
		int paren_count, the_error_code, currentNum;
		
		void reset_variables();
		bool check_binary_ops(syntax_status& the_status, char the_operator);
		bool check_number(syntax_status& the_status, bool working);
		int multichar_token_unfinished(syntax_status& the_status);
};


#endif 