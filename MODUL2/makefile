all: program

program: main.o
	g++ main.o -o program

main.o: main.cpp
	g++ -c main.cpp -o main.o

clean:
	rm -f main.o program
