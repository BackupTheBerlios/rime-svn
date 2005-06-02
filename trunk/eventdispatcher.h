#ifndef __EVENTDISPATCHER_H
#define __EVENTDISPATCHER_H

#include <list>

using namespace std;

#include "eventhandler.h"

class ControlObject;
class Menu;
class Tab;
class TabsLine;
class StatusLine;

class  EventDispatcher : public EventHandlerObject
{
 private:
  list<ControlObject *> objects;
  ControlObject * _currentControl;

  Menu * _menu;
  Tab * _tab;
  TabsLine * _tabsLine;
  StatusLine * _statusLine;

  ControlObject * currentMenu;

  void setCurrentControl(ControlObject *);

 public:
  virtual int processEvent(const Event &);
  virtual ~EventDispatcher();

  int addTarget(ControlObject *);
  int removeTarget(ControlObject *);

  void setMenu(ControlObject *);
  void setTab(ControlObject *);
  void setTabsLine(ControlObject *);
  void setStatusLine(ControlObject *);
};

#endif // __EVENTDISPATCHER_H
