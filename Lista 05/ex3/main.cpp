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
	static const int states = 10;
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
		set_transition(1, 'a', 8);
		set_transition(1, 'b', 7);
		set_transition(8, 'a', 6);
		set_transition(8, 'b', 9);
		set_transition(9, 'a', 10);
		set_transition(9, 'b', 5);
		set_transition(5, 'a', 6);
		set_transition(5, 'b', 5);
		set_transition(10, 'a', 2);
		set_transition(2, 'b', 3);
		set_transition(3, '4', 4);
		set_transition(4, 'a', 2);

		set_final(4);
		set_final(6);
		set_final(7);
		set_final(8);
		set_final(10);

		set_string(7, "(action 3)");
		set_string(8, "(action 3)");
		set_string(6, "(action 2)");
		set_string(10, "(action 1)");
		set_string(4, "(action 1)");
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
				cout << automato.get_state_string(last_final_state) << " " << input.substr(start, last_final_position-start+1) << endl;

				start = last_final_position + 1;
			}
			else{
				char c = input.data()[start];
				if(c != '\0' && c != ' ' && c != '\n'){
					cout << "ERRO " << input.substr(start, position-start+1) << endl;
					//cout << "ERRO" << endl;
				}
				start++;
			}
			position = start - 1;
			current_state = 1;
			last_final_state = 0;
		}
	}
}
