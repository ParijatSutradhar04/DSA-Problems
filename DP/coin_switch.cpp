#include<bits/stdc++.h>
using namespace std;

int change(int* denomination, int n, int target) {
    int* dp = new int[target+1];
    dp[0] = 0;
    for (int i=1; i<=target; i++) {
        dp[i] = INT_MAX;
        for (int j=0; j<n; j++) {
            if (i-denomination[j] >= 0) {
                dp[i] = min(dp[i], dp[i-denomination[j]]+1);
            }
        }
    }
    return dp[target];
}

int main(){
    int n;
    cout << "Enter number of denominations: ";
    cin >> n;
    int* denomination = new int[n];
    cout << "Enter denominations: ";
    for (int i=0; i<n; i++) {
        cin >> denomination[i];
    }
    int target;
    cout << "Enter target: ";
    cin >> target;
    cout << "Minimum number of coins required: " << change(denomination, n, target) << endl;

    return 0;
}
