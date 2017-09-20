#include "../include/Map.h"
#include "../include/utility.hpp"
#include <iostream>

using namespace std;

Map::Map(int width, int height) : grid(height, width), width(width), height(height), rooms(47)
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
    int width = R.getWidth();
    int height = R.getHeight();

    for(int i = p.x; i < p.x + width; i++)
        for(int j = p.y; j < p.y + height; j++)
        {
            if((i != p.x && i != p.x + width - 1) && (j != p.y && j != p.y + height - 1))
                (*this)(i,j).setType(PAVEMENT);
            else
                (*this)(i,j).setType(ROOM_BORDER);
            (*this)(i,j).setId(R.getId());
            (*this)(i,j).setVisible(R.isVisible());
        }
}

bool Map::overlaps(Room& R)
{
    Point p = R.getCorner();
    int width = R.getWidth();
    int height = R.getHeight();
    tile_t type = (*this)(p.x,p.y).getType();
    bool corner = type == PAVEMENT || type == ROOM_BORDER;  // the corner overlaps another room
    if(p.x > 0)
        corner = corner || (*this)(p.x - 1,p.y).getType() == ROOM_BORDER; // the corner is adjacent to a room which is to its left
    if(p.y > 0)
        corner = corner || (*this)(p.x,p.y - 1).getType() == ROOM_BORDER; // the corner is adjacent to a room which is above it
    if(corner)
        return true;
    else
    {
        for(int i = p.x; i < p.x + width; i++)
        {
            bool up,down;
            up = (*this)(i,p.y).getType() == PAVEMENT || (*this)(i,p.y).getType() == ROOM_BORDER; // The block overlaps another room
            if(p.y > 0)
                up = up || (*this)(i,p.y - 1).getType() == ROOM_BORDER;   // The block is adjacent to a room which is above it
            down = (*this)(i,p.y + height - 1).getType() == PAVEMENT || (*this)(i,p.y + height - 1).getType() == ROOM_BORDER;
            if(p.y + height < this->height)
                down = down || (*this)(i,p.y + height).getType() == ROOM_BORDER; // The block is adjacent to a room which is under it
            if(up || down)
                return true;
        }

        for(int i = p.y; i < p.y + height; i++)
        {
            bool left,right;
            left = (*this)(p.x,i).getType() == PAVEMENT || (*this)(p.x,i).getType() == ROOM_BORDER;
            if(p.x > 0)
                left = left || (*this)(p.x - 1,i).getType() == ROOM_BORDER; // The block is adjacent to a room which is to its left
            right = (*this)(p.x + width - 1,i).getType() == PAVEMENT || (*this)(p.x + width - 1,i).getType() == ROOM_BORDER;
            if(p.x + width < this->width)
                right = right || (*this)(p.x + width,i).getType() == ROOM_BORDER; // The block is adjacent to a room which is to its right
            if(left || right)
                return true;
        }

        /*
        for(int i = p.x; i < p.x + width; i++)
            for(int j = p.y; j < p.y + height; j++)
                if((*this)(i,j).getType() == PAVEMENT || (*this)(i,j).getType() == ROOM_BORDER)
                    return true;
                    */
        return false;
    }

}

void Map::addRoom(Room& R,string id)
{
    rooms[id] = R;
}

Room Map::pickRoom()
{
    int index = rand(0,rooms.size()-1);
    unordered_map<string,Room>::iterator it = rooms.begin();

    while(index > 0)
    {
        ++it;
        --index;
    }

    return (*it).second;
}

void Map::setVisible(string id)
{
    rooms[id].setVisible(true);
    Point p = rooms[id].getCorner();    
    int width = rooms[id].getWidth();
    int height = rooms[id].getHeight();
    for(int i = p.x; i < p.x + width; i++)
        for(int j = p.y; j < p.y + height; j++)
            (*this)(i,j).setVisible(true);
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
    int n = 0;
    int roomID = 0;
    Room R,Q;
    deque<Room> rooms;
    Graph dots;

    for(int i = 0; i < width; i++)        // Map initialization
        for(int j = 0; j < height; j++)
        {
            (*this)(i,j).setType(WALL);
            (*this)(i,j).setVisible(false);
        }

    while(n < requiredRooms)
    {
        string id = "room" + to_string(roomID);
        roomID++;
        R = generateRoom(id);
        while(overlaps(R))
        {
            R = generateRoom(id);
        }
        rooms.push_front(R);
        addRoom(R,id);
        place(R);
        n++;
    }

    populateGraph(dots);
    createLinks(dots);

    R = *(rooms.begin());
    rooms.pop_front();
    Q = *(rooms.begin());
    while(!rooms.empty())
    {
        link(R,Q,dots); // to add to map class
        R = *(rooms.begin());
        rooms.pop_front();
        if(!rooms.empty())
            Q = *(rooms.begin());
    }
}

Room Map::generateRoom(string id)
{
    Point p;
    int wLimit, hLimit;
    int w,h;

    p.x = rand(2,width - 9);
    p.y = rand(2,height - 9);

    wLimit = width - 2 - p.x < 20 ? width - 2 - p.x : 20;
    hLimit = height - 2 - p.y < 20 ? height - 2 - p.y : 20;
    w = rand(7, wLimit);
    h = rand(7, hLimit);

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
    Point toRemove1;
    Point toRemove2;
    list<Point> steps;
    unordered_map<Point,Point> T(6143);

    connectToMap(G,p,toRemove1);
    connectToMap(G,q,toRemove2);

    if(p != q)
    {
        shortestPath(G,p,T);
        retrievePath(steps,T,p,q);
    }
    else
        steps.insert(steps.begin(),p);

    for(Point p : steps)
    {
        if(p != Point())
            (*this)(p).setType(HALLWAY);
    }

    disconnectFromMap(G,p,toRemove1);
    disconnectFromMap(G,q,toRemove2);
}

void Map::connectToMap(Graph& G, Point& p, Point& q)
{
    G.insertPoint(p);
    if((*this)(p).getType() == ROOM_BORDER)
    {
        if((*this)(p.x - 1, p.y).getType() == WALL || (*this)(p.x - 1, p.y).getType() == HALLWAY)
            q = {p.x - 1,p.y};
        else if((*this)(p.x + 1, p.y).getType() == WALL || (*this)(p.x + 1, p.y).getType() == HALLWAY)
            q = {p.x + 1,p.y};
        else if((*this)(p.x, p.y - 1).getType() == WALL || (*this)(p.x, p.y - 1).getType() == HALLWAY)
            q = {p.x,p.y - 1};
        else if((*this)(p.x, p.y + 1).getType() == WALL || (*this)(p.x, p.y + 1).getType() == HALLWAY)
            q = {p.x,p.y + 1};
        G.insertPoint(q);
        G.insertEdge(p,q);
    }
}

void Map::disconnectFromMap(Graph& G, Point& p, Point& q)
{
    G.deleteEdge(p,q);
    G.deletePoint(p);
    G.deletePoint(q);
}


/*
void Map::spawnMonsters(int _monsters,unordered_map<string,Monster>& monsters)
{
    unordered_map<string,Room>::iterator it = --(rooms.end());    // The last room created
    int count = 0;

    for(int i = 0; i < _monsters; i++) 
    {
        int x = (*it).key.getCorner().x;
        int y = (*it).key.getCorner().y;
        int height = (*it).key.getHeight();
        int width = (*it).key.getWidth();
        Point position(rand(x+1,x+width-1),rand(y+1,y+height-1));
        string name = "monster" + toString(count);
        Monster m(position,name); // The creation of the monster, depends on the constructor
        monserts.insert({name,m});

        --it;
        --it; // skip one room
        ++count;
    }
}

void Map::spawnItems(int _items,unordered_map<Point p,Item>& items)
{
    unordered_map<string,Room>::iterator it = --(rooms.end());    // The last room created
    int count = 0;

    for(int i = 0; i < _items; i++) 
    {
        int x = (*it).key.getCorner().x;
        int y = (*it).key.getCorner().y;
        int height = (*it).key.getHeight();
        int width = (*it).key.getWidth();
        Point position;

        do
        {
            position = Point(rand(x+1,x+width-1),rand(y+1,y+height-1));
        }
        while(!isFree(position.x,position.y));

        string name = "item" + toString(count);
        Item item(position,name); // The creation of the item, depends on the constructor
        items.insert({name,m});
        placeItem(item);

        --it;
        --it; // skip one room
        ++count;
    }
}

bool Map::isFree(int x, int y)
{
    return itemsLayer(y,x) == VOID // need to implement the VOID item
}

void Map::placeItem(Item item, int x, int y)
{
    itemsLayer[y][x] = item;
}
*/
