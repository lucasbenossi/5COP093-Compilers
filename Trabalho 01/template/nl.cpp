#include "nl.hpp"
#include <iostream>
using namespace std;

string nl(){
	static bool first = true;
	if(first){
		first = false;
		return "";
	}
	return "\n";
}
