/*
=========================================================
Date        : 05-09-2026
Problem Name: Longest Subsequence with Adjacent Diff as 1
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Dynamic Programming, Arrays, Hash Table

Problem Summary:
Given an array arr[] of size n, find the length of the longest
subsequence such that the absolute difference between any two
adjacent elements in the subsequence is exactly 1.

Key Observation:
An element x can only extend a valid subsequence that ends at
either (x - 1) or (x + 1).
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Dynamic Programming (LIS Variation)
---------------------------------------------------------
• Intuition:
  Similar to the Longest Increasing Subsequence (LIS), we can check
  all previous elements j < i and transition if |arr[i] - arr[j]| == 1.

• Approach:
  - Maintain a dp array where dp[i] is the length of the longest valid
    subsequence ending at index i.
  - For each i from 0 to n-1, check all j from 0 to i-1.
  - If |arr[i] - arr[j]| == 1, update dp[i] = max(dp[i], dp[j] + 1).

• Why it Works:
  It systematically evaluates every valid pair transition across indices.

• Time Complexity: O(n^2)
• Space Complexity: O(n)
*/

/*
---------------------------------------------------------
APPROACH 2: Hash Map / Direct Frequency Lookup DP (Optimal)
---------------------------------------------------------
• Intuition:
  Instead of scanning all previous elements, we only care about the best
  length achieved so far by subsequences ending with value (x - 1) or (x + 1).

• Approach:
  - Use a hash map or direct lookup table `dp` where `dp[v]` stores the length
    of the longest valid subsequence ending with value `v`.
  - For each element x in arr:
      dp[x] = 1 + max(dp[x - 1], dp[x + 1])
  - Track the maximum value observed in `dp`.

• Why it Works:
  Only the values (x - 1) and (x + 1) can precede x; keeping the running
  maximum for each value guarantees optimal extension in constant time.

• Time Complexity: O(n)
• Space Complexity: O(n) or O(max_val)
*/

/*
=========================================================
FINAL APPROACH: Hash Map DP
=========================================================
Approach 2 is chosen because the constraints allow arr.size() up to 10^6,
where an O(n^2) approach will result in Time Limit Exceeded (TLE).
This approach reduces the lookup to O(1) average time per element,
yielding an overall optimal O(n) runtime.
=========================================================
*/

#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    int longestSubseq(std::vector<int>& arr) {
        std::unordered_map<int, int> dp;
        int maxLength = 0;

        for (int x : arr) {
            int prevLess = dp.count(x - 1) ? dp[x - 1] : 0;
            int prevMore = dp.count(x + 1) ? dp[x + 1] : 0;

            dp[x] = 1 + std::max(prevLess, prevMore);
            maxLength = std::max(maxLength, dp[x]);
        }

        return maxLength;
    }
};
