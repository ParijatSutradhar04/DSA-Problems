#include<bits/stdc++.h>
using namespace std;

bool subsetSum(int *arr, int n, int sum) {
    bool dp[n+1][sum+1];
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=sum; j++) {
            if (i == 0) {
                dp[i][j] = false;
            }
            if (j == 0) {
                dp[i][j] = true;
            }
            else if (arr[i-1] <= j) {
                dp[i][j] = dp[i-1][j-arr[i-1]] || dp[i-1][j];
            }
            else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][sum];
}

// Space optimized version
bool subsetSum_opt(int *arr, int n, int sum) {
    bool dp[sum+1] = {false};
    dp[0] = true;
    for (int i=1; i<=n; i++) {
        for (int j=sum; j>=0; j--) {
            if (arr[i-1] <= j) {
                dp[j] = dp[j-arr[i-1]] || dp[j];
            }
        }
    }
    return dp[sum];
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

    int sum;
    cout << "Enter the sum: ";
    cin >> sum;

    cout << "Using DP with tabulation: " << endl;
    if (subsetSum(arr, n, sum)) {
        cout << "Subset with the given sum exists." << endl;
    } else {
        cout << "Subset with the given sum does not exist." << endl;
    }

    cout << "Using DP with tabulation and space optimization with a single array: " << endl;
    if (subsetSum_opt(arr, n, sum)) {
        cout << "Subset with the given sum exists." << endl;
    } else {
        cout << "Subset with the given sum does not exist." << endl;
    }
    
    return 0;
}
