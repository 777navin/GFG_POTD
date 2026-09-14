/*
=========================================================
Date        : 14-09-2026
Problem Name: Shortest Safe Route in Grid
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Graph, Breadth-First Search (BFS), Matrix

Problem Summary:
Find the shortest path length from any cell in the first column to the last column.
Avoid landmines (0s) and all their directly adjacent cells (up, down, left, right).

Key Observation:
Since we can start from multiple valid cells in the first column and need the shortest 
path on an unweighted grid, Multi-Source Breadth-First Search (BFS) is the best choice.
=========================================================

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Multi-Source BFS (Optimal)
   - Intuition: BFS finds the shortest path in an unweighted graph by exploring level by level.
   - Approach:
     * Precompute a boolean matrix to mark all landmines and their 4-directional neighbors as unsafe.
     * Enqueue all safe cells from the first column into the BFS queue with an initial distance of 1.
     * Perform BFS. Move to adjacent valid, unvisited cells and increment the distance.
     * Stop and return the distance the moment a cell in the last column is reached.
   - Why it Works: Starting BFS simultaneously from all valid first-column cells guarantees the shortest absolute path globally.
   - Time Complexity (TC): O(N * M), as each cell is processed at most a constant number of times.
   - Space Complexity (SC): O(N * M), required for the queue, visited array, and safe matrix.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
Multi-source BFS is chosen because it inherently handles multiple starting points and 
finds the optimal path without redundant DFS backtracking. It guarantees the absolute 
shortest route in O(N * M) time.
*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int shortestPath(vector<vector<int>>& mat) {
        int n = mat.size();
        if (n == 0) return -1;
        int m = mat[0].size();
        
        vector<vector<bool>> safe(n, vector<bool>(m, true));
        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};
        
        // Step 1: Mark landmines and their adjacent cells as unsafe
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mat[i][j] == 0) {
                    safe[i][j] = false;
                    for (int k = 0; k < 4; ++k) {
                        int ni = i + dr[k];
                        int nj = j + dc[k];
                        if (ni >= 0 && ni < n && nj >= 0 && nj < m) {
                            safe[ni][nj] = false;
                        }
                    }
                }
            }
        }
        
        // Step 2: Multi-source BFS from the first column
        queue<pair<pair<int, int>, int>> q; // {{row, col}, distance}
        vector<vector<bool>> vis(n, vector<bool>(m, false));
        
        for (int i = 0; i < n; ++i) {
            if (safe[i][0]) {
                q.push({{i, 0}, 1});
                vis[i][0] = true;
            }
        }
        
        while (!q.empty()) {
            auto curr = q.front();
            q.pop();
            
            int r = curr.first.first;
            int c = curr.first.second;
            int dist = curr.second;
            
            // If we've reached the rightmost column, return the distance
            if (c == m - 1) {
                return dist;
            }
            
            // Explore 4 directional neighbors
            for (int k = 0; k < 4; ++k) {
                int nr = r + dr[k];
                int nc = c + dc[k];
                
                if (nr >= 0 && nr < n && nc >= 0 && nc < m && safe[nr][nc] && !vis[nr][nc]) {
                    vis[nr][nc] = true;
                    q.push({{nr, nc}, dist + 1});
                }
            }
        }
        
        // No path found
        return -1;
    }
};
