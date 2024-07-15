#include<bits/stdc++.h>
using namespace std;

// Brute force method: O(2^n)
int knapsack_bf(int *weights, int *values, int n, int w) {
    if (n == 0 || w == 0) {
        return 0;
    }

    if (weights[n-1] > w) {
        return knapsack_bf(weights, values, n-1, w);
    } else {
        return max(values[n-1] + knapsack_bf(weights, values, n-1, w-weights[n-1]), knapsack_bf(weights, values, n-1, w));
    }
}

// DP with memoization (Top-down): O(n*w)
int knapsack_memo(int *weights, int *values, int n, int w, int **dp) {
    if (n == 0 || w == 0) {
        return 0;
    }

    if (dp[n][w] != -1) {
        return dp[n][w];
    }

    if (weights[n-1] > w) {
        dp[n][w] = knapsack_memo(weights, values, n-1, w, dp);
    } else {
        dp[n][w] = max(values[n-1] + knapsack_memo(weights, values, n-1, w-weights[n-1], dp), knapsack_memo(weights, values, n-1, w, dp));
    }

    return dp[n][w];
}

// DP with tabulation (Bottom-up): O(n*w)
int knapsack_tab(int *weights, int *values, int n, int w) {
    int dp[n+1][w+1] = {{-1}};
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= w; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            }
            else if (weights[i-1] <= j) {
                dp[i][j] = max(values[i-1] + dp[i-1][j-weights[i-1]], dp[i-1][j]);
            }
            else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    return dp[n][w];
}

// Dynamic programming method (tabulation): O(n*w)
vector<int> knapsack_items(int *weights, int *values, int n, int w) {
    int dp[n+1][w+1] = {{-1}};
    for (int i=0; i<=n; i++) {
        for (int j=0; j<=w; j++) {
            if (i == 0 || j == 0) {
                dp[i][j] = 0;
            } else if (weights[i-1] <= j) {
                dp[i][j] = max(values[i-1] + dp[i-1][j-weights[i-1]], dp[i-1][j]);
            } else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    // Retracing the DP matrix to get the items that have been selected
    vector<int> res;
    int i = n, j = w;
    while (i > 0 && j > 0) {
        if (dp[i][j] == dp[i-1][j]) {
            i--;
        } else {
            res.push_back(i-1);
            j -= weights[i-1];
            i--;
        }
    }

    return res;
}

// DP with tabulation with space optimization: O(n*w)
int knapsack_tab_opt(int *weights, int *values, int n, int w) {
    vector<int> prev(w+1, 0);
    vector<int> curr(w+1, 0);

    for (int i=1; i<=n; i++) {
        for (int j=0; j <= w; j++) {
            if (weights[i-1] <= j) {
                curr[j] = max(values[i-1] + prev[j - weights[i-1]], prev[j]);
            }
            else {
                curr[j] = prev[j];
            }
        }
        prev = curr;
    }
    return curr[w];
}

// DP with tabulation using single array (space optimized): O(n*w)
int knapsack_tab_1D(int *weights, int *values, int n, int w) {
    vector<int> dp(w+1, 0);
    for (int i=1; i<=n; i++) {
        for (int j=w; j>=0; j--) {
            if (weights[i-1] <= j) {
                dp[j] = max(values[i-1] + dp[j - weights[i-1]], dp[j]);
            }
        }
    }
    return dp[w];
}
 
int main(){
    int n, w;
    cout << "Enter the number of items and the maximum weight: ";
    cin >> n >> w;
    
    cout << "Enter the weights of the items: ";
    int *weights = new int[n];
    for (int i=0; i<n; i++) {
        cin >> weights[i];
    }

    cout << "Enter the values of the items: ";
    int *values = new int[n];
    for (int i=0; i<n; i++) {
        cin >> values[i];
    }

    cout << "Brute force method: " << knapsack_bf(weights, values, n, w) << endl;

    int **dp = new int*[n+1];
    for (int i=0; i<=n; i++) {
        dp[i] = new int[w+1];
        for (int j=0; j<=w; j++) {
            dp[i][j] = -1;
        }
    }
    cout << "DP with memoization (Top-down): " << knapsack_memo(weights, values, n, w, dp) << endl;

    cout << "DP with tabulation (Bottom-up): " << knapsack_tab(weights, values, n, w) << endl;
    
    vector<int> items = knapsack_items(weights, values, n, w);
    cout << "Items selected: ";
    for (auto i : items) {
        cout << i << " ";
    }
    cout << endl;

    cout << "DP with tabulation with space optimization: " << knapsack_tab_opt(weights, values, n, w) << endl;

    cout << "DP with tabulation using single array (space optimized): " << knapsack_tab_1D(weights, values, n, w) << endl;

    return 0;
}
