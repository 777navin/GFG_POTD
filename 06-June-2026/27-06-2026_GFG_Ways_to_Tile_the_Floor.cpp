/*
Date: 27-06-2026
Problem Name: Ways to Tile the Floor
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Dynamic Programming, Recursion, Math

Problem Summary:
Given a floor of dimensions n x m and an unlimited supply of tiles of size 1 x m, 
find the total number of ways to completely tile the floor. A tile can be placed 
horizontally (covering 1 row and m columns) or vertically (covering m rows and 1 column).
Return the answer modulo 10^9 + 7.

Methods to Solve:
1. Dynamic Programming (Tabulation/Space Optimized)

For Method 1:
- Intuition: 
  Let dp[i] be the number of ways to tile a floor of size i x m.
  - If we place a tile vertically (1 x m), it takes 1 unit of length, leaving a floor of size (i-1) x m.
  - If we place tiles horizontally (m x 1), we must place m such tiles to cover the width, 
    taking m units of length, leaving a floor of size (i-m) x m.
  - Recurrence: dp[i] = dp[i-1] + dp[i-m] for i >= m, and dp[i] = 1 for i < m.
- Approach: Use a DP array to store results and compute values iteratively.
- Dry Run (n=4, m=4):
  dp[0]=1, dp[1]=1, dp[2]=1, dp[3]=1
  dp[4] = dp[3] + dp[4-4] = 1 + 1 = 2.
- Time Complexity: O(n)
- Space Complexity: O(n) (Can be optimized to O(m))

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
DP     | O(n)| O(n)| General Purpose

Final Recommended Solution: Dynamic Programming
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Calculates the number of ways to tile an n x m floor using 1 x m tiles.
     * * @param n The height of the floor
     * @param m The width of the tiles/floor constraint
     * @return Total ways modulo 10^9 + 7
     */
    int countWays(int n, int m) {
        if (n < m) return 1;
        if (n == m) return 2;

        const int MOD = 1e9 + 7;
        // dp[i] stores the number of ways to tile a floor of length i
        vector<int> dp(n + 1);

        // Base cases: 
        // For length < m, we can only place tiles horizontally in one way.
        for (int i = 1; i <= n; i++) {
            if (i < m) {
                dp[i] = 1;
            } else if (i == m) {
                dp[i] = 2;
            } else {
                // Recurrence: 
                // Either place 1 vertical tile (take 1 length) 
                // OR place m horizontal tiles (take m length)
                dp[i] = (dp[i - 1] + dp[i - m]) % MOD;
            }
        }

        return dp[n];
    }
};

/*
// Example Driver Code (for local testing):
int main() {
    Solution sol;
    cout << sol.countWays(4, 4) << endl; // Output: 2
    cout << sol.countWays(2, 3) << endl; // Output: 1
    return 0;
}
*/
