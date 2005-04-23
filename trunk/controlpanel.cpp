#include "controlpanel.h"
#include "tab.h"
#include "keymanager.h"

#include <curses.h>

#include <iostream>
using namespace std;

#define DEBUG

ControlPanel::ControlPanel()
{
#ifdef DEBUG
  cout << "ControlPanel::ControlPanel()" << endl;
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
  noecho();
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

  while(true)
    {
      for(list<EventManager *>::iterator it = eventMgrs.begin(); it != eventMgrs.end(); it++)
        {
          if((*it)->peekEvent(ev, PE_REMOVE))
            {
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
