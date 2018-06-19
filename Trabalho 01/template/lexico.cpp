#include "lexico.hpp"
using namespace std;

void Automato::set_transition(int state, char c, int next){
	this->edges[state][(int)c] = next;
}
void Automato::set_final(int state){
	this->finals[state] = true;
}
void Automato::set_token(int state, Symbol token){
	this->tokens[state] = token;
}
int Automato::get_transition(int state, char c){
	if(state >= START){
		return this->edges[state][(int)c];
	}
	return INVALID;
}
bool Automato::is_final(int state){
	if(state >= START){
		return this->finals[state];
	}
	return false;
}
Symbol Automato::get_token(int state){
	if(state >= START){
		return this->tokens[state];
	}
	return INVALIDO;
}
Automato::Automato(string input){
	for(int i = 0; i < STATES; i++){
		for(int j = 0; j < SYMBOLS; j++){
			this->edges[i][j] = INVALID;
		}
		this->finals[i] = false;
		this->tokens[i] = INVALIDO;
	}
	this->input = input;
	this->length = input.length();

	for(char i = 'a'; i <= 'z'; i++){
		set_transition(0, i, 1);
		set_transition(1, i, 1);
	}
	for(char i = '0'; i <= '9'; i++){
		set_transition(1, i, 1);
	}
	set_transition(0, '+', 2);
	set_transition(0, '*', 3);
	set_transition(0, '(', 4);
	set_transition(0, ')', 5);
	set_transition(0, '$', 6);
	for(int i = 1; i <= 6; i++){
		set_final(i);
	}
	set_token(1, ID);
	set_token(2, PLUS);
	set_token(3, MULT);
	set_token(4, LPAREN);
	set_token(5, RPAREN);
	set_token(6, END);
}
Symbol Automato::get_token(){
	int current_state = START;
	int last_final_state = INVALID;
	int last_final_position = 0;
	Symbol token = VAZIO;
	this->token_string = "";
	for(int position = this->start; position <= this->length; position++){
		char symbol = input.data()[position];
		current_state = get_transition(current_state, symbol);
		if(is_final(current_state)){
			last_final_state = current_state;
			last_final_position = position;
		}
		if(current_state == INVALID){
			if(last_final_state != INVALID){
				token = get_token(last_final_state);
				this->token_string = this->input.substr(start, last_final_position-start+1);
				this->start = last_final_position+1;
				break;
			}
			else{
				int start = this->start;
				this->start++;
				char c = this->input.data()[start];
				if(c != '\n' && c != ' ' && c != '\0'){
					token = INVALIDO;
					this->token_string = this->input.substr(start, position-start+1);
					break;
				}
				current_state = START;
				last_final_state = INVALID;
			}
		}
	}
	return token;
}
string Automato::get_token_string(){
	return this->token_string;
}
