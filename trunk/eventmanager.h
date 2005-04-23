#ifndef __EVENTMANAGER_H
#define __EVENTMANAGER_H

#include <queue>
using namespace std;

#include "event.h"

enum PEAction {PE_KEEP, PE_REMOVE};

class EventManager
{
 protected:
  queue<Event> events;
 public:
  EventManager();
  virtual ~EventManager();

  virtual bool peekEvent(Event &, PEAction);

  virtual void start() = 0;
};

#endif // __EVENTMANAGER_H
