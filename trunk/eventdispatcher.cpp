#include <assert.h>
#include <curses.h>

#include <algorithm>

using namespace std;

#include "control.h"
#include "eventdispatcher.h"
#include "controlpanel.h"

EventDispatcher::~EventDispatcher()
{
}

int EventDispatcher::processEvent(Event & e)
{
  // TODO:
  switch(e.getType())
    {
    case Event::EV_CHARACTER:
      if(e.getValue() == 27)
        {
          ControlPanel::cPanel.setState(ControlPanel::CP_DONE);
        }

      if(currentControl != NULL)
        currentControl->processEvent(e);
      else
        {
          printw("Cannot!");
          refresh();
        }

      break;
    }

  return 0;
}

int EventDispatcher::addTarget(ControlObject * target)
{
  if(find(objects.begin(), objects.end(), target) == objects.end())
    {
      objects.push_back(target);
      setCurrentControl(target);
      return 0;
    }

  return 1;
}

int EventDispatcher::removeTarget(ControlObject * target)
{
  objects.remove(target);
  return 0;
}

void EventDispatcher::setCurrentControl(ControlObject * target)
{
  currentControl = target;
}
