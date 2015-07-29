#include <stdio.h>
#include "avl.h"

typedef struct s_trunk {
  char *str;
  struct s_trunk *prev;
} t_trunk;

static void show_trunks(t_trunk *trunk) {
  if (!trunk)
    return;
  show_trunks(trunk->prev);
  printf("%s", trunk->str);
}

static void __show(t_node *root, t_trunk *prev, int is_left) {
  t_trunk disp = {"    ", prev};
  char *prev_str = disp.str;

  if (root == nil)
    return;
  __show(root->left, &disp, 1);
  if (!prev)
    disp.str = "---";
  else if (is_left) {
    disp.str = ".--";
    prev_str = "   |";
  }
  else {
    disp.str = "`--";
    prev->str = prev_str;
  }
  show_trunks(&disp);
  printf("%d\n", root->val);
  if (prev)
    prev->str = prev_str;
  disp.str = "   |";
  __show(root->right, &disp, 0);
  if (!prev)
    printf("\n");
}

void show(t_node *root) {
  __show(root, NULL, 0);
}
