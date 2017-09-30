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
    if(quit == true) 
        endCurses();
    else
    {
        Window infoWindow(101, 0, 37, 20);
        int width = 100;
        int height = 37;
        int status = -1;
        clear();
        refresh();
        PlayableCharacter player;
        switch(character)
        {
            case 0:
                player = PlayableCharacter(15,0,20,12,"Gaudenzio");
                break;
            case 1:
                player = PlayableCharacter(10,20,10,8,"Peppino");
                break;
            case 2:
                player = PlayableCharacter(10,0,5,12,"Badore");
                break;
        }
        list<Level> levels;
        list<Level>::iterator currentLevel;
        int n = 1;
        int rooms = 10;
        int items = 2;
        int monsters = 2;
        levels.insert(levels.begin(),Level(n,width,height,rooms,items,monsters));
        currentLevel = levels.begin();
        (*currentLevel).placeCharacter(player,0);
        (*currentLevel).printMap(player);
        writeInfo(infoWindow,player);
        while(status != 0)
        {
            int playerPosition;
            status = (*currentLevel).handleMovement(infoWindow,player);
            if(status == 1)
            {
                ++currentLevel;
                if(currentLevel == levels.end())
                {
                    ++n;
                    Level newLevel = Level(n,width,height,rooms,items,monsters);
                    currentLevel = levels.insert(levels.end(),newLevel);
                    playerPosition = 0;
                }
                else
                {
                    playerPosition = 1; // no need to increment, the increment was done in the if part
                }
            }
            else if(status == -1)
            {
                if(currentLevel != levels.begin())
                    currentLevel--;
                playerPosition = -1;
            }
            (*currentLevel).placeCharacter(player,playerPosition);
            (*currentLevel).printMap(player);
            infoWindow.clear();
            writeInfo(infoWindow,player);
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
    bool done = false, close = false;
    int choice = -1;
    int confirm; 

    while(!done)
    {
        string filename = "resources/descriptions/";
        if(choice == -1)    // The first time choice is uninitialized (= -1); the next times this won't be necessary
            choice = players.handleChoice();
        switch(choice)
        {
            case 0:
                filename += "gaudenzio.desc";
                break;
            case 1:
                filename += "peppino.desc";
                break;
            case 2:
                filename += "badore.desc";
                break;
            case 3:
                close = true;
                break;
        }
        if(!close)
        {
            description.readFromFile(filename);
            confirm = players.handleChoice();
            if(confirm == choice)
                done = true;
            else
                choice = confirm;
        }
        else
        {
            return -1;   // The player hit back, no charater was selected
        }
    }

    return choice;
}

