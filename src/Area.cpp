#include "../include/Area.h"
#include "../include/utility.h"

Area::Area():p({-1,-1}),width(-1),height(-1)
{}

Area::Area(Point position, int width, int height) : p(position), width(width), height(height)
{}


Area::Area(const Area& A)
{
    p = A.p;
    width = A.width;
    height = A.height;
}
// Copy constructor

Point Area::getCorner()
{
    return p;
}
// Returns the upper left corner

int Area::getWidth()
{
    return width;
}
// Returns the width of the room

int Area::getHeight()
{
    return height;
}
// Returns the height of the room

void Area::split(Area& A1, Area& A2, bool vertical)
{
    int offset,x1,y1,w1,h1,x2,y2,w2,h2;
    if(vertical)
    {
        offset = width / 3;
        int xsplit = p.x + offset + rand(0,offset);

        x1 = p.x;
        y1 = p.y;
        h1 = height;
        w1 = xsplit - p.x;
        
        x2 = xsplit;
        y2 = p.y;
        h2 = height;
        w2 = width - (xsplit - p.x);
    }
    else
    {
        offset = height / 3;
        int ysplit = p.y + offset + rand(0,offset);

        x1 = p.x;
        y1 = p.y;
        h1 = ysplit - p.y;
        w1 = width;
        
        x2 = p.x;
        y2 = ysplit;
        h2 = height - (ysplit - p.y);
        w2 = width;
    }
    A1 = Area({x1,y1},w1,h1);
    A2 = Area({x2,y2},w2,h2);
}

void Area::splitInHalf(Area& A1, Area& A2, bool vertical)
{
    int x1,y1,w1,h1,x2,y2,w2,h2;
    if(vertical)
    {
        int xsplit = p.x + width / 2;

        x1 = p.x;
        y1 = p.y;
        h1 = height;
        w1 = xsplit - p.x;
        
        x2 = xsplit;
        y2 = p.y;
        h2 = height;
        w2 = width - (xsplit - p.x);
    }
    else
    {
        int ysplit = p.y + height / 2;

        x1 = p.x;
        y1 = p.y;
        h1 = ysplit - p.y;
        w1 = width;
        
        x2 = p.x;
        y2 = ysplit;
        h2 = height - (ysplit - p.y);
        w2 = width;
    }
    A1 = Area({x1,y1},w1,h1);
    A2 = Area({x2,y2},w2,h2);
}

namespace std
{
    size_t hash<Area>::operator()(Area A) const
    {
        return hash<Point>()(A.getCorner()) ^ hash<int>()(A.getWidth() & ~A.getHeight());
    }
}

bool operator==(Area A1,Area A2)
{
    return (A1.p == A2.p && A1.width == A2.width && A1.height == A2.height);
}
