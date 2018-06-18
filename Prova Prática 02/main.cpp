#include <iostream>
#include <stack>
#include <vector>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
using namespace std;

static const int TERMINALS = 7;
static const int NONTERMINALS = 7;

string nl(){
    static bool first = true;
    if(first){
        first = false;
        return "";
    }
    return "\n";
}

enum Symbol{
    ID, PLUS, MULT, INC, LPAREN, RPAREN, END,
    E, E1, T, T1, F, P, S,
    VAZIO
};
static const string strings[] = {
    "id", "+", "*", "++", "(", ")", "$",
    "E", "E'", "T", "T'", "F", "P", "S",
    ""
};
bool is_terminal(Symbol s){
    if(s >= ID && s <= END){
        return true;
    }
    return false;
}
bool is_non_terminal(Symbol s){
    if(s >= E && s <= S){
        return true;
    }
    return false;
}

class Automato{
private:
    string input;
    unsigned int position;
public:
    Automato(string input){
        this->input = input;
        this->position = 0;
    }
    Symbol get_token(){
        if(this->position < this->input.length()){
            Symbol s = (Symbol) (this->input.data()[position] - '0');
            this->position++;
            return s;
        }
        return VAZIO;
    }
};

class Parser{
private:
    vector<Symbol> *table[NONTERMINALS][TERMINALS];
    string input;
    void set_transition(Symbol non_terminal, Symbol terminal, vector<Symbol> next){
        this->table[non_terminal-(END+1)][terminal] = new vector<Symbol>(next);
    }
    vector<Symbol> *get_transition(Symbol non_terminal, Symbol terminal){
        return this->table[non_terminal-(END+1)][terminal];
    }
    string get_string_token(Symbol token){
        if(token == VAZIO){
            return " ";
        }
        return " " + strings[token] + " ";
    }
    string get_string_esperado(Symbol symbol){
        bool first = true;
        string esperado;
        if(is_non_terminal(symbol)){
            for(int i = 0; i < TERMINALS; i++){
				vector<Symbol> *v = get_transition(symbol, (Symbol)i);
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
            esperado = " " + strings[symbol];
        }
        return esperado;
    }
public:
    Parser(string input){
        this->input = input;
        for(int i = 0; i < NONTERMINALS; i++){
            for(int j = 0; j < TERMINALS; j++){
                this->table[i][j] = NULL;
            }
        }
        set_transition(E, ID, {T, E1});
        set_transition(T, ID, {F, T1});
        set_transition(F, ID, {ID, P});
        set_transition(S, ID, {E, END});
        set_transition(E1, PLUS, {PLUS, T, E1});
        set_transition(T1, PLUS, {});
        set_transition(P, PLUS,{});
        set_transition(T1, MULT, {MULT, F, T1});
        set_transition(P, MULT, {});
        set_transition(P, INC, {INC});
        set_transition(E, LPAREN, {T, E1});
        set_transition(T, LPAREN, {F, T1});
        set_transition(F, LPAREN, {LPAREN, E, RPAREN, P});
        set_transition(S, LPAREN, {E, END});
        set_transition(E1, RPAREN, {});
        set_transition(T1, RPAREN, {});
        set_transition(P, RPAREN, {});
        set_transition(E1, END, {});
        set_transition(T1, END, {});
        set_transition(P, END, {});
    }
    ~Parser(){
        for(int i = 0; i < NONTERMINALS; i++){
            for(int j = 0; j < TERMINALS; j++){
                delete this->table[i][j];
            }
        }
    }
    void parse(){
        Automato automato(this->input);
        stack<Symbol> ss;
        ss.push(S);
        Symbol token = automato.get_token();
        while(ss.size() > 0){
            Symbol symbol = ss.top();
            ss.pop();
            if(token == symbol){
                token = automato.get_token();
            }
            else{
                vector<Symbol> *next = NULL;
                if(is_non_terminal(symbol) && is_terminal(token)){
                    next = get_transition(symbol, token);
                }
                if(next == NULL){
                    cout << nl() << "ERRO SINTATICO EM:" << get_string_token(token) << "ESPERADO:" << get_string_esperado(symbol);
                    return;
                }
                for(int i = next->size()-1; i >= 0; i--){
                    ss.push(next->at(i));
                }
            }
        }
        cout << nl() << "CADEIA ACEITA";
    }
};

int main(){
    int c;
    c = fgetc(stdin);
    while(c != EOF){
        string input;
        while(c != '\n' && c != EOF){
            input.append(sizeof(char), c);
            c = fgetc(stdin);
        }

        /*cout << input << endl << endl;

        Automato automato(input);
        int i = automato.get_token();
        while(i != VAZIO){
            cout << i << endl;
            i = automato.get_token();
        }*/

        Parser parser(input);
        parser.parse();

        c = fgetc(stdin);
    }

    return 0;
}