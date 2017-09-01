#ifndef MYMENU_H
#define MYMENU_H
#include <cstdarg>
#include <ncurses.h>
#include <string>
#include <menu.h>
#include "List.h"

class Menu
{
    private:

        ITEM** items;
        MENU* menu;
        WINDOW* menuwin;
        WINDOW* subwin;
        char** choices;
        int nlines;
        int ncols;
        int x;
        int y;

    public:

        Menu(int x, int y, int n, std::string option1, ...);
        // Given two position coordinates, the number of the options and the options, as strings, it creates a new menu

        ~Menu();
        // Destructor

        int handleChoice();
        // Lets an user navigate the menu and choose an option from it
        // Returns an int correponding to the positon of the choice (0 is first)

};

#endif
