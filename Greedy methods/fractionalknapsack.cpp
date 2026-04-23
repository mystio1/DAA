#include <iostream>
using namespace std;

// Class to represent one item of the knapsack.
// Each item has a value, a weight, and its profit-per-weight ratio (pw).
// We need the ratio because fractional knapsack is solved greedily
// by picking items with the highest value-to-weight ratio first.
class Item {
public:
    int val;     // value (profit) of the item
    int wt;      // weight of the item
    double pw;   // profit/weight ratio -> used for sorting items greedily
};

// Function to sort the items in DECREASING order of their pw ratio.
// I used Insertion Sort here because it is simple and works well
// for small inputs. After sorting, items with highest ratio come first,
// which is exactly what the greedy method needs.
void sortItems(Item a[], int n) {
    for (int i = 1; i < n; i++) {
        Item key = a[i];           // pick the current element
        int j = i - 1;

        // shift all elements with smaller ratio one step to the right
        while (j >= 0 && a[j].pw < key.pw) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;            // place key in its correct sorted position
    }
}

// Main function - entry point of the program.
// It takes the items and capacity from the user, sorts the items
// by ratio, and then picks items greedily to get the maximum profit.
int main() {
    int n;
    cout << "How many items do you want to enter? ";
    cin >> n;

    Item items[100];               // array to hold all the items (max 100)

    // Input loop: take value and weight of each item
    // and calculate its profit-per-weight ratio.
    for (int i = 0; i < n; i++) {
        cout << "Item " << (i + 1) << " -> value & weight: ";
        cin >> items[i].val >> items[i].wt;
        items[i].pw = (double) items[i].val / items[i].wt;   // ratio = value / weight
    }

    int cap;
    cout << "Enter the knapsack capacity: ";
    cin >> cap;

    // Sort items so the most "valuable per kg" item comes first.
    sortItems(items, n);

    // Variables used during the greedy selection
    double profit = 0.0;           // total profit collected so far
    int used = 0;                  // how much weight we have already put in the bag
    int i = 0;                     // index of current item being considered

    // Greedy loop: keep taking items until the bag is full or items finish.
    while (i < n && used < cap) {
        // Case 1: whole item fits -> take it completely
        if (items[i].wt + used <= cap) {
            used = used + items[i].wt;
            profit = profit + items[i].val;
        }
        // Case 2: item does not fit fully -> take only the fractional part
        else {
            int left = cap - used;              // remaining capacity
            profit = profit + items[i].pw * left; // fractional profit = ratio * leftover space
            used = cap;                         // bag is now completely full
        }
        i++;
    }

    // Finally, print the total profit earned.
    cout << "\nMax profit obtained = " << profit << endl;
    return 0;
}
//time complexity = O(n²) due to insertion sort