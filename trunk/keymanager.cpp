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
  while(true)
    {
      int ch  = getch() ;
      Event ev( Event::EV_CHARACTER, ch);       
      events.push(ev);        
    }
}

