/*
=========================================================
Date        : 10-09-2026
Problem Name: Pairs with Given GCD and LCM
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Mathematics, Factorization, Number Theory

Problem Summary:
Given two integers x and y representing the GCD and LCM
of two positive integers a and b, count all valid pairs (a, b)
satisfying both conditions. Pairs (a, b) and (b, a) are
counted as distinct when a != b.

Key Observation:
For valid pairs to exist, y must be divisible by x. If y % x == 0,
the problem reduces to finding pairs of coprime factors (u, v)
such that u * v = y / x.
=========================================================
*/

#include <numeric>

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Brute Force
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Iterate through all possible pairs (a, b) in the range [x, y]
  and check if their gcd equals x and lcm equals y.

• Approach:
  Run nested loops for a and b from x to y. Compute std::gcd(a, b)
  and its corresponding lcm = (a / gcd) * b. Increment the counter
  whenever both match the given x and y.

• Why it Works:
  It exhaustively verifies the definition of GCD and LCM across all
  candidate values in the permissible search space.

• Time Complexity (TC):
  O((y - x + 1)^2 * log(y)) - Quadratic iteration over the range with
  logarithmic gcd computation.

• Space Complexity (SC):
  O(1) - Only scalar variables are used.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Optimized (Coprime Factor Pairs)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Let a = x * u and b = x * v where gcd(u, v) = 1.
  Then lcm(a, b) = x * u * v = y, which simplifies to u * v = y / x.
  Valid pairs correspond directly to coprime factor pairs of n = y / x.

• Approach:
  1. Check if y % x != 0; if so, return 0.
  2. Let n = y / x. If n == 1, exactly 1 pair (x, x) exists.
  3. Iterate i from 1 to floor(sqrt(n)). If i divides n, let j = n / i.
  4. If std::gcd(i, j) == 1:
     - If i == j, add 1 to the count.
     - If i != j, add 2 (for (a, b) and (b, a)).

• Why it Works:
  Every unique pair of coprime factors of (y / x) uniquely maps to a valid
  pair (x * u, x * v) satisfying gcd = x and lcm = y.

• Time Complexity (TC):
  O(sqrt(y / x) * log(y / x)) - Checks divisors up to sqrt(n) with
  logarithmic gcd checks.

• Space Complexity (SC):
  O(1) - Constant auxiliary space.
*/

/*
=========================================================
FINAL APPROACH:
The Coprime Factor Pairs approach is chosen because it operates
in O(sqrt(y / x) * log(y / x)) instead of brute-forcing all pairs
up to O((y - x)^2). This reduces iterations from up to 10^8 down
to at most 100 steps for y <= 10^4, avoiding any TLE risk.
=========================================================
*/

class Solution {
  public:
    int pairCount(int x, int y) {
        // LCM must be a multiple of GCD
        if (y % x != 0) {
            return 0;
        }

        int n = y / x;
        int count = 0;

        // Find all factor pairs (i, j) of n such that gcd(i, j) == 1
        for (long long i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                long long j = n / i;

                if (std::gcd(i, j) == 1) {
                    if (i == j) {
                        count += 1;
                    } else {
                        count += 2; // (x*i, x*j) and (x*j, x*i) are distinct
                    }
                }
            }
        }

        return count;
    }

    // Alias to support alternative function naming conventions on GFG
    int countPairs(int x, int y) {
        return pairCount(x, y);
    }
};
