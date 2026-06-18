/*
Date: 18-06-2026
Problem Name: 18-06-2026_GFG_Coverage_of_all_zeros_in_a_binary_matrix.cpp
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Array, Matrix, Simulation

Problem Summary:
Given a binary matrix, find the total coverage of all zeros.
Coverage of a particular 0 is defined by the presence of at least one '1' 
in its four directions (left, right, up, down) before reaching the matrix boundary.
Since we only count a direction once (even if there are multiple 1s), the maximum 
coverage for a single '0' cell is 4.

Methods to Solve:
1. Simulation with Early Termination (Optimal):
   - For every '0', scan outward in all 4 directions.
   - If a '1' is encountered, increase the coverage count and `break` out of that direction's loop to avoid overcounting.

Comparison Table:
Method             | TC            | SC    | Best Use Case
-------------------|---------------|-------|-------------------------
Simulation         | O(N*M*(N+M))  | O(1)  | Direct, optimally handles given constraints

Final Recommended Solution:
Adding a `break` statement ensures we don't overcount multiple 1s in the same direction, which perfectly resolves the previous test case failure (5 vs 7).
*/

#include <vector>

class Solution {
public:
    long long findCoverage(std::vector<std::vector<int>>& matrix) {
        int n = matrix.size();
        if (n == 0) return 0;
        int m = matrix[0].size();
        
        long long totalCoverage = 0;
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                // We only calculate coverage for cells containing 0
                if (matrix[i][j] == 0) {
                    
                    // 1. Check Left
                    for (int k = j - 1; k >= 0; --k) {
                        if (matrix[i][k] == 1) {
                            totalCoverage++;
                            break; // Stop after finding the first 1 in this direction
                        }
                    }
                    
                    // 2. Check Right
                    for (int k = j + 1; k < m; ++k) {
                        if (matrix[i][k] == 1) {
                            totalCoverage++;
                            break; // Stop after finding the first 1 in this direction
                        }
                    }
                    
                    // 3. Check Up
                    for (int k = i - 1; k >= 0; --k) {
                        if (matrix[k][j] == 1) {
                            totalCoverage++;
                            break; // Stop after finding the first 1 in this direction
                        }
                    }
                    
                    // 4. Check Down
                    for (int k = i + 1; k < n; ++k) {
                        if (matrix[k][j] == 1) {
                            totalCoverage++;
                            break; // Stop after finding the first 1 in this direction
                        }
                    }
                    
                }
            }
        }
        return totalCoverage;
    }
};
