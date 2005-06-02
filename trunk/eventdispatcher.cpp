#include <assert.h>
#include <curses.h>
#include <menu.h>

#include <algorithm>

using namespace std;

#include "control.h"
#include "event.h"
#include "eventdispatcher.h"
#include "controlpanel.h"
#include "menu.h"
#include "tab.h"
#include "statusline.h"
#include "tabsline.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


EventDispatcher::~EventDispatcher()
{
}


int EventDispatcher::processEvent(const Event & e)
{
  // TODO:

  //Menu *menu_file;

  switch(e.getType())
    {
    case Event::EV_CHARACTER:
      switch(e.getValue())
        {
        case KEY_F(10):
          if(_currentControl == (ControlObject *) _tab)
            {
              _currentControl = (ControlObject *) _menu;
              refresh();
            }
          else
            {
              _currentControl = (ControlObject *) _tab;
              refresh();
            }
          break;

        default:
          if(_currentControl != NULL)
            {
              _currentControl->processEvent(e);
            }
          else
            {
              printw("Cannot!");
              refresh();
            }
          break;
        }
      break;
    case Event::EV_CLICK:
      clog << "Click detected!" << endl;
      switch(LOWORD(e.getValue())) // y
        {
        case 0:
	  _currentControl = _menu;
          _menu->processEvent(e);
          break;
        case 1:
          break;
        default:
	  _currentControl = _tab;
          _tab->processEvent(e);
          break;
        }
      break;
    case Event::EV_REDRAW:
      for(list<ControlObject *>::iterator it = objects.begin(); it != objects.end(); it++)
        (*it)->draw();

      doupdate();
      break;

    case Event::EV_QUIT:
      clog << "EV_QUIT" << endl;
      ControlPanel::cPanel.setState(ControlPanel::CP_DONE);
      break;
      
      
    case Event::EV_EDIT:
      clog << "EV_EDIT" << endl;
      break;
      
    case Event::EV_HELP:
      clog << "EV_HELP" << endl;
      int x,y;
      WINDOW *help_win;
      char text1[300], text2[300], authors1[200], authors2[200];
      strcpy(text1,"RimE text editor");
      strcpy(text2,"Version 1.0");
      strcpy(authors1,"Ciumeica Mihai, Ciur Eugen");
      strcpy(authors2,"Corlateanu Radu, Radu Ionut");
      help_win = newwin(LINES/2,COLS/2,LINES/4,COLS/4);
      getyx(help_win,y,x);
      box(help_win,0,0);
      mvwprintw(help_win, y + 1, (x+COLS/2)/2 - strlen("About:")/2,"About:");
      mvwprintw(help_win,(y+LINES/2)/2-2,(x+COLS/2)/2-(strlen(text1)/2),"%s",text1);
      mvwprintw(help_win,(y+LINES/2)/2,(x+COLS/2)/2-(strlen(text2)/2),"%s",text2);
      mvwprintw(help_win,y+LINES/2-5,(x+COLS/2)/2 - (strlen("Authors:")/2), "Authors:");
      mvwprintw(help_win,y+LINES/2-4,(x+COLS/2)/2 - (strlen(authors1)/2), "%s",authors1);
      mvwprintw(help_win,y+LINES/2-3,(x+COLS/2)/2 - (strlen(authors2)/2), "%s",authors2);
      mvwprintw(help_win,y+LINES/2-2,(x+COLS/2)/2 - (strlen("Press SPACEBAR to continue")/2), "Press SPACEBAR to continue");	
      keypad(help_win,TRUE);
      wrefresh(help_win); 
      break;  
      
       
      
    case Event::EV_FILE_NEW:
      clog << "EV_FILE_NEW" << endl;
      break;
    case Event::EV_FILE_OPEN:
      clog << "EV_FILE_OPEN" << endl;
      break;
    case Event::EV_FILE_SAVE:
      clog << "EV_FILE_SAVE" << endl;
      break;
      

    default:
      break;
    }

  return 0;
}


int EventDispatcher::addTarget(ControlObject * target)
{
  if(find(objects.begin(), objects.end(), target) == objects.end())
    {
      objects.push_back(target);
      setCurrentControl(target);

      return 0;
    }

  return 1;
}


int EventDispatcher::removeTarget(ControlObject * target)
{
  objects.remove(target);
  return 0;
}


void EventDispatcher::setCurrentControl(ControlObject * target)
{
  _currentControl = target;
}


void EventDispatcher::setMenu(ControlObject * menu)
{
  _menu = (Menu *) menu;
}


void EventDispatcher::setTab(ControlObject * tab)
{
  _tab = (Tab *) tab;
  _tabsLine->addTab(_tab);
}


void EventDispatcher::setTabsLine(ControlObject * tabsline)
{
  _tabsLine = (TabsLine *) tabsline;
}


void EventDispatcher::setStatusLine(ControlObject * statusline)
{
  _statusLine = (StatusLine *) statusline;
}
