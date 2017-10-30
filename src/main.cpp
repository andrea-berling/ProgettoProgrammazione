#include "../include/Menu.h"
#include "../include/Window.h"
#include "../include/Level.h"
#include "../include/personaggiGiocabili.h"
#include <list>
#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include <menu.h>
#include <iostream>
#include <fstream>

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

void showStory();
// Creates a window that shows the main story

void setCharacter(PlayableCharacter& player, int character);
// Sets the chosen character as player

list<Level>::iterator createLevel(list<Level>& levels, LevelConfig& config, PlayableCharacter& player, Window& mapWindow, Window& infoWindow);
// Creates a new level, stores it in the given levels list and returns an iterator pointing to it. Furthermore it
// prints the map and the stats of the player

void showCredits();
// Displays the credits for the game

void showEpilogue(status_t status);
// Displays the epilogue of the game, based on the given status

int main()
{	
    int choice;
    bool quit = false;
    int character = -1;
    srand(time(0));
    startCurses();

    while(character == -1 && !quit)
    {
        choice = mainMenu();
        switch(choice)
        {
            case 0:
                character = playerChoiceMenu();
                break;
            case 1:
                showCredits();
                break;
            case 2:
                quit = true;
                break;
        }
    }
    if(!quit) 
    {
        status_t status = DEFAULT;
        // level, width, height, rooms, monsters, items
        LevelConfig config = {1,100,37,2,1,1};
        Window mapWindow(0,0,config.height,config.width), infoWindow(101, 0, 37, 30), bottomWindow(0, 37, 10, 100);
        list<Level> levels;
        list<Level>::iterator currentLevel;
        PlayableCharacter player;
        bool done = false;

        clear();
        refresh();
        showStory();    // Shows the main story

        setCharacter(player,character);
        currentLevel = createLevel(levels,config,player,mapWindow,infoWindow);                   
        showInstructions();
        bottomWindow.box();

        while(!done)
        {
            status = (*currentLevel).handleTurn(mapWindow,infoWindow,bottomWindow,player);
            if(status != LOSS && status != WIN && status != QUIT)
            {
                switch(status)
                {
                    case UP:
                        ++currentLevel;
                        if(currentLevel == levels.end())
                        {
                            // Creation of a new level
                            config.newLevel();
                            player.LVLup();
                            mapWindow.clear();
                            currentLevel = createLevel(levels,config,player,mapWindow,infoWindow);                   
                        }
                        else
                            (*currentLevel).placeCharacter(player,DOWNSTAIRS); // no need to increment, the increment was done in the if part
                        break;
                    case DOWN:
                        if(currentLevel != levels.begin())
                        {
                            currentLevel--;
                            (*currentLevel).placeCharacter(player,UPSTAIRS);
                        }
                        break;
                }
                (*currentLevel).printMap(player.getPosition(),mapWindow);
                infoWindow.clear();
                (*currentLevel).writeInfo(infoWindow,player);
            }
            else
            {
                if(status != QUIT)
                {
                    mapWindow.clear();
                    infoWindow.clear();
                    bottomWindow.clear();
                    showEpilogue(status);
                }
                done = true;
            }
        }
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
        string name;
        string classe;
        switch(choice)
        {
            case 0:
                name = "Gaudenzio";
                classe = "Guerriero";
                filename += "gaudenzio.desc";
                stats = "LP: 15 MP: 0 DEF: 15 ATK: 9 LUCK: 5 COINS: 30";
                break;
            case 1:
                name = "Peppino";
                classe = "Mago";
                filename += "peppino.desc";
                stats = "LP: 10 MP: 9 DEF: 8 ATK: 5 LUCK: 5 COINS: 30";
                break;
            case 2:
                name = "Badore";
                filename += "badore.desc";
                classe = "Ladro";
                stats = "LP: 10 MP: 0 DEF: 5 ATK: 8 LUCK: 12 COINS: 60";
                break;
            case 3:
                done = true;
                break;
        }
        if(!done)
        {
            description.clear();
            description.printLine(name);
            description.printLine("");
            description.printLine("Classe: " + classe);
            description.printLine("");
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

void showStory()
{
    Window storyWin(COLS/3,LINES/5,30,70);
    storyWin.readFromFile("resources/storia.dat");
    storyWin.printLine("Premi un tasto per continuare...");
    getch();
}

void setCharacter(PlayableCharacter& player, int character)
{
    switch(character)
    {
        case 0:
            player = PlayableCharacter(15,0,15,9,5,30,"Gaudenzio");
            break;
        case 1:
            player = PlayableCharacter(10,9,8,5,5,30,"Peppino");
            break;
        case 2:
            player = PlayableCharacter(10,0,5,8,12,60,"Badore");
            break;
    }
}

list<Level>::iterator createLevel(list<Level>& levels,LevelConfig& config, PlayableCharacter& player, Window& mapWindow, Window& infoWindow)
{
    list<Level>::iterator it;
    levels.push_back(Level(config,player));
    it = --levels.end();   // last element of the list
    (*it).placeCharacter(player,RANDOM);   // place the player in a random room
    (*it).printMap(player.getPosition(),mapWindow);
    (*it).writeInfo(infoWindow,player);
    return it;
}

void showCredits()
{
    Window creditsWin(COLS/3 + 10,LINES/3,30,70);
    ifstream credits("resources/credits.dat");
    string line;
    while(credits)
    {
        getline(credits,line);
        creditsWin.printLine(line);
    }
    getch();
}

void showEpilogue(status_t status)
{
    Window epilogueWin(COLS/3,LINES/5,30,70);
    ifstream file;
    string filePath="resources/";
    switch(status)
    {
        case WIN:
            filePath += "victory.dat";
            break;
        case LOSS:
            filePath += "loss.dat";
            break;
    }
    epilogueWin.readFromFile(filePath);
    getch();
}
