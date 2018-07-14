cc = gcc -g
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

lexer.yy.c lexer.yy.h : lexer.l
	flex lexer.l

parser.tab.c parser.tab.h : parser.y
	bison -r states parser.y

string.o : string.h string.c
	${ccw} -c string.c

clean:
	rm *.yy.h *.yy.c *.tab.c *.tab.h *.o
	rm ${out}
