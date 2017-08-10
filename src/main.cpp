#include <limits.h>
#include <ncurses.h>
#include <math.h>
#include "../include/Graph.h"
#include "../include/Map.h"
#include "../include/Room.h"
#include "../include/dequeue.h"
#include "../include/HashTable.h"
#include "../include/List.h"
#include "../include/utility.hpp"
#include <iostream>

#define HEIGHT 37
#define WIDTH 100

void printMap(Map& M);
// Prints the map M

void setUpMap(Map& M);
// Sets up the Map for the level

void handleMovement(Map& M);
// Handles the movement of the main character

int main()
{
    Map M(WIDTH,HEIGHT);
    M.generate(10);
    setUpMap(M);
    handleMovement(M);
}

void handleMovement(Map& M)
{
    int x,y,c;
    getyx(stdscr,y,x);
    x--;
    M.showAround(x,y);      // the cursor is to the immediate right of the char
    while((c = getch()) != 'q')
    {
        switch(c)
        {
            case 'k':
            case KEY_UP:
                if(M(x,y - 1).getType() == PAVEMENT || M(x,y - 1).getType() == HALLWAY) 
                {
                    M.showAround(x, y - 1);
                    printMap(M);
                    mvaddch(y,x,' ');
                    mvaddch(y - 1,x,'@');
                }
                break;

            case 'j':
            case KEY_DOWN:
                if(M(x,y + 1).getType() == PAVEMENT || M(x,y + 1).getType() == HALLWAY) 
                {
                    M.showAround(x, y + 1);
                    printMap(M);
                    mvaddch(y,x,' ');
                    mvaddch(y + 1,x,'@');
                }
                break;

            case 'h':
            case KEY_LEFT:
                if(M(x - 1,y).getType() == PAVEMENT || M(x - 1,y).getType() == HALLWAY) 
                {
                    M.showAround(x - 1, y);
                    printMap(M);
                    mvaddch(y,x,' ');
                    mvaddch(y,x - 1,'@');
                }
                break;

            case 'l':
            case KEY_RIGHT:
                if(M(x + 1,y).getType() == PAVEMENT || M(x + 1,y).getType() == HALLWAY) 
                {
                    M.showAround(x + 1, y);
                    printMap(M);
                    mvaddch(y,x,' ');
                    mvaddch(y,x + 1,'@');
                }
                break;
#ifdef DEBUG
            case 'p':
                for(int i = 0; i < M.getHeight(); i++)
                    for(int j = 0; j < M.getWidth(); j++)
                        M(j,i).setVisible(true);
#endif
        }
        getyx(stdscr,y,x);
        x = x - 1;
        if(M(x,y).getId() != "")
        {
            M.setVisible(M(x,y).getId());
            printMap(M);
            mvaddch(y,x,'@');
        }
        refresh();
    }
    endwin();
}

void setUpMap(Map& M)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr,true);
    curs_set(0);
    Room R;
    Point p;
    R = M.pickRoom();
    M.setVisible(R.getId());
    p = R.pickPoint();
    printMap(M);
    mvaddch(p.y,p.x,'@');
    refresh();
}

void printMap(Map& M)
{
    int x,y;
    getyx(stdscr,y,x);
    move(0,0);
    for( int i = 0; i < M.getHeight(); i++)
    {
        for (int j = 0; j < M.getWidth(); j++)
        {
            if(M(j,i).isVisible())
                addch(M(j,i).getSymbol());
            else
                addch(' ');
        }
        printw("\n");
    }
    move(y,x);
    refresh();
}
