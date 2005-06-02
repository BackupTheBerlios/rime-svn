#include <ncurses.h>
#include <menu.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "control.h"
#include "controlpanel.h"

Menu::Menu(EventDispatcher * pEd, vector<string> choices) : ControlObject(pEd)
{
  pEd->setMenu(this);
/*
  choices.push_back("File");
  choices.push_back("Edit");
  choices.push_back("View");
  choices.push_back("Help");  
 */
 
  pMyItems = (ITEM**)calloc(choices.size() + 1, sizeof(ITEM*));
    
  for(unsigned int i = 0; i < choices.size(); i++)
	pMyItems[i] = new_item(choices[i].c_str(), "");
	
  pMyItems[choices.size()] = (ITEM*)NULL;
  pMyMenu = new_menu((ITEM**)pMyItems);
  refresh();
  set_menu_format(pMyMenu,1,4);
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
      ControlPanel::cPanel.pushEvent(Event(Event::EV_QUIT));
      return 0;
    }
  if(stare == "File")///accesare File din meniul principal
    {
      ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE));
      return 0;
    }
  if(stare == "Edit")
    {
      ControlPanel::cPanel.pushEvent(Event(Event::EV_EDIT));
      return 0;
    }    
  if(stare == "Help")
    {
      ControlPanel::cPanel.pushEvent(Event(Event::EV_HELP));
      return 0;
    }
    
///////////////////////////////////////////////////////////////////////////////////////    

  if(stare == "New")///File->New
    {
      ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE_NEW));
    }
  if(stare == "<-Back")///iesire din submeniul File si revenire la meniul principal
    {
      ControlPanel::cPanel.pushEvent(Event(Event::EV_BACK_FILE));
    }

  ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW));
  
  return 0;
}
