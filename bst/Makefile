.PHONY: clean

CFLAGS=-Wall -g

run: bst
	./bst

bst: main.o bst.o

clean:
	rm -f *.o

fclean:
	rm -f *.o bst

re: clean run