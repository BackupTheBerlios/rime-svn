#include "control.h"

ControlObject::ControlObject(EventDispatcher * e)
{
  pDisp = e;

  pDisp->addTarget(this);
}

ControlObject::~ControlObject()
{
  pDisp->removeTarget(this);
}
