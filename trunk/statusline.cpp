#include <curses.h>

#include "statusline.h"
#include "eventdispatcher.h"
#include "tab.h"

StatusLine::StatusLine(EventDispatcher * pEd) : ControlObject(pEd)
{
  pEd->setStatusLine(this);

  win = newwin(1, cols, lines - 1, 1);
}

StatusLine::~StatusLine()
{
  delwin(win);
}

void StatusLine::draw()
{
  werase(win);
  
  wprintw(win, "[%s]", pDisp->getTab()->getBuffer()->getFileName().c_str());
  wnoutrefresh(win);
}

int StatusLine::processEvent(const Event &)
{
  return 0;
}
