#include "keymanager.h"
#include "event.h"
#include "globals.h"

#include <pthread.h>
#include <curses.h>

#include <iostream>
using namespace std;


queue<Event> KeyManager::events ;

void KeyManager::start()
{

  pthread_t thread;
  pthread_create( &thread, NULL, start_FORKED,  0);
  
}



void * KeyManager::start_FORKED(void * pvKeyManager)
{ 
  
  while(true)
    {
       int ch  = getch() ;       
       
       Event ev( Event::EV_CHARACTER, ch);       
       events.push(ev);        
       
       //sleep( 1 ) ;
    }
    
    
  return NULL;
}

