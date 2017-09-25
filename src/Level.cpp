#include "../include/Level.h"
#include "../include/utility.h"
#include <ncurses.h>
#include <vector>
#include <cmath>
#include <fstream>

using namespace std;

Level::Level(int level, int width, int height, int rooms, int _monsters, int _items):level(level),map(width,height),monsters(47),items(47)
{
    unordered_set<Point> spots;
    vector<Item> itemsSet;
    vector<Monster> monstersSet;
    ifstream itemsFile("resources/items.txt");
    retrieveItems(itemsFile,itemsSet);
    monstersSet = {Monster("Goblin",level),Monster("Troll",level),Monster("Golem",level),Monster("Gineppino",level)};

    map.generate(rooms);
    map.freeSpots(_items,spots);
    for(Point p : spots)
    {
        int index = rand(0,max(level*3,static_cast<int>(itemsSet.size())-1));
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
        monstersSet[index].setPosition(p.x,p.y);
        map.placeMonster(monstersSet[index]);
        monsters.insert(monstersSet[index]);
        // Spawn a monster
    }
}

void Level::printMap(PlayableCharacter& player)
{
    clear();
    move(0,0);
    for(int i = 0; i < map.getHeight(); i++)
    {
        for (int j = 0; j < map.getWidth(); j++)
        {
            if(map(j,i).isVisible())
                addch(map(j,i).getSymbol());
            else
                addch(' ');
        }
        addch('\n');
    }
    for(Monster m : monsters)
    {
        Point position = m.getPosition();
        mvaddch(position.y,position.x,m.getSymbol());
    }
    for(Item i : items)
    {
        Point position = i.getPosition();
        mvaddch(position.y,position.x,i.getSymbol());
    }
    Point p = player.getPosition();
    mvaddch(p.y,p.x,'@');

    refresh();
}

void Level::placeCharacter(PlayableCharacter& player)
{
    map.placeCharacter(player);
}

void Level::handleMovement(Window& info,PlayableCharacter& player)
{
    int x,y,c;
    Point pos = player.getPosition();
    x = pos.x;
    y = pos.y;
    map.showAround(x,y);
    while((c = getch()) != 'q')
    {
        switch(c)
        {
            case 'k':
            case KEY_UP:
                if(map(x,y - 1).getType() == PAVEMENT || map(x,y - 1).getType() == HALLWAY) 
                {
                    y = y - 1;
                }
                break;

            case 'j':
            case KEY_DOWN:
                if(map(x,y + 1).getType() == PAVEMENT || map(x,y + 1).getType() == HALLWAY) 
                {
                    y = y + 1;
                }
                break;

            case 'h':
            case KEY_LEFT:
                if(map(x - 1,y).getType() == PAVEMENT || map(x - 1,y).getType() == HALLWAY) 
                {
                    x = x - 1;
                }
                break;

            case 'l':
            case KEY_RIGHT:
                if(map(x + 1,y).getType() == PAVEMENT || map(x + 1,y).getType() == HALLWAY) 
                {
                    x = x + 1;
                }
                break;
#ifdef DEBUG
            case 'p':
                for(int i = 0; i < map.getHeight(); i++)
                    for(int j = 0; j < map.getWidth(); j++)
                        map(j,i).setVisible(true);
#endif
        }
        player.setPosition(x,y);
        if(map(x,y).getId() != "")
        {
            map.setVisible(map(x,y).getId());
        }
        else
        {
            map.showAround(x,y);
        }
        printMap(player);
        info.clear();
        writeInfo(info,player);
    }
}

void writeInfo(Window& win,PlayableCharacter& pg){
    win.box();
    win.printLine(pg.getName());
    win.printLine("LP: " + to_string(pg.getLP()) + '/' + to_string(pg.getLPMAX()));
    win.printLine("MP: " + to_string(pg.getMP()) + '/' + to_string(pg.getMPMAX()));
    win.printLine("ATK: " + to_string(pg.getATK()));
    win.printLine("DEF: " + to_string(pg.getDEF()));
}
