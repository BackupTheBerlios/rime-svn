#include "tab.h"
#include "event.h"

#include <iostream>
using namespace std;

Tab::Tab(EventDispatcher * ed) : ControlObject(ed)
{
}

void Tab::draw()
{
  cout << "Tab::Draw()" << endl;
}

int Tab::processEvent(Event & ev)
{
  cout << "Event::type = " << ev.getType() << "; Event::value = " << ev.getValue() << endl;
  return 0;
}
