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

  cout << "KeyManager::KeyManager()" << endl;
  start_FORK();
}

KeyManager::~KeyManager()
{
}

void KeyManager::start_FORK()
{
  pthread_t thread;

  cout << "KeyManager::start_FORK()" << endl;
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
  cout << "KeyManager::start()!" << endl;

  while(true)
    {
      int ch = getch();

      Event ev(Event::EV_CHARACTER, ch);
      events.push(ev);
      
      clog << "Pushed event : " << ev << endl;
    }
}
