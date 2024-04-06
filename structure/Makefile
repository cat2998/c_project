.PHONY: clean

CFLAGS=-Wall -g

main: linkedlist.o main.o
	valgrind ./main

clean:
	rm -f *.o

fclean:
	rm -f *.o main

re: clean driver