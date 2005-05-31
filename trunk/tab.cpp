#include "tab.h"
#include "event.h"
#include "controlpanel.h"

#include <curses.h>
#include <stdlib.h>

#include <iostream>
#include <iterator>
using namespace std;

#define DEBUG

Tab::Tab(EventDispatcher * ed) : ControlObject(ed)
{
  win = newwin(COLS, LINES-1, 0, 1);
  pBuffer = new Buffer;

   if(win == NULL)
     {
#ifdef DEBUG
       clog << "Cannot create window.";
       endwin();
       exit(0);
#endif
     }
}

Tab::~Tab()
{
  delete pBuffer;
  delwin(win);
}

void Tab::draw()
{
  for(unsigned int i = 0; i < pBuffer->lines.size(); i++)
     {
       vector<char> & l = pBuffer->lines[i];
       for(vector<char>::iterator it = l.begin(); it != l.end(); it++)
         {
           mvwaddch(win, i, distance<vector<char>::iterator>(l.begin(), it), *it);
         }
     }

  wnoutrefresh(win);
}

int Tab::processEvent(const Event & ev)
{
  switch(ev.getType())
    {
    case Event::EV_CHARACTER:
      switch(ev.getValue())
        {
        default:
          pBuffer->add(ev.getValue());
          ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW, 0));
          break;
        }
      break;
    default:
      break;
    }

  return 0;
}
