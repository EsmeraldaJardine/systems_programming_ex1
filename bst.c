#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int value;             // The value stored in the node
    struct node *left;     // Pointer to the left child
    struct node *right;    // Pointer to the right child
} node_t;


node_t *initialise_tree(int firstElem) {
    node_t *root = malloc(sizeof(node_t));
    if (root == NULL) {
        return NULL;
    }
    root->value = firstElem;
    root->left = NULL;
    root->right = NULL;
    return root;
    

};


