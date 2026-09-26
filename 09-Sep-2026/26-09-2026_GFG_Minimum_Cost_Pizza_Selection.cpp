/*
=========================================================
Date        : 26-09-2026
Problem Name: Minimum Cost Pizza Selection
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Knapsack

Problem Summary:
Given three types of pizzas (Small, Medium, Large) with areas (s, m, l) and costs (cs, cm, cl).
Find the minimum cost required to buy pizzas such that the total pizza area is at least x.
Any number of pizzas of each type can be purchased.

Key Observation:
Since x <= 500 and pizza sizes are up to 100, we can build a Dynamic Programming array up to x + max(s, m, l) to handle total area exceeding the minimum requirement x.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Dynamic Programming (Unbounded Knapsack Style)
---------------------------------------------------------

• Intuition:
  We want to reach or exceed a target area x at minimum cost using three item types with unlimited quantity.

• Approach:
  1. Define upper bound limit = x + max({s, m, l}) to account for overshooting area x.
  2. Initialize a DP array of size limit + 1 filled with infinity, and dp[0] = 0.
  3. Iterate i from 1 to limit and transition:
     dp[i] = min({dp[max(0, i-s)] + cs, dp[max(0, i-m)] + cm, dp[max(0, i-l)] + cl}).
  4. Find the minimum cost in dp[i] for all i >= x.

• Why it Works:
  It explores all optimal combinations of purchasing pizzas up to target area x and slight overshoots, guaranteeing the global minimum due to optimal substructure.

• Time Complexity (TC):
  O(x + max(s, m, l)) since we evaluate constant (3) transitions for each area state.

• Space Complexity (SC):
  O(x + max(s, m, l)) for storing the 1D DP array.
*/

/*
---------------------------------------------------------
FINAL APPROACH CHOICE
---------------------------------------------------------
• Why this approach is chosen:
  The constraints (x <= 500) are small, making 1D Dynamic Programming optimal, fast, and easy to implement.
• Why it is better than previous ones:
  It eliminates exponential recursion time complexity and directly computes the minimum cost state in linear time.
*/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution {
public:
    int minimumCost(int x, int s, int m, int l, int cs, int cm, int cl) {
        int max_size = std::max({s, m, l});
        int limit = x + max_size;
        
        // dp[i] stores the minimum cost to achieve exact area i
        std::vector<int> dp(limit + 1, 1e9);
        dp[0] = 0;
        
        for (int i = 1; i <= limit; ++i) {
            if (i >= s) dp[i] = std::min(dp[i], dp[i - s] + cs);
            else dp[i] = std::min(dp[i], cs);
            
            if (i >= m) dp[i] = std::min(dp[i], dp[i - m] + cm);
            else dp[i] = std::min(dp[i], cm);
            
            if (i >= l) dp[i] = std::min(dp[i], dp[i - l] + cl);
            else dp[i] = std::min(dp[i], cl);
        }
        
        int min_cost = 1e9;
        for (int i = x; i <= limit; ++i) {
            min_cost = std::min(min_cost, dp[i]);
        }
        
        return min_cost;
    }
};
