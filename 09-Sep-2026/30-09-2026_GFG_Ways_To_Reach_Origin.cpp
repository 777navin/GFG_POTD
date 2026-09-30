/*
=========================================================
Date        : 30-09-2026
Problem Name: Ways to Reach Origin
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Combinatorics, Math

Problem Summary:
Given a point (x, y) on a 2D grid, find the total number of distinct paths to reach the origin (0, 0).
From any cell (x, y), moves are only allowed left to (x - 1, y) or down to (x, y - 1).
Return the result modulo 10^9 + 7.

Key Observation:
Reaching (0, 0) from (x, y) requires exactly x moves left and y moves down in any order.
This is equivalent to finding the combination C(x + y, x) % (10^9 + 7).
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Recursive / Brute Force
---------------------------------------------------------
• Intuition:
  At any cell (x, y), the total paths to (0, 0) is the sum of paths from (x - 1, y) and (x, y - 1).

• Approach:
  Recursively compute paths(x, y) = paths(x - 1, y) + paths(x, y - 1) with base cases when x == 0 or y == 0.

• Why it Works:
  Explores all possible valid paths down to the origin recursively.

• Time Complexity (TC): O(2^(x + y))
• Space Complexity (SC): O(x + y) due to recursion stack depth.


---------------------------------------------------------
APPROACH 2: Dynamic Programming (2D Tabulation)
---------------------------------------------------------
• Intuition:
  Overlapping subproblems can be cached using a 2D table where dp[i][j] stores ways to reach (0, 0) from (i, j).

• Approach:
  Initialize dp[i][0] = 1 and dp[0][j] = 1.
  Fill the grid iteratively: dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % 10^9+7.

• Why it Works:
  Builds up the answer bottom-up using previously computed results for smaller grid coordinates.

• Time Complexity (TC): O(x * y)
• Space Complexity (SC): O(x * y)


---------------------------------------------------------
APPROACH 3: Combinatorics / Combinations Formula (Most Optimal)
---------------------------------------------------------
• Intuition:
  Any path requires total steps = (x + y), consisting of x left moves and y down moves.
  The total distinct paths is simply choosing x positions out of (x + y) total positions, i.e., C(x + y, x).

• Approach:
  Compute nCr(x + y, min(x, y)) modulo 10^9 + 7 using multiplicative combination or Pascal's identity / DP.

• Why it Works:
  Directly counts permutations of the movement steps without simulating grid paths.

• Time Complexity (TC): O(x * y) or O(x + y)
• Space Complexity (SC): O(x * y) or O(1)
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
• We use Dynamic Programming / Pascal's Triangle approach to compute C(x + y, x) modulo 10^9 + 7.
• Since constraints are 0 <= x, y <= 500, a 2D table of size up to 1001x1001 runs well within time limits (O(x * y)).
• Avoids modular inverse computations needed for direct division in combinations.
*/

#include <vector>

class Solution {
public:
    int ways(int x, int y) {
        int MOD = 1e9 + 7;
        
        // dp[i][j] stores the number of paths from (i, j) to (0, 0)
        std::vector<std::vector<int>> dp(x + 1, std::vector<int>(y + 1, 0));
        
        for (int i = 0; i <= x; i++) {
            for (int j = 0; j <= y; j++) {
                if (i == 0 || j == 0) {
                    dp[i][j] = 1; // Only 1 straight path along the axes
                } else {
                    dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
                }
            }
        }
        
        return dp[x][y];
    }
};
