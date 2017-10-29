#ifndef ROOM_H
#define ROOM_H
#include "Area.h"
#include <string>

class Room : public Area
{
    protected:

        std::string id;
        bool visible;

    public:

        Room();
        // Default constructor

        Room(const Point position, const int width, const int height, const std::string id);
        // Creates a new room given a position for the top left corner, a width, a height and an id

        bool isVisible() const;
        // Returns true if the room is visible

        void setVisible(bool);
        // Sets the visibility of the room

        Point pickPoint() const;
        // Returns a Point in the room

        Point pickAPointAround() const;
        // Returns a randomly picked Point around the room border (not the corners)
        
        std::string getId() const;
        // Returns the id of the room

        void setId(const std::string id);
        // Sets the id of the room

        bool isBorder(const int x, const int y) const;
        // Returns true if the given point is on the border of the room, false otherwise

};

#endif // ROOM_H
