cc = gcc -g -Wall
out = sintatico
objs = main.o lexer.yy.o parser.tab.o

${out} : ${objs}
	${cc} ${objs} -o ${out}

main.o : main.c lexer.yy.h parser.tab.h
	${cc} -c main.c

lexer.yy.o : lexer.yy.h lexer.yy.c parser.tab.h
	gcc -g -c lexer.yy.c

parser.tab.o : parser.tab.h parser.tab.c
	gcc -g -c parser.tab.c

lexer.yy.c lexer.yy.h : lexer.l
	flex lexer.l

parser.tab.c parser.tab.h : parser.y
	bison -r states parser.y

clean:
	rm *.yy.h *.yy.c *.tab.c *.tab.h *.o
	rm ${out}
