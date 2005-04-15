#ifndef __TAB_H
#define __TAB_H

#include "buffer.h"
#include "globals.h"
#include "event.h"
#include "control.h"

class Tab: public ControlObject
{
 public:
  Buffer * pBuffer;  
  RECT size;

  Tab(EventDispatcher *);

  virtual void draw();
  virtual int processEvent(Event &);
};

#endif
