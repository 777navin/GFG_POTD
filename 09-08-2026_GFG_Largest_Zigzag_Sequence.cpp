/*
=========================================================
Date        : 09-08-2026
Problem Name: Largest Zigzag Sequence
Platform    : GFG
Difficulty  : Easy
Tags        : Dynamic Programming, Matrix

Problem Summary:
Given an n x n square matrix, find the maximum sum of a zigzag 
sequence starting from the top row and ending at the bottom row. 
Two consecutive elements in the sequence cannot be from the same column.

Key Observation:
The maximum sum ending at any cell in row `i` only depends on the maximum 
values from row `i-1`, excluding the element in the same column. 
This optimal substructure makes it perfect for Dynamic Programming.
=========================================================
*/

/*
1. Brute Force (Recursive)
   - Intuition: Explore every possible path from the top row to the bottom row.
   - Approach: At each cell, recursively call all cells in the next row except the one in the same column.
   - Why it Works: It exhaustively checks every valid zigzag path to find the absolute maximum.
   - Time Complexity (TC): O(n * (n-1)^(n-1)) - Exponential, will cause TLE for n=100.
   - Space Complexity (SC): O(n) - For the recursive call stack depth.

2. Better (Dynamic Programming with 2D Table)
   - Intuition: Overlapping subproblems exist since multiple paths can converge on the same cell.
   - Approach: Maintain a DP table `dp[n][n]` where `dp[i][j]` stores the max sum path reaching `mat[i][j]`.
   - Why it Works: Memorizing previous row results prevents redundant recalculations.
   - Time Complexity (TC): O(n^3) - Iterating over row, current column, and previous row's columns.
   - Space Complexity (SC): O(n^2) - For the full 2D DP matrix.

3. Most Optimal (Space-Optimized DP)
   - Intuition: To compute values for row `i`, we only need the results from row `i-1`.
   - Approach: Keep two 1D arrays of size `n` (`prevRow` and `currRow`) instead of a full `n x n` matrix.
   - Why it Works: It safely discards older rows that are no longer needed, saving space.
   - Time Complexity (TC): O(n^3)
   - Space Complexity (SC): O(n) - Only tracking two rows of size n.
*/

/*
=========================================================
FINAL APPROACH
=========================================================
We choose the Most Optimal (Space-Optimized DP) approach. 
With n <= 100, O(n^3) time complexity takes only ~10^6 operations, easily 
running within the time limit. Space optimization drops memory requirements 
from O(n^2) down to O(n), representing competitive programming best practices.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int zigzagSequence(vector<vector<int>>& mat) {
        int n = mat.size();
        if (n == 1) return mat[0][0];

        // Track only the previous row's maximum sums
        vector<int> prevRow = mat[0];
        vector<int> currRow(n, 0);

        for (int i = 1; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int max_prev = 0;
                // Find the maximum value from the previous row not in column j
                for (int k = 0; k < n; ++k) {
                    if (k != j) {
                        max_prev = max(max_prev, prevRow[k]);
                    }
                }
                currRow[j] = mat[i][j] + max_prev;
            }
            // Move current row results to previous row for the next iteration
            prevRow = currRow;
        }

        // The answer is the maximum value in the final row
        int ans = 0;
        for (int j = 0; j < n; ++j) {
            ans = max(ans, prevRow[j]);
        }
        
        return ans;
    }
};

// Driver code to test the solution and ensure standalone runnability 
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    vector<vector<int>> mat1 = {
        {3, 1, 2}, 
        {4, 8, 5}, 
        {6, 9, 7}
    };
    cout << "Test Case 1 Output: " << sol.zigzagSequence(mat1) << "\n"; // Expected: 18

    vector<vector<int>> mat2 = {
        {1, 2, 4}, 
        {3, 9, 6}, 
        {11, 3, 15}
    };
    cout << "Test Case 2 Output: " << sol.zigzagSequence(mat2) << "\n"; // Expected: 28

    return 0;
}
