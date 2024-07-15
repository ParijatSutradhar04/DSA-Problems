#include<bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int data) {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    Node* insert(Node* root, int data) {
        if (root == NULL) {
            return new Node(data);
        }
        if (data < root->data) {
            root->left = insert(root->left, data);
        } else if (data > root->data) {
            root->right = insert(root->right, data);
        }
        return root;
    }

    void inOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        inOrder(root->left);
        cout << root->data << " ";
        inOrder(root->right);
    }

    void preOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        cout << root->data << " ";
        preOrder(root->left);
        preOrder(root->right);
    }

    bool search(Node* root, int data) {
        if (root == NULL) {
            return false;
        }
        if (root->data == data) {
            return true;
        }
        if (data < root->data) {
            return search(root->left, data);
        } else {
            return search(root->right, data);
        }
    } 

    Node* findMin(Node* root) {
        if (root == NULL) {
            cout << "Error: Tree is empty\n";
            return NULL;
        }
        while (root->left != NULL) {
            root = root->left;
        }
        return root;
    }

    Node* findMax(Node* root) {
        if (root == NULL) {
            cout << "Error: Tree is empty\n";
            return NULL;
        }
        while (root->right != NULL) {
            root = root->right;
        }
        return root;
    }

    int findHeight(Node* root) {
        if (root == NULL) {
            return -1;
        }
        return max(findHeight(root->left), findHeight(root->right)) + 1;
    }

    Node* deleteNode(Node* root, int data) {
        if (root == NULL) {
            return NULL;
        }
        if (root->data == data) {
            if (root->left == NULL && root->right == NULL) {
                delete root;
                return NULL;
            } else if (root->left == NULL) {
                Node* temp = root;
                root = root->right;
                delete temp;
                return root;
            } else if (root->right == NULL) {
                Node* temp = root;
                root = root->left;
                delete temp;
                return root;
            } else {
                int rightMin = findMin(root->right)->data;
                root->data = rightMin;
                root->right = deleteNode(root->right, rightMin);
                return root;
            }
        } else if (data < root->data) {
            root->left = deleteNode(root->left, data);
        } else {
            root->right = deleteNode(root->right, data);
        }
        return root;
    }

    Node* rotateRight(Node* root) {
        if (root == nullptr || root->left == nullptr) {
            return root;
        }
        Node* newRoot = root->left;
        root->left = newRoot->right;
        newRoot->right = root;
        return newRoot;
    }

    Node* rotateLeft(Node* root) {
        if (root == nullptr || root->right == nullptr) {
            return root;
        }
        Node* newRoot = root->right;
        root->right = newRoot->left;
        newRoot->left = root;
        return newRoot;
    }

    Node* changeRoot(Node* root, int key) {
        if (root == nullptr) {
            return nullptr;
        }
        if (root->data == key) {
            return root;
        }
        if (key < root->data) {
            root->left = changeRoot(root->left, key);
            return rotateRight(root);
        } else {
            root->right = changeRoot(root->right, key);
            return rotateLeft(root);
        }
    }

    Node* successor(Node* root) {
        if (root == NULL) {
            return NULL;
        }
        if (root->right != NULL) {
            return findMin(root->right);
        }
        Node* current = root;
        while (current->left != NULL) {
            current = current->left;
        }
        return current;
    }

    Node* predecessor(Node* root) {
        if (root == NULL) {
            return NULL;
        }
        if (root->left != NULL) {
            return findMax(root->left);
        }
        Node* current = root;
        while (current->right != NULL) {
            current = current->right;
        }
        return current;
    }
};
 
int main(){
    Node* root = NULL;
    BST bst;
    root = bst.insert(root, 15);
    root = bst.insert(root, 10);
    root = bst.insert(root, 20);
    root = bst.insert(root, 25);
    root = bst.insert(root, 8);
    root = bst.insert(root, 12);
    
    cout << "Inorder: ";
    bst.inOrder(root);
    cout << endl;
    cout << "Preorder: ";
    bst.preOrder(root);
    cout << endl;

    cout << "Search 10: " << bst.search(root, 10) << endl;
    cout << "Search 25: " << bst.search(root, 25) << endl;
    cout << "Search 13: " << bst.search(root, 13) << endl;

    cout << "Min: " << bst.findMin(root) << endl;
    cout << "Max: " << bst.findMax(root) << endl;
    cout << "Height: " << bst.findHeight(root) << endl;

    root = bst.deleteNode(root, 10);
    cout << "Inorder: ";
    bst.inOrder(root);
    cout << endl;
    cout << "Preorder: ";
    bst.preOrder(root);
    cout << endl;

    root = bst.changeRoot(root, 20);
    cout << "Inorder: ";
    bst.inOrder(root);
    cout << endl;
    cout << "Preorder: ";
    bst.preOrder(root);
    cout << endl;
    
    return 0;
}
