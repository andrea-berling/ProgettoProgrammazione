#ifndef GRAPH_H
#define GRAPH_H
#include <limits.h>
#include <unordered_set>
#include <unordered_map>
#include <list>

#define INF INT_MAX

struct Point
{
        int x,y;
        Point();
        Point(const int x, const int y);
};

bool operator ==(const Point p, const Point q);
// returns true if two Points have the same coordinates

bool operator !=(const Point p, const Point q);
// returns true if two Points have the same coordinates


namespace std
{
    template <> struct hash<Point>
    {
        size_t operator()(const Point n) const;
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
        
        bool insertPoint(const Point p);
        // Inserts a node into the graph
        // Returns true if inserted correctly, false otherwise

        bool insertEdge(const Point p, const Point q);
        // Inserts an edge into the graph
        // Returns true if inserted correctly, false otherwise

        bool deletePoint(const Point u);
        // Deletes a node in the graph
        // Returns true if deleted correctly, false otherwise

        bool deleteEdge(const Point u, const Point v);
        // Deletes an edge in the graph
        // Returns true if deleted correctly, false otherwise

        std::unordered_set<Point>* adj(const Point u);
        // Returns the set of all the nodes adiacient to u

        std::unordered_set<Point>* V() const;
        // Retruns the set of all nodes in the graph

        int n() const;
        // Retuns the number of nodes
        
};

void shortestPath(Graph& G, const Point r,std::unordered_map<Point,Point>& T);
// Find the shortest path between point r and all other points in the graph G

void retrievePath(std::list<Point>& l,std::unordered_map<Point,Point>& T,Point p,Point q);
// Retrieves the path between one and two, saved in the map T, and stores it in l

int w(const Point p, const Point q);
// Returns the walking distance between p and q in the map (how many steps are required to get to q from p)

#endif
