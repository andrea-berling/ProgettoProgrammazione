#ifndef GRAPH_H
#define GRAPH_H
#include "../../DataStructures/Set/include/set.h"
#include "../../DataStructures/HashTable/include/HashTable.h"
#include "../../DataStructures/List/include/List.h"
#ifndef DEBUG
#define DEBUG
#endif

struct point
{
    int x,y;

    friend bool operator ==(point p, point q);
    // returns true if two points have the same coordinates

#ifdef DEBUG
    void print();
    // debug method
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
        // Returns true if two nodes have the same point

        friend bool operator !=(Node n1, Node n2);
        // Returns !(n1 == n2)

#ifdef DEBUG
        void print();
        // debug method
#endif
};

namespace std
{
    template <> struct hash<Node>
    {
        size_t operator()(Node n) const;
        // needed to generate a hash code out of a node
    };
}

class Graph
{
    private:

        HashTable<Node,List<Node>*> nodes;
        int C;

    public:

        Graph();
        // Default constructor; creates an empty graph

        ~Graph();
        // Destructor
        
        bool insertNode(Node u);
        // Inserts a node into the graph

        bool insertEdge(Node u, Node v);
        // Inserts an edge into the graph

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

#endif
