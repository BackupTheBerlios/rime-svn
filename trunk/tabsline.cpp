#include "tabsline.h"
#include "controlpanel.h"

TabsLine::TabsLine(EventDispatcher * pEd) : ControlObject(pEd)
{
  win = newwin(1, cols, 1, 0);

  pEd->setTabsLine((ControlObject *) this);
}

TabsLine::~TabsLine()
{
  delwin(win);
}

int TabsLine::processEvent(const Event & e)
{
  unsigned int x;
  unsigned int c = 1;

  switch(e.getType())
    {
    case  Event::EV_CLICK:
      x = LOWORD(e.getValue());
      clog << "X = " << x << endl;
       for(unsigned int s = 0; s < 2; s++)
         {
           c += 5 + _tabs[s]->getBuffer()->getFileName().length();
           clog << "C = " << c << "; ";
           if (x <= c)
             {
              pDisp->setTab(_tabs[s]);
              break;
            }
        }

      ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW));

      break;
    default:
      break;
    }
  return 0;
}

void TabsLine::draw()
{
  werase(win);
  
  wmove(win, 0, 1);

  waddch(win, '|');

  for(vector<Tab *>::iterator it = _tabs.begin(); it != _tabs.end(); it++)
    {
      wprintw(win, " #%s# |", (*it)->getBuffer()->getFileName().c_str());
    }

  wnoutrefresh(win);
}

void TabsLine::addTab(Tab * t)
{
  if(find(_tabs.begin(), _tabs.end(), t) == _tabs.end())
    _tabs.push_back(t);
}
