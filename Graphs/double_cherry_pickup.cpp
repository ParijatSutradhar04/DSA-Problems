#include<bits/stdc++.h>
using namespace std;

int give_max(int i, int j1, int j2, vector<vector<vector<int>>> &dp, int r, int c, vector<vector<int>> grid) {
    if (j1 < 0 || j2 < 0 || j1 > c-1 || j2 > c-1) {
        return -1e6;
    }
    
    if (i == r-1) {
        if (j1 == j2) return grid[i][j1];
        else return grid[i][j1] + grid[i][j2];
    }

    if (dp[i][j1][j2] != -1) return dp[i][j1][j2];

    int maxim = -1e6;
    for (int d1 = -1; d1 <= 1; d1++) {
        for (int d2 = -1; d2 <= 1; d2++) {
            int value = 0;
            if (j1 == j2) value = grid[i][j1];
            else value = grid[i][j1] + grid[i][j2];
            value += give_max(i + 1, j1 + d1, j2 + d2, dp, r, c, grid);
            maxim = max(maxim, value);
        }
    }
    return dp[i][j1][j2] = maxim;
}

int give_max(vector<vector<vector<int>>> &dp, int r, int c, vector<vector<int>> grid) {
    for (int j1 = 0; j1 < c; j1++) {
        for (int j2 = 0; j2 < c; j2++) {
            if (j1 == j2) {
                dp[r-1][j1][j2] = grid[r-1][j1];
            }
            else {
                dp[r-1][j1][j2] = grid[r-1][j1] + grid[r-1][j2];
            }
        }
    }

    for (int i = r-2; i >= 0; i--) {
        for (int j1 = 0; j1 < c; j1++) {
            for (int j2 = 0; j2 < c; j2++) {
                int maxim = -1e6;
                for (int d1 = -1; d1 <= 1; d1++) {
                    for (int d2 = -1; d2 <= 1; d2++) {
                        int value = 0;
                        if (j1 == j2) value = grid[i][j1];
                        else value = grid[i][j1] + grid[i][j2];
                        if (j1 + d1 >= 0 && j2 + d2 >= 0 && j1 + d1 < c && j2 + d2 < c) {
                            value += dp[i+1][j1+d1][j2+d2];
                        }
                        maxim = max(maxim, value);
                    }
                }
                dp[i][j1][j2] = maxim;
            }
        }
    }
    return dp[0][0][c-1];
}

int cherry_pickup2(vector<vector<int>> grid) {
    int r = grid.size();
    int c = grid[0].size();

    vector<vector<vector<int>>> dp(r, vector<vector<int>> (c, vector<int> (c, 0)));
    
    return give_max(0, 0, c-1, dp, r, c, grid);
}

int cherry_pickup_optimised(vector<vector<int>> grid) {
    int r = grid.size();
    int c = grid[0].size();
    vector<vector<int>> curr(c, vector<int> (c, -1));
    vector<vector<int>> front(c, vector<int> (c, -1));

    for (int j1 = 0; j1 < c; j1++) {
        for (int j2 = 0; j2 < c; j2++) {
            if (j1 == j2) {
                front[j1][j2] = grid[r-1][j1];
            }
            else {
                front[j1][j2] = grid[r-1][j1] + grid[r-1][j2];
            }
        }
    }

    for (int i = r-2; i >= 0; i--) {
        for (int j1 = 0; j1 < c; j1++) {
            for (int j2 = 0; j2 < c; j2++) {
                int maxim = -1e6;
                for (int d1 = -1; d1 <= 1; d1++) {
                    for (int d2 = -1; d2 <= 1; d2++) {
                        int value = 0;
                        if (j1 == j2) value = grid[i][j1];
                        else value = grid[i][j1] + grid[i][j2];
                        if (j1 + d1 >= 0 && j2 + d2 >= 0 && j1 + d1 < c && j2 + d2 < c) {
                            value += front[j1+d1][j2+d2];
                        }
                        maxim = max(maxim, value);
                    }
                }
                curr[j1][j2] = maxim;
            }
        }
        front = curr;
    }

    return curr[0][c-1];
}
 
int main(){
    
    return 0;
}
