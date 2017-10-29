#ifndef LEVEL_H
#define LEVEL_H
#include "Map.h"
#include <unordered_map>
#include <vector>
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

        bool validPosition(const Point pos,const Point playerPos);
        // Returns true if the given position is a valid position for the monster to move into

        void spawnItems(const int n,const std::vector<Item>& itemsSet, const int generatedRooms);
        // Spawns the items given the vector of all possible items, the number of items to spawn and the number of
        // generated rooms

        void spawnMonsters(const int n,const int generatedRooms);
        // Spawns the monsters given the number of monsters and the number of generated rooms

        status_t pickItUp(PlayableCharacter& player,Window& win);
        // Makes the player pick up what is beneath him, if possible, printing messages to the given win
        // Returns WIN if the picked up item was the last special item (which means victory), DEFAULT otherwise

        status_t handleBattles(PlayableCharacter& player, Window& bottom, Window& playerInfo, Window& mapWindow);
        // Handles the battle with monsters nearby, if present. It a turn battle one monster at a time
        // Returns a LOSS status upon a lost battle, DEFAULT if no battle is lost 

    public:

        Level(const LevelConfig& config,PlayableCharacter& pg);
        // Given a level configuration and the player it creates a new level

        void printMap(const Point playerPos, Window& mapWindow);
        // Prints the map, the monsters, the items and the player

        void placeCharacter(PlayableCharacter& player, const pos_pref_t preference);
        // Given a main character and a preference for the position, places the characeter accordingly
        // if preference == RANDOM, the position is random
        // if preference == DOWN, the position is the same as the one of the down stairs
        // if preference == UP, the position is the same as the one of the up stairs

        status_t handleTurn(Window& mapWindow, Window& info, Window& bottom, PlayableCharacter& player);
        // Handles the player's turn
        // Returns UP or DOWN, if the player is on the up or down stairs respectively, WIN or LOSS if the player has
        // won the game or has lost due to a battle, QUIT if the quit request was confirmed

        int getLevel() const;
        //  Restituisce il numero del livello

        Point getUpStairs() const;
        // Returns the coordinates of the up stairs

        Point getDownStairs() const;
        // Returns the coordinates of the down stairs

        void monstersAround(const Point playerPos, std::list<Monster>& list);
        // Given a player and an empty list, it fills the list with the the monsters around player

        void shopMenu(PlayableCharacter& pg,std::vector<Item>& itemsSet);
        // Genera la finestra dello shop con i vari Item da acquistare

        void moveMonster(Point playerPosition, Monster& mons);
        // Muove il mostro passato in modo che si avvicini al giocatore 

        bool Battle (Window& battle_win, Window& right_win, Window& mapWin, PlayableCharacter& player, Monster& m);

        void showMap(const Point pos);
        // Given the position of the player, it shows the map dinamically: shows the four tiles adjacent to pos, if the
        // position is not within a room, else it shows the whole room

        void writeInfo(Window& win,PlayableCharacter& pg);
        //  Scrive le informazioni nella finestra a destra, fornendo i dati su oggetti posseduti e sulle statistiche del PG
};

void writeEquipment(Window& win, PlayableCharacter& pg);
//  Scrive gli oggetti equipaggiati nella finestra a destra

int Atk_Def (int def, int atk);

int Luck (int luck);

status_t promptExit(Window& win);
// Prompts an exit confirmation request on the given window
// Returns QUIT if the exit request is confirmed, DEFAULT otherwise

void showInstructions();
// Shows general instructions for the game

#endif  // LEVEL_H
