#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

static const int symbols = 128;

class Automato{
private:
	const int states = 13;
	int *edges[symbols];
	bool *finals;
	string *return_strings;
	void set_transition(int state, char symbol, int next){
		this->edges[(int)symbol][state-1] = next;
	}
	void set_final(int state){
		this->finals[state-1] = true;
	}
	void set_string(int state, string return_string){
		this->return_strings[state-1] = return_string;
	}
public:
	Automato(){
		for(int i = 0; i < symbols; i++){
			this->edges[i] = new int[states];
			for(int j = 0; j < states; j++){
				this->edges[i][j] = 0;
			}
		}
		this->finals = new bool[states];
		for(int i = 0; i < states; i++){
			this->finals[i] = false;
		}
		this->return_strings = new string[states];

		for(int c = 0; c <= 127; c++){
			set_transition(1, c, 13);
		}
		for(char c = 'a'; c <= 'z'; c++){
			set_transition(3, c, 4);
			set_transition(4, c, 4);
			set_transition(10, c, 10);
			if(c != 'i'){
				set_transition(1, c, 4);
			}
			if(c != 'f'){
				set_transition(2, c, 4);
			}
		}
		for(char c = '0'; c <= '9'; c++){
			set_transition(2, c, 4);
			set_transition(3, c, 4);
			set_transition(4, c, 4);
			set_transition(1, c, 7);
			set_transition(7, c, 7);
			set_transition(8, c, 8);
			set_transition(5, c, 6);
			set_transition(6, c, 6);
		}
		set_transition(1, 'i', 2);
		set_transition(1, '.', 5);
		set_transition(1, '-', 9);
		for(char c : {'\t', '\n', ' '}){
			set_transition(1, c, 12);
			set_transition(12, c, 12);
		}
		set_transition(7, '.', 8);
		set_transition(9, '-', 10);
		set_transition(10, '\n', 11);

		for(int state : {2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13}){
			set_final(state);
		}

		set_string(2, "ID");
		set_string(3, "IF");
		set_string(4, "ID");
		set_string(5, "error");
		set_string(6, "REAL");
		set_string(7, "NUM");
		set_string(8, "REAL");
		set_string(9, "error");
		set_string(11, "comment");
		set_string(12, "white space");
		set_string(13, "error");
	}
	~Automato(){
		for(int i = 0; i < symbols; i++){
			delete[] this->edges[i];
		}
		delete[] this->finals;
		delete[] this->return_strings;
	}
	int get_transition(int state, char symbol){
		return this->edges[(int)symbol][state-1];
	}
	bool is_final(int state){
		if(state > 0){
			return this->finals[state-1];
		}
		return false;
	}
	string get_state_string(int state){
		return this->return_strings[state-1];
	}
};

int main(){
	Automato automato;

	string input;
	char current;
	while(scanf("%c", &current) != EOF){
		input.append(sizeof(char), current);
	}

	const char *input_c = input.c_str();
	int start = 0;
	int length = input.length()+1; // include null terminator
	int current_state = 1;
	int last_final_state = 0;
	int last_final_position = 0;
	for( int position = 0; position < length; position++ ){
		char symbol = input_c[position];

		current_state = automato.get_transition(current_state, symbol);
		if(automato.is_final(current_state)){
			last_final_state = current_state;
			last_final_position = position;
		}

		if(current_state == 0){
			if(last_final_state != 0){
				if(last_final_state == 11){
					cout << input.substr(start, last_final_position-start) << " ";
				}
				else if(last_final_state == 12){
				}
				else{
					cout << input.substr(start, last_final_position-start+1) << " ";
				}
				cout << automato.get_state_string(last_final_state) << endl;
				start = last_final_position + 1;
			}
			else{
				if(symbol != '\0' && symbol != '\n'){
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
