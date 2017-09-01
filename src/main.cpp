#include "../include/Menu.h"
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
    bool player = false;
    int choice = mainMenu();
    endCurses();
    switch(choice)
    {
        case 0:
            startCurses();
            choice = playerChoiceMenu();
            player = true;
            break;
        case 1:
            cout << "You selected Credits" << endl;
            break;
        case 2:
            cout << "You selected Quit" << endl;
            break;
    }
    endCurses();
    if(player)
        switch(choice)
        {
            case 0:
                cout << "You selected Stocazzo" << endl;
                break;
            case 1:
                cout << "You selected Staminchia" << endl;
                break;
            case 2:
                cout << "You selected Stograncazzo" << endl;
                break;
            case 3:
                cout << "You selected Vaffanculo" << endl;
                break;
            case 4:
                cout << "You selected Porcodio" << endl;
                break;
            case 5:
                cout << "Ti coddiri" << endl;
                break;
        }
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
    Menu players((COLS - 10)/2,(LINES - 10)/2,6,"Stocazzo","Staminchia","Stogran cazzo","Vaffanculo","Porcodio","SardiniaNoEstItalia");
    return players.handleChoice();
}
