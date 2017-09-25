#ifndef LEVEL_H
#define LEVEL_H
#include "Map.h"
#include <unordered_map>
#include <string>
#include "Graph.h"
#include "personaggiGiocabili.h"
#include "Monster.h"
#include "Item.h"
#include "Window.h"

class Level
{
    private:

        Map map;
        std::unordered_set<Monster> monsters;
        std::unordered_set<Item> items;
        int level;

    public:

        Level(int level,int width,int height,int rooms, int _monsters, int _items);
        // Given a width, a height and a number of rooms, monsters and items, it creates a new level

        void printMap(PlayableCharacter& player);
        // Prints the map, the monsters, the items and the player

        void placeCharacter(PlayableCharacter& player);
        // Given a main character, places it in a random room in the map

        void handleMovement(Window& info, PlayableCharacter& player);
        // Handles the movement of the main character and the exploration of the map
        // and the printing of the stats

};

void writeInfo(Window& win,PlayableCharacter& pg);
//  Finestra che fornisce i dati su oggetti posseduti e statistiche del PG

#endif
