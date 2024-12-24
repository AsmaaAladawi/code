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
/* heap sort*/
#include <iostream>
#include <vector>
using namespace std;

// Function to perform Max-Heapify on a subtree rooted at index `i`
void maxHeapify(vector<int>& arr, int n, int i) {
    int largest = i;         // Initialize the largest as root
    int left = 2 * i + 1;    // Left child
    int right = 2 * i + 2;   // Right child

    // Check if left child exists and is greater than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // Check if right child exists and is greater than the current largest
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If the largest is not root, swap and heapify the affected subtree
    if (largest != i) {
        swap(arr[i], arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// Function to build a Max-Heap from the input array
void buildMaxHeap(vector<int>& arr) {
    int n = arr.size();
    // Start from the last non-leaf node and perform Max-Heapify
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }
}

// Function to perform Heap-Sort
void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Step 1: Build a Max-Heap
    buildMaxHeap(arr);

    // Step 2: Extract elements from the heap
    for (int i = n - 1; i > 0; i--) {
        // Swap the root (maximum) with the last element
        swap(arr[0], arr[i]);

        // Rebuild the heap on the reduced array
        maxHeapify(arr, i, 0);
    }
}

// Utility function to print an array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

// Main function
int main() {
    vector<int> arr = {8, 10, 23, 13, 2};
    heapSort(arr);

    cout << "Sorted array: ";
    printArray(arr);

    return 0;
}
