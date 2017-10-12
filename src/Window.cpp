#include "../include/Window.h"
#include <boost/tokenizer.hpp>
#include <fstream>

using namespace std;
using namespace boost;

Window::Window(int x, int y, int nlines, int ncols):x(x),y(y),nlines(nlines),ncols(ncols)
{
    win = newwin(nlines,ncols,y,x);
    firstAvailableLine = 1;
}
// Given position coordinates and the number of lines and columns, it creates a new window

Window::~Window()
{
    werase(win);
    wrefresh(win);
    delwin(win);
}
// Destructor

void Window::readFromFile(string filename)
{
    ifstream file(filename);
    string line;
    string description = "";
    string title;
    
    werase(win);
    wrefresh(win);
    getline(file,title);
    title = wrap(title,ncols);
    while(file)
    {
        getline(file,line);
        description += line;
    }
    description = wrap(description, ncols);
    description = title + '\n' + description;
    wprintw(win,description.c_str());
    wrefresh(win);
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
        line += '\n';
        mvwprintw(win,firstAvailableLine,1,line.c_str());
        wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
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
