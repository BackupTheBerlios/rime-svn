#include "keymanager.h"
#include "event.h"
#include "globals.h"

#include <pthread.h>
#include <curses.h>

#include <iostream>
using namespace std;

KeyManager::KeyManager()
{
  start_FORK();
}

void KeyManager::start_FORK()
{
  pthread_t thread;

  pthread_create(&thread, NULL, start_FORKED, (void *) this);
}

void * KeyManager::start_FORKED(void * pvKeyManager)
{ 
  KeyManager * pKeyManager = (KeyManager *) pvKeyManager;
  
  pKeyManager->start();
  return NULL;
}

void KeyManager::start()
{
  MEVENT mEvent;
  Event ev;

  mousemask(BUTTON1_CLICKED, NULL);

  while(true)
    {
      int ch  = getch() ;

      switch(ch)
        {
        case KEY_MOUSE:
          getmouse(&mEvent);
          ch = (mEvent.x & 0xFFFF) << 16 + mEvent.y & 0xFFFF;
          ev = Event(Event::EV_CLICK, ch);
          break;
        default:
          ev = Event(Event::EV_CHARACTER, ch);       
          break;
        }
      events.push(ev);        
    }
}

