#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> build_adj(vector<vector<int>> matrix, int n) {
    vector<vector<pair<int, int>>> adj(n * n, vector<pair<int, int>>());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int curr_edge = n * i + j;
            if (j + 1 < n) {
                int edge = curr_edge + 1;
                int weight = matrix[i][j+1];
                if (weight != -1) {
                    adj[curr_edge].push_back({edge, weight});
                }
            }
            if (i + 1 < n) {
                int edge = curr_edge + n;
                int weight = matrix[i+1][j];
                if (weight != -1) {
                    adj[curr_edge].push_back({edge, weight});
                }
            }
        }
    }
    return adj;
}

vector<int> dijkstra(vector<vector<pair<int, int>>> &adj, int V, int src) {
    vector<int> dist(V, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; // {weight, node}
    
    pq.push({0, src});
    dist[src] = 0;

    while(!pq.empty()) {
        int distance = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        for (auto it : adj[u]) {
            int v = it.first;
            int w = it.second;
            if (dist[v] < dist[u] + w) {
                it.second = 0;
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}

int cherryPickup(vector<vector<int>> &matrix) {
    int n = matrix.size();
    vector<vector<pair<int, int>>> adj = build_adj(matrix, n);
    int forward = dijkstra(adj, n*n, 0)[n*n - 1];
    int backward = dijkstra(adj, n*n, n*n - 1)[0];
    return forward + backward;
}
 
int main(){
    int n;
    cout << "Enter n: ";
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    cout << "Size: " << matrix.size() << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            matrix[i][j] = x;
        }
    }

    cout << "Maximum cherries: " << cherryPickup(matrix) << endl;

    return 0;
}
