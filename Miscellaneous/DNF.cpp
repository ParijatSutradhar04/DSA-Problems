#include<bits/stdc++.h>
using namespace std;

void DNF(int* arr, int n) {
    int low = 0, mid = 0, high = n-1;
    // 0 to low-1 -> 0
    // low to mid-1 -> 1
    // mid to high -> unknown
    // high+1 to n-1 -> 2
    while(mid <= high) {
        if (arr[mid] == 0) {
            swap(arr[low], arr[mid]);
            low++;
            mid++;
        }
        else if (arr[mid] == 1) {
            mid++;
        }
        else {
            swap(arr[mid], arr[high]);
            high--;
        }
    }
}
 
int main(){
    int arr[] = {1, 0, 2, 1, 0, 1, 2, 1, 2};
    int n = sizeof(arr)/sizeof(arr[0]);
    DNF(arr, n);
    for(int i=0; i<n; i++) {
        cout << arr[i] << " ";
    }
    
    return 0;
}
