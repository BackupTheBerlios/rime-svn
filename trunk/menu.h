#ifndef __MENU_H
#define __MENU_H

#include <curses.h>
#include <menu.h>

#include "control.h"


class Menu: public ControlObject
{
 public: 
  Menu(EventDispatcher* );
  
  virtual void draw();
  virtual int processEvent(Event &);
};

#endif // _MENU_H
