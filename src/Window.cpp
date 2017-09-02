#include "../include/Window.h"
#include <boost/tokenizer.hpp>
#include <fstream>

using namespace std;
using namespace boost;

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
    string description = "";
    int length = 0;
    string title;
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
