CC=gcc
CFLAGS=


all:fever 

fever:
	$(CC) -o fever src/main.c

run:
	./fever
