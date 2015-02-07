CC = g++
CFLAGS = -g -Wall
#LDFLAGS = -lCppUTest

all: test_list 
#test_rbtree

test_list: list_test.o
	$(CC) -o test_list list_test.o $(LDFLAGS)

#test_rbtree: rbtree_test.o
#	gcc -c rbtree.c
#	$(CC) -o test_rbtree rbtree_test.o rbtree.o $(LDFLAGS)

list_test.o: list.h list_test.c

#rbtree_test.o: rbtree.h rbtree_test.c

clean:
	-rm -f *.o test_list test_rbtree

