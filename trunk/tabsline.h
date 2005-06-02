#ifndef __TABSLINE_H
#define __TABSLINE_H

#include "control.h"
#include "tab.h"

#include <list>
using namespace std;

class TabsLine : public ControlObject
{
 private:
  list<Tab *> tabs;
 public:
  TabsLine(EventDispatcher *);
  ~TabsLine();

  virtual int processEvent(const Event &);
  virtual void draw();
};

#endif // _TABSLINE_H
