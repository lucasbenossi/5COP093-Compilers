o_list = main.o lexico.o symbols.o sintatico.o nl.o
out = automato
cc = g++ -Wall -Wextra -g

${out}: ${o_list}
	${cc} ${o_list} -o ${out}

main.o : main.cpp
	${cc} -c main.cpp

lexico.o : lexico.hpp lexico.cpp
	${cc} -c lexico.cpp

symbols.o : symbols.hpp symbols.cpp
	${cc} -c symbols.cpp

sintatico.o : sintatico.hpp sintatico.cpp
	${cc} -c sintatico.cpp

nl.o : nl.hpp nl.cpp
	${cc} -c nl.cpp

reset :
	rm automato *.o
