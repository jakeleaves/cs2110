/* DO NOT MODIFY FILE */

#ifndef TREE_H
#define TREE_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define UNUSED(x) ((void)x)

typedef struct Node {
  int id;
  char *data;
  struct Node *parent;
  int num_children;
  struct Node **children;
} Node;

typedef struct Tree {
  Node *root;
  int num_nodes;
} Tree;

extern int id_counter;

char *dynamic_string_copy(const char *str);
Tree *create_tree(void);
Node *create_node(const char *str);
Node *find_node(Tree *tree, int id);
char *update_node(Tree *tree, int id, const char *new_data);
int insert_node(Tree *tree, int parent_id, const char *new_child_data);
char *remove_node(Tree *tree, int id);
void sort_children(Tree *tree, int parent_id,
                   int (*compare_func)(char *, char *));
void destroy_node(Node *node);
void destroy_tree(Tree *tree);
Tree *build_tree(FILE *file);

#endif
