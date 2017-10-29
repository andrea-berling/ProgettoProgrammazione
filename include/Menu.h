#ifndef MYMENU_H
#define MYMENU_H
#include <cstdarg>
#include <ncurses.h>
#include <panel.h>
#include <list>
#include <vector>
#include <string>
#include <menu.h>

class Menu
{
    private:

        ITEM **items;
        MENU *menu;
        PANEL *menupanel;
        WINDOW *menuwin;
        WINDOW *subwin;
        char **choices;
        int choice;
        int nlines;
        int ncols;
        int x;
        int y;

        void createMenu();
        // Once the items and choices arrays have been filled, creates a new menu

    public:

        Menu(const int x, const int y, std::vector<std::string> options);
        // Given two position coordinates and the options, as strings in a vector, it creates a new menu

        Menu(const int x, const int y, const int n, const std::string option1, ...);
        // Given two position coordinates, the number of the options and the options, as strings, it creates a new menu

        ~Menu();
        // Destructor

        int handleChoice();
        // Lets an user navigate the menu and choose an option from it
        // Returns an int correponding to the positon of the choice (0 is first)

        int getX() const;
        // Returns the x coordinate of the top left corner of the window

        int getY() const;
        // Returns the y coordinate of the top left corner of the window
};

#endif
