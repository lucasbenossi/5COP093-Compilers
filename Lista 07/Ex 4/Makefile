cc = g++
program = cstats

$(program): lexico.l
	flex lexico.l
	$(cc) lex.yy.c -o $(program)
