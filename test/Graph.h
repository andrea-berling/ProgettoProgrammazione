#ifndef GRAPH_H
#define GRAPH_H
#include "../../DataStructures/Set/include/set.h"
#ifndef DEBUG
#define DEBUG
#endif

struct point
{
    int x,y;

    friend bool operator ==(point p, point q);

#ifdef DEBUG
    void print();
#endif
};

class Node
{
    private:

        point p;

    public:
        
        Node();
        // Default constructor
        
        Node(point p);
        // Creates a new node given a point p
        
        Node(int x, int y);
        // Creates a new node given a point p

        void setPoint(point p);
        // point setter
        
        point getPoint();
        // point getter

        friend bool operator ==(Node n1, Node n2);
        // == operator

        friend bool operator !=(Node n1, Node n2);
        // == operator

#ifdef DEBUG
        void print();
#endif
};

namespace std
{
    template <> struct hash<Node>
    {
        size_t operator()(Node n) const;
    };
}

class Edge
{
    private:

        Node u,v;

    public:

        Edge();
        // Default constructor

        Edge(Node u, Node v);
        // Creates a new edge given u and v

        Node getFirstNode();
        // first node getter

        Node getSecondNode();
        // second node getter

        void setFirstNode(Node u);
        // first node setter

        void setSecondNode(Node v);
        // second node setter
        
        friend bool operator == (Edge e, Edge f);
        // == operator
        
#ifdef DEBUG
        void print();
#endif
};

namespace std
{
    template <> struct hash<Edge>
    {
        size_t operator()(Edge e) const;
    };
}

class Graph
{
    private:

        Hash::Set<Node> nodes;
        Hash::Set<Edge> edges;

    public:

        Graph();
        // Default constructor; creates an empty graph

        bool insertNode(Node u);
        // Inserts a node into the graph

        bool insertEdge(Node u, Node v);
        // Inserts a node into the graph

        bool deleteNode(Node u);
        // Deletes a node in the graph

        bool deleteEdge(Node u, Node v);
        // Deletes an edge in the graph

        Hash::Set<Node>* adj(Node u);
        // Returns the set of all the nodes adiacient to u

        Hash::Set<Node>* V();
        // Retruns the set of all nodes in the graph

        int n();
        // Retuns the size of the nodes set
        
#ifdef DEBUG
        void print();
        bool contains(Node n);
#endif
};

//#include "Graph.cpp"

#endif
