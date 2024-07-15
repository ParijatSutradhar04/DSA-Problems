#include<bits/stdc++.h>
using namespace std;

int longestIncreasingSubsequence(int *arr, int n) {
    int dp[n] = {1};
    for (int i=1; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (arr[i] > arr[j]) {
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
    }
    return *max_element(dp, dp+n);
}

int main(){
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    cout << "Enter the elements: ";
    int *arr = new int[n];
    for (int i=0; i<n; i++) {
        cin >> arr[i];
    }

    cout << "Length of the longest increasing subsequence: " << longestIncreasingSubsequence(arr, n) << endl;
    
    return 0;
}
