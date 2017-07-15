#include <limits.h>
#include <ncurses.h>
#include <math.h>
#include "../include/Graph.h"
#include "../include/Map.h"
#include "../include/Room.h"
#include "../include/dequeue.h"
#include "../include/HashTable.h"
#include "../include/List.h"
#include "../include/stack.h"
#include "../include/utility.hpp"
#include <iostream>

#define INF INT_MAX
#define HEIGHT 37
#define WIDTH 100
#define nil Node()

void link(Room& R,Room& Q,Graph& G,Map& M);

int w(Node u, Node v);

void populateGraph(Graph& dots,Map& M);

void createLinks(Graph& dots,Map& M);

void shortestPath(Graph& G, Node r,HashTable<Node,Node>& T);

void generateMap(Map& M);

List<Node>* retrievePath(HashTable<Node,Node>& T,Node& one,Node& two);

void printMap(Map& M);

void setUpMap(Map& M);

void handleMovement(Map& M);

int main()
{
    Map M(WIDTH,HEIGHT);
    generateMap(M);
    setUpMap(M);
    handleMovement(M);
}

void handleMovement(Map& M)
{
    int x,y;
    getyx(stdscr,y,x);
    int c = getch();
    while(c != 'q')
    {
        switch(c)
        {
            case 'k':
            case KEY_UP:
                getyx(stdscr,y,x);
                if(M(x - 1,y - 1) == PAVEMENT) 
                {
                    mvaddch(y,x - 1,' ');
                    mvaddch(y - 1,x - 1,'@');
                    refresh();
                }
                break;

            case 'j':
            case KEY_DOWN:
                getyx(stdscr,y,x);
                if(M(x - 1,y + 1) == PAVEMENT) 
                {
                    mvaddch(y,x - 1,' ');
                    mvaddch(y + 1,x - 1,'@');
                    refresh();
                }
                break;
                
            case 'h':
            case KEY_LEFT:
                getyx(stdscr,y,x);
                if(M(x - 2,y) == PAVEMENT) 
                {
                    mvaddch(y,x - 1,' ');
                    mvaddch(y,x - 2,'@');
                    refresh();
                }
                break;

            case 'l':
            case KEY_RIGHT:
                getyx(stdscr,y,x);
                if(M(x,y) == PAVEMENT) 
                {
                    mvaddch(y,x - 1,' ');
                    mvaddch(y,x,'@');
                }
                refresh();
                break;

        }
        c = getch();
    }
    endwin();
}

void setUpMap(Map& M)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,true);
    curs_set(0);
    printMap(M);
    point p;
    p.x = rand(0,WIDTH-1);
    p.y = rand(0,HEIGHT-1);
    while(M(p) != PAVEMENT)
    {
        p.x = rand(0,WIDTH-1);
        p.y = rand(0,HEIGHT-1);
    }
    mvaddch(p.y,p.x,'@');
    refresh();
}

void populateGraph(Graph& dots,Map& M)
{
    for(int i = 0; i < HEIGHT; i++)
        for(int j = 0; j < WIDTH; j++)
        {
            if(M(j,i) == WALL || M(j,i) == ROOM_BORDER)
                dots.insertNode(Node(j,i));
        }
}

void createLinks(Graph& dots,Map& M)
{
    for(int i = 0; i < M.getHeight(); i++)
        for(int j = 0; j < M.getWidth(); j++)
        {
            Node current(Node(j,i));
            Node right(Node(j + 1,i));
            Node down(Node(j, i + 1));
            if(M(current.getPoint()) == WALL || M(current.getPoint()) == ROOM_BORDER)
            {
                if(j < M.getWidth() - 1 && (M(right.getPoint()) == WALL || M(right.getPoint()) == ROOM_BORDER))
                    dots.insertEdge(current,right);

                if(i < M.getHeight() - 1 && (M(down.getPoint()) == WALL || M(down.getPoint()) == ROOM_BORDER))
                    dots.insertEdge(current,down);
            }
        }
}

void shortestPath(Graph& G, Node r,HashTable<Node,Node>& T)
{
    HashTable<Node,int> d(G.n());
    HashTable<Node,bool> b(G.n());
    Hash::Set<Node>* adj = G.V();
    Dequeue<Node> S;
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
    S.push(r);
    while(!S.empty())
    {
        Node u = S.pop();
        b.insert(u,false);
        adj = G.adj(u);
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
               T.insert(*it,u);
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

void generateMap(Map& M)
{
    int n = 0;
    int requiredRooms = 10;
    int seed = 2;
    Room R,Q;
    Stack<Room> rooms;
    Graph dots;

    for(int i = 0; i < M.getWidth(); i++)        // Map initialization
        for(int j = 0; j < M.getHeight(); j++)
            M(i,j) = WALL;

    while(n < requiredRooms)
    {
        seed = 2;
        R = generateRoom(M.getWidth(), M.getHeight(), seed);
        while(R.overlaps(M))
        {
            seed += 2;
            R = generateRoom(M.getWidth(), M.getHeight(), seed);
        }
        rooms.push(R);
        R.place(M);
        n++;
    }

    populateGraph(dots,M);   // needs to be modified
    createLinks(dots,M);     // this as well

    R = rooms.pop();
    Q = rooms.top();
    while(!rooms.isEmpty())
    {
        link(R,Q,dots,M);
        R = rooms.pop();
        if(!rooms.isEmpty())
            Q = rooms.top();
    }
    
}

void link(Room& R,Room& Q,Graph& G,Map& M)
{
    point p = R.pickAPointAround(M);
    point q = Q.pickAPointAround(M);
    Node one(p);
    Node two(q);
    List<Node>* steps;
    HashTable<Node,Node> T(6143);

    if(one != two)
    {
        shortestPath(G,one,T);
        steps = retrievePath(T,one,two);
    }
    else
        steps->insert(one);

    for(List_iterator<Node> it = steps->begin(); it != steps->end(); it++)
    {
        if((*it).getPoint() != nil)
            M((*it).getPoint()) = PAVEMENT;
    }

    delete steps;
}

List<Node>* retrievePath(HashTable<Node,Node>& T,Node& one,Node& two)
{
    List<Node>* l = new List<Node>();
    
    l->insert(two);
    Node p = T[two];

    while(p != one)
    {
        l->insert(p);
        p = T[p];
    }

    l->insert(one);

    return l;
}

void printMap(Map& M)
{
    using namespace std;

    for( int i = 0; i < M.getHeight(); i++)
    {
        for (int j = 0; j < M.getWidth(); j++)
        {
            if (M(j,i) == WALL || M(j,i) == ROOM_BORDER)
                printw("#");
            else if ((M(j,i) == PAVEMENT) || (M(j,i) == VOID))
                printw(" ");
        }
        printw("\n");
    }
    cout << endl;
}
