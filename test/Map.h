#ifndef MAP_H
#define MAP_H
#include "Matrix.h"

enum tile_t { VOID, PAVEMENT, WALL};

struct point
{
    int x,y;
};

class Map : public Matrix<tile_t>
{
    protected:

        int width, height;

    public:

        Map();
        // Defualt constructor
        
        Map(int width, int height);
        // Creates a new map with the given # of rows and columns

        ~Map();
        // Destructor

        tile_t& operator () (int x, int y);
        // Returns a reference variable to Map(x,y)

        tile_t& operator () (point p);
        // Returns a reference variable to Map(x,y)

        int getWidth();
        // getter for width
        
        int getHeight();
        // getter for height
};

#endif
