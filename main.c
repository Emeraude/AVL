#include <time.h>
#include <stdlib.h>
#include "avl.h"

int main(int ac, char **av)
{
  int x;
  t_avl *avl;

  avl = avl_new();
  srand(time(0));

  for (x = 0; x < 32; x++)
    if (rand()&1)
      avl_insert(avl, (void *)(long)(rand() % 32));

  avl_show(avl);
  avl_delete(avl, (void *)(long)12);
  avl_show(avl);
  return 0;
}
