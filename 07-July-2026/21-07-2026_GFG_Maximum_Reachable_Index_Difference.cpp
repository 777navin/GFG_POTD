/*
=========================================================
Date        : 21-07-2026
Problem Name: Maximum Reachable Index Difference
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Arrays, Strings

Problem Summary:
Given a string of lowercase letters, start at any 'a'.
Jump to any index on the right containing the immediate next letter in the alphabet.
Find the maximum difference between the start and end indices, or -1 if 'a' is absent.

Key Observation:
Since jumps are strictly to the right side, evaluating the string from right to left ensures we only look at valid future moves. 
Storing the maximum reachable index for each character dynamically allows O(1) optimal transitions.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Right-to-Left Dynamic Programming
---------------------------------------------------------

• Intuition:
  To maximize the ending index from a character `c`, we must jump to a `c+1` on its right that itself can reach the furthest. 
  By processing from right to left, the optimal future choices for every character are already computed.

• Approach:
  1. Maintain an array `max_dp[26]` initialized to -1 to track the max reachable end index for each character seen from the right.
  2. Iterate from the end of the string down to 0.
  3. For character `c`, its max reach is itself `i`, or `max(i, max_dp[c + 1])` if `c+1` exists to its right.
  4. Update `max_dp[c]` and if `c == 'a'`, maximize the global answer with `reach - i`.

• Why it Works:
  Processing backwards guarantees that when we check `max_dp[c + 1]`, it represents a valid path strictly moving rightwards.

• Time Complexity (TC): O(N) where N is the length of the string.
• Space Complexity (SC): O(1) auxiliary space since we only use a fixed array of size 26.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH
---------------------------------------------------------
• Why this approach is chosen: 
  It correctly handles the strict "jump to the right" requirement while maintaining linear time. 
• Why it is better than the previous ones: 
  It fixes a logical flaw where global tracking could incorrectly assume a valid reach, ensuring 100% strict rightward transitions.
---------------------------------------------------------
*/

class Solution {
  public:
    int maxIndexDifference(string s) {
        int n = s.size();
        vector<int> max_dp(26, -1);
        int max_diff = -1;
        
        for (int i = n - 1; i >= 0; i--) {
            int c = s[i] - 'a';
            int reach = i; // Base case: character stops here
            
            // If the next character exists to the right, jump to its max reach
            if (c < 25 && max_dp[c + 1] != -1) {
                reach = max(reach, max_dp[c + 1]);
            }
            
            // Update the maximum reach for the current character
            max_dp[c] = max(max_dp[c], reach);
            
            // If we are at an 'a', check if this is the maximum difference overall
            if (c == 0) {
                max_diff = max(max_diff, reach - i);
            }
        }
        
        return max_diff;
    }
};
