#include <malloc.h>
#include "avl.h"

struct s_node dummy = {0, 0, {&dummy, &dummy}};
struct s_node *nil = &dummy;

t_node *rotate(t_node **root, int side) {
  t_node *old_root = *root;
  t_node *new_root = (*root)->node[side];

  if ((*root = new_root) == nil)
    free(old_root);
  else {
    old_root->node[side] = new_root->node[!side];
    old_root->height = 1 + MAX(old_root->node[0]->height, old_root->node[1]->height);
    new_root->node[!side] = old_root;
  }
  return new_root;
}

void balance(t_node **root) {
  int b = BALANCE(*root) / 2;

  if (b) {
    int const side = (1 - b) / 2;
    if (BALANCE((*root)->node[side]) == -b)
      rotate(&(*root)->node[side], !side);
    *root = rotate(root, side);
  }
  if (*root != nil)
    (*root)->height = 1 + MAX((*root)->node[0]->height, (*root)->node[1]->height);
}

void insert(t_node **root, int val) {
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
  else if (val != (*root)->val) {
    insert(&(*root)->node[val > (*root)->val], val);
    balance(root);
  }
}
