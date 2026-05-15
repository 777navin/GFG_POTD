/*
Date: 15-05-2026
Problem Name: Special Keyboard
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Dynamic Programming, Greedy, Recursion

Problem Summary:
Imagine a special keyboard with only 4 keys:
1. Key 1: Print 'A'
2. Key 2: Ctrl+A (Select All)
3. Key 3: Ctrl+C (Copy)
4. Key 4: Ctrl+V (Paste)
Given 'n' key presses, find the maximum number of 'A' characters that can be printed on the screen.

Methods to Solve:

1. Recursive Approach (Brute Force):
   - Intuition: At any point, we can either press 'A' or use the Copy-Paste sequence.
   - Approach: For each 'n', try all possible break-points where we could have started a 
     Ctrl-A, Ctrl-C, Ctrl-V sequence.
   - Time Complexity: O(2^N) - Exponential.
   - Space Complexity: O(N) - Recursion stack.
   - When to use: Only for very small N (N < 20).

2. Dynamic Programming (Optimal Approach):
   - Intuition: The maximum characters for 'n' can be derived from the results of 
     fewer key presses. If n <= 6, the maximum is simply 'n' (pressing 'A' repeatedly). 
     For n > 6, we look for a breakpoint 'j' where we performed a Copy-Paste operation.
   - Approach: 
     - Create a dp[n+1] array.
     - For i <= 6: dp[i] = i.
     - For i > 6: dp[i] = max(dp[i-1] + 1, max over j from (i-3) down to 1: dp[j] * (i-j-1)).
     - The multiplier (i-j-1) comes from: 1 step for Ctrl-A, 1 for Ctrl-C, and (i-j-2) for Ctrl-V.
       Total = dp[j] + (i-j-2) * dp[j] = dp[j] * (i-j-1).
   - Dry Run (n=7):
     - dp[1..6] = {1, 2, 3, 4, 5, 6}
     - For i=7:
       j=4: dp[4] * (7-4-1) = 4 * 2 = 8
       j=3: dp[3] * (7-3-1) = 3 * 3 = 9 (Max)
     - Result: 9.
   - Time Complexity: O(N^2)
   - Space Complexity: O(N)
   - Why better: Eliminates redundant calculations via memoization/tabulation.
   - When to use: Best for the given constraints (N <= 75).

Comparison Table:
Method             | TC     | SC   | Best Use Case
-------------------|--------|------|-------------------------
Recursive          | O(2^N) | O(N) | Educational purposes
Dynamic Programming| O(N^2) | O(N) | Competitive Programming / Production

Final Recommended Solution: Dynamic Programming (Tabulation).
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * @brief Calculates the maximum number of 'A's using N keystrokes.
     * * @param n Number of key presses allowed.
     * @return long long Maximum characters possible.
     */
    long long optimalKeys(int n) {
        // If n is less than 7, the optimal way is always just pressing 'A' n times.
        // Because Ctrl-A, Ctrl-C, Ctrl-V takes 3 steps, it only becomes beneficial 
        // when we have enough steps to paste and exceed the linear count.
        if (n <= 6) {
            return n;
        }

        // dp[i] stores the maximum 'A's possible with i key presses.
        // We use long long as n=75 can exceed 32-bit integer limits.
        vector<long long> dp(n + 1, 0);

        // Base cases for n <= 6
        for (int i = 1; i <= 6; i++) {
            dp[i] = i;
        }

        // Fill DP table for values from 7 to n
        for (int i = 7; i <= n; i++) {
            // Option 1: Just press 'A' (though for i > 6, this is rarely optimal)
            dp[i] = dp[i - 1] + 1;

            // Option 2: Try all possible break-points for Copy-Paste
            // We need at least 3 steps for the sequence (Ctrl-A, Ctrl-C, Ctrl-V)
            // So we check from j = i-3 downwards.
            for (int j = i - 3; j >= 1; j--) {
                long long current_val = dp[j] * (i - j - 1);
                if (current_val > dp[i]) {
                    dp[i] = current_val;
                }
            }
        }

        return dp[n];
    }
};

// Driver Code for GFG-compatible environment
int main() {
    int t;
    // For local testing, you can set t = 1 or use cin
    if (!(cin >> t)) t = 0; 
    
    while (t--) {
        int n;
        cin >> n;
        
        Solution ob;
        cout << ob.optimalKeys(n) << "\n";
    }
    return 0;
}
