#include<bits/stdc++.h>
using namespace std;

class DisjointSet {
    private:
    vector<int> parent, rank, size;

    public:
    DisjointSet(int n) {
        parent = vector<int>(n+1);
        rank = vector<int>(n+1, 0);
        size = vector<int>(n+1, 1);
        for(int i = 0; i <= n; i++) {
            parent[i] = i;
        }
    }

    int findParent(int x) {
        if (parent[x] == x) return x;
        parent[x] = findParent(parent[x]); // Path compression
        return parent[x];
    }

    // Both union by rank and union by size has almost constant time complexity, but union by size is slightly better
    // Time complexity = 4 * alpha

    void unionByRank(int x, int y) {
        int px = findParent(x);
        int py = findParent(y);

        if (px == py) return;

        if (rank[px] < rank[py]) {
            parent[px] = py;
        }
        else if (rank[px] > rank[py]) {
            parent[py] = px;
        }
        else {
            parent[px] = py;
            rank[py]++;
        }
    }

    void unionBySize(int x, int y) {
        int px = findParent(x);
        int py = findParent(y);

        if (px == py) return;

        if (size[px] < size[py]) {
            parent[px] = py;
            size[py] += size[px];
        }
        else if (size[px] > size[py]) {
            parent[py] = px;
            size[px] += size[py];
        }
        else {
            parent[px] = py;
            size[py] += size[px];
        }
    }

    bool isSameSet(int x, int y) {
        return findParent(x) == findParent(y);
    }
};
 
int main(){
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    DisjointSet ds(n);
    int x, y;

    while(true) {
        int option;
        cout << "1: Enter the element to union" << endl;
        cout << "2: Enter the elements to check if they are in the same set" << endl;
        cout << "3: Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;
        if (option == 1) {
            cout << "Enter the elements to union: ";
            cin >> x >> y;
            ds.unionByRank(x, y);
        } else if (option == 2){
            cout << "Enter the elements to check if they are in the same set: ";
            cin >> x >> y;
            cout << (ds.isSameSet(x, y) ? "Yes" : "No") << endl;
        } else {
            break;
        }
    }
    
    return 0;
}
