IN=tests/main.c
OUT=bin/main
CC=gcc -Wall -g
LIB_FILES=lib/arena.c
LIB_UPDATE_FILES=lib/arena.c lib/arena.h
ifeq ($(OS), Windows_NT)
	LIB_TARGET = arena.dll
else
	LIB_TARGET = libarena.so
endif

build: l
	$(CC) -c $(IN) -o $(OUT).o
	$(CC) $(OUT).o -o $(OUT) -lregx -L ./bin


l: $(LIB_UPDATE_FILES)
	$(CC) -o bin/$(LIB_TARGET) -fpic -shared $(LIB_FILES)

test: build
	LD_LIBRARY_PATH="./bin/" $(OUT)
tv: build
	LD_LIBRARY_PATH="./bin/" valgrind --leak-check=yes $(OUT)

clean:
	rm -rf ./bin/*
