#include "controlpanel.h"

ControlPanel::ControlPanel()
{
  pEd = new EventDispatcher();

  // TODO: read layout from a file

  // TODO: initialize controls

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

  while(true)
    {
      for(list<EventManager *>::iterator it = events.begin(); it != events.end(); it++)
        {
          if(it->PeekEvent(pEvent, PE_REMOVE))
            {
              pEd->processEvent(pEvent);
              delete pEvent;
            }
        }
    }
}
