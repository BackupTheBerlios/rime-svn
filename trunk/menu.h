#ifndef __MENU_H
#define __MENU_H

#include <curses.h>
#include <menu.h>

#include <vector>
#include <string>

using namespace std;

#include "control.h"


class Menu: public ControlObject
{
 private:
  MENU *pMyMenu;
  ITEM **pMyItems;

  string stare;

  unsigned int numItems;

 public: 
  Menu(EventDispatcher*, vector<string>);
  ~Menu();
  
  virtual void draw();
  virtual int processEvent(const Event &);

  void buildMenu(const vector<string> &);
  void destroyMenu();
};

#endif // _MENU_H
