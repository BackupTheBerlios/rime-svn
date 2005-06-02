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
  //stare = "begin";
  pEd->setMenu(this);
 
  pMyItems = new ITEM*[choices.size() + 1];
    
  for(unsigned int i = 0; i < choices.size(); i++)
	pMyItems[i] = new_item(choices[i].c_str(), "");
	
  pMyItems[choices.size()] = NULL;

  pMyMenu = new_menu((ITEM**)pMyItems);

  refresh();
  set_menu_format(pMyMenu,1,7);
  win = newwin(0, COLS, 0, 0);
  keypad(win,TRUE);
  set_menu_win(pMyMenu,win);
  set_menu_mark(pMyMenu,"*");
    
  post_menu(pMyMenu);
  
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
  
  Menu *menu_file;
//  EventDispatcher *pEd;

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
          clog << "stare:"<<stare << endl;

          if( (stare == "Quit")/* || (item_index(current_item(pMyMenu))==3)*/ )
            {///bug la Quit...uneori item-ul se transforma intr-un string ciudat
              ControlPanel::cPanel.pushEvent(Event(Event::EV_QUIT));
              return 0;
            }
          if( (stare == "File")/* || (item_index(current_item(pMyMenu))==0)*/ )///accesare File din meniul principal
            {
//              ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE));
		
		
		EventDispatcher *pEd = new EventDispatcher();
		vector<string> choices_file;

		
		
		
		choices_file.push_back("Back");
		choices_file.push_back("Save");
		choices_file.push_back("Open");
		choices_file.push_back("New ");								
								
		
		unpost_menu(pMyMenu);
		menu_file = new Menu(pEd,choices_file);
		post_menu(pMyMenu);
		wrefresh(win);

		ControlPanel::cPanel.addControl(menu_file);
                return 0;
            }
          if( (stare == "Edit")/* || (item_index(current_item(pMyMenu))==1)*/ )
            {
              ControlPanel::cPanel.pushEvent(Event(Event::EV_EDIT));
              return 0;
            }    
          if( (stare == "Help")/* || (item_index(current_item(pMyMenu))==2)*/ )
            {
              ControlPanel::cPanel.pushEvent(Event(Event::EV_HELP));
              return 0;
            }
    
          ///////////////////////////////////////////////////////////////////////////////////////    

          if(stare == "New ")///File->New
            {
              ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE_NEW));
              return 0;	      
            }

          if(stare == "Open")///File->Open
            {
              ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE_OPEN));
              return 0;	      
            }

          if(stare == "Save")///File->Save
            {
              ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE_SAVE));
              return 0;	      
            }

          if(stare == "Back")///iesire din submeniul File si revenire la meniul principal
            {
              //ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE_BACK));
	      EventDispatcher *pEd = new EventDispatcher();
	      vector<string> choices;



	      choices.push_back("File");
	      choices.push_back("Edit");		
	      choices.push_back("Help");
	      choices.push_back("Quit");
	      
	      unpost_menu(pMyMenu);
	      
	      Menu *menu = new Menu(pEd,choices);
	      post_menu(pMyMenu);

	      wrefresh(win);
	      ControlPanel::cPanel.addControl(menu);
	      pEd->removeTarget(menu_file);
	      pEd->addTarget(menu);
              //return 0;	      
            }
          break;
        }
    }

  ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW));
  
  return 0;
}
