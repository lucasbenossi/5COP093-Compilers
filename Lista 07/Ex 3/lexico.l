/* Nao usar a biblioteca do flex*/
%option noyywrap

%%

(aba)+		{printf("(action 1) %s\n",yytext);}
(a(b)*a)	{printf("(action 2) %s\n",yytext);}
(a|b)		{printf("(action 3) %s\n",yytext);}

%%

int main(int argc, char **argv)
{
	yylex();
	return 0;
}
