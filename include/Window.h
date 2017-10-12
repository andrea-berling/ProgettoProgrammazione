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
        int x,y,nlines,ncols, firstAvailableLine;

    public:

        Window(int x, int y, int nlines, int ncols);
        // Given position coordinates and the number of lines and columns, it creates a new window

        ~Window();
        // Destructor

        void readFromFile(std::string filename);
        // Given a filename, it writes its contents in the window

        void printLine(std::string);
        //  Stampa una stringa e poi va a capo

        void separator();
        //  Stampa una riga di trattini

        void box();
        // Prints a box around the window

        void clear();
        // Clears the window

        WINDOW *getWin();
        // Returns the WINDOW pointer
};

std::string wrap(std::string text,unsigned int maxLength);
// Given a text and a limit length, it wraps the text to respect the given text width and returns it as a string
#endif
