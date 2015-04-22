CFLAGS = -Wall -g
CC = cc

all: cell-cat cell-ls

cell-cat: cat.o
	$(CC) $(CFLAGS) cat.o -o cell-cat

cell-ls: ls.o
	$(CC) $(CFLAGS) ls.o -o cell-ls

clean:
	rm -f cell-* *.o

