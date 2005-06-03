#include <curses.h>

#include "statusline.h"
#include "eventdispatcher.h"
#include "tab.h"

#include <string>

using namespace std;

StatusLine::StatusLine(EventDispatcher * pEd) : ControlObject(pEd)
{
  pEd->setStatusLine(this);

  win = newwin(1, cols, lines - 1, 1);
}

StatusLine::~StatusLine()
{
  delwin(win);
}

void StatusLine::draw()
{
  Buffer * pBuffer = pDisp->getTab()->getBuffer();
  werase(win);
  
  wprintw(win, "%s[%s] %s %s", 
          pBuffer->getModified() ? "*" : "",
          pBuffer->getFileName().c_str(),
          (pBuffer->getInsMode() == Buffer::INS) ? "OVR" : "INS",
          (pBuffer->getCommandMode() == Buffer::ON) ? "command" : "text"
          );
  wnoutrefresh(win);
}

int StatusLine::processEvent(const Event &)
{
  return 0;
}

string StatusLine::prompt(EventManager * em)
{
  Event e;
  string a;

  while(true)
    {
      if(em->peekEvent(e, PE_REMOVE))
        {
          if(e.getType() == Event::EV_CHARACTER)
            {
              switch(e.getValue())
                {
                case '\n':
                case '\r':
                  a = answer;
                  answer = "";
                  return a;
                default:
                  if(isprint(e.getValue()))
                    {
                      answer += char(e.getValue());
                      waddch(win, e.getValue());
                      wrefresh(win);
                    }
                  break;
                }
            }
        }
    }
}
