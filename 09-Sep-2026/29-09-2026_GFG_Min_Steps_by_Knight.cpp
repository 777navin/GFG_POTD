/*
=========================================================
Date        : 29-09-2026
Problem Name: Min Steps by Knight
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Graph, BFS, Breadth-First Search, Shortest Path

Problem Summary:
Given an n x n square chessboard and the initial position (knightPos) and target 
position (targetPos) of a Knight, find the minimum number of steps required 
for the Knight to reach the target position. 1-based indexing is used.

Key Observation:
Since each Knight move has a uniform step weight of 1, finding the minimum steps 
to reach a target node in an unweighted grid graph can be modeled as finding 
the shortest path using Breadth-First Search (BFS).
=========================================================
*/

/*
=========================================================
APPROACH 1: Breadth-First Search (BFS) [Optimal]
=========================================================

• Intuition:
  - Moving on an unweighted grid with standard cost per move naturally forms a 
    graph where each cell is a vertex and each valid knight move is an edge.
  - BFS explores level by level, ensuring that the first time we visit the target 
    cell, we have found the shortest path (minimum steps).

• Approach:
  - Use a queue to perform level-order traversal, starting from the knight's initial position.
  - Track visited cells using a 2D boolean grid or matrix initialized to false.
  - For the current cell, explore all 8 possible L-shaped knight moves.
  - If a move leads to an unvisited cell within the n x n grid, mark it visited 
    and push it into the queue along with its incremented step count.

• Why it Works:
  - Unweighted shortest path problems are guaranteed to yield optimal distances 
    when processed in BFS order because nodes are visited in increasing order of distance.

• Time Complexity (TC):
  - O(N^2) in the worst case, as every cell in the n x n grid is visited at most once.

• Space Complexity (SC):
  - O(N^2) to maintain the visited array and the queue for storing grid coordinates.
=========================================================
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
The BFS approach is selected because it directly guarantees the minimum number of moves 
in an unweighted state-space graph. Simple DFS or dynamic programming does not guarantee 
shortest path efficiency here due to potential cycles and arbitrary movement directions.
=========================================================
*/

#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    int minStepToReachTarget(vector<int>& knightPos, vector<int>& targetPos, int n) {
        int startX = knightPos[0];
        int startY = knightPos[1];
        int targetX = targetPos[0];
        int targetY = targetPos[1];
        
        // If initial position is already the target position
        if (startX == targetX && startY == targetY) {
            return 0;
        }

        // Possible 8 moves for a Knight
        int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};

        // 2D grid to track visited cells (1-based indexing used, so dimension size n + 1)
        vector<vector<bool>> visited(n + 1, vector<bool>(n + 1, false));

        // Queue for BFS storing {x, y, steps}
        queue<pair<pair<int, int>, int>> q;

        // Push start position and mark visited
        q.push({{startX, startY}, 0});
        visited[startX][startY] = true;

        while (!q.empty()) {
            auto current = q.front();
            q.pop();

            int currX = current.first.first;
            int currY = current.first.second;
            int steps = current.second;

            // Check all 8 possible moves
            for (int i = 0; i < 8; ++i) {
                int nextX = currX + dx[i];
                int nextY = currY + dy[i];

                // If target reached
                if (nextX == targetX && nextY == targetY) {
                    return steps + 1;
                }

                // Check bounds and whether it's visited
                if (nextX >= 1 && nextX <= n && nextY >= 1 && nextY <= n && !visited[nextX][nextY]) {
                    visited[nextX][nextY] = true;
                    q.push({{nextX, nextY}, steps + 1});
                }
            }
        }

        return -1; // Unreachable destination
    }
};
