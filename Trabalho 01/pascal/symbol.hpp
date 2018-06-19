#ifndef SYMBOL_HPP
#define SYMBOL_HPP

#include <iostream>
using namespace std;

enum Symbol{
	// terminals
	_LESS_THAN, _LESS_EQUAL, _NOT_EQUAL, _EQUAL, _GREATER_THAN, _GREATER_EQUAL,
	_MINUS, _COMMA, _SEMICOLON, _COLON, _ASSIGN, _DOT, _DOUBLEDOT, _L_PAREN,
	_R_PAREN, _L_SQUARE_BRACKET, _R_SQUARE_BRACKET, _MULTIPLY, _PLUS, _AND,
	_ARRAY, _BEGIN, _DIV, _DO, _ELSE, _END, _FUNCTION, _IF, _NOT, _OF, _OR,
	_PROCEDURE, _PROGRAM, _THEN, _VAR, _WHILE, _ID, _NUM, _COMMENT1, _COMMENT2,
	// non-terminals
	PROGRAMA, BLOCO, A, AA, AAA, X, Y, TIPO, ZZ, ZZZ, B, PARAMFORMAIS, C, CC,
	CCC, VARIAVEL, D, DD, COMANDO, Z, E, EE, EXPRESSAO, F, EXPSIMPLES, G, GG,
	TERMO, H, FATOR, V, VV, CONSTANTE,
	// other
	INVALIDO, VAZIO
};
extern const string strings[];

static const int FIRST_TERMINAL = _LESS_THAN;
static const int LAST_TERMINAL = _COMMENT2;

static const int FIRST_NON_TERMINAL = PROGRAMA;
static const int LAST_NON_TERMINAL = CONSTANTE;

static const int TERMINALS = LAST_TERMINAL - FIRST_TERMINAL + 1;
static const int NON_TERMINALS = LAST_NON_TERMINAL - FIRST_TERMINAL + 1;

bool is_terminal(Symbol s);
bool is_non_terminal(Symbol s);

#endif
