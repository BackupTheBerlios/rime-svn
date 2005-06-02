#ifndef __CONTROLPANEL_H
#define __CONTROLPANEL_H

#include "eventdispatcher.h"
#include "eventmanager.h"
#include "eventhandler.h"

class ControlPanel : public EventManager
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
  int getState();

  void addControl(ControlObject *);
  void addEvent(Event &);
  void addEventManager(EventManager *);
  int processEvent(Event &) { return 0; }
  int pushEvent(const Event & ev) { events.push(ev); return 0; }

  static ControlPanel cPanel;
};

#endif // __CONTROLPANEL_H
