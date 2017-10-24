#include "../include/Window.h"
#include <boost/tokenizer.hpp>
#include <fstream>

using namespace std;
using namespace boost;

Window::Window(int x, int y, int nlines, int ncols):x(x),y(y),nlines(nlines),ncols(ncols)
{
    win = newwin(nlines,ncols,y,x);
    panel = new_panel(win);
    update_panels();
    doupdate();
    firstAvailableLine = 1;
}
// Given position coordinates and the number of lines and columns, it creates a new window

Window::~Window()
{
    werase(win);
    wrefresh(win);
    del_panel(panel);
    update_panels();
    doupdate();
    delwin(win);
}
// Destructor

void Window::readFromFile(string filename)
{
    ifstream file(filename);
    string line;
    string description = "";
    
    while(file)
    {
        getline(file,line);
        if(line.front() != ' ')
            description += " " + line;
        else
            description += line;
    }
    print(description);
}
// Given a filename, it writes its contents in the window

string wrap(string text,unsigned int maxLength)
{
    int length = 0;
    char_separator<char> sep(" ");
    string buffer = "";
    tokenizer<char_separator<char>> tokens(text,sep);
    for(string token : tokens)
    {
        if(token.length() + length + 1 > maxLength) // +1 for the space
        {
            buffer += "\n" + token + " ";
            length = token.length() + 1;
        }
        else
        {
            buffer += token + " ";
            length += token.length() + 1;
        }
    }
    return buffer;
}
// Given a text and a limit length, it wraps the text to respect the given text width and returns it as a string

void Window::printLine(string line) {
    if (line.length() < ncols) {
        mvwprintw(win,firstAvailableLine,1,line.c_str());
        firstAvailableLine++;
        wrefresh(win);
    }
}

void Window::separator(){
    for (int i = 1; i < ncols - 1; i++) {
        mvwaddch(win, firstAvailableLine, i, '-');
    }
    firstAvailableLine++;
    wrefresh(win);
}

void Window::box()
{
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    wrefresh(win);
}

void Window::clear()
{
    wclear(win);
    wrefresh(win);
    firstAvailableLine = 1;
}

WINDOW *Window::getWin()
{
    return win;
}

void Window::show()
{
    show_panel(panel);
    update_panels();
    doupdate();
}

void Window::hide()
{
    hide_panel(panel);
    update_panels();
    doupdate();
}

void Window::clean()
{
    clear();
    box();
}

void Window::print(string str)
{
    str = wrap(str, ncols - 1);
    char_separator<char> sep("\n");
    tokenizer<char_separator<char>> tokens(str,sep);
    for(string line : tokens)
        printLine(line);
}
