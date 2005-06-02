#include <curses.h>

#include "statusline.h"
#include "eventdispatcher.h"

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
  wprintw(win, "Status!");
  wnoutrefresh(win);
}

int StatusLine::processEvent(const Event &)
{
  return 0;
}
