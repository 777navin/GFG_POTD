/*
=========================================================
Date        : 07-09-2026
Problem Name: Minimum Elements Outside Subsequences
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Dynamic Programming, Subsequences, Arrays

Problem Summary:
Given an array arr[] of size n, partition its elements into 
a strictly increasing subsequence and a strictly decreasing subsequence.
Each element belongs to at most one subsequence, leaving some unused.
Determine the minimum number of elements left unselected.

Key Observation:
Minimizing unselected elements is equivalent to maximizing the total 
number of elements assigned to the two subsequences. For each element, 
we can either extend the increasing subsequence, extend the decreasing 
subsequence, or leave it unused.
=========================================================
*/

/*
APPROACH 1: Dynamic Programming with Memoization (3D State)
• Intuition:
  Process elements from left to right. At index i, maintain the last element 
  picked in the increasing subsequence and the last element picked in the decreasing subsequence.
• Approach:
  Define dp(i, inc_idx, dec_idx) as the maximum elements selected from index i onward.
  Transition by trying:
  1. Skip arr[i].
  2. Append arr[i] to the increasing sequence if arr[i] > arr[inc_idx].
  3. Append arr[i] to the decreasing sequence if arr[i] < arr[dec_idx].
• Why it Works:
  Exploring all valid transitions guarantees discovering the optimal assignment.
• Time Complexity (TC):
  O(n^3) - there are O(n^3) states, each taking O(1) transitions.
• Space Complexity (SC):
  O(n^3) - for the 3D memoization table and recursion stack.

APPROACH 2: Value-Based Dynamic Programming (2D State)
• Intuition:
  Since constraints specify 1 <= arr[i] <= 100, the last chosen values in 
  the increasing and decreasing subsequences can be directly indexed by their values (0 to 101).
• Approach:
  Let dp[inc_val][dec_val] store the maximum count of elements chosen so far.
  For each number x in arr, update the state transitions:
  - If x > inc_val, state (x, dec_val) can be reached with count + 1.
  - If x < dec_val, state (inc_val, x) can be reached with count + 1.
  - Leave unchanged (element skipped).
• Why it Works:
  Subsequence validity only depends on the actual value of the last appended elements.
• Time Complexity (TC):
  O(n * V^2), where V <= 100. With n <= 100, operations are ~100 * 100 * 100 = 10^6, easily passing within limits.
• Space Complexity (SC):
  O(V^2) using space optimization across iterations.
*/

/*
FINAL APPROACH:
• Why this approach is chosen:
  The 3D DP over indices is O(n^3), which is compact, intuitive, and fits safely within the 
  tight limits (n <= 100, yielding ~10^6 operations) without needing value bounds.
• Why it is better than the previous ones:
  Memoization over indices (i, inc_idx + 1, dec_idx + 1) avoids large memory allocations,
  handles negative/large array values gracefully if constraints change, and avoids 2D table copy overhead.
*/

#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
    int memo[105][105][105];

    int solve(int i, int inc_idx, int dec_idx, const vector<int>& arr) {
        if (i == arr.size()) {
            return 0;
        }

        if (memo[i][inc_idx + 1][dec_idx + 1] != -1) {
            return memo[i][inc_idx + 1][dec_idx + 1];
        }

        // Option 1: Skip the current element
        int ans = solve(i + 1, inc_idx, dec_idx, arr);

        // Option 2: Add to increasing subsequence
        if (inc_idx == -1 || arr[i] > arr[inc_idx]) {
            ans = max(ans, 1 + solve(i + 1, i, dec_idx, arr));
        }

        // Option 3: Add to decreasing subsequence
        if (dec_idx == -1 || arr[i] < arr[dec_idx]) {
            ans = max(ans, 1 + solve(i + 1, inc_idx, i, arr));
        }

        return memo[i][inc_idx + 1][dec_idx + 1] = ans;
    }

public:
    int minCount(vector<int>& arr) {
        int n = arr.size();
        memset(memo, -1, sizeof(memo));
        
        int maxIncluded = solve(0, -1, -1, arr);
        return n - maxIncluded;
    }
};
