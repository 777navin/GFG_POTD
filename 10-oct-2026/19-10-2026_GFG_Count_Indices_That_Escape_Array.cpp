/*
=========================================================
Date        : 19-10-2026
Problem Name: Count Indices That Escape Array
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Array, Graph, Cycle Detection

Problem Summary:
- Given an array where each element represents the number of steps to move from index i.
- Positive values move right, negative values move left, and 0 means no move (bad).
- An index is "good" if repeatedly following jumps eventually takes you outside the array, otherwise "bad" (e.g., forms a cycle or hits a 0).
- Return the total number of good indices.

Key Observation:
- Since each index has a unique next position, this forms a functional graph (each node has out-degree 1).
- We can memoize or use state tracking (visited, visiting, visited states like 0: unvisited, 1: visiting/cycle, 2: good/escapes) to avoid redundant traversals.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Brute Force (Simulation)
• Intuition: Simulate the jump sequence for each index one by one until it goes out of bounds or repeats.
• Approach: For every index, follow jumps using a visited array to detect cycles.
• Why it Works: Direct simulation checks the exact problem statement definition.
• Time Complexity (TC): $O(N^2)$ in the worst case due to repeated paths.
• Space Complexity (SC): $O(N)$ for tracking visited elements per simulation.

2. Optimized State Memoization (Most Optimal)
• Intuition: We can cache the result for each index to avoid re-evaluating paths we've already checked.
• Approach: Use a status array where `0` means unvisited, `1` means currently visiting (part of current path/cycle), and `2` means safe/escapes. Propagate the results back along the path.
• Why it Works: Each index is visited a constant number of times, transforming repetitive traversals into linear time.
• Time Complexity (TC): $O(N)$ because each index is processed and memoized once.
• Space Complexity (SC): $O(N)$ for the recursion stack and memoization state array.

=========================================================
FINAL APPROACH
=========================================================
- The optimized memoization approach is chosen because it avoids redundant path recalculations.
- By maintaining a state lookup table for each index (escaping vs trapped/cycle), we achieve linear time complexity, easily handling constraints up to $10^5$.
*/

#include <vector>
#include <iostream>

class Solution {
public:
    int goodIndices(std::vector<int>& arr) {
        int n = arr.size();
        // 0: unvisited, 1: visiting (cycle detection), 2: good (escapes), 3: bad (trapped/cycle)
        std::vector<int> state(n, 0);
        int good_count = 0;

        auto dfs = [&](auto& self, int curr) -> int {
            // If out of bounds, it escapes -> good
            if (curr < 0 || curr >= n) {
                return 2;
            }
            // If currently in the path, we hit a cycle -> bad
            if (state[curr] == 1) {
                return 3;
            }
            // If already computed, return cached state
            if (state[curr] != 0) {
                return state[curr];
            }

            // Mark as visiting
            state[curr] = 1;

            int next_idx = curr + arr[curr];
            state[curr] = self(self, next_idx);

            return state[curr];
        };

        for (int i = 0; i < n; ++i) {
            if (state[i] == 0) {
                dfs(dfs, i);
            }
            if (state[i] == 2) {
                good_count++;
            }
        }

        return good_count;
    }
};
