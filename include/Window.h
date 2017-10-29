#ifndef MY_WINDOW_H
#define MY_WINDOW_H
#include <ncurses.h>
#include <panel.h>
#include <string>
    /**
      Wrapper for the ncurses window
       */
class Window
{
    private:

        WINDOW* win;
        PANEL* panel;
        int x,y,nlines,ncols, firstAvailableLine;

    public:

        Window(const int x, const int y, const int nlines, const int ncols);
        // Given position coordinates and the number of lines and columns, it creates a new window

        ~Window();
        // Destructor

        void readFromFile(const std::string filename);
        // Given a filename, it writes its contents in the window

        void printLine(const std::string);
        //  Stampa una stringa e poi va a capo

        void separator();
        //  Stampa una riga di trattini

        void box();
        // Prints a box around the window

        void clear();
        // Clears the window

        void clean();
        // Cleans the window, keeping the box
        // Use only with boxed windows

        WINDOW *getWin() const;
        // Returns the WINDOW pointer

        void show();
        // Shows the panel of the window

        void hide();
        // Hides the panel of the window

        void print(std::string str);
        // Prints the string str to the window, wrapping it if necessary

};

std::string wrap(const std::string text,const unsigned int maxLength);
// Given a text and a limit length, it wraps the text to respect the given text width and returns it as a string

#endif
