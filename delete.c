#include <stdio.h>
#include "avl.h"

static void __delete(t_avl *avl, t_node **root, void *val) {
  if (*root == nil)
    return;
  if (!avl->hook_cmp((*root)->val, val)) {
    if ((*root = rotate(root, BALANCE(*root) < 0)) == nil)
      return;
  }
  __delete(avl, &(*root)->node[avl->hook_cmp(val, (*root)->val) < 0], val);
  balance(root);
}

static int __default_hook_cmp(void const* const a, void const *const b) {
  return (int)(long)b - (int)(long)a;
}

void avl_delete(t_avl *const avl, void *const val) {
  if (!avl->hook_cmp) {
    fprintf(stderr, "%s: Warning: no cmp hook defined. Using default comparators.\n", __FUNCTION__);
    avl->hook_cmp = __default_hook_cmp;
  }
  __delete(avl, &avl->root, val);
}
