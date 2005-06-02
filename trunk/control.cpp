#include "control.h"

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
