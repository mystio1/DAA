#include <iostream>
#include <string>
#include <chrono>       // for measuring the time taken by the search
using namespace std;
using namespace std::chrono;

// Program: KMP (Knuth-Morris-Pratt) Pattern Matching.
// Unlike the Naive method, KMP does NOT re-check characters that have
// already matched. It uses an LPS (Longest Prefix-Suffix) table to decide
// how far to shift the pattern after a mismatch -> O(n + m) time.

// Builds the LPS array (also called failure function) for the pattern.
// lps[i] = length of the longest proper prefix of pattern[0..i]
// that is also a suffix of pattern[0..i]. This is what tells KMP
// how many characters we can SKIP after a mismatch instead of rechecking.
void buildLPS(string pattern, int lps[]) {
    int m = pattern.length();
    int len = 0;                  // length of previous longest prefix-suffix
    lps[0] = 0;                   // LPS of a single char is always 0

    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            // Characters match -> extend the current prefix-suffix length.
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                // Mismatch but we had a partial match:
                // fall back to the previous longest prefix-suffix.
                // We don't increment i here because we want to retry.
                len = lps[len - 1];
            }
            else {
                // No previous match to fall back on -> lps[i] = 0.
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Performs the actual KMP search.
// Prints each index where the pattern is found and returns total matches.
int kmpSearch(string text, string pattern, int lps[]) {
    int n = text.length();
    int m = pattern.length();

    int i = 0;         // index in text
    int j = 0;         // index in pattern
    int matches = 0;

    while (i < n) {
        if (text[i] == pattern[j]) {
            // Characters match -> move both pointers forward.
            i++;
            j++;

            // Full pattern matched -> record the starting index.
            if (j == m) {
                cout << "Pattern found at index " << (i - j) << endl;
                matches++;

                // Instead of restarting j from 0, use LPS to skip ahead.
                j = lps[j - 1];
            }
        }
        else {
            // Mismatch after j matched characters.
            if (j != 0) {
                // Use LPS info -> we already know some prefix matches, so
                // shift the pattern smartly instead of starting over.
                j = lps[j - 1];
            }
            else {
                // Nothing matched yet -> just move to the next char in text.
                i++;
            }
        }
    }
    return matches;
}

int main() {
    string text, pattern;

    cout << "Enter the text: ";
    getline(cin, text);                     // getline -> allows spaces in text

    cout << "Enter the pattern: ";
    getline(cin, pattern);

    // Basic input validation.
    if (pattern.empty() || pattern.length() > text.length()) {
        cout << "Invalid input: pattern is empty or longer than text." << endl;
        return 0;
    }

    int m = pattern.length();
    int lps[1000];                          // supports patterns up to length 1000

    // Build the LPS table first (preprocessing step of KMP).
    buildLPS(pattern, lps);

    // Display the LPS table so the user can see how KMP preprocesses the pattern.
    cout << "\nLPS Table:" << endl;
    cout << "Index    : ";
    for (int i = 0; i < m; i++) cout << i << " ";
    cout << "\nPattern  : ";
    for (int i = 0; i < m; i++) cout << pattern[i] << " ";
    cout << "\nLPS      : ";
    for (int i = 0; i < m; i++) cout << lps[i] << " ";
    cout << endl << endl;

    // --- Measure time taken by the KMP search only (not input) ---
    auto start = high_resolution_clock::now();
    int total = kmpSearch(text, pattern, lps);
    auto stop = high_resolution_clock::now();

    // nanoseconds -> needed because KMP finishes in <1 microsecond for small inputs.
    auto duration = duration_cast<nanoseconds>(stop - start);

    if (total == 0)
        cout << "\nPattern not found in the given text." << endl;
    else
        cout << "\nTotal occurrences = " << total << endl;

    cout << "Time taken by KMP search = " << duration.count() << " nanoseconds" << endl;

    return 0;
}

// Time Complexity  : O(n + m)   -> LPS build is O(m), search is O(n)
// Space Complexity : O(m)       -> for the LPS array
