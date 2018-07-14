flex=flex
bison=bison -d
cc = gcc -g -Wall
ccnW = gcc -g
out = sintatico
objs = main.o lexer.o

${out} : ${objs}
	${cc} ${objs} -o ${out}

main.o : main.c
	${cc} -c main.c

lexer.o parser.o : lexer.l parser.y
	${bison} parser.y
	${flex} -o lexer.yy.c lexer.l
	${ccnW} -c parser.tab.c -o parser.o
	${ccnW} -c lexer.yy.c -o lexer.o

clean:
	rm *.yy.c
	rm *.tab.c *.tab.h
	rm *.o
	rm ${out}
