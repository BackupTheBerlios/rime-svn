#ifndef __EVENT_H
#define __EVENT_H

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
};

#endif
