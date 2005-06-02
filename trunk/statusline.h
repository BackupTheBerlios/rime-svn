#ifndef __STATUSLINE_H
#define __STATUSLINE_H

#include "control.h"

class StatusLine : public ControlObject
{
 private:

 public:
  StatusLine(EventDispatcher *);
  ~StatusLine();

  virtual void draw();
  virtual int processEvent(const Event &);
};

#endif // __STATUSLINE_H
