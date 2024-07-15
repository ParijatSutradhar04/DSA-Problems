#include<bits/stdc++.h>
#include<C:\Users\parij\parijat_java\Algo1\priorityQueue.h>

using namespace std;

class Graph{
    int V;
    vector<int> *adj;
    public:
    Graph(int V) {
        this->V = V;
        adj = new vector<int>[V];
    }

    void addEdge(int v, int w) {
        adj[v].push_back(w);
    }
    
    int* BFS(int s) {
        int visited[V] = {0};
        int* bfs = new int[V];
        int k = 0;
        queue<int> q;
        q.push(s);
        visited[s] = 1;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            bfs[k++] = u;
            for(int i = 0; i < adj[u].size(); i++) {
                if(visited[adj[u][i]] == 0) {
                    q.push(adj[u][i]);
                    visited[adj[u][i]] = 1;
                }
            }
        }
        return bfs;
    }
    
    void DFSHelper(int s, int* dfs, int visited[]) {
        dfs[0] = s;
        visited[s] = 1;
        for (auto i : adj[s]) {
            if(visited[i] == 0) {
                DFSHelper(i, dfs+1, visited);
            }
        }
    }

    int* DFS(int s) {
        int* dfs = new int[V];
        int visited[V] = {0};
        DFSHelper(s, dfs, visited);
        return dfs;
    }

    int* DFSwithStack(int s) {
        int visited[V] = {0};
        int* dfs = new int[V];
        int k = 0;
        stack<int> st;
        st.push(s);
        visited[s] = 1;
        while(!st.empty()) {
            int u = st.top();
            st.pop();
            dfs[k++] = u;
            for(int i = 0; i < adj[u].size(); i++) {
                if(visited[adj[u][i]] == 0) {
                    st.push(adj[u][i]);
                    visited[adj[u][i]] = 1;
                }
            }
        }
        return dfs;
    }

    // Topological Sort
    void topologicalSortHelper(int s, int* visited, stack<int>& st) {
        visited[s] = 1;
        for(auto i : adj[s]) {
            if(visited[i] == 0) {
                topologicalSortHelper(i, visited, st);
            }
        }
        st.push(s);
    }

    int* topologicalSort() {
        int* visited = new int[V];
        for(int i = 0; i < V; i++) {
            visited[i] = 0;
        }
        stack<int> st;
        for(int i = 0; i < V; i++) {
            if(visited[i] == 0) {
                topologicalSortHelper(i, visited, st);
            }
        }
        int* topological = new int[V];
        int k = 0;
        while(!st.empty()) {
            topological[k++] = st.top();
            st.pop();
        }
        return topological;
    }

    // Detect Cycle in Directed Graph
    bool isCyclicHelper(int s, int* visited, int* recStack) {
        if(visited[s] == 0) {
            visited[s] = 1;
            recStack[s] = 1;
            for(auto i : adj[s]) {
                if(visited[i] == 0 && isCyclicHelper(i, visited, recStack)) {
                    return true;
                } else if(recStack[i] == 1) {
                    return true;
                }
            }
        }
        recStack[s] = 0;
        return false;
    }

    bool isDirectedCyclic() {
        int* visited = new int[V];
        int* recStack = new int[V];
        for(int i = 0; i < V; i++) {
            visited[i] = 0;
            recStack[i] = 0;
        }
        for(int i = 0; i < V; i++) {
            if(isCyclicHelper(i, visited, recStack)) {
                return true;
            }
        }
        return false;
    }

    // Detect Cycle in Undirected Graph
    bool isCyclicHelper(int s, int* visited, int parent) {
        visited[s] = 1;
        for(auto i : adj[s]) {
            if(visited[i] == 0) {
                if(isCyclicHelper(i, visited, s)) {
                    return true;
                }
            } else if(i != parent) {
                return true;
            }
        }
        return false;
    }

    bool isCyclic() {
        int* visited = new int[V];
        for(int i = 0; i < V; i++) {
            visited[i] = 0;
        }
        for(int i = 0; i < V; i++) {
            if(visited[i] == 0) {
                if(isCyclicHelper(i, visited, -1)) {
                    return true;
                }
            }
        }
        return false;
    }

    // Shortest Path in Unweighted Graph
    int* shortestPath(int s) {
        int* visited = new int[V];
        int* distance = new int[V];
        for(int i = 0; i < V; i++) {
            visited[i] = 0;
            distance[i] = INT_MAX;
        }
        queue<int> q;
        q.push(s);
        visited[s] = 1;
        distance[s] = 0;
        while(!q.empty()) {
            int u = q.front();
            q.pop();
            for(auto i : adj[u]) {
                if(visited[i] == 0) {
                    q.push(i);
                    visited[i] = 1;
                    distance[i] = distance[u] + 1;
                }
            }
        }
        return distance;
    }

    // Shortest Path in Weighted Graph
    int* shortestPath(int s, int* weight) {
        int* visited = new int[V];
        int* distance = new int[V];
        for(int i = 0; i < V; i++) {
            visited[i] = 0;
            distance[i] = INT_MAX;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, s});
        distance[s] = 0;
        while(!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for(auto i : adj[u]) {
                int v = i;
                int w = weight[u] + weight[v];
                if(distance[v] > distance[u] + w) {
                    distance[v] = distance[u] + w;
                    pq.push({distance[v], v});
                }
            }
        }
        return distance;
    }

    // Shortest Path in Weighted Graph using Dijkstra's Algorithm
    int* dijkstra(int s, int* weight) {
        int* distance = new int[V];
        for(int i = 0; i < V; i++) {
            distance[i] = INT_MAX;
        }
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, s});
        distance[s] = 0;
        while(!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            for(auto i : adj[u]) {
                int v = i;
                int w = weight[u] + weight[v];
                if(distance[v] > distance[u] + w) {
                    distance[v] = distance[u] + w;
                    pq.push({distance[v], v});
                }
            }
        }
        return distance;
    }

    // Shortest Path in Weighted Graph using Bellman Ford Algorithm
    int* bellmanFord(int s, int* weight) {
        int* distance = new int[V];
        for(int i = 0; i < V; i++) {
            distance[i] = INT_MAX;
        }
        distance[s] = 0;
        for(int i = 0; i < V-1; i++) {
            for(int j = 0; j < V; j++) {
                for(auto k : adj[j]) {
                    int u = j;
                    int v = k;
                    int w = weight[u] + weight[v];
                    if(distance[v] > distance[u] + w) {
                        distance[v] = distance[u] + w;
                    }
                }
            }
        }
        return distance;
    }

    // Shortest Path in Weighted Graph using Floyd Warshall Algorithm
    int* floydWarshall(int* weight) {
        int* distance = new int[V];
        for(int i = 0; i < V; i++) {
            distance[i] = INT_MAX;
        }
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                for(int k = 0; k < V; k++) {
                    if(distance[j] > distance[i] + distance[k]) {
                        distance[j] = distance[i] + distance[k];
                    }
                }
            }
        }
        return distance;
    }

    // Minimum Spanning Tree using Prim's Algorithm
    pair<int, vector<pair<int, int>>> prim(int* weight) {
        int visited[V] = {0};
        int weight_sum = 0;
        vector<pair<int, int>> mst; // {node, parent}
        // priority_queue: {weight, {node, parent}}
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pq;
        pq.push({0, {0, -1}});
        visited[0] = 1;
        while(!pq.empty()) {
            int node = pq.top().second.first;
            int parent = pq.top().second.second;
            int w = pq.top().first;
            if (parent != -1 && visited[node] == 0) {
                mst.push_back({node, parent});
                weight_sum += w;
                visited[node] = 1;
            }
            for (auto v : adj[node]) {
                if(visited[v] == 0) {
                    pq.push({weight[node] + weight[v], {v, node}});
                }
            }
        }
    }

    // Minimum Spanning Tree using Prim's Algorithm without Priority Queue
    // Time Complexity: O(V^2)
    int minKey(int* key, int* mstSet) {
        int min = INT_MAX;
        int min_index;
        for(int i = 0; i < V; i++) {
            if(mstSet[i] == 0 && key[i] < min) {
                min = key[i];
                min_index = i;
            }
        }
        return min_index;
    }

    int* prim_without_pq(int* weight) {
        int* parent = new int[V];
        int* key = new int[V];
        int* mstSet = new int[V];
        for(int i = 0; i < V; i++) {
            key[i] = INT_MAX;
            mstSet[i] = 0;
        }
        key[0] = 0;
        parent[0] = -1;
        for(int i = 0; i < V-1; i++) {
            int u = minKey(key, mstSet);
            mstSet[u] = 1;
            for(auto j : adj[u]) {
                int v = j;
                int w = weight[u] + weight[v];
                if(mstSet[v] == 0 && weight[v] < key[v]) {
                    parent[v] = u;
                    key[v] = weight[v];
                }
            }
        }
        return parent;
    }

    // Minimum Spanning Tree using Boruvka's Algorithm
    int* boruvka(int* weight) {
        int* parent = new int[V];
        int* cheapest = new int[V];
        int* cheapestEdge = new int[V];
        for(int i = 0; i < V; i++) {
            parent[i] = -1;
            cheapest[i] = -1;
            cheapestEdge[i] = -1;
        }
        int numTrees = V;
        while(numTrees > 1) {
            for(int i = 0; i < V; i++) {
                cheapest[i] = -1;
                cheapestEdge[i] = -1;
            }
            for(int i = 0; i < V; i++) {
                int set_u = find(parent, i);
                if(cheapest[set_u] == -1) {
                    cheapest[set_u] = weight[i];
                    cheapestEdge[set_u] = i;
                } else {
                    if(weight[i] < cheapest[set_u]) {
                        cheapest[set_u] = weight[i];
                        cheapestEdge[set_u] = i;
                    }
                }
            }
            for(int i = 0; i < V; i++) {
                if(cheapestEdge[i] != -1) {
                    int set_u = find(parent, i);
                    int set_v = find(parent, cheapestEdge[i]);
                    if(set_u != set_v) {
                        parent[set_u] = set_v;
                        numTrees--;
                    }
                }
            }
        }
        return parent;
    }

    // Minimum Spanning Tree using Kruskal's Algorithm
    int find(int parent[], int i) {
        if(parent[i] == -1) {
            return i;
        }
        return find(parent, parent[i]);
    }

    void Union(int parent[], int x, int y) {
        int xset = find(parent, x);
        int yset = find(parent, y);
        parent[xset] = yset;
    }

    int* kruskal(int* weight) {
        int* parent = new int[V];
        for(int i = 0; i < V; i++) {
            parent[i] = -1;
        }
        vector<pair<int, pair<int, int>>> edges;
        for(int i = 0; i < V; i++) {
            for(auto j : adj[i]) {
                edges.push_back({weight[i] + weight[j], {i, j}});
            }
        }
        sort(edges.begin(), edges.end());
        int* mst = new int[V];
        int k = 0;
        for(int i = 0; i < edges.size(); i++) {
            int u = edges[i].second.first;
            int v = edges[i].second.second;
            int set_u = find(parent, u);
            int set_v = find(parent, v);
            if(set_u != set_v) {
                mst[k++] = u;
                Union(parent, set_u, set_v);
            }
        }
        return mst;
    }

    // Strongly Connected Components
    void SCCUtil(int u, int* disc, int* low, stack<int>& st, int* stackMember, int* visited) {
        static int time = 0;
        disc[u] = low[u] = ++time;
        st.push(u);
        stackMember[u] = 1;
        for(auto i : adj[u]) {
            int v = i;
            if(disc[v] == -1) {
                SCCUtil(v, disc, low, st, stackMember, visited);
                low[u] = min(low[u], low[v]);
            } else if(stackMember[v] == 1) {
                low[u] = min(low[u], disc[v]);
            }
        }
        int w = 0;
        if(low[u] == disc[u]) {
            while(st.top() != u) {
                w = st.top();
                cout << w << " ";
                stackMember[w] = 0;
                st.pop();
            }
            w = st.top();
            cout << w << endl;
            stackMember[w] = 0;
            st.pop();
        }
    }

    void SCC() {
        int* disc = new int[V];
        int* low = new int[V];
        int* stackMember = new int[V];
        int* visited = new int[V];
        stack<int> st;
        for(int i = 0; i < V; i++) {
            disc[i] = -1;
            low[i] = -1;
            stackMember[i] = 0;
            visited[i] = 0;
        }
        for(int i = 0; i < V; i++) {
            if(disc[i] == -1) {
                SCCUtil(i, disc, low, st, stackMember, visited);
            }
        }
    }

    void printGraph() {
        for(int i = 0; i < V; i++) {
            cout << i << " -> ";
            for(int j = 0; j < adj[i].size(); j++) {
                cout << adj[i][j] << " ";
            }
            cout << endl;
        }
    }
};

void print(int* arr) {
    int n = sizeof(arr)/sizeof(arr[0]);
    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
}
 
int main(){
    
    return 0;
}
