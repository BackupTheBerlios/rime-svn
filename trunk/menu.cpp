#include <ncurses.h>
#include <menu.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "control.h"
#include "controlpanel.h"

Menu::Menu(EventDispatcher * pEd) : ControlObject(pEd)
{
  choices.push_back("Choice 1");
  choices.push_back("Choice 2");
  choices.push_back("Quit");

  
  pMyItems = (ITEM**)calloc(choices.size() + 1, sizeof(ITEM*));
    
  for(unsigned int i = 0; i < choices.size(); i++)
	pMyItems[i] = new_item(choices[i].c_str(), "");
	
  pMyItems[choices.size()] = (ITEM*)NULL;
  pMyMenu = new_menu((ITEM**)pMyItems);
  refresh();
  set_menu_format(pMyMenu,1,3);
  win = newwin(0, COLS, 0, 0);
  keypad(win,TRUE);
  set_menu_win(pMyMenu,win);
  set_menu_mark(pMyMenu,"*");
    
  post_menu(pMyMenu);
  stare = "begin";
}

Menu::~Menu()
{
  unpost_menu(pMyMenu);
  for(unsigned int i = 0; i < choices.size(); i++)    
  	free_item(pMyItems[i]);
    
  free_menu(pMyMenu);
  refresh();
}
void Menu::draw()
{
  clog << "Menu::draw()" << endl;
  wrefresh(win);
}

int Menu::processEvent(const Event &ev)
{
  clog << "Got an event" << endl;

  if(ev.getType() == Event::EV_CHARACTER)
    {
      clog << "The event is " << ev.getValue() << " != " << KEY_RIGHT << " " << KEY_LEFT << " " << KEY_ENTER << endl;
      switch(ev.getValue())
        {
	    case KEY_RIGHT:
          menu_driver(pMyMenu,REQ_RIGHT_ITEM);
          break;
		
	    case KEY_LEFT:
          menu_driver(pMyMenu,REQ_LEFT_ITEM);
          break;
		
	    case 13: ///daca s-a apasat tasta "Enter"
          stare = item_name(current_item(pMyMenu));
          break;
        }
    }

  if(stare == "Quit")
    {
      ControlPanel::cPanel.pushEvent(Event(Event::EV_QUIT, 0));
      return 0;
    }

  ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW, 0));
  
  return 0;
}
