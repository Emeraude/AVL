#pragma once

typedef struct s_node {
  int val;
  int height;
  struct s_node *node[2];
} t_node;

extern struct s_node dummy;
extern struct s_node *nil;

t_node *rotate(t_node **root, int side);
void balance(t_node **root);

void insert(t_node **root, int val);
void show(t_node *root);
void delete(t_node **root, int val);

#define MAX(x, y)	(x < y ? y : x)
#define BALANCE(x)	((x)->node[0]->height - (x)->node[1]->height)
