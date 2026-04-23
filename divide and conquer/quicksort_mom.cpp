#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

/*
  Function: findMedian
  --------------------
  Finds the median of a small array (size <= 5)
  Steps:
  1. Sort the small array
  2. Return the middle element
*/
int findMedian(int arr[], int size) {
    sort(arr, arr + size);        // Sort the small group
    return arr[size / 2];         // Return middle element
}

/*
  Function: medianOfMedians
  -------------------------
  Selects a good pivot using the Median of Medians algorithm
  This guarantees balanced partitions
*/
int medianOfMedians(int arr[], int n) {

    // Base case: if array size is small,
    // directly return its median
    if (n <= 5)
        return findMedian(arr, n);

    int groups = (n + 4) / 5;     // Number of groups of size 5
    int *medians = new int[groups]; // Array to store medians

    int i = 0;

    // Divide array into groups of 5 and find medians
    for (; i < n / 5; i++) {
        medians[i] = findMedian(arr + i * 5, 5);
    }

    // Handle remaining elements (< 5)
    if (i * 5 < n) {
        medians[i] = findMedian(arr + i * 5, n % 5);
        i++;
    }

    // Recursively find median of medians
    int mom = medianOfMedians(medians, i);

    delete[] medians;             // Free allocated memory
    return mom;
}

/*
  Function: partition
  -------------------
  Rearranges elements around the chosen pivot
  Elements < pivot go left, > pivot go right
*/
int partition(int arr[], int low, int high, int pivot) {

    // Find the index of the pivot in the array
    int pivotIndex;
    for (pivotIndex = low; pivotIndex <= high; pivotIndex++) {
        if (arr[pivotIndex] == pivot)
            break;
    }

    // Move pivot to the end
    swap(arr[pivotIndex], arr[high]);

    int i = low;

    // Place elements smaller than pivot on the left
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
    }

    // Place pivot in its correct sorted position
    swap(arr[i], arr[high]);

    return i;   // Return final position of pivot
}

/*
  Function: quickSort
  -------------------
  Quick Sort using Divide and Conquer
  Pivot is chosen using Median of Medians
*/
void quickSort(int arr[], int low, int high) {
    if (low < high) {

        // Number of elements in current subarray
        int n = high - low + 1;

        // Choose pivot using Median of Medians
        int pivot = medianOfMedians(arr + low, n);

        // Partition array around pivot
        int pivotPos = partition(arr, low, high, pivot);

        // Recursively sort left subarray
        quickSort(arr, low, pivotPos - 1);

        // Recursively sort right subarray
        quickSort(arr, pivotPos + 1, high);
    }
}

int main() {
    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    int *arr = new int[n];        // Array for sorting
    int *original = new int[n];   // Backup of original input

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        original[i] = arr[i];     // Save original array
    }

    int repeat = 10000;            // Repeat sorting to measure time

    clock_t start = clock();      // Start time

    for (int r = 0; r < repeat; r++) {

        // Restore original array before each sort
        for (int i = 0; i < n; i++)
            arr[i] = original[i];

        // Perform Quick Sort
        quickSort(arr, 0, n - 1);
    }

    clock_t end = clock();        // End time

    // Calculate total time in seconds
    double timeTaken = double(end - start) / CLOCKS_PER_SEC;

    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << "\n\nTime taken to sort: " << timeTaken << " seconds";

    delete[] arr;                 // Free memory
    delete[] original;
    return 0;
}
