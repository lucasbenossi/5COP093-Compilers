o_list = main.o
out = automato
cc = g++ -Wall -Wextra -g

${out}: ${o_list}
	${cc} ${o_list} -o ${out}

main.o: main.cpp
	${cc} -c main.cpp
