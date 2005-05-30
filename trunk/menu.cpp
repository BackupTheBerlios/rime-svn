#include <ncurses.h>
#include <menu.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "control.h"

#define ARRAY_SIZE(a) ( sizeof(a) / sizeof(a[0]) )


Menu::Menu(EventDispatcher * pEd) : ControlObject(pEd)
{
}

void Menu::draw()
{
    
    char* choices[] = {"Choice 1","Choice 2","Quit"};
    int n_choices, i, c, ch = 1;
    char stare[20];
    
    WINDOW *pMyMenuWin;
    MENU *pMyMenu;
    ITEM **pMyItems;
    
    
    n_choices = ARRAY_SIZE(choices);
    pMyItems = (ITEM**)calloc(n_choices+1, sizeof(ITEM*));
    
    for(i=0;i<n_choices;i++)
	pMyItems[i] = new_item(choices[i], "");
	
    pMyItems[n_choices] = (ITEM*)NULL;
    pMyMenu = new_menu((ITEM**)pMyItems);
    refresh();
    set_menu_format(pMyMenu,1,3);
    pMyMenuWin = newwin(0,COLS,LINES-1,0);
    keypad(pMyMenuWin,TRUE);
    set_menu_win(pMyMenu,pMyMenuWin);
    set_menu_mark(pMyMenu,"*");
    
    post_menu(pMyMenu);
    wrefresh(pMyMenuWin);
    
    strcpy(stare,"begin");
    while(strcmp(stare,"Quit") != 0)///cat timp nu s-a ales optiunea "Quit"
    {
	wrefresh(pMyMenuWin);
	
	c = wgetch(pMyMenuWin);
	
	switch(c)
	{
	    case KEY_RIGHT:
		menu_driver(pMyMenu,REQ_RIGHT_ITEM);
		break;
		
	    case KEY_LEFT:
		menu_driver(pMyMenu,REQ_LEFT_ITEM);
		break;
		
	    case 13: ///daca s-a apasat tasta "Enter"
		strcpy(stare,item_name(current_item(pMyMenu)));
		break;
		
	}///end switch
    }///end while
    unpost_menu(pMyMenu);
    for(i=0;i<n_choices;i++)    
	free_item(pMyItems[i]);
    
    free_menu(pMyMenu);
    refresh();
}

int Menu::processEvent(Event &ev)
{
}
