#ifndef LEVEL_H
#define LEVEL_H
#include "Map.h"
#include <unordered_map>
#include <string>
#include "Graph.h"
#include "Monster.h"
#include "Item.h"

class Level
{
    private:

        Map map;
        std::unordered_map<std::string,Monster> monsters;
        std::unordered_map<std::string,Item> items;
        int level;

    public:

        Level(int width,int height,int rooms, int _monsters, int _items);
        // Given a width, a height and a  number of rooms, it creates a new level
};
#endif
