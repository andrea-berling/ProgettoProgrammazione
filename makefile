CC=g++
SRC=src
CFLAGS=-I include -g -std=c++11
CURSES=-lpanel -lncurses -lmenu -ltinfo
BUILD=build
DEPS=utility.h
SHELL=/bin/bash

all: builddir game

builddir: 
	if [ ! -d "$(BUILD)" ]; then mkdir "$(BUILD)"; fi;

game: $(BUILD)/Graph.o $(BUILD)/main.o $(BUILD)/Map.o $(BUILD)/Matrix.o $(BUILD)/Room.o $(BUILD)/Tile.o $(BUILD)/main.o $(BUILD)/Menu.o $(BUILD)/Window.o $(BUILD)/Item.o $(BUILD)/Level.o $(BUILD)/Monster.o $(BUILD)/personaggiGiocabili.o $(BUILD)/utility.o $(BUILD)/Area.o
	$(CC) build/*.o -o Test $(CFLAGS) $(CURSES)
$(BUILD)/main.o: src/main.cpp
	g++ -c $(CFLAGS) src/main.cpp -o $(BUILD)/main.o -g $(CURSES)
$(BUILD)/Menu.o: src/Menu.cpp include/Menu.h
	g++ -c $(CFLAGS) src/Menu.cpp -o $(BUILD)/Menu.o -g $(CURSES) 
$(BUILD)/Window.o: src/Window.cpp include/Window.h
	g++ -c $(CFLAGS) src/Window.cpp -o $(BUILD)/Window.o -g $(CURSES)
$(BUILD)/Tile.o: src/Tile.cpp include/Tile.h
	$(CC) -c $(SRC)/Tile.cpp $(CFLAGS) -o $(BUILD)/Tile.o
$(BUILD)/Graph.o: src/Graph.cpp include/Graph.h
	$(CC) -c $(SRC)/Graph.cpp $(CFLAGS) -o $(BUILD)/Graph.o
$(BUILD)/Map.o: src/Map.cpp include/Map.h include/utility.h
	$(CC) -c $(SRC)/Map.cpp $(CFLAGS) -o $(BUILD)/Map.o
$(BUILD)/Matrix.o: src/Matrix.cpp include/Matrix.h
	$(CC) -c $(SRC)/Matrix.cpp $(CFLAGS) -o $(BUILD)/Matrix.o
$(BUILD)/Room.o: src/Room.cpp include/Room.h include/utility.h
	$(CC) -c $(SRC)/Room.cpp $(CFLAGS) -o $(BUILD)/Room.o
$(BUILD)/Area.o: src/Area.cpp include/Area.h include/utility.h
	$(CC) -c $(SRC)/Area.cpp $(CFLAGS) -o $(BUILD)/Area.o
$(BUILD)/Item.o: src/Item.cpp include/Item.h
	$(CC) -c $(SRC)/Item.cpp $(CFLAGS) -o $(BUILD)/Item.o
$(BUILD)/Level.o: src/Level.cpp include/Level.h
	$(CC) -c $(SRC)/Level.cpp $(CFLAGS) -o $(BUILD)/Level.o $(CURSES)
$(BUILD)/Monster.o: src/Monster.cpp include/Monster.h
	$(CC) -c $(SRC)/Monster.cpp $(CFLAGS) -o $(BUILD)/Monster.o
$(BUILD)/personaggiGiocabili.o: src/personaggiGiocabili.cpp include/personaggiGiocabili.h
	$(CC) -c $(SRC)/personaggiGiocabili.cpp $(CFLAGS) -o $(BUILD)/personaggiGiocabili.o
$(BUILD)/utility.o: src/utility.cpp include/utility.h
	$(CC) -c $(SRC)/utility.cpp $(CFLAGS) -o $(BUILD)/utility.o
clean:
	rm build/* 
	if [ -f Test ]; then rm Test; fi;
