#ifndef __CONTROLPANEL_H
#define __CONTROLPANEL_H

#include "eventdispatcher.h"
#include "eventmanager.h"
#include "eventhandler.h"

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

  /// The constructor
  ControlPanel();
  ~ControlPanel();

  void start();
  void setState(states);

  void addControl(ControlObject *);
  void addEvent(Event &);
  void addEventManager(EventManager *);
  int processEvent(Event &) {}

  static ControlPanel cPanel;
};

#endif // __CONTROLPANEL_H
