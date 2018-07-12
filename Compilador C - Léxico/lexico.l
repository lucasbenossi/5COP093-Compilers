/* Nao usar a biblioteca do flex*/
%option noyywrap
%option yylineno

%top{
	void print_token(int option, char *token);
	int get_col();
	const char* nl();

	static const int WHITE_SPACE = 0;
	static const int PRINT = 1;
	static const int DONTPRINT = 2;
	static const int STRING = 3;
	static const int ERROR = 4;
	static const int SL_COMMENT = 5;
	static const int ML_COMMENT_START = 6;
	static const int ML_COMMENT_END = 7;

	static int ml_comment = 0;
	static int ml_comment_lin, ml_comment_col;
}

%%

"void" {print_token(DONTPRINT, "VOID");}
"int" {print_token(DONTPRINT, "INT");}
"char" {print_token(DONTPRINT, "CHAR");}
"return" {print_token(DONTPRINT, "RETURN");}
"break" {print_token(DONTPRINT, "BREAK");}
"switch" {print_token(DONTPRINT, "SWITCH");}
"case" {print_token(DONTPRINT, "CASE");}
"default" {print_token(DONTPRINT, "DEFAULT");}
"do" {print_token(DONTPRINT, "DO");}
"while" {print_token(DONTPRINT, "WHILE");}
"for" {print_token(DONTPRINT, "FOR");}
"if" {print_token(DONTPRINT, "IF");}
"else" {print_token(DONTPRINT, "ELSE");}
"typedef" {print_token(DONTPRINT, "TYPEDEF");}
"struct" {print_token(DONTPRINT, "STRUCT");}
"+" {print_token(DONTPRINT, "PLUS");}
"-" {print_token(DONTPRINT, "MINUS");}
"*" {print_token(DONTPRINT, "MULTIPLY");}
"/" {print_token(DONTPRINT, "DIV");}
"%" {print_token(DONTPRINT, "REMAINDER");}
"++" {print_token(DONTPRINT, "INC");}
"--" {print_token(DONTPRINT, "DEC");}
"&" {print_token(DONTPRINT, "BITWISE_AND");}
"|" {print_token(DONTPRINT, "BITWISE_OR");}
"~" {print_token(DONTPRINT, "BITWISE_NOT");}
"^" {print_token(DONTPRINT, "BITWISE_XOR");}
"!" {print_token(DONTPRINT, "NOT");}
"&&" {print_token(DONTPRINT, "LOGICAL_AND");}
"||" {print_token(DONTPRINT, "LOGICAL_OR");}
"==" {print_token(DONTPRINT, "EQUAL");}
"!=" {print_token(DONTPRINT, "NOT_EQUAL");}
"<" {print_token(DONTPRINT, "LESS_THAN");}
">" {print_token(DONTPRINT, "GREATER_THAN");}
"<=" {print_token(DONTPRINT, "LESS_EQUAL");}
">=" {print_token(DONTPRINT, "GREATER_EQUAL");}
">>" {print_token(DONTPRINT, "R_SHIFT");}
"<<" {print_token(DONTPRINT, "L_SHIFT");}
"=" {print_token(DONTPRINT, "ASSIGN");}
"+=" {print_token(DONTPRINT, "ADD_ASSIGN");}
"-=" {print_token(DONTPRINT, "MINUS_ASSIGN");}
";" {print_token(DONTPRINT, "SEMICOLON");}
"," {print_token(DONTPRINT, "COMMA");}
":" {print_token(DONTPRINT, "COLON");}
"(" {print_token(DONTPRINT, "L_PAREN");}
")" {print_token(DONTPRINT, "R_PAREN");}
"{" {print_token(DONTPRINT, "L_CURLY_BRACKET");}
"}" {print_token(DONTPRINT, "R_CURLY_BRACKET");}
"[" {print_token(DONTPRINT, "L_SQUARE_BRACKET");}
"]" {print_token(DONTPRINT, "R_SQUARE_BRACKET");}
"?" {print_token(DONTPRINT, "TERNARY_CONDITIONAL");}
"#" {print_token(DONTPRINT, "NUMBER_SIGN");}
"->" {print_token(DONTPRINT, "POINT");}
"printf" {print_token(DONTPRINT, "PRINTF");}
"scanf" {print_token(DONTPRINT, "SCANF");}
"define" {print_token(DONTPRINT, "DEFINE");}
"exit" {print_token(DONTPRINT, "EXIT");}

[_A-Za-x][_A-Za-x0-9]* {print_token(PRINT, "IDENTIFIER");}

"0"[0-7]+ {print_token(PRINT, "NUM_OCTAL");}
"0x"[0-9a-f]+ {print_token(PRINT, "NUM_HEXA");}
[0-9]* {print_token(PRINT, "NUM_INTEGER");}

\".*\" {print_token(STRING, "STRING");}
\'[.]\' {print_token(PRINT, "CHARACTER");}

"//".* {print_token(SL_COMMENT, "");}
"/*" {print_token(ML_COMMENT_START, "");}
"*/" {print_token(ML_COMMENT_END, "");}

[ \t]* {print_token(WHITE_SPACE, "");}
. {print_token(ERROR, "");}
[\r\n] {}

%%

int main(int argc, char **argv)
{
	yylex();
	if(ml_comment){
		fputs(nl(), stdout);
		printf("error:lexical:%d:%d: unterminated comment", ml_comment_lin, ml_comment_col);
	}
	return 0;
}

void print_token(int option, char *token){
	int col = get_col();

	if(option == ML_COMMENT_START){
		ml_comment = 1;
		ml_comment_lin = yylineno;
		ml_comment_col = col;
		return;
	}

	if(option == ML_COMMENT_END){
		ml_comment = 0;
		return;
	}

	if(option == WHITE_SPACE || option == SL_COMMENT || ml_comment){
		return;
	}

	fputs(nl(), stdout);
	fputs(token, stdout);

	if(option == PRINT){
		printf("(%s)", yytext);
	}
	else if(option == STRING){
		putchar('(');
		int i, size = strlen(yytext);
		for( i = 1; i < size-1; i++ ){
			putchar(yytext[i]);
		}
		putchar(')');
	}
	else if(option == ERROR){
		printf("error:lexical:%d:%d: %s", yylineno, col, yytext );
	}
}

int get_col(){
	static int line = 0;
	static int col = 1;
	int ret;
	if(yylineno > line){
		line = yylineno;
		col = 1;
	}
	ret = col;
	col += strlen(yytext);
	return ret;
}

const char* nl(){
	static int first = 1;
	if(first){
		first = 0;
		return "";
	}
	return "\n";
}
