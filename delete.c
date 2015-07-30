#include "avl.h"

void delete(t_node **root, int val) {
  if (*root == nil)
    return;
  if ((*root)->val == val) {
    if ((*root = rotate(root, BALANCE(*root) < 0)) == nil)
      return;
  }
  delete(&(*root)->node[val > (*root)->val], val);
  balance(root);
}
