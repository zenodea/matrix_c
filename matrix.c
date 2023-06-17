#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>

struct lineInst
             {
  int posx,curry,inity;
  int len;
  bool finished;
  int totlen;
};

// Struct representing one instance of line of code
int main()
{

  int random, count, row, col;
  int y ;
  int x ;

  // Seed random number generator
  srand(time(NULL));

  initscr();
  curs_set(0);

  // SIZE SETTINGS
  getmaxyx(stdscr, y,x);
  bool activeline [x];
  int size = x;
  struct lineInst lines[size];    


  // COLOR SETTINGS
  start_color();
// Enable transparency
  assume_default_colors(-1, -1);
  // Green Color for text
  init_pair(1, COLOR_GREEN, -1);
  // White text for front of the line of chars
  init_pair(2, COLOR_WHITE, -1);

  // get max values

  for (int i = 0; i < x; i++)
  {
    activeline[i] = false;
  }

  for (int i = 0; i < size; i++)
  {
    do
    {
      lines[i].posx = i; 
    }
    while(activeline[lines[i].posx] == true);
    activeline[lines[i].posx] = true;

    int starty;
    starty = rand() % (y-10) + 0;
    lines[i].len = rand() % (starty/30) + 5;
    lines[i].inity = starty ; 
    lines[i].curry = starty ; 
    lines[i].len = rand() % 10 + 5;
    lines[i].totlen = 0; 
    lines[i].finished = false;
  }

  char c;

  while(1)
  {
    usleep(30000);
    for (int i = 0; i < size; i++ )
      {

      // If line reaches maxY
      if (lines[i].curry == y)
      {
        lines[i].finished = true;
        attron(COLOR_PAIR(1));
        int ch = mvinch(lines[i].curry-1, lines[i].posx) & A_CHARTEXT;
        mvaddch(lines[i].curry-1, lines[i].posx, ch);
        attroff(COLOR_PAIR(1));
      }

      // if line has reached its designated length
      if (lines[i].totlen >= lines[i].len)
      {
        activeline[lines[i].posx] = false;
        mvaddch(lines[i].inity, lines[i].posx,' ');
        lines[i].inity++;
      }

      // if end of line reaches maxY
      if (lines[i].inity == y)
      {
        do
          {
            lines[i].posx = i; 
          }
        while(activeline[lines[i].posx] == true);
        activeline[lines[i].posx] = true;
        lines[i].inity = 0; 
        lines[i].curry = 0; 
        lines[i].len = rand() % 25 + 5;
        lines[i].totlen = 0; 
        lines[i].finished = false;
      }

      // if line has not yet reached maxY
      if (lines[i].finished != true)
      {
        // Select random character from UNICODE 33 to 58
        random= rand() % 58 + 33;
        c = random;

        // Set color of first character to WHITE
        attron(COLOR_PAIR(2));
        mvaddch(lines[i].curry, lines[i].posx, c);
        attroff(COLOR_PAIR(2));

        // Update color of previous character
        attron(COLOR_PAIR(1));
        int ch = mvinch(lines[i].curry-1, lines[i].posx) & A_CHARTEXT;
        mvaddch(lines[i].curry-1, lines[i].posx, ch);
        attroff(COLOR_PAIR(1));
        lines[i].curry++;
        lines[i].totlen++;
      }
      }
      refresh();
  }
  return 1;
}
