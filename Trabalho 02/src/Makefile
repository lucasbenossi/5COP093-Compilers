cc = gcc -g
ccw = ${cc} -Wall
out = dcmat
objs = main.o settings.o tree.o matrix.o plot.o lexer.yy.o parser.tab.o

${out} : ${objs}
	${ccw} ${objs} -o ${out} -lm


main.o : main.c lexer.yy.h parser.tab.h
	${ccw} -c main.c

settings.o : settings.h settings.c
	${ccw} -c settings.c

tree.o : tree.h tree.c parser.tab.h
	${ccw} -c tree.c

matrix.o : matrix.h matrix.c
	${ccw} -c matrix.c

plot.o : plot.h plot.c
	${ccw} -c plot.c

lexer.yy.o : lexer.yy.h lexer.yy.c parser.tab.h
	${cc} -g -c lexer.yy.c

parser.tab.o : parser.tab.h parser.tab.c lexer.yy.h
	${cc} -g -c parser.tab.c


lexer.yy.h lexer.yy.c : lexer.l
	flex lexer.l

parser.tab.h parser.tab.c : parser.y
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
		settings.h settings.c \
		tree.h tree.c \
		matrix.h matrix.c \
		plot.h plot.c \
		lexer.l \
		parser.y
