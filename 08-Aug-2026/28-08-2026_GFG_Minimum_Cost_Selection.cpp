/*
=========================================================
Date        : 28-08-2026
Problem Name: Minimum Cost Selection (Buying Vegetables)
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Dynamic Programming, Matrix, Arrays

Problem Summary:
Given an n x 3 cost matrix representing three choices per row, select exactly 
one choice from each row such that no two adjacent rows pick the same choice.
Return the minimum total cost required across all rows.

Key Observation:
The choice in the current row only depends on the choices made in the immediately 
preceding row; we cannot pick the same column index in consecutive rows.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Recursive / Brute Force (Explore All Paths)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Try every valid combination of choices row by row and find the minimum sum.

• Approach:
  Recursively pick column j for row i, then call for row i + 1 with any column != j.

• Why it Works:
  It exhaustively searches all valid non-adjacent paths across the matrix.

• Time Complexity (TC):
  O(3 * 2^(n - 1)) = O(2^n) - Exponential branching at every row.

• Space Complexity (SC):
  O(n) - Maximum recursion stack depth.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Dynamic Programming (Tabulation - 2D Table)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Store the minimum cost to reach each choice at the current row to avoid recomputation.

• Approach:
  Maintain a DP table dp[n][3] where dp[i][j] = mat[i][j] + min(dp[i-1][(j+1)%3], dp[i-1][(j+2)%3]).

• Why it Works:
  Optimal substructure and overlapping subproblems guarantee the global optimum.

• Time Complexity (TC):
  O(n) - Single pass over n rows with 3 choices each.

• Space Complexity (SC):
  O(n) - Table of size n x 3.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 3: Space-Optimized Dynamic Programming (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Only the results of the previous row (3 values) are needed to compute the current row.

• Approach:
  Keep track of prev0, prev1, prev2 representing minimum costs ending at row i - 1, 
  and update them iteratively for each row.

• Why it Works:
  Transition only looks back by one step, so older history can be safely discarded.

• Time Complexity (TC):
  O(n) - Exactly n iterations performing constant O(1) operations.

• Space Complexity (SC):
  O(1) - Constant auxiliary space using only a few scalar variables.
*/

/*
=========================================================
FINAL APPROACH: Space-Optimized DP
• Why this approach is chosen:
  It achieves the optimal linear time complexity O(n) while minimizing auxiliary memory to O(1).
• Why it is better than previous ones:
  Eliminates the exponential call stack of recursion and reduces O(n) memory allocation of the 2D DP table.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minCost(vector<vector<int>>& mat) {
        int n = mat.size();
        if (n == 0) return 0;

        // Base state: costs for the first row
        int prev0 = mat[0][0];
        int prev1 = mat[0][1];
        int prev2 = mat[0][2];

        // Transition through remaining rows
        for (int i = 1; i < n; i++) {
            int curr0 = mat[i][0] + min(prev1, prev2);
            int curr1 = mat[i][1] + min(prev0, prev2);
            int curr2 = mat[i][2] + min(prev0, prev1);

            prev0 = curr0;
            prev1 = curr1;
            prev2 = curr2;
        }

        // Return minimum cost among all three ending choices
        return min({prev0, prev1, prev2});
    }
};
