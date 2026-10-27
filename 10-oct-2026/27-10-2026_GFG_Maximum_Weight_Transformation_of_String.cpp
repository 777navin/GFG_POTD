/*
=========================================================
Date        : 27-10-2026
Problem Name: Maximum Weight Transformation of String
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Strings

Problem Summary:
- Given a binary string consisting of 'A' and 'B', you can toggle characters ('A' <-> 'B').
- Alternating adjacent pairs ("AB" or "BA") contribute 4 points (non-overlapping).
- Characters not belonging to any pair contribute 1 point.
- Each toggle performed reduces the total weight by 1 point.
- Find the maximum possible weight obtainable.

Key Observation:
- This is a classic overlapping subproblem structure. For each character at index i, we can either leave it unpaired (contributing 1 point and moving to i+1) or form an alternating pair with i+1 (contributing 4 minus any toggle cost, moving to i+2).
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    /*
    Approach: Dynamic Programming with Space Optimization
    
    • Intuition:
      - We want to make a choice at every index whether to pair up with the next character or leave the current character single.
    
    • Approach:
      - Iterate from right to left (suffix DP).
      - Option 1 (Leave s[i] unpaired): Gain 1 point, move to index i + 1.
      - Option 2 (Form an alternating pair with s[i] and s[i+1]): Gain (4 - toggles) points, move to index i + 2, where toggles = 1 if s[i] == s[i+1] else 0.
      - Take the maximum of both options.
    
    • Why it Works:
      - Optimal substructure allows us to compute the maximum weight of suffix s[i...n-1] based solely on states at i+1 and i+2.
    
    • Time Complexity (TC): O(n), where n is the length of the string.
    • Space Complexity (SC): O(1), using space optimization since we only need the last two states.
    */
    
    /*
    Final Approach Selection:
    - We use the space-optimized Dynamic Programming approach because it achieves optimal O(n) time and O(1) space, avoiding the overhead of a full memoization or DP table array while cleanly solving the problem for strings up to length 10^5.
    */
    
    int getMaxWeight(string &s) {
        int n = s.length();
        if (n == 0) return 0;
        if (n == 1) return 1;

        int next_next_val = 0; // Represents dp[i+2]
        int next_val = 1;      // Represents dp[i+1] for the last character (i = n-1)
        int curr_val = 1;

        for (int i = n - 2; i >= 0; --i) {
            // Choice 1: Leave s[i] unpaired
            int option1 = 1 + next_val;

            // Choice 2: Form an alternating pair with s[i] and s[i+1]
            int toggles = (s[i] == s[i+1] ? 1 : 0);
            int option2 = (4 - toggles) + next_next_val;

            curr_val = max(option1, option2);

            // Shift values for the next iteration
            next_next_val = next_val;
            next_val = curr_val;
        }

        return curr_val;
    }
};
