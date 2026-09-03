/*
=========================================================
Date        : 03-09-2026
Problem Name: Max Adjacent Diffs Sum with 1 Replacements
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Dynamic Programming, Arrays

Problem Summary:
Given an integer array arr, replace any number of elements with 1.
Find the maximum possible sum of absolute differences between consecutive elements.
Constraints: 1 <= arr.size() <= 10^5.

Key Observation:
For each element arr[i], to maximize absolute differences with its neighbors,
it is always optimal to choose either its original value arr[i] or 1.
=========================================================
*/

/*
=========================================================
APPROACH 1: Brute Force (Recursion)
=========================================================
• Intuition:
  At each position i, we have 2 choices: keep arr[i] or change it to 1.
• Approach:
  Recursively try both choices for each element and calculate the sum of adjacent differences.
• Why it Works:
  Explores the full state space of 2^N possible array configurations.
• Time Complexity (TC): O(2^N) - Exponential branching at each element.
• Space Complexity (SC): O(N) - Recursion call stack depth.

=========================================================
APPROACH 2: Dynamic Programming with Memoization (Top-Down)
=========================================================
• Intuition:
  The choice for index i only depends on the choice made at index i - 1.
• Approach:
  Define memo[i][prev_state] where prev_state is 0 (arr[i-1] was replaced by 1) or 1 (arr[i-1] remained original).
• Why it Works:
  Eliminates redundant overlapping subproblems across recursive branches.
• Time Complexity (TC): O(N) - 2 * N distinct states computed once.
• Space Complexity (SC): O(N) - DP table of size N x 2 plus recursion stack.

=========================================================
APPROACH 3: Dynamic Programming (Bottom-Up / Space-Optimized) [Most Optimal]
=========================================================
• Intuition:
  At index i, transition values depend strictly on index i - 1.
• Approach:
  Maintain two variables:
  - dp0: max sum ending at previous index replaced by 1.
  - dp1: max sum ending at previous index kept as original.
  For index i, compute new values for choosing 1 vs arr[i] and update in O(1) space.
• Why it Works:
  Captures the optimal substructure with strictly constant auxiliary space.
• Time Complexity (TC): O(N) - Single pass through the array.
• Space Complexity (SC): O(1) - Only four scalar variables are used.
=========================================================
*/

/*
=========================================================
FINAL APPROACH:
Chosen Approach: Space-Optimized Dynamic Programming (Approach 3).
Reason:
It achieves linear O(N) time with optimal O(1) auxiliary space, effortlessly
handling the constraint N <= 10^5 without memory overhead or call stack risk.
=========================================================
*/

#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDiffSum(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        // dp0: max sum up to previous index where previous element was replaced by 1
        // dp1: max sum up to previous index where previous element was kept as arr[prev]
        long long dp0 = 0;
        long long dp1 = 0;

        for (int i = 1; i < n; ++i) {
            // If current element is replaced by 1:
            long long next_dp0 = max(dp0 + abs(1 - 1), 
                                     dp1 + abs(1 - arr[i - 1]));

            // If current element is kept as arr[i]:
            long long next_dp1 = max(dp0 + abs(arr[i] - 1), 
                                     dp1 + abs(arr[i] - arr[i - 1]));

            dp0 = next_dp0;
            dp1 = next_dp1;
        }

        return max(dp0, dp1);
    }
};
