/* Nao usar a biblioteca do flex */
%option noyywrap

%{
#include <iostream>
using namespace std;
int total_lines = 0;
int blank_lines = 0;
int lines_w_comments = 0;
int nb_nc_lines = 0;
int semi_colons = 0;
int preproc_direct = 0;
bool ml_comment = false;
%}

%%
"/*" {
	ml_comment = true;
}

"*/" {
	ml_comment = false;
	lines_w_comments++;
}

"#include"|"#define" {
	if(!ml_comment){
		preproc_direct++;
	}
}

";" {
	if(!ml_comment){
		semi_colons++;
	}
}

"//"[^\n]*\n {
	lines_w_comments++;
	total_lines++;
}

^[[:space:]\t]*\n {
	if(!ml_comment){
		blank_lines++;
	}
	else{
		lines_w_comments++;
	}
	total_lines++;
}

\n {
	if(!ml_comment){
		nb_nc_lines++;
	}
	else{
		lines_w_comments++;
	}
	total_lines++;
}

. {}
%%

void reset_vars(){
	total_lines = 0;
	blank_lines = 0;
	lines_w_comments = 0;
	nb_nc_lines = 0;
	semi_colons = 0;
	preproc_direct = 0;
	ml_comment = false;
}

int main(int argc, char **argv){
	cout << " total    blank lines w/   nb, nc    semi- preproc. file" << endl;
	cout << " lines    lines comments    lines   colons  direct." << endl;
	cout << "------+--------+--------+--------+--------+--------+----" << endl;

	for( int i = 1; i < argc; i++ ){
		yyin = fopen(argv[i], "r");

		reset_vars();
		yylex();

		printf("%6d %8d %8d %8d %8d %8d %s\n", total_lines, blank_lines, lines_w_comments, nb_nc_lines, semi_colons, preproc_direct, argv[i] );

		fclose(yyin);
	}

	return 0;
}
