cc = gcc -g
ccw = ${cc} -Wall
out = semantico
objs = main.o lexer.yy.o parser.tab.o string.o list.o hash_table.o ast_programa.o ast_variavel.o

${out} : ${objs}
	${ccw} ${objs} -o ${out}

main.o : main.c lexer.yy.h parser.tab.h
	${ccw} -c main.c

lexer.yy.o : lexer.yy.h lexer.yy.c parser.tab.h
	${cc} -c lexer.yy.c

parser.tab.o : parser.tab.h parser.tab.c lexer.yy.h
	${cc} -c parser.tab.c

string.o : string.h string.c
	${ccw} -c string.c

list.o : list.h list.c
	${ccw} -c list.c

hash_table.o : hash_table.h hash_table.c
	${ccw} -c hash_table.c

ast_programa.o : ast_programa.h ast_programa.c
	${ccw} -c ast_programa.c

ast_variavel.o : ast_variavel.h ast_variavel.c
	${ccw} -c ast_variavel.c


lexer.yy.c lexer.yy.h : lexer.l
	flex lexer.l

parser.tab.c parser.tab.h : parser.y
	bison -r states parser.y


clean:
	bash clean.sh \
		lexer.yy.h lexer.yy.c \
		parser.tab.h parser.tab.c parser.output \
		${objs} ${out}

${out}.zip :
	zip ${out}.zip \
		Makefile \
		*.c *.h \
		lexer.l parser.y
