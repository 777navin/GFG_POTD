/*
=========================================================
Date        : 16-07-2026
Problem Name: Numbers with Given Digit Sum
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Recursion, Memoization

Problem Summary:
Find the total number of n-digit positive integers (without 
leading zeros) whose digits add up to a specific given sum.
Return -1 if no such number can be formed.

Key Observation:
This is a classical combinatorics problem where each digit choice 
restricts the remaining sum. Since the subproblems overlap (e.g., 
needing a sum of S with D digits left can be reached via multiple 
paths), Dynamic Programming perfectly optimizes the search space.
=========================================================

=========================================================
APPROACH EXPLANATIONS
=========================================================

1. Brute Force (Recursion)
   - Intuition: Try all valid digit combinations.
   - Approach: Pick a digit for the current position and recursively 
     solve for the remaining digits and remaining sum.
   - Why it Works: Exhaustively searches all possible n-digit numbers.
   - Time Complexity (TC): O(10^n) - Exponential, as it branches up to 10 times per digit.
   - Space Complexity (SC): O(n) - For the recursion stack.

2. Optimized (Dynamic Programming / Memoization)
   - Intuition: Overlapping subproblems exist (same remaining sum and digits left).
   - Approach: Cache the results of `solve(digits_left, current_sum)` in a 2D DP array.
   - Why it Works: Avoids redundant calculations by directly returning precomputed results.
   - Time Complexity (TC): O(n * sum * 10) - State space is n * sum, and we loop 10 times per state.
   - Space Complexity (SC): O(n * sum) - Auxiliary space for the 2D DP table and recursion stack.

=========================================================
FINAL APPROACH
=========================================================
- The Memoization approach is chosen because the constraints are 
  small (n <= 9, sum <= 81). 
- It drastically reduces the exponential time complexity of the 
  Brute Force method down to polynomial time, passing easily 
  within execution time limits.
*/

#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

class Solution {
private:
    int dp[10][82];
    
    // Helper function to calculate ways for remaining digits
    int solve(int n, int sum) {
        // Base cases
        if (n == 0) {
            return (sum == 0) ? 1 : 0;
        }
        if (sum < 0) {
            return 0;
        }
        
        // Return precomputed result if available
        if (dp[n][sum] != -1) {
            return dp[n][sum];
        }
        
        int ways = 0;
        // The remaining digits can be anything from 0 to 9
        for (int i = 0; i <= 9; i++) {
            if (sum - i >= 0) {
                ways += solve(n - 1, sum - i);
            }
        }
        
        return dp[n][sum] = ways;
    }

public:
    int countWays(int n, int sum) {
        // Initialize DP table with -1
        memset(dp, -1, sizeof(dp));
        
        int totalWays = 0;
        
        // The first digit cannot be 0 (must be 1-9)
        for (int i = 1; i <= 9; i++) {
            if (sum - i >= 0) {
                totalWays += solve(n - 1, sum - i);
            }
        }
        
        // Return -1 if no such number exists, otherwise return the calculated ways
        return (totalWays == 0) ? -1 : totalWays;
    }
};
