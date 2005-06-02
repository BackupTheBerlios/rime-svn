#ifndef __EVENT_H
#define __EVENT_H

#include <iostream>

using namespace std;

class Event
{
 public:
  enum types {EV_UNKNOWN, EV_CHARACTER, EV_CLICK, EV_REDRAW, EV_FILE, EV_EDIT, EV_HELP ,EV_QUIT, EV_FILE_NEW, EV_BACK_FILE};

 private:
  types type;
  int value;

 public:
  Event();
  Event(types, int value = 0);

  types getType() const;
  int getValue() const;
};

ostream & operator << (ostream &, const Event &);

#endif
