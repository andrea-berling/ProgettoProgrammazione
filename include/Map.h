#ifndef MAP_H
#define MAP_H
#include <string>
#include "Tile.h"
#include "Matrix.h"
#include "HashTable.h"
#include "dequeue.h"
#include "Graph.h"
#include "Room.h"

class Map
{
    private:

        Matrix<Tile> grid;
        HashTable<std::string,Room> rooms;
        int width, height;

        void connectToMap(Graph& G, Point& p, Point& q);
        // Connects the given points to the graph

        void disconnectFromMap(Graph& G, Point& p, Point& q);
        // Removes the given points to the graph and the edege that connects them

        void place(Room& R);
        // Places a room in the grid

        bool overlaps(Room& R);
        // Returns true if the given room overlaps with other rooms or is adjacent to another room

        void populateGraph(Graph& G);
        // Fills the graph with the points of the grid that are not rooms

        void createLinks(Graph& G);
        // Creates the links between points in the graph

        void link(Room& R,Room& Q,Graph& G);
        // Links two rooms in the map making use of the graph of the map
        
        Room generateRoom(std::string id, int seed);
        // Generates a room given an id and a seed

    public:

        Map();
        // Defualt constructor
        
        Map(int width, int height);
        // Creates a new map with the given # of rows and columns

        Tile& operator () (int x, int y);
        // Returns a reference variable to Map(x,y)

        Tile& operator () (Point p);
        // Returns a reference variable to Map(p.x,p.y)

        int getWidth();
        // getter for width
        
        int getHeight();
        // getter for height

        void addRoom(Room& R, std::string id);
        // Adds the given room with the given id to the map

        void generate(int requiredRooms);
        // Generates the map given a number of required rooms

        void setVisible(std::string id);
        // Given an id, it sets the corresponding room visible

        Room pickRoom();
        // Picks the first room in the Rooms map

        void showAround(int x, int y);
        // Shows the tiles around the position of the main character

};

#endif
