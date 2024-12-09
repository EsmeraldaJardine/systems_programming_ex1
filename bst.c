#include <stdio.h>
#include <stdlib.h>


typedef struct node {
    int value;             // The value stored in the node
    struct node *left;     // Pointer to the left child
    struct node *right;    // Pointer to the right child
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
    

};

node_t * search(node_t * node, int toFind){
    if (node == NULL) {
        printf("Not found\n");
        return NULL;
    }
    if (toFind == node->value) {
        printf("%d was found\n", node->value);
        return node;
    }
    if (toFind < node->value) {
        return search(node->left, toFind);
    }
    else {
        return search(node->right, toFind);
    }

};


void insert(node_t *node, int elem){
    if (elem == node->value || node == NULL) {
        printf("Error \n");
        return;
    }
    // left subtree
    if (elem < node->value) {
        if (node->left == NULL) {
            node->left = malloc(sizeof(node_t));
            if (node->left != NULL) { // if malloc was successful
                node->left->value = elem;
                node->left->left = NULL;
                node->left->right = NULL;
            }
        } 
        else { insert(node->left, elem); }
    }
    //right subtree
    if (elem > node->value) {
        if (node->right == NULL) {
            node->right = malloc(sizeof(node_t));
            if (node->right != NULL) { // if malloc was successful
                node->right->value = elem;
                node->right->left = NULL;
                node->right->right = NULL;
            }
        } 
        else { insert(node->right, elem); }
    }
};
    

int main(){
    node_t *root = createTree(10);
    insert(root, 5);
    insert(root, 12);
    insert(root, 5);
    printf("%d\n", root->left->value);
    printf("%d\n", root->right->value);
    search(root, 5);
    search(root, 12);
    search(root, 22);
};

