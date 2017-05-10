#include <limits.h>
#include <math.h>
#include "Graph.h"
#include "Map.h"
#include "Room.h"
#include "../../DataStructures/Dequeue/include/dequeue.h"
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
    for(int i = 0; i < M->getHeight(); i++)
        for(int j = 0; j < M->getWidth(); j++)
        {
            Node current(Node(j,i));
            Node right(Node(j + 1,i));
            Node down(Node(j, i + 1));
            if((*M)(current.getPoint()) == WALL || (*M)(current.getPoint()) == ROOM_BORDER)
            {
                if(j < M->getWidth() - 1 && ((*M)(right.getPoint()) == WALL || (*M)(right.getPoint()) == ROOM_BORDER))
                    dots->insertEdge(current,right);

                if(i < M->getHeight() - 1 && ((*M)(down.getPoint()) == WALL || (*M)(down.getPoint()) == ROOM_BORDER))
                    dots->insertEdge(current,down);
            }
        }
}

void shortestPath(Graph* G, Node r,HashTable<Node,Node>* T)
{
    HashTable<Node,int> d(G->n());
    HashTable<Node,bool> b(G->n());
    Hash::Set<Node>* adj = G->V();
    Dequeue<Node> S;
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
    S.push(r);
    while(!S.empty())
    {
        Node u = S.pop();
        b.insert(u,false);
        adj = G->adj(u);
        for(Hash::set_iterator<Node> it = adj->begin(); it != adj->end(); it++)
        {
           if(d[u] + w(u,*it) < d[*it])
           {
               if(!b[*it])
               {
                   if(d[*it] == INF)
                       S.push_back(*it);
                   else
                       S.push(*it);
                   b.insert(*it,true);
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
    Stack<Room> rooms;
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
        rooms.push(R);
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

    R = rooms.pop();
    Q = rooms.top();
    while(!rooms.isEmpty())
    {
        link(R,Q,&dots,M);
#ifdef DEBUG
        logfile.open("logfile",ios::out);
        printMap(M,logfile);
        printGraph(M,&dots,logfile);
        logfile.close();
#endif
        R = rooms.pop();
        if(!rooms.isEmpty())
            Q = rooms.top();
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
#ifdef DEBUG
    if(!G->contains(one) || !G->contains(two))
    {
        cerr << "Error, a point that is not in the graph was generated" << endl;
        exit(1);
    }
#endif

    if(one != two)
    {
        shortestPath(G,one,&T);
        steps = retrievePath(&T,one,two);
    }
    else
        steps->insert(one);

    for(List_iterator<Node> it = steps->begin(); it != steps->end(); it++)
    {
        if((*it).getPoint() != nil)
            (*M)((*it).getPoint()) = PAVEMENT;
    }

    delete steps;
}

List<Node>* retrievePath(HashTable<Node,Node>* T,Node& one,Node& two)
{
    List<Node>* l = new List<Node>();    
    
    l->insert(two);
    Node p = (*T)[two];
#ifdef DEBUG
    int i = 0;
#endif

    while(p != one)
    {
        l->insert(p);
        p = (*T)[p];
#ifdef DEBUG
        i++;
        if(i > 50000)
        {
            cerr << "Too many tries, there's no link between one and two" << endl;
        logfile.close();
            exit(1);
        }
#endif
    }

    l->insert(one);

    return l;
}

void printMap(Map* M)
{
    using namespace std;

    for( int i = 0; i < M->getHeight(); i++)
    {
        for (int j = 0; j < M->getWidth(); j++)
        {
            if ((*M)(j,i) == WALL || (*M)(j,i) == ROOM_BORDER)
                cout << "#";
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
            if ((*M)(j,i) == WALL || (*M)(j,i) == ROOM_BORDER)
                out << "#";
            else if (((*M)(j,i) == PAVEMENT) || ((*M)(j,i) == VOID))
                out << " ";
        }
        out << endl;
    }
    out << endl;
}

void printGraph(Map* M,Graph* G,ofstream& out)
{
    for(int i = 0; i < M->getHeight(); i++)
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

    Hash::Set<Node> *adj;
    for(int i = 0; i < M->getHeight(); i++)
    {
        for (int j = 0; j < M->getWidth(); j++)
        {
            bool dirs[4];
            adj = G->adj(Node(j,i));
            if(adj->contains(Node(j - 1,i)))
                dirs[0] = true;
            else
                dirs[0] = false;
            if(adj->contains(Node(j,i + 1)))
                dirs[1] = true;
            else
                dirs[1] = false;
            if(adj->contains(Node(j,i - 1)))
                dirs[2] = true;
            else
                dirs[2] = false;
            if(adj->contains(Node(j + 1,i)))
                dirs[3] = true;
            else
                dirs[3] = false;
            if(dirs[0] && dirs[1] && dirs[2] && dirs[3])
                out << "✛";
            else if(dirs[0] && dirs[1] && dirs[2])
                out << "⊣";
            else if(dirs[1] && dirs[2] && dirs[3])
                out << "⊢";
            else if(dirs[0] && dirs[2] && dirs[3])
                out << "⊥";
            else if(dirs[0] && dirs[1] && dirs[3])
                out << "⊤";
            else if(dirs[0] && dirs[1])
                out << "↰";
            else if(dirs[1] && dirs[2])
                out << "↕";
            else if(dirs[2] && dirs[3])
                out << "↱";
            else if(dirs[3] && dirs[0])
                out << "↔";
            else if(dirs[0] && dirs[2])
                out << "↵";
            else if(dirs[3] && dirs[1])
                out << "⸀";
            else if (dirs[0])
                out << "←";
            else if (dirs[1])
                out << "↓";
            else if (dirs[2])
                out << "↑";
            else if (dirs[3])
                out << "→";
            else
                out << " ";
        }
        out << endl;
    }
    out << endl;
}
#endif
