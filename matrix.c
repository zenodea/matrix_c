#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  int random;
  char c;
  while(1)
  {
    random=rand() % 249;
    c = random;
    printf("%c",c);

  }
  printf("\033[1;37mTHIS IS WHITE TEXT\033[0m\n");
  printf("\033[1;32mTHIS IS GREEN TEXT\033[0m\n");
  return 1;
}
