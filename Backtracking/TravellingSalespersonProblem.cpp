#include <iostream>
using namespace std;

#define N 4
#define INF 99999

// Cost matrix: cost[i][j] = distance/cost from city i to city j.
// 0 on the diagonal means "same city" (no self-loop).
int cost[N][N] = {
    {0, 12, 18, 22},
    {12, 0, 40, 28},
    {18, 40, 0, 35},
    {22, 28, 35, 0}
};

bool visited[N];          // visited[i] = true if city i is already in our current path
int minCost = INF;        // best tour cost found so far (used for pruning)

// Recursive function that explores all tours using Backtracking + Branch & Bound.
//   currCity  -> city we are currently at
//   count     -> how many cities have been visited including currCity
//   currCost  -> total cost of the path taken so far
void tsp(int currCity, int count, int currCost) {

    // --- Branch & Bound pruning ---
    // If the path so far is already costlier than the best known tour,
    // there's no point exploring further -> cut this branch early.
    if (currCost >= minCost) return;

    // --- Base case ---
    // All N cities visited AND a return edge to the starting city exists.
    // Update minCost if completing the tour gives a smaller total.
    if (count == N && cost[currCity][0] > 0) {
        int totalCost = currCost + cost[currCity][0];
        if (totalCost < minCost) {
            minCost = totalCost;
        }
        return;
    }

    // --- Try every unvisited city reachable from currCity ---
    for (int next = 0; next < N; next++) {
        if (!visited[next] && cost[currCity][next] > 0) {

            visited[next] = true;                                   // choose this city
            tsp(next, count + 1, currCost + cost[currCity][next]);  // explore further
            visited[next] = false;                                  // BACKTRACK: undo choice so other paths can use it
        }
    }
}

int main() {
    // Mark all cities unvisited initially.
    // (bool globals are already false, but we reset for clarity.)
    for (int i = 0; i < N; i++) visited[i] = false;

    // Start the tour from city 0 -> mark it visited.
    // count = 1 because city 0 is already included in the path.
    visited[0] = true;
    tsp(0, 1, 0);

    cout << "Minimum Cost of the Tour = " << minCost << endl;
    return 0;
}

// Time Complexity  : O(N!)   -> explores every permutation of cities in worst case
// Space Complexity : O(N)    -> recursion depth + visited array
