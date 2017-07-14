#ifndef GRAPH_CPP
#define GRAPH_CPP
#include "../include/Graph.h"
#include <iostream>
#ifndef DEBUG
#define DEBUG
#endif

bool operator !=(Node p, Node q)
{
    return !(p == q);
}

bool operator ==(point p, point q)
{
    return (p.x == q.x) && (p.y == q.y);
}

#ifdef DEBUG
void point::print()
{
    cout << "(" << x << "," << y << ")";
}

void Node::print()
{
    p.print();
}

#endif

Node::Node()
{
    p = {-1,-1};
}
// Default constructor

Node::Node(point p)
{
    this->p = p;
}
// Creates a new node given a point p

Node::Node(int x, int y)
{
    p.x = x;
    p.y = y;
}

void Node::setPoint(point p)
{
    this->p = p;
}
// point setter

point Node::getPoint()
{
    return this->p;
}
// point getter

bool operator ==(Node n1, Node n2)
{
    return (n1.p == n2.p);
}
// == operator

namespace std
{
    size_t hash<Node>::operator()(Node n) const
    {
        int xHash = n.getPoint().x;
        xHash = hash<int>()(xHash);
        int yHash = n.getPoint().y;
        yHash = hash<int>()(yHash);

        return xHash ^ yHash;
    }
}

Graph::Graph():nodes(HashTable<Node,List<Node>*>(6143)),C(0) 
{}
// Default constructor; creates an empty graph

bool Graph::insertNode(Node u)
{
    if(!nodes.contains(u))
    {
        nodes.insert(u,new List<Node>());
        C++;
        return true;
    }
    else
        return false;
}
// Inserts a node into the graph

Graph::~Graph()
{
    for(hash_iterator<Node,List<Node>*> it = nodes.begin(); it != nodes.end(); it++)
        delete (*it).getValue();
}

bool Graph::insertEdge(Node u, Node v)
{
    if(nodes.contains(u) && nodes.contains(v))
    {
        List<Node>* l = nodes.lookup(u); 
        if(!l->contains(v))
            l->insert(v);
        l = nodes.lookup(v);
        if(!l->contains(u))
            l->insert(u);
        return true;
    }
    else
        return false;
}
// Inserts a node into the graph

bool Graph::deleteNode(Node u)
{
    if(nodes.contains(u))
    {
        bool done = false;
        nodes.remove(u);
        for(hash_iterator<Node,List<Node>*> it = nodes.begin(); it != nodes.end(); it++)
        {
            for(List_iterator<Node> it2 = (*it).getValue()->begin(); it2 != (*it).getValue()->end() && !done; it2++)
                if(*it2 == u)
                {
                    (*it).getValue()->remove(it2);
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

bool Graph::deleteEdge(Node u, Node v)
{
    if(nodes.contains(u) && nodes.contains(v))
    {
        List<Node>* l = nodes.lookup(u);
        bool done = false;
        for(List_iterator<Node> it = l->begin(); it != l->end() && !done; it++)
            if(*it == v)
            {
                l->remove(it);
                done = true;
            }
        done = false;
        l = nodes.lookup(v);
        for(List_iterator<Node> it = l->begin(); it != l->end() && !done; it++)
            if(*it == u)
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

Hash::Set<Node>* Graph::adj(Node u)
{
    Hash::Set<Node> *adj = new Hash::Set<Node>(10);

    for(List_iterator<Node> it = (nodes.lookup(u))->begin(); it != (nodes.lookup(u))->end(); it++)
    {
        adj->insert(*it);
    }

    return adj;
}
// Returns the set of all the nodes adiacient to u

Hash::Set<Node>* Graph::V()
{
    Hash::Set<Node> *v = new Hash::Set<Node>(6143);               // a new set is created, so that modifications in this set without using the graph methods won't affect the graph

    for(hash_iterator<Node,List<Node>*> it = nodes.begin(); it != nodes.end(); it++)
    {
        v->insert((*it).getKey());
    }

    return v;
}
// Retruns the set of all nodes in the graph

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

bool Graph::contains(Node n)
{
    return nodes.contains(n);
}
#endif

#endif
