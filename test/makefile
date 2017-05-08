DEBUG=-g
BUILD=build

all: $(BUILD)/Graph.o $(BUILD)/Map.o $(BUILD)/Matrix.o $(BUILD)/Room.o $(BUILD)/newtest.o
	g++ $(BUILD)/Graph.o $(BUILD)/newtest.o $(BUILD)/Map.o $(BUILD)/Matrix.o $(BUILD)/Room.o -o Test $(DEBUG)
$(BUILD)/Graph.o: Graph.cpp Graph.h
	g++ -c Graph.cpp $(DEBUG) -o $(BUILD)/Graph.o
$(BUILD)/Map.o: Map.cpp Map.h
	g++ -c Map.cpp $(DEBUG) -o $(BUILD)/Map.o
$(BUILD)/Matrix.o: Matrix.cpp Matrix.h
	g++ -c Matrix.cpp $(DEBUG) -o $(BUILD)/Matrix.o
$(BUILD)/Room.o: Room.cpp Room.h
	g++ -c Room.cpp $(DEBUG) -o $(BUILD)/Room.o
$(BUILD)/newtest.o: newtest.cpp 
	g++ -c newtest.cpp $(DEBUG) -o $(BUILD)/newtest.o
clean:
	rm $(BUILD)/*.o
