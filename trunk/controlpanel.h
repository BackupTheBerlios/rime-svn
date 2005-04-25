#ifndef __CONTROLPANEL_H
#define __CONTROLPANEL_H

#include "eventdispatcher.h"
#include "eventmanager.h"

class ControlPanel
{
 public:
  enum states {CP_WORKING, CP_DONE};
 private:
  EventDispatcher * pEd;
  list<ControlObject *> controls;
  list<EventManager *> eventMgrs;
  states state;

 public:
  ControlPanel();
  ~ControlPanel();

  void start();
  void setState(states);

  void addControl(ControlObject *);
  void addEventManager(EventManager *);

  static ControlPanel cPanel;
};

#endif // __CONTROLPANEL_H
