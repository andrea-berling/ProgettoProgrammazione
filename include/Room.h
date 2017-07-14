#ifndef ROOM_H
#define ROOM_H
#include "Map.h"

class Room 
{
    protected:

        point p;
        int width;
        int height;

    public:

        Room();
        // Default constructor

        Room(Room& lhs);
        // Copy constructor

        Room(point position, int width, int height);
        // Creates a new room given a position for the top left corner, a width and a height

        void place(Map* M);
        // Given a Map, it places the given room in the map grid

        bool overlaps(Map* M);
        // Returns true if the Room overlaps already occupied space in the given map

        point pickAPointAround(Map* M);
        // Returns a randomly picked point around the room border

};

Room generateRoom(int w, int h,int seed);
// Given the width and the height of an area and a seed, it generates a room with min size 5x5
// and max size 20x20, which does not overlap the area border

#endif
