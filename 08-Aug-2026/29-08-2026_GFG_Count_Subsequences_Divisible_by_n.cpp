/*
=========================================================
Date        : 29-08-2026
Problem Name: [Count Subsequences Divisible by n](https://www.geeksforgeeks.org/problems/number-of-subsequences-in-a-string-divisible-by-n5947/1)
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Number Theory, String

Problem Summary:
Given a numeric string s containing only digits and an integer n, count the 
number of non-empty subsequences of s whose numeric value is divisible by n. 
Return the result modulo 1e9 + 7.

Key Observation:
Each digit can either start a new subsequence or append to existing subsequences. 
Appending digit 'd' to a subsequence with value 'v' (modulo n = r) results in 
a new remainder: (r * 10 + d) % n.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Optimized Dynamic Programming (Space-Optimized Remainder Array)
• Intuition: Maintain an array representing the count of non-empty subsequences for each remainder modulo n.
• Approach: Iterate through each character/digit in string s. Update remainder counts by considering the current digit starting a new subsequence or extending previous ones.
• Why it Works: Transitions strictly depend on the previous prefix's remainder distribution, enabling O(n) space and linear-factor transitions per character.
• Time Complexity (TC): O(|s| * n)
• Space Complexity (SC): O(n)
=========================================================
*/

/*
=========================================================
FINAL APPROACH & RATIONALE
=========================================================
• We use a 1D DP array of size n to track remainder frequencies.
• The function name `countSubsequences` matches the exact driver code signature expected by GeeksforGeeks.
• Space is minimized to O(n) while computing the exact count modulo 1e9 + 7.
=========================================================
*/

class Solution {
  public:
    int countSubsequences(string& s, int n) {
        const int MOD = 1e9 + 7;
        vector<long long> dp(n, 0);

        for (char c : s) {
            int digit = c - '0';
            vector<long long> next_dp = dp;

            // Start a new single-digit subsequence
            int rem = digit % n;
            next_dp[rem] = (next_dp[rem] + 1) % MOD;

            // Extend existing subsequences
            for (int r = 0; r < n; ++r) {
                if (dp[r] > 0) {
                    int new_rem = (r * 10 + digit) % n;
                    next_dp[new_rem] = (next_dp[new_rem] + dp[r]) % MOD;
                }
            }

            dp = move(next_dp);
        }

        return dp[0];
    }
};
