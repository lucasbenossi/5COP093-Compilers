#ifndef SINTATICO_HPP
#define SINTATICO_HPP

#include <iostream>
#include <vector>
#include <stack>

#include "symbols.hpp"
#include "lexico.hpp"
#include "nl.hpp"

using namespace std;

static const int TERMINALS = 6;
static const int NONTERMINALS = 6;

class Parser{
private:
	vector<Symbol> *table[NONTERMINALS][TERMINALS];
	string input;
	void set_production(Symbol non_terminal, Symbol terminal, vector<Symbol> next);
	vector<Symbol> *get_production(Symbol non_terminal, Symbol terminal);
	string get_string_token(Symbol token);
	string get_string_esperado(Symbol s);
public:
	Parser(string input);
	~Parser();
	void parse();
};

#endif
