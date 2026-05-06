// Date: 20-04-2026
// Problem: Count Derangements
// Difficulty: Medium
// Language: C++

#include <bits/stdc++.h>
using namespace std;

/*
==================================================
Problem Statement:
Given a number n, find total number of derangements.
A derangement is a permutation where no element
appears in its original position.

Example:
Input: n = 3
Output: 2
Explanation:
[2,3,1], [3,1,2]
==================================================
*/

/*
==================================================
Approach: Dynamic Programming

Intuition:
Let dp[i] = number of derangements for i elements.

Recurrence Relation:
dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2])

Why?
Place first element in any of (i - 1) wrong positions.
Then two cases are formed, giving:
(dp[i - 1] + dp[i - 2])

Base Cases:
dp[1] = 0
dp[2] = 1

Time Complexity: O(n)
Space Complexity: O(n)
==================================================
*/

class Solution {
public:
    int derangeCount(int n) {
        if (n == 1) return 0;
        if (n == 2) return 1;

        vector<int> dp(n + 1, 0);
        dp[1] = 0;
        dp[2] = 1;

        for (int i = 3; i <= n; i++) {
            dp[i] = (i - 1) * (dp[i - 1] + dp[i - 2]);
        }

        return dp[n];
    }
};

/*
==================================================
Optimized Approach
Use only previous two values.

Time Complexity: O(n)
Space Complexity: O(1)
==================================================
*/

class SolutionOptimized {
public:
    int derangeCount(int n) {
        if (n == 1) return 0;
        if (n == 2) return 1;

        int prev2 = 0;
        int prev1 = 1;
        int curr;

        for (int i = 3; i <= n; i++) {
            curr = (i - 1) * (prev1 + prev2);
            prev2 = prev1;
            prev1 = curr;
        }

        return prev1;
    }
};
