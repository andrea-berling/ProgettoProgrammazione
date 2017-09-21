#include "../include/Room.h"
#include "../include/utility.hpp"

using namespace std;

Room::Room()
{
    p = {-1,-1};
    width = height = -1;
    visible = false;
    id = "";
}

Room::Room(Point position, int width, int height, string id) : p(position), width(width), height(height), visible(false), id(id)
{}

Point Room::getCorner()
{
    return p;
}
// Returns the upper left corner

int Room::getWidth()
{
    return width;
}
// Returns the width of the room

int Room::getHeight()
{
    return height;
}
// Returns the height of the room

Point Room::pickPoint()
{
    Point p;
    p.x = rand(this->p.x + 1,this->p.x + this->width - 2);
    p.y = rand(this->p.y + 1,this->p.y + this->height - 2);
    return p;
}

Point Room::pickAPointAround()
{
    Point q;

    if(rand() % 2 == 0) // choose a Point on the upper or the lower side
    {
        q.y = rand() % 2 == 0 ? p.y : p.y + height - 1;    
        q.x = rand(p.x + 1,p.x + width - 2);
    }
    else // choose a Point on the left or right side
    {
        q.x = rand() % 2 == 0 ? p.x : p.x + width - 1;
        q.y = rand(p.y + 1,p.y + height - 2);
    }

    return q;
}

bool Room::isVisible()
{
    return visible;
}

void Room::setVisible(bool b)
{
    visible = b;
}

string Room::getId()
{
    return id;
}
// Returns the id of the room

void Room::setId(string id)
{
    this->id = id;
}
// Sets the id of the room
