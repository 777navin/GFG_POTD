/*
=========================================================
Date        : 31-08-2026
Problem Name: Minimum Cost for n Characters
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Dynamic Programming, Greedy, Algorithms

Problem Summary:
Given four integers n, i (insert cost), d (delete cost), and c (copy-paste double cost).
Starting with an empty screen, find the minimum cost to get exactly n characters.

Key Observation:
To reach length `k` from a smaller length, we can either insert from `k-1`, 
double an even length `k/2`, or double `(k+1)/2` and delete one character.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Dynamic Programming (Bottom-Up 1D DP)
---------------------------------------------------------
• Intuition:
  - Building characters incrementally allows each state `k` to depend on optimal costs of reaching smaller lengths.
  - An even state `k` can be reached from `k-1` (insert) or `k/2` (copy-paste).
  - An odd state `k` can be reached from `k-1` (insert) or `(k+1)/2` (copy-paste then delete 1).

• Approach:
  - Initialize `dp` array of size `n + 1` with 0.
  - Base case: `dp[0] = 0`, `dp[1] = i`.
  - For each `k` from 2 to `n`:
    - If `k` is even: `dp[k] = min(dp[k - 1] + i, dp[k / 2] + c)`
    - If `k` is odd:  `dp[k] = min(dp[k - 1] + i, dp[(k + 1) / 2] + c + d)`
  - Return `dp[n]`.

• Why it Works:
  - Any optimal sequence never needs to overshoot beyond `(k+1)` before deleting back to `k` because doubling beyond `(k+1)` incurs unnecessary delete costs.

• Time Complexity (TC): O(n)
• Space Complexity (SC): O(n)
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
• Bottom-Up 1D DP is chosen as it runs in strictly linear O(n) time and easily fits within memory limits for n <= 10^6.
• It provides optimal transitions without overhead and avoids recursion stack depth issues.
---------------------------------------------------------
*/

class Solution {
public:
    int minCost(int n, int i, int d, int c) {
        if (n <= 0) return 0;
        if (n == 1) return i;

        vector<long long> dp(n + 1, 0);
        dp[1] = i;

        for (int k = 2; k <= n; ++k) {
            if (k % 2 == 0) {
                dp[k] = min(dp[k - 1] + i, dp[k / 2] + c);
            } else {
                dp[k] = min(dp[k - 1] + i, dp[(k + 1) / 2] + c + d);
            }
        }

        return (int)dp[n];
    }
};
