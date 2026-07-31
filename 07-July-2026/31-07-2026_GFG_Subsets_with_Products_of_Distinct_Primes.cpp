/*
=========================================================
Date        : 31-07-2026
Problem Name: Subsets with Products of Distinct Primes (Game of Subsets)
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Dynamic Programming, Bitmask, Number Theory, Math

Problem Summary:
Given an array arr[] of positive integers, count the number of subsets whose product 
can be represented as a product of one or more distinct prime numbers.
Subsets formed by different indices are considered distinct.
Return the answer modulo 10^9 + 7.

Key Observation:
Since arr[i] <= 30, the relevant primes <= 30 are only 10: {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}.
Any number with repeated prime factors (4, 8, 9, 12, 16, 18, 20, 24, 25, 27, 28) can never be included.
Numbers with distinct prime factors can be represented as a 10-bit mask. The number 1 can be included 
any number of times without altering prime products.
=========================================================
*/

/*
=========================================================
APPROACH 1: Bitmask Dynamic Programming
=========================================================
• Intuition:
  Since elements are <= 30, there are only 10 primes up to 30. We can represent the selection 
  of primes in a subset product using a 10-bit integer mask.

• Approach:
  1. Filter out numbers divisible by square primes (> 1).
  2. Count frequencies of all valid numbers in arr[].
  3. Use DP state `dp[mask]` = number of valid subsets formed so far with prime mask `mask`.
  4. For each valid number x (from 2 to 30) with frequency `cnt`:
     - Represent x as a bitmask of its prime factors.
     - For each existing DP state `prev_mask` that doesn't overlap with x's mask (`(prev_mask & x_mask) == 0`):
       - `new_dp[prev_mask | x_mask] = (new_dp[prev_mask | x_mask] + dp[prev_mask] * cnt) % MOD`
  5. Account for '1': 1 doesn't add any prime factors, but each 1 can either be included or excluded. 
     Multiply total non-empty subsets by 2^(count of 1s).

• Why it Works:
  Disjoint prime masks ensure that no prime factor is repeated in any subset product, 
  satisfying the distinct prime product condition.

• Time Complexity (TC):
  O(N + MAX_VAL * 2^P), where MAX_VAL = 30 and P = 10 (number of primes <= 30).
  2^10 = 1024, so this runs well within milliseconds.

• Space Complexity (SC):
  O(2^P) = O(1024) auxiliary space for the DP array.
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
• The Bitmask DP approach is optimal because the value constraint arr[i] <= 30 makes the prime count 
  extremely small (10 primes).
• It reduces an exponential subset problem O(2^N) down to O(N + 30 * 2^10), easily passing within execution limits.
*/

#include <vector>

using namespace std;

class Solution {
public:
    int countSubsets(vector<int>& arr) {
        const int MOD = 1e9 + 7;
        
        // Primes up to 30
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
        
        // Map each number x from 2 to 30 to its prime mask if square-free, else -1
        vector<int> prime_mask(31, 0);
        for (int i = 2; i <= 30; ++i) {
            int temp = i;
            int mask = 0;
            bool is_square_free = true;
            
            for (int p_idx = 0; p_idx < 10; ++p_idx) {
                int p = primes[p_idx];
                if (temp % p == 0) {
                    temp /= p;
                    if (temp % p == 0) { // Divisible by p^2
                        is_square_free = false;
                        break;
                    }
                    mask |= (1 << p_idx);
                }
            }
            if (is_square_free) {
                prime_mask[i] = mask;
            } else {
                prime_mask[i] = -1; // Invalid number containing repeated prime factors
            }
        }

        // Count frequency of each number in input array
        vector<int> freq(31, 0);
        for (int x : arr) {
            freq[x]++;
        }

        // DP array: dp[mask] = ways to get subset product represented by mask
        vector<long long> dp(1 << 10, 0);
        dp[0] = 1; // Base case: 1 way to get empty mask

        // Process numbers from 2 to 30
        for (int i = 2; i <= 30; ++i) {
            if (freq[i] == 0 || prime_mask[i] == -1) continue;

            int mask = prime_mask[i];
            long long count = freq[i];

            // Iterate backwards to use values from previous state
            for (int prev_mask = (1 << 10) - 1; prev_mask >= 0; --prev_mask) {
                if ((prev_mask & mask) == 0 && dp[prev_mask] > 0) {
                    dp[prev_mask | mask] = (dp[prev_mask | mask] + dp[prev_mask] * count) % MOD;
                }
            }
        }

        // Sum all valid subset configurations (mask > 0 because subset product must have distinct primes)
        long long total_subsets = 0;
        for (int mask = 1; mask < (1 << 10); ++mask) {
            total_subsets = (total_subsets + dp[mask]) % MOD;
        }

        // Handle the number '1': each 1 doubles the number of valid subsets (include or exclude)
        long long power_of_two = 1;
        for (int i = 0; i < freq[1]; ++i) {
            power_of_two = (power_of_two * 2) % MOD;
        }

        total_subsets = (total_subsets * power_of_two) % MOD;

        return total_subsets;
    }
};
