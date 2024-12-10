#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node {
    int value;             
    struct node *left;    
    struct node *right;   
} node_t;

node_t *createTree(int firstElem) {
    node_t *root = malloc(sizeof(node_t));
    if (root == NULL) {
        return NULL;
    }
    root->value = firstElem;
    root->left = NULL;
    root->right = NULL;
    return root;
}

node_t * search(node_t * node, int toFind){
    if (node == NULL) {
        printf("%d was not found\n", toFind);
        return NULL;
    }
    if (toFind == node->value) {
        printf("%d was found\n", node->value);
        return node;
    }
    if (toFind < node->value) {
        printf("Searching left of %d\n", node->value);
        return search(node->left, toFind);
    }
    else {
        printf("Searching right of %d\n", node->value);
        return search(node->right, toFind);
    }
}

void insert(node_t *node, int elem){
    if (elem == node->value) {
        return;
    }
    // left subtree
    if (elem < node->value) {
        if (node->left == NULL) {
            node->left = malloc(sizeof(node_t));
            if (node->left != NULL) {
                node->left->value = elem;
                node->left->left = NULL;
                node->left->right = NULL;
                printf("Inserted %d to the left of %d\n", elem, node->value);
            }
        } else { 
            insert(node->left, elem);
        }
    }
    //right subtree
    if (elem > node->value) {
        if (node->right == NULL) {
            node->right = malloc(sizeof(node_t));
            if (node->right != NULL) { 
                node->right->value = elem;
                node->right->left = NULL;
                node->right->right = NULL;
                printf("Inserted %d to the right of %d\n", elem, node->value);
            }
        } else {
            insert(node->right, elem);
        }
    }
}

void destroyTree(node_t * node){
    if (node == NULL) {return;}

    destroyTree(node->left);
    node->left = NULL; 

    destroyTree(node->right);
    node->right = NULL;
    free(node);
}

void delete(node_t * node, int elem){
    node_t *parent = NULL;
    node_t *current = node;
    bool isLeftChild = false;
    //traversal
    while (current != NULL && current->value != elem){
        parent = current;
        if (elem < current->value){
            current = current->left;
            isLeftChild = true;
        }else{
            current = current->right;
            isLeftChild = false;
        }
    }
    if (current == NULL){return;}

    // leaf node 
    if (current->left == NULL && current->right == NULL) {
        if (parent == NULL) {
            free(current); 
            return;
        }

        if (isLeftChild){
            parent->left = NULL;
        } 
        else{
            parent->right = NULL;
        }

        free(current);
        printf("Deleted leaf node\n");
        return; 
    } 
    // node with one child
    if (current->left == NULL || current->right == NULL) {
        node_t *child = (current->left == NULL) ? current->right : current->left;
        if (parent == NULL) {
            *node = *child;
            free(child);
            return;
        }
        if (isLeftChild){
            parent->left = child;
        }else{
            parent->right = child;
        }
        
        free(current);
        return;
    }else {
        // node with two children
        printf("Deleting node with two children\n");
        node_t *min_elem = current->right;
        node_t *min_elem_parent = current;
        while (min_elem->left != NULL) { 
            min_elem_parent = min_elem;
            min_elem = min_elem->left;
        }
        current->value = min_elem->value;    
        if (min_elem_parent->left == min_elem) { 
            min_elem_parent->left = min_elem->right; 
        } else {
            min_elem_parent->right = min_elem->right; 
        }
        free(min_elem);
    }
        
}
    



