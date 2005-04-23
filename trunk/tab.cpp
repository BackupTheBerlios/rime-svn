#include "tab.h"

#include <iostream>
using namespace std;

Tab::Tab(EventDispatcher * ed) : ControlObject(ed)
{
}

void Tab::draw()
{
  cout << "Tab::Draw()" << endl;
}

int Tab::processEvent(Event &)
{
  return 0;
}
