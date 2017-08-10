CC=g++
SRC=src
CFLAGS=-I include -g
BUILD=build
DEPS=utility.hpp

all: $(BUILD)/Graph.o $(BUILD)/main.o $(BUILD)/Map.o $(BUILD)/Matrix.o $(BUILD)/Room.o $(BUILD)/Tile.o
	$(CC) $(BUILD)/Graph.o $(BUILD)/main.o $(BUILD)/Map.o $(BUILD)/Matrix.o $(BUILD)/Room.o $(BUILD)/Tile.o -o Test $(CFLAGS) -lncurses
$(BUILD)/Tile.o: src/Tile.cpp include/Tile.h
	$(CC) -c $(SRC)/Tile.cpp $(CFLAGS) -o $(BUILD)/Tile.o
$(BUILD)/Graph.o: src/Graph.cpp include/Graph.h
	$(CC) -c $(SRC)/Graph.cpp $(CFLAGS) -o $(BUILD)/Graph.o
$(BUILD)/Map.o: src/Map.cpp include/Map.h
	$(CC) -c $(SRC)/Map.cpp $(CFLAGS) -o $(BUILD)/Map.o
$(BUILD)/Matrix.o: src/Matrix.cpp include/Matrix.h
	$(CC) -c $(SRC)/Matrix.cpp $(CFLAGS) -o $(BUILD)/Matrix.o
$(BUILD)/Room.o: src/Room.cpp include/Room.h include/utility.hpp
	$(CC) -c $(SRC)/Room.cpp $(CFLAGS) -o $(BUILD)/Room.o
$(BUILD)/main.o: src/main.cpp include/utility.hpp
	$(CC) -c $(SRC)/main.cpp $(CFLAGS) -o $(BUILD)/main.o
clean:
	rm $(BUILD)/*.o
