#ifndef MAP_H
#define MAP_H
#include <string>
#include "Tile.h"
#include "Matrix.h"
#include <unordered_map>
#include <deque>
#include <vector>
#include "Graph.h"
#include "Area.h"
#include "Room.h"
#include "Item.h"
#include "Monster.h"
#include "personaggiGiocabili.h"

class Map
{
    private:

        Matrix<Tile> grid;
        Matrix<Item> itemsLayer;
        Matrix<Monster> monstersLayer;
        std::unordered_map<std::string,Room> rooms;
        int width, height;

        void connectToMap(Graph& G, Point& p, Point& q);
        // Connects the given points to the graph

        void place(Room& R);
        // Places a room in the grid

        void populateGraph(Graph& G);
        // Fills the graph with the points of the grid that are not rooms, borders excluded

        void createLinks(Graph& G);
        // Creates the links between points in the graph

        void link(Room& R,Room& Q,Graph& G);
        // Links two rooms in the map making use of the graph of the map
        
        Room generateRoom(Area A,std::string id);
        // Generates a room with the given an id 


    public:

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

        void generateRooms(int n);
        // Given a number n, it generates n rooms

        void setVisible(std::string id);
        // Given an id, it sets the corresponding room visible

        Room pickRoom();
        // Picks a random room in the Rooms map

        void showAround(int x, int y);
        // Shows the tiles around the position of the main character

        void freeSpots(int n,std::unordered_set<Point>& spots,int r = 1);
        // Given a number of rooms n, a number of repetitions r and a vector of points, it stores n*r free spots in the
        // map in the vector, with r spots per room

        void placeCharacter(PlayableCharacter& player);
        // Given a main character, places it in a random room in the map

        void placeItem(Item i);
        // Given an item it places it on the map

        void placeMonster(Monster& m);
        // Given a monster it places it on the map

        Point freeSpot(Room R);
        // Given a room, returns a free spot in the room

        bool isWalkable(int x, int y);
        // Returns true if the tile in Map(x,y) is walkable, false otherwise
};

#endif
