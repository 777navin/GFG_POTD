/*
Date: 18-05-2026
Problem Name: Maximum Sum Problem
Platform: GeeksforGeeks (GFG)
Difficulty: Easy
Tags: Dynamic Programming, Recursion, Memoization

Problem Summary:
Given a number 'n', we need to find its maximum sum value obtained by recursively 
breaking it into three parts: floor(n/2), floor(n/3), and floor(n/4). At each step, 
we can either choose to divide the number further or take its current value, 
whichever yields a larger sum.

Methods to Solve:

1. Brute Force (Pure Recursion)
- Intuition: Directly simulate the problem statement by recursively computing the 
  maximum sum for n/2, n/3, and n/4, and comparing their combined sum with n.
- Approach: Define a recursive function `solve(n)` that returns `max(n, solve(n/2) + solve(n/3) + solve(n/4))` 
  with a base case where `n = 0` returns 0.
- Dry Run (n = 12):
  solve(12) = max(12, solve(6) + solve(4) + solve(3))
  - solve(6) = max(6, solve(3) + solve(2) + solve(1)) -> returns 6
  - solve(4) = max(4, solve(2) + solve(1) + solve(1)) -> returns 4
  - solve(3) = max(3, solve(1) + solve(1) + solve(0)) -> returns 3
  solve(12) = max(12, 6 + 4 + 3) = max(12, 13) = 13.
- Time Complexity: O(3^(log_2(n))) ≈ O(n^1.58) due to redundant overlapping subproblems.
- Space Complexity: O(log n) for the recursion call stack.
- Why better than previous method: N/A (Baseline approach).
- When to use: Only for extremely small values of n where overhead tracking is unnecessary.

2. Better Approach (Top-Down DP / Memoization)
- Intuition: The recursive tree contains massive overlapping subproblems (e.g., solve(2) 
  is called multiple times). Caching these values prevents redundant computations.
- Approach: Use an array or hash map `dp` initialized with -1. Before making recursive 
  calls for `n`, check if `dp[n]` is already calculated. If yes, return it.
- Dry Run (n = 12): Same branching structure as recursion, but once solve(3) or solve(2) 
  is computed, its value is retrieved in O(1) time for subsequent calls.
- Time Complexity: O(n) as each state from 0 to n is computed exactly once.
- Space Complexity: O(n) for the memoization table + O(log n) for the recursion stack.
- Why better than previous method: Drastically cuts down execution time from exponential to linear.
- When to use: When you want an intuitive translation from recursive logic with a limited recursion depth.

3. Optimal Approach (Bottom-Up DP / Tabulation)
- Intuition: Eliminate recursion stack overhead entirely by filling a table iteratively 
  from base cases (0) up to the target value `n`.
- Approach: Create a DP table of size `n + 1`. Initialize `dp[0] = 0`. Run a loop from 
  1 to n and compute `dp[i] = max(i, dp[i/2] + dp[i/3] + dp[i/4])`. The answer will be at `dp[n]`.
- Dry Run (n = 12):
  dp[0] = 0, dp[1] = 1, dp[2] = 2 ... dp[12] = max(12, dp[6] + dp[4] + dp[3]) = max(12, 6 + 4 + 3) = 13.
- Time Complexity: O(n)
- Space Complexity: O(n) for the DP array storage.
- Why better than previous method: Avoids call stack overflow risks and recursive overhead.
- When to use: Ideal for linear constraints up to 10^6 where an array allocation is efficient.

Comparison Table:
Method         | TC          | SC          | Best Use Case
----------------------------------------------------------------------
Brute Force    | O(n^1.58)   | O(log n)    | Small n (n < 12)
Memoization    | O(n)        | O(n)        | Sparse subproblem evaluation
Tabulation     | O(n)        | O(n)        | Standard iterative linear constraints

Final Recommended Solution: Bottom-Up Tabulation for maximum execution stability.
*/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int maxSum(int n) {
        // Base case handling for zero
        if (n == 0) return 0;
        
        // DP table allocation up to n
        std::vector<int> dp(n + 1, 0);
        
        // Base transitions: for values less than 12, breaking them down
        // yields a sum less than or equal to the number itself.
        for (int i = 1; i <= n; ++i) {
            int breakSum = dp[i / 2] + dp[i / 3] + dp[i / 4];
            dp[i] = std::max(i, breakSum);
        }
        
        return dp[n];
    }
};
