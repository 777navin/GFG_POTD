/*
Date: 15-06-2026
Problem Name: Minimum Cost to Fill Given Weight
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Dynamic Programming, Knapsack Problem

Problem Summary:
Given a bag of capacity 'w' and an array 'cost' where 'cost[i]' represents the cost 
of a packet of weight 'i+1'. If 'cost[i]' is -1, that packet size is unavailable. 
Find the minimum cost to get exactly 'w' weight. Infinite supply of packets available.

Methods to Solve:
1. Dynamic Programming (Unbounded Knapsack Variation)

For Method 1 (Dynamic Programming):

- Intuition: This is a variation of the Unbounded Knapsack problem. We want to 
  minimize the cost to reach exactly weight 'w' using given weights.
- Approach:
  - Create a DP array `dp` of size `w + 1`, initialized to a large value (infinity).
  - Set `dp[0] = 0` (cost to fill 0 weight is 0).
  - Iterate through all possible weights `i` from 1 to `w`.
  - For each weight `i`, iterate through all available packet sizes `j` (1 to `cost.size()`).
  - If `j <= i` and `cost[j-1] != -1`, update `dp[i] = min(dp[i], dp[i-j] + cost[j-1])`.
- Time Complexity: O(w * N), where N is the number of packet types.
- Space Complexity: O(w) for the DP table.
- Why better: Efficiently handles the sub-problems to find the global optimum.
- When to use: When sub-problems overlap and optimal substructure exists.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
DP     | O(w*N) | O(w) | Finding optimal weight combination

Final Recommended Solution: Dynamic Programming
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minimumCost(vector<int>& cost, int w) {
        // Use a large value to represent infinity
        // 1e9 is safe as cost constraints are up to 10^5
        const int INF = 1e9;
        int n = cost.size();
        
        // dp[i] will store the minimum cost to fill weight i
        vector<int> dp(w + 1, INF);
        
        dp[0] = 0;
        
        // Iterate through all weights from 1 to w
        for (int i = 1; i <= w; ++i) {
            // Check all available packets
            for (int j = 1; j <= n; ++j) {
                // If weight of packet (j) <= current total weight (i) 
                // and the packet is available (cost[j-1] != -1)
                if (j <= i && cost[j - 1] != -1) {
                    if (dp[i - j] != INF) {
                        dp[i] = min(dp[i], dp[i - j] + cost[j - 1]);
                    }
                }
            }
        }
        
        // If dp[w] is still INF, it's impossible to achieve weight w
        return (dp[w] == INF) ? -1 : dp[w];
    }
};
