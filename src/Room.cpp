#include "../include/Room.h"
#include "../include/utility.h"

using namespace std;

Room::Room():Area()
{
    visible = false;
    id = "";
}

Room::Room(const Point position, const int width, const int height, const string id) : Area(position,width,height), visible(false), id(id)
{}

Point Room::pickPoint() const
{
    Point p;
    p.x = rand(this->p.x + 1,this->p.x + this->width - 2);
    p.y = rand(this->p.y + 1,this->p.y + this->height - 2);
    return p;
}

Point Room::pickAPointAround() const
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

bool Room::isVisible() const
{
    return visible;
}

void Room::setVisible(bool b)
{
    visible = b;
}

string Room::getId() const
{
    return id;
}
// Returns the id of the room

void Room::setId(string id)
{
    this->id = id;
}
// Sets the id of the room

bool Room::isBorder(const int x, const int y) const
{
    return x == p.x || x == p.x + width - 1 || y == p.y || y == p.y + height - 1;
}
