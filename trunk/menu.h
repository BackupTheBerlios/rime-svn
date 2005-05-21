#ifndef __MENU_H
#define __MENU_H

#include <menu.h>
#include <curses.h>

#include "control.h"

class Menu: public ControlObject
{

 public: 
  Menu();
  
   

 virtual void draw();
 virtual int processEvent(Event &);
 
 static Menu meniu;
};

#endif // _MENU_H
