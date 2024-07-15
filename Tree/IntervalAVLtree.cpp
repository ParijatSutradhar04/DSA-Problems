#include<bits/stdc++.h>
using namespace std;

// Structure to represent an interval
struct Interval{
    int low, high;
};

// Structure to represent a node in the AVL tree
struct Node{
    Interval i; // interval stored in the node
    int max; // maximum value of the high of the intervals in the subtree rooted at this node
    Node *left, *right; // left and right children of the node
    int height; // height of the node
};


// Function to get the maximum of two integers
int max(int a, int b){
    return (a > b) ? a : b;
}

// Function to get the height of the node
int height(Node* node){
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

// Function to create a new node with the given interval
Node* newNode(Interval i){
    Node* node = new Node;
    node->i = i;
    node->max = i.high;
    node->left = node->right = NULL;
    node->height = 1;
    return node;
}

// Function to get the balance factor of the node
int getBalance(Node* node){
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

// Function to right rotate the subtree rooted with y
Node* rightRotate(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;
    // Perform rotation
    x->right = y;
    y->left = T2;
    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    // Update max values
    y->max = max(y->i.high, max((y->left != NULL) ? y->left->max : 0, (y->right != NULL) ? y->right->max : 0));
    x->max = max(x->i.high, max((x->left != NULL) ? x->left->max : 0, (x->right != NULL) ? x->right->max : 0));
    // Return new root
    return x;
}

// Function to left rotate the subtree rooted with x
Node* leftRotate(Node* x){
    Node* y = x->right;
    Node* T2 = y->left;
    // Perform rotation
    y->left = x;
    x->right = T2;
    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    // Update max values
    x->max = max(x->i.high, max((x->left != NULL) ? x->left->max : 0, (x->right != NULL) ? x->right->max : 0));
    y->max = max(y->i.high, max((y->left != NULL) ? y->left->max : 0, (y->right != NULL) ? y->right->max : 0));
    // Return new root
    return y;
}

// Insert a new interval into the AVL tree
Node* insert(Node* node, Interval i) {
    // If the tree is empty, return a new node
    if (node == NULL) {
        return newNode(i);
    }
    // If the interval to be inserted is smaller than the root's interval, then it goes to the left subtree
    if (i.low < node->i.low) {
        node->left = insert(node->left, i);
    }
    // If the interval to be inserted is greater than the root's interval, then it goes to the right subtree
    else if (i.low > node->i.low) {
        node->right = insert(node->right, i);
    }
    // Update the max value of this ancestor if needed
    node->max = max(node->max, i.high);
    // Update the height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));
    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = getBalance(node);
    // If this node becomes unbalanced, then there are 4 cases
    // Left Left Case
    if (balance > 1 && i.low < node->left->i.low) {
        return rightRotate(node);
    }
    // Right Right Case
    if (balance < -1 && i.low > node->right->i.low) {
        return leftRotate(node);
    }
    // Left Right Case
    if (balance > 1 && i.low > node->left->i.low) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    // Right Left Case
    if (balance < -1 && i.low < node->right->i.low) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    // If the node is balanced, return the node
    return node;
}


int main(){
    
    return 0;
}
