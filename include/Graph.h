#ifndef GRAPH_H
#define GRAPH_H
#include <limits.h>
#include <unordered_set>
#include <unordered_map>
#include <list>
#ifndef DEBUG
#define DEBUG
#endif

#define INF INT_MAX

class Point
{
    public: 

        int x,y;
        Point();
        Point(int x,int y);
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

        std::unordered_map<Point,std::list<Point>*> Points;
        int C;

    public:

        Graph();
        // Default constructor; creates an empty graph

        ~Graph();
        // Destructor
        
        bool insertPoint(Point p);
        // Inserts a node into the graph
        // Returns true if inserted correctly, false otherwise

        bool insertEdge(Point p, Point q);
        // Inserts an edge into the graph
        // Returns true if inserted correctly, false otherwise

        bool deletePoint(Point u);
        // Deletes a node in the graph
        // Returns true if deleted correctly, false otherwise

        bool deleteEdge(Point u, Point v);
        // Deletes an edge in the graph
        // Returns true if deleted correctly, false otherwise

        std::unordered_set<Point>* adj(Point u);
        // Returns the set of all the nodes adiacient to u

        std::unordered_set<Point>* V();
        // Retruns the set of all nodes in the graph

        int n();
        // Retuns the size of the nodes set
        
};

void shortestPath(Graph& G, Point r,std::unordered_map<Point,Point>& T);
// Find the shortest path between point r and all other points in the graph G

void retrievePath(std::list<Point>& l,std::unordered_map<Point,Point>& T,Point p,Point q);
// Retrieves the path between one and two, saved in the map T and stores it in l

int w(Point p, Point q);
// Returns the walking distance between p and q in the map (how many steps are required to get to q from p)

#endif
