#ifndef CONSTANTS_H
#define CONSTANTS_H

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
// LPAREN: (
// RPAREN: )
// Parenthesis don't affect the token value in the syntax checker but they do in the expression tokenizer

/*
Single character versions of double character operators (==, &&, and ||) are not supported, but the tokens for such
are used to correctly process double character operators and determine if a double character operator has been
prematurely terminated.
*/

enum syntax_status { PLUS, MINUS, MULT, DIV, MOD, POWER, NOT, GT, GE, LT, LE, AND, OR, EQ, NE, NONE, DIGIT, SINGLEEQ, SINGLEAND, SINGLEOR, LPAREN, RPAREN };

#endif