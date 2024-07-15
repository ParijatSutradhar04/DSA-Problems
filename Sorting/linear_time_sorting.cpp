#include<bits/stdc++.h>
using namespace std;

// Counting Sort
// Time Complexity: O(n+k), where k is the range of the non-negative key values and n is the number of elements in the input
void counting_sort(int *arr, int n, int k) {
    int *count = new int[k+1];
    int *output = new int[n];
    // Makinnig the count array takes O(k) time
    for(int i=0; i<=k; i++) 
        count[i] = 0;
    for(int i=0; i<n; i++) 
        count[arr[i]]++;
    for(int i=1; i<=k; i++) 
        count[i] += count[i-1];

    // Making the output array takes O(n) time
    for(int i=n-1; i>=0; i--) { // reverse loop to maintain stability
        output[count[arr[i]]-1] = arr[i];
        count[arr[i]]--;
    }
    for(int i=0; i<n; i++) 
        arr[i] = output[i];
    
    delete [] count;
    delete [] output;
}

// Radix Sort
// Time Complexity: O(d*(n+b)), where d is the number of digits in the maximum number, n is the number of elements in the input array and b is the base of the number system
void radix_sort(int *arr, int n, int d) {
    int *output = new int[n];
    
    for(int i=0; i<d; i++) {
        int *count = new int[10];

        for(int j=0; j<10; j++) 
            count[j] = 0;

        for(int j=0; j<n; j++) 
            count[(arr[j]/(int)pow(10,i))%10]++;

        for(int j=1; j<10; j++) 
            count[j] += count[j-1];

        for(int j=n-1; j>=0; j--) {
            output[count[(arr[j]/(int)pow(10,i))%10]-1] = arr[j];
            count[(arr[j]/(int)pow(10,i))%10]--;
        }

        for(int j=0; j<n; j++) 
            arr[j] = output[j];

        delete [] count;
    }

    delete [] output;
}

// Bucket Sort
// Time Complexity: O(n^2), where n is the number of elements in the input array
void bucket_sort(float *arr, int n) {
    vector<float> *bucket = new vector<float>[n];
    for(int i=0; i<n; i++) {
        int index = n*arr[i];
        bucket[index].push_back(arr[i]);
    }

    for(int i=0; i<n; i++) 
        sort(bucket[i].begin(), bucket[i].end()); // can use any sorting algo

    int index = 0;
    for(int i=0; i<n; i++) {
        for(int j=0; j<bucket[i].size(); j++) 
            arr[index++] = bucket[i][j];
    }

    delete [] bucket;
}
 
int main(){
    int n;
    cout << "Enter the number of elements: ";
    cin>>n;
    int *arr = new int[n];
    cout << "Enter the elements: ";
    for(int i=0; i<n; i++) 
        cin>>arr[i];
    
    cout << "Counting Sort: " << endl;
    int k;
    cout << "Enter the range of the non-negative key values: ";
    cin>>k;

    counting_sort(arr, n, k);
    cout << "After Counting Sort: ";
    for(int i=0; i<n; i++) 
        cout << arr[i] << " ";
    cout << endl;

    
    return 0;
}
