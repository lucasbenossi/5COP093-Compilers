#include "symbol.hpp"
using namespace std;

const string strings[] = {
	// terminals
	"_LESS_THAN", "_LESS_EQUAL", "_NOT_EQUAL", "_EQUAL", "_GREATER_THAN",
	"_GREATER_EQUAL", "_MINUS", "_COMMA", "_SEMICOLON", "_COLON", "_ASSIGN",
	"_DOT", "_DOUBLEDOT", "_L_PAREN", "_R_PAREN", "_L_SQUARE_BRACKET",
	"_R_SQUARE_BRACKET", "_MULTIPLY", "_PLUS", "_AND", "_ARRAY", "_BEGIN",
	"_DIV", "_DO", "_ELSE", "_END", "_FUNCTION", "_IF", "_NOT", "_OF", "_OR",
	"_PROCEDURE", "_PROGRAM", "_THEN", "_VAR", "_WHILE", "_ID", "_NUM",
	"_COMMENT1", "_COMMENT2",
	// non-terminals
	"PROGRAMA", "BLOCO", "A", "AA", "AAA", "X", "Y", "TIPO", "ZZ", "ZZZ", "B",
	"PARAMFORMAIS", "C", "CC", "CCC", "VARIAVEL", "D", "DD", "COMANDO", "Z",
	"E", "EE", "EXPRESSAO", "F", "EXPSIMPLES", "G", "GG", "TERMO", "H", "FATOR",
	"V", "VV", "CONSTANTE",
	// other
	"INVALIDO", "VAZIO"
};

bool is_terminal(Symbol s){
	if(s >= FIRST_TERMINAL && s <= LAST_TERMINAL){
		return true;
	}
	return false;
}
bool is_non_terminal(Symbol s){
	if(s >= FIRST_NON_TERMINAL && s <= LAST_NON_TERMINAL){
		return true;
	}
	return false;
}
