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

        void generateRooms(int n);
        // Given a number n, it generates n rooms


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

        void generate(int requiredRooms);
        // Generates the map given a number of required rooms

        void setVisible(std::string id,std::unordered_map<std::string,Monster>& monsters,std::unordered_map<std::string,Item>& items);
        // Given an id, it sets the corresponding room visible
        // Every monster and item in the room is set visible as well

        Room pickRoom();
        // Picks a random room in the Rooms map

        void showAround(int x, int y);
        // Shows the tiles around the position of the main character

        void freeSpots(int n,std::unordered_set<Point>& spots,int r = 1);
        // Given a number of rooms n, a number of repetitions r and a vector of points, it stores n*r free spots in the
        // map in the vector, with r spots per room

        std::string placeCharacter(PlayableCharacter& player);
        // Given a main character, places it in a random room in the map
        // Returns the id of the room the player was placed in

        Point freeSpot(Room R);
        // Given a room, returns a free spot in the room

};

#endif
