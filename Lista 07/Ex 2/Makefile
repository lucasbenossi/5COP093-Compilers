cc = gcc
programa = programa

$(programa): lexico.l
	flex lexico.l
	$(cc) lex.yy.c -o $(programa)
