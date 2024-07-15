#include<bits/stdc++.h>
using namespace std;

// Heapify function to maintain the max-heap property
void heapify(int *arr, int n, int i) {
    int largest = i;
    int left = 2*i+1;
    int right = 2*i+2;
    if(left<n && arr[left]>arr[largest]) {
        largest = left;
    }
    if(right<n && arr[right]>arr[largest]) {
        largest = right;
    }
    if(largest!=i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// Build-Max-Heap function to build a max-heap from an array
void buildMaxHeap(int *arr, int n) {
    for(int i = n/2-1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

void heapSort(int *arr, int n) {
    buildMaxHeap(arr, n);
    for(int i = n-1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
 
int main(){
    int n;
    cout<<"Enter the number of elements: ";
    cin>>n;
    int arr[n];
    int arr2[n];
    cout<<"Enter the elements: ";
    for(int i=0;i<n;i++){
        cin>>arr[i];
        arr2[i] = arr[i];
    }

    buildMaxHeap(arr, n);

    cout<<"The heap after BUILT-MAX-HEAP operation is: ";
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;

    heapSort(arr2, n);
    cout << "The heap after HEAP-SORT operation is: ";
    for(int i=0;i<n;i++){
        cout<<arr2[i]<<" ";
    }

    return 0;
}
