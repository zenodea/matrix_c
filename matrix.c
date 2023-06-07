#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  time_t start;
  int random, count;
  char c;
  start = time (NULL) + 0.1 ;
  while(1)
  {
    if (time (NULL) > start)
    {
      random=rand() % 256;
      c = random;
      printf("\033[1;32m%c\033[0m\n",c);
      count++;
      start = start + 1;
    }


  }
  return 1;
}
