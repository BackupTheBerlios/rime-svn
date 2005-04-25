#include "tab.h"
#include "event.h"

#include <iostream>
using namespace std;

Tab::Tab(EventDispatcher * ed) : ControlObject(ed)
{
}

void Tab::draw()
{
#ifdef DEBUG
  clog << "Tab::Draw()" << endl;
#endif
}

int Tab::processEvent(Event & ev)
{
#ifdef DEBUG
  clog << "Event::type = " << ev.getType() << "; Event::value = " << ev.getValue() << endl;
#endif
  return 0;
}
