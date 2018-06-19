#include "sintatico.hpp"
#include "lexico.hpp"
#include "nl.hpp"
using namespace std;

void Parser::set_production(Symbol non_terminal, Symbol terminal, vector<Symbol> next){
	this->table[non_terminal-(LAST_TERMINAL+1)][terminal] = new vector<Symbol>(next);
}
vector<Symbol> *Parser::get_production(Symbol non_terminal, Symbol terminal){
	return this->table[non_terminal-(LAST_TERMINAL+1)][terminal];
}
string Parser::get_string_token(Symbol token){
	if(token == VAZIO){
		return " ";
	}
	return " " + strings[token] + " ";
}
string Parser::get_string_esperado(Symbol s){
	bool first = true;
	string esperado;
	if(is_non_terminal(s)){
		for(int i = 0; i < TERMINALS; i++){
			vector<Symbol> *v = get_production(s, (Symbol)i);
			if(v != NULL){
				if(first){
					first = false;
					esperado += " ";
				}
				else{
					esperado += ", ";
				}
				esperado += strings[i];
			}
		}
	}
	else{
		esperado += " " + strings[s];
	}
	return esperado;
}
Parser::Parser(string input){
	this->input = input;
	for(int i = 0; i < NON_TERMINALS; i++){
		for(int j = 0; j < TERMINALS; j++){
			this->table[i][j] = NULL;
		}
	}
	set_productions();
}
Parser::~Parser(){
	for(int i = 0; i < NON_TERMINALS; i++){
		for(int j = 0; j < TERMINALS; j++){
			delete this->table[i][j];
		}
	}
}
void Parser::parse(){
	Automato automato(this->input);
	stack<Symbol> ss;
	ss.push(PROGRAMA);
	Token token = automato.get_token();
	while(!ss.empty()){
		if(token.symbol == INVALIDO){
			cout << "ERRO LEXICO. Linha: " << token.lin << " Coluna: " << token.col << " -> "<< token.string;
			return;
		}
		else if(token.symbol == _COMMENT1 || token.symbol == _COMMENT2){
			token = automato.get_token();
			continue;
		}
		Symbol symbol = ss.top();
		ss.pop();
		if(token.symbol == symbol){
			token = automato.get_token();
		}
		else{
			vector<Symbol> *next = NULL;
			if(is_non_terminal(symbol) && is_terminal(token.symbol)){
				next = get_production(symbol, token.symbol);
			}
			if(next == NULL){
				cout << "ERRO DE SINTAXE. Linha: " << token.lin << " -> \"" << token.string << "\"";
				return;
			}
			for(int i = next->size()-1; i >= 0; i--){
				ss.push(next->at(i));
			}
		}
	}
	cout << "PROGRAMA CORRETO.";
}
