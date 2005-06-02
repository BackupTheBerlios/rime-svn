#include <ctype.h>
#include <curses.h>

#include <iostream>
#include <iterator>

using namespace std;

#include "buffer.h"

Buffer::mode Buffer::st = OVR	       ;
unsigned int Buffer::mark_set = OFF     ;
unsigned int Buffer::mark_start_x = 0   ;
unsigned int Buffer::mark_end_x = 0     ;
unsigned int Buffer::mark_start_y = 0   ;
unsigned int Buffer::mark_end_y = 0     ;
unsigned int Buffer::mark_ready = 0     ;
unsigned int Buffer::command_mode = OFF ;

Buffer::Buffer() : lines(1)
{
  cursor.x = 0;
  cursor.y = 0;
  lines[0] = vector<char> (0);
}


int Buffer::add(int ch)
{
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

    case KEY_DC:
	  key_del() ;
      break;

    case '\t':
	  key_tab() ;
      break;

    case 27:
      key_esc() ;
      break;

    case 'M':
    case 'm':
      key_m( ch ) ;
      break ;

    case 'D':
    case 'd':
      key_d( ch ) ;
      break;

    case 'C':
    case 'c':
      key_c( ch , OFF ) ; // del_mode == OFF
      break;

    case 'X': // inca neimplementat ( ! )
    case 'x':
      key_c( ch , ON ) ; // del_mode == ON ;
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
      key_13() ;
      break;

    case KEY_IC:
      key_ins() ;
      break;

    default:
      if(isprint(ch))
        {
          aux_add_ch( ch ) ;
        }
      break;
    }
  return 0;
}


void Buffer::key_del()
{
  vector<char>::iterator itt;

  itt = lines[cursor.y].begin();
  advance(itt, cursor.x);
  if(  itt < lines[cursor.y].end()  )
    lines[cursor.y].erase(itt,itt+1);
}


void Buffer::key_ins()
{
  if( st == OVR  )
    st = INS ;
  else
    st = OVR ;
}


void Buffer::key_13()
{
  vector<vector<char> >::iterator it, it1;
  vector<char>::iterator itt;

  it = lines.begin();
  advance(it, cursor.y);
  itt = it->begin();
  advance(itt, cursor.x);
  it1 = it;
  it1++;
  lines.insert(it+1 , vector<char>(0) );
  for( unsigned i = cursor.x , j =0  ; i < lines[ cursor.y  ].size() ; i++ , j++  )
    {
      lines[cursor.y+1].insert( lines[cursor.y+1].begin() + j , (char) lines[cursor.y][i] );
    }
  lines[ cursor.y  ].erase( lines[ cursor.y  ].begin() + cursor.x ,  lines[ cursor.y  ].end()   ) ;
  cursor.y++;
  cursor.x = 0;
}


void Buffer::key_tab()
{
  int i = 0 ;

  for( i =0  ; i < 8 ; i++  )
    {
      aux_add_ch( ' ' );
    }
}


void Buffer::key_c( char ch, int del_mode ) // del_mode in {ON , OFF}
{
  unsigned int i, j;

  if(command_mode == OFF)
    {
      if(isprint(ch))
        aux_add_ch(ch) ;
      return ;
    }

  ///////////////////// selecttie randuri diferite caz y1 < y2  /////////////////////
  if(mark_start_y < mark_end_y )
    {
      for( i = mark_start_x ; i < lines[mark_start_y].size()  ; i++  )
	    {
          aux_add_ch(  lines[mark_start_y][i]  );
	    }

      key_13() ;

      for(j = mark_start_y + 1; j < mark_end_y; j++)
	    {
          for( i = 0 ; i < lines[j].size() ; i++   )
    		{
              aux_add_ch(  lines[j][i]  );
            }
          key_13();
	    }


      for( i = 0 ; i < mark_end_x  ; i++  )
	    {
          aux_add_ch(  lines[mark_end_y][i]  );
	    }

    }
  ///////////////////// selecttie randuri diferite caz y1 < y2 stop /////////////////////


  ///////////////////// selecttie randuri diferite caz y1 > y2  /////////////////////
  if( mark_start_y > mark_end_y  )
    {

      for( i = mark_start_x ; i < lines[ mark_end_y  ].size()  ; i++  )
        {
          aux_add_ch(  lines[mark_end_y][i]  );
        }

	  key_13() ;

	  for( j = mark_end_y+1 ; j <  mark_start_y  ; j++  )
        {
          for( i = 0 ; i < lines[j].size() ; i++   )
            {
              aux_add_ch(  lines[j][i]  );
            }
          key_13();
        }


	  for( i = 0 ; i < mark_end_x  ; i++  )
        {
          aux_add_ch(  lines[mark_start_y][i]  );
        }
    }
  ///////////////////// selecttie randuri diferite caz y1 > y2  /////////////////////


  ////////////////////// selectie in aceeashi linie start//////////////////////////////////

  if( mark_start_y == mark_end_y  )
    {
      if( mark_start_x < mark_end_x   )
        {
	      for( i = 0 ; i < mark_end_x - mark_start_x   ; i++  )
            {
              aux_add_ch(  lines[mark_start_y][mark_start_x+i]  );
            }
	    }
      else
        {
          if( mark_start_x > mark_end_x  )
            {
              for( i = 0 ; i < mark_end_x - mark_start_x   ; i++  )
                {
                  aux_add_ch(  lines[mark_start_y][mark_end_x+i]  );
                }
            }
        }
    }

  ////////////////////// selectie in aceeashi linie stop //////////////////////////////////


}


void Buffer::key_x( char ch )
{

}


void Buffer::key_d( char ch )
{
  if( command_mode == ON  )
    {
      lines.erase( lines.begin()+ cursor.y  , lines.begin()+ cursor.y+1  );
    }
  else
    {
      if( isprint(ch) )
        aux_add_ch( ch ) ;
    }
}


void Buffer::key_esc()
{
  if( command_mode == OFF  )
    {
      command_mode  = ON ;
    }
  else
    {
      if( command_mode == ON  )
        {
          command_mode = OFF ;
        }
    }

}


void Buffer::key_m(char ch)
{

  if( command_mode == OFF    )
    {
      if( isprint(ch) )
        aux_add_ch( ch ) ;
	  return ;

    }

  if( mark_set == OFF )
    {
      mark_set = ON;
      mark_start_x = cursor.x ;
      mark_start_y = cursor.y ;

    }
  else
    {
      if( mark_set == ON  )
        {
          mark_set = OFF;
          mark_end_x = cursor.x ;
          mark_end_y = cursor.y ;
        }
    }
}



void Buffer::aux_add_ch(char ch)
{
  vector<char>::iterator itt;

  if(lines[cursor.y].size() == lines[cursor.y].capacity())
    lines[cursor.y].reserve(lines[cursor.y].capacity() * 2 + 1);

  itt = lines[cursor.y].begin();
  advance(itt, cursor.x);

  if( st == INS  )
    {
	  if( itt == lines[cursor.y].end()  )
        {
          lines[cursor.y].insert(itt, (char) ch);

        }
      else
        {
	      lines[cursor.y][cursor.x] = (char)ch;
        }
    }
  else
    {
      if( st == OVR  ) // asta mai mult ca st sa nu o ia razna  shi sa aiba alta valoare ;)
	    {
          lines[cursor.y].insert(itt, (char) ch);
	    }
    }

  cursor.x++;
}

// [eug] end
