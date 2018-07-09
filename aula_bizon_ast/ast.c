#include <ast.h>
#include <sintatico.tab.h>

void RPN_Walk(TreeNode* aux)
{
	if(aux)
	{
		RPN_Walk(aux->left);
		RPN_Walk(aux->right);
		switch(aux->node_type)
		{
			case ADD:{printf("+ ");}break;
			case SUB:{printf("- ");}break;
			case MUL:{printf("* ");}break;
			case DIV:{printf("/ ");}break;
			case NUMBER:{printf("%d ",aux->value);};break;
			default:{printf("ERROR: INVALID TYPE ");};break;
		}
	}
}