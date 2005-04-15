#include "controlpanel.h"
#include "tab.h"

#include <iostream>
using namespace std;

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
}

ControlPanel::~ControlPanel()
{
  for(list<EventManager *>::iterator it = events.begin(); it != events.end(); it++)
    {
      delete *it;
    }

  for(list<ControlObject *>::iterator it = controls.begin(); it != controls.end(); it++)
    {
      delete *it;
    }

  delete pEd;
}

void ControlPanel::start()
{
  Event ev;

  while(true)
    {
      for(list<EventManager *>::iterator it = events.begin(); it != events.end(); it++)
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