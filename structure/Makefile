.PHONY: clean

CFLAGS=-Wall -g

name= ./main

run: main
	valgrind ${name}

main: linkedlist.o main.o

clean:
	rm -f *.o

fclean:
	rm -f *.o main

re: clean main