#ifndef __BUFFER_H
#define __BUFFER_H

#include "globals.h"

#include <vector>
#include <list>

using namespace std;

class Buffer
{
 private:
  POINT cursor;

  vector<vector<char> > lines;
 public:
  Buffer();
  int add(int ch);

  friend class Tab;
};

#endif // __BUFFER_H
