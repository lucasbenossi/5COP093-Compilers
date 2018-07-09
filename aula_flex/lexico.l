/* Nao usar a biblioteca do flex*/
%option noyywrap

%{
int chars = 0;
int words = 0;
int lines = 1;
%}

%%

"while"    {printf("WHILE\n");}
"for"      {printf("FOR\n");}
"if"       {printf("IF\n");}
"else"     {printf("ELSE\n");}
"+"        {printf("PLUS\n");}
"exit"     {return;}
[+-]?[0-9]+ {printf("NUM:(%s)\n",yytext);}
[_a-zA-Z][a-zA-Z0-9]* { printf("ID(%s)\n",yytext); }
[ \t]      {chars++;}
[\n]       {lines++;}
.          { printf("ERRO(%s)\n",yytext); chars++;}

%%

main(int argc, char **argv)
{
	yylex();
	return 0;
}
