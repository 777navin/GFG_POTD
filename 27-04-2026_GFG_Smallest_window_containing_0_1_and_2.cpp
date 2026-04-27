/*
Date: 27-04-2026
Problem Name: Smallest window containing 0, 1 and 2
Platform: GeeksforGeeks
Difficulty: Easy / Medium
Tags: String, Sliding Window, Two Pointers

Problem Summary
Given a string `s` consisting only of characters '0', '1' and '2', determine the length of the smallest substring that contains all three characters at least once. If no such substring exists, return -1.

Methods to Solve:
1. Brute Force
2. Optimal Approach (Tracking Last Seen Indices)

-------------------------------------------------------------------------------
Method 1: Brute Force
-------------------------------------------------------------------------------
Intuition:
The most straightforward way is to check every single substring possible in the given string and see if it contains '0', '1', and '2'. We keep track of the minimum length among all valid substrings.

Approach:
- Use two nested loops to generate all possible substrings.
- The outer loop `i` marks the start of the substring.
- The inner loop `j` marks the end of the substring.
- For each substring `s[i...j]`, check if it has all three characters.
- If it does, update the minimum length found so far.

Dry Run (small example):
s = "10212"
- i=0 ('1'): j=0 ("1"), j=1 ("10"), j=2 ("102" -> Valid! len 3). Min = 3.
- i=1 ('0'): j=1 ("0"), j=2 ("02"), j=3 ("021" -> Valid! len 3). Min = 3.
- i=2 ('2'): j=2 ("2"), j=3 ("21"), j=4 ("212" -> No '0').
...

Time Complexity: O(N^2) - Where N is the length of the string. We check all pairs.
Space Complexity: O(1) - No extra space used other than variables.
Why better than previous method: N/A (Baseline).
When to use: Only when N is very small (e.g., N <= 1000). Will give Time Limit Exceeded (TLE) for N = 10^5.

-------------------------------------------------------------------------------
Method 2: Optimal Approach (Tracking Last Seen Indices)
-------------------------------------------------------------------------------
Intuition:
Instead of checking all substrings, as we iterate through the string from left to right, we only care about the most recent positions we saw a '0', '1', and '2'. If we have seen all three at least once, the smallest valid window ending at our current position stretches back to the minimum of those three last-seen indices.

Approach:
- Initialize three variables `lastZero`, `lastOne`, and `lastTwo` to -1.
- Initialize `minLength` to a very large number (or INT_MAX).
- Iterate through the string `s` using an index `i`.
- Update `lastZero`, `lastOne`, or `lastTwo` to `i` depending on `s[i]`.
- Check if `lastZero != -1`, `lastOne != -1`, and `lastTwo != -1` (meaning we've found at least one of each).
- If true, the current valid window length is `i - min({lastZero, lastOne, lastTwo}) + 1`.
- Update `minLength` with the minimum of itself and the current window length.
- If `minLength` was never updated, return -1. Otherwise, return `minLength`.

Dry Run (small example):
s = "10212"
Init: z=-1, o=-1, t=-1, minL=INT_MAX
- i=0 ('1'): o=0. (z=-1, t=-1) -> Cannot form window.
- i=1 ('0'): z=1. (o=0, t=-1) -> Cannot form window.
- i=2 ('2'): t=2. All seen! len = 2 - min(1, 0, 2) + 1 = 2 - 0 + 1 = 3. minL = 3.
- i=3 ('1'): o=3. All seen! len = 3 - min(1, 3, 2) + 1 = 3 - 1 + 1 = 3. minL = 3.
- i=4 ('2'): t=4. All seen! len = 4 - min(1, 3, 4) + 1 = 4 - 1 + 1 = 4. minL = 3.
Result: 3

Time Complexity: O(N) - We iterate through the string exactly once.
Space Complexity: O(1) - We only use a few integer variables.
Why better than previous method: Drastically reduces time complexity from quadratic to linear, easily passing the 10^5 constraint.
When to use: This is the standard, optimal approach for finding the smallest window containing a fixed set of characters.

Comparison Table:
Method | TC     | SC   | Best Use Case
-------------------------------------------------------------------------------
1      | O(N^2) | O(1) | Small strings, interviews (as a starting thought process).
2      | O(N)   | O(1) | Production code, competitive programming, large constraints.

Final Recommended Solution: Method 2
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    int smallestSubstring(string s) {
        int lastZero = -1;
        int lastOne = -1;
        int lastTwo = -1;
        
        int minLength = 1e9; // Use a large number to represent infinity
        int n = s.length();
        
        for (int i = 0; i < n; i++) {
            // Update the most recent index of the current character
            if (s[i] == '0') lastZero = i;
            else if (s[i] == '1') lastOne = i;
            else if (s[i] == '2') lastTwo = i;
            
            // If all three characters have been encountered at least once
            if (lastZero != -1 && lastOne != -1 && lastTwo != -1) {
                // The start of the smallest valid window ending at 'i' is the minimum of the last seen indices
                int windowStart = min({lastZero, lastOne, lastTwo});
                int currentWindowLength = i - windowStart + 1;
                
                // Update the global minimum length
                minLength = min(minLength, currentWindowLength);
            }
        }
        
        // If minLength was never updated, no valid substring exists
        return (minLength == 1e9) ? -1 : minLength;
    }
};
