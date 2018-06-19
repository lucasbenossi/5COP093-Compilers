#ifndef SINTATICO_HPP
#define SINTATICO_HPP

#include <iostream>
#include <vector>
#include <stack>

#include "symbol.hpp"

using namespace std;

class Parser{
private:
	vector<Symbol> *table[NON_TERMINALS][TERMINALS];
	string input;
	void set_production(Symbol non_terminal, Symbol terminal, vector<Symbol> next);
	vector<Symbol> *get_production(Symbol non_terminal, Symbol terminal);
	void set_productions();
	string get_string_token(Symbol token);
	string get_string_esperado(Symbol s);
public:
	Parser(string input);
	~Parser();
	void parse();
};

#endif
