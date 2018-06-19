#include <iostream>
#include <cstring>

#include "symbols.hpp"
#include "lexico.hpp"
#include "sintatico.hpp"

using namespace std;

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
