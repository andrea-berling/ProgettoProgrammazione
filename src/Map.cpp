#include "../include/Map.h"
#include "../include/utility.hpp"
#include <iostream>

using namespace std;

Map::Map():grid(0,0),width(0),height(0),rooms(47)
{}
// Defualt constructor

Map::Map(int width, int height) : grid(height, width), width(width), height(height),rooms(47)
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
    rooms.insert({id,R});
}

Room Map::pickRoom()
{
    HashTable<string,Room>::iterator it = rooms.begin();
    Room R = (*it).value;
    return R;
}

void Map::setVisible(string id)
{
    Room R = rooms[id];
    R.setVisible(true);
    rooms.insert({R.getId(),R});
    Point p = R.getCorner();    
    int width = R.getWidth();
    int height = R.getHeight();
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
    int seed = 2;
    int roomID = 0;
    Room R,Q;
    Dequeue<Room> rooms;
    Graph dots;

    for(int i = 0; i < width; i++)        // Map initialization
        for(int j = 0; j < height; j++)
        {
            (*this)(i,j).setType(WALL);
            (*this)(i,j).setVisible(false);
        }

    while(n < requiredRooms)
    {
        seed = 2;
        string id = "room" + to_string(roomID);
        roomID++;
        R = generateRoom(id, seed);
        while(overlaps(R))
        {
            seed += 2;
            R = generateRoom(id, seed);
        }
        rooms.push(R);
        addRoom(R,id);
        place(R);
        n++;
    }

    populateGraph(dots);
    createLinks(dots);

    R = rooms.pop();
    Q = rooms.top();
    while(!rooms.empty())
    {
        link(R,Q,dots); // to add to map class
        R = rooms.pop();
        if(!rooms.empty())
            Q = rooms.top();
    }
}

Room Map::generateRoom(string id, int seed)
{
    Point p;
    srand(time(NULL)*seed);
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
    for(int i = 0; i < height; i++)
        for(int j = 0; j < width; j++)
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
    List<Point>* steps;
    HashTable<Point,Point> T(6143);

    connectToMap(G,p,toRemove1);
    connectToMap(G,q,toRemove2);

    if(p != q)
    {
        shortestPath(G,p,T);
        steps = retrievePath(T,p,q);
    }
    else
        steps->insert(p);

    for(Point p : *steps)
    {
        if(p != Point())
            (*this)(p).setType(HALLWAY);
    }

    disconnectFromMap(G,p,toRemove1);
    disconnectFromMap(G,q,toRemove2);

    delete steps;
}

void shortestPath(Graph& G, Point r,HashTable<Point,Point>& T)
{
    HashTable<Point,int> d(G.n());
    HashTable<Point,bool> b(G.n());
    HashSet<Point>* adj = G.V();
    Dequeue<Point> S;
    for(Point u : *adj)
    {
        if(u != r)
        {
            T.insert({u,Point()});
            d.insert({u,INF});
            b.insert({u,false});
        }
    }

    delete adj;
    T.insert({r,Point()});
    d.insert({r,0});
    b.insert({r,true});
    S.push(r);
    while(!S.empty())
    {
        Point u = S.pop();
        b.insert({u,false});
        adj = G.adj(u);
        for(Point v : *adj)
        {
            if(d[u] + w(u,v) < d[v])
            {
                if(!b[v])
                {
                    if(d[v] == INF)
                        S.push_back(v);
                    else
                        S.push(v);
                    b.insert({v,true});
                }
                T.insert({v,u});
                d.insert({v,d[u] + w(u,v)});
            }
        }
        delete adj;
    }
}

List<Point>* retrievePath(HashTable<Point,Point>& T,Point& one,Point& two)
{
    List<Point>* l = new List<Point>();
    
    
    Point p = two;

    while(p != Point())
    {
        l->insert(p);
        p = T[p];
    }

    return l;
}

int w(Point p, Point q)
{
   return abs(p.x - q.x) + abs(p.y - q.y);
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
