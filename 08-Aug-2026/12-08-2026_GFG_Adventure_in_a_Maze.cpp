/*
=========================================================
Date        : 12-08-2026
Problem Name: Adventure in a Maze
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Dynamic Programming, Matrix, Graph

Problem Summary:
Given an N x N grid where cells have values 1 (Right), 2 (Down), 
or 3 (Right and Down), find the total number of valid paths 
from (0,0) to (n-1, n-1) and the maximum path sum (adventure).

Key Observation:
Reaching a cell (i, j) only depends on its valid top (i-1, j) 
and left (i, j-1) neighbors, making this a perfect DP problem.
=========================================================
*/

/*
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━

1. Brute Force (DFS / Recursion)
• Intuition: Try all possible paths starting from (0,0) to the destination.
• Approach: Recursively move Right or Down if the current cell's value allows it.
• Why it Works: It exhaustively checks every valid path to count ways and find the max sum.
• Time Complexity (TC): O(2^(2N)) - Exponential due to branching at each step.
• Space Complexity (SC): O(N) - Recursion stack space.

2. Optimized (Dynamic Programming)
• Intuition: Overlapping subproblems exist since multiple paths can converge on the same cell.
• Approach: Use two 2D arrays, `paths` to count ways and `maxAdv` to track the max sum up to (i,j).
• Why it Works: Computes results cell-by-cell sequentially, eliminating redundant calculations.
• Time Complexity (TC): O(N^2) - We iterate through the N x N grid exactly once.
• Space Complexity (SC): O(N^2) - For storing the `paths` and `maxAdv` DP states.
*/

/*
FINAL APPROACH
━━━━━━━━━━━━━━
The Dynamic Programming approach is chosen because the DFS approach will result 
in a Time Limit Exceeded (TLE) error for larger grids. Given N <= 100, an O(N^2) 
DP solution easily runs within the time constraints and securely computes both 
the path count and maximum adventure sum simultaneously.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> findWays(vector<vector<int>>& grid) {
        int n = grid.size();
        long long MOD = 1e9 + 7;
        
        // DP tables to store number of paths and maximum adventure
        vector<vector<long long>> paths(n, vector<long long>(n, 0));
        vector<vector<int>> maxAdv(n, vector<int>(n, 0));
        
        // Base initialization for the entry point
        paths[0][0] = 1;
        maxAdv[0][0] = grid[0][0];
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                // Skip the starting cell
                if (i == 0 && j == 0) continue;
                
                long long ways = 0;
                int mx = 0;
                
                // Check if we can reach (i, j) from the Top (i-1, j)
                if (i > 0 && paths[i - 1][j] > 0 && (grid[i - 1][j] == 2 || grid[i - 1][j] == 3)) {
                    ways = (ways + paths[i - 1][j]) % MOD;
                    mx = max(mx, maxAdv[i - 1][j]);
                }
                
                // Check if we can reach (i, j) from the Left (i, j-1)
                if (j > 0 && paths[i][j - 1] > 0 && (grid[i][j - 1] == 1 || grid[i][j - 1] == 3)) {
                    ways = (ways + paths[i][j - 1]) % MOD;
                    mx = max(mx, maxAdv[i][j - 1]);
                }
                
                // If the cell is reachable, update its state
                if (ways > 0) {
                    paths[i][j] = ways;
                    maxAdv[i][j] = mx + grid[i][j];
                }
            }
        }
        
        // If there are no paths to the exit, return {0, 0}
        if (paths[n - 1][n - 1] == 0) {
            return {0, 0};
        }
        
        return {(int)paths[n - 1][n - 1], maxAdv[n - 1][n - 1]};
    }
};
