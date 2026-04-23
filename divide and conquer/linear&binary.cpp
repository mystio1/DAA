#include <iostream>   // For input and output (cin, cout)
#include <iomanip>    // For setprecision
#include <windows.h>  // For QueryPerformanceCounter (true high-resolution timer on Windows)
using namespace std;

/*
  Linear Search Function
  - Searches element one by one from start to end
  - Returns index if found, else -1
*/
int linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {     // Traverse entire array
        if (arr[i] == key)            // If key matches current element
            return i;                 // Return index
    }
    return -1;                        // Key not found
}

/*
  Binary Search (Iterative)
  - Works only on sorted array
  - Uses loop to divide search space
*/
int binarySearchIterative(int arr[], int n, int key) {
    int low = 0, high = n - 1;        // Initialize search boundaries

    while (low <= high) {             // Repeat while search space exists
        int mid = (low + high) / 2;   // Find middle index

        if (arr[mid] == key)          // If middle element is key
            return mid;
        else if (key < arr[mid])      // If key is smaller
            high = mid - 1;            // Search left half
        else
            low = mid + 1;             // Search right half
    }
    return -1;                        // Key not found
}

/*
  Binary Search (Recursive)
  - Uses recursion instead of loop
*/
int binarySearchRecursive(int arr[], int low, int high, int key) {
    if (low > high)                   // Base condition (no elements left)
        return -1;

    int mid = (low + high) / 2;       // Find middle index

    if (arr[mid] == key)              // If key found
        return mid;
    else if (key < arr[mid])          // Search left half recursively
        return binarySearchRecursive(arr, low, mid - 1, key);
    else                              // Search right half recursively
        return binarySearchRecursive(arr, mid + 1, high, key);
}

int main() {
    int n, key, choice;
    int repeat = 1000000;             // Repeat count to make time measurable
    volatile int sink = 0;            // Prevents compiler from optimizing the loop away

    cout << "Enter number of elements: ";
    cin >> n;

    int *arr = new int[n];            // Dynamic array allocation

    cout << "Enter elements (sorted for Binary Search):\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];                // Input array elements
    }

    cout << "Enter element to search: ";
    cin >> key;

    // Menu for choosing search method
    cout << "\n1. Linear Search";
    cout << "\n2. Binary Search (Iterative)";
    cout << "\n3. Binary Search (Recursive)";
    cout << "\nEnter your choice: ";
    cin >> choice;

    int result = -1;                  // Stores index of found element
    LARGE_INTEGER freq, start, end;   // Windows high-resolution counter
    QueryPerformanceFrequency(&freq); // Counter ticks per second
    double timeTaken;                 // Stores execution time in seconds

    switch (choice) {
        case 1:
            QueryPerformanceCounter(&start);
            for (int i = 0; i < repeat; i++) {
                result = linearSearch(arr, n, key);
                sink += result;        // Force compiler to keep the call
            }
            QueryPerformanceCounter(&end);
            break;

        case 2:
            QueryPerformanceCounter(&start);
            for (int i = 0; i < repeat; i++) {
                result = binarySearchIterative(arr, n, key);
                sink += result;
            }
            QueryPerformanceCounter(&end);
            break;

        case 3:
            QueryPerformanceCounter(&start);
            for (int i = 0; i < repeat; i++) {
                result = binarySearchRecursive(arr, 0, n - 1, key);
                sink += result;
            }
            QueryPerformanceCounter(&end);
            break;

        default:
            cout << "Invalid choice";
            delete[] arr;             // Free allocated memory
            return 0;
    }

    // Total elapsed time in seconds (sub-microsecond resolution)
    timeTaken = double(end.QuadPart - start.QuadPart) / double(freq.QuadPart);

    if (result != -1)
        cout << "\nElement found at index: " << result;
    else
        cout << "\nElement not found";

    cout << fixed << setprecision(9);
    cout << "\nTotal time for " << repeat << " runs: " << timeTaken << " seconds";
    cout << "\nAverage time per search: " << (timeTaken / repeat) << " seconds";

    delete[] arr;                     // Free memory
    return 0;
}
