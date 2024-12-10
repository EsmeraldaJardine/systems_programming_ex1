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
}

void destroyTree(node_t * node){
    if (node == NULL) {return;}

    destroyTree(node->left);
    destroyTree(node->right);
    free(node);
}

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
            printf("Deleted root node\n");
            return;
        }
        if (hasLeftChild)
            {parent->left = NULL;} 
        else 
            {parent->right = NULL;}
        free(current);
        printf("Deleted leaf node\n");
        return; //this is not doing the right thing as leaf node has no children
    } 
    // node with one child
    if (current->left == NULL || current->right == NULL) {
        node_t *child = (current->left == NULL) ? current->right : current->left;
        
        //root node?
        if (current == node) {
            *node = *child;
            free(current);
            return;
        }
        
        if (hasLeftChild)
            {parent->left = child;}
        else
            {parent->right = child;}
        
        free(current);
        return;
    }

    else {
    // node with two children
    printf("Deleting node with two children\n");
    node_t *min_elem = current->right;
    node_t *min_elem_parent = current;
    while (min_elem->left != NULL) { // find the smallest element in the right subtree
        min_elem_parent = min_elem;
        min_elem = min_elem->left;
    }
    current->value = min_elem->value; // replace the current node with the smallest element
    if (min_elem_parent->left == min_elem) { // handle the case where the smallest element is the left child of its parent 
        min_elem_parent->left = min_elem->right; // set the right child of the smallest element as the left child of its parent (null or not)
    } else {
        min_elem_parent->right = min_elem->right; // handle the case where the smallest element is the right child of its parent
    }
    free(min_elem);
    }
        
}
    

int main(){
    node_t *root = createTree(10);
    insert(root, 5);
    insert(root, 15);
    insert(root, 8);
    insert(root, 3);
    insert(root, 12);
    insert(root, 18);
    insert(root, 1);
    insert(root, 4);
    insert(root, 7);
    insert(root, 9);
    insert(root, 11);
    insert(root, 13);
    insert(root, 17);
    insert(root, 19);
    delete(root, 10);
    search(root, 10);
    search(root, 5);
}

