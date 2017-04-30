#include "Room.h"
#include "utility.hpp"

Room::Room()
{
    p = {-1,-1};
    width = height = -1;
}

Room::Room(Room& lhs) : p(lhs.p), width(lhs.width), height(lhs.height)
{}

Room::Room(point position, int width, int height) : p(position), width(width), height(height)
{}

void Room::place(Map M)
{
    for(int i = p.x; i < p.x + width; i++)
        for(int j = p.y; j < p.y + height; j++)
            M(i,j) = PAVEMENT;
}

bool Room::overlaps(Map M)
{
    if(M(p.x,p.y) == PAVEMENT)
        return true;
    else
    {
        for(int i = p.x; i < p.x + width; i++)
            if(M(i,p.y) == PAVEMENT || M(i,p.y + height - 1) == PAVEMENT)
                return true;

        for(int i = p.y; i < p.y + height; i++)
            if(M(p.x,i) == PAVEMENT || M(p.x + width - 1,i) == PAVEMENT)
                return true;

        return false;
    }

}

Room generateRoom(int w, int h)
{
    point p;

    p.x = rand(1,w - 6);
    p.y = rand(1,h - 6);

    w = rand(5, w - 1 - p.x);
    h = rand(5, h - 1 - p.y);

    Room R(p,w,h);

    return R;

}
