%{

#include <stdio.h>
#include <ast.h>
extern int yylex();

TreeNode* AST = NULL;

%}

%union{
	TreeNode* ast;
	int integer;
}

/* declare tokens */
%token NUMBER
%token ADD
%token SUB
%token MUL
%token DIV
%token ABS
%token EOL

%type <ast> calc
%type <ast> exp
%type <ast> factor
%type <ast> term
%type <integer> NUMBER

%start calc

%%

calc: exp EOL { AST = $1; 
                    if(AST)
					{
						RPN_Walk(AST);
					}
					else
					{
						printf("AST is NULL\n");
					}
                    return;
                }
;

exp: factor 		 { $$ = $1;}
	| exp ADD factor {TreeNode* aux = (TreeNode*)malloc(sizeof(struct node));
	                   aux->node_type = ADD;
					   aux->value = 0;
					   aux->left = $1;
					   aux->right = $3;
					   $$ = aux;
					  }
	| exp SUB factor {TreeNode* aux = (TreeNode*)malloc(sizeof(struct node));
	                   aux->node_type = SUB;
					   aux->value = 0;
					   aux->left = $1;
					   aux->right = $3;
					   $$ = aux;
					  }
;

factor: term          { $$ = $1;}
	| factor MUL term {TreeNode* aux = (TreeNode*)malloc(sizeof(struct node));
	                   aux->node_type = MUL;
					   aux->value = 0;
					   aux->left = $1;
					   aux->right = $3;
					   $$ = aux;
					  }
	| factor DIV term {TreeNode* aux = (TreeNode*)malloc(sizeof(struct node));
	                   aux->node_type = DIV;
					   aux->value = 0;
					   aux->left = $1;
					   aux->right = $3;
					   $$ = aux;
					  }
;

term: NUMBER   { TreeNode* aux = (TreeNode*)malloc(sizeof(struct node)); 
                 aux->node_type = NUMBER;
				 aux->value = $1;
				 aux->left = NULL;
				 aux->right = NULL;
				 $$ = (TreeNode*) aux;
			   }
	| ABS term { TreeNode* aux = (TreeNode*)malloc(sizeof(struct node)); 
                 aux->node_type = ABS;
				 aux->value = 0;
				 aux->left = $2;
				 aux->right = NULL;
				 $$ = aux;
			   }               
;

%%


yyerror(char *s)
{
	fprintf(stderr, "error: %s\n", s);
}

int main(int argc, char **argv)
{
	yyparse();
}

