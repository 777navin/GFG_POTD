/*
=========================================================
Date        : 12-10-2026
Problem Name: Minimum_Squares_with_Full_Cuts
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Recursion, Memoization

Problem Summary:
Given a rectangular paper with dimensions n x m, find the minimum number of squares that can be formed by cutting the paper. 
Each cut must be made completely across the remaining paper either horizontally or vertically.

Key Observation:
Since constraints go up to 10^9, a fixed 2D array (`dp[1005][1005]`) causes out-of-bounds errors. 
Using `map<pair<int, int>, int>` for memoization handles large dimensions efficiently while avoiding redundant recursive calls.
=========================================================
*/

/*
=========================================================
Approach Explanation:

1. Recursion with Map Memoization
   • Intuition: Try all possible horizontal and vertical full cuts across the rectangle and recursively find the minimum squares for the resulting sub-rectangles.
   • Approach: Use a helper function with `map<pair<int, int>, int>` to memoize states. Optimize state space by ensuring `n <= m` and returning early if `m % n == 0`.
   • Why it Works: Caching unique dimension pairs prevents exponential time blowup while supporting large values up to 10^9.
   • Time Complexity (TC): O(n * m) states in the worst case, heavily pruned by memoization.
   • Space Complexity (SC): O(number of unique state pairs stored in the map).
=========================================================
*/

/*
=========================================================
Final Approach:
Memoized recursion with `map` is chosen to safely handle large constraints up to 10^9 without hitting fixed-size array limits or memory overflow.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
private:
    map<pair<int, int>, int> memo;

    int solve(int n, int m) {
        if (n == m) return 1;
        
        // Keep n as the smaller dimension to minimize states
        if (n > m) swap(n, m);
        
        // If one dimension is a multiple of the other, return the exact quotient
        if (m % n == 0) return m / n;

        if (memo.count({n, m})) return memo[{n, m}];

        int ans = INT_MAX;

        // Try all horizontal cuts
        for (int i = 1; i <= n / 2; i++) {
            ans = min(ans, solve(i, m) + solve(n - i, m));
        }

        // Try all vertical cuts
        for (int j = 1; j <= m / 2; j++) {
            ans = min(ans, solve(n, j) + solve(n, m - j));
        }

        return memo[{n, m}] = ans;
    }

public:
    int minSquares(int n, int m) {
        memo.clear();
        return solve(n, m);
    }
};
