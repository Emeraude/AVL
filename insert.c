#include <malloc.h>
#include "avl.h"

struct s_node dummy = {0, 0, {&dummy, &dummy}};
struct s_node *nil = &dummy;

t_node *rotate_left(t_node **root) {
  t_node *old_root = *root;
  t_node *new_root = (*root)->node[1];

  if ((*root = new_root) == nil)
    free(old_root);
  else {
    old_root->node[1] = new_root->node[0];
    old_root->height = 1 + MAX(old_root->node[0]->height, old_root->node[1]->height);
    new_root->node[0] = old_root;
  }
  return new_root;
}

t_node *rotate_right(t_node **root) {
  t_node *old_root = *root;
  t_node *new_root = (*root)->node[0];

  if ((*root = new_root) == nil)
    free(old_root);
  else {
    old_root->node[0] = new_root->node[1];
    old_root->height = 1 + MAX(old_root->node[0]->height, old_root->node[1]->height);
    new_root->node[1] = old_root;
  }
  return new_root;
}

void balance(t_node **root) {
  int b = BALANCE(*root) / 2;

  if (b) {
    if ((1 - b) / 2) {
      if (BALANCE((*root)->node[1]) == -b)
	rotate_right(&(*root)->node[1]);
      *root = rotate_left(root);
    }
    else {
      if (BALANCE((*root)->node[0]) == -b)
	rotate_left(&(*root)->node[0]);
      *root = rotate_right(root);
    }
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
    if (val > (*root)->val) {
      insert(&(*root)->node[1], val);
      balance(root);
    }
    else {
      insert(&(*root)->node[0], val);
      balance(root);
    }
  }
}
