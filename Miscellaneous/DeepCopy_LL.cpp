#include<bits/stdc++.h>
using namespace std;

class Node{
    public:
    int data;
    Node* next;
    Node* arb;
    Node(int data){
        this->data = data;
        this->next = NULL;
        this->arb = NULL;
    }

    Node* insert(Node* head, int data){
        Node* temp = new Node(data);
        if(head == NULL){
            head = temp;
        }else{
            Node* temp1 = head;
            while(temp1->next != NULL){
                temp1 = temp1->next;
            }
            temp1->next = temp;
        }
        return head;
    }

    Node* insertRandom(Node* head, int data, int randomData) {
        Node* left = head;
        Node* right = head;
        while (left) {
            if (left->data == data) {
                break;
            }
            left = left->next;
        }
        while (right) {
            if (right->data == randomData) {
                break;
            }
            right = right->next;
        }
        left->arb = right;
        return head;
    }

    void print(Node* head){
        Node* temp = head;
        while(temp != NULL){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
};

Node* deepCopy(Node* head) {
    if (head == NULL) return NULL;
    if (head->next == NULL && head->arb == NULL) return new Node(head->data);
    
    Node *newNode = head;
    while(newNode) {
        Node *curr = new Node(newNode->data);
        Node *temp = newNode->next;
        newNode->next = curr;
        curr->next = temp;
        newNode = temp;
    }
    
    newNode = head;
    Node* newHead = head->next;
    while(newNode->next->next) {
        Node *temp = newNode->next->next;
        newNode->next->next = newNode->next->next->next;
        if (newNode->arb) {
            newNode->next->arb = newNode->arb->next;
        }
        else {
            newNode->next->arb = NULL;
        }
        
        newNode->next = temp;
        newNode = temp;
    }
    
    if (newNode->arb) {
        newNode->next->arb = newNode->arb->next;
    }
    else {
        newNode->next->arb = NULL;
    }
    
    newNode->next = NULL;
    
    return newHead;
}
 
int main(){
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;
    Node* head = NULL;
    while(n--) {
        int data;
        cout << "Enter the data: ";
        cin >> data;
        head = head->insert(head, data);
    }
    cout << "Enter number of random connections: ";
    cin >> n;
    while(n--) {
        int data, randomData;
        cout << "Enter the data and random data: ";
        cin >> data >> randomData;
        head = head->insertRandom(head, data, randomData);
    }
    head->print(head);
    Node* newHead = deepCopy(head);
    newHead->print(newHead);
    
    return 0;
}
