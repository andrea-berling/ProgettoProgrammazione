#ifndef GRAPH_CPP
#define GRAPH_CPP
#include "../include/dequeue.h"
#include "../include/Graph.h"
#include <iostream>
#ifndef DEBUG
#define DEBUG
#endif

bool operator ==(Point p, Point q)
{
    return (p.x == q.x) && (p.y == q.y);
}

bool operator !=(Point p, Point q)
{
    return p.x != q.x || p.y != q.y;
}

#ifdef DEBUG
void Point::print()
{
    cout << "(" << x << "," << y << ")";
}

#endif

Point::Point():x(-1),y(-1)
{}

Point::Point(int x, int y): x(x),y(y)
{
}

namespace std
{
    size_t hash<Point>::operator()(Point n) const
    {
        int xHash = n.x;
        xHash = hash<int>()(xHash);
        int yHash = n.y;
        yHash = hash<int>()(yHash);

        return xHash ^ yHash;
    }
}

Graph::Graph():Points(6143),C(0) 
{}
// Default constructor; creates an empty graph

bool Graph::insertPoint(Point p)
{
    if(!Points.contains(p))
    {
        Points.insert({p,new List<Point>()});
        C++;
        return true;
    }
    else
        return false;
}
// Inserts a node into the graph

Graph::~Graph()
{
    for(auto pair : Points)
        delete pair.value;  // frees the memory occupied by the adjacency lists
}

bool Graph::insertEdge(Point p, Point q)
{
    if(Points.contains(p) && Points.contains(q))
    {
        List<Point>* l = Points[p]; 
        if(!l->contains(q))
            l->insert(q);
        l = Points[q];
        if(!l->contains(p)) // The graph is undirected
            l->insert(p);
        return true;
    }
    else
        return false;
}
// Inserts a node into the graph

bool Graph::deletePoint(Point p)
{
    if(Points.contains(p))
    {
        bool done = false;
        Points.remove(p);
        C--;
        for(auto q : Points) // removing node p from all the adjacency lists where it appears
        {
            for(List<Point>::iterator it = q.value->begin(); it != q.value->end() && !done; it++)
                if(*it == p)
                {
                    q.value->remove(it);
                    done = true;
                }
            done = false;
        }
        return true;
    }
    else
        return false;
}
// Deletes a node in the graph

bool Graph::deleteEdge(Point p, Point q)
{
    if(Points.contains(p) && Points.contains(q))
    {
        List<Point>* l = Points[p];
        bool done = false;
        for(List<Point>::iterator it = l->begin(); it != l->end() && !done; it++)
            if(*it == q)
            {
                l->remove(it);
                done = true;
            }
        done = false;
        l = Points[q];
        for(List<Point>::iterator it = l->begin(); it != l->end() && !done; it++)
            if(*it == p)
            {
                l->remove(it);
                done = true;
            }
        return true;
    }
    else
        return false;
}
// Deletes an edge in the graph

HashSet<Point>* Graph::adj(Point p)
{
    HashSet<Point> *adj = new HashSet<Point>(17);   // in the graph of the map there are at most 4 adjacent Points

    for(Point q : *(Points[p]))
    {
        adj->insert(q);
    }

    return adj;
}
// Returns the set of all the Points adiacient to u

HashSet<Point>* Graph::V()
{
    HashSet<Point> *v = new HashSet<Point>(6143);               // a new set is created, so that modifications in this set without using the graph methods won't affect the graph

    for(auto pair : Points)
    {
        v->insert(pair.key);
    }

    return v;
}
// Retruns the set of all Points in the graph

int Graph::n()
{
    return C;
}

#ifdef DEBUG
//void Graph::print()
//{
//    using namespace std;        
//
//    for(Hash::set_iterator<Edge> it = edges.begin(); it != edges.end(); it++)
//    {
//        (*it).print();
//        cout << " , ";
//    }
//
//    cout << endl;
//}

bool Graph::contains(Point p)
{
    return Points.contains(p);
}
#endif

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

void retrievePath(List<Point>& l,HashTable<Point,Point>& T,Point& one,Point& two)
{
    Point p = two;

    while(p != Point())
    {
        l.insert(p);
        p = T[p];
    }
}

int w(Point p, Point q)
{
   return abs(p.x - q.x) + abs(p.y - q.y);
}


#endif
