/*
=========================================================
Date        : 22-09-2026
Problem Name: Longest Matching in Dictionary with Removals
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Two-Pointers, Strings, Sorting

Problem Summary:
Given a string 's' and a dictionary of strings 'd[]', find the longest word in 'd'
that can be formed by deleting characters from 's' without changing their order.
If multiple words share the maximum length, return the lexicographically smallest.

Key Observation:
A word can be formed from 's' if and only if it is a subsequence of 's'.
Checking subsequence takes linear time using two pointers.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Check Each Word Individually (Without Sorting)
---------------------------------------------------------
• Intuition:
  Iterate through each word in the dictionary, check if it is a subsequence of 's',
  and maintain the best word seen so far based on length and lexicographical order.

• Approach:
  - Initialize result string as empty.
  - For each word in 'd', use two pointers to verify if it is a subsequence of 's'.
  - If valid, update result if word.length() > result.length() or
    (word.length() == result.length() && word < result).

• Why it Works:
  Directly checks all candidates against 's' and applies the selection criteria
  on valid matches.

• Time Complexity (TC):
  O(n * |s|), where n is the number of words in 'd' and |s| is the length of string 's'.

• Space Complexity (SC):
  O(1) auxiliary space (excluding result storage).
---------------------------------------------------------

---------------------------------------------------------
APPROACH 2: Custom Sorting + Subsequence Check (Optimal)
---------------------------------------------------------
• Intuition:
  Sort the dictionary words such that longer words come first, and words of the same
  length appear in lexicographical order. The first valid subsequence found is guaranteed to be the answer.

• Approach:
  - Sort dictionary 'd' using a custom comparator:
    Length descending: a.length() > b.length()
    Lexicographical ascending if lengths tie: a < b
  - Iterate through sorted 'd'. For each word, test if it is a subsequence of 's' using two pointers.
  - Return the very first word that matches. If none match, return an empty string.

• Why it Works:
  The custom sorting directly encodes the priority criteria, allowing early termination
  as soon as the first valid match is encountered.

• Time Complexity (TC):
  O(n * log(n) * m + k * |s|), where m is max word length in 'd', and k is the number of words checked before finding a match (k <= n).

• Space Complexity (SC):
  O(1) auxiliary space (or O(log n) sorting stack space).
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Custom Sorting + Subsequence Check
=========================================================
• Why this approach is chosen:
  It provides an optimal, clean solution that avoids checking all words once the best match is found.
• Why it is better than previous ones:
  By sorting up front by length (descending) and lexicographical order (ascending),
  we can immediately return the first match without tracking and comparing candidates throughout the entire array.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    // Helper function to check if word is a subsequence of s
    bool isSubsequence(const string &word, const string &s) {
        int i = 0, j = 0;
        int n = word.length(), m = s.length();
        
        while (i < n && j < m) {
            if (word[i] == s[j]) {
                i++;
            }
            j++;
        }
        return i == n;
    }

public:
    string findLongestWord(string &s, vector<string> &d) {
        // Sort: primary by length descending, secondary by lexicographical ascending
        sort(d.begin(), d.end(), [](const string &a, const string &b) {
            if (a.length() != b.length()) {
                return a.length() > b.length();
            }
            return a < b;
        });

        // The first word in sorted order that is a subsequence of s is our answer
        for (const string &word : d) {
            if (isSubsequence(word, s)) {
                return word;
            }
        }

        return "";
    }
};
