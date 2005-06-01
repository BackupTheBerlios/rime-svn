#ifndef __EVENTDISPATCHER_H
#define __EVENTDISPATCHER_H

#include <list>

using namespace std;

#include "eventhandler.h"


class ControlObject;

class  EventDispatcher : public EventHandlerObject
{
 private:
  list<ControlObject *> objects;
  ControlObject * currentControl;

  ControlObject * _menu;

  void setCurrentControl(ControlObject *);

 public:
  virtual int processEvent(const Event &);
  virtual ~EventDispatcher();

  int addTarget(ControlObject *);
  int removeTarget(ControlObject *);

  void setMenu(ControlObject *);
};

#endif // __EVENTDISPATCHER_H
