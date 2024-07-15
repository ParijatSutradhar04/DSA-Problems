// https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* left;
    Node* right;
    Node* parent;
    char color;
};

Node* leftRotate(Node* root, Node* x){
    Node* y = x->right;
    x->right = y->left;
    if(x->right != NULL){
        x->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL){
        root = y;
    }
    else if(x == x->parent->left){
        x->parent->left = y;
    }
    else{
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
    return root;
}

Node* rightRotate(Node* root, Node* y){
    Node* x = y->left;
    y->left = x->right;
    if(y->left != NULL){
        y->left->parent = y;
    }
    x->parent = y->parent;
    if(y->parent == NULL){
        root = x;
    }
    else if(y == y->parent->left){
        y->parent->left = x;
    }
    else{
        y->parent->right = x;
    }
    x->right = y;
    y->parent = x;
    return root;
}

Node* insertFixUP(Node* root, Node* pt){
    Node* parent_pt = NULL;
    Node* grand_parent_pt = NULL;
    
    while((pt != root) && (pt->color != 'b') && (pt->parent->color == 'r')){
        parent_pt = pt->parent;
        grand_parent_pt = pt->parent->parent;
        
        if(parent_pt == grand_parent_pt->left){
            Node* uncle_pt = grand_parent_pt->right;
            
            if(uncle_pt != NULL && uncle_pt->color == 'r'){
                grand_parent_pt->color = 'r';
                parent_pt->color = 'b';
                uncle_pt->color = 'b';
                pt = grand_parent_pt;
            }
            else{
                if(pt == parent_pt->right){
                    root = leftRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                root = rightRotate(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
        else{
            Node* uncle_pt = grand_parent_pt->left;
            
            if(uncle_pt != NULL && uncle_pt->color == 'r'){
                grand_parent_pt->color = 'r';
                parent_pt->color = 'b';
                uncle_pt->color = 'b';
                pt = grand_parent_pt;
            }
            else{
                if(pt == parent_pt->left){
                    root = rightRotate(root, parent_pt);
                    pt = parent_pt;
                    parent_pt = pt->parent;
                }
                root = leftRotate(root, grand_parent_pt);
                swap(parent_pt->color, grand_parent_pt->color);
                pt = parent_pt;
            }
        }
    }
    root->color = 'b';
    return root;
}

Node* insert(Node* root, int data){
    Node* pt = new Node;
    pt->parent = NULL;
    pt->data = data;
    pt->left = NULL;
    pt->right = NULL;
    pt->color = 'r';
    
    Node* x = root;
    Node* y = NULL;
    
    while(x != NULL){
        y = x;
        if(pt->data < x->data){
            x = x->left;
        }
        else{
            x = x->right;
        }
    }
    pt->parent = y;
    if(y == NULL){
        root = pt;
    }
    else if(pt->data < y->data){
        y->left = pt;
    }
    else{
        y->right = pt;
    }
    return insertFixUP(root, pt);
}

Node* deleteFixUP(Node* root, Node* node){
    if(node == NULL){
        return root;
    }
    if(node == root){
        return root;
    }
    if(node->color == 'r' || node->left != NULL || node->right != NULL){
        return root;
    }
    Node* sibling = NULL;
    Node* parent = NULL;
    Node* pt = node;
    char color;
    while(pt != root && pt->color == 'b'){
        parent = pt->parent;
        if (parent == NULL) {
            break;
        }
        if(pt == parent->left){
            sibling = parent->right;
            if(sibling != NULL){
                if(sibling->color == 'r'){
                    sibling->color = 'b';
                    parent->color = 'r';
                    root = leftRotate(root, parent);
                    sibling = parent->right;
                }
                if(sibling->left != NULL && sibling->right != NULL){
                    if(sibling->left->color == 'b' && sibling->right->color == 'b'){
                        sibling->color = 'r';
                        pt = parent;
                    }
                    else{
                        if(sibling->right != NULL && sibling->right->color == 'b'){
                            sibling->left->color = 'b';
                            sibling->color = 'r';
                            root = rightRotate(root, sibling);
                            sibling = parent->right;
                        }
                        sibling->color = parent->color;
                        parent->color = 'b';
                        sibling->right->color = 'b';
                        root = leftRotate(root, parent);
                        pt = root;
                    }
                }
            }
        }
        else{
            sibling = parent->left;
            if(sibling != NULL){
                if(sibling->color == 'r'){
                    sibling->color = 'b';
                    parent->color = 'r';
                    root = rightRotate(root, parent);
                    sibling = parent->left;
                }
                if(sibling->left != NULL && sibling->right != NULL){
                    if(sibling->right->color == 'b' && sibling->left->color == 'b'){
                        sibling->color = 'r';
                        pt = parent;
                    }
                    else{
                        if(sibling->left != NULL && sibling->left->color == 'b'){
                            sibling->right->color = 'b';
                            sibling->color = 'r';
                            root = leftRotate(root, sibling);
                            sibling = parent->left;
                        }
                        sibling->color = parent->color;
                        parent->color = 'b';
                        sibling->left->color = 'b';
                        root = rightRotate(root, parent);
                        pt = root;
                    }
                }
            }
        }
    }
    pt->color = 'b';
    return root;
}

Node* deleteNode(Node* root, int data){
    Node* pt = root;
    Node* parent = NULL;
    Node* node = NULL;
    while(pt != NULL){
        if(pt->data == data){
            node = pt;
            break;
        }
        if(pt->data <= data){
            pt = pt->right;
        }
        else{
            pt = pt->left;
        }
    }
    if(node == NULL){
        return root;
    }
    Node* y = node;
    char y_original_color = y->color;
    if(node->left == NULL){
        Node* x = node->right;
        root = deleteFixUP(root, node);
        if(node == root){
            root = x;
        }
        else if(node->parent != NULL && node == node->parent->left){
            node->parent->left = x;
        }
        else if(node->parent != NULL){
            node->parent->right = x;
        }
        if(x != NULL){
            x->parent = node->parent;
        }
        delete node;
    }
    else if(node->right == NULL){
        Node* x = node->left;
        root = deleteFixUP(root, node);
        if(node == root){
            root = x;
        }
        else if(node->parent != NULL && node == node->parent->left){
            node->parent->left = x;
        }
        else if(node->parent != NULL){
            node->parent->right = x;
        }
        if(x != NULL){
            x->parent = node->parent;
        }
        delete node;
    }
    else{
        y = node->right;
        while(y->left != NULL){
            y = y->left;
        }
        y_original_color = y->color;
        Node* x = y->right;
        if(y->parent == node){
            if(x != NULL){
                x->parent = y;
            }
        }
        else{
            root = deleteFixUP(root, y);
            if(y == root){
                root = x;
            }
            else if(y->parent != NULL && y == y->parent->left){
                y->parent->left = x;
            }
            else if(y->parent != NULL){
                y->parent->right = x;
            }
            if(x != NULL){
                x->parent = y->parent;
            }
            y->right = node->right;
            y->right->parent = y;
        }
        root = deleteFixUP(root, node);
        if(node == root){
            root = y;
        }
        else if(node->parent != NULL && node == node->parent->left){
            node->parent->left = y;
        }
        else if(node->parent != NULL){
            node->parent->right = y;
        }
        y->parent = node->parent;
        y->left = node->left;
        y->left->parent = y;
        y->color = node->color;
        delete node;
    }
    if(y_original_color == 'b'){
        root = deleteFixUP(root, y);
    }
    return root;
}

Node* buildRBTree(int* arr, int n){
    Node* root = NULL;
    for(int i = 0; i < n; i++){
        root = insert(root, arr[i]);
    }
    return root;
}

void inOrder(Node* root){
    if(root == NULL){
        return;
    }
    inOrder(root->left);
    cout << root->data;
    if (root->color == 'r') {
        cout << "R  ";
    }
    else{
        cout << "B  ";
    }
    inOrder(root->right);
}

void preOrder(Node* root){
    if(root == NULL){
        return;
    }
    cout << root->data;
    if (root->color == 'r') {
        cout << "R  ";
    }
    else{
        cout << "B  ";
    }
    preOrder(root->left);
    preOrder(root->right);
}

void search(Node* root, int data){
    Node* pt = root;
    while(pt != NULL){
        if(pt->data == data){
            cout << "Element found" << endl;
            return;
        }
        if(pt->data < data){
            pt = pt->right;
        }
        else{
            pt = pt->left;
        }
    }
    cout << "Element not found" << endl;
}

int bh(Node* root){
    if(root == NULL){
        return 1;
    }
    int l = bh(root->left);
    int r = bh(root->right);
    if(l != r){
        cout << "Black height not same" << endl;
    }
    if(root->color == 'b'){
        return l + 1;
    }
    else{
        return l;
    }
}

int minimum(Node* root){
    while(root->left != NULL){
        root = root->left;
    }
    return root->data;
}

int maximum(Node* root){
    while(root->right != NULL){
        root = root->right;
    }
    return root->data;
}

int predecessor(Node* root, int data){
    Node* pt = root;
    Node* pre = NULL;
    while(pt != NULL){
        if(pt->data == data){
            if(pt->left != NULL){
                return maximum(pt->left);
            }
            else{
                while(root != NULL){
                    if(pt->data > root->data){
                        pre = root;
                        root = root->right;
                    }
                    else if(pt->data < root->data){
                        root = root->left;
                    }
                    else{
                        break;
                    }
                }
                return pre->data;
            }
        }
        if(pt->data < data){
            pre = pt;
            pt = pt->right;
        }
        else{
            pt = pt->left;
        }
    }
    return -1;
}

int successor(Node* root, int data){
    Node* pt = root;
    Node* suc = NULL;
    while(pt != NULL){
        if(pt->data == data){
            if(pt->right != NULL){
                return minimum(pt->right);
            }
            else{
                while(root != NULL){
                    if(pt->data < root->data){
                        suc = root;
                        root = root->left;
                    }
                    else if(pt->data > root->data){
                        root = root->right;
                    }
                    else{
                        break;
                    }
                }
                return suc->data;
            }
        }
        if(pt->data < data){
            pt = pt->right;
        }
        else{
            suc = pt;
            pt = pt->left;
        }
    }
    return -1;
}

int main(){
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    int* arr = new int[n];
    cout << "Enter the elements: ";
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    Node* root = buildRBTree(arr, n);
    cout << "Inorder Traversal: ";
    inOrder(root);
    cout << endl;
    cout << "Preorder Traversal: ";
    preOrder(root);
    cout << endl;

    cout << "Enter the element to be deleted: ";
    int data;
    cin >> data;
    root = deleteNode(root, data);
    cout << "Inorder Traversal: ";
    inOrder(root);
    cout << endl;
    cout << "Preorder Traversal: ";
    preOrder(root);
    cout << endl;

    return 0;
}   