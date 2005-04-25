#include "controlpanel.h"
#include "tab.h"
#include "keymanager.h"
#include "event.h"

#include <curses.h>

#include <iostream>
using namespace std;

#define DEBUG

ControlPanel ControlPanel::cPanel;

ControlPanel::ControlPanel()
{
#ifdef DEBUG
  clog << "ControlPanel::ControlPanel()" << endl;
#endif

  pEd = new EventDispatcher();

  // TODO: read layout from a file

  // TODO: initialize controls

  addControl(new Tab(pEd));

  // TODO: initialize event managers

  addEventManager(new KeyManager());

  // TODO: initialise CURSES

  initscr();
  keypad(stdscr, TRUE);
  nonl();
  cbreak();
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

  endwin();
}

void ControlPanel::start()
{
  Event ev;

  while(state != CP_DONE)
    {
      for(list<EventManager *>::iterator it = eventMgrs.begin(); it != eventMgrs.end(); it++)
        {
          if((*it)->peekEvent(ev, PE_REMOVE))
            {
#ifdef DEBUG
              clog << "Event found!" << endl;
#endif
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
