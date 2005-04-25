#ifndef __TAB_H
#define __TAB_H

#include "buffer.h"
#include "globals.h"
#include "event.h"
#include "control.h"

class Tab: public ControlObject
{
  Buffer * pBuffer;  
  int cursor;

 public:
  Tab(EventDispatcher *);

  virtual void draw();
  virtual int processEvent(Event &);
};

#endif
