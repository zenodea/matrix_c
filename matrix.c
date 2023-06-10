#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#define COLOR_NEON_GREEN 10
#define MAXY 45
#define MAXX 200

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

  struct timeval set, new, result;

  int size;

  size = 150;

  struct lineInst lines[size];    


  int random, count, row, col;
  int y = MAXY;
  int x = MAXX;

  bool activeline [MAXX];

  WINDOW *win;


  // Seed random number generator
  srand(time(NULL));

  initscr();
  wresize(win,y,x);
  curs_set(0);
  start_color();

  init_color(COLOR_NEON_GREEN, 57, 255, 20);

  // Green Color for text
  init_pair(1, COLOR_NEON_GREEN, COLOR_BLACK);

  // White text for front of the line of chars
  init_pair(2, COLOR_WHITE, COLOR_BLACK);

  // get max values

  for (int i = 0; i < 200; i++)
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
    if (i % 2 == 0)
    {
        starty = rand() % 20 + 10;
        lines[i].len = rand() % 10 + 5;
    }
    else {
        starty = rand() % 10 + 0;
        lines[i].len = rand() % 20 + 10;
    }
    lines[i].inity = starty ; 
    lines[i].curry = starty ; 
    lines[i].len = rand() % 10 + 5;
    lines[i].totlen = 0; 
    lines[i].finished = false;
  }

  char c;

  while(1)
  {
    usleep(50000);
    for (int i = 0; i < size; i++ )
      {

      // If line reaches maxY
      if (lines[i].curry == y)
      {
        lines[i].finished = true;
      }

      // if line has reached its designated length
      if (lines[i].totlen >= lines[i].len)
      {
        activeline[lines[i].posx] = false;
        move(lines[i].inity, lines[i].posx);
        printw(" ");
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
        lines[i].len = rand() % 20 + 5;
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
        move(lines[i].curry, lines[i].posx);
        printw("%c", c);
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
