#include "lexico.hpp"
using namespace std;

void Automato::set_transition(int state, char c, int next){
	this->edges[state][(int)c] = next;
}
void Automato::set_final(int state){
	this->finals[state] = true;
}
void Automato::set_symbol(int state, Symbol symbol){
	this->tokens[state] = symbol;
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
Symbol Automato::get_symbol(int state){
	if(state >= START){
		return this->tokens[state];
	}
	return INVALIDO;
}
void Automato::set_reset(){
	this->reset = this->start < this->length && is_nl(this->start);
}
bool Automato::is_nl(char c){
	return c == '\n';
}
bool Automato::is_nl(int position){
	return input.data()[position] == '\n';
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
	this->start = 0;
	this->lin = 1;
	this->col = 1;
	set_reset();

	set_transitions();
}
Token Automato::get_token(){
	int current_state = START;
	int last_final_state = INVALID;
	int last_final_position = 0;
	int last_final_lin = 0;
	int last_final_col = 0;
	Token token;
	int lin = this->lin;
	int col = this->col;
	bool reset = this->reset;
	for(int position = this->start; position <= this->length; position++){
		char symbol = tolower(input.data()[position]);
		reset = is_nl(symbol);
		current_state = get_transition(current_state, symbol);
		if(is_final(current_state)){
			last_final_state = current_state;
			last_final_position = position;
			last_final_lin = lin;
			last_final_col = col;
		}
		if(current_state == INVALID){
			if(last_final_state != INVALID){
				token.symbol = get_symbol(last_final_state);
				token.string = this->input.substr(this->start, last_final_position-this->start+1);
				token.lin = this->lin;
				token.col = this->col;
				this->start = last_final_position + 1;
				if(is_nl(last_final_position)){
					this->lin = last_final_lin + 1;
					this->col = 1;
				}
				else{
					this->lin = last_final_lin;
					this->col = last_final_col + 1;
				}
				set_reset();
				break;
			}
			else{
				int start = this->start;
				int lin = this->lin;
				int col = this->col;
				this->start++;
				if(this->reset){
					this->lin++;
					this->col = 1;
				}
				else{
					this->col++;
				}
				set_reset();
				char c = this->input.data()[start];
				if(c != '\n' && c != ' ' && c != '\0'){
					token.symbol = INVALIDO;
					token.string = this->input.substr(start, position-start+1);
					token.lin = lin;
					token.col = col;
					break;
				}
				current_state = START;
				last_final_state = INVALID;
			}
		}
		if(reset){
			lin++;
			col = 1;
		}
		else{
			col++;
		}
	}
	return token;
}
