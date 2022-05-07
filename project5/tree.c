#include "tree.h"
int id_counter = 0;

/*
 * @brief Allocate a new string, copy  the passed-in string over to it, and
 * return the new string
 *
 * Should fail (return NULL) if the input string is NULL or malloc fails
 *
 * @param const char *str, the string to copy
 * @return char*, a pointer to a new string
 */
char *dynamic_string_copy(const char *str) {
  if (str == NULL) {
    return NULL;
  }
  char *copy = malloc(sizeof(char) * (strlen(str) + 1));
  if (copy == NULL) {
    return NULL;
  }
  strcpy(copy, str);
  return copy; 
  free(copy);
}

/*
 * @brief Allocate a new Tree, and return a pointer to it. You should initialize
 * it to have a NULL root and num_nodes = 0
 *
 * Should fail (return NULL) if malloc fails
 *
 * @return Tree*, a pointer to the new tree. NULL if malloc fails
 */
Tree *create_tree(void) { 
  Tree *tree = malloc(sizeof(Tree));
  if (tree == NULL) {
    return NULL;
  }
  tree -> root = NULL;
  tree -> num_nodes = 0;
  return tree; 
  free(tree);
}

/*
 * @brief Allocate and initialize a new Node with a copy of the given data, and
 * return a pointer to it. Make sure to use the global id counter (increment
 * this counter for every new node)! For example, if you call create_node(...)
 * one time, the node returned should have an ID of 0. If you call it a second
 * time, the node returned should have an ID of 1
 *
 * Should fail (return NULL) if the input string is NULL or malloc fails
 *
 * @param const char *str, copy this string and use it as the new Node's data
 * @return Node*, a pointer to the new node. NULL if malloc fails
 */
Node *create_node(const char *str) {
  Node *node = malloc(sizeof(Node));
  if (node == NULL) {
    return NULL;
  }
  node -> id = id_counter;
  id_counter++;
  node -> data = dynamic_string_copy(str);
  if (node -> data == NULL) {
    id_counter--;
    return NULL;
  }
  node -> parent = NULL;
  node -> children = NULL;
  node -> num_children = 0;
  return node;
  free(node);
}

/*
 * @brief Traverse the given Tree, and return a pointer to the Node with the
 * given id. Return NULL if it does not exist
 *
 * Should fail (return NULL) if the given tree is NULL or if a node with the
 * given id is not found
 *
 * @param Tree *tree, the tree to search in
 * @param int id, the id to search for in the tree
 * @return Node*, a pointer to the found node
 */

Node *find_Node_Helper(Node *node, int id);

Node *find_node(Tree *tree, int id) {
  if (tree == NULL || id < 0) {
    return NULL;
  }
  return find_Node_Helper(tree -> root, id);
}

Node *find_Node_Helper(Node *node, int id) {
  if (node -> id == id) {
    return node;
  } else if (node -> num_children == 0) {
    return NULL;
  } else {
    for (int i = 0; i < node -> num_children; i++) {
      Node *result = find_Node_Helper(node -> children[i], id);
      if (result != NULL) {
        return result;
      }
    }
    return NULL;
  }
}

/*
 * @brief Update the data of the Node with the given id. Return the old data
 *
 * Should fail (return NULL) if the given tree is NULL or if a node with the
 * given id is not found. Also fail if malloc fails (when copying the string)
 *
 * @param Tree *tree, the tree to look in
 * @param int id, the id of the node to update
 * @param const char *new_data, the string to copy and update the node with
 * @return char*, a pointer to the old data of the node. NULL if the method
 * fails
 */
char *update_node(Tree *tree, int id, const char *new_data) {
  if (tree == NULL) {
    return NULL;
  }
  if (new_data == NULL) {
    return NULL;
  }

  Node *updated_node = find_node(tree, id);
  if (updated_node == NULL) {
    return NULL;
  }
  char *old_data = updated_node -> data;
  char *copy = malloc((strlen(new_data) + 1) * sizeof(char));
  if (copy == NULL) {
    return NULL;
  }
  strcpy(copy, new_data);
  updated_node -> data = copy;
  return old_data;
}

/*
 * @brief Create a new Node, and insert it as the last child of the existing
 * Node in the Tree with the id parent_id. Return 0 if this method fails, and 1
 * if it succeeds
 *
 * Should fail if the given tree is NULL, a node with the given id is found, or
 * the given data is NULL. Should also fail if malloc fails at any point. Make
 * sure to free things you have malloced along the way if you fail!
 *
 * @param Tree *tree, the tree to look in
 * @param int parent_id, the id of the node the add a child to
 * @param const char *new_child_data, the data to copy and use for the new child
 * @return int, 1 if success, 0 if failure
 */
int insert_node(Tree *tree, int parent_id, const char *new_child_data) {
  int failure = 0;
  int success = 1;
  if (tree == NULL || parent_id < 0 || new_child_data == NULL) {
    return failure;
  }
  Node *parent = find_node(tree, parent_id);
  if (parent == NULL) {
    return failure;
  }
  Node *child = create_node(new_child_data);
  if (child == NULL) {
    return failure;
  }
  Node **children = realloc(parent -> children, sizeof(Node) * (parent->num_children + 1));
  if (children == NULL) {
    free(child -> data);
    free(child);
    return failure;
  }
  parent -> children = children;
  parent -> children[parent -> num_children] = child;
  parent -> num_children++;
  child -> parent = parent;
  tree -> num_nodes++;
  return success;
}

/*
 * @brief Remove the Node with the given id. Assign all of the removed Node's
 * children to its parent, and return the removed Node's data. Do not worry
 * about removing the root of a tree
 *
 * Should fail if the given tree is NULL, a node with the given id is not found,
 * the node to remove is the root, or malloc fails
 *
 * @param Tree *tree, the tree to look in
 * @param int id, the id of the node to remove from the tree
 * @return char*, a pointer to the data of the removed node
 */
char *remove_node(Tree *tree, int id) {
  if (tree == NULL) {
    return NULL;
  }
  Node *node_id = find_node(tree, id);
  if (node_id == NULL || node_id == tree -> root) {
    return NULL;
  }
  Node *children_id =  realloc(node_id -> children, sizeof(Node) * (node_id -> num_children - 1));
  if (children_id == NULL) {
    return NULL;
  }
  children_id -> parent = node_id -> parent;
  node_id -> children = NULL;
  node_id -> parent = NULL;
  tree -> num_nodes--;
  return node_id -> data;
  free(node_id);
}

/*
 * @brief Sort the array of children of the Node with the the given id. Use the
 * given comparison function for sorting. You can use any sorting algorithm you
 * like
 *
 * Should fail if the given tree is NULL, the given function pointer is NULL, or
 * a node with the given id is not found
 *
 * @param Tree *tree, the tree to search in
 * @param int id, the id of the node whose children we are sorting
 * @param int (*compare_func)(char*, char*), the comparison function to use for
 * sorting
 */
void sort_children(Tree *tree, int id, int (*compare_func)(char *, char *)) {
  UNUSED(tree);
  UNUSED(id);
  UNUSED(compare_func);
}

/*
 * @brief Completely destroy the given Tree. This means freeing everything that
 * the Tree references (all Nodes)
 *
 * @param Tree *tree, the tree to destroy
 */
void destroy_tree(Tree *tree) { 
   if (tree == NULL) {
     return;
   }
   destroy_node(tree -> root);
   free(tree);
}

/*
 * @brief Completely destroy the given Node. This function should probably be
 * recursive
 *
 * @param Node *node, the node to destroy
 */
void destroy_node(Node *node) { 
  if (node == NULL) {
    return;
  } else {
    free(node -> data);
    for (int i = 0; i < (node -> num_children) - 1; i++) {
      destroy_node(node -> children[i]);
    }
    free(node);
  }
}

/*
 * @brief Build a Tree from a specification in a file, and return a pointer to
 * it. The file will contain text in a format like:
 *
 * a:( bb:( ccc:() ddd:() ) ee:( fff:() ) gg:() )
 *
 * Each node starts with a string of non-colon characters (at least length 1).
 * This is the node's data. Following the colon is a a set of parentheses
 * containing a list of whitespace-separated child nodes. A node will no
 * children will have an empty set of parentheses. Of course, the outermost node
 * is the root of the tree
 *
 * Should return NULL if malloc fails at any time (make sure to free your
 * previous allocations though). Do not worry about the format of text in the
 * file being incorrect
 *
 * @param FILE *file, the file pointer to read text from
 * @return Tree*, a pointer to the built tree
 */
Tree *build_tree(FILE *file) {
  /*
   * This function is tricky, so here's some partial pseudocode + hints
   *
   * Create a recursive helper function with prototype
   * Node *build_tree_helper(Tree*, FILE*);
   * which will parse a node from the given file-pointer, and update the given
   * Tree by incrementing tree->num_nodes as necessary.
   *
   * The main file IO functions you will need to implement this are:
   * fgetc and ungetc (fscanf could also potentially be useful)
   *
   * Node *build_tree_helper(Tree *tree, FILE *file) {
   *     // read from the filepointer until you reach a colon (there are many
   *     // ways to do this). place that string in a char buffer then call:
   *     Node *node = create_node(buffer);
   *     // skip the colon and open-parenthesis
   *     // do a while loop over each character of the file
   *     while (c = next char of the file) {
   *         if (c == ')' || c is the end of the file) {
   *             // the list of children is over! just break from the loop
   *         }
   *         if (c != ' ') {
   *             // we have encountered a child node! Its time to
   *             // "unget" the character (so the recursive call can parse it)
   *             // and then make a recursive call to parse the child
   *             unget the character c;
   *             Node *child = build_tree_helper(tree, file);
   *             // do a null check!!
   *             // insert the new child into node
   *             // remember to increment tree->num_nodes and
   *             // node->num_children!
   *         }
   *     }
   *     // we either reached the end of the file or broke from the loop
   *     // just return
   *     return node;
   * }
   *
   * Once you have this helper function, the main function shouldn't be too much
   * more work. Just create a tree and call the helper once
   *
   */

  UNUSED(file);
  return NULL;
}