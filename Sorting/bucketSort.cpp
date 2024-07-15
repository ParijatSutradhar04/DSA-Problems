#include<bits/stdc++.h>
using namespace std;

class Node {
    public:
        float data;
        Node *next;
        Node () {
            this->data = 0;
            this->next = NULL;
        }

        Node(float data) {
            this->data = data;
            this->next = NULL;
        }

        void insert(float data) {
            Node *temp = this;
            while(temp->next != NULL) 
                temp = temp->next;
            temp->next = new Node(data);
        }

        // INSERTION SORT
        void sort() {
            Node *temp = this;
            while(temp != NULL) {
                Node *min = temp;
                Node *temp2 = temp->next;
                while(temp2 != NULL) {
                    if(temp2->data < min->data) 
                        min = temp2;
                    temp2 = temp2->next;
                }
                float t = temp->data;
                temp->data = min->data;
                min->data = t;
                temp = temp->next;
            }
        }

        void print() {
            Node *temp = this;
            while(temp != NULL) {
                cout << temp->data << " -> ";
                temp = temp->next;
            }
            cout << endl;
        }
};

void bucket_sort(float *arr, int n) {
    Node **bucket = new Node*[n]();

    for (int i = 0; i < n; i++) {
        int index = static_cast<int>(n * arr[i]);
        if (bucket[index] == nullptr) {
            bucket[index] = new Node(arr[i]);
        } else {
            bucket[index]->insert(arr[i]);
        }
    }

    for (int i = 0; i < n; i++) {
        if (bucket[i] != nullptr) {
            bucket[i]->sort();
        }
    }

    int index = 0;
    for (int i = 0; i < n; i++) {
        Node *temp = bucket[i];
        while (temp != nullptr) {
            arr[index++] = temp->data;
            temp = temp->next;
        }
        delete bucket[i];  // Delete each bucket after use
    }

    delete[] bucket;  // Delete the array of buckets
}

 
int main(){
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    float *arr = new float[n];
    cout << "Enter the elements: ";
    for(int i=0; i<n; i++) 
        cin >> arr[i];

    bucket_sort(arr, n);

    cout << "Sorted array: ";
    for(int i=0; i<n; i++) 
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
