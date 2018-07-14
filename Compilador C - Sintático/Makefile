cc = gcc -g -Wall
out = sintatico
objs = main.o lexer.yy.o parser.tab.o

${out} : ${objs}
	${cc} ${objs} -o ${out}

main.o : main.c lexer.yy.h parser.tab.h
	${cc} -c main.c

lexer.yy.o : lexer.yy.h lexer.yy.c
	gcc -g -c lexer.yy.c

parser.tab.o : parser.tab.h parser.tab.c
	gcc -g -c parser.tab.c

parser.tab.c parser.tab.h : parser.y
	bison parser.y

lexer.yy.c lexer.yy.h : lexer.l
	flex lexer.l

clean:
	rm *.yy.h *.yy.c
	rm *.tab.c *.tab.h
	rm *.o
	rm ${out}
