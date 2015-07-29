#include "avl.h"

void delete(t_node **root, int val) {
  if (*root == nil)
    return;
  if ((*root)->val == val) {
    if (BALANCE(*root) < 0) {
      if ((*root = rotate_left(root)) == nil)
	return;
    }
    else if ((*root = rotate_right(root)) == nil)
      return;
  }
  if (val > (*root)->val)
    delete(&(*root)->right, val);
  else
    delete(&(*root)->left, val);
  balance(root);
}
