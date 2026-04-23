#include <iostream>
using namespace std;

#define N 4

char board[N][N];

// Flags to remember which columns and diagonals are already attacked.
// Using these makes the safety check O(1) instead of scanning the board.
bool colUsed[N];          // colUsed[c]  -> true if column c already has a queen
bool diagLR[2 * N];       // for '\' diagonals, cells with same (row - col) lie on same diagonal
bool diagRL[2 * N];       // for '/' diagonals, cells with same (row + col) lie on same diagonal

int solutionCount = 0;    // total number of valid arrangements found

// Checks whether placing a queen at (row, col) is safe.
// We only need to check column and the two diagonals because the row
// is already safe (we place exactly one queen per row).
bool isSafe(int row, int col) {
    if (colUsed[col])                return false;
    if (diagLR[row - col + N - 1])   return false;   // shift by (N-1) to avoid negative index
    if (diagRL[row + col])           return false;
    return true;
}

// Prints the current board layout as one valid solution.
void printBoard() {
    solutionCount++;
    cout << "\nSolution " << solutionCount << ":" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

// Recursive backtracking function: tries to place queens row by row.
void solve(int row) {
    // Base case: all N queens placed successfully -> print this arrangement.
    if (row == N) {
        printBoard();
        return;
    }

    // Try every column in the current row.
    for (int col = 0; col < N; col++) {
        if (isSafe(row, col)) {

            // ---- place the queen and mark its attacks ----
            board[row][col] = 'Q';
            colUsed[col] = true;
            diagLR[row - col + N - 1] = true;
            diagRL[row + col] = true;

            // Move to the next row
            solve(row + 1);

            // ---- BACKTRACK: undo the placement if the path fails ----
            // This lets us try the next column in this same row.
            board[row][col] = '.';
            colUsed[col] = false;
            diagLR[row - col + N - 1] = false;
            diagRL[row + col] = false;
        }
    }
}

int main() {
    // Initialize the board with '.' (empty cell).
    // All flag arrays are bool globals, so they are already false by default.
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            board[i][j] = '.';

    cout << "Solving " << N << "-Queens problem using Backtracking..." << endl;

    solve(0);     // start placing from row 0

    if (solutionCount == 0)
        cout << "\nNo solution exists for N = " << N << endl;
    else
        cout << "\nTotal solutions found = " << solutionCount << endl;

    return 0;
}

// Time Complexity  : O(N!)   -> in worst case we try every column permutation
// Space Complexity : O(N)    -> recursion depth + flag arrays
