/*
=========================================================
Date        : 18-08-2026
Problem Name: Secret Cipher
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Strings, KMP, Prefix Function, Greedy

Problem Summary:
Given a string s, compress it by replacing any repeated prefix
block with '*'. Decoding replaces '*' with all characters that
came before it. Find the shortest/smallest encoded string.

Key Observation:
Working backwards greedily from the end, if a prefix of even length
2k consists of two identical halves (s[0...k-1] == s[k...2k-1]),
we can replace the second half with '*' and jump to index k-1.
=========================================================
*/

// =========================================================
// APPROACH 1: Brute Force (Substrings Comparison)
// =========================================================
// • Intuition: Traverse backwards from n - 1. For every even length prefix 2k, extract both halves and compare them character by character.
// • Approach: If s.substr(0, k) == s.substr(k, k), append '*' and move pointer to k - 1; otherwise append s[i] and decrement i by 1.
// • Why it Works: Directly simulates the reverse decoding process step-by-step.
// • Time Complexity (TC): O(N^2) due to substring creation and comparison at each step.
// • Space Complexity (SC): O(N) for storing the result and temporary substrings.

// =========================================================
// APPROACH 2: Optimized (KMP / LPS Array + Periodicity)
// =========================================================
// • Intuition: A prefix of length 2k consists of two identical halves iff its border length satisfies KMP periodicity properties.
// • Approach:
//   1. Precompute the KMP Longest Prefix Suffix (LPS) array for string s in O(N).
//   2. Traverse from i = n - 1 down to 0.
//   3. If i is odd (length N = i + 1 is even), check if lps[i] >= N / 2 and N % (2 * (N - lps[i])) == 0.
//   4. If true, push '*' and jump to i = N / 2 - 1; otherwise push s[i] and i--.
//   5. Reverse the resulting string.
// • Why it Works: LPS values capture the minimal period p = N - lps[i]; if 2p divides N, the second half perfectly mirrors the first half.
// • Time Complexity (TC): O(N) linear time for LPS computation and single backward pass.
// • Space Complexity (SC): O(N) for LPS array and result storage.

// =========================================================
// FINAL APPROACH: KMP Longest Prefix Suffix (LPS) Array
// =========================================================
// • Why this approach is chosen:
//   It reduces string matching and prefix repetition verification to O(1) per index after an O(N) preprocessing phase.
// • Why it is better:
//   Avoids expensive O(N^2) substring comparisons and easily handles large constraints (N <= 10^5) within the 1-second limit.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
private:
    void computeLPS(const string& s, vector<int>& lps) {
        int n = s.length();
        int len = 0;
        lps[0] = 0;
        int i = 1;

        while (i < n) {
            if (s[i] == s[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                if (len != 0) {
                    len = lps[len - 1];
                } else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

public:
    string compress(string& s) {
        int n = s.length();
        if (n == 0) return "";

        vector<int> lps(n, 0);
        computeLPS(s, lps);

        string encoded = "";
        int i = n - 1;

        while (i >= 0) {
            int len = i + 1;
            // Check if current prefix length is even and formed by two identical halves
            if (i % 2 == 1 && lps[i] >= len / 2 && (len % (2 * (len - lps[i])) == 0)) {
                encoded.push_back('*');
                i = len / 2 - 1; // Jump to end of first half
            } else {
                encoded.push_back(s[i]);
                i--;
            }
        }

        reverse(encoded.begin(), encoded.end());
        return encoded;
    }
};
