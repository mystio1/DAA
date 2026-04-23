#include <iostream>
#include <string>
using namespace std;

// Program: Naive Pattern Matching
// Given a text and a pattern, find ALL positions in the text where the pattern occurs.
// This is the most basic approach: slide the pattern over the text one character
// at a time, and for every position check character-by-character if it matches.

// Function that performs naive pattern matching.
// Returns the number of times the pattern was found in the text.
int naiveSearch(string text, string pattern) {
    int n = text.length();          // length of main text
    int m = pattern.length();       // length of pattern
    int matches = 0;                // count of total matches found

    // Try every possible starting position i in the text.
    // We only go up to (n - m) because a pattern of length m
    // cannot start any later than that.
    for (int i = 0; i <= n - m; i++) {

        int j = 0;                  // index inside the pattern

        // Compare pattern[0..m-1] with text[i..i+m-1] character by character.
        // Stop the moment a mismatch is found (no point continuing).
        while (j < m && text[i + j] == pattern[j]) {
            j++;
        }

        // If j reached m, it means all characters matched -> pattern found.
        if (j == m) {
            cout << "Pattern found at index " << i << endl;
            matches++;
        }
    }

    return matches;
}

int main() {
    string text, pattern;

    cout << "Enter the text: ";
    getline(cin, text);             // getline used so text can contain spaces

    cout << "Enter the pattern: ";
    getline(cin, pattern);

    // Edge case: empty pattern or pattern longer than text -> no search possible.
    if (pattern.empty() || pattern.length() > text.length()) {
        cout << "Invalid input: pattern is empty or longer than text." << endl;
        return 0;
    }

    int total = naiveSearch(text, pattern);

    if (total == 0)
        cout << "\nPattern not found in the given text." << endl;
    else
        cout << "\nTotal occurrences = " << total << endl;

    return 0;
}

// Time Complexity  : O((n - m + 1) * m)  ~=  O(n * m)  in the worst case
// Space Complexity : O(1)  -> only a few integer variables used
