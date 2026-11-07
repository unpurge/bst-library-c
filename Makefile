CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g -Iinclude
SANITIZE = -fsanitize=address,undefined

.PHONY: all test exemplo clean

all: exemplo

build: mkdir -p build

build/test_bst: tests/test_bst.c src/bst.c include/bst.h | build
	$(CC) $(CFLAGS) $(SANITIZE) tests/test_bst.c src/bst.c -o $@
	
test: build/test_bst
	./build/test_bst

exemplo: build/exemplo
	./build/exemplo

clean: rm -rf build
