#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <fstream>

using namespace std;

struct POINT
{
  unsigned int x, y;
};

struct RECT
{
  unsigned int x1, y1;

  unsigned int x2, y2;
};

#define MAKEINT(x, y) ((((y) & 0xFFFF) << 16) + ((x) & 0xFFFF))
#define HIWORD(x) (((x) >> 16) & 0xFFFF)
#define LOWORD(x) ((x) & 0xFFFF)

#endif // __GLOBALS_H
