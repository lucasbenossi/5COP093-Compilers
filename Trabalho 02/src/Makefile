cc = gcc -g
ccw = ${cc} -Wall
out = dcmat
objs = main.o lexer.yy.o parser.tab.o settings.o tree.o matrix.o

${out} : ${objs}
	${ccw} ${objs} -o ${out} -lm

main.o : main.c lexer.yy.h parser.tab.h
	${ccw} -c main.c

lexer.yy.o : lexer.yy.h lexer.yy.c parser.tab.h
	${cc} -g -c lexer.yy.c

parser.tab.o : parser.tab.h parser.tab.c lexer.yy.h
	${cc} -g -c parser.tab.c

settings.o : settings.h settings.c
	${ccw} -c settings.c

tree.o : tree.h tree.c parser.tab.h
	${ccw} -c tree.c

matrix.o : matrix.h matrix.c
	${ccw} -c matrix.c

lexer.yy.c lexer.yy.h : lexer.l
	flex lexer.l

parser.tab.c parser.tab.h : parser.y
	bison -r states parser.y

clean:
	bash clean.sh *.yy.h *.yy.c *.tab.c *.tab.h *.o parser.output ${out}

sintatico.zip :
	zip sintatico.zip Makefile main.c lexer.l parser.y string.h string.c
