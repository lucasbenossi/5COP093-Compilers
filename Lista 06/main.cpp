#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

static const int symbols = 128;

class Estado{
private:
	int edges[symbols];
	bool is_final_state;
	string return_string;
public:
	Estado(){
		for(int i = 0; i < symbols; i++){
			this->edges[i] = 0;
		}
		this->is_final_state = false;
		this->return_string = "";
	}

	void set_transition(char symbol, int next){
		this->edges[(int)symbol] = next;
	}
	int get_transition(char symbol){
		return this->edges[(int)symbol];
	}

	void set_final(){
		this->is_final_state = true;
	}
	bool is_final(){
		return this->is_final_state;
	}

	void set_string(string return_string){
		this->return_string = return_string;
	}
	string get_string(){
		return this->return_string;
	}
};

class Automato{
private:
	static const int states = 22;
	Estado estados[states];
	void set_transition(int state, char symbol, int next){
		this->estados[state-1].set_transition(symbol, next);
	}
	void set_final(int state){
		this->estados[state-1].set_final();
	}
	void set_string(int state, string return_string){
		this->estados[state-1].set_string(return_string);
	}
public:
	Automato(){
		for(char c = '0'; c <= '9'; c++){
			set_transition(20, c, 22);
			set_transition(21, c, 22);
			set_transition(22, c, 22);
			set_transition( 1, c, 19);
			set_transition(19, c, 19);
		}
		set_transition( 1, '+', 17);
		set_transition( 1, '-', 18);
		set_transition( 1, 'h',  2);
		set_transition( 1, 's',  4);
		set_transition( 1, 'c', 11);
		set_transition(19, 'e', 20);
		set_transition( 2, 'e',  3);
		set_transition( 2, 'i',  7);
		set_transition( 4, 'h',  5);
		set_transition(11, 'a', 12);
		set_transition(20, '+', 21);
		set_transition(20, '-', 21);
		set_transition( 3, 'r',  9);
		set_transition( 7, 's',  8);
		set_transition( 5, 'e',  6);
		set_transition(12, 't', 13);
		set_transition(12, 'r', 14);
		set_transition( 9, 's', 10);
		set_transition(13, 's', 15);
		set_transition(14, 's', 16);

		set_final(17);
		set_final(18);
		set_final(19);
		set_final(3);
		set_final(8);
		set_final(6);
		set_final(13);
		set_final(14);
		set_final(22);
		set_final(10);
		set_final(15);
		set_final(16);

		set_string(17, "MAIS");
		set_string(18, "MENOS");
		set_string(19, "INTEIRO");
		set_string(3, "ELE");
		set_string(8, "DELE");
		set_string(6, "ELA");
		set_string(13, "GATO");
		set_string(14, "CARRO");
		set_string(22, "REAL");
		set_string(10, "DELA");
		set_string(15, "GATOS");
		set_string(16, "CARROS");
	}
	int get_transition(int state, char symbol){
		return this->estados[state-1].get_transition(symbol);
	}
	bool is_final(int state){
		if(state > 0){
			return this->estados[state-1].is_final();
		}
		return false;
	}
	string get_state_string(int state){
		return this->estados[state-1].get_string();
	}
};

int main(){
	Automato automato;

	string input;
	char current;
	while(scanf("%c", &current) != EOF){
		input.append(sizeof(char), current);
	}

	int start = 0;
	int length = input.length();
	int current_state = 1;
	int last_final_state = 0;
	int last_final_position = 0;
	for( int position = 0; position <= length; position++ ){ // include null terminator
		char symbol = input.data()[position];

		current_state = automato.get_transition(current_state, symbol);
		if(automato.is_final(current_state)){
			last_final_state = current_state;
			last_final_position = position;
		}

		if(current_state == 0){
			if(last_final_state != 0){
				cout << automato.get_state_string(last_final_state);
				if( last_final_state == 19 || last_final_state == 22 ){
					cout << " " << input.substr(start, last_final_position-start+1);
				}
				cout << endl;

				start = last_final_position + 1;
			}
			else{
				char c = input.data()[start];
				if(c != '\0' && c != ' ' && c != '\n'){
					//cout << "ERRO " << input.substr(start, position-start+1) << " " << start << " " << position << endl;
					cout << "ERRO" << endl;
				}
				start++;
			}
			position = start - 1;
			current_state = 1;
			last_final_state = 0;
		}
	}
}
