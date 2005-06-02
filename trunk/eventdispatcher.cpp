#include <assert.h>
#include <curses.h>
#include <menu.h>

#include <algorithm>

using namespace std;

#include "control.h"
#include "event.h"
#include "eventdispatcher.h"
#include "controlpanel.h"
#include "menu.h"

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))


EventDispatcher::~EventDispatcher()
{
}


int EventDispatcher::processEvent(const Event & e)
{
  // TODO:

  //  Menu *menu_file;

  switch(e.getType())
    {
    case Event::EV_CHARACTER:
      switch(e.getValue())
        {
        case KEY_F(10):
          if(_currentControl == _tab)
            {
              _currentControl = _menu;
              refresh();
            }
          else
            {
              _currentControl = _tab;
              refresh();
            }
          break;

        default:
          if(_currentControl != NULL)
            {
              _currentControl->processEvent(e);
            }
          else
            {
              printw("Cannot!");
              refresh();
            }
          break;
        }
      break;
    case Event::EV_REDRAW:
      for(list<ControlObject *>::iterator it = objects.begin(); it != objects.end(); it++)
        (*it)->draw();

      doupdate();
      break;

    case Event::EV_QUIT:
      clog << "EV_QUIT" << endl;
      ControlPanel::cPanel.setState(ControlPanel::CP_DONE);
      break;
      
    case Event::EV_FILE:
      // menu_file = new Menu(this, qw123);    
      clog << "EV_FILE" << endl;
 
      doupdate();
      // addTarget(menu_file);
      break;
      
    case Event::EV_EDIT:
      clog << "EV_EDIT" << endl;
      break;
      
    case Event::EV_VIEW:
      clog << "EV_VIEW" << endl;
      break;  
      
       
      
    case Event::EV_FILE_NEW:
      clog << "EV_FILE_NEW" << endl;
      break;
    case Event::EV_FILE_OPEN:
      clog << "EV_FILE_OPEN" << endl;
      break;
    case Event::EV_FILE_SAVE:
      clog << "EV_FILE_SAVE" << endl;
      break;
      
    case Event::EV_FILE_BACK:
      clog << "EV_FILE_BACK" << endl;
//       removeTarget(menu_file);
//       addTarget(_menu);
      break;

    default:
      break;
    }

  return 0;
}


int EventDispatcher::addTarget(ControlObject * target)
{
  if(find(objects.begin(), objects.end(), target) == objects.end())
    {
      objects.push_back(target);
      setCurrentControl(target);
      return 0;
    }

  return 1;
}


int EventDispatcher::removeTarget(ControlObject * target)
{
  objects.remove(target);
  return 0;
}


void EventDispatcher::setCurrentControl(ControlObject * target)
{
  _currentControl = target;
}


void EventDispatcher::setMenu(ControlObject * menu)
{
  _menu = menu;
}


void EventDispatcher::setTab(ControlObject * tab)
{
  _tab = tab;
}
