#pragma once

typedef struct s_node {
  int val;
  int height;
  struct s_node *left;
  struct s_node *right;
} t_node;

extern struct s_node dummy;
extern struct s_node *nil;

void insert(t_node **root, int val);

#define MAX(x, y)	(x < y ? y : x)
#define BALANCE(x)	((x)->left->height - (x)->right->height)
