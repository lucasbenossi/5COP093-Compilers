#include <iostream>
#include <cstring>

#include "symbol.hpp"
#include "lexico.hpp"
#include "sintatico.hpp"

using namespace std;

int main(){
	int symbol = fgetc(stdin);
	string input;
	while(symbol != EOF){
		input.append(sizeof(char), symbol);
		symbol = fgetc(stdin);
	}

	// Automato automato(input);
	// Token t = automato.get_token();
	// while(t.symbol != VAZIO){
	// 	cout << strings[t.symbol] << "  " << t.string << "  " << t.lin << "  " << t.col << endl;
	// 	t = automato.get_token();
	// }

	Parser parser(input);
	parser.parse();

	return 0;
}
