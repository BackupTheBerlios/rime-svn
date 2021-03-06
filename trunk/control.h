#ifndef __CONTROL_H
#define __CONTROL_H

#include <curses.h>

#include "drawable.h"
#include "eventhandler.h"
#include "globals.h"
#include "eventdispatcher.h"


class ControlObject : public DrawableObject, public EventHandlerObject
{
 protected:
  EventDispatcher * pDisp;
  RECT bounds;
  WINDOW * win;
  int lines, cols;
 
 public:

  ControlObject(EventDispatcher *);
  virtual ~ControlObject();
  virtual int processEvent(const Event &) = 0;
  virtual void draw() = 0;
  virtual void printout(string what);
  
  RECT getBounds();
  void setBounds(RECT );
};

#endif // __CONTROL_H
