/*
Date: 19-06-2026
Problem Name: 19-06-2026_GFG_Equalize_All_Prefix_Sums.cpp
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Array, Math, Prefix Sum, DP

Problem Summary:
Given a sorted array `arr[]`. For each index `i`, find the minimum number of operations 
(+1 or -1) to make all elements from index 0 to `i` equal. Do this for all `i` from 0 to n-1.
Must be solved in O(1) extra space (excluding the output array).

Methods to Solve:
1. Brute Force (Iterating Medians)
2. Optimal Approach (Mathematical Recurrence / DP)

For EACH method include:

- Intuition:
  For any sorted array or subarray, the target value that minimizes the sum of absolute differences
  is always the median. For a subarray `arr[0...i]`, the median is at index `i/2`.
  Instead of recalculating the operations for every prefix from scratch, we can find a 
  relationship between the answer for prefix `i-1` and prefix `i`.

- Approach (Optimal):
  1. Initialize an `ans` array of size `n` with `ans[0] = 0`.
  2. Loop `i` from 1 to `n-1`.
  3. For each step, the newly added operations follow a strict mathematical recurrence:
     `ans[i] = ans[i-1] + arr[i] - arr[i/2]`.
  4. This elegantly avoids nested loops and tracks the absolute differences implicitly.

- Dry Run (small example):
  Input: arr = [1, 6, 9, 12]
  i=0: ans[0] = 0
  i=1: ans[1] = ans[0] + arr[1] - arr[1/2] = 0 + 6 - 1 = 5
  i=2: ans[2] = ans[1] + arr[2] - arr[2/2] = 5 + 9 - 6 = 8
  i=3: ans[3] = ans[2] + arr[3] - arr[3/2] = 8 + 12 - 6 = 14
  Result: [0, 5, 8, 14]

- Time Complexity: O(N) where N is the length of the array, as we iterate exactly once.
- Space Complexity: O(1) auxiliary space, as we only construct the required output array.
- Why better than previous method: The brute force takes O(N^2) as it recalculates the median differences for every prefix. This brings it down to strict O(N).
- When to use: When minimum absolute differences are required on expanding windows or prefixes of sorted arrays.

Comparison Table:
Method             | TC      | SC      | Best Use Case
-------------------|---------|---------|-------------------------
Brute Force        | O(N^2)  | O(1)    | Never (results in TLE)
Math Recurrence    | O(N)    | O(1)    | Optimal, production-ready

Final Recommended Solution:
The mathematical recurrence (ans[i] = ans[i-1] + arr[i] - arr[i/2]) is the most optimal 
solution matching the requested O(1) extra space constraint.
*/

#include <vector>

class Solution {
public:
    std::vector<int> optimalArray(std::vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return {};
        
        std::vector<int> ans(n, 0);
        
        // ans[0] is always 0 since it requires 0 operations to make a single element equal to itself
        for (int i = 1; i < n; ++i) {
            ans[i] = ans[i - 1] + arr[i] - arr[i / 2];
        }
        
        return ans;
    }
};

