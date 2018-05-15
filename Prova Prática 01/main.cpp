#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

const int STATES = 10;
const int SYMBOLS = 256;
const int INVALID = -1;
const int START = 0;

string nl(){
    static int first = true;
    if(first){
        first = false;
        return "";
    }
    return "\n";
}

class Automato{
private:
    int edges[STATES][SYMBOLS];
    bool finals[STATES];
    string strings[STATES];

    void set_transition(int state, char symbol, int next){
        this->edges[state][(int)symbol] = next;
    }
    void set_final(int state){
        this->finals[state] = true;
    }
    void set_string(int state, string s){
        this->strings[state] = s;
    }
    void inicializa(){
        for(int i = 0; i < STATES; i++){
            for(int j = 0; j < SYMBOLS; j++){
                this->edges[i][j] = INVALID;
            }
            this->finals[i] = false;
        }
    }
public:
    Automato(){
        inicializa();

        for(char c = '0'; c <= '9'; c++){
            set_transition(1, c, 3);
            set_transition(2, c, 3);
            set_transition(3, c, 3);
            set_transition(0, c, 4);
            set_transition(4, c, 4);
            set_transition(5, c, 5);
            set_transition(7, c, 8);
            set_transition(8, c, 9);
            set_transition(9, c, 9);
        }
        set_transition(0, 'i', 1);
        set_transition(1, 'f', 2);
        for(char c = 'a'; c <= 'z'; c++){
            if(c != 'f'){
                set_transition(1, c, 3);
            }
            if(c != 'i'){
                set_transition(0, c, 3);
            }
            set_transition(2, c, 3);
            set_transition(3, c, 3);
        }
        set_transition(0, ' ' , 6);
        set_transition(0, '\t', 6);
        set_transition(4, '.', 5);
        set_transition(4, 'e', 7);
        set_transition(7, '+', 8);
        set_transition(7, '-', 8);

        set_final(1); set_string(1, "ID");
        set_final(2); set_string(2, "IF");
        set_final(3); set_string(3, "ID");
        set_final(4); set_string(4, "NUM");
        set_final(5); set_string(5, "REAL");
        set_final(6); set_string(6, "WHITE SPACE");
        set_final(9); set_string(9, "REAL");
    }
    int get_transition(int state, char symbol){
        if(state != INVALID){
            return this->edges[state][(int)symbol];
        }
        return INVALID;
    }
    bool is_final(int state){
        if(state != INVALID){
            return this->finals[state];
        }
        return false;
    }
    string get_string(int state){
        if(state != INVALID){
            return this->strings[state];
        }
        return "";
    }
};

int main() {
    Automato automato;
    string input;
    for( int c = fgetc(stdin); c != EOF; c = fgetc(stdin) ){
        input.append(sizeof(char), c);
    }

    int start = 0;
    int lenght = input.length();
    int current_state = START;
    int last_final_state = INVALID;
    int last_final_position;
    for( int position = 0; position <= lenght; position++ ){ //include null terminator
        char symbol = input.data()[position];

        current_state = automato.get_transition(current_state, symbol);
        if(automato.is_final(current_state)){
            last_final_state = current_state;
            last_final_position = position;
        }

        if(current_state == INVALID){
            if(last_final_state != INVALID){
                cout << nl() << automato.get_string(last_final_state);

                start = last_final_position + 1;
            }
            else{
                char c = input.data()[start];
                if( c != '\n' && c != '\0' && c != ' ' ){
                    cout << nl() << "ERRO";
                }

                start++;
            }

            position = start - 1;
            current_state = START;
            last_final_state = INVALID;
        }
    }

    return 0;
}