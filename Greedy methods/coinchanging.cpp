#include <iostream>
using namespace std;

// Function to sort the coin array in DECREASING order.
// I wrote a simple selection sort manually instead of using STL sort()
// because the greedy method needs the largest coin first, and this way
// I also understand the sorting logic clearly.
void sortDesc(int coins[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int maxIdx = i;                          // assume current position has the max
        for (int j = i + 1; j < n; j++) {
            if (coins[j] > coins[maxIdx]) {      // found a bigger coin -> update index
                maxIdx = j;
            }
        }
        // swap the biggest coin found with position i
        int temp = coins[i];
        coins[i] = coins[maxIdx];
        coins[maxIdx] = temp;
    }
}

// Main function - entry point of the program.
// Takes coin denominations and the amount from user, then tries
// to make the amount using the MINIMUM number of coins by applying
// the greedy approach (pick the largest coin that fits, repeat).
int main() {
    int n;
    cout << "How many different coins do you have? ";
    cin >> n;

    int coins[100];                              // array to store coin denominations

    // Input all the coin values from user.
    cout << "Enter values of the coins:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    // Sort the coins from largest to smallest so the greedy
    // method can always try the biggest coin first.
    sortDesc(coins, n);

    int amount;
    cout << "Enter the value of the item: ";
    cin >> amount;

    int used[100] = {0};                         // count of each coin used
    int idx = 0;                                 // pointer to current coin

    // Greedy loop: keep subtracting the largest coin that fits
    // until the amount becomes 0 OR we run out of coins.
    while (amount > 0 && idx < n) {
        if (coins[idx] <= amount) {              // coin fits -> take it
            amount = amount - coins[idx];
            used[idx] = used[idx] + 1;
        }
        else {
            idx++;                               // coin too big -> move to smaller one
        }
    }

    // If amount is still not zero, it means we could not make
    // the exact value with the given coin denominations.
    if (amount != 0) {
        cout << "\nAmount cannot be formed with given coins" << endl;
        return 0;
    }

    // Otherwise, print how many of each coin were used.
    cout << "\nCoins required:" << endl;
    for (int j = 0; j < n; j++) {
        if (used[j] > 0) {
            cout << used[j] << " coin(s) of " << coins[j] << endl;
        }
    }

    return 0;
}
//Time complexity = O(n²) due to selection sort; greedy loop itself is O(n).