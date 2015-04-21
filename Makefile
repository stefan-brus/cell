CFLAGS = -Wall -g
CC = cc

all: cell-cat

cell-cat: cat.o
	$(CC) $(CFLAGS) cat.o -o cell-cat

clean:
	rm -f cell-* *.o

