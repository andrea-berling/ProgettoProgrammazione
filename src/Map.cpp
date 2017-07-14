#include "../include/Map.h"

Map::Map() : Matrix()
{}
// Defualt constructor

Map::Map(int width, int height) : Matrix(height, width), width(width), height(height)
{}
// Creates a new map with the given # of rows and columns

tile_t& Map::operator () (int x, int y)
{
    return matrix[y][x];
}
// Returns a reference variable to Map(x,y)

tile_t& Map::operator () (point p)
{
    return matrix[p.y][p.x];
}
// Returns a reference variable to Map(x,y)

int Map::getWidth()
{
    return this->width;
}

int Map::getHeight()
{
    return this->height;
}
