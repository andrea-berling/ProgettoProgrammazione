#ifndef GRAPH_CPP
#define GRAPH_CPP
#include <algorithm>
#include <deque>
#include "../include/Graph.h"
#include <utility>
#include <boost/functional/hash.hpp>
#include <iostream>

using namespace std;

bool operator ==(Point p, Point q)
{
    return (p.x == q.x) && (p.y == q.y);
}

bool operator !=(Point p, Point q)
{
    return p.x != q.x || p.y != q.y;
}

Point::Point():x(-1),y(-1)
{}

Point::Point(int x, int y): x(x),y(y)
{
}

namespace std
{
    size_t hash<Point>::operator()(Point n) const
    {
        return hash<int>()(boost::hash<pair<int,int>>()(pair<int,int>(n.x,n.y)));
    }
}


Graph::Graph():Points(6143),C(0)
{}
// Default constructor; creates an empty graph

bool Graph::insertPoint(Point p)
{
    if(Points.find(p) == Points.end())
    {
        Points[p] = new list<Point>();
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
        delete pair.second;  // frees the memory occupied by the adjacency lists
}

bool Graph::insertEdge(Point p, Point q)
{
    if(Points.find(p) != Points.end() && Points.find(q) != Points.end())
    {
        list<Point>* l = Points[p]; 
        if(find(l->begin(),l->end(),q) == l->end())
            l->insert(l->begin(),q);
        l = Points[q];
        if(find(l->begin(),l->end(),p) == l->end()) // The graph is undirected
            l->insert(l->begin(),p);
        return true;
    }
    else
        return false;
}
// Inserts a node into the graph

bool Graph::deletePoint(Point p)
{
    unordered_map<Point,list<Point>*>::iterator p_it = Points.find(p);
    if(p_it != Points.end())
    {
        bool done = false;
        delete (*p_it).second;
        Points.erase(p_it);
        C--;
        for(auto q : Points) // removing node p from all the adjacency lists where it appears
        {
            for(list<Point>::iterator it = q.second->begin(); it != q.second->end() && !done; it++)
                if(*it == p)
                {
                    q.second->erase(it);
                    done = true;    // Stops looking for p in the adjacency list of the current node
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
    if(Points.find(p) != Points.end() && Points.find(q) != Points.end())
    {
        list<Point>* l = Points[p];
        list<Point>* m = Points[q];
        list<Point>::iterator it1 = find(l->begin(),l->end(),q); // Removing q from p's adjacency list
        list<Point>::iterator it2 = find(m->begin(),m->end(),p); // Removing q from p's adjacency list
        if(it1 != l->end() && it2 != m->end())
        {
            l->erase(it1);
            m->erase(it2);
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
// Deletes an edge in the graph

unordered_set<Point>* Graph::adj(const Point p)
{
    unordered_set<Point> *adj = new unordered_set<Point>();   // in the graph of the map there are at most 4 adjacent Points

    for(Point q : *(Points[p]))
    {
        adj->insert(q);
    }

    return adj;
}
// Returns the set of all the Points adiacient to u

unordered_set<Point>* Graph::V() const
{
    unordered_set<Point> *v = new unordered_set<Point>();               // a new set is created, so that modifications in this set without using the graph methods won't affect the graph

    for(auto pair : Points)
    {
        v->insert(pair.first);
    }

    return v;
}
// Retruns the set of all Points in the graph

int Graph::n() const
{
    return C;
}

void shortestPath(Graph& G, const Point r,unordered_map<Point,Point>& T)
{
    unordered_map<Point,int> d(2*G.n()+1);
    unordered_map<Point,bool> b(2*G.n()+1);
    unordered_set<Point>* adj = G.V();
    deque<Point> S;

    for(Point u : *adj)
    {
        if(u != r)
        {
            T[u] = Point();
            d[u] = INF;
            b[u] = false;
        }
    }

    delete adj;

    T[r] = Point();
    d[r] = 0;
    b[r] = true;
    S.push_front(r);

    while(!S.empty())
    {
        Point u = *(S.begin());
        S.pop_front();
        b[u] = false;
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
                        S.push_front(v);
                    b[v] = true;
                }
                T[v] = u;
                d[v] = d[u] + w(u,v);
            }
        }
        delete adj;
    }
}

void retrievePath(list<Point>& l, unordered_map<Point,Point>& T,Point p,Point q)
{
    while(q != p)
    {
        if (q != Point())
            l.insert(l.begin(),q);
        q = T[q];
    }

    l.insert(l.begin(),p);
}

int w(Point p, Point q)
{
   return abs(p.x - q.x) + abs(p.y - q.y);
}

#endif
