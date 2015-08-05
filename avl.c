#include <malloc.h>
#include <string.h>
#include "avl.h"

#define MAX(x, y)	(x < y ? y : x)
#define BALANCE(x)	((x)->node[0]->height - (x)->node[1]->height)

typedef struct s_node {
  void *val;
  int height;
  struct s_node *node[2];
} t_node;

static t_node dummy = {0, 0, {&dummy, &dummy}};
static t_node *nil = &dummy;

/* Used by avl_show */
typedef struct s_trunk {
  char *str;
  struct s_trunk *prev;
} t_trunk;

/* default hooks */
static int __default_hook_cmp(void const* const a, void const *const b) {
  return (int)(long)b - (int)(long)a;
}

static void __default_hook_print(void const* const a) {
  printf("%d\n", (int)(long)a);
}

/* rotation and balance */
static t_node *rotate(t_avl *avl, t_node **root, int side) {
  t_node *old_root = *root;
  t_node *new_root = (*root)->node[side];

  if ((*root = new_root) == nil) {
    if (avl->hook_delete)
      avl->hook_delete(old_root->val);
    free(old_root);
  }
  else {
    old_root->node[side] = new_root->node[!side];
    old_root->height = 1 + MAX(old_root->node[0]->height, old_root->node[1]->height);
    new_root->node[!side] = old_root;
  }
  return new_root;
}

static void balance(t_avl *avl, t_node **root) {
  int b = BALANCE(*root) / 2;

  if (b) {
    int const side = (1 - b) / 2;
    if (BALANCE((*root)->node[side]) == -b)
      rotate(avl, &(*root)->node[side], !side);
    *root = rotate(avl, root, side);
  }
  if (*root != nil)
    (*root)->height = 1 + MAX((*root)->node[0]->height, (*root)->node[1]->height);
}

/* insertion */
static void __insert(t_avl *const avl, t_node **root, void *val) {
  if (*root == nil) {
    if (!(*root = malloc(sizeof(**root)))) {
      perror("malloc");
      return;
    }
    (*root)->val = val;
    (*root)->height = 1;
    (*root)->node[0] = nil;
    (*root)->node[1] = nil;
  }
  else if (avl->hook_cmp(val ,(*root)->val)) {
    __insert(avl, &(*root)->node[avl->hook_cmp(val, (*root)->val) < 0], val);
    balance(avl, root);
  }
}

/* deletion */
static void __delete(t_avl *avl, t_node **root, void *val) {
  if (*root == nil)
    return;
  if (!avl->hook_cmp((*root)->val, val)) {
    if ((*root = rotate(avl, root, BALANCE(*root) < 0)) == nil)
      return;
  }
  __delete(avl, &(*root)->node[avl->hook_cmp(val, (*root)->val) < 0], val);
  balance(avl, root);
}

/* searching */
static void *__search(t_avl *const avl, t_node *const root, void *val) {
  if (root == nil)
    return NULL;
  else if (!avl->hook_cmp(root->val, val))
    return root->val;
  else
    return __search(avl, root->node[avl->hook_cmp(root->val, val) > 0], val);
}

/* show */
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

/* functions callable externally */
t_avl *avl_new() {
  t_avl *avl;

  if (!(avl = malloc(sizeof(*avl)))) {
    perror("malloc");
    return NULL;
  }
  memset(avl, 0, sizeof(*avl));
  avl->root = nil;
  return avl;
}

void avl_insert(t_avl *const avl, void *const val) {
  if (!avl->hook_cmp) {
    fprintf(stderr, "%s: Warning: no cmp hook defined. Using default comparators.\n", __FUNCTION__);
    avl->hook_cmp = __default_hook_cmp;
  }
  __insert(avl, (t_node **)&avl->root, val);
}

void avl_remove(t_avl *const avl, void *const val) {
  if (!avl->hook_cmp) {
    fprintf(stderr, "%s: Warning: no cmp hook defined. Using default comparators.\n", __FUNCTION__);
    avl->hook_cmp = __default_hook_cmp;
  }
  __delete(avl, (t_node **)&avl->root, val);
}

void *avl_search(t_avl *const avl, void *val) {
  if (!avl->hook_cmp) {
    fprintf(stderr, "%s: Warning: no cmp hook defined. Using default comparators.\n", __FUNCTION__);
    avl->hook_cmp = __default_hook_cmp;
  }
  return __search(avl, (t_node *)avl->root, val);
}

void avl_show(t_avl *avl) {
  if (!avl->hook_print) {
    fprintf(stderr, "%s: Warning: no print hook defined. Using default.\n", __FUNCTION__);
    avl->hook_print = __default_hook_print;
  }
  __show(avl, (t_node *)avl->root, NULL, 0);
}
