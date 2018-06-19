#include "symbols.hpp"
using namespace std;

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
