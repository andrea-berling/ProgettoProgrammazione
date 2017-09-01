#include "../include/Menu.h"
#include <cstring>
#include <cstdlib>

using namespace std;

Menu::Menu(int x, int y, int n, string option1, ...):x(x),y(y)
{
    va_list args;
    va_start(args,option1);
    nlines = n;

    string max = option1;
    ncols = max.length();

    for(int i = 0; i < n - 1; i++) // given n arguments, the variadic arguments are n - 1
    {
        string current(va_arg(args,char*));
        if(current.length() > ncols)
        {
            max = current;
            ncols = current.length();
        }
    }   // finds the longest string and assigns its length to ncols

    choices = (char**)malloc(nlines*sizeof(char*)); // Given nlines choices, an array of nlines char arrays is
    // allocated
    items = (ITEM**)malloc((nlines + 1)*sizeof(ITEM*));

    va_start(args,option1);
    choices[0] = (char*)malloc(ncols*sizeof(char));
    strcpy(choices[0],option1.c_str());
    items[0] = new_item(choices[0],nullptr); 

    for(int i = 1; i < nlines; i++)
    {
        choices[i] = (char*)malloc(ncols*sizeof(char)); // ncols is the length of the longest string in the list
        strcpy(choices[i],va_arg(args,char*));
        items[i] = new_item(choices[i],nullptr); 
    }
    items[nlines] = nullptr;
    
    menuwin = newwin(nlines + 1,ncols,y,x);
    subwin = derwin(menuwin,nlines,ncols,1,0); // The items show up one line after the title, at the same indentation
    //level as the title
    keypad(menuwin,TRUE); // Lets the user use arrow keys
    keypad(subwin,TRUE);
    
    menu = new_menu(items);
    set_menu_win(menu,menuwin);
    set_menu_sub(menu,subwin);

    set_menu_mark(menu,"");
    curs_set(0);

    post_menu(menu);
    wrefresh(menuwin);
}

Menu::~Menu()
{
    unpost_menu(menu);
    wrefresh(menuwin);
    for(int i = 0; i < nlines; i++)
    {
        free_item(items[i]);
        free(choices[i]);
    }
    free(choices);
    free(items);
	free_menu(menu);
    delwin(subwin);
    delwin(menuwin);
}

int Menu::handleChoice()
{
    int choice = -1;
    bool done = false;
    int c;

	while(!done)
	{   
        c = wgetch(menuwin);
        switch(c)
	    {	
            case KEY_DOWN:
		        menu_driver(menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(menu, REQ_UP_ITEM);
				break;
            case 10:
                ITEM* cur_item = current_item(menu);
                int i = 0;
                while(i < nlines && choice == -1)
                {
                    if(strcmp(item_name(cur_item),choices[i]) == 0)
                        choice = i;
                    i++;
                }
                done = true;
                break;
		}
        wrefresh(menuwin);
	}	
    return choice;
}
