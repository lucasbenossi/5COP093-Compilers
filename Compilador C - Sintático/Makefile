flex=flex
bison=bison -d
cc = gcc -g -Wall
ccnW = gcc -g
out = sintatico
objs = main.o lex.o

${out} : ${objs}
	${cc} ${objs} -o ${out}

main.o : main.c
	${cc} -c main.c

lex.o parser.o : lex.l parser.y
	${bison} parser.y
	${flex} lex.l
	${ccnW} -c parser.tab.c -o parser.o
	${ccnW} -c lex.yy.c -o lex.o

clean:
	rm *.yy.c
	rm *.tab.c *.tab.h
	rm *.o
	rm ${out}
