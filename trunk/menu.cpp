#include <curses.h>
#include <menu.h>
#include <malloc.h>
#include <stdio.h>

#include "menu.h"
#include "control.h"

#define ARRAY_SIZE(a) ( sizeof(a) / sizeof(a[0]) )

Menu Menu::meniu;

Menu::Menu()
{
}

void Menu::draw()
{
    
    clog<<" apel draw din clasa Menu ";
    //char* choices[] = {"Choice 1","Choice 2","Quit"};
    /*MENU *pMyMenu;
    WINDOW *pMyMenuWin;
    ITEM **pMyItems;
    int n_choices, i;
    */
    
}
int Menu::processEvent(Event &ev)
{

}
