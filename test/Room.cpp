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

void Room::place(Map* M)
{
    for(int i = p.x; i < p.x + width; i++)
        for(int j = p.y; j < p.y + height; j++)
            (*M)(i,j) = PAVEMENT;
    for(int i = p.x - 1; i <= p.x + width; i++)
    {
        (*M)(i,p.y - 1) = ROOM_BORDER;
        (*M)(i,p.y + height) = ROOM_BORDER;
    }
    for(int i = p.y - 1; i <= p.y + height; i++)
    {
        (*M)(p.x - 1,i) = ROOM_BORDER;
        (*M)(p.x + width,i) = ROOM_BORDER;
    }
}

bool Room::overlaps(Map* M)
{
    if((*M)(p.x,p.y) == PAVEMENT || (*M)(p.x,p.y) == ROOM_BORDER)
        return true;
    else
    {
        for(int i = p.x; i < p.x + width; i++)
            if((*M)(i,p.y) == PAVEMENT || (*M)(i,p.y + height - 1) == PAVEMENT || (*M)(i,p.y) == ROOM_BORDER || (*M)(i,p.y + height - 1) == ROOM_BORDER)
                return true;

        for(int i = p.y; i < p.y + height; i++)
            if((*M)(p.x,i) == PAVEMENT || (*M)(p.x + width - 1,i) == PAVEMENT || (*M)(p.x,i) == ROOM_BORDER || (*M)(p.x + width - 1,i) == ROOM_BORDER)
                return true;

        return false;
    }

}

Room generateRoom(int w, int h,int seed)
{
    point p;
    srand(time(NULL)*seed);
    int wLimit, hLimit;

    p.x = rand(2,w - 7);
    p.y = rand(2,h - 7);

    wLimit = w - 2 - p.x < 20 ? w - 2 - p.x : 20;
    hLimit = h - 2 - p.y < 20 ? h - 2 - p.y : 20;
    w = rand(5, wLimit);
    h = rand(5, hLimit);

    Room R(p,w,h);

    return R;

}

point Room::pickAPointAround(Map* M)
{
    using namespace std;    

    int i;
    vector<point> points;
    point q; 
    
    if(p.x > 1)
    {
        q.x = p.x - 1;
        q.y = rand(p.y, p.y + height - 1);
        i = 0;
//        while((*M)(q.x,q.y) == PAVEMENT && i < height)
//        {
//            q.y = p.y + i % height;
//            i++;
//        }
//        if(i < height)
        points.push_back(q);
    }

    if(p.y > 1)
    {
        q.y = p.y - 1;
        q.x = rand(p.x, p.x + width - 1);
        points.push_back(q);
        i = 0;
//        while((*M)(q.x,q.y) == PAVEMENT && i < width)
//        {
//            q.x = p.x + i % width;
//            i++;
//        }
//        if(i < width)
        points.push_back(q);
    }

    if(p.x + width < M->getWidth())
    {
        q.x = p.x + width;
        q.y = rand(p.y, p.y + height - 1);
        points.push_back(q);
//        while((*M)(q.x,q.y) == PAVEMENT && i < height)
//        {
//            q.y = p.y + i % height;
//            i++;
//        }
//        if(i < height)
        points.push_back(q);
    }

    if(p.y + height < M->getHeight())
    {
        q.y = p.y + height;
        q.x = rand(p.x, p.x + width - 1);
        points.push_back(q);
//        while((*M)(q.x,q.y) == PAVEMENT && i < width)
//        {
//            q.x = p.x + i % width;
//            i++;
//        }
//        if(i < width)
        points.push_back(q);
    }

    return pick<point>(points);

}
