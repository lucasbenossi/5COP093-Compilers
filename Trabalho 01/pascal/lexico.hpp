#ifndef LEXICO_HPP
#define LEXICO_HPP
#include "symbol.hpp"
#include <iostream>
using namespace std;

static const int SYMBOLS = 128;
static const int STATES = 94;
static const int START = 0;
static const int INVALID = -1;

class Token{
public:
	Symbol symbol = VAZIO;
	std::string string = "";
	int lin = 0;
	int col = 0;
};

class Automato{
private:
	int edges[STATES][SYMBOLS];
	bool finals[STATES];
	Symbol tokens[STATES];
	string input;
	int length;
	int start;
	int lin;
	int col;
	bool reset;

	void set_transition(int state, char c, int next);
	void set_final(int state);
	void set_symbol(int state, Symbol token);
	int get_transition(int state, char c);
	bool is_final(int state);
	Symbol get_symbol(int state);
	void set_reset();
	bool is_nl(char c);
	bool is_nl(int position);
	void set_transitions();
public:
	Automato(string input);
	Token get_token();
};

#endif
