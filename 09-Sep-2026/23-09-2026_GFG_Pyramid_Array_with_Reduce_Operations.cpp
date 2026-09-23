/*
=========================================================
Date        : 23-09-2026
Problem Name: Pyramid Array with Reduce Operations
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Dynamic Programming, Arrays, Prefix Sum

Problem Summary:
Given an array arr[] of stone heights, find the minimum total cost to transform the stones
into a symmetric pyramid of shape [1, 2, ..., x, ..., 2, 1] by only reducing stone heights.
All stones outside this pyramid subarray must be reduced to height 0.

Key Observation:
A pyramid of peak height x has a total stone requirement of x^2. Minimizing the reduction cost
is equivalent to maximizing the stone count (or peak height x) of a valid pyramid, where peak height
at index i is limited by arr[i], left boundary reach, and right boundary reach.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  Try every index i as the center of the pyramid and test every possible peak height x from 1 to arr[i].
• Approach:
  For each index i, decrement possible peak x and verify if arr[i - k] >= x - k and arr[i + k] >= x - k
  for all 0 <= k < x. Track the maximum valid x found.
• Why it Works:
  Directly checks all potential peak positions and heights according to the problem constraints.
• Time Complexity: O(N^2)
• Space Complexity: O(1)

---------------------------------------------------------
APPROACH 2: Optimized (Two-Pass Dynamic Programming)
---------------------------------------------------------
• Intuition:
  The maximum possible height of an increasing ramp ending at index i depends on arr[i] and the ramp height at i - 1.
  Similarly, the decreasing ramp starting at index i depends on arr[i] and the ramp at i + 1.
• Approach:
  1. Compute left[i] = min(arr[i], left[i - 1] + 1) representing the maximum ramp height ending at i.
  2. Compute right[i] = min(arr[i], right[i + 1] + 1) representing the maximum ramp height starting at i.
  3. At each index i, the maximum feasible peak height is min({left[i], right[i], i + 1, n - i}).
  4. Maximize peak x across all valid centers. The total sum of a pyramid of peak x is x^2.
  5. The minimum operations needed = (total sum of arr) - (max_x^2).
• Why it Works:
  Left and right passes decouple the constraints on each side into linear time transitions, guaranteeing
  the optimal peak height can be identified in O(N).
• Time Complexity: O(N)
• Space Complexity: O(N)
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION:
---------------------------------------------------------
Approach 2 (Two-Pass DP) is selected because N <= 10^5, making an O(N^2) brute force
lead to Time Limit Exceeded (TLE). The linear time DP calculates left and right height bounds
in two straightforward passes, yielding optimal efficiency and clean implementation.
---------------------------------------------------------
*/

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int formPyramid(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;

        vector<int> left(n);
        vector<int> right(n);

        // Left pass: maximum strictly increasing sequence up to index i
        left[0] = min(arr[0], 1);
        for (int i = 1; i < n; ++i) {
            left[i] = min(arr[i], left[i - 1] + 1);
        }

        // Right pass: maximum strictly decreasing sequence from index i
        right[n - 1] = min(arr[n - 1], 1);
        for (int i = n - 2; i >= 0; --i) {
            right[i] = min(arr[i], right[i + 1] + 1);
        }

        // Find the maximum peak height x of a valid pyramid
        long long max_peak = 0;
        for (int i = 0; i < n; ++i) {
            long long current_peak = min({left[i], right[i], i + 1, n - i});
            max_peak = max(max_peak, current_peak);
        }

        // Total stones in the original array
        long long total_sum = 0;
        for (int x : arr) {
            total_sum += x;
        }

        // Sum of pyramid of peak x is 1 + 2 + ... + x + ... + 2 + 1 = x^2
        long long pyramid_sum = max_peak * max_peak;

        return (int)(total_sum - pyramid_sum);
    }
};
