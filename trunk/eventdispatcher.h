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

  void setCurrentControl(ControlObject *);

 public:
  virtual int processEvent(Event &);
  virtual ~EventDispatcher();

  int addTarget(ControlObject *);
  int removeTarget(ControlObject *);
};

#endif // __EVENTDISPATCHER_H
