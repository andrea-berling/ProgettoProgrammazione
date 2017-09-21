#ifndef ROOM_H
#define ROOM_H
#include "../include/Graph.h"
#include <string>

class Room 
{
    protected:

        Point p;
        int width;
        int height;
        std::string id;
        bool visible;

    public:

        Room();
        // Default constructor

        Room(Point position, int width, int height, std::string id);
        // Creates a new room given a position for the top left corner, a width, a height and an id

        bool isVisible();
        // Returns true if the room is visible

        void setVisible(bool);
        // Sets the visibility of the room

        Point pickPoint();
        // Picks a Point in the room

        Point pickAPointAround();
        // Returns a randomly picked Point around the room border (not the corners)
        
        Point getCorner();
        // Returns the upper left corner

        int getWidth();
        // Returns the width of the room

        int getHeight();
        // Returns the height of the room

        std::string getId();
        // Returns the id of the room

        void setId(std::string id);
        // Sets the id of the room
};

#endif
