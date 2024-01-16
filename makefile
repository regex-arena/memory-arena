IN=tests/main.c
OUT=bin/main
CC=gcc -Wall -g
LIB_FILES=lib/arena.h
LIB_NAME=arena

build:
	$(CC) -c $(IN) -o $(OUT).o
	$(CC) $(OUT).o -o $(OUT) -L ./bin

install:
	sudo cp $(LIB_FILES) -i /usr/local/include

test: build
	LD_LIBRARY_PATH="./bin/" $(OUT)
tv: build
	LD_LIBRARY_PATH="./bin/" valgrind --leak-check=yes $(OUT)

clean:
	rm -rf ./bin/*
