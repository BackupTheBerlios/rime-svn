#include "eventmanager.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
}

bool EventManager::peekEvent(Event & ev, PEAction pa)
{
  if(events.empty())
    return false;

  ev = events.front();

  if(pa == PE_REMOVE)
    events.pop();

  return true;
}

