/*
=========================================================
Date        : 10-08-2026
Problem Name: High Effort vs Low Effort
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Dynamic Programming, Arrays

Problem Summary:
Given two arrays for high-effort (h) and low-effort (l) tasks per day,
maximize the total tasks completed. High-effort tasks can only be done 
on day 1, or if no task was performed on the preceding day.

Key Observation:
For any day 'i', the maximum tasks come from either doing a low-effort 
task (adding to max tasks from 'i-1') or doing a high-effort task (adding 
to max tasks from 'i-2' since day 'i-1' must be a rest day).
=========================================================

1. Brute Force
   • Intuition: Try all possible choices for every day.
   • Approach: Recursively compute max of picking low-effort (i-1) or high-effort (i-2).
   • Why it Works: Explores every valid combination of tasks over the days.
   • Time Complexity (TC): O(2^N)
   • Space Complexity (SC): O(N) for recursive stack space.

2. Better (Memoization / 1D DP)
   • Intuition: The recursive approach solves overlapping subproblems repeatedly.
   • Approach: Use an array `dp` where `dp[i]` stores the max tasks up to day i.
   • Why it Works: Prevents redundant calculations by storing computed states.
   • Time Complexity (TC): O(N)
   • Space Complexity (SC): O(N) for the DP array.

3. Most Optimal (Space Optimized DP)
   • Intuition: We only need the results of the last two days to compute the current day.
   • Approach: Maintain `prev1` (day i-1) and `prev2` (day i-2) instead of a full array.
   • Why it Works: Condenses the space requirement while keeping the same transition logic.
   • Time Complexity (TC): O(N)
   • Space Complexity (SC): O(1)

=========================================================
FINAL APPROACH:
Using Space Optimized DP (Approach 3).
It provides the optimal O(N) time complexity without requiring extra O(N) space 
for a DP array. It efficiently tracks just the previous two days' maximums.
=========================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxTask(vector<int>& h, vector<int>& l) {
        int n = h.size();
        
        // Base case: If there are no days, return 0
        if (n == 0) return 0;
        
        // Base case: Only one day, pick the maximum of high or low effort
        if (n == 1) return max(h[0], l[0]);
        
        // prev2 stores the maximum tasks up to day i-2
        int prev2 = max(h[0], l[0]);
        
        // prev1 stores the maximum tasks up to day i-1
        int prev1 = max(prev2 + l[1], h[1]);
        
        // Iterate for the remaining days
        for (int i = 2; i < n; i++) {
            // Pick low effort on day i (add to prev1)
            int pickLow = prev1 + l[i];
            
            // Pick high effort on day i (add to prev2)
            int pickHigh = prev2 + h[i];
            
            // Current max is the best of both choices
            int curr = max(pickLow, pickHigh);
            
            // Update previous variables for the next iteration
            prev2 = prev1;
            prev1 = curr;
        }
        
        return prev1;
    }
};

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<int> h(n), l(n);
            for (int i = 0; i < n; i++) cin >> h[i];
            for (int i = 0; i < n; i++) cin >> l[i];
            
            Solution ob;
            cout << ob.maxTask(h, l) << "\n";
        }
    } else {
        // Sample Test Case Fallback Execution
        Solution ob;
        vector<int> h = {3, 6, 8, 7, 6};
        vector<int> l = {1, 5, 4, 5, 3};
        cout << "Example 1 Output: " << ob.maxTask(h, l) << "\n";
        
        vector<int> h2 = {2, 8, 1};
        vector<int> l2 = {1, 2, 1};
        cout << "Example 2 Output: " << ob.maxTask(h2, l2) << "\n";
    }
    
    return 0;
}
