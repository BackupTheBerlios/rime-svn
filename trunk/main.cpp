#include "controlpanel.h"

#include <curses.h>
#include <signal.h>

#include <iostream>
#include <fstream>

using namespace std ;

void sigwinch_handler(int )
{
  endwin();
  initscr();

  ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW));
}

int main(int  argc , char** argv )
{
  ofstream slog("rime.log");
  if(slog.is_open())
    clog.rdbuf(slog.rdbuf());

  signal(SIGWINCH, sigwinch_handler);

  ControlPanel::cPanel.pushEvent(Event(Event::EV_REDRAW));

  ControlPanel::cPanel.start();

  clog << "Main is done!" << endl;
  return 0;
}
