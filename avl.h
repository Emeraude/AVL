#pragma once

typedef struct s_node {
  void *val;
  int height;
  struct s_node *node[2];
} t_node;

typedef struct s_avl {
  t_node *root;
  int (*hook_cmp)(const void *, const void *);
  void (*hook_print)(const void *);
  void (*hook_delete)(const void *);
} t_avl;

extern struct s_node dummy;
extern struct s_node *nil;

t_node *rotate(t_node **root, int side);
void balance(t_node **root);

void insert(t_node **root, int val);
void show(t_node *root);
void delete(t_node **root, int val);

t_avl *avl_new();
void avl_insert(t_avl *const avl, void *const val);
void *avl_search(t_avl *const avl, void *val);
void avl_show(t_avl *avl);
void avl_delete(t_avl *const avl, void *const val);

#define MAX(x, y)	(x < y ? y : x)
#define BALANCE(x)	((x)->node[0]->height - (x)->node[1]->height)
