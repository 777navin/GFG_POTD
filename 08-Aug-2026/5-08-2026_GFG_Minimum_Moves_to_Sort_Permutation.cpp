/*
=========================================================
Date        : 25-08-2026
Problem Name: Minimum Moves to Sort Permutation (Morning Assembly)
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Arrays, Dynamic Programming, Hash

Problem Summary:
Given an array containing a permutation of numbers from 1 to n.
In one operation, an element can be moved to either the beginning or the end.
Find the minimum number of operations required to sort the array in ascending order.

Key Observation:
Moving elements to the ends means keeping the longest contiguous subsegment of elements 
of the form [x, x+1, x+2, ...] that already appear in increasing order of index unchanged, 
and moving all other (n - L) elements around them.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Dynamic Programming / Hash Map (Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - We want to leave a subsequence of consecutive integers (x, x+1, x+2, ..., x+k-1) untouched.
  - The answer will simply be n - (length of longest contiguous consecutive subsequence).

• Approach:
  - Maintain a DP array/map where dp[x] represents the length of the consecutive increasing subsequence ending at value x.
  - For each element x in arr, dp[x] = dp[x - 1] + 1.
  - Track the maximum length max_len among all dp[x].
  - Result is n - max_len.

• Why it Works:
  - If x - 1 appeared earlier in the array, x can extend that sequence by 1.
  - All elements not part of this longest consecutive chain must be moved at most once to either the start or end.

• Time Complexity (TC): O(n) - Single pass over the array.
• Space Complexity (SC): O(n) - To store DP values / frequencies up to n.
*/

/*
=========================================================
FINAL APPROACH:
We use a 1D DP vector of size (n + 1) to track the longest consecutive increasing
subsequence ending at each value in O(n) time and O(n) auxiliary space.
This is optimal as we must inspect every element at least once.
=========================================================
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minMoves(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        vector<int> dp(n + 1, 0);
        int max_len = 0;

        for (int x : arr) {
            dp[x] = dp[x - 1] + 1;
            max_len = max(max_len, dp[x]);
        }

        return n - max_len;
    }
};
