cc = gcc -g
ccw = ${cc} -Wall
out = semantico
objs = main.o lexer.yy.o parser.tab.o string.o

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
		main.c \
		string.h string.c \
		lexer.l parser.y
