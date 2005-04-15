#include "keymanager.h"

#include <pthread.h>

KeyManager::KeyManager()
{
  // TODO:

  start_FORK();
}

KeyManager::~KeyManager()
{
}

bool KeyManager::peekEvent(Event *& pEv, PEAction action)
{
  if(!events.empty())
    {
      pEv = events.front();

      if(action == PE_REMOVE)
        events.pop();

      return true;
    }

  return false;
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
