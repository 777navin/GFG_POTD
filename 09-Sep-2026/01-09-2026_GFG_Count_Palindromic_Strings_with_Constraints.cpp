/*
=========================================================
Date        : 01-09-2026
Problem Name: Count Palindromic Strings with Constraints
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Combinatorics, Math, Strings

Problem Summary:
Given integers n and k, count the number of palindromic strings of length 
at most n using the first k lowercase English letters.
Each character can appear at most twice in the entire string.
Return the answer modulo 10^9 + 7.

Key Observation:
In a palindrome, matching symmetric pairs consume 2 occurrences of a character, 
and the middle character (if odd length) consumes 1 occurrence.
Since no character can appear > 2 times, all chosen symmetric pairs and the middle 
character must use distinct characters from the alphabet of size k.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Combinatorics / Permutations
---------------------------------------------------------
• Intuition:
  - A palindrome of length L is determined by its first ceil(L / 2) characters.
  - If L = 2m (even): We need m distinct characters. The number of ways to pick and order them is P(k, m) = k * (k - 1) * ... * (k - m + 1).
  - If L = 2m + 1 (odd): We need m distinct characters for the pairs and 1 distinct character for the center, total (m + 1) distinct characters. The number of ways is P(k, m + 1).

• Approach:
  - Iterate length L from 1 to n.
  - Determine the number of distinct characters needed: d = (L + 1) / 2.
  - If d <= k, add P(k, d) % MOD to the total count.
  - Sum over all lengths 1 <= L <= n.

• Why it Works:
  - Each distinct character placed in the first half uniquely reflects to the second half, using exactly 2 occurrences.
  - The middle element uses exactly 1 occurrence.
  - No character is repeated beyond its allowed symmetric positions, guaranteeing frequency <= 2.

• Time Complexity (TC): O(n)
• Space Complexity (SC): O(1)
---------------------------------------------------------
*/

/*
---------------------------------------------------------
FINAL APPROACH:
- Chosen because n <= 52 and k <= 26, allowing an immediate O(n) sequential calculation of permutations.
- It directly computes the valid permutations without extra memory overhead and handles modular arithmetic cleanly.
---------------------------------------------------------
*/

class Solution {
public:
    int palindromicStrings(int n, int k) {
        const long long MOD = 1e9 + 7;
        long long totalCount = 0;

        for (int len = 1; len <= n; ++len) {
            int distinctNeeded = (len + 1) / 2;
            
            // If the required distinct characters exceed the alphabet size k,
            // no valid palindrome can be formed for this length.
            if (distinctNeeded > k) {
                continue;
            }

            // Calculate P(k, distinctNeeded) % MOD
            long long permutations = 1;
            for (int i = 0; i < distinctNeeded; ++i) {
                permutations = (permutations * (k - i)) % MOD;
            }

            totalCount = (totalCount + permutations) % MOD;
        }

        return totalCount;
    }
};
