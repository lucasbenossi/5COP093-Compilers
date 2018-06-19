#ifndef LEXICO_HPP
#define LEXICO_HPP
#include "symbols.hpp"

static const int SYMBOLS = 256;
static const int STATES = 7;
static const int START = 0;
static const int INVALID = -1;

class Automato{
private:
	int edges[STATES][SYMBOLS];
	bool finals[STATES];
	Symbol tokens[STATES];
	string input;
	int length;
	int start = 0;
	string token_string;

	void set_transition(int state, char c, int next);
	void set_final(int state);
	void set_token(int state, Symbol token);
	int get_transition(int state, char c);
	bool is_final(int state);
	Symbol get_token(int state);

public:
	Automato(string input);
	Symbol get_token();
	string get_token_string();
};

#endif
