all: do-command

do-command: main.o
	g++ -Wall -Wextra -Werror main.o -o do-command

main.o: main.cpp
	g++ -Wall -Wextra -Werror -c main.cpp -o main.o

clean:
	rm -f main.o do-command
