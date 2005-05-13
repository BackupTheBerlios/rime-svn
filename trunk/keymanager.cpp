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
  clog << "Creating thread..." << endl;
  pthread_create(&thread, NULL, start_FORKED, (void *) this);
  clog << "Thread created." << endl;
}

void * KeyManager::start_FORKED(void * pvKeyManager)
{ 
  KeyManager * pKeyManager = (KeyManager *) pvKeyManager;
  
  clog << "Thread started." << endl;
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

