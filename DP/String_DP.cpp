#include<bits/stdc++.h>
using namespace std;

// Longest Common Subsequence
// Time Complexity: O(n*m)
// Space Complexity: O(n*m)
int longestCommonSubsequence(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = 1 + dp[i - 1][j - 1];
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[n][m];
}

// Longest Common Subsequence with space optimization
// Time Complexity: O(n*m)
// Space Complexity: O(m)
int longestCommonSubsequence(string s1, string s2) {
    int n = s1.size(), m = s2.size();
    vector<int> dp(m + 1, 0);

    for (int i = 1; i <= n; i++) {
        int prev = 0;
        for (int j = 1; j <= m; j++) {
            int temp = dp[j];
            if (s1[i - 1] == s2[j - 1]) {
                dp[j] = 1 + prev;
            } else {
                dp[j] = max(dp[j], dp[j - 1]);
            }
            prev = temp;
        }
    }
    return dp[m];
}

// Least change to make s1 to s2
// Time Complexity: O(n*m)
// Space Complexity: O(n*m)
int minChange(string s1, string s2){
    int n = s1.size(), m = s2.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
    for(int i=1; i<=n; i++){
        dp[i][0] = i;
    }
    for(int i=1; i<=m; i++){
        dp[0][i] = i;
    }
    for(int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            if(s1[i-1] == s2[j-1]){
                dp[i][j] = dp[i-1][j-1];
            }else{
                dp[i][j] = 1 + min({dp[i-1][j-1], dp[i-1][j], dp[i][j-1]});
            }
        }
    }
    return dp[n][m];
}

// Least change to make s1 to s2 with space optimization
// Time Complexity: O(n*m)
// Space Complexity: O(m)
int minChange(string s1, string s2){
    int n = s1.size(), m = s2.size();
    vector<int> dp(m+1, 0);
    for(int i=1; i<=m; i++){
        dp[i] = i;
    }
    for(int i=1; i<=n; i++){
        int prev = dp[0];
        dp[0] = i;
        for(int j=1; j<=m; j++){
            int temp = dp[j];
            if(s1[i-1] == s2[j-1]){
                dp[j] = prev;
            }else{
                dp[j] = 1 + min({prev, dp[j], dp[j-1]});
            }
            prev = temp;
        }
    }
    return dp[m];
}

int main(){
    string s1, s2;
    cout << "Enter the two strings: ";
    cin >> s1 >> s2;
    cout << "Longest Common Substring: " << longestCommonSubsequence(s1, s2) << endl;
    cout << "Minimum Change: " << minChange(s1, s2) << endl;

    return 0;
}
