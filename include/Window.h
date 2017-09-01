#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include <ncurses.h>
#include <string>
    /**
      Wrapper for the ncurses window
       */
class Window
{
    private:

        WINDOW* win;
        int x,y,nlines,ncols;

    public:

        Window(int x, int y, int nlines, int ncols);
        // Given position coordinates and the number of lines and columns, it creates a new window

        ~Window();
        // Destructor

        void readFromFile(std::string filename);
        // Given a filename, it writes its contents in the window
};
#endif
