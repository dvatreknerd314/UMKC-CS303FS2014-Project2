#ifndef SYNTAX_CHECKER_H
#define SYNTAX_CHECKER_H


enum syntax_status {PLUS,MINUS,MULT,DIV,MOD,POWER,NOT,GT,GE,LT,LE,AND,OR,EQ,NE,NONE,DIGIT};

class SyntaxChecker()
{
	public:
		SyntaxChecker();
		bool syntax_check(string the_input);
	
	private:
		syntax_status the_status;
		bool quantity_before_not, quantity_before_equal, space, working_on_number, begin_and, begin_or;
		int paren_count;
	
		bool check_binary_ops(syntax_status& the_status);
		bool check_number(syntax_status& the_status, bool working);
};



#endif 