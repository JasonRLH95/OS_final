CC = gcc
Flags = -Wall -g

all: myShell

myShell: myShell.o
	$(CC) $(Flags) -o myShell myShell.o

myShell.o: myShell.c myShell.h
	$(CC) $(Flags) -c myShell.c

clean:
	rm -f *.o myShell