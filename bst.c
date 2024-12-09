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
    if (node == NULL){return;}
    //traversal
    if (elem < node->value){
        delete(node->left, elem);
    }
    else if (elem > node->value){
        delete(node->right, elem);
    }
    else{
        //leaf node
        if (elem == node->value && node->left == NULL && node->right == NULL){
        printf("Deleting leaf node\n");
        free(node);
        return;
        } 
        //node with one child
        if (elem == node->value && node->left != NULL || node->right != NULL){
            printf("Deleting node with one child\n");
            node_t *child = (node->left != NULL) ? node->left : node->right; //child pointer
            node->value = child->value;
            node->left = child->left;
            node->right = child->right;
            free(child);
        }
        //node with two children
        if (elem == node->value && node->left != NULL && node->right != NULL){
            printf("Deleting node with two children\n");
            node_t *min_elem = node->right;
            while (min_elem->left != NULL){
                min_elem = min_elem->left;
            }
            node->value = min_elem->value;
            delete(node->right, min_elem->value);
        }
    }
};
    

int main(){
    node_t *root = createTree(10);
    insert(root, 20);
    insert(root, 5);
    insert(root, 12);
    insert(root, 5);
    printf("%d\n", root->left->value);
    printf("%d\n", root->right->value);
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

