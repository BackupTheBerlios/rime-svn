#include "tab.h"

#include <iostream>
using namespace std;

void Tab::draw()
{
  cout << "Tab::Draw()" << endl;
}

int Tab::processEvent(Event &)
{
  return 0;
}
