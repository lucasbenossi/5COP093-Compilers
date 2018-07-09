%option noyywrap
%{

#include <sintatico.tab.h>


int yylval;

%}
%%

"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
\n { return EOL; }
[ \t] { /* ignore whitespace */ }
. { printf("Caracter Misterioso: %c\n", *yytext); exit(0);}

%%
