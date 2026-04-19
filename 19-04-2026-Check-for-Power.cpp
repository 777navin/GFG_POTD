#include <bits/stdc++.h>
using namespace std;

// Problem: Check for Power
// Date: 19-04-2026
// Language: C++

/*
=========================================================
Approach 1: Iterative Division (Optimal)
=========================================================
Intuition:
If y is a power of x, then repeatedly divide y by x.

Example:
x = 2, y = 8

8 -> 4 -> 2 -> 1

If at any point y is not divisible by x,
then y is not a power of x.

Special Case:
If x == 1:
Only power possible is 1.

Time Complexity: O(logx(y))
Space Complexity: O(1)

=========================================================
Approach 2: Multiplication Method
=========================================================
Start from 1 and keep multiplying by x
until value >= y.

If value == y return true else false.

Time Complexity: O(logx(y))
Space Complexity: O(1)
=========================================================
*/

class Solution {
public:

    // Approach 1: Iterative Division
    bool isPowerofX(int x, int y) {

        if (x == 1)
            return (y == 1);

        while (y > 1) {
            if (y % x != 0)
                return false;

            y /= x;
        }

        return true;
    }

    // Approach 2: Multiplication Method
    bool isPowerMultiply(int x, int y) {

        if (x == 1)
            return (y == 1);

        long long val = 1;

        while (val < y) {
            val *= x;
        }

        return (val == y);
    }
};

// Driver Code
int main() {
    int t;
    cin >> t;

    while (t--) {
        int x, y;
        cin >> x >> y;

        Solution obj;

        if (obj.isPowerofX(x, y))
            cout << "true" << endl;
        else
            cout << "false" << endl;
    }

    return 0;
}
