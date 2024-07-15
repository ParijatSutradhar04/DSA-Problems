// Given an array of size n, find the majority element. The majority element is the element that appears more than n/2 times.

#include<bits/stdc++.h>
using namespace std;

int majorityElement(int* arr, int n) {
    int count = 0, candi = -1;
    for(int i = 0; i < n; i++) {
        if (count == 0) {
            candi = arr[i];
            count++;
        } else if (arr[i] == candi) {
            count++;
        } else {
            count--;
        }
    }
    // candi stores the element that occurs maximum number of times
    count = 0;
    for(int i = 0; i < n; i++) {
        if (arr[i] == candi) {
            count++;
        }
    }
    return count > n/2 ? candi : -1;
}
 
int main(){
    int n;
    cout << "ENter the size of the array: ";
    cin >> n;
    int* arr = new int[n];
    cout << "Enter the elements of the array: ";
    for(int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << majorityElement(arr, n) << endl;
    
    return 0;
}
