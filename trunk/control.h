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

  ControlObject(EventDispatcher *);
  virtual ~ControlObject();
  virtual int processEvent(const Event &) = 0;
  
  RECT getBounds();
  void setBounds(RECT );
};

#endif // __CONTROL_H
