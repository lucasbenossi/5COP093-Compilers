#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

static const int SYMBOLS = 256;
static const int STATES = 7;
static const int START = 0;
static const int INVALID = -1;
static const int TERMINALS = 6;
static const int NONTERMINALS = 6;

string nl(){
	static bool first = true;
	if(first){
		first = false;
		return "";
	}
	return "\n";
}

enum Symbol{
	ID, PLUS, MULT, LPAREN, RPAREN, END,
	E, E1, T, T1, F, S,
	VAZIO, INVALIDO
};
static const string strings[] = {
	"id", "+", "*", "(", ")", "$",
	"E", "E'", "T", "T'", "F", "S",
	"", "invalido"
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
	int edges[STATES][SYMBOLS];
	bool finals[STATES];
	Symbol tokens[STATES];
	string input;
	int length;
	int start = 0;
	string token_string;
	void set_transition(int state, char c, int next){
		this->edges[state][(int)c] = next;
	}
	void set_final(int state){
		this->finals[state] = true;
	}
	void set_token(int state, Symbol token){
		this->tokens[state] = token;
	}
	int get_transition(int state, char c){
		if(state >= START){
			return this->edges[state][(int)c];
		}
		return INVALID;
	}
	bool is_final(int state){
		if(state >= START){
			return this->finals[state];
		}
		return false;
	}
	Symbol get_token(int state){
		if(state >= START){
			return this->tokens[state];
		}
		return INVALIDO;
	}
public:
	Automato(string input){
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
	Symbol get_token(){
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
	string get_token_string(){
		return this->token_string;
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
	string get_string_esperado(Symbol s){
		bool first = true;
		string esperado;
		if(is_non_terminal(s)){
			for(int i = 0; i < TERMINALS; i++){
				vector<Symbol> *v = get_transition(s, (Symbol)i);
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
		set_transition(F, ID, {ID});
		set_transition(S, ID, {E, END});
		set_transition(E1, PLUS, {PLUS, T, E1});
		set_transition(T1, PLUS, {});
		set_transition(T1, MULT, {MULT, F, T1});
		set_transition(E, LPAREN, {T, E1});
		set_transition(T, LPAREN, {F, T1});
		set_transition(F, LPAREN, {LPAREN, E, RPAREN});
		set_transition(S, LPAREN, {E, END});
		set_transition(E1, RPAREN, {});
		set_transition(T1, RPAREN, {});
		set_transition(E1, END, {});
		set_transition(T1, END, {});
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
					next = get_transition(symbol, token);
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
};

int main(){
	int symbol = fgetc(stdin);
	while(symbol != EOF){
		string input;
		while(symbol != '\n' && symbol != EOF){
			input.append(sizeof(char), symbol);
			symbol = fgetc(stdin);
		}
		Parser parser(input);
		parser.parse();
		// Automato automato(input);
		// while(automato.get_token() != VAZIO){
		// 	cout << automato.get_token_string() << endl;
		// }
		symbol = fgetc(stdin);
	}
	return 0;
}
