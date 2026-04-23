#include <iostream>
#include <iomanip>    // For setprecision
#include <windows.h>  // For QueryPerformanceCounter (true high-resolution timer)
using namespace std;

/*
  Function: merge
  ----------------
  Merges two sorted subarrays into one sorted array

  Left subarray  : arr[l .. m]
  Right subarray : arr[m+1 .. r]
*/
void merge(int arr[], int l, int m, int r) {

    // Calculate sizes of two subarrays
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temporary arrays
    int *L = new int[n1];
    int *R = new int[n2];

    // Copy elements into left temporary array
    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];

    // Copy elements into right temporary array
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Initial indices for L[], R[], and main array
    int i = 0, j = 0, k = l;

    // Merge elements back into arr[] in sorted order
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy remaining elements of L[] (if any)
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy remaining elements of R[] (if any)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free temporary memory
    delete[] L;
    delete[] R;
}

/*
  Function: mergeSort
  -------------------
  Sorts the array using Divide and Conquer

  Steps:
  1. Divide the array into two halves
  2. Recursively sort both halves
  3. Merge the sorted halves
*/
void mergeSort(int arr[], int l, int r) {

    // Base condition: at least two elements
    if (l < r) {

        // Find middle index
        int m = l + (r - l) / 2;

        // Recursively sort left half
        mergeSort(arr, l, m);

        // Recursively sort right half
        mergeSort(arr, m + 1, r);

        // Merge the two sorted halves
        merge(arr, l, m, r);
    }
}

int main() {

    int n;
    cout << "Enter number of elements: ";
    cin >> n;

    // Dynamic arrays
    int *arr = new int[n];
    int *original = new int[n];   // Backup for time measurement

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        original[i] = arr[i];     // Save original input
    }

    int repeat = 10000;           // Repeat to get measurable time
    volatile int sink = 0;        // Prevents compiler from optimizing the loop away

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&start);
    for (int r = 0; r < repeat; r++) {

        // Restore original array before each sort
        for (int i = 0; i < n; i++)
            arr[i] = original[i];

        // Perform Merge Sort
        mergeSort(arr, 0, n - 1);

        sink += arr[0];           // Force compiler to keep the work
    }
    QueryPerformanceCounter(&end);

    // Total elapsed time in seconds (sub-microsecond resolution)
    double timeTaken = double(end.QuadPart - start.QuadPart) / double(freq.QuadPart);

    // Display sorted array
    cout << "\nSorted array:\n";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";

    cout << fixed << setprecision(9);
    cout << "\n\nTotal time for " << repeat << " runs: " << timeTaken << " seconds";
    cout << "\nAverage time per sort: " << (timeTaken / repeat) << " seconds";

    // Free allocated memory
    delete[] arr;
    delete[] original;

    return 0;
}
