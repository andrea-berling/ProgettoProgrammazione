#include "../include/Menu.h"
#include "../include/Window.h"
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

void freeMainMenu(int n_choices,ITEM** my_items,char** choices,MENU* my_menu,WINDOW* menuwin);
// Frees up the memory used by the main menu parts

int playerChoiceMenu();
// Sets up the menu that lets the player choose the character
// Returns an int corresponding to the choice made

void endCurses();
// Ends curses mode

int main()
{	
    startCurses();
    int choice = mainMenu();
    switch(choice)
    {
        case 0:
            startCurses();
            choice = playerChoiceMenu();
            break;
        case 1:
            cout << "You selected Credits" << endl;
            break;
        case 2:
            cout << "You selected Quit" << endl;
            break;
    }
    endCurses();
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
    Menu players((COLS)/2 - 25,(LINES - 10)/2,6,"Stocazzo","Staminchia","Stogran cazzo","Vaffanculo","Porcodio","SardiniaNoEstItalia");
    Window description(players.getX() + 20,players.getY() - 5,19,70);
    bool done = false;
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
                filename += "stocazzo.desc";
                break;
            case 1:
                filename += "staminchia.desc";
                break;
            case 2:
                filename += "stograncazzo.desc";
                break;
            case 3:
                filename += "vaffanculo.desc";
                break;
            case 4:
                filename += "porcodio.desc";
                break;
            case 5:
                filename += "sardinia.desc";
                break;
        }
        description.readFromFile(filename);
        confirm = players.handleChoice();
        if(confirm == choice)
            done = true;
        else
            choice = confirm;
    }
}
