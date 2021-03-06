#include "controlpanel.h"
#include "tab.h"
#include "keymanager.h"
#include "event.h"
#include "menu.h"
#include "statusline.h"
#include "tabsline.h"

#include <curses.h>
#include <menu.h>
#include <string.h>

#include <iostream>
#include <fstream>
using namespace std;

#define DEBUG

ControlPanel ControlPanel::cPanel;

ControlPanel::ControlPanel()
{
  initscr();
  keypad(stdscr, TRUE);
  nonl();
  noecho();
  cbreak();
  
  pEd = new EventDispatcher();
  
  // TODO: read layout from a file

  

  // TODO: initialize controls

  vector<string> choices;
  choices.push_back("File");
  choices.push_back("Edit");  
  choices.push_back("Help");
  choices.push_back("Quit");

  addControl(new StatusLine(pEd));
  addControl(new TabsLine(pEd));
  addControl(new Menu(pEd,choices));
  addControl(new Tab(pEd));
  addControl(new Tab(pEd));
 

  // TODO: initialize event managers

  pKeyMgr = new KeyManager();
  addEventManager(pKeyMgr);
  addEventManager(this);
  
  state = CP_WORKING;
}

ControlPanel::~ControlPanel()
{
  for(list<EventManager *>::iterator it = eventMgrs.begin(); it != eventMgrs.end(); it++)
    {
      if((*it) != (EventManager *) this)
        delete *it;
    }

  for(list<ControlObject *>::iterator it = controls.begin(); it != controls.end(); it++)
    {
      delete *it;
    }

 delete pEd;

  // CURSES cleanup

  endwin();
}

void ControlPanel::start()
{
  Event ev;

  pushEvent(Event(Event::EV_REDRAW));

  refresh();

  while(state != CP_DONE)
    {
      for(list<EventManager*>::iterator it = eventMgrs.begin(); it != eventMgrs.end(); it++)
        {
          while((*it)->peekEvent(ev, PE_REMOVE))
            {
              pEd->processEvent(ev);
            }    
        }
    }

#ifdef DEBUG
  clog << "ControlPanel is done!!" << endl;
#endif
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

int ControlPanel::getState()
{
  return state;
}
