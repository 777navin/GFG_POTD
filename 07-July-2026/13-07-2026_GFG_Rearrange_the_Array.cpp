/*
=========================================================
Date        : 13-07-2026
Problem Name: Rearrange the Array
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Mathematical, Permutation, Disjoint Set Union (DSU), Graphs

Problem Summary:
Given a 1-based permutation array b[] of size n and an initial array a[] = [1, 2, 3, ..., n]. 
In each operation, the element at position i moves to position b[i]. We need to find the 
minimum non-zero number of operations required to restore a[] to its initial state, modulo 10^9+7.

Key Observation:
The permutation can be broken down into multiple independent, disjoint cyclic components. 
The entire array returns to its original state when all individual cycles simultaneously complete 
their periods, which equals the Least Common Multiple (LCM) of all cycle lengths.
=========================================================
*/

#include <vector>
#include <numeric>
#include <map>

using namespace std;

/*
=========================================================
APPROACH 1: Cycle Length Extraction + LCM via Prime Factorization
=========================================================
• Intuition:
  The permutation forms a directed graph where each node has an out-degree of 1 and in-degree of 1, 
  guaranteeing a collection of disjoint cycles. The answer is the LCM of all cycle lengths. Since 
  the LCM result can be extremely large, we cannot compute it directly using standard integer types 
  before applying the modulo. Instead, we must maintain the prime factorization of the LCM.

• Approach:
  1. Traverse the array to find all unvisited cycles and calculate their lengths.
  2. For each cycle length, find its prime factorization.
  3. Track the maximum exponent for each prime factor seen across all cycle lengths using a global map.
  4. Compute the final answer by multiplying these highest prime powers together, modulo 10^9+7.

• Why it Works:
  Standard LCM calculation via `(LCM * length) / GCD` causes arithmetic overflow prior to taking 
  the modulo. Prime factorization allows us to safely accumulate the LCM value without overflow 
  by applying the modulo operator during the final product phase.

• Time Complexity (TC): 
  O(N * sqrt(N)) worst case for prime factorization of each cycle length, though practically much faster 
  as the sum of cycle lengths is N.
• Space Complexity (SC): 
  O(N) to store visited states and prime factors tracking.
*/

/*
=========================================================
FINAL APPROACH WHY CHOSEN:
=========================================================
This prime factorization approach is selected because calculating the LCM directly over a large set 
of numbers whose product exceeds standard 64-bit integer limits is impossible without modular arithmetic. 
Since LCM does not distribute over modulo (i.e., LCM(x, y) % M != LCM(x % M, y % M)), maintaining 
the maximal prime factor frequencies ensures mathematical correctness while avoiding overflow.
*/

class Solution {
public:
    int minOperations(vector<int> &b) {
        int n = b.size();
        vector<bool> visited(n, false);
        map<int, int> max_prime_powers;
        long long MOD = 1e9 + 7;

        // Step 1: Find the lengths of all disjoint cycles
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                int curr = i;
                int cycle_length = 0;
                
                while (!visited[curr]) {
                    visited[curr] = true;
                    // Convert 1-based indexing from input to 0-based indexing
                    curr = b[curr] - 1; 
                    cycle_length++;
                }

                // Step 2: Factorize the cycle length and update global prime power requirements
                int temp = cycle_length;
                for (int p = 2; p * p <= temp; p++) {
                    if (temp % p == 0) {
                        int count = 0;
                        while (temp % p == 0) {
                            count++;
                            temp /= p;
                        }
                        max_prime_powers[p] = max(max_prime_powers[p], count);
                    }
                }
                if (temp > 1) {
                    max_prime_powers[temp] = max(max_prime_powers[temp], 1);
                }
            }
        }

        // Step 3: Compute the LCM modulo 10^9 + 7 from the collected prime powers
        long long ans = 1;
        for (auto const& [prime, exponent] : max_prime_powers) {
            long long power_val = 1;
            for (int i = 0; i < exponent; i++) {
                power_val = (power_val * prime) % MOD;
            }
            ans = (ans * power_val) % MOD;
        }

        return ans;
    }
};
