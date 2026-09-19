/*
=========================================================
Date        : 19-09-2026
Problem Name: Min Cost To Make Two Strings Identical
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Dynamic Programming, Strings, LCS

Problem Summary:
Given two strings s1 and s2 along with deletion costs costS1 and costS2.
Find the minimum cost required to make both strings identical by deleting
characters from either string while maintaining the relative order.

Key Observation:
To minimize deletion cost, we must maximize the preserved characters.
The characters that remain in both strings must form a common subsequence.
Specifically, we find the Longest Common Subsequence (LCS) to maximize savings.
=========================================================
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Recursion (Brute Force)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  At each character pair (i, j), we either match them if equal, or branch into
  deleting from s1 or deleting from s2 to find the minimum cost.

• Approach:
  Explore all combinations of deletions recursively from the end of both strings.

• Why it Works:
  It exhaustively searches the entire solution space of all valid common subsequences.

• Time Complexity (TC) : O(2^(n + m)) - Exponential branching at every mismatch.
• Space Complexity (SC): O(n + m) - Recursive call stack depth.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Dynamic Programming - LCS Table (Better)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Instead of generic recursion, compute the length of the Longest Common Subsequence (LCS).
  Any character not part of the LCS must be deleted.

• Approach:
  Build a 2D table dp[n+1][m+1] where dp[i][j] stores the LCS length of s1[0..i-1] and s2[0..j-1].
  Final Cost = (n - lcs_len) * costS1 + (m - lcs_len) * costS2.

• Why it Works:
  Maximizing identical characters preserved minimizes the count of deleted characters.

• Time Complexity (TC) : O(n * m) - Two nested loops of size n and m.
• Space Complexity (SC): O(n * m) - 2D DP matrix storage.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 3: Space-Optimized Dynamic Programming (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Notice that computing the current row of the DP table only requires values
  from the previous row and the current row itself.

• Approach:
  Use two 1D arrays (`prev` and `curr`) of size (m + 1) to iteratively compute the LCS length.
  Update `prev = curr` after processing each character of s1.

• Why it Works:
  Preserves the optimal substructure of LCS while discarding older rows that are no longer needed.

• Time Complexity (TC) : O(n * m) - Standard LCS transition steps.
• Space Complexity (SC): O(m) - Reduced auxiliary space to two 1D vectors.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH SELECTION:
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
We select Approach 3 (Space-Optimized DP).
It achieves the optimal O(n * m) time complexity required by the constraints (up to 1000x1000)
while drastically reducing memory usage from O(n * m) down to O(m), making it cache-friendly
and immune to potential stack or memory limits.
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

class Solution {
public:
    int findMinCost(string &s1, string &s2, int costS1, int costS2) {
        int n = s1.size();
        int m = s2.size();

        // prev[j] stores LCS length for s1 up to previous character and s2 up to j
        vector<int> prev(m + 1, 0);
        vector<int> curr(m + 1, 0);

        // Compute LCS length
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                if (s1[i - 1] == s2[j - 1]) {
                    curr[j] = 1 + prev[j - 1];
                } else {
                    curr[j] = max(prev[j], curr[j - 1]);
                }
            }
            prev = curr;
        }

        int lcsLength = prev[m];

        // Cost of characters to delete from s1 and s2
        int deletionsS1 = n - lcsLength;
        int deletionsS2 = m - lcsLength;

        return (deletionsS1 * costS1) + (deletionsS2 * costS2);
    }
};
