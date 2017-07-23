CC=g++
SRC=src
CFLAGS=-I include -g
BUILD=build
DEPS=utility.hpp

all: src/main.cpp
	g++ src/main.cpp -o Test -g
clean:
	rm Test
