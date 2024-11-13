#include "tree.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

/*
* This is a recursive routine that prints a subtree starting at a node.
* Usually it is not called directly, but it is called by tree_print().
*
* We use an "in-order" traversal of the tree.  This means that the
* following order is followed:
*
*   1. if node is NULL, then just return
*   2. recurse to node->left
*   3. print count and key of node
*   4. recurse to node->right
*
* When printing a Node, use the printf() format string "%d %d\n".  The
* first number is the count of the Node; the second number is the key of
* the Node.
*/
void tree_print_node(Node *node) {
    if (node == NULL) {
	   //debug:
	  // printf("NULL node encountered");
	    return; } //node is empty nothing to do

    //debug:
   // printf("Printing node: %d (%d)\n", node->key, node->count);

    tree_print_node(node->left); //traverse the left subtree

    printf("%d %d\n", node->count, node->key); //prints count & key of node 

    tree_print_node(node->right);

}

/*
* Print a tree by calling tree_print_node() with the root of the tree.
*
* The value of tree->root might be NULL, in which case the tree is empty
* and nothing is printed.
*/
void tree_print(Tree *tree) {
    assert(tree); //ensure tree not empty

    if (tree->root == NULL) {
	    return; //if tree is empty do nothing 
    }

    tree_print_node(tree->root); //print from root node 
}

/*
* Allocate a new tree.
* Remember to use assert() to check that calloc() returns a non-NULL pointer.
*/
Tree *tree_alloc(void) {
    Tree *tree = (Tree *)calloc(1, sizeof(Tree));
    //debug:
    //printf("Allocating tree...\n");

    assert(tree);
    tree->root = NULL;
    return tree;
}

/*
* This is the most important part of the Tree abstract data type.
*
* This function searches for the key, and then:
*
*   - If the key is IN THE TREE, then increment the count for that key.
*
*   - If the key is NOT IN THE TREE, then add it to the tree, and set its
*     count to 1.
*
* See Section 2.2 of the assignment PDF for more information.
*/
void tree_add(Tree *tree, int key) {
    assert(tree);

    Node **current = &(tree->root); //starts w the address of the root 
    //debug:
    //printf("Inserting key: %d\n", key);

    while(*current != NULL) {
	    if ((*current)->key == key) {
		    (*current)->count++;
		    //debug:
		   // printf("found existing key incrementing count\n");
		    return;
	    } else if (key < (*current)->key) {
		    //debug:
		   // printf("going left\n");
		    current = &((*current)->left);
	    } else {
		    //debug:
                   // printf("going right\n");
		    current = &((*current)->right);
	    }}
    
    //create a new node
    Node *new_node = malloc(sizeof(Node));
    assert(new_node);
    
    new_node->key = key;
    new_node->count = 1;
    new_node->left = NULL;
    new_node->right = NULL;

    *current = new_node; //link new node to tree
    //debug:
    //printf("inserted node w key: %d\n", key); 
    // replace this line with your source code
}

/*
* This is a recursive routine that frees a subtree starting at a node.
* Usually it is not called directly, but it is called by tree_free().
*
* We use a "postorder" traversal of the tree to free all of the nodes of
* the tree.  This means that the following order is followed:
*
*   1. if node is NULL, then just return.
*   2. recurse to node->left
*   3. recurse to node->right
*   4. free the node
*/
void tree_free_node(Node *node) {
    if (node == NULL) {
	    return;
    }
    
    tree_free_node(node->left);
    tree_free_node(node->right);
    
    free(node);// replace this line with your source code
}

/*
* Free a tree that had been allocated by tree_alloc().
*
* 1. If the tree pointer *p already is NULL, then the tree already has been
*    freed, and so just return.
* 2. Free the nodes of the tree by calling tree_free_node() with the root
*    of the tree.
* 3. Free the tree node by calling free(*p);
* 4. Set the tree pointer to NULL:  *p = NULL;
*/
void tree_free(Tree **p) {
    assert(p);

    if (*p == NULL) {
	    return;
    }
    
    tree_free_node((*p)->root);
    free(*p);
    *p = NULL;
    // replace this line with your source code
}

/*
* Recursive routine for printing a debugging dump of a binary tree.
* Usually this routine is not called directly, but it is called by
* tree_dump().
*/
void tree_dump_node(Node *node, int level, char prefix) {
    if (node) {
        tree_dump_node(node->right, level + 1, '/');
        printf("%*c %d (x%d)\n", 4 * level + 1, prefix, node->key,
                node->count);
        tree_dump_node(node->left, level + 1, '\\');
    } else {
        printf("%*c NULL\n", 4 * level + 1, prefix);
    }
}

/*
* Print debugging output by calling tree_dump_node() with the root of the
* tree.
*
* The result of calling this routine is a text-based image of the tree that
* is printed sideways with the root on the left.  For example, this is the
* debugging output for a tree with 314 at the root, 76 to the left, and
* 95064 to the right.  (Rotate your head to the left to see it with the
* root at the top.)
*
*                 / NULL
*             / 95064 (x2)
*                 \ NULL
*         < 314 (x1)
*                 / NULL
*             \ 76 (x3)
*                 \ NULL
*/
void tree_dump(Tree *tree) {
    assert(tree);
    tree_dump_node(tree->root, 0, '<');
}

