#include "controlpanel.h"

#include <iostream>
#include <fstream>

using namespace std ;

int main(int  argc , char** argv )
{
  /*  ofstream slog("rime.log");
  if(slog.is_open())
  clog.rdbuf(slog.rdbuf());*/

  ControlPanel::cPanel.start();

  return 0;
}



