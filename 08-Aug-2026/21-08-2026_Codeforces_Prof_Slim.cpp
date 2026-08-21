/*
=========================================================
Date        : 21-08-2026
Problem Name: Transform String
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Strings, Greedy, Two Pointers, Hash Table

Problem Summary:
Given two strings s1 and s2, find the minimum operations to convert s1 to s2.
The only allowed operation is picking any character from s1 and moving it to the front.
Return -1 if transformation is impossible.

Key Observation:
Moving a character to the front preserves the relative order of the remaining characters.
Characters matched from right-to-left never need to be moved; all unmatched characters must be moved to the front.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Frequency Check + Greedy Two Pointers
---------------------------------------------------------
• Intuition:
  - If s1 and s2 do not have identical character frequencies or lengths, transformation is impossible.
  - To minimize front insertions, we must keep the longest possible subsequence of s1 that matches a suffix of s2 from right to left.

• Approach:
  - Check if lengths match; if not, return -1.
  - Use a hash map / frequency array (size 256) to verify both strings are anagrams.
  - Traverse both strings backwards using two pointers (i for s1, j for s2).
  - If s1[i] == s2[j], both pointers decrement.
  - If s1[i] != s2[j], character s1[i] must eventually be moved to the front; increment operation count and decrement only i.

• Why it Works:
  - Moving characters to the front only shifts unmatched characters ahead, leaving matched suffixes aligned.

• Time Complexity (TC): O(N) where N is the length of the strings.
• Space Complexity (SC): O(1) using a fixed-size 256 array for character counts.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION:
- The Greedy Two-Pointer approach operates in linear time O(N) and O(1) auxiliary space.
- It directly computes the minimum operations by greedily matching characters from the end.
---------------------------------------------------------
*/

class Solution {
public:
    int transform(string& s1, string& s2) {
        int n = s1.length();
        int m = s2.length();

        // Unequal lengths cannot be transformed
        if (n != m) return -1;

        // Verify that s1 and s2 are anagrams
        int freq[256] = {0};
        for (int i = 0; i < n; i++) {
            freq[(unsigned char)s1[i]]++;
            freq[(unsigned char)s2[i]]--;
        }

        for (int i = 0; i < 256; i++) {
            if (freq[i] != 0) return -1;
        }

        // Greedy matching from right to left
        int i = n - 1;
        int j = n - 1;
        int operations = 0;

        while (i >= 0) {
            if (s1[i] == s2[j]) {
                i--;
                j--;
            } else {
                // Character s1[i] needs to be moved to the front
                operations++;
                i--;
            }
        }

        return operations;
    }
};
