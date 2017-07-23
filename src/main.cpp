#include <cstdlib>
#include <cstring>
#include <ncurses.h>
#include <menu.h>
#include <errno.h>

int main()
{	
    char** choices;
    ITEM **my_items;
	int c;				
	MENU *my_menu;
	int n_choices, i;
	ITEM *cur_item;
    WINDOW *menuwin;
	
    choices = (char**) malloc(4*sizeof(char*));
    for(int i = 0; i < 4; i++)
        choices[i] = (char*) malloc(15*sizeof(char));
    strcpy(choices[0],"New Game");	
    strcpy(choices[1],"Load Game");	
    strcpy(choices[2],"Credits");	
    strcpy(choices[3],"Quit");	
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	refresh();
	
	n_choices = 4;
	my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));

	for(i = 0; i < n_choices; ++i)
	        my_items[i] = new_item(choices[i],NULL);
	my_items[n_choices] = (ITEM *)NULL;

    menuwin = newwin(5,15,(LINES - 10)/2,(COLS - 10)/2);
	keypad(menuwin, TRUE);
    wrefresh(menuwin);

	my_menu = new_menu((ITEM **)my_items);
    set_menu_mark(my_menu," ");
    set_menu_win(my_menu,menuwin);
    set_menu_sub(my_menu,menuwin);
	mvprintw(LINES - 2, 0, "F1 to Exit");
	post_menu(my_menu);
    wrefresh(menuwin);
    refresh();

    bool done = false;

	while(!done && (c = wgetch(menuwin)) != KEY_F(1))
	{   switch(c)
	    {	case KEY_DOWN:
		        menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
            case 10:
                cur_item = current_item(my_menu);
                char* name = (char*) malloc(15*sizeof(char));
                strcpy(name,item_name(cur_item));
                if(strcmp(name,choices[3]) != 0)
                {
                    mvprintw(0,0,"You selected %s\n",name);
                    refresh();
                }
                else
                    done = true;
                break;
		}
        wrefresh(menuwin);
	}	

    for(int i = 0; i < n_choices; i++)
    {
        free_item(my_items[i]);
        free(choices[i]);
    }
    free(choices);
    free(my_items);
	free_menu(my_menu);
    delwin(menuwin);
	endwin();
}
