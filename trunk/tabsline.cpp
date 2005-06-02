#include "tabsline.h"

TabsLine::TabsLine(EventDispatcher * pEd) : ControlObject(pEd)
{
  win = newwin(1, cols, 1, 0);

  pEd->setTabsLine((ControlObject *) this);
}

TabsLine::~TabsLine()
{
  delwin(win);
}

int TabsLine::processEvent(const Event &)
{
  win = newwin(1, cols, 1, 0);

  return 0;
}

void TabsLine::draw()
{
  int i = 0;
  werase(win);
  
  wmove(win, 0, 1);

  wvline(win, ACS_VLINE, 1);

  for(list<Tab *>::iterator it = _tabs.begin(); it != _tabs.end(); it++)
    {
      wprintw(win, " #%s# ", (*it)->getBuffer()->getFileName().c_str());
      wvline(win, ACS_VLINE, 1);
    }

  wnoutrefresh(win);
}

void TabsLine::addTab(Tab * t)
{
  _tabs.push_back(t);
}
