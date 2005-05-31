#ifndef __TAB_H
#define __TAB_H

#include <curses.h>

#include "buffer.h"
#include "globals.h"
#include "event.h"
#include "control.h"

class Tab: public ControlObject
{
  Buffer * pBuffer;  
  POINT cursor;
  WINDOW * win;

 public:
  Tab(EventDispatcher *);
  ~Tab();

  virtual void draw();
  virtual int processEvent(const Event &);
};

#endif
