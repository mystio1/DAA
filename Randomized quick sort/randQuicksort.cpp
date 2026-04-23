#include <iostream>
#include <cstdlib>      // for rand() and srand()
#include <ctime>        // for time() - used to seed the random generator
using namespace std;

// Program: Randomized Quick Sort.
// Normal Quick Sort picks the last (or first) element as the pivot, which
// gives O(n^2) time for already-sorted arrays. Randomized Quick Sort picks
// a RANDOM pivot each time -> expected O(n log n) even for bad inputs.

// Swap helper (kept separate so partition() stays clean and readable).
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Partition step (Lomuto scheme):
// Rearranges arr[low..high] so that all elements <= pivot come before it
// and all elements > pivot come after. Returns the pivot's final index.
int partition(int arr[], int low, int high) {
    int pivot = arr[high];          // pivot is placed at arr[high] by randomPartition
    int i = low - 1;                // i = boundary of "smaller than pivot" region

    for (int j = low; j < high; j++) {
        // If current element is smaller or equal to pivot, move it left.
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    // Finally, place pivot in its correct sorted position.
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Randomized partition:
// Picks a RANDOM index in [low..high], swaps it with arr[high], then calls
// normal partition(). This randomization is what gives us the expected
// O(n log n) time regardless of input order.
int randomPartition(int arr[], int low, int high) {
    int randIdx = low + rand() % (high - low + 1);   // random index in the range
    swap(arr[randIdx], arr[high]);                   // move random element to end
    return partition(arr, low, high);
}

// Recursive Randomized Quick Sort.
void randQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = randomPartition(arr, low, high);     // split around a random pivot
        randQuickSort(arr, low, p - 1);              // sort left half
        randQuickSort(arr, p + 1, high);             // sort right half
    }
}

int main() {
    // Seed rand() with current time so we get different random pivots
    // every time we run the program.
    srand(time(0));

    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    int arr[100];                   // fixed max size
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    randQuickSort(arr, 0, n - 1);

    cout << "\nSorted array: ";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

// Time Complexity:
//   Best / Average : O(n log n)   -> random pivot balances partitions on average
//   Worst          : O(n^2)       -> very rare (only if unlucky pivots every time)
// Space Complexity : O(log n)     -> recursion stack in average case
C:\Users\rahul\OneDrive\Desktop\daa\randQuicksort.cpp