/*
=========================================================
Date        : 08-07-2026
Problem Name: Towers Reaching Both Stations (Geeks Island)
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Matrix, Graph, DFS, BFS

Problem Summary:
Given an n x m matrix representing signal strengths of towers. Two control stations P (top & left boundaries) and Q (bottom & right boundaries) monitor the network. A signal can flow from a tower to a 4-directional neighbor only if the neighbor's strength is less than or equal to the current tower's strength. Find the total number of towers that can transmit signals to both Station P and Station Q.

Key Observation:
Instead of simulating flow downwards from every single cell, reverse the flow. Start from the boundaries (Station P and Station Q) and move "upwards" to higher or equal signal strengths using Multi-source DFS/BFS. The intersection of cells reachable from both stations gives the answer.
=========================================================
*/

#include <vector>

using namespace std;

/*
=========================================================
APPROACH 1: Multi-Source DFS from Boundaries (Optimized)
=========================================================
• Intuition:
  Flowing from cells to boundaries for each cell would take O((N*M)^2) time (Brute Force). By reversing the logic, water/signals can flow from the boundaries to higher or equal height inland towers.
  
• Approach:
  1. Maintain two boolean matrices/grids: `reachP` and `reachQ` initialized to false.
  2. Run DFS for Station P from the top row (0, j) and left column (i, 0).
  3. Run DFS for Station Q from the bottom row (n-1, j) and right column (i, m-1).
  4. In the DFS traversal, only move to a neighbor if its signal strength is greater than or equal to the current cell's strength and it hasn't been visited yet.
  5. Count all coordinates where both `reachP[i][j]` and `reachQ[i][j]` are true.

• Why it Works:
  If a boundary cell can reach an inland cell by moving to greater-than-or-equal heights, it implies that the inland cell can naturally flow down to that boundary cell following the strictly decreasing/equal path rules.

• Time Complexity (TC) : O(n * m) - Each cell is visited at most a constant number of times during the DFS traversals.
• Space Complexity (SC): O(n * m) - To maintain the reachability matrices and the recursion stack.
=========================================================
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
• The reversed Multi-Source DFS approach is chosen because it avoids redundant cell traversals, optimizing the time complexity from an inefficient O((N*M)^2) to a highly optimal O(N*M), which comfortably passes within the 10^3 constraint limits.
=========================================================
*/

class Solution {
private:
    int n, m;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    void dfs(int r, int c, vector<vector<int>>& mat, vector<vector<bool>>& visited) {
        visited[r][c] = true;
        
        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i];
            int nc = c + dy[i];
            
            // Boundary checks and validation for reverse flow (neighbor >= current)
            if (nr >= 0 && nr < n && nc >= 0 && nc < m && !visited[nr][nc] && mat[nr][nc] >= mat[r][c]) {
                dfs(nr, nc, mat, visited);
            }
        }
    }

public:
    int countCoordinates(vector<vector<int>>& mat) {
        if (mat.empty() || mat[0].empty()) return 0;
        
        n = mat.size();
        m = mat[0].size();
        
        vector<vector<bool>> reachP(n, vector<bool>(m, false));
        vector<vector<bool>> reachQ(n, vector<bool>(m, false));
        
        // Multi-source DFS from Top and Bottom boundaries
        for (int j = 0; j < m; ++j) {
            dfs(0, j, mat, reachP);     // Top boundary for Station P
            dfs(n - 1, j, mat, reachQ); // Bottom boundary for Station Q
        }
        
        // Multi-source DFS from Left and Right boundaries
        for (int i = 0; i < n; ++i) {
            dfs(i, 0, mat, reachP);     // Left boundary for Station P
            dfs(i, m - 1, mat, reachQ); // Right boundary for Station Q
        }
        
        // Count common intersections
        int count = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (reachP[i][j] && reachQ[i][j]) {
                    count++;
                }
            }
        }
        
        return count;
    }
};
