#pragma once

typedef struct s_avl {
  void *root;
  int (*hook_cmp)(const void *, const void *);
  void (*hook_print)(const void *);
  void (*hook_delete)(const void *);
} t_avl;

t_avl *avl_new();
void avl_insert(t_avl *const avl, void *const val);
void *avl_search(t_avl *const avl, void *val);
void avl_show(t_avl *avl);
void avl_delete(t_avl *const avl, void *const val);
