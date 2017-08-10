#ifndef GRAPH_H
#define GRAPH_H
#include "set.h"
#include "HashTable.h"
#include "List.h"
#ifndef DEBUG
#define DEBUG
#endif

class Point
{
    public: 

        int x,y;
        Point();
        Point(int x,int y);

#ifdef DEBUG
        void print();
        // debug method
#endif
};

bool operator ==(Point p, Point q);
// returns true if two Points have the same coordinates

bool operator !=(Point p, Point q);
// returns true if two Points have the same coordinates

namespace std
{
    template <> struct hash<Point>
    {
        size_t operator()(Point n) const;
        // needed to generate a hash code out of a node
    };
}

class Graph
{
    private:

        HashTable<Point,List<Point>*> Points;
        int C;

    public:

        Graph();
        // Default constructor; creates an empty graph

        ~Graph();
        // Destructor
        
        bool insertPoint(Point p);
        // Inserts a node into the graph

        bool insertEdge(Point p, Point q);
        // Inserts an edge into the graph

        bool deletePoint(Point u);
        // Deletes a node in the graph

        bool deleteEdge(Point u, Point v);
        // Deletes an edge in the graph

        HashSet<Point>* adj(Point u);
        // Returns the set of all the nodes adiacient to u

        HashSet<Point>* V();
        // Retruns the set of all nodes in the graph

        int n();
        // Retuns the size of the nodes set
        
#ifdef DEBUG
        void print();
        bool contains(Point n);
#endif
};

#endif
