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

        Room(Room& lhs);

        Room(point position, int width, int height);

        void place(Map M);

        bool overlaps(Map M);

};

Room generateRoom(int w, int h);

#endif
