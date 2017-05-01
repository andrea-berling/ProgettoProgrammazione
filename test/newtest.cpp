#include <limits.h>
#include <math.h>
#include "Graph.h"
#include "Map.h"
#include "Room.h"
#include "utility.hpp"
#include "../../DataStructures/PriorityQueue/include/priorityqueue.h"
#include "../../DataStructures/HashTable/include/HashTable.h"
#include "../../DataStructures/List/include/List.h"

#define INF INT_MAX
#define HEIGHT 37
#define WIDTH 100
#define nil Node()

void link(Room& R,Room& Q,Graph& G,Map& M);

int w(Node u, Node v);

void populateGraph(Graph& dots,const Map& M);

void createLinks(Graph& dots,const Map& M);

void shortestPath(Graph& G, Node r,HashTable<Node,Node>& T);

void generateMap(Map& M);

List<Node>* retrievePath(HashTable<Node,Node>& T,Node& one,Node& two);

int main()
{
    Graph dots;
    Node r(1,1);
    HashTable<Node,Node> T;

    populateGraph(&dots);
    T = HashTable<Node,Node>(dots.n());
    createLinks(&dots);
    shortestPath(&dots,r,&T);
}

void populateGraph(Graph& dots,const Map& M)
{
    for(int i = 1; i < HEIGHT - 1; i++)
        for(int j = 1; j < WIDTH - 1; j++)
        {
            if(M(j,i) == WALL)
                dots->insertNode(Node(j,i));
        }
}

void createLinks(Graph& dots,const Map& M)
{
    for(int i = 1; i < M.getHeight() -1; i++)
        for(int j = 1; j < M.getWidth() - 1; j++)
        {
            Node current(Node(j,i));
            Node right(Node(j + 1,i));
            Node down(Node(j, i + 1));
            if(M(current.getPoint()) == WALL)
            {
                if(M(right.getPoint()) == WALL && j < M.getWidth() - 2)
                    dots->insertEdge(right);

                if(M(down.getPoint()) == WALL && i < M.getHeight() - 2)
                    dots->insertEdge(down);
            }
        }
}

void shortestPath(Graph& G, Node r,HashTable<Node,Node>& T)
{
    HashTable<Node,int> d(G.n());
    HashTable<Node,bool> b(G.n());
    Hash::Set<Node>* adj = G.adj(r);
    HashTable<Node,PriorityItem<Node>> pos(G.n());
    PriorityItem<Node> p;
    for(Hash::set_iterator<Node> it = adj->begin(); it != adj->end(); it++)
    {
        if((*it) != r)
        {
            T.insert(*it,nil);
            d.insert(*it,INF);
            b.insert(*it,false);
        }
    }

    T.insert(r,nil);
    d.insert(r,0);
    b.insert(r,true);
    PriorityQueue<Node> S(G.n());
    p = S.insert(r,0);
    pos.insert(r,p);
    while(!S.isEmpty())
    {
        Node u = S.deleteMin();
        b.insert(u,false);
        adj = G.adj(u);
        for(Hash::set_iterator<Node> it = adj->begin(); it != adj->end(); it++)
        {
           if(d.lookup(u) + w(u,*it) < d.lookup(*it))
           {
               if(!b.lookup(*it))
               {
                   p = S.insert(*it,d.lookup(u) + w(u,*it));
                   pos.insert(*it,p);
                   b.insert(*it,true);
               }
               else
               {
                   PriorityItem<Node> dec = pos.lookup(*it);
                   S.decrease(dec ,d.lookup(u) + w(u,*it));
               }
               T.insert(*it,u);
               d.insert(*it,d.lookup(u) + w(u,*it));
           }
        }
    }

    delete adj;
}

int w(Node u, Node v)
{
   return abs(u.getPoint().x - v.getPoint().x) + abs(u.getPoint().y - v.getPoint().y);
}

void generateMap(Map& M)
{
    int n = 0;
    int requiredRooms = 7;
    Room R,Q;
    List<Room> rooms;
    Graph dots;

    for(int i = 0; i < M.getWidth(); i++)        // Map initialization
        for(int j = 0; j < M.getHeight(); j++)
            M(i,j) = WALL;

    while(n < requiredRooms)
    {
        R = generateRoom(M.getWidth(), M.getHeight());
        while(!R.overlaps(M))
        {
            R = generateRoom(M.getWidth(), M.getHeight());
        }
        rooms.insert(rooms.head(),R);
        R.place(M);
        n++;
    }

    populateGraph(dots,M);   // needs to be modified
    createLinks(dots,M);     // this as well

    while(!rooms.empty())
    {
        R = rooms.read(rooms.head());
        Q = rooms.read(rooms.next(rooms.head()));
        link(R,Q,G,M);
        rooms.remove(rooms.head());
    }
}

void link(Room& R,Room& Q,Graph& G,Map& M)
{
    point p = R.pickAPointAround(M);
    point q = Q.pickAPointAround(M);
    Node one(p);
    Node two(q);
    List<Node>* steps = new List<Node>();
    HashTable<Node,Node> T;

    shortestPath(G,one,T);
    steps = retrievePath(T,one,two);

    for(List<Node>* it = steps->head(); it != steps; it = steps->next(it))
    {
        M((steps->read(it)).getPoint()) = PAVEMENT;
    }

    steps->destroy();
}

List<Node>* retrievePath(HashTable<Node,Node>& T,Node& one,Node& two)
{
    
}
