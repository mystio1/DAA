#include <iostream>
using namespace std;

// Global variable to count number of comparisons
int comparisons = 0;

/*
  Structure to store minimum and maximum together
  This helps return both values from the function
*/
struct MinMax {
    int min;
    int max;
};

/*
  Function to find minimum and maximum using Divide & Conquer
  Parameters:
  arr  -> input array
  low  -> starting index
  high -> ending index
*/
MinMax findMinMax(int arr[], int low, int high) {
    MinMax result, left, right;

    // -------- BASE CASE 1: Only one element --------
    // If the array has only one element,
    // then min and max are the same
    if (low == high) {
        result.min = arr[low];
        result.max = arr[low];
        return result;
    }

    // -------- BASE CASE 2: Two elements --------
    // Only one comparison is needed
    if (high == low + 1) {
        comparisons++;   // counting comparison
        if (arr[low] < arr[high]) {
            result.min = arr[low];
            result.max = arr[high];
        } else {
            result.min = arr[high];
            result.max = arr[low];
        }
        return result;
    }

    // -------- RECURSIVE CASE: More than two elements --------

    // Divide the array into two halves
    int mid = (low + high) / 2;

    // Recursively find min and max of left half
    left = findMinMax(arr, low, mid);

    // Recursively find min and max of right half
    right = findMinMax(arr, mid + 1, high);

    // Compare minimums of both halves
    comparisons++;
    result.min = (left.min < right.min) ? left.min : right.min;

    // Compare maximums of both halves
    comparisons++;
    result.max = (left.max > right.max) ? left.max : right.max;

    // Return combined result
    return result;
}

int main() {
    int n;

    cout << "Enter number of elements: ";
    cin >> n;

    // Dynamically allocate array
    int *arr = new int[n];

    cout << "Enter elements:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Call divide and conquer Min–Max function
    MinMax result = findMinMax(arr, 0, n - 1);

    // Output results
    cout << "\nMinimum element: " << result.min;
    cout << "\nMaximum element: " << result.max;
    cout << "\nNumber of comparisons: " << comparisons;

    // Free allocated memory
    delete[] arr;

    return 0;
}
