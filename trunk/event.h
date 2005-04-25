#ifndef __EVENT_H
#define __EVENT_H

#include <iostream>

using namespace std;

class Event
{
 public:
  enum types {EV_UNKNOWN, EV_CHARACTER, EV_CLICK};

 private:
  types type;
  int value;

 public:
  Event();
  Event(types, int);

  types getType() const;
  int getValue() const;
};

ostream & operator << (ostream &, const Event &);

#endif
