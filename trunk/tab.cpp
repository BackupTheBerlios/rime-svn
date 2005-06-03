#include "tab.h"
#include "event.h"
#include "controlpanel.h"

#include <curses.h>
#include <stdlib.h>

#include <iostream>
#include <iterator>
using namespace std;

#define DEBUG

Tab::Tab(EventDispatcher * pEd) : ControlObject(pEd)
{
  int win_height = lines - 3;
  int win_width = cols;

  win = newwin(win_height, win_width, 2, 0);

  pBuffer = new Buffer;

   if(win == NULL)
     {
#ifdef DEBUG
       clog << "Cannot create window.";
       endwin();
       exit(0);
#endif
     }

   pEd->setTab((ControlObject *) this);

   draw();
}

Tab::~Tab()
{
  delete pBuffer;
  delwin(win);
}

void Tab::draw()
{
  int new_lines, new_cols;
  getmaxyx(stdscr, new_lines, new_cols);
  if(new_lines != lines || new_cols != cols)
    {
      lines = new_lines;
      cols = new_cols;

      int win_height = lines - 3;
      int win_width = cols;
      
      wresize(win, win_height, win_width);
    } 

  werase(win);
  box(win, 0, 0);
  
  for(unsigned int i = 0; i < pBuffer->lines.size(); i++)
     {
       vector<char> & l = pBuffer->lines[i];
       for(unsigned int j = 0; j < l.size(); j++)
         {
           mvwaddch(win, i + 1, j + 1, l[j]);
         }
     }

  wmove(win, pBuffer->cursor.y + 1, pBuffer->cursor.x + 1);
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
          ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW));
          break;
        }
      break;
    default:
      break;
    }

  return 0;
}
