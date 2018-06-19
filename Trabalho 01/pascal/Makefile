o_list = main.o lexico.o lexico2.o symbol.o sintatico.o sintatico2.o
out = pascal
cc = g++ -std=c++11 -Wall -Wextra -g

${out}: ${o_list}
	${cc} ${o_list} -o ${out}

main.o : main.cpp
	${cc} -c main.cpp

lexico.o lexico2.o : lexico.hpp lexico.cpp lexico2.cpp
	${cc} -c lexico.cpp lexico2.cpp

symbol.o : symbol.hpp symbol.cpp
	${cc} -c symbol.cpp

sintatico.o sintatico2.o : sintatico.hpp sintatico.cpp sintatico2.cpp
	${cc} -c sintatico.cpp sintatico2.cpp

reset :
	rm pascal *.o
