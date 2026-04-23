#include <iostream>
#include <cmath>
#include <iomanip>    // For setprecision
#include <windows.h>  // For QueryPerformanceCounter (true high-resolution timer)
using namespace std;

/*
  Karatsuba multiplication using Divide and Conquer
*/
long long karatsuba(long long x, long long y) {

    // Base case: if numbers are small, multiply directly
    if (x < 10 || y < 10)
        return x * y;

    // Find the number of digits
    int n = max((int)log10(x) + 1, (int)log10(y) + 1);
    int half = n / 2;

    // Split numbers
    long long a = x / (long long)pow(10, half);
    long long b = x % (long long)pow(10, half);
    long long c = y / (long long)pow(10, half);
    long long d = y % (long long)pow(10, half);

    // Recursive multiplications
    long long ac = karatsuba(a, c);
    long long bd = karatsuba(b, d);
    long long ad_bc = karatsuba(a + b, c + d) - ac - bd;

    // Combine results
    return ac * (long long)pow(10, 2 * half)
         + ad_bc * (long long)pow(10, half)
         + bd;
}

int main() {
    long long x, y;

    cout << "Enter first large integer: ";
    cin >> x;
    cout << "Enter second large integer: ";
    cin >> y;

    int repeat = 1000000;          // Repeat to get measurable time
    long long result = 0;
    volatile long long sink = 0;   // Prevents compiler from optimizing the loop away

    LARGE_INTEGER freq, start, end;
    QueryPerformanceFrequency(&freq);

    QueryPerformanceCounter(&start);
    for (int i = 0; i < repeat; i++) {
        result = karatsuba(x, y);
        sink += result;            // Force compiler to keep the call
    }
    QueryPerformanceCounter(&end);

    double timeTaken = double(end.QuadPart - start.QuadPart) / double(freq.QuadPart);

    cout << fixed << setprecision(9);
    cout << "\nResult of multiplication: " << result;
    cout << "\nTotal time for " << repeat << " runs: " << timeTaken << " seconds";
    cout << "\nAverage time per call: " << (timeTaken / repeat) << " seconds";

    return 0;
}
