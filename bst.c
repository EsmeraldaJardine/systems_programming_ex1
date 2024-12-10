#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
        printf("%d was not found\n", toFind);
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
    if (elem == node->value) {
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
                printf("Inserted %d to the left of %d\n", elem, node->value);
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
                printf("Inserted %d to the right of %d\n", elem, node->value);
            }
        } 
        else { insert(node->right, elem); }
    }
};

void destroyTree(node_t * node){
    if (node == NULL) {return;}

    destroyTree(node->left);
    destroyTree(node->right);
    free(node);
};

void delete(node_t * node, int elem){
    node_t *parent = NULL;
    node_t *current = node;
    bool hasLeftChild = false;
    //traversal
    while (current != NULL && current->value != elem){
        parent = current;
        if (elem < current->value){
            current = current->left;
            hasLeftChild = true;
        }else{
            current = current->right;
            hasLeftChild = false;
        }
    }
    if (current == NULL){return;}

    // leaf node 
    if (current->left == NULL && current->right == NULL) {
        // root node?
        if (current == node) {
            free(current); 
            node = NULL;
            return;
        }
        if (hasLeftChild)
            {parent->left = NULL;} 
        else 
            {parent->right = NULL;}
        free(current);
        return; //this is not doing the right thing as leaf node has no children
    } 
    // node with one child
    if (current->left == NULL || current->right == NULL) {
        node_t *child = (current->left == NULL) ? current->right : current->left;
        
        //root node?
        if (current == node) {
            node = child;
            free(current);
            return  ;
        }
        
        if (hasLeftChild)
            {parent->left = child;}
        else
            {parent->right = child;}
        
        free(current);
        return;
    }

    else {
        //node with two children
        printf("Deleting node with two children\n");
            node_t *min_elem = current->right;
            while (min_elem->left != NULL){
                min_elem = min_elem->left;
            }
            current->value = min_elem->value;
            delete(current->right, min_elem->value);


    }

    

        
};
    

int main(){
    node_t *root = createTree(10);
    insert(root, 20);
    insert(root, 5);
    insert(root, 12);
    insert(root, 5);
    search(root, 5);
    search(root, 12);
    search(root, 22);
    delete(root, 5);
    search(root, 5);
    insert(root, 7);
    insert(root, 6);
    insert(root, 8);
    insert(root, 1);
    insert(root, 3);
    insert(root, 4);


};

