#include "control.h"

#include <string>

using namespace std;

ControlObject::ControlObject(EventDispatcher * e)
{
  pDisp = e;

  pDisp->addTarget(this);

  getmaxyx(stdscr, lines, cols);
}

ControlObject::~ControlObject()
{
  pDisp->removeTarget(this);
}

RECT ControlObject::getBounds()
{
  return bounds;
}

void ControlObject::setBounds(RECT bounds)
{
  this->bounds = bounds;
}

void ControlObject::printout(string what)
{
  werase(win);
  wprintw(win, "%s", what.c_str());
  wrefresh(win);
}
