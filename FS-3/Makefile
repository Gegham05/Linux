all: program

program: main.o
	g++ -o program main.o

main.o: main.cpp
	g++ -c main.cpp -o main.o

clear:
	rm -f main.o program

