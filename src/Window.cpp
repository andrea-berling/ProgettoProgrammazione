#include "../include/Window.h"
#include <fstream>

using namespace std;

Window::Window(int x, int y, int nlines, int ncols):x(x),y(y),nlines(nlines),ncols(ncols)
{
    win = newwin(nlines,ncols,y,x);
}
// Given position coordinates and the number of lines and columns, it creates a new window

Window::~Window()
{
    delwin(win);
}
// Destructor

void Window::readFromFile(string filename)
{
    werase(win);
    wrefresh(win);
    ifstream file(filename);
    string line;
    string buffer = "";
    while(file)
    {
        getline(file,line);
        buffer += line + "\n";
    }
    wprintw(win,buffer.c_str());
    wrefresh(win);
}
// Given a filename, it writes its contents in the window
