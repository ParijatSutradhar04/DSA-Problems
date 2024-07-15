#include <iostream>
#include <queue>
#include <cmath> // for abs function
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

class BinaryTree {
public:
    // Build a binary tree from an array of pre-order traversal
    Node* buildTree(int *keys, int &index) {
        index++;
        if (keys[index] == -1) {
            return NULL;
        }
        Node* newNode = new Node(keys[index]);
        newNode->left = buildTree(keys, index);
        newNode->right = buildTree(keys, index);
        return newNode;
    }

    Node* buildTreeLevelOrder(int *keys, int n) {
        Node* root = new Node(keys[0]);
        queue<Node*> q;
        q.push(root);
        int i = 1;
        while (!q.empty() && i < n) {
            Node* temp = q.front();
            q.pop();
            if (keys[i] != -1) {
                temp->left = new Node(keys[i]);
                q.push(temp->left);
            }
            i++;
            if (i < n && keys[i] != -1) {
                temp->right = new Node(keys[i]);
                q.push(temp->right);
            }
            i++;
        }
        return root;
    }

    void deleteTree(Node* root) {
        if (root == NULL) {
            return;
        }
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
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

    void postOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        postOrder(root->left);
        postOrder(root->right);
        cout << root->data << " ";
    }

    void levelOrder(Node* root) {
        if (root == NULL) {
            return;
        }
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            Node* temp = q.front();
            q.pop();
            cout << temp->data << " ";
            if (temp->left != NULL) {
                q.push(temp->left);
            }
            if (temp->right != NULL) {
                q.push(temp->right);
            }
        }
    }

    int height(Node* root) {
        if (root == NULL) {
            return -1;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return max(leftHeight, rightHeight) + 1;
    }

    int diameter(Node* root) {
        if (root == NULL) {
            return 0;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        int leftDiameter = diameter(root->left);
        int rightDiameter = diameter(root->right);
        return max(leftHeight + rightHeight + 1, max(leftDiameter, rightDiameter));
    }

    bool isBalanced(Node* root) {
        if (root == NULL) {
            return true;
        }
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (abs(leftHeight - rightHeight) <= 1 && isBalanced(root->left) && isBalanced(root->right)) {
            return true;
        }
        return false;
    }

    void printLeafNodes(Node* root) {
        if (root == NULL) {
            return;
        }
        if (root->left == NULL && root->right == NULL) {
            cout << root->data << " ";
        }
        printLeafNodes(root->left);
        printLeafNodes(root->right);
    }

    void printLeftBoundary(Node* root) {
        if (root == NULL) {
            return;
        }
        if (root->left != NULL) {
            cout << root->data << " ";
            printLeftBoundary(root->left);
        }
        else if (root->right != NULL) {
            cout << root->data << " ";
            printLeftBoundary(root->right);
        }
    }

    void printRightBoundary(Node* root) {
        if (root == NULL) {
            return;
        }
        if (root->right != NULL) {
            printRightBoundary(root->right);
            cout << root->data << " ";
        }
        else if (root->left != NULL) {
            printRightBoundary(root->left);
            cout << root->data << " ";
        }
    }

    void printBoundary(Node* root) {
        if (root == NULL) {
            return;
        }
        cout << root->data << " ";
        printLeftBoundary(root->left);
        printLeafNodes(root->left);
        printLeafNodes(root->right);
        printRightBoundary(root->right);
    }

    bool isIdentical(Node* root1, Node* root2) {
        if (root1 == NULL && root2 == NULL) {
            return true;
        }
        if (root1 == NULL || root2 == NULL) {
            return false;
        }
        return (root1->data == root2->data && isIdentical(root1->left, root2->left) && isIdentical(root1->right, root2->right));
    }

    bool isSubTree(Node* root1, Node* root2) {
        if (root2 == NULL) {
            return true;
        }
        if (root1 == NULL) {
            return false;
        }
        if (isIdentical(root1, root2)) {
            return true;
        }
        return isSubTree(root1->left, root2) || isSubTree(root1->right, root2);
    }

    bool bstSearch(Node* root, int key) {
        if (root == NULL) {
            return false;
        }
        if (root->data == key) {
            return true;
        }
        if (root->data > key) {
            return bstSearch(root->left, key);
        }
        return bstSearch(root->right, key);
    }
};

int main() {
    BinaryTree tree;
    int keys[] = {1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, -1, 7, -1, -1};
    int index = -1;
    Node* root = tree.buildTree(keys, index);

    cout << "Inorder: " << endl;
    tree.inOrder(root);
    cout << endl;
    cout << "Preorder: " << endl;
    tree.preOrder(root);
    cout << endl;
    cout << "Postorder: " << endl;
    tree.postOrder(root);
    cout << endl;
    cout << "Levelorder: " << endl;
    tree.levelOrder(root);
    cout << endl;
    cout << "Height: " << tree.height(root) << endl;
    cout << "Diameter: " << tree.diameter(root) << endl;
    cout << "isBalanced: " << tree.isBalanced(root) << endl;
    cout << "Bondary: ";
    tree.printBoundary(root);
    cout << endl;

    int keys2[] = {1, 2, 4, -1, -1, 5, -1, -1, 3, 6, -1, -1, 7, -1, -1};
    int index2 = -1;
    Node* root2 = tree.buildTree(keys2, index2);

    cout << "isIdentical: " << tree.isIdentical(root, root2) << endl;
    cout << "isSubTree: " << tree.isSubTree(root, root2) << endl;
    cout << "BST Search: " << tree.bstSearch(root, 5) << endl;

    tree.deleteTree(root);
    tree.deleteTree(root2);

    return 0;
}
    

