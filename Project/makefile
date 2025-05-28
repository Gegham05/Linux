CC = gcc
CFLAGS = -Wall -Wextra -pedantic 
LDFLAGS = -lrt -pthread

all: sender pipemail

sender: sender.cpp
	$(CC) $(CFLAGS) -o sender sender.cpp $(LDFLAGS)

pipemail: receiver.cpp
	$(CC) $(CFLAGS) -o pipemail receiver.cpp $(LDFLAGS)

clean:
	rm -f sender pipemail
