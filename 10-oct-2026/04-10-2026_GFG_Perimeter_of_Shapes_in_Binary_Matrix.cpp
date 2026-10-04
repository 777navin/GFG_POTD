/*
=========================================================
Date        : 04-10-2026
Problem Name: Perimeter of Shapes in Binary Matrix
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Matrix, Arrays, Matrix Traversal

Problem Summary:
Given an n x m binary matrix, calculate the total perimeter of the shapes formed by 1s.
A standalone cell of 1 has a perimeter of 4, but adjacent 1s share sides, which do not count towards the perimeter.

Key Observation:
Each 1 cell can contribute up to 4 to the perimeter. For every neighbor (up, down, left, right) that is also a 1, one exposed edge is lost.
=========================================================

1. Matrix Traversal (Optimal)

• Intuition
  Instead of complex component finding, we can evaluate each cell individually. The perimeter is simply the count of exposed edges for all 1s.

• Approach
  - Iterate through every cell (i, j) in the matrix.
  - If the cell contains a 1, check its 4 immediate neighbors (top, bottom, left, right).
  - For each neighbor that is either out of bounds (matrix edge) or contains a 0, increment the perimeter count by 1.

• Why it Works
  By counting the boundaries where a 1 meets a 0 or the grid boundary, we exactly compute the external perimeter of all shapes without double-counting shared internal edges.

• Time Complexity (TC)
  O(n * m) - We visit each cell in the n x m matrix exactly once.

• Space Complexity (SC)
  O(1) - No extra space is required aside from a few variables.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• The optimal matrix traversal is chosen.
• It solves the problem in a single pass achieving O(n*m) time complexity.
• It avoids the overhead of graph traversal algorithms (like BFS/DFS) and uses constant O(1) memory.
*/

#include <vector>

using namespace std;

class Solution {
public:
    int findPerimeter(vector<vector<int>> &mat) {
        int n = mat.size();
        if (n == 0) return 0;
        int m = mat[0].size();
        
        int perimeter = 0;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (mat[i][j] == 1) {
                    // Check Top
                    if (i == 0 || mat[i - 1][j] == 0) {
                        perimeter++;
                    }
                    // Check Bottom
                    if (i == n - 1 || mat[i + 1][j] == 0) {
                        perimeter++;
                    }
                    // Check Left
                    if (j == 0 || mat[i][j - 1] == 0) {
                        perimeter++;
                    }
                    // Check Right
                    if (j == m - 1 || mat[i][j + 1] == 0) {
                        perimeter++;
                    }
                }
            }
        }
        
        return perimeter;
    }
};
