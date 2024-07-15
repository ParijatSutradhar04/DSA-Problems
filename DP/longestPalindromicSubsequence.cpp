#include<bits/stdc++.h>
using namespace std;

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

int longestPalindromeSubseq(string s) {
    string rev_s = string(s.rbegin(), s.rend());
    return longestCommonSubsequence(s, rev_s);
}

// Longest Palindromic Subsequence
// Time Complexity: O(n^2)
// Space Complexity: O(n^2)
int longestPalindromicSubsequence(string s) {
    int n = s.size();
    vector<vector<int>> dp(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        dp[i][i] = 1;
    }

    for (int len = 2; len <= n; len++) {
        for (int i = 0; i < n - len + 1; i++) {
            int j = i + len - 1;
            if (s[i] == s[j] && len == 2) {
                dp[i][j] = 2;
            } else if (s[i] == s[j]) {
                dp[i][j] = 2 + dp[i + 1][j - 1];
            } else {
                dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }
    return dp[0][n - 1];
}

int main(){
    string s;
    cout << "Enter the string: ";
    cin >> s;

    cout << "Length of the longest palindromic subsequence: " << longestPalindromeSubseq(s) << endl;
    cout << "Length of the longest palindromic subsequence: " << longestPalindromicSubsequence(s) << endl;
    
    return 0;
}
