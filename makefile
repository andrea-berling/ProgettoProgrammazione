CC=g++
SRC=src
CFLAGS=-I include -g
BUILD=build
DEPS=utility.hpp

all: build/main.o build/Menu.o build/Window.o
	g++ build/*.o -o Test -g -lncurses -lmenu
build/main.o: src/main.cpp
	g++ -c -lncurses -lmenu src/main.cpp -o build/main.o -g
build/Menu.o: src/Menu.cpp include/Menu.h
	g++ -c -lncurses -lmenu src/Menu.cpp -o build/Menu.o -g
build/Window.o: src/Window.cpp include/Window.h
	g++ -c -lncurses -lmenu src/Window.cpp -o build/Window.o -g
clean:
	rm build/* Test
