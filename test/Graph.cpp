#ifndef GRAPH_CPP
#define GRAPH_CPP
#include "Graph.h"
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

void Edge::print()
{
    u.print();
    cout << " -> ";
    v.print();
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

    size_t hash<Edge>::operator()(Edge e) const
    {
        return hash<Node>()(e.getFirstNode()) ^ hash<Node>()(e.getSecondNode()); 
    }
}

Edge::Edge():u(Node()), v(Node())
{ }
// Default constructor

Edge::Edge(Node u, Node v)
{
    this->u = u;
    this->v = v;
}
// Creates a new edge given u and v

Node Edge::getFirstNode()
{
    return u;
}
// first node getter

Node Edge::getSecondNode()
{
    return v;
}
// second node getter

void Edge::setFirstNode(Node u)
{
    this->u = u;
}
// first node setter

void Edge::setSecondNode(Node v)
{
    this->v = v;
}
// second node setter

bool operator == (Edge e, Edge f)
{
    return (e.getFirstNode() == f.getFirstNode()) && (e.getSecondNode() == f.getSecondNode());
}

Graph::Graph():nodes(Hash::Set<Node>(6143)), edges(Hash::Set<Edge>(12289)) 
{}
// Default constructor; creates an empty graph

bool Graph::insertNode(Node u)
{
    if(!nodes.contains(u))
    {
        nodes.insert(u);
        return true;
    }
    else
        return false;
}
// Inserts a node into the graph

bool Graph::insertEdge(Node u, Node v)
{
    Edge e(u,v);
    if(!edges.contains(e))
    {
        edges.insert(e);
        e = Edge(v,u);
        edges.insert(e);
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
        nodes.remove(u);
        for(Hash::set_iterator<Edge> e = edges.begin(); e != edges.end(); e++)
        {
            if ((*e).getFirstNode() == u || (*e).getSecondNode() == u)
                edges.remove(*e);
        }
        return true;
    }
    else
        return false;
}
// Deletes a node in the graph

bool Graph::deleteEdge(Node u, Node v)
{
    Edge e(u,v);
    if(edges.contains(e))
    {
        edges.remove(e);
        e = Edge(v,u);
        edges.remove(e);
        return true;
    }
    else
        return false;
}
// Deletes an edge in the graph

Hash::Set<Node>* Graph::adj(Node u)
{
    Hash::Set<Node> *adj = new Hash::Set<Node>(6143);

    for(Hash::set_iterator<Edge> e = edges.begin(); e != edges.end(); e++)
    {
        if((*e).getFirstNode() == u)
            adj->insert((*e).getSecondNode());
        else if((*e).getSecondNode() == u)
            adj->insert((*e).getFirstNode());
    }

    return adj;
}
// Returns the set of all the nodes adiacient to u

Hash::Set<Node>* Graph::V()
{
    Hash::Set<Node> *v = new Hash::Set<Node>(6143);               // a new set is created, so that modifications in this set without using the graph methods won't affect the graph

    for(Hash::set_iterator<Node> it = nodes.begin(); it != nodes.end(); it++)
    {
        v->insert(*it);
    }

    return v;
}
// Retruns the set of all nodes in the graph

int Graph::n()
{
    return nodes.size();
}

#ifdef DEBUG
void Graph::print()
{
    using namespace std;        

    for(Hash::set_iterator<Edge> it = edges.begin(); it != edges.end(); it++)
    {
        (*it).print();
        cout << " , ";
    }

    cout << endl;
}

bool Graph::contains(Node n)
{
    return nodes.contains(n);
}
#endif

#endif
