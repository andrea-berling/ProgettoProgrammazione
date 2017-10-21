#include "../include/Map.h"
#include "../include/utility.h"
#include <unordered_set>
#ifdef DEBUG
#include <cstdlib>
#include <iostream>
#include <fstream>
#endif

using namespace std;

Map::Map(int width, int height) : grid(height, width), width(width), height(height)
{}
// Creates a new map with the given # of rows and columns


Tile& Map::operator () (int x, int y)
{
    return grid(y,x);
}
// Returns a reference variable to Map(x,y)

Tile& Map::operator () (Point p)
{
    return grid(p.y,p.x);
}
// Returns a reference variable to Map(x,y)

int Map::getWidth()
{
    return this->width;
}

int Map::getHeight()
{
    return this->height;
}

void Map::place(Room& R)
{
    Point p = R.getCorner();
    int RWidth = R.getWidth();
    int RHeight = R.getHeight();

    for(int i = p.x; i < p.x + RWidth; i++)
        for(int j = p.y; j < p.y + RHeight; j++)
        {
            if((i != p.x && i != p.x + RWidth - 1) && (j != p.y && j != p.y + RHeight - 1))
                (*this)(i,j).setType(PAVEMENT);
            else
                (*this)(i,j).setType(ROOM_BORDER);
            (*this)(i,j).setId(R.getId());
            (*this)(i,j).setVisible(R.isVisible());
        }
}

Room Map::pickRoom()
{
    int index = rand(0,rooms.size()-1);
    unordered_map<string,Room>::iterator it = rooms.begin();

    for(; index > 0; index--)
        ++it;

    return (*it).second;
}

void Map::setVisible(string id,std::unordered_map<std::string,Monster>& monsters,std::unordered_map<std::string,Item>& items)
{
    rooms[id].setVisible(true);
    Point p = rooms[id].getCorner();    
    int width = rooms[id].getWidth();
    int height = rooms[id].getHeight();
    for(int i = p.x; i < p.x + width; i++)
        for(int j = p.y; j < p.y + height; j++)
        {
            (*this)(i,j).setVisible(true);
            if((*this)(i,j).getUpperLayer() != "")   // Wake up monsters and show items
            {
                if((*this)(i,j).getUpperLayer()[0] == 'm')
                    monsters[(*this)(i,j).getUpperLayer()].wakeUp(true);
                else
                    items[(*this)(i,j).getUpperLayer()].setVisible(true);
            }
        }
}

void Map::showAround(int x, int y)
{
    (*this)(x + 1,y).setVisible(true);
    (*this)(x - 1,y).setVisible(true);
    (*this)(x,y + 1).setVisible(true);
    (*this)(x,y - 1).setVisible(true);
}

void Map::generate(int requiredRooms)
{
    unordered_map<string,Room>::iterator it;
    Room R,Q;
    Graph dots;

    for(int i = 0; i < width; i++)        // Map initialization
        for(int j = 0; j < height; j++)
        {
            (*this)(i,j).setType(WALL);
            (*this)(i,j).setVisible(false);
        }

    generateRooms(requiredRooms);
    populateGraph(dots);
    createLinks(dots);

    it = rooms.begin();
    R = (*it).second;
    ++it;
    while(it != rooms.end())
    {
        Q = (*it).second;
        ++it;
        link(R,Q,dots);
        R = Q;
    }
}

Room Map::generateRoom(Area A,string id)
{
    Point p;
    int x = A.getCorner().x;
    int y = A.getCorner().y;
    int width = A.getWidth();
    int height = A.getHeight();
    int wMax, hMax;
    int w,h;

    p.x = rand(x + 1, x + width - 2 - 7); // a room has a minimum size of 7x7 and a max size of 20x20
    p.y = rand(y + 1, y + height - 2 - 7); 
    
    int freeXSpace = x + width - 2 - p.x;
    int freeYSpace = y + height - 2 - p.y;

    if(20 < freeXSpace)
        wMax = 20;
    else 
        wMax = freeXSpace;

    if(20 < freeYSpace)
        hMax = 20;
    else 
        hMax = freeYSpace;

    w = rand(7, wMax);
    h = rand(7, hMax);

    return Room(p,w,h,id);
}

void Map::populateGraph(Graph& G)
{
    for(int i = 1; i < height - 1; i++)
        for(int j = 1; j < width - 1; j++)
        {
            if((*this)(j,i).getType() == WALL)
                G.insertPoint({j,i});
        }
}

void Map::createLinks(Graph& G)
{
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
        {
            Point current = {j, i};
            Point right = {j + 1, i};
            Point down = {j, i + 1};
            if((*this)(current).getType() == WALL)
            {
                if(j < width - 1 && (*this)(right).getType() == WALL)
                    G.insertEdge(current,right);

                if(i < height - 1 && (*this)(down).getType() == WALL)
                    G.insertEdge(current,down);
            }
        }
}

void Map::link(Room& R,Room& Q,Graph& G)
{
    Point p = R.pickAPointAround();
    Point q = Q.pickAPointAround();
    Point p2;   // A point adjacent to p in the map and which is in the graph
    Point q2;
    list<Point> steps;
    unordered_map<Point,Point> T(6143);

    connectToMap(G,p,p2);
    connectToMap(G,q,q2);

    shortestPath(G,p,T);
    retrievePath(steps,T,p,q);

    for(Point p : steps)
    {
        (*this)(p).setType(HALLWAY);
    }

    G.deletePoint(p);
    G.deletePoint(q);
}

void Map::connectToMap(Graph& G, Point& p, Point& q)
{
    G.insertPoint(p);
    if((*this)(p.x-1,p.y).isWalkable() && (*this)(p.x-1,p.y).getType() != HALLWAY) // The room is on the left of the point
        q = {p.x+1,p.y};
    else if((*this)(p.x+1,p.y).isWalkable() && (*this)(p.x+1,p.y).getType() != HALLWAY) // The room is on the right of the point
        q = {p.x-1,p.y};
    else if((*this)(p.x,p.y-1).isWalkable() && (*this)(p.x,p.y-1).getType() != HALLWAY) // And so on
        q = {p.x,p.y+1};
    else if((*this)(p.x,p.y+1).isWalkable() && (*this)(p.x,p.y+1).getType() != HALLWAY)
        q = {p.x,p.y-1};
    G.insertEdge(p,q);
}

void Map::freeSpots(int n,unordered_set<Point>& spots,int r)
{
    unordered_map<string,Room>::iterator it;
    int permutation[n];
    generateKPermutation(permutation,0,rooms.size()-1,n);

    for(int i = 0; i < n; i++) 
    {
        it = rooms.begin();
        for(int j = 0; j < permutation[i]; j++)
            ++it;

        for(int k = 0; k < r; k++)
        {
            Point position;

            do
            {
                position = freeSpot((*it).second);
            }
            while(spots.find(position) != spots.end());
            spots.insert(position);
        }
    }
}

std::string Map::placeCharacter(PlayableCharacter& player)
{
    Room R = pickRoom();
    Point p;
    int x = R.getCorner().x;
    int y = R.getCorner().y;
    int height = R.getHeight();
    int width = R.getWidth();
    do
    {
        p = Point(rand(x+1,x+width-2),rand(y+1,y+height-2));
    }
    while((*this)(p.x,p.y).getUpperLayer() != "");

    player.setPosition(p.x,p.y);

    return R.getId();
}

void Map::generateRooms(int n)
{
    Area A({1,1},width-1,height-1);
    unordered_set<Area> areas,toRemove,toInsert;
    bool vertical = true;
    int i = 1;
    int roomId = 0;
    string id;
    int tries = 0;

    areas.insert(A);
    while(i < n && tries < 500)
    {
        toRemove.clear();
        toInsert.clear();
        for(Area A : areas)
        {
            if(i < n) 
            {
                bool split = false;
                Area A1,A2;
                if ((vertical && (A.getWidth()/3 > 10)) || (!vertical && (A.getHeight()/3 > 10)))
                {
                    A.split(A1,A2,vertical);
                    split = true;
                }
                else if ((vertical && (A.getWidth()/2 > 10)) || (!vertical && (A.getHeight()/2 > 10)))
                {
                    A.splitInHalf(A1,A2,vertical);
                    split = true;
                }
                if(split)
                {
                    toInsert.insert(A1);
                    toInsert.insert(A2);
                    i++;
                    toRemove.insert(A);
                }
                tries++;
            }
        }
        for(Area A : toRemove)
            areas.erase(A);
        for(Area A : toInsert)
            areas.insert(A);
        vertical = !vertical;
    }
    // Generate rooms for each area
    for(Area A : areas)
    {
        id = "room" + to_string(roomId);
        roomId++;
        Room R = generateRoom(A,id);
        rooms[id] = R;
        place(R);
    }
}
// Given a number n, it generates n rooms

Point Map::freeSpot(Room R)
{
    int x = R.getCorner().x;
    int y = R.getCorner().y;
    int height = R.getHeight();
    int width = R.getWidth();
    Point p;

    do
    {
        p = Point(rand(x+1,x+width-2),rand(y+1,y+height-2));
    }
    while((*this)(p.x,p.y).getUpperLayer() != "");

    return p;
}
