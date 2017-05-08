#include <limits.h>
#include <math.h>
#include "Graph.h"
#include "Map.h"
#include "Room.h"
#include "../../DataStructures/PriorityQueue/include/priorityqueue.h"
#include "../../DataStructures/HashTable/include/HashTable.h"
#include "../../DataStructures/List/include/List.h"
#include "../../DataStructures/Stack/include/stack.h"
#include <iostream>
#define DEBUG

#ifdef DEBUG
#include <fstream>
ofstream logfile;
#endif

#define INF INT_MAX
#define HEIGHT 37
#define WIDTH 100
#define nil Node()

#ifdef DEBUG
void printMap(Map* M,ofstream& out);
void printGraph(Map* M,Graph* G,ofstream& out);
#endif

void link(Room& R,Room& Q,Graph* G,Map* M);

int w(Node u, Node v);

void populateGraph(Graph* dots,Map* M);

void createLinks(Graph* dots,Map* M);

void shortestPath(Graph* G, Node r,HashTable<Node,Node>* T);

void generateMap(Map* M);

List<Node>* retrievePath(HashTable<Node,Node>* T,Node& one,Node& two);

void printMap(Map* M);

int main()
{
    Map M(WIDTH,HEIGHT);
    generateMap(&M);
    printMap(&M);
}

void populateGraph(Graph* dots,Map* M)
{
    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
        {
            if((*M)(j,i) == WALL || (*M)(j,i) == ROOM_BORDER)
                dots->insertNode(Node(j,i));
        }
}

void createLinks(Graph* dots,Map* M)
{
    for(int i = 1; i < M->getHeight() -1; i++)
        for(int j = 1; j < M->getWidth() - 1; j++)
        {
            Node current(Node(j,i));
            Node right(Node(j + 1,i));
            Node down(Node(j, i + 1));
            if((*M)(current.getPoint()) == WALL || (*M)(current.getPoint()) == ROOM_BORDER)
            {
                if(((*M)(right.getPoint()) == WALL || (*M)(right.getPoint()) == ROOM_BORDER) && j < M->getWidth() - 2)
                    dots->insertEdge(current,right);

                if(((*M)(down.getPoint()) == WALL || (*M)(down.getPoint()) == ROOM_BORDER) && i < M->getHeight() - 2)
                    dots->insertEdge(current,down);
            }
        }
}

void shortestPath(Graph* G, Node r,HashTable<Node,Node>* T)
{
    HashTable<Node,int> d(G->n());
    HashTable<Node,bool> b(G->n());
    Hash::Set<Node>* adj = G->V();
    HashTable<Node,PriorityItem<Node>> pos(G->n());
    PriorityItem<Node> p;
    for(Hash::set_iterator<Node> it = adj->begin(); it != adj->end(); it++)
    {
        if((*it) != r)
        {
            T->insert(*it,nil);
            d.insert(*it,INF);
            b.insert(*it,false);
        }
    }

    T->insert(r,nil);
    d.insert(r,0);
    b.insert(r,true);
    PriorityQueue<Node> S(G->n());
    p = S.insert(r,0);
    pos.insert(r,p);
    while(!S.isEmpty())
    {
        Node u = S.deleteMin();
        b.insert(u,false);
        adj = G->adj(u);
        for(Hash::set_iterator<Node> it = adj->begin(); it != adj->end(); it++)
        {
           if(d[u] + w(u,*it) < d[*it])
           {
               if(!b[*it])
               {
                   p = S.insert(*it,d[u] + w(u,*it));
                   pos.insert(*it,p);
                   b.insert(*it,true);
               }
               else
               {
                   PriorityItem<Node> dec = pos[*it];
                   S.decrease(dec ,d[u] + w(u,*it));
               }
               T->insert(*it,u);
               d.insert(*it,d[u] + w(u,*it));
           }
        }
    }

    delete adj;
}

int w(Node u, Node v)
{
   return abs(u.getPoint().x - v.getPoint().x) + abs(u.getPoint().y - v.getPoint().y);
}

void generateMap(Map* M)
{
    int n = 0;
    int requiredRooms = 10;
    int seed = 2;
    Room R,Q;
    List<Room> rooms;
    Graph dots;

    for(int i = 0; i < M->getWidth(); i++)        // Map initialization
        for(int j = 0; j < M->getHeight(); j++)
            (*M)(i,j) = WALL;

    while(n < requiredRooms)
    {
        seed = 2;
        R = generateRoom(M->getWidth(), M->getHeight(), seed);
        while(R.overlaps(M))
        {
            seed += 2;
            R = generateRoom(M->getWidth(), M->getHeight(), seed);
        }
        rooms.insert(rooms.head(),R);
        R.place(M);
        n++;
    }

    populateGraph(&dots,M);   // needs to be modified
    createLinks(&dots,M);     // this as well

#ifdef DEBUG
        logfile.open("logfile",ios::out);
        printMap(M,logfile);
        printGraph(M,&dots,logfile);
        logfile.close();
#endif

    R = rooms.read(rooms.head());
    rooms.remove(rooms.head());
    Q = rooms.read(rooms.head());
    while(!rooms.empty())
    {
        link(R,Q,&dots,M);
#ifdef DEBUG
        logfile.open("logfile",ios::out);
        printMap(M,logfile);
        printGraph(M,&dots,logfile);
        logfile.close();
#endif
        R = rooms.read(rooms.head());
        rooms.remove(rooms.head());
        if(!rooms.empty())
            Q = rooms.read(rooms.head());
    }
    
}

void link(Room& R,Room& Q,Graph* G,Map* M)
{
    point p = R.pickAPointAround(M);
    point q = Q.pickAPointAround(M);
    Node one(p);
    Node two(q);
    List<Node>* steps = new List<Node>();
    HashTable<Node,Node> T(6143);

    if(one != two)
    {
        shortestPath(G,one,&T);
        steps = retrievePath(&T,one,two);
    }
    else
        steps->insert(steps->head(),one);

    for(List<Node>* it = steps->head(); !steps->finished(it); it = steps->next(it))
    {
        if((steps->read(it)).getPoint() != nil)
            (*M)((steps->read(it)).getPoint()) = PAVEMENT;
    }

    steps->destroy();
    delete steps;
}

List<Node>* retrievePath(HashTable<Node,Node>* T,Node& one,Node& two)
{
    List<Node>* l = new List<Node>();    
    
    l->insert(l->head(),two);
    Node p = (*T)[two];
#ifdef DEBUG
    int i = 0;
#endif

    while(p != one)
    {
        l->insert(l->head(),p);
        p = (*T)[p];
#ifdef DEBUG
        i++;
        if(i > 10000)
        {
            cerr << "Too many tries, there's no link between one and two" << endl;
        logfile.close();
            exit(1);
        }
#endif
    }

    l->insert(l->head(),one);

    return l;
}

void printMap(Map* M)
{
    using namespace std;

    for( int i = 0; i < M->getHeight(); i++)
    {
        for (int j = 0; j < M->getWidth(); j++)
        {
            if ((*M)(j,i) == WALL)
                cout << "#";
            else if ((*M)(j,i) == ROOM_BORDER)
                cout << "%";
            else if (((*M)(j,i) == PAVEMENT) || ((*M)(j,i) == VOID))
                cout << " ";
        }
        cout << endl;
    }
    cout << endl;
}

#ifdef DEBUG
void printMap(Map* M,ofstream& out)
{
    for( int i = 0; i < M->getHeight(); i++)
    {
        for (int j = 0; j < M->getWidth(); j++)
        {
            if ((*M)(j,i) == WALL)
                out << "#";
            else if ((*M)(j,i) == ROOM_BORDER)
                out << "%";
            else if (((*M)(j,i) == PAVEMENT) || ((*M)(j,i) == VOID))
                out << " ";
        }
        out << endl;
    }
    out << endl;
}

void printGraph(Map* M,Graph* G,ofstream& out)
{
    for( int i = 0; i < M->getHeight(); i++)
    {
        for (int j = 0; j < M->getWidth(); j++)
        {
            if (G->contains(Node(j,i)))
                out << "#";
            else
                out << " ";
        }
        out << endl;
    }
    out << endl;
}
#endif
