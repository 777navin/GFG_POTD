
/*
=========================================================
Date        : 06-11-2026
Problem Name: Balanced Binary Tree Counter
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Dynamic Programming, Trees, Mathematics

Problem Summary:
Find the maximum number of distinct balanced binary trees
having exactly height h. Return the answer modulo 10^9 + 7.

Key Observation:
For a balanced binary tree of height h, the left and
right subtrees can have heights (h-1, h-1) or
(h-1, h-2) or (h-2, h-1).

=========================================================

APPROACH 1: RECURSION

- Intuition:
  Calculate the number of trees using smaller heights.

- Approach:
  Recursively calculate countBT(h-1) and countBT(h-2).

- Why it Works:
  Every balanced tree follows the height difference rule.

- Time Complexity: Exponential
- Space Complexity: O(h) recursion stack.


APPROACH 2: MEMOIZATION

- Intuition:
  Avoid recalculating previously computed heights.

- Approach:
  Store calculated results in a DP array.

- Why it Works:
  Each height is calculated only once.

- Time Complexity: O(h)
- Space Complexity: O(h)


APPROACH 3: TABULATION

- Intuition:
  Build answers from smaller heights to larger heights.

- Approach:
  Use the recurrence:
  dp[h] = dp[h-1]^2 + 2 * dp[h-1] * dp[h-2]

- Why it Works:
  All valid combinations of balanced subtrees are counted.

- Time Complexity: O(h)
- Space Complexity: O(h)


APPROACH 4: SPACE OPTIMIZATION

- Intuition:
  Only the previous two DP values are required.

- Approach:
  Maintain two variables instead of a DP array.

- Why it Works:
  Each new answer depends only on the previous two heights.

- Time Complexity: O(h)
- Space Complexity: O(1)


FINAL APPROACH: SPACE OPTIMIZATION

- Chosen because it provides linear time complexity
  with constant auxiliary space.
- It avoids storing an entire DP array.
- Suitable for the constraint h <= 10^6.

=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int countBT(int h) {

        const long long MOD = 1000000007LL;

        // Base cases:
        // Height 0: Empty tree = 1
        // Height 1: Single node = 1

        long long prev2 = 1;
        long long prev1 = 1;

        // Calculate balanced binary trees for each height.
        for (int i = 2; i <= h; i++) {

            long long curr = (
                (prev1 * prev1) % MOD +
                (2LL * prev1 % MOD * prev2) % MOD
            ) % MOD;

            prev2 = prev1;
            prev1 = curr;
        }

        return (int)prev1;
    }
};

/*
=========================================================
COMPLEXITY ANALYSIS

Time Complexity  : O(h)
Auxiliary Space  : O(1)

=========================================================

EXAMPLE:

Input:
h = 3

Output:
15

Explanation:
dp[0] = 1
dp[1] = 1
dp[2] = 1*1 + 2*1*1 = 3
dp[3] = 3*3 + 2*3*1 = 15

=========================================================
*/
