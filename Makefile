CFLAGS = -Wall -g
CC = cc

all: cell-cat cell-cd cell-ls cell-pwd

cell-cat: cat.o
	$(CC) $(CFLAGS) cat.o -o cell-cat

cell-cd: cd.o
	$(CC) $(CFLAGS) cd.o -o cell-cd

cell-ls: ls.o
	$(CC) $(CFLAGS) ls.o -o cell-ls

cell-pwd: pwd.o
	$(CC) $(CFLAGS) pwd.o -o cell-pwd

clean:
	rm -f cell-* *.o

