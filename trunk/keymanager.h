#ifndef __KEYMANAGER_H
#define __KEYMANAGER_H

#include "eventmanager.h"

class KeyManager : public EventManager
{
 public:
  KeyManager();
  ~KeyManager();

  virtual bool peekEvent(Event *&, PEAction );

  virtual void start(void *);

  virtual void start_FORK();
  static void * start_FORKED(void *);
};

#endif // __KEYMANAGER_H
