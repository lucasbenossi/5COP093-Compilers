#include <iostream>
#include <cstring>
#include <stdio.h>
using namespace std;

static const int symbols = 256;
static const int states = 8;

string nl(){
    static bool first = true;
    if(first){
        first = false;
        return "";
    }
    return "\n";
}

class Automato{
private:
    int edges[states][symbols];
    bool finals[states];

    void inicializa(){
        for(int i = 0; i < states; i++){
            for(int j = 0; j < symbols; j++){
                edges[i][j] = 0;
            }
            finals[i] = false;
        }
    }

    void set_transition(int state, char symbol, int next){
        this->edges[state-1][(int)symbol] = next;
    }
    void set_final(int state){
        this->finals[state-1] = true;
    }
public:
    Automato(){
        inicializa();

        for(char i = '0'; i <= '9'; i++){
            set_transition(2, i, 2);
            set_transition(1, i, 5);
            set_transition(5, i, 5);
            set_transition(6, i, 8);
            set_transition(7, i, 8);
            set_transition(8, i, 8);
        }
        for(char i = 'a'; i <= 'z'; i++){
            set_transition(1, i, 2);
            set_transition(2, i, 2);
        }
        set_transition(1, '+', 3);
        set_transition(1, '-', 4);
        set_transition(5, 'e', 6);
        set_transition(6, '+', 7);
        set_transition(6, '-', 7);

        for(int state : {2, 3, 4, 5, 8}){
            set_final(state);
        }
    }

    int get_transition(int state, char symbol){
        if(state > 0){
            return this->edges[state-1][(int)symbol];
        }
        return 0;
    }
    bool is_final(int state){
        if(state > 0){
            return this->finals[state-1];
        }
        return false;
    }
};

int main(){
    string input;
    for( int symbol = fgetc(stdin); symbol != EOF; symbol = fgetc(stdin) ){
        input.append(sizeof(char), symbol);
    }

    Automato automato;

    int start = 0;
    int lenght = input.length();
    int current_state = 1;
    int last_final_state = 0;
    int last_final_position = 0;
    for(int position = 0; position <= lenght; position++){ //include null terminator
        char symbol = input.data()[position];

        current_state = automato.get_transition(current_state, symbol);

        if(automato.is_final(current_state)){
            last_final_state = current_state;
            last_final_position = position;
        }

        if(current_state == 0){
            if(last_final_state != 0){
                cout << nl() << input.substr(start, last_final_position-start+1);
                start = last_final_position+1;
            }
            else{
                char c = input.data()[start];
                if(c != '\n' && c != ' ' && c != '\0'){
                    cout << nl() << "ERRO";
                }
                start++;
            }
            position = start - 1;
            current_state = 1;
            last_final_state = 0;
        }
    }

    return 0;
}
