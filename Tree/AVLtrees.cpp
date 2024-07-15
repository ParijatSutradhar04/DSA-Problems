#include <iostream>

using namespace std;

typedef int keyTyp;

class AVLnode {
public:
    keyTyp key;
    AVLnode *lChild, *rChild;
    int height;

    AVLnode(keyTyp _key) : key(_key), lChild(nullptr), rChild(nullptr), height(0) {}
};

class AVLTree {
public:
    AVLnode *root;

    AVLTree() : root(nullptr) {}

    AVLnode* search(AVLnode *root, keyTyp key) {
        if (root == nullptr || root->key == key) {
            return root;
        }
        if (key < root->key) {
            return search(root->lChild, key);
        }
        return search(root->rChild, key);
    }

    AVLnode* insert(AVLnode *root, keyTyp key) {
        if (root == nullptr) {
            root = new AVLnode(key);
            return root;
        }

        if (root->key == key) {
            return root;
        }

        if (key < root->key) {
            root->lChild = insert(root->lChild, key);
        } else {
            root->rChild = insert(root->rChild, key);
        }

        root->height = 1 + max(height(root->lChild), height(root->rChild));
        root = balance(root);

        return root;
    }

    AVLnode* del(AVLnode *root, keyTyp key) {
        if (root == nullptr) {
            return root;
        }
        if (key < root->key) {
            root->lChild = del(root->lChild, key);
        } else if (key > root->key) {
            root->rChild = del(root->rChild, key);
        } else {
            if (root->lChild == nullptr || root->rChild == nullptr) {
                AVLnode *temp = (root->lChild != nullptr) ? root->lChild : root->rChild;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                }
                delete temp;
            } else {
                AVLnode *temp = root->rChild;
                while (temp->lChild != nullptr) {
                    temp = temp->lChild;
                }
                root->key = temp->key;
                root->rChild = del(root->rChild, temp->key);
            }
        }

        if (root != nullptr) {
            root->height = 1 + max(height(root->lChild), height(root->rChild));
            root = balance(root);
        }
        return root;
    }

    AVLnode* rotateLeft(AVLnode *root) {
        if (root == nullptr || root->rChild == nullptr) {
            return root;
        }
        AVLnode *newRoot = root->rChild;
        root->rChild = newRoot->lChild;
        newRoot->lChild = root;
        root->height = 1 + max(height(root->lChild), height(root->rChild));
        newRoot->height = 1 + max(height(newRoot->lChild), height(newRoot->rChild));
        return newRoot;
    }

    AVLnode* rotateRight(AVLnode *root) {
        if (root == nullptr || root->lChild == nullptr) {
            return root;
        }
        AVLnode *newRoot = root->lChild;
        root->lChild = newRoot->rChild;
        newRoot->rChild = root;
        root->height = 1 + max(height(root->lChild), height(root->rChild));
        newRoot->height = 1 + max(height(newRoot->lChild), height(newRoot->rChild));
        return newRoot;
    }

    AVLnode* balance(AVLnode *root) {
        if (root == nullptr) {
            return root;
        }
        int balance = height(root->lChild) - height(root->rChild);
        if (balance > 1) {
            if (height(root->lChild->lChild) >= height(root->lChild->rChild)) {
                return rotateRight(root);
            } else {
                root->lChild = rotateLeft(root->lChild);
                return rotateRight(root);
            }
        }
        if (balance < -1) {
            if (height(root->rChild->rChild) >= height(root->rChild->lChild)) {
                return rotateLeft(root);
            } else {
                root->rChild = rotateRight(root->rChild);
                return rotateLeft(root);
            }
        }
        return root;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(AVLnode *node) {
        if (node == nullptr)
            return -1;
        return node->height;
    }

    void inOrder(AVLnode *root) {
        if (root != nullptr) {
            inOrder(root->lChild);
            cout << root->key << " ";
            inOrder(root->rChild);
        }
    }

    void preOrder(AVLnode *root) {
        if (root != nullptr) {
            cout << root->key << " ";
            preOrder(root->lChild);
            preOrder(root->rChild);
        }
    }
};

int main() {
    AVLTree tree;
    tree.root = tree.insert(tree.root, 10);
    tree.root = tree.insert(tree.root, 20);
    tree.root = tree.insert(tree.root, 30);
    tree.root = tree.insert(tree.root, 40);
    tree.root = tree.insert(tree.root, 50);
    tree.root = tree.insert(tree.root, 32);
    tree.root = tree.insert(tree.root, 34);
    tree.root = tree.insert(tree.root, 36);

    // cout << "Inorder: ";
    // tree.inOrder(tree.root);
    // cout << endl;
    cout << "Preorder: ";
    tree.preOrder(tree.root);
    cout << endl;

    // tree.root = tree.del(tree.root, 5);
    // cout << "Inorder: ";
    // tree.inOrder(tree.root);
    // cout << endl;
    // cout << "Preorder: ";
    // tree.preOrder(tree.root);
    // cout << endl;

    // AVLnode *temp = tree.search(tree.root, 25);
    // if (temp != nullptr) {
    //     cout << "25 Found\n";
    // }


    
    return 0;
}
