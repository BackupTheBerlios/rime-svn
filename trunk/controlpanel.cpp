#include "controlpanel.h"
#include "tab.h"
#include "keymanager.h"
#include "event.h"
#include "menu.h"

#include <curses.h>
#include <menu.h>
#include <string.h>

#include <iostream>
using namespace std;

#define DEBUG

//KeyManager *pManager = new KeyManager();

ControlPanel ControlPanel::cPanel;

ControlPanel::ControlPanel()
{
#ifdef DEBUG
  clog << "ControlPanel::ControlPanel()" << endl;
#endif

  initscr();
  keypad(stdscr, TRUE);
  nonl();
  noecho();
  cbreak();
  
  pEd = new EventDispatcher();

  // TODO: read layout from a file

  // TODO: initialize controls

  addControl(new Tab(pEd));

  // TODO: initialize event managers

  KeyManager * pKeyMgr = new KeyManager();
  addEventManager(pKeyMgr);
}

ControlPanel::~ControlPanel()
{
  for(list<EventManager *>::iterator it = eventMgrs.begin(); it != eventMgrs.end(); it++)
    {
      delete *it;
    }

  for(list<ControlObject *>::iterator it = controls.begin(); it != controls.end(); it++)
    {
      delete *it;
    }

  delete pEd;

  // CURSES cleanup

  //  endwin();
}

void ControlPanel::start()
{
  Event ev;
  Menu *pMenu;
  
  
  
  WINDOW *pMyMenuWin;
  pMyMenuWin = newwin(0,COLS-1,LINES-1,0);
  refresh();
  keypad(pMyMenuWin, TRUE);
  wmove(pMyMenuWin,0,0);
  wrefresh(pMyMenuWin);
  mvwprintw(pMyMenuWin,0,0,"F2-Menu");
  wrefresh(pMyMenuWin);
  wmove(stdscr,1,0);
  refresh();

  while(state != CP_DONE)
    {
      for(list<EventManager *>::iterator it = eventMgrs.begin(); it != eventMgrs.end(); it++)
        {
          if((*it)->peekEvent(ev, PE_REMOVE))
            {
//#ifdef DEBUG
/*

                clog << (char)ev.getValue();
//		wrefresh(pMyMenuWin);
		refresh()
*/
//#endif			     
              pEd->processEvent(ev);
            }    
        }
    }
}

void ControlPanel::addControl(ControlObject * pCtrl)
{
  controls.push_back(pCtrl);
}

void ControlPanel::addEventManager(EventManager * pEvMgr)
{
  eventMgrs.push_back(pEvMgr);
}

void ControlPanel::setState(states state)
{
  this->state = state;
}
