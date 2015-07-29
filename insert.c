#include <malloc.h>
#include "avl.h"

struct s_node dummy = {0, 0, &dummy, &dummy};
struct s_node *nil = &dummy;

t_node *rotate_left(t_node **root) {
  t_node *old_root = *root;
  t_node *new_root = (*root)->right;

  if ((*root = new_root) == nil)
    free(old_root);
  else {
    old_root->right = new_root->left;
    old_root->height = 1 + MAX(old_root->left->height, old_root->right->height);
    new_root->left = old_root;
  }
  return new_root;
}

t_node *rotate_right(t_node **root) {
  t_node *old_root = *root;
  t_node *new_root = (*root)->left;

  if ((*root = new_root) == nil)
    free(old_root);
  else {
    old_root->left = new_root->right;
    old_root->height = 1 + MAX(old_root->left->height, old_root->right->height);
    new_root->right = old_root;
  }
  return new_root;
}

void balance(t_node **root) {
  int b = BALANCE(*root) / 2;

  if (b) {
    if ((1 - b) / 2) {
      if (BALANCE((*root)->right) == -b)
	rotate_right(&(*root)->right);
      *root = rotate_left(root);
    }
    else {
      if (BALANCE((*root)->left) == -b)
	rotate_left(&(*root)->left);
      *root = rotate_right(root);
    }
  }
  if (*root != nil)
    (*root)->height = 1 + MAX((*root)->left->height, (*root)->right->height);
}

void insert(t_node **root, int val) {
  if (*root == nil) {
    if (!(*root = malloc(sizeof(**root)))) {
      perror("malloc");
      return;
    }
    (*root)->val = val;
    (*root)->height = 1;
    (*root)->left = nil;
    (*root)->right = nil;
  }
  else if (val != (*root)->val) {
    if (val > (*root)->val) {
      insert(&(*root)->right, val);
      balance(root);
    }
    else {
      insert(&(*root)->left, val);
      balance(root);
    }
  }
}
