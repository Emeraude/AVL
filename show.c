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

static void __show(t_avl *avl, t_node *root, t_trunk *prev, int is_left) {
  t_trunk disp = {"    ", prev};
  char *prev_str = disp.str;

  if (root == nil)
    return;
  __show(avl, root->node[0], &disp, 1);
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
  avl->hook_print(root->val);
  if (prev)
    prev->str = prev_str;
  disp.str = "   |";
  __show(avl, root->node[1], &disp, 0);
  if (!prev)
    printf("\n");
}


static void __default_hook_print(void const* const a) {
  printf("%d\n", (int)(long)a);
}


void avl_show(t_avl *avl) {
  if (!avl->hook_print) {
    fprintf(stderr, "%s: Warning: no print hook defined. Using default.\n", __FUNCTION__);
    avl->hook_print = __default_hook_print;
  }
  __show(avl, avl->root, NULL, 0);
}
