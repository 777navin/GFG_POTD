/*
=========================================================
Date        : 20-09-2026
Problem Name: Largest Subsquare Surrounded by X
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Dynamic Programming, Matrix, Prefix Sum

Problem Summary:
Given an n x n square matrix consisting of characters 'X' and 'O'.
Find the maximum side length of a square submatrix whose 
perimeter/boundary cells are all 'X'. Cells inside the boundary
can be either 'X' or 'O'.

Key Observation:
A square with bottom-right corner at (i, j) and side length k
is valid if and only if both the row and column consecutive 'X' counts
at (i, j) are >= k, the row count at (i - k + 1, j) is >= k, and 
the column count at (i, j - k + 1) is >= k.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  Iterate over all possible submatrices of all possible side lengths 
  and check if all boundary cells contain 'X'.

• Approach:
  1. Loop through all top-left corners (r, c) and possible side lengths k.
  2. Traverse all four borders of size k to verify every cell is 'X'.
  3. Track and update the maximum valid side length found.

• Why it Works:
  Exhaustively inspects every boundary to guarantee the correctness of the result.

• Time Complexity (TC) : O(n^4)
• Space Complexity (SC): O(1)
---------------------------------------------------------

---------------------------------------------------------
APPROACH 2: Dynamic Programming / Precomputed Consecutive 'X' (Optimized)
---------------------------------------------------------
• Intuition:
  Checking boundaries in O(1) time is possible if we precompute 
  the number of consecutive 'X's ending at each cell from the left and from above.

• Approach:
  1. Build two 2D arrays:
     - left[i][j]: consecutive 'X's horizontally ending at (i, j).
     - top[i][j] : consecutive 'X's vertically ending at (i, j).
  2. Iterate bottom-right corner (i, j) from bottom-right to top-left.
  3. For each cell, maximum possible side length is min(left[i][j], top[i][j]).
  4. For candidate size k from minLen down to maxSide + 1:
     Check if top[i][j - k + 1] >= k and left[i - k + 1][j] >= k.
  5. If valid, update maxSide and break early for this cell.

• Why it Works:
  left[i][j] and top[i][j] validate the bottom and right edges of length k, 
  while left[i - k + 1][j] and top[i][j - k + 1] validate the top and left edges.

• Time Complexity (TC) : O(n^3) in the worst case, often much faster due to pruning.
• Space Complexity (SC): O(n^2) for the DP tables.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Dynamic Programming with Precomputed Consecutive 'X'
=========================================================
• Reduces the boundary check from O(k) to O(1) using precalculated DP tables.
• Checking candidate sizes k in decreasing order allows immediate breaking once 
  a valid square is found for a cell, optimizing real-world runtime.
• Easily fits within the constraints where n <= 1000.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
  public:
    int largestSubsquare(vector<vector<char>>& mat) {
        int n = mat.size();
        if (n == 0) return 0;

        // left[i][j]: count of consecutive 'X' ending at mat[i][j] going leftwards
        // top[i][j] : count of consecutive 'X' ending at mat[i][j] going upwards
        vector<vector<int>> left(n, vector<int>(n, 0));
        vector<vector<int>> top(n, vector<int>(n, 0));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (mat[i][j] == 'X') {
                    left[i][j] = (j == 0) ? 1 : left[i][j - 1] + 1;
                    top[i][j]  = (i == 0) ? 1 : top[i - 1][j] + 1;
                }
            }
        }

        int maxSide = 0;

        // Iterate from bottom-right to top-left
        for (int i = n - 1; i >= 0; --i) {
            for (int j = n - 1; j >= 0; --j) {
                int small = min(left[i][j], top[i][j]);

                // Only search for squares larger than currently found maxSide
                while (small > maxSide) {
                    // Check top edge and left edge of the square of side length 'small'
                    if (top[i][j - small + 1] >= small && left[i - small + 1][j] >= small) {
                        maxSide = small;
                        break;
                    }
                    small--;
                }
            }
        }

        return maxSide;
    }
};
