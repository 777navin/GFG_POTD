/*
Date: 06-06-2026
Problem Name: Non-Attacking Black and White Knights
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Combinatorics, Chessboard, Mathematics

Problem Summary:
Given dimensions n x m of a chessboard, find the number of ways to place one black knight and one white knight such that they do not attack each other. 
A knight attacks if it moves in an 'L' shape (2 squares in one cardinal direction and 1 in the perpendicular direction). Knights must be on different squares.

Methods to Solve:
1. Combinatorial Counting (Optimal)

For the Method:
- Intuition: 
  The total number of ways to place two distinct knights on an n x m board is (n*m) * (n*m - 1). 
  We need to subtract the number of ways they can attack each other. A knight at (i, j) can attack 8 possible positions. 
  Instead of iterating all, we count the number of 2x3 and 3x2 rectangles in the grid, as each contains 2 pairs of attacking positions.
  
- Approach:
  1. Total ways = (n * m) * (n * m - 1)
  2. Total attacking positions = 4 * (n - 1) * (m - 2) + 4 * (n - 2) * (m - 1)
  3. Result = Total ways - Total attacking positions
  
- Time Complexity: O(1)
- Space Complexity: O(1)

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Math   | O(1)| O(1)| Always (optimal for constraints)

Final Recommended Solution
*/

#include <iostream>

class Solution {
public:
    /**
     * Calculates the number of ways to place two non-attacking knights.
     * @param n Number of rows
     * @param m Number of columns
     * @return Number of ways
     */
    long long numOfWays(int n, int m) {
        // Total ways to place two knights on distinct squares
        long long total_cells = (long long)n * m;
        long long total_ways = total_cells * (total_cells - 1);

        // Calculate attacking positions
        // A knight can attack from a 2x3 or 3x2 block.
        // For each 2x3 block, there are 2 attacking pairs.
        // For each 3x2 block, there are 2 attacking pairs.
        long long attacking_ways = 0;
        
        if (n >= 1 && m >= 2) {
            attacking_ways += 4LL * (n - 1) * (m - 2);
        }
        if (n >= 2 && m >= 1) {
            attacking_ways += 4LL * (n - 2) * (m - 1);
        }

        return total_ways - attacking_ways;
    }
};

// Driver Code for local testing
int main() {
    Solution sol;
    int n = 2, m = 2;
    std::cout << "Ways for " << n << "x" << m << ": " << sol.numOfWays(n, m) << std::endl;
    return 0;
}
