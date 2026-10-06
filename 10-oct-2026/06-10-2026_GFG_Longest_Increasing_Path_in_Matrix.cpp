/*
=========================================================
Date        : 06-10-2026
Problem Name: Longest Increasing Path in Matrix
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Dynamic Programming, Depth-First Search (DFS), Memoization, Matrix, Graph

Problem Summary:
Given an n x m matrix of integers, find the length of the longest strictly 
increasing path. From any cell, you can move up, down, left, or right. 
No cell can be revisited in a single path, and moving out of bounds or 
diagonally is not allowed.

Key Observation:
Since the path must be strictly increasing, there are no directed cycles in 
the implied state graph. This allows using Depth-First Search with Memoization 
(or Topological Sorting) to avoid recomputing the longest path starting from 
any cell (i, j).
=========================================================
*/

#include <bits/stdc++.h>
using std::vector;
using std::max;

/*
=========================================================
APPROACH 1: Pure DFS (Brute Force)
=========================================================
• Intuition:
  - Explore all possible strictly increasing paths from every cell using 
    recursion and return the maximum path length found.

• Approach:
  - Iterate through each cell (i, j) in the matrix as a potential starting point.
  - From cell (i, j), recursively traverse in all 4 cardinal directions where 
    the neighboring cell value is strictly greater than matrix[i][j].
  - Track the maximum path length reached from all paths.

• Why it Works:
  - It exhaustively explores every valid increasing path in the grid to guarantee 
    finding the maximum length.

• Time Complexity (TC):
  - O(4^(N * M)) in the worst case, due to overlapping subproblems evaluated repeatedly.

• Space Complexity (SC):
  - O(N * M) auxiliary recursion stack space in the worst case.
*/

/*
=========================================================
APPROACH 2: DFS with Memoization / Dynamic Programming (Optimal)
=========================================================
• Intuition:
  - The length of the longest increasing path starting at cell (i, j) is constant. 
    Once computed, we can store (memoize) this result to reuse in future paths.

• Approach:
  - Maintain a 2D memoization table `memo` initialized to -1, where `memo[i][j]` 
    stores the length of the longest increasing path starting at (i, j).
  - For each cell (i, j), call a recursive helper `dfs(i, j)`.
  - If `memo[i][j]` is already computed, return it immediately.
  - Otherwise, explore 4 neighbors (up, down, left, right). For any valid neighbor 
    with a strictly greater value, compute 1 + dfs(neighbor) and update the local max.
  - Store the result in `memo[i][j]` and return it.
  - Take the overall maximum of `memo[i][j]` across all cells in the matrix.

• Why it Works:
  - Strict increase guarantees DAG (Directed Acyclic Graph) structure, preventing 
    infinite loops or back-and-forth cycles without explicit visited arrays.

• Time Complexity (TC):
  - O(N * M), because each cell and its edges are processed a constant number of times.

• Space Complexity (SC):
  - O(N * M) for the memoization table and recursive call stack.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
• Chosen Approach: DFS with Memoization (Approach 2)
• Why Chosen:
  - DFS with memoization reduces time complexity from exponential O(4^(N*M)) 
    to linear O(N * M) relative to grid size.
  - It naturally handles strict monotonicity without requiring complex topological 
    sorting constructs or graph building overhead.
=========================================================
*/

class Solution {
private:
    int n, m;
    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    int dfs(int r, int c, const vector<vector<int>>& matrix, vector<vector<int>>& memo) {
        if (memo[r][c] != -1) {
            return memo[r][c];
        }

        int maxLen = 1;

        for (int i = 0; i < 4; ++i) {
            int nr = r + dx[i];
            int nc = c + dy[i];

            if (nr >= 0 && nr < n && nc >= 0 && nc < m && matrix[nr][nc] > matrix[r][c]) {
                maxLen = max(maxLen, 1 + dfs(nr, nc, matrix, memo));
            }
        }

        return memo[r][c] = maxLen;
    }

public:
    int longIncPath(vector<vector<int>>& matrix, int n, int m) {
        this->n = n;
        this->m = m;

        if (n == 0 || m == 0) return 0;

        vector<vector<int>> memo(n, vector<int>(m, -1));
        int maxLength = 0;

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                maxLength = max(maxLength, dfs(i, j, matrix, memo));
            }
        }

        return maxLength;
    }
};
