#ifndef __CONTROLPANEL_H
#define __CONTROLPANEL_H

#include "eventdispatcher.h"
#include "eventmanager.h"

class ControlPanel
{
 private:
  EventDispatcher * pEd;
  list<ControlObject *> controls;
  list<EventManager *> events;

 public:
  ControlPanel();
  ~ControlPanel();

  void start();
};

#endif // __CONTROLPANEL_H
