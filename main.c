#include <time.h>
#include <stdlib.h>
#include "avl.h"

int main(void)
{
  int x;
  t_node *root = nil;

  srand(time(0));

  for (x = 0; x < 32; x++)
    if (rand()&1)
      insert(&root, rand() % 32);

  show(root);
  delete(&root, 12);
  show(root);
  return 0;
}
