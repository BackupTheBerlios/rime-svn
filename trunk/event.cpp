#include "event.h"

Event::Event()
{
  type = EV_UNKNOWN;
  value = 0;
}

Event::Event(Event::types type, int value)
{
  this->type = type;
  this->value = value;
}

Event::types Event::getType() const
{
  return type;
}

int Event::getValue() const
{
  return value;
}

ostream & operator << (ostream & c, const Event & e)
{
  c << "Event(" << e.getType() << ", " << e.getValue() << ")";
}
