#ifndef __EVENTHANDLER_H
#define __EVENTHANDLER_H

#include "event.h"

class EventHandlerObject
{
 public:
  virtual int processEvent( const Event & ) = 0;      
};

#endif // __EVENTHANDLER_H
