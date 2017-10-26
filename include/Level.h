#ifndef LEVEL_H
#define LEVEL_H
#include "Map.h"
#include <unordered_map>
#include <string>
#include <list>
#include "Graph.h"
#include "personaggiGiocabili.h"
#include "Monster.h"
#include "Item.h"
#include "Window.h"

enum status_t {WIN, LOSS, UP, DOWN, QUIT, DEFAULT};

enum pos_pref_t {RANDOM, UPSTAIRS, DOWNSTAIRS};

struct LevelConfig
{
    int n,width,height,rooms,monsters,items;

    void newLevel();
    // Changes the configuration for a new level
};

class Level
{
    private:

        Map map;
        std::unordered_map<std::string,Monster> monsters;
        std::unordered_map<std::string,Item> items;
        Point upStairs;
        Point downStairs;
        int level;
        bool validPosition(Point pos,Point playerPos);

    public:

        Level(LevelConfig& config,PlayableCharacter& pg);
        // Given a width, a height and a number of rooms, monsters and items, it creates a new level

        void printMap(Point playerPos, Window& mapWindow);
        // Prints the map, the monsters, the items and the player

        void placeCharacter(PlayableCharacter& player, pos_pref_t preference);
        // Given a main character and a preference for the position, places the characeter accordingly
        // if playerPosition == 0, the position is random
        // if playerPosition == 1, the position is the same as the one of the down stairs
        // if playerPosition == -1, the position is the same as the one of the up stairs

        status_t handleTurn(Window& mapWindow, Window& info, Window& bottom, PlayableCharacter& player);
        // Handles the player's turn

        int getLevel();
        //  Restituisce il numero del livello

        Point getUpStairs();
        // Returns the coordinates of the up stairs

        Point getDownStairs();
        // Returns the coordinates of the down stairs

        void monstersAround(Point playerPos, std::list<Monster>& list);
        // Given a player and an empty list, it fills the list with the the monsters around player

        void shopMenu(PlayableCharacter& pg, std::vector<Item>& itemsSet);
        //  Genera la finestra dello shop con i vari Item da acquistare

        void moveMonster(Point playerPosition, Monster& mons);
        // Muove il mostro passato in modo che si avvicini al giocatore 

        bool Battle (Window& battle_win, Window& right_win, Window& mapWin, PlayableCharacter& player, Monster& m);

        void showMap(Point pos);
        // Given the position of the player, it shows the map dinamically: shows the four tiles adjacent to pos, if the
        // position is not within a room, else it shows the whole room

        status_t pickItUp(PlayableCharacter& player,Window& win);
        // Makes the player pick up what is beneath him, if possible, printing messages to the given win
        // Returns 2 if the picked up item was the last special item (which means victory), -2 otherwise

        status_t handleBattles(PlayableCharacter& player, Window& bottom, Window& playerInfo, Window& mapWindow);
        // Handles the battle with monsters nearby, if present
        // Returns a LOSS status upon a lost battle, DEFAULT if no battle is lost 

        void writeInfo(Window& win,PlayableCharacter& pg);
        //  Scrive le informazioni nella finestra a destra, fornendo i dati su oggetti posseduti e sulle statistiche del PG
};

void writeEquipment(Window& win, PlayableCharacter& pg);
//  Scrive gli oggetti equipaggiati nella finestra a destra

int Atk_Def (int def, int atk);

int Luck (int luck);

status_t promptExit(Window& win);
// Prompts an exit confirmation request on the given window
// Returns 0 if the exit request is confirmed, -2 otherwise


#endif
