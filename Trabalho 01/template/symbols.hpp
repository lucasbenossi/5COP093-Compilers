#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <iostream>
using namespace std;

enum Symbol{
	ID, PLUS, MULT, LPAREN, RPAREN, END,
	E, E1, T, T1, F, S,
	VAZIO, INVALIDO
};
const string strings[] = {
	"id", "+", "*", "(", ")", "$",
	"E", "E'", "T", "T'", "F", "S",
	"", "invalido"
};;

bool is_terminal(Symbol s);
bool is_non_terminal(Symbol s);

#endif
