#ifndef AREA_H
#define AREA_H
#include "Graph.h"

class Area
{
    protected:

        Point p;
        int width;
        int height;

    public:

        Area();
        // Default constructor

        Area(Point position, int width, int height);
        // Given a position, width and height creates a new Area

        Area(const Area& A);
        // Copy constructor

        Point getCorner();
        // Returns the upper left corner

        int getWidth();
        // Returns the width of the room

        int getHeight();
        // Returns the height of the room

        void split(Area& A1, Area& A2, bool vertical);
        // Splits the area in two subareas and stores them in A1 and A2
        // if vertical == true, the split is vertical, otherwise it's horizontal
        // The split is in two areas such that one area is at most 2/3 of the original area

        void splitInHalf(Area& A1, Area& A2, bool vertical);
        // Splits the area in two subareas and stores them in A1 and A2
        // if vertical == true, the split is vertical, otherwise it's horizontal
        // The split is in two equal halves

        friend bool operator==(Area A1,Area A2);
        // Comparison operator
};

namespace std
{
    template <> struct hash<Area>
    {
        size_t operator()(Area A) const;
        // hash function for the Area 
    };
}

#endif
