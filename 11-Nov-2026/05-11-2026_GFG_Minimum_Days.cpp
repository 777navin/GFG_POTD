/*
=========================================================
Date        : 05-11-2026
Problem Name: Minimum Days
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Strings, Permutation, Greedy

Problem Summary:
Given a string and a permutation array, replace characters
with '?' in the specified order, one character per day.
Find the minimum days required to eliminate equal adjacent
characters.

Key Observation:
Only adjacent equal characters need to be eliminated.
Process the string from left to right and perform replacements
until the current adjacent pair becomes valid.
=========================================================

APPROACH 1: GREEDY SIMULATION

- Intuition:
  Whenever two adjacent characters are equal, at least one
  of them must eventually be replaced with '?'.

- Approach:
  1. Traverse the string from left to right.
  2. If adjacent characters are equal and not '?',
     replace s[p[days]] with '?'.
  3. Increment days after every replacement.
  4. Continue until the current pair becomes valid.

- Why it Works:
  We process every adjacent pair and perform replacements
  in the exact order specified by the permutation.
  Every replacement resolves at least the currently
  problematic pair once one of its positions is selected.

- Time Complexity (TC): O(N)
  Each position and permutation element is processed
  at most once.

- Space Complexity (SC): O(1)
  The given string is modified directly.

FINAL APPROACH:
Greedy simulation is optimal because we process the required
replacements directly without repeatedly checking the entire
string. Every permutation index is consumed at most once,
giving O(N) time and O(1) auxiliary space.
=========================================================
*/

class Solution {
public:
    int getMinimumDays(string &s, vector<int> &p) {

        int n = s.size();
        int days = 0;

        for (int i = 0; i < n - 1; i++) {

            while (s[i] != '?' && s[i] == s[i + 1]) {

                s[p[days]] = '?';

                days++;
            }
        }

        return days;
    }
};
