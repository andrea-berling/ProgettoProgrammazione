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
        Point upStairs;
        Point downStairs;
        int level;

    public:

        Level(int level,int width,int height,int rooms, int _monsters, int _items);
        // Given a width, a height and a number of rooms, monsters and items, it creates a new level

        void printMap(PlayableCharacter& player);
        // Prints the map, the monsters, the items and the player

        void placeCharacter(PlayableCharacter& player, int playerPosition);
        // Given a main character and a preference for the position, places the characeter accordingly
        // if playerPosition == 0, the position is random
        // if playerPosition == 1, the position is the same as the one of the down stairs
        // if playerPosition == -1, the position is the same as the one of the up stairs

        int handleMovement(Window& info, PlayableCharacter& player);
        // Handles the movement of the main character and the exploration of the map
        // and the printing of the stats

        int getLevel();
        //  Restituisce il numero del livello

        Point getUpStairs();
        // Returns the coordinates of the up stairs

        Point getDownStairs();
        // Returns the coordinates of the down stairs
};

void writeInfo(Window& win,PlayableCharacter& pg, int level);
//  Scrive le informazioni sulla finestra che fornisce i dati su oggetti posseduti e statistiche del PG

void writeEquipment(Window& win, PlayableCharacter& pg);
//  Scrive gli oggetti equipaggiati

#endif
