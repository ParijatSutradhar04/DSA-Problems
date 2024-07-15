#include<bits/stdc++.h>
using namespace std;

// Dijkstra's Algorithm
vector<pair<int, int>> dijkstra(int s, int V, vector<vector<int>> weights) {
    vector<pair<int, int>> path(V, {INT_MAX, 0});
    path[s] = {0, 0};
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, s});
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        for (int v = 0; v < V; v++) {
            int w = weights[u][v];
            if (path[u].first + w < path[v].first) {
                path[v] = {path[u].first + w, u};
                pq.push({path[v].first, v});
            }
        }
    }
    return path;
}

// Shortest Path
vector<vector<pair<int, int>>> shortest_path(int V, vector<vector<int>> weights) {
    vector<vector<pair<int, int>>> min_cost(V, vector<pair<int, int>> (V));
    for (int i = 0; i < V; i++) {
        min_cost[i] = dijkstra(i, V, weights);
    }
    return min_cost;
}

// 1-token Shortest Path
vector<vector<pair<int, int>>> one_token_shortest_path(int V, vector<vector<int>> weights) {
    vector<vector<pair<int, int>>> min_cost(V, vector<pair<int, int>> (V,  {INT_MAX, 0}));
    for (int i = 0; i < V; i++) {
        vector<pair<int, int>> path = dijkstra(i, V, weights);
        for (int u = 0; u < V; u++) {
            for (int v = 0; v < V; v++) {
                vector<pair<int, int>> path_v(V, {1000, 0});
                if (u != v) {
                    path_v = dijkstra(v, V, weights);
                    path_v[v] = {0, u};
                }
                for (int k = 0; k < V; k++) {
                    if (path[u].first + path_v[k].first != 0) {
                        if (path[u].first + path_v[k].first < min_cost[i][k].first) {
                            min_cost[i][k].first = path[u].first + path_v[k].first;
                            min_cost[i][k].second = path_v[k].second;
                        }
                    }
                }
            }
        }
    }
    return min_cost;
}

 
int main(){
    int n;
    cout << "Enter the number of vertices: ";
    cin >> n;
    vector<vector<int>> weights(n, vector<int> (n));
    for (int i = 0; i < n; i++) {
        weights[i][i] = 0;
        for (int j = i+1; j < n; j++) {
            cout << "Enter the cost between city " << i+1 << " and " << j+1 << ": ";
            cin >> weights[i][j];
            weights[j][i] = weights[i][j];
        }
    }

    vector<vector<pair<int, int>>> min_cost = shortest_path(n, weights);

    cout << "Shortest Routes: " << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (i != j) {
                cout << "[" << j+1 << ", " << i+1 << "]: "; 
                int k = j;
                while(k != i) {
                    cout << k+1 << " ";
                    k = min_cost[i][k].second;
                }
                cout << i+1 << ", ";
                cout << "with cost: " << min_cost[i][j].first << endl;
            }
        }
    }

    vector<vector<pair<int, int>>> one_token_min_cost = one_token_shortest_path(n, weights);
    cout << "1-token Shortest Routes: " << endl;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < i; j++) {
    //         if (i != j) {
    //             cout << "[" << j+1 << ", " << i+1 << "]: "<< one_token_min_cost[i][j].first << endl; 
    //         }
    //     }
    // }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (i != j) {
                cout << "[" << j+1 << ", " << i+1 << "]: "; 
                int k = j;
                while(k != i) {
                    cout << k+1 << " ";
                    k = one_token_min_cost[i][k].second;
                }
                cout << i+1 << ", ";
                cout << "with cost: " << one_token_min_cost[i][j].first << endl;
            }
        }
    }

    return 0;
}