#include<bits/stdc++.h>
using namespace std;

vector<int> prefix_func(string s) {
    int n = s.size();
    vector<int> pi(n, 0);

    for (int i = 1; i < n; i++) {
        int j = pi[i-1];

        while(j > 0 && s[i] != s[j]) {
            j = pi[j-1];
        }

        if (s[i] == s[j]) {
            pi[i] = j + 1;
        }
    }

    return pi;
}

int KMP(string text, string pattern) {
    int n = text.size();
    int m = pattern.size();
    vector<int> pi = prefix_func(pattern);

    int i = 0, j = 0; // i for text, j for pattern
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        else if (j > 0) {
            j = pi[j-1];
        }
        else {
            i++;
        }
        if (j == m) {
            return i - m;
        }
    }
    return -1;
}
 
int main() {
    string s = "abacabacabacaba";
    vector<int> pi = prefix_func(s);
    for (int i = 0; i < pi.size(); i++) {
        cout << pi[i] << " ";
    }
    cout << endl;

    string text = "aaaxaaaa";
    string pattern = "aaaa";

    cout << KMP(text, pattern) << endl;

    return 0;
}
