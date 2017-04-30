#include <limits.h>
#include <math.h>
#include "Graph.h"
#include "../../DataStructures/PriorityQueue/include/priorityqueue.h"
#include "../../DataStructures/HashTable/include/HashTable.h"

#define INF INT_MAX
#define HEIGHT 37
#define WIDTH 100
#define nil Node()

int w(Node u, Node v);

void populateGraph(Graph* dots);

void createLinks(Graph* dots);

void shortestPath(Graph* G, Node r,HashTable<Node,Node>* T);

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

void populateGraph(Graph* dots)
{
    for(int i = 1; i < HEIGHT - 1; i++)
        for(int j = 1; j < WIDTH - 1; j++)
            dots->insertNode(Node(j,i));
}

void createLinks(Graph* dots)
{
    for(int i = 1; i < HEIGHT -1; i++)
        for(int j = 1; j < WIDTH - 1; j++)
        {
            Node current(Node(j,i));
            Node right(Node(j + 1,i));
            Node down(Node(j, i + 1));
            if(j < WIDTH - 2) 
                dots->insertEdge(current, right);
            if(i < HEIGHT - 2)
                dots->insertEdge(current,down);
        }

}

void shortestPath(Graph* G, Node r,HashTable<Node,Node>* T)
{
    HashTable<Node,int> d(G->n());
    HashTable<Node,bool> b(G->n());
    Hash::Set<Node>* adj = G->adj(r);
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
               T->insert(*it,u);
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
