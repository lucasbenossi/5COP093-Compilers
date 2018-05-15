#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

static const int symbols = 128;

class Automato{
private:
	const int states = 22;
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

		for(char c = 'a'; c <= 'z'; c++){
			set_transition(1, c, 2);
			set_transition(2, c, 2);
		}
		for(char c = '0'; c <= '9'; c++){
			set_transition(1, c, 5);
			set_transition(2, c, 2);
			set_transition(6, c, 8);
			set_transition(7, c, 8);
			set_transition(8, c, 8);
		}
		set_transition(1, '+', 3);
		set_transition(1, '-', 4);
		set_transition(6, '+', 7);
		set_transition(6, '-', 7);
		set_transition(5, 'e', 6);
		set_final(2);
		set_final(3);
		set_final(4);
		set_final(5);
		set_final(8);
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
				cout << input.substr(start, last_final_position-start+1) << endl;
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
