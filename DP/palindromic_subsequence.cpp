#include<bits/stdc++.h>
using namespace std;

bool isPalindrome(string s, int i) {
    if (s[i] != s[i + 4]) return false;
    if (s[i + 1] != s[i + 3]) return false;
    return true;
}
int num_seq(string s, int i, int j, int k=5) {
    if (j - i < k - 1) return 0;
    if (j - i == k - 1) return isPalindrome(s, i);
    if (k == 1) return j - i + 1;
    if (s[i] == s[j]) return num_seq(s, i + 1, j - 1, k - 2) + num_seq(s, i, j - 1, k) + num_seq(s, i + 1, j, k) - num_seq(s, i + 1, j - 1, k);
    return num_seq(s, i, j - 1, k) + num_seq(s, i + 1, j, k) - num_seq(s, i + 1, j - 1, k);
}

int num_seq(string s) {
    if (s.size() < 5) return 0;
    int n = s.size();
    vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(6, 0)));
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            dp[i][j][1] = j - i + 1;
        }
    }

    for (int i = n-5; i >= 0; i--) {
        for (int k = 3; k <= 5; k += 2) {
            for (int j = i + k - 1; j < n; j++) {
                if (s[i] == s[j]) {
                    dp[i][j][k] = dp[i + 1][j - 1][k - 2] + dp[i][j - 1][k] + dp[i + 1][j][k] - dp[i + 1][j - 1][k];
                } else {
                    dp[i][j][k] = dp[i][j - 1][k] + dp[i + 1][j][k] - dp[i + 1][j - 1][k];
                }
            }
        }
    }
    return dp[0][n - 1][5];
}
 
int main() {
    string s = "0100110";
    int n = s.size();
    cout << "Number of palindromic subsequences: " << num_seq(s) << endl;
    return 0;
}