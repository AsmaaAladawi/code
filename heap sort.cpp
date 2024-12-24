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
