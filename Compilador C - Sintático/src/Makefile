cc = gcc -g -std=c11
ccw = ${cc} -Wall
out = sintatico
objs = main.o lexer.yy.o parser.tab.o string.o

${out} : ${objs}
	${ccw} ${objs} -o ${out}

main.o : main.c lexer.yy.h parser.tab.h
	${ccw} -c main.c

lexer.yy.o : lexer.yy.h lexer.yy.c parser.tab.h
	${cc} -g -c lexer.yy.c

parser.tab.o : parser.tab.h parser.tab.c
	${cc} -g -c parser.tab.c

string.o : string.h string.c
	${ccw} -c string.c

lexer.yy.c lexer.yy.h : lexer.l
	flex lexer.l

parser.tab.c parser.tab.h : parser.y
	bison parser.y

clean:
	bash clean.sh *.yy.h *.yy.c *.tab.c *.tab.h *.o ${out}

sintatico.zip :
	zip sintatico.zip Makefile main.c lexer.l parser.y string.h string.c
