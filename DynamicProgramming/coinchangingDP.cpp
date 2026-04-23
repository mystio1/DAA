#include <iostream>
using namespace std;

// A large value used like "infinity" to represent an unreachable state.
// If dp[i] is still equal to INF at the end, it means amount i cannot
// be formed using the given coin denominations.
const int INF = 1000000;

// Function that builds the DP table and returns the minimum number
// of coins required to make the given amount.
//
// Approach: Bottom-Up Dynamic Programming (Tabulation)
//   - dp[x] stores the minimum coins needed to make amount x
//   - Recurrence:  dp[x] = min( dp[x - coin] + 1 )  for every coin <= x
//   - Base case :  dp[0] = 0  (0 coins needed to make amount 0)
int minCoins(int coins[], int n, int amount) {
    int dp[10001];                              // dp table (supports amount up to 10000)

    // Step 1: Initialize all dp values as INF (unreachable).
    for (int x = 0; x <= amount; x++) {
        dp[x] = INF;
    }
    dp[0] = 0;                                  // base case

    // Step 2: Fill the dp table for every amount from 1 to the target.
    for (int x = 1; x <= amount; x++) {
        // Try each coin denomination for the current amount x
        for (int c = 0; c < n; c++) {
            if (coins[c] <= x) {                // coin can be used only if it fits
                int prev = dp[x - coins[c]];    // look up the smaller subproblem

                // If the smaller subproblem is reachable, update dp[x]
                if (prev != INF && prev + 1 < dp[x]) {
                    dp[x] = prev + 1;
                }
            }
        }
    }

    // Step 3: Return the final answer from the dp table.
    return dp[amount];
}

// Main function - entry point of the program.
// Takes coin denominations and a target amount from user, then uses
// Dynamic Programming to find the MINIMUM number of coins needed.
// Unlike the Greedy approach, DP works correctly for ALL denominations.
int main() {
    int n;
    cout << "Enter the number of different coins: ";
    cin >> n;

    int coins[100];                             // array to store coin denominations

    cout << "Enter the values of the coins: ";
    for (int i = 0; i < n; i++) {
        cin >> coins[i];
    }

    int amount;
    cout << "Enter the amount: ";
    cin >> amount;

    // Call the DP function to compute the result.
    int result = minCoins(coins, n, amount);

    // If result is still INF, the amount cannot be formed.
    if (result == INF) {
        cout << "\nNot possible to form the amount" << endl;
    }
    else {
        cout << "\nMinimum coins required = " << result << endl;
    }

    return 0;
}
// Time Complexity  : O(n * V)   where n = number of coins, V = amount
// Space Complexity : O(V)       for the dp[] table
