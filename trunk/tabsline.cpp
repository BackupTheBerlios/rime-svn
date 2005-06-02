#include "tabsline.h"

TabsLine::TabsLine(EventDispatcher * pEd) : ControlObject(pEd)
{
  win = newwin(1, cols, 1, 0);

  pEd->setTabsLine(this);
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
  /*  for(list<Tab *>::iterator it = tabs.begin(); it != tabs.end(); it++)
    {
      
    }*/

  werase(win);
  wprintw(win, "Hello world!");

  wnoutrefresh(win);
}
