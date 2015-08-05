# AVL

It's a simple generic implementation of the AVL that I wrote in C. An AVL is a self-balancing binary tree, that is balanced at insertion and at removal. It make it slower but searching is really fast.

## Usage

You can stock the data you want in it. The t_avl structure is defined as it :

```C
typedef struct s_avl {
  void *root;
  int (*hook_cmp)(const void *, const void *);
  void (*hook_print)(const void *);
  void (*hook_remove)(void *);
} t_avl;
```

**root** is a pointer to the root of the tree. You don't have to modify it;  
**hook_cmp** is a function used to compare two functions, because datas in the avl are *void \**. The function must have the same behavior than *strcmp*.  
**hook_print** is a function used to print the value of your data. It must not contain any \n.  
**hook_remove** is the function that is called before any deletion in the AVL. it can be used if your data need to be freed for example.

Note that if **hook_cmp** and **hook_print** are not defined, it will be assumed that your data is int.

Here is the available functions :

```C
t_avl *avl_new(void); /* It will alloc a new AVL and return it to you. The returned pointer has to be sent to avl_delete and must be verified. */
void avl_insert(t_avl *const avl, void *const val); /* It will add the data val in the avl, using the hook_cmp defined above */
void *avl_search(t_avl *const avl, void *const val); /* It will search for the data val and return the found data. It is usefull when that you search is not exactly what you store in your tree (a hash-table or a strucure for example)  */
void avl_show(t_avl *const avl); /* It will display the tree in a human readable format, using the hook_print defined above */
void avl_remove(t_avl *const avl, void *const val); /* It will search for the data val and remove it from the tree. */
void avl_delete(t_avl *const avl); /* It will delete and free the avl and all his data */
```

### Author

Emeraude
