// In a network of n cities with one direct road between each pair, multiple routes may exist via other cities. Travelling between cities incurs toll taxes. Total cost from city A to B via cities C and D is the sum of toll taxes for {A, C}, {C, D}, and {D, B}. Using a token on a road reduces tolls; e.g., using a token on C-D route eliminates its toll. The shortest route between A and B has the minimum toll tax. A k-token-shortest route minimizes tolls using k tokens to eliminate k tolls.

#include<bits/stdc++.h>
using namespace std;

// Shortest Path in Weighted Graph using Bellman Ford Algorithm
int** shortestDistance(int s, int n, int** weight) {
    int** path = new int* [n];
    for(int i = 0; i < n; i++) {
        path[i] = new int[2];
        path[i][0] = 1000;
    }
    path[s][0] = 0;
    for(int i = 0; i < n-1; i++) {
        for(int j = 0; j < n; j++) {
            for(int k = 0; k < n; k++) {
                if (k != j) {
                    int w = weight[j][k];
                    if(path[k][0] > path[j][0] + w) {
                        path[k][0] = path[j][0] + w;
                        path[k][1] = j;
                    }
                }
            }
        }
    }
    return path;
}

int main() {
    int n;
    cout << "Enter the number of cities: ";
    cin >> n;
    int **tolls = new int* [n];
    for (int i=0; i<n; i++) {
        tolls[i] = new int[n];
        tolls[i][i] = 0;
        for (int j=0; j<i; j++) {
            cout << "Enter the cost between vertex " << j+1 << " and " << i+1 << ": ";
            cin >> tolls[i][j];
            tolls[j][i] = tolls[i][j];
        }
    }

    int **min_cost[n];
    for (int i = 0; i < n; i++) {
        min_cost[i] = shortestDistance(i, n, tolls);
    }

    cout << "Shortest Routes: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (i != j) {
                cout << "[" << i+1 << ", " << j+1 << "]: "; 
                int k = j;
                while(k != i) {
                    cout << k+1 << " ";
                    k = min_cost[i][k][1];
                }
                cout << i+1 << ", ";
                cout << "with cost: " << min_cost[i][j][0] << endl;
            }
        }
    }

    return 0;
}