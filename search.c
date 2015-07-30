#include <stdio.h>
#include "avl.h"

void *__search(t_avl *const avl, t_node *const root, void *val) {
  if (root == nil)
    return NULL;
  else if (!avl->hook_cmp(root->val, val))
    return root->val;
  else
    __search(avl, root->node[avl->hook_cmp(root->val, val) > 0], val);
}

static int __default_hook_cmp(void const* const a, void const *const b) {
  return (int)(long)b - (int)(long)a;
}

void *avl_search(t_avl *const avl, void *val) {
  if (!avl->hook_cmp) {
    fprintf(stderr, "%s: Warning: no cmp hook defined. Using default comparators.\n", __FUNCTION__);
    avl->hook_cmp = __default_hook_cmp;
  }
  return __search(avl, avl->root, val);
}
