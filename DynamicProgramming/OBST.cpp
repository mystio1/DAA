#include <iostream>
using namespace std;

// Program: Optimal Binary Search Tree (OBST) using Dynamic Programming.
// Given sorted keys with success probabilities p[i] and failure probabilities q[i],
// find a BST with minimum expected search cost.

const double INF = 1e9;       // used as "infinity" while taking minimum
const int MAX = 50;           // max keys supported (keeps table sizes fixed)

double e[MAX][MAX];           // e[i][j] = min expected cost of OBST on keys i..j
double w[MAX][MAX];           // w[i][j] = total probability weight of keys i..j
int rootTbl[MAX][MAX];        // stores best root for keys i..j (needed to print tree)

// Builds the DP tables and returns the minimum expected search cost.
double buildOBST(double p[], double q[], int n) {

    // Base case: empty subtree (j = i-1) has only the dummy failure key q[i-1].
    for (int i = 1; i <= n + 1; i++) {
        e[i][i - 1] = q[i - 1];
        w[i][i - 1] = q[i - 1];
    }

    // L = length of the subtree range; we grow from small subtrees to full tree
    // because e[i][j] depends on shorter ranges e[i][r-1] and e[r+1][j].
    for (int L = 1; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;

            e[i][j] = INF;                           // start with INF to take min later
            w[i][j] = w[i][j - 1] + p[j] + q[j];     // weight = old weight + new key + new dummy

            // Try every key r in [i..j] as the root and keep the one giving min cost.
            // +w[i][j] is added because making r the root increases depth of every
            // node in this range by 1, contributing its total weight to the cost.
            for (int r = i; r <= j; r++) {
                double t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    rootTbl[i][j] = r;               // remember which root was best
                }
            }
        }
    }

    return e[1][n];          // answer for full tree covering all n keys
}

// Prints tree structure by recursively reading rootTbl[][] filled during DP.
void printTree(int i, int j, int parent, string side) {
    if (i > j) return;                               // empty subtree -> stop

    int r = rootTbl[i][j];
    if (parent == 0)
        cout << "k" << r << " is the ROOT of the tree" << endl;
    else
        cout << "k" << r << " is the " << side << " child of k" << parent << endl;

    printTree(i, r - 1, r, "LEFT");
    printTree(r + 1, j, r, "RIGHT");
}

int main() {
    int n;
    cout << "Enter the number of keys: ";
    cin >> n;

    double p[MAX];           // p[1..n] -> success probabilities
    double q[MAX];           // q[0..n] -> failure probabilities (one extra, for gaps)

    cout << "Enter the " << n << " successful search probabilities (p1..pn): ";
    for (int i = 1; i <= n; i++) cin >> p[i];

    cout << "Enter the " << (n + 1) << " unsuccessful search probabilities (q0..qn): ";
    for (int i = 0; i <= n; i++) cin >> q[i];

    double minCost = buildOBST(p, q, n);

    cout << "\nMinimum expected search cost = " << minCost << endl;
    cout << "\nStructure of the Optimal BST:" << endl;
    printTree(1, n, 0, "");

    return 0;
}

// Time Complexity  : O(n^3)   -> three nested loops (L, i, r)
// Space Complexity : O(n^2)   -> for e[][], w[][], rootTbl[][] tables
