// 14-06-2026_GFG_Exit_Point_in_a_Matrix.cpp

/*
Date: 14-06-2026
Problem Name: Exit Point in a Matrix
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Array, Matrix, Simulation

Problem Summary:
Given a matrix of size n x m consisting of 0s and 1s, start at (0, 0) moving right.
- If cell is 0, continue in the same direction.
- If cell is 1, turn 90 degrees clockwise and set the cell to 0.
Find the coordinates [row, col] where you exit the matrix.

Methods to Solve:
1. Simulation Approach (Optimal)

For Simulation Approach:
- Intuition: Keep track of current position (i, j) and current direction (dr, dc). 
  Use a direction array to handle turns easily.
- Approach:
  - Directions: Right (0, 1), Down (1, 0), Left (0, -1), Up (-1, 0).
  - Use a variable `dir` to store current direction index (0 to 3).
  - If current cell is 1, update `dir = (dir + 1) % 4` and set mat[i][j] = 0.
  - Move to next cell `(i + dr, j + dc)`.
  - Keep track of the last valid cell inside the matrix before moving out.
- Dry Run: 
  Start (0,0), move Right -> (0,1) is 1, turn Down, mat[0][1]=0 -> move (1,1) is 1, turn Left, mat[1][1]=0 -> move (1,0) is 0 -> move (1,-1) [EXIT]. Last valid [1,0].
- Time Complexity: O(n * m) - In worst case, we visit cells.
- Space Complexity: O(1) - No extra space used.

Comparison Table:
Method | TC | SC | Best Use Case
Simulation | O(n*m) | O(1) | Standard approach for matrix traversal problems

Final Recommended Solution: Simulation
*/

#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    vector<int> exitPoint(vector<vector<int>>& mat) {
        int n = mat.size();
        int m = mat[0].size();
        
        // Direction vectors: Right, Down, Left, Up
        int dr[] = {0, 1, 0, -1};
        int dc[] = {1, 0, -1, 0};
        
        int i = 0, j = 0; // Current position
        int dir = 0;      // Current direction: 0:Right, 1:Down, 2:Left, 3:Up
        
        int prevI = 0, prevJ = 0;
        
        while (i >= 0 && i < n && j >= 0 && j < m) {
            prevI = i;
            prevJ = j;
            
            if (mat[i][j] == 1) {
                // Change direction clockwise
                dir = (dir + 1) % 4;
                // Update cell value
                mat[i][j] = 0;
            }
            
            // Move in current direction
            i += dr[dir];
            j += dc[dir];
        }
        
        return {prevI, prevJ};
    }
};
