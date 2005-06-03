#include <ncurses.h>
#include <menu.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "menu.h"
#include "control.h"
#include "controlpanel.h"
#include "buffer.h"

Menu::Menu(EventDispatcher * pEd, vector<string> choices) : ControlObject(pEd)
{
  //stare = "begin";
  pEd->setMenu(this);
 
  win = newwin(0, COLS, 0, 0);
  keypad(win,TRUE);

  buildMenu(choices);

  draw();
}

Menu::~Menu()
{
  destroyMenu();

  refresh();
}


void Menu::draw()
{
  clog << "Menu::draw()" << endl;
  wrefresh(win);
}


int Menu::processEvent(const Event &ev)
{
  int x;
  
  clog << "Got an event" << endl;
  
  switch(ev.getType())
    {
    case Event::EV_CHARACTER:
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
              vector<string> choices;
              choices.clear();
              choices.push_back("New ");								
              choices.push_back("Open");
              choices.push_back("Save");
              choices.push_back("Back");
								
              destroyMenu();

              buildMenu(choices);
              
              wrefresh(win);

              return 0;
            }
        
          if( (stare == "Edit")/* || (item_index(current_item(pMyMenu))==1)*/ )
            {
              //ControlPanel::cPanel.pushEvent(Event(Event::EV_EDIT));
              Buffer *buf = new Buffer();
              buf->add(27);///intrat in modul comanda din clasa Buffer
              vector<string> choices;

              choices.clear();
				
              choices.push_back("Mark");								
              choices.push_back("Copy");
              choices.push_back("Past");
              choices.push_back("<---");
								
              destroyMenu();

              buildMenu(choices);
              
              wrefresh(win);
              refresh();

              return 0;
              // return 0;
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
            }
          else if(stare == "Open")///File->Open
            {
              ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE_OPEN));
            }
          else if(stare == "Save")///File->Save
            {
              ControlPanel::cPanel.pushEvent(Event(Event::EV_FILE_SAVE));
            }
          else if(stare == "Mark")
            {
              Buffer *buf = new Buffer();
              buf->add('m');///trimit caracterul 'm' la buffer in modul comanda --> Mark
            }
          else if(stare == "Copy")
            {
              Buffer *buf = new Buffer();
              buf->add(99);///trimit caracterul 'c' la buffer in modul comanda --> Copy
            } 
          else if(stare == "Past")
            {
            }

          vector<string> choices;

          choices.push_back("File");
          choices.push_back("Edit");		
          choices.push_back("Help");
          choices.push_back("Quit");
	      
          destroyMenu();
          
          buildMenu(choices);

          stare = "File";

          break;
        }
      break;
    case  Event::EV_CLICK:
      x = LOWORD(ev.getValue());
      clog << "X = " << x << endl;
      x = x / 6;
      if ( x > 4) 
        x = 1;
      menu_driver(pMyMenu , REQ_FIRST_ITEM);
	
      for ( int k = 0 ; k < x; k++)
	    menu_driver(pMyMenu , REQ_RIGHT_ITEM);

      ControlPanel::cPanel.pushEvent(Event(Event::EV_CHARACTER, 13));
      break;
    default:
      break;
    }

  ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW));

  return 0;
}


void Menu::buildMenu(const vector<string> & choices)
{
  numItems = choices.size();

  pMyItems = new ITEM*[numItems + 1];
    
  for(unsigned int i = 0; i < numItems; i++)
	pMyItems[i] = new_item(choices[i].c_str(), "");
  
  pMyItems[numItems] = NULL;

  pMyMenu = new_menu((ITEM**)pMyItems);

  set_menu_format(pMyMenu,1,7);
  set_menu_win(pMyMenu,win);
  set_menu_mark(pMyMenu,"*");
    
  post_menu(pMyMenu);

  refresh();
}


void Menu::destroyMenu()
{
  unpost_menu(pMyMenu);

  for(unsigned int i = 0; i < numItems; i++)    
  	free_item(pMyItems[i]);

  delete[] pMyItems;

  free_menu(pMyMenu);
}
