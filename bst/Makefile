.PHONY: clean

CFLAGS=-Wall -g -DBST

run: bst
	valgrind ./bst

bst: test.o bst.o

clean:
	rm -f *.o

fclean:
	rm -f *.o bst

re: clean run
