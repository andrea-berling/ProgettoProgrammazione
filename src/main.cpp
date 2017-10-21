#include "../include/Menu.h"
#include "../include/Window.h"
#include "../include/Level.h"
#include "../include/personaggiGiocabili.h"
#include <list>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include <menu.h>
#include <errno.h>
#include <iostream>

using namespace std;

void startCurses();
// Sets up and starts curses mode

int mainMenu();
// Sets up and handles the main menu of the game (New Game, Credits, etc) 
// Returns an int corresponding to the choice made

int playerChoiceMenu();
// Sets up the menu that lets the player choose the character
// Returns an int corresponding to the choice made

void endCurses();
// Ends curses mode

int main()
{	
    int choice;
    bool quit = false;
    int character = -1;
    srand(time(0));

    while(character == -1 && !quit)
    {
        startCurses();
        choice = mainMenu();
        switch(choice)
        {
            case 0:
                character = playerChoiceMenu();
                break;
            case 1:
                quit = true;
                // To implement the credits window
                break;
            case 2:
                quit = true;
                break;
        }
    }
    if(!quit) 
    {
        int mapWidth = 100, mapHeight = 37, n = 1, rooms = 10, items = 5, monsters = 5, status = -1;
        Window mapWindow(0,0,mapHeight,mapWidth), infoWindow(101, 0, 37, 30), bottomWindow(0, 37, 10, 100);
        list<Level> levels;
        list<Level>::iterator currentLevel;
        PlayableCharacter player;
        bool done = false;
        int positionPreference = 0;

        clear();
        refresh();
        bottomWindow.box();

        switch(character)
        {
            case 0:
                player = PlayableCharacter(15,0,20,12,5,30,"Gaudenzio");
                break;
            case 1:
                player = PlayableCharacter(10,9,10,8,5,30,"Peppino");
                break;
            case 2:
                player = PlayableCharacter(10,0,5,12,10,60,"Badore");
                break;
        }

        levels.insert(levels.begin(),Level(n,mapWidth,mapHeight,rooms,items,monsters, player));
        currentLevel = levels.begin();
        (*currentLevel).placeCharacter(player,positionPreference);   // place the player in a random room
        (*currentLevel).printMap(player.getPosition(),mapWindow);
        writeInfo(infoWindow,player,(*currentLevel).getLevel());
        while(!done)
        {
            status = (*currentLevel).handleTurn(mapWindow,infoWindow,bottomWindow,player);
            if(status != 0 && status != 2)
            {
                switch(status)
                {
                    case 1:
                        ++currentLevel;
                        if(currentLevel == levels.end())
                        {
                            // Creation of a new level
                            ++n;
                            mapWindow.clear();
                            Level newLevel = Level(n,mapWidth,mapHeight,rooms,items,monsters, player);
                            currentLevel = levels.insert(levels.end(),newLevel);
                            positionPreference = 0;
                        }
                        else
                            positionPreference = 1; // no need to increment, the increment was done in the if part
                        break;
                    case -1:
                        if(currentLevel != levels.begin())
                        {
                            currentLevel--;
                            positionPreference = -1;
                        }
                        break;
                }
                (*currentLevel).placeCharacter(player,positionPreference);
                (*currentLevel).printMap(player.getPosition(),mapWindow);
                infoWindow.clear();
                writeInfo(infoWindow,player,(*currentLevel).getLevel());
            }
            else
            {
                switch(status)
                {
                    case 2:
                        // Victory
                        break;
                    case 0:
                        // Loss
                        break;
                }

                done = true;
            }
        }
        // Generate the map with the given character
    }

    endCurses();

    return 0;
}

void startCurses()
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	refresh();
}

int mainMenu()
{
    Menu mainMenu((COLS - 10)/2,(LINES - 10)/2,3,"New Game","Credits","Quit");
    refresh();
    return mainMenu.handleChoice();
}

void endCurses()
{
	endwin();
}

int playerChoiceMenu()
{
    Menu players((COLS)/2 - 25,(LINES - 10)/2,4,"Gaudenzio","Peppino","Badore","Indietro");
    Window description(players.getX() + 20,players.getY() - 5,19,70);
    string stats;
    bool done = false;
    int choice = -1;
    int confirm; 

    choice = players.handleChoice();
    while(!done)
    {
        string filename = "resources/descriptions/";
        switch(choice)
        {
            case 0:
                filename += "gaudenzio.desc";
                stats = "LP: 15 MP: 0 DEF: 20 ATK: 12 LUCK: 5 COINS: 30";
                break;
            case 1:
                filename += "peppino.desc";
                stats = "LP: 10 MP: 9 DEF: 10 ATK: 8 LUCK: 5 COINS: 30";
                break;
            case 2:
                filename += "badore.desc";
                stats = "LP: 10 MP: 0 DEF: 5 ATK: 12 LUCK: 10 COINS: 60";
                break;
            case 3:
                done = true;
                break;
        }
        if(!done)
        {
            description.readFromFile(filename);
            description.separator();
            description.printLine(stats);
            confirm = players.handleChoice();
            if(confirm == choice)
                done = true;
            else
                choice = confirm;
        }
        else
            choice = -1;   // The player hit back, no charater was selected
    }

    return choice;
}

