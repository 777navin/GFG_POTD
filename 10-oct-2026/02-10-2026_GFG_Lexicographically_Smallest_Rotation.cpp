/*
=========================================================
Date        : 02-10-2026
Problem Name: Lexicographically Smallest Rotation
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Strings, Two Pointers, Booth's Algorithm, Suffix Automaton

Problem Summary:
Given a string s, find the lexicographically smallest string that can be formed by rotating s left any number of times (0 to N-1).

Key Observation:
Finding the lexicographically smallest rotation of a string of length N in O(N) time can be efficiently achieved using Booth's Algorithm for Minimal String Rotation.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
APPROACH 1: Brute Force (Generate All Rotations)
=========================================================
• Intuition:
  Generate all N left rotations of the string, store them, and find the lexicographically smallest one.

• Approach:
  1. Concatenate string s with itself to form double length string S = s + s.
  2. Extract all substrings of length N starting at indices 0 to N-1.
  3. Compare all generated substrings to maintain the lexicographically smallest string.

• Why it Works:
  Every valid left rotation of string s corresponds to a substring of length N in s + s starting at an index in [0, N-1].

• Time Complexity (TC):
  O(N^2) - Generating N substrings, each taking O(N) comparison time.

• Space Complexity (SC):
  O(N) - Storing substrings or string comparisons.
*/

/*
=========================================================
APPROACH 2: Optimized (Booth's Algorithm)
=========================================================
• Intuition:
  Instead of comparing whole substrings repeatedly, we can maintain two candidate starting indices and compare characters. When a mismatch occurs, we can jump the failing index past redundant comparisons using failure function logic similar to KMP.

• Approach:
  1. Duplicate the string S = s + s to easily handle circular comparisons.
  2. Maintain a failure table / preprocessing array or use two pointers i and j representing two candidate rotation indices, and k representing offset length.
  3. Compare S[i + k] with S[j + k].
  4. If S[i + k] == S[j + k], increment k.
  5. If S[i + k] > S[j + k], candidate i cannot be the minimal start, so advance i = i + k + 1. If i <= j, set i = j + 1. Reset k = 0.
  6. If S[i + k] < S[j + k], candidate j cannot be the minimal start, so advance j = j + k + 1. If j <= i, set j = i + 1. Reset k = 0.
  7. Return the substring of length N starting at min(i, j).

• Why it Works:
  When a mismatch occurs at offset k, all starting positions between the candidate index and candidate + k are guaranteed to produce lexicographically larger or equal rotations, allowing us to safely skip them in O(1) amortized time.

• Time Complexity (TC):
  O(N) - Each pointer advances at most 2N times.

• Space Complexity (SC):
  O(N) - To store the doubled string S (or O(1) space using modulo operations on original string).
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
• Booth's algorithm (Two Pointers on doubled string) is chosen because the constraint N <= 10^6 renders O(N^2) brute-force solutions TLE (Time Limit Exceeded).
• It runs in linear O(N) time and O(N) space, making it perfectly optimal for N = 1,000,000.
=========================================================
*/

class Solution {
public:
    string lexiString(string &s) {
        int n = s.length();
        string S = s + s;
        int i = 0, j = 1, k = 0;
        
        while (i < n && j < n && k < n) {
            if (S[i + k] == S[j + k]) {
                k++;
            } else if (S[i + k] > S[j + k]) {
                i = i + k + 1;
                if (i <= j) {
                    i = j + 1;
                }
                k = 0;
            } else {
                j = j + k + 1;
                if (j <= i) {
                    j = i + 1;
                }
                k = 0;
            }
        }
        
        int start_idx = min(i, j);
        return S.substr(start_idx, n);
    }
};02-10-2026_GFG_Lexicographically_Smallest_Rotation.cpp
