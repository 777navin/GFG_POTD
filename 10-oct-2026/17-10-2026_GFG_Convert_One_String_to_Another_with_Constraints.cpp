/*
=========================================================
Date        : 17-10-2026
Problem Name: Convert One String to Another with Constraints
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Two Pointers, Strings

Problem Summary:
Given two strings s1 and s2 consisting of 'A', 'B', and '#', determine if s1 can be transformed into s2.
'A' can move only left and 'B' can move only right through '#', and they cannot cross each other.

Key Observation:
Ignoring '#' characters, the sequence of non-empty characters ('A' and 'B') in both strings must be identical.
Also, the relative indices of 'A' and 'B' must respect their movement constraints (A's new index <= old index, B's new index >= old index).
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Two Pointers
---------------------------------------------------------

• Intuition:
  - First, verify if the relative order and count of 'A' and 'B' characters are identical in both strings by ignoring all '#' characters.
  - Second, ensure that each 'A' in s1 has an index greater than or equal to its corresponding 'A' in s2 (since 'A' can only move left).
  - Third, ensure that each 'B' in s1 has an index less than or equal to its corresponding 'B' in s2 (since 'B' can only move right).

• Approach:
  - Iterate through both strings using two pointers, skipping '#' characters.
  - If characters at the current pointers do not match, return false.
  - If the character is 'A', check if the index in s1 is greater than or equal to the index in s2.
  - If the character is 'B', check if the index in s1 is less than or equal to the index in s2.

• Why it Works:
  - Characters cannot cross each other, meaning their relative order is strictly preserved.
  - Tracking initial and final positions validates the directional movement constraints of 'A' and 'B'.

• Time Complexity (TC): O(N), where N is the length of the strings, as we traverse them linearly.
• Space Complexity (SC): O(1), as we only use a few pointer variables.
---------------------------------------------------------
*/

/*
FINAL APPROACH CHOSEN:
- The Two-Pointers approach is optimal and runs in linear time with constant extra space.
- It directly validates sequence matching and movement constraints in a single pass without extra data structures.
*/

#include <iostream>
#include <string>
#include <vector>

class Solution {
public:
    bool isItPossible(string s1, string s2) {
        if (s1.length() != s2.length()) {
            return false;
        }
        
        int n = s1.length();
        int i = 0, j = 0;
        
        while (i < n && j < n) {
            // Skip '#' in s1
            while (i < n && s1[i] == '#') {
                i++;
            }
            // Skip '#' in s2
            while (j < n && s2[j] == '#') {
                j++;
            }
            
            // If both reached the end
            if (i == n && j == n) {
                return true;
            }
            // If one reached the end before the other
            if (i == n || j == n) {
                return false;
            }
            
            // Characters must match
            if (s1[i] != s2[j]) {
                return false;
            }
            
            // Check movement constraints
            if (s1[i] == 'A') {
                // 'A' can only move to the left (s1 index >= s2 index)
                if (i < j) {
                    return false;
                }
            } else if (s1[i] == 'B') {
                // 'B' can only move to the right (s1 index <= s2 index)
                if (i > j) {
                    return false;
                }
            }
            
            i++;
            j++;
        }
        
        // Skip remaining trailing '#' in s1
        while (i < n && s1[i] == '#') {
            i++;
        }
        // Skip remaining trailing '#' in s2
        while (j < n && s2[j] == '#') {
            j++;
        }
        
        return i == n && j == n;
    }
};
