/*
=========================================================
Date        : 25-07-2026
Problem Name: Max Sum Square Sub-Matrix of Size k
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Matrix, 2D Prefix Sum, Sliding Window

Problem Summary:
Given an n x n 2D grid containing integers (which can be negative),
find the maximum sum of any k x k square sub-grid.

Key Observation:
Instead of recalculating the sum of each k x k sub-matrix from scratch,
a 2D Prefix Sum array allows computing the sum of any sub-matrix in O(1) time.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Brute Force
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - Iterate over every possible top-left cell of a k x k sub-matrix and sum all elements inside.

• Approach:
  - Fix top-left corner at (i, j) where 0 <= i, j <= n - k.
  - Use nested loops to sum all k x k elements and track the maximum sum encountered.

• Why it Works:
  - It checks every valid sub-matrix of size k x k exhaustively.

• Time Complexity (TC) : O(n^2 * k^2)
• Space Complexity (SC): O(1)


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Optimized (2D Prefix Sum)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - By preprocessing the matrix into a 2D prefix sum array, the sum of any rectangular sub-grid
    can be computed using Inclusion-Exclusion Principle in constant time.

• Approach:
  - Create a 2D prefix sum table pref of size (n+1) x (n+1).
  - Fill pref[i][j] = mat[i-1][j-1] + pref[i-1][j] + pref[i][j-1] - pref[i-1][j-1].
  - Query each k x k sub-matrix sum ending at (i, j) using:
    sum = pref[i][j] - pref[i-k][j] - pref[i][j-k] + pref[i-k][j-k].
  - Track and return the maximum sum found.

• Why it Works:
  - 2D Prefix Sum precalculates cumulative region sums, avoiding repetitive additions across overlapping regions.

• Time Complexity (TC) : O(n^2)
• Space Complexity (SC): O(n^2)
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH CHOICE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• We choose Approach 2 (2D Prefix Sum).
• It reduces the query time for each sub-grid from O(k^2) to O(1).
• This lowers the total runtime complexity from O(n^2 * k^2) to O(n^2), which comfortably passes within time limits for n <= 1000.
*/

#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int maximumSum(std::vector<std::vector<int>>& mat, int k) {
        int n = mat.size();
        
        // Construct 2D Prefix Sum array (1-indexed for easy boundary checks)
        std::vector<std::vector<int>> pref(n + 1, std::vector<int>(n + 1, 0));
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                pref[i + 1][j + 1] = mat[i][j] 
                                   + pref[i][j + 1] 
                                   + pref[i + 1][j] 
                                   - pref[i][j];
            }
        }
        
        int maxSum = INT_MIN;
        
        // Iterate through all k x k sub-grid bottom-right positions
        for (int i = k; i <= n; i++) {
            for (int j = k; j <= n; j++) {
                int currentSum = pref[i][j] 
                               - pref[i - k][j] 
                               - pref[i][j - k] 
                               + pref[i - k][j - k];
                maxSum = std::max(maxSum, currentSum);
            }
        }
        
        return maxSum;
    }
};
