#include "sintatico.hpp"
using namespace std;

void Parser::set_production(Symbol non_terminal, Symbol terminal, vector<Symbol> next){
	this->table[non_terminal-(END+1)][terminal] = new vector<Symbol>(next);
}
vector<Symbol> *Parser::get_production(Symbol non_terminal, Symbol terminal){
	return this->table[non_terminal-(END+1)][terminal];
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
	for(int i = 0; i < NONTERMINALS; i++){
		for(int j = 0; j < TERMINALS; j++){
			this->table[i][j] = NULL;
		}
	}
	set_production(E, ID, {T, E1});
	set_production(T, ID, {F, T1});
	set_production(F, ID, {ID});
	set_production(S, ID, {E, END});
	set_production(E1, PLUS, {PLUS, T, E1});
	set_production(T1, PLUS, {});
	set_production(T1, MULT, {MULT, F, T1});
	set_production(E, LPAREN, {T, E1});
	set_production(T, LPAREN, {F, T1});
	set_production(F, LPAREN, {LPAREN, E, RPAREN});
	set_production(S, LPAREN, {E, END});
	set_production(E1, RPAREN, {});
	set_production(T1, RPAREN, {});
	set_production(E1, END, {});
	set_production(T1, END, {});
}
Parser::~Parser(){
	for(int i = 0; i < NONTERMINALS; i++){
		for(int j = 0; j < TERMINALS; j++){
			delete this->table[i][j];
		}
	}
}
void Parser::parse(){
	Automato automato(this->input);
	stack<Symbol> ss;
	ss.push(S);
	Symbol token = automato.get_token();
	while(!ss.empty()){
		if(token == INVALIDO){
			cout << nl() << "ERRO LEXICO: " << automato.get_token_string();
			return;
		}
		Symbol symbol = ss.top();
		ss.pop();
		if(token == symbol){
			token = automato.get_token();
		}
		else{
			vector<Symbol> *next = NULL;
			if(is_non_terminal(symbol) && is_terminal(token)){
				next = get_production(symbol, token);
			}
			if(next == NULL){
				cout << nl() << "ERRO SINTATICO EM:" + get_string_token(token) + "ESPERADO:" + get_string_esperado(symbol);
				return;
			}
			for(int i = next->size()-1; i >= 0; i--){
				ss.push(next->at(i));
			}
		}
	}
	cout << nl() << "CADEIA ACEITA";
}
