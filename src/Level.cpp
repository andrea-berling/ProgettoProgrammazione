#include "../include/Level.h"
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

Level::Level(int level, int width, int height, int rooms, int _monsters, int _items):level(level),map(width,height),monsters(47),items(47)
{
    unordered_set<Point> spots;
    vector<Item> itemsSet;
    vector<Monster> monstersSet;
    ifstream file("../resources/items.txt");
    retrieveItems(itemsFile,itemsSet);
    monstersSet = {Monster("Goblin",level),Monster("Troll",level),Monster("Golem",level),Monster("Gineppino",level)};

    map.generate(rooms);
    map.freeSpots(_items,spots);
    for(Point p : spots)
    {
        int index = rand(0,max{LV*3,itemsSet.size()-1});
        itemsSet[index].setPosition(p.x,p.y);
        map.placeItem(itemsSet[index]);
        items.insert(itemsSet[index]);
        // Place an object
    }
    spots.clear();
    map.freeSpots(_monsters,spots);
    for(Point p : spots)
    {
        int index = rand(0,monstersSet.size()-1);
        monsterSet[index].setPosition(p.x,p.y);
        map.placeMonser(monstersSet[index]);
        monsters.insert(monstersSet[index]);
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

void Level::placeCharacter(PlayableCharacter& player)
{
    map.placeCharacter(player);
}

void Level::handleMovement(playableCharacter& player)
{
    int x,y,c;
    Point pos = player.getPosition();
    x = pos.x;
    y = pos.y;
    M.showAround(x,y);
    while((c = getch()) != KEY_F(4))
    {
        switch(c)
        {
            case 'k':
            case KEY_UP:
                if(M(x,y - 1).getType() == PAVEMENT || M(x,y - 1).getType() == HALLWAY) 
                {
                    y = y - 1;
                }
                break;

            case 'j':
            case KEY_DOWN:
                if(M(x,y + 1).getType() == PAVEMENT || M(x,y + 1).getType() == HALLWAY) 
                {
                    y = y + 1;
                }
                break;

            case 'h':
            case KEY_LEFT:
                if(M(x - 1,y).getType() == PAVEMENT || M(x - 1,y).getType() == HALLWAY) 
                {
                    x = x - 1;
                }
                break;

            case 'l':
            case KEY_RIGHT:
                if(M(x + 1,y).getType() == PAVEMENT || M(x + 1,y).getType() == HALLWAY) 
                {
                    x = x + 1;
                }
                break;
#ifdef DEBUG
            case 'p':
                for(int i = 0; i < M.getHeight(); i++)
                    for(int j = 0; j < M.getWidth(); j++)
                        M(j,i).setVisible(true);
#endif
        }
        player.setPosition(x,y);
        if(M(x,y).getId() != "")
        {
            M.setVisible(M(x,y).getId());
        }
        else
        {
            M.showAround(x,y);
        }
    }
}
