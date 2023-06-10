#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#define COLOR_NEON_GREEN 10

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
  int y = 45;
  int x = 200;

  bool activeline [200];

  WINDOW *win;


  // Seed random number generator
  // srand(time(NULL));

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
    lines[i].inity = 0; 
    lines[i].curry = 0; 
    lines[i].len = rand() % 20 + 5;
    lines[i].totlen = 0; 
    lines[i].finished = false;
  }


  //getmaxyx(stdscr,row,col);


  char c;

  while(1)
  {
    usleep(50000);
    for (int i = 0; i < size; i++ )
      {

      if (lines[i].curry == y)
      {
        lines[i].finished = true;
      }

      if (lines[i].totlen >= lines[i].len)
      {
        activeline[lines[i].posx] = false;
        move(lines[i].inity, lines[i].posx);
        printw(" ");
        lines[i].inity++;
      }

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

      if (lines[i].finished != true)
      {
        random= rand() % 58 + 33;
        c = random;

        attron(COLOR_PAIR(2));
        move(lines[i].curry, lines[i].posx);
        printw("%c", c);
        attroff(COLOR_PAIR(2));

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
