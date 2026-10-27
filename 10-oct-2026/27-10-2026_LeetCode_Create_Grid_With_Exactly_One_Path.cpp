/*
=========================================================
Date        : 27-10-2026
Problem Name: Create Grid With Exactly One Path
Platform    : LeetCode
Difficulty  : Easy
Tags        : Constructive Algorithms, Grid, Implementation

Problem Summary:
• Construct an m x n grid using '.' and '#'.
• There must be exactly one valid path from (0,0) to (m-1,n-1).
• Movement is allowed only Right or Down.
• Return any valid grid.

Key Observation:
• We only need to keep one possible route open.
• Block every other cell so no alternative path exists.
=========================================================
*/

/*
=========================================================
Approach 1 : Construct a Single L-Shaped Path
=========================================================

Intuition:
• Create only one route from start to destination.
• Go right across the first row, then go down the last column.

Approach:
• Initialize all cells as obstacles '#'.
• Make every cell in the first row '.'.
• Make every cell in the last column '.'.

Why it Works:
• The path is forced:
  Move Right -> Right ... -> Down -> Down ...
• No other free cells exist to create another route.

TC:
• O(m * n)

SC:
• O(m * n)
*/

/*
=========================================================
Final Approach Chosen
=========================================================

• The L-shaped construction is the simplest possible solution.
• It guarantees exactly one valid path.
• No path counting, DP, DFS, or graph traversal is needed.
• Works for all valid constraints directly.
=========================================================
*/

class Solution {
public:
    vector<string> createGrid(int m, int n) {

        vector<string> grid(m, string(n, '#'));

        // Open the entire first row.
        for (int col = 0; col < n; col++) {
            grid[0][col] = '.';
        }

        // Open the entire last column.
        for (int row = 0; row < m; row++) {
            grid[row][n - 1] = '.';
        }

        return grid;
    }
};
