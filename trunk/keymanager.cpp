#include "keymanager.h"
#include "event.h"
#include "globals.h"

#include <pthread.h>
#include <curses.h>

#include <iostream>
using namespace std;

KeyManager::KeyManager()
{
  // TODO:

#ifdef DEBUG
  clog << "KeyManager::KeyManager()" << endl;
#endif
  start_FORK();
}

KeyManager::~KeyManager()
{
}

void KeyManager::start_FORK()
{
  pthread_t thread;

#ifdef DEBUG
  clog << "KeyManager::start_FORK()" << endl;
#endif
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
#ifdef DEBUG
  clog << "KeyManager::start()!" << endl;
#endif

  while(true)
    {
      int ch = getch();

      Event ev(Event::EV_CHARACTER, ch);
      events.push(ev);

#ifdef DEBUG      
      clog << "Pushed event : " << ev << endl;
#endif
    }
}
