#include <stdio.h>
#include <stdlib.h>
#define RED 0
#define BLACK 1

struct Node {
    int data;
    int color;
    struct Node *left, *right, *parent;
};
struct Node *root = NULL;
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->color = RED; 
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}
void rotateLeft(struct Node **root, struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
}
void rotateRight(struct Node **root, struct Node *y) {
    struct Node *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;
    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;
    x->right = y;
    y->parent = x;
}
void fixViolation(struct Node **root, struct Node *z) {
    while (z != *root && z->parent->color == RED) {
        struct Node *grandparent = z->parent->parent;
        if (z->parent == grandparent->left) {
            struct Node *uncle = grandparent->right;
            if (uncle != NULL && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }
            else {
                if (z == z->parent->right) {
                    z = z->parent;
                    rotateLeft(root, z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                rotateRight(root, grandparent);
            }
        }
        else {
            struct Node *uncle = grandparent->left;
            if (uncle != NULL && uncle->color == RED) {
                z->parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }
            else {
                if (z == z->parent->left) {
                    z = z->parent;
                    rotateRight(root, z);
                }
                z->parent->color = BLACK;
                grandparent->color = RED;
                rotateLeft(root, grandparent);
            }
        }
    } (*root)->color = BLACK;
}
void insert(struct Node **root, int data){
    struct Node *z = createNode(data);
    struct Node *y = NULL;
    struct Node *x = *root;
    while (x != NULL) {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;
    fixViolation(root, z);
}
void inorder(struct Node *root) {
    if (root == NULL)
        return;
    inorder(root->left);
    printf("%d(%s) ", root->data, root->color == RED ? "R" : "B");
    inorder(root->right);
}
int main() {
    int arr[] = {10, 20, 30, 15, 25, 5, 1};
    int n = sizeof(arr)/sizeof(arr[0]);
    for (int i = 0; i < n; i++) {
        
        insert(&root, arr[i]);
    }
    printf("Inorder Traversal of Red-Black Tree:\n");
    inorder(root);
    printf("\n");
    return 0;
}
