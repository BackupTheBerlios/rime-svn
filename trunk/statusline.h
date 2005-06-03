#ifndef __STATUSLINE_H
#define __STATUSLINE_H

#include "control.h"
#include "eventmanager.h"

#include <string>

using namespace std;

class StatusLine : public ControlObject
{
 private:
  string answer;
  bool ready;

 public:
  StatusLine(EventDispatcher *);
  ~StatusLine();

  virtual void draw();
  virtual int processEvent(const Event &);

  string prompt(EventManager *);
};

#endif // __STATUSLINE_H
