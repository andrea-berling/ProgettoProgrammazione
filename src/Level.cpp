#include "../include/Level.h"

using namespace std;

Level::Level(int level, int width, int height, int rooms, int _monsters, int _items):level(level),map(width,height),monsters(47),items(47)
{
    unordered_set<Point> spots;
    map.generate(rooms);
    map.freeSpots(_items,spots);
    for(Point p : spots)
    {
        // Place an object
    }
    spots.clear();
    map.freeSpots(_monsters,spots);
    for(Point p : spots)
    {
        // Spawn a monster
    }
}

void Level::printMap()
{
    clear();
    move(0,0);
    for(int i = 0; i < map.getHeight(); i++)
    {
        for (int j = 0; j < map.getWidth(); j++)
        {
            addch(map(j,i).isVisible() ? map(j,i).getSymbol() : ' ');
        }
        addch('\n');
    }
    for(Monster m : monster)
    {
        Point position = m.getPosition();
        mvaddch(position.x,position.y,m.getSymbol());
    }
    for(Item i : items)
    {
        Point position = i.getPosition();
        mvaddch(position.x,position.y,i.getSymbol());
    }
    refresh();
}

void placeCharacter(PlayableCharacter& player)
{
    map.placeCharacter(player);
}
