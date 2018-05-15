/* Nao usar a biblioteca do flex*/
%option noyywrap

%%

"if"					{printf("%s IF\n",yytext);}
[a-z][a-z0-9]*			{printf("%s ID\n",yytext);}
[0-9]*"."[0-9]+			{printf("%s REAL\n",yytext);}
[0-9]+					{printf("%s NUM\n",yytext);}
"--"[a-z]+"\n"			{printf("%s comment\n",yytext);}
[ \t\n]+				{printf("white space\n",yytext);}
.						{printf("%s error\n",yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
