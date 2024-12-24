#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int findParent(int v, vector<int>& parent) {
    if (parent[v] != v)
        parent[v] = findParent(parent[v], parent); // Path compression
    return parent[v];
}

// Union two sets containing u and v
void unionSets(int u, int v, vector<int>& parent, vector<int>& rank) {
    int rootU = findParent(u, parent);
    int rootV = findParent(v, parent);

    if (rootU != rootV) {
        // Union by rank
        if (rank[rootU] < rank[rootV]) {
            parent[rootU] = rootV;
        } else if (rank[rootU] > rank[rootV]) {
            parent[rootV] = rootU;
        } else {
            parent[rootV] = rootU;
            rank[rootU]++;
        }
    }
}

// Kruskal's Algorithm to find MST
void kruskal(int V, vector<vector<int>>& edges) {
    // Step 1: Sort edges by weight
    sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[2] < b[2]; // Compare edge weights
    });

    // Initialize Union-Find data structure
    vector<int> parent(V);
    vector<int> rank(V, 0);
    for (int i = 0; i < V; i++) {
        parent[i] = i; // Each vertex is its own parent initially
    }

    vector<vector<int>> mst; // Store the MST edges
    int mstWeight = 0;

    // Step 2: Iterate through sorted edges
    for (const auto& edge : edges) {
        int u = edge[0], v = edge[1], weight = edge[2];

        // Check if u and v are in different sets
        if (findParent(u, parent) != findParent(v, parent)) {
            // Add edge to MST
            mst.push_back(edge);
            mstWeight += weight;

            // Union the sets of u and v
            unionSets(u, v, parent, rank);

            // Stop if MST contains V-1 edges
            if (mst.size() == V - 1)
                break;
        }
    }

    cout << "Edges in MST:" << endl;
    for (const auto& edge : mst) {
        cout << edge[0] << " - " << edge[1] << " : " << edge[2] << endl;
    }
    cout << "Total weight of MST: " << mstWeight << endl;
}

// Main function
int main() {
    int V = 4; // Number of vertices
    vector<vector<int>> edges = {
        {0, 1, 10},
        {0, 2, 8},
        {0, 3, 5},
        {1, 2, 14},
        {2, 3, 5}
    };

    kruskal(V, edges);

    return 0;
}
