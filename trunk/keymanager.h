#ifndef __KEYMANAGER_H
#define __KEYMANAGER_H

#include "eventmanager.h"

class KeyManager 
{
 public:
 
   KeyManager(){}
  ~KeyManager(){}

  static void start();
  
  static void*  start_FORKED(void *);  
  
  static queue<Event> events;
};

#endif // __KEYMANAGER_H
