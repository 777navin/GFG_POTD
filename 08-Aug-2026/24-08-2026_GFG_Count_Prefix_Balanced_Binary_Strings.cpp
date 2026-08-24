/*
=========================================================
Date        : 24-08-2026
Problem Name: Count Prefix-Balanced Binary Strings
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Combinatorics, Dynamic Programming, Math

Problem Summary:
Given an integer n, count the number of binary strings of length 2*n
containing exactly n ones and n zeros such that every prefix of the
string contains at least as many ones as zeros. Return the answer modulo 10^9 + 7.

Key Observation:
This is equivalent to the classic Catalan number problem, where every prefix
must maintain count(1) >= count(0) and end with count(1) == count(0) == n.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Dynamic Programming (Catalan Recurrence)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - Decompose a valid string as "1" + A + "0" + B, where A and B are valid substrings.
• Approach:
  - Use DP table to compute C(n) = sum(C(i) * C(n - 1 - i)) for i from 0 to n - 1.
• Why it Works:
  - Enumerates all possible positions where the balance first hits 0.
• Time Complexity (TC): O(n^2)
• Space Complexity (SC): O(n)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Combinatorics with Modular Inverse (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - The n-th Catalan number is given by C(n) = (1 / (n + 1)) * nCr(2n, n).
• Approach:
  - Compute factorials up to 2n modulo 10^9 + 7.
  - Calculate C(n) = (2n)! / ((n + 1)! * n!) % MOD using Fermat's Little Theorem for modular inverse.
• Why it Works:
  - Directly evaluates the closed-form formula in O(n) time.
• Time Complexity (TC): O(n)
• Space Complexity (SC): O(n)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
The Combinatorial approach with modular inverse is chosen because:
1. It reduces time complexity from O(n^2) to O(n).
2. It easily satisfies 1 <= n <= 1000 constraints.
3. It has minimal memory overhead and avoids nested loops.
*/

#include <vector>

class Solution {
private:
    const int MOD = 1e9 + 7;

    long long power(long long base, long long exp) {
        long long res = 1;
        base %= MOD;
        while (exp > 0) {
            if (exp % 2 == 1) res = (res * base) % MOD;
            base = (base * base) % MOD;
            exp /= 2;
        }
        return res;
    }

    long long modInverse(long long n) {
        return power(n, MOD - 2);
    }

public:
    int prefixStrings(int n) {
        if (n <= 0) return 1;

        int limit = 2 * n;
        std::vector<long long> fact(limit + 1, 1);
        for (int i = 2; i <= limit; ++i) {
            fact[i] = (fact[i - 1] * i) % MOD;
        }

        // Catalan(n) = (2n)! / ((n + 1)! * n!)
        long long num = fact[2 * n];
        long long den = (fact[n + 1] * fact[n]) % MOD;

        long long ans = (num * modInverse(den)) % MOD;
        return (int)ans;
    }
};
