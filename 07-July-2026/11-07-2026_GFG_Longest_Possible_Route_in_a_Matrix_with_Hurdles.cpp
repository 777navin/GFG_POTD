/*
=========================================================
Date        : 11-07-2026
Problem Name: Longest Possible Route in a Matrix with Hurdles
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : DFS, Backtracking, Matrix, Graph

Problem Summary:
Given a binary matrix with 1s (path) and 0s (hurdles), find the longest path length 
from a source (xs, ys) to a destination (xd, yd) without visiting the same cell twice.

Key Observation:
Since we need the "longest" simple path in a grid where cycles are possible, 
backtracking is necessary to explore all valid paths.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

/*
Approach: Backtracking (DFS)

1. Intuition:
   - To find the longest path, we must explore all possible non-repeating paths.
   - DFS naturally explores paths until it hits a wall or the destination.

2. Approach:
   - Start DFS from (xs, ys).
   - Keep track of visited cells to ensure no cell is revisited.
   - If destination is reached, update the maximum path length found so far.
   - After visiting a cell, unmark it (backtrack) to allow other paths to use it.

3. Why it Works:
   - It exhaustively explores all valid, non-self-intersecting paths in the grid.

4. Time Complexity (TC):
   - O(3^(N*M)) in the worst case, as at each cell we can move in at most 3 directions 
     (excluding the one we came from).

5. Space Complexity (SC):
   - O(N*M) due to the recursion stack and the visited matrix.
*/

class Solution {
public:
    int longestPath(vector<vector<int>>& mat, int xs, int ys, int xd, int yd) {
        int n = mat.size();
        int m = mat[0].size();
        
        // If source or destination is blocked, no path exists
        if (mat[xs][ys] == 0 || mat[xd][yd] == 0) return -1;
        
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        int maxLen = -1;
        
        solve(mat, xs, ys, xd, yd, 0, maxLen, visited);
        
        return maxLen;
    }

private:
    void solve(vector<vector<int>>& mat, int i, int j, int xd, int yd, int currDist, int& maxLen, vector<vector<bool>>& visited) {
        // Base case: Reached destination
        if (i == xd && j == yd) {
            maxLen = max(maxLen, currDist);
            return;
        }
        
        // Mark current cell as visited
        visited[i][j] = true;
        
        // Directions: Up, Down, Left, Right
        int dx[] = {-1, 1, 0, 0};
        int dy[] = {0, 0, -1, 1};
        
        for (int k = 0; k < 4; k++) {
            int ni = i + dx[k];
            int nj = j + dy[k];
            
            // Check boundaries, if cell is traversable and not visited
            if (ni >= 0 && ni < mat.size() && nj >= 0 && nj < mat[0].size() && 
                mat[ni][nj] == 1 && !visited[ni][nj]) {
                solve(mat, ni, nj, xd, yd, currDist + 1, maxLen, visited);
            }
        }
        
        // Backtrack: Unmark cell for other possible paths
        visited[i][j] = false;
    }
};

/*
Final Approach Explanation:
- Backtracking is chosen because finding the longest simple path in a graph is an NP-hard problem.
- Given the small constraints (1 <= n, m <= 10), backtracking is efficient enough to explore the state space.
- This is the optimal approach for this specific problem size, as it guarantees finding the longest path.
*/

// 11-07-2026_GFG_Longest_Possible_Route_in_a_Matrix_with_Hurdles.cpp
