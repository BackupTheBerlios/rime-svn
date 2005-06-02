#ifndef __BUFFER_H
#define __BUFFER_H

#include "globals.h"

#include <vector>
#include <list>
#include <string>

using namespace std;

class Buffer
{
 public:
  //[eug begin]

  enum mode { INS = 0 , OVR =1 };  // INS == insert mode ,  OVR == overwrite mode
  enum { ON = 0 , OFF = 1 };
  
  //[eug end]  
  
 private:
  POINT cursor;
  string _fileName;
  
  vector<vector<char> > lines;

  mode st ; // st in  {  INS , OVR } 
  unsigned int mark_set , mark_ready, mark_start_x , mark_end_x,
    mark_start_y, mark_end_y, 
    command_mode;  // mark_set in { ON , OFF  }

 public:
  Buffer();
 
  int add(int ch);
  
  //[eug begin]  
  void key_del( ) ; 
  void key_ins( ) ;
  void key_13 ( )  ;
  void key_tab( ) ;
  void key_c( char ch, int del_mode ) ; // del_mode in { ON , OFF  }
  void key_m( char ch ) ;
  void key_d( char ch ) ;
  void key_esc() ;
  void key_x(  char ch  ) ;  
  
  void aux_add_ch( char ch  ) ; // asta tine cont de faptul ca  st poate fi sau OVR sau INS  
  //[eug end]  

  string getFileName() const { return _fileName; }

  friend class Tab;
};

#endif // __BUFFER_H
