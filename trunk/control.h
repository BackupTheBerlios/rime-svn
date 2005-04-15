#ifndef __CONTROL_H
#define __CONTROL_H

#include "drawable.h"
#include "eventhandler.h"
#include "globals.h"
#include "eventdispatcher.h"

class ControlObject : public DrawableObject, public EventHandlerObject
{
 private:
  EventDispatcher * pDisp;
  RECT bounds;
 public:

  virtual void draw();
  virtual int processEvent(Event &);

  ControlObject(EventDispatcher *);
  virtual ~ControlObject();
  
  RECT getBounds();
};

#endif // __CONTROL_H
