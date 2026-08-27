/*
=========================================================
Date        : 27-08-2026
Problem Name: Largest Rectangle with Column Swaps
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Matrix, Sorting, Dynamic Programming

Problem Summary:
Given a binary matrix of size n x m containing 0s and 1s.
Any pair of columns can be swapped any number of times.
Find the maximum area of a rectangle consisting entirely of 1s.

Key Observation:
Since column swaps are allowed freely, the relative order of columns does not matter.
For each row, we can calculate consecutive 1s ending at that row, sort them descendingly, and compute maximum rectangular areas.
=========================================================
*/

/*
=========================================================
APPROACH 1: Consecutive Heights Calculation + Sorting
=========================================================

• Intuition:
  Treat each cell (i, j) as having a height representing consecutive 1s above it in the same column.
  Since columns can be permuted arbitrarily in any row, sorting these heights for each row brings larger heights together to form the widest possible rectangles.

• Approach:
  1. Build a 2D height matrix `hist[n][m]` where `hist[i][j]` is the number of consecutive 1s ending at `(i, j)`.
  2. For each row `i` from 0 to `n-1`:
     - Extract all heights in row `i` and sort them in non-increasing order (or use count sort since height <= n).
     - For each position `k` (0-indexed) with sorted height `h`, the width is `k + 1`, giving an area of `h * (k + 1)`.
  3. Track and return the maximum area found across all rows.

• Why it Works:
  Swapping columns allows any combination of columns to be adjacent.
  Sorting heights in descending order greedily maximizes width for any chosen height threshold.

• Time Complexity (TC):
  - Height computation: O(n * m)
  - Sorting per row: O(n * m log m) or O(n * (m + n)) using Counting Sort.
  - Overall TC: O(n * m log m)

• Space Complexity (SC):
  - Auxiliary Space: O(n * m) to store histogram heights (can be optimized to O(m)).
=========================================================
*/

/*
=========================================================
APPROACH 2: Counting Sort Optimization (Most Optimal)
=========================================================

• Intuition:
  Heights are bounded between 0 and n, so we can use counting sort / bucket frequency instead of comparison-based sorting for each row to achieve linear time per row.

• Approach:
  1. Maintain an array `hist[m]` representing consecutive 1s in each column up to current row.
  2. For each row `i`, update `hist[j] = (mat[i][j] == 0) ? 0 : hist[j] + 1`.
  3. Count frequencies of each height `0` to `n` in an array `count`.
  4. Iterate from maximum height `n` down to 1, accumulating the number of columns with height >= `h`, and compute `area = h * total_cols`.
  5. Return the maximum area across all rows.

• Why it Works:
  Counting sort leverages the small range of height values [0, n], eliminating the log factor.

• Time Complexity (TC):
  - O(n * (m + n)) or O(n * m) when m and n are comparable.

• Space Complexity (SC):
  - O(m + n) auxiliary space for height tracking and count sort.
=========================================================
*/

/*
=========================================================
FINAL APPROACH SELECTION:
We use the Consecutive Heights + Sorting approach (Approach 1 / Counting Sort).
It runs strictly within the time limits for 1 <= n, m <= 1000 and requires minimal space overhead.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxArea(vector<vector<int>>& mat) {
        int n = mat.size();
        if (n == 0) return 0;
        int m = mat[0].size();

        // Step 1: Precompute consecutive 1s ending at each cell
        vector<vector<int>> hist(n, vector<int>(m, 0));
        for (int j = 0; j < m; j++) {
            hist[0][j] = mat[0][j];
            for (int i = 1; i < n; i++) {
                hist[i][j] = (mat[i][j] == 0) ? 0 : hist[i - 1][j] + 1;
            }
        }

        int max_area = 0;

        // Step 2: For each row, use counting sort to find max rectangle area
        for (int i = 0; i < n; i++) {
            vector<int> count(n + 1, 0);
            for (int j = 0; j < m; j++) {
                count[hist[i][j]]++;
            }

            int cols_seen = 0;
            for (int h = n; h >= 1; h--) {
                cols_seen += count[h];
                max_area = max(max_area, cols_seen * h);
            }
        }

        return max_area;
    }
};
