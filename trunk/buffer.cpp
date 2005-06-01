#include <curses.h>
#include <iostream>
#include <iterator>

using namespace std;

#include "buffer.h"

Buffer::Buffer() : lines(1)
{
  cursor.x = 0;
  cursor.y = 0;
  lines[0] = vector<char> (0);
}

int Buffer::add(int ch)
{
  vector<vector<char> >::iterator it, it1;
  vector<char>::iterator itt;  
  
  switch(ch)
    {
    case KEY_UP:
      if(cursor.y > 0)
        cursor.y--;

      if(cursor.x > lines[cursor.y].size() - 1)
        cursor.x = lines[cursor.y].size() - 1;
      break;
    case KEY_DOWN:
      if(cursor.y + 1 < lines.size())
        cursor.y++;
      if(cursor.x > lines[cursor.y].size())
        cursor.x = lines[cursor.y].size();
      break;
    case KEY_LEFT:
      if(cursor.x > 0)
        cursor.x--;
      break;
    case KEY_RIGHT:
      if(cursor.x + 1 < lines[cursor.y].size())
        cursor.x++;
      break;
    case KEY_HOME:
      cursor.x = 0;
      break;
    case KEY_END:
      cursor.x = lines[cursor.y].size();
      break;
    case KEY_BACKSPACE:
      if(cursor.x > 0)
        {
          itt = lines[cursor.y].begin();
          advance(itt, cursor.x - 1);
          lines[cursor.y].erase(itt);
          cursor.x--;
        }
      break;
    case 13:
      it = lines.begin();
      advance(it, cursor.y);
      itt = it->begin();
      advance(itt, cursor.x);
      it1 = it;
      it1++;
      lines.insert(it1, vector<char>(0));
      copy(itt, it->end(), it1->end());
      it->erase(itt, it->end());
      cursor.y++;
      cursor.x = 0;
      break;

    default:
      if(isprint(ch))
        {
          if(lines[cursor.y].size() == lines[cursor.y].capacity())
            lines[cursor.y].reserve(lines[cursor.y].capacity() * 2 + 1);

          itt = lines[cursor.y].begin();
          advance(itt, cursor.x);
          lines[cursor.y].insert(itt, (char) ch);
          cursor.x++;
        }
      break;
    }
  return 0;
}
