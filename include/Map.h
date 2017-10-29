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

        void place(const Room& R);
        // Places a room on the grid

        void populateGraph(Graph& G);
        // Fills the graph with the points of the grid that are not rooms, map borders excluded

        void createLinks(Graph& G);
        // Creates the links between points in the graph

        void link(const Room& R,const Room& Q,Graph& G);
        // Links two rooms in the map making use of the graph of the map
        
        Room generateRoom(const Area A,const std::string id);
        // Generates a room with the given an id 

        void generateRooms(const int n);
        // Given a number n, it tries to generate n rooms

        bool isWithinRoom(const int x,const int y);
        // Returns true if the given point is inside a room, borders excluded, false otherwise

    public:

        Map(const int width,const int height);
        // Creates a new map with the given width and height

        Tile& operator () (const int x, const int y) const;
        // Returns a reference variable to the tile in (x,y)

        Tile& operator () (const Point p) const;
        // Returns a reference variable to the tile in (p.x,p.y)

        int getWidth() const;
        // Returns the width
        
        int getHeight() const;
        // Returns the height

        int generate(const int requiredRooms);
        // Tries to generate a map with the required number of rooms
        // Returns the actual number of generated rooms

        void setVisible(const std::string id,std::unordered_map<std::string,Monster>& monsters,std::unordered_map<std::string,Item>& items);
        // Given an id, it sets the corresponding room visible
        // Every monster and item in the room is set awake/visible as well

        Room pickRoom();
        // Picks a random room in the Rooms map

        void showAround(const int x, const int y);
        // Shows the tiles around the position of the main character

        void freeSpots(const int n,std::unordered_set<Point>& spots,const int r = 1);
        // Given a number of rooms n, a number of repetitions r and a vector of points, it stores n free spots in the
        // map in the vector, with r spots per room (not all rooms)

        std::string placeCharacter(PlayableCharacter& player);
        // Given a main character, places it in a random room in the map
        // Returns the id of the room the player was placed in

        Point freeSpot(const Room R);
        // Given a room, returns a free spot in the room

        Point placeStairs(const tile_t type, const int x = -1, const int y = -1);
        // Places the stairs
        // If the type is UP_STAIRS, they are placed randomly in the map
        // If the type is DOWN_STAIRS, they are placed on x,y
        // The coordinates of the placed stairs are returned

        bool movePlayer(PlayableCharacter& player, const int c);
        // Moves the player to the position specified by input c, if possible
        // Returns true if the player moved, false otherwise

};

#endif
