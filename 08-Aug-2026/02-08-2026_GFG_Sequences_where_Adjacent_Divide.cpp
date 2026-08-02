/*
=========================================================
Date        : 02-08-2026
Problem Name: Sequences where Adjacent Divide
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Dynamic Programming, Math

Problem Summary:
Find the total number of valid arrays of size 'n' where 
each element is in the range [1, m]. Every pair of 
adjacent elements must perfectly divide one another 
(i.e., A[i] divides A[i+1] or A[i+1] divides A[i]).

Key Observation:
The valid choices for the i-th element in the sequence 
depend solely on the (i-1)-th element. This optimal 
substructure allows us to count sequences using 1D DP.
=========================================================
*/

/*
=========================================================
1. Brute Force (Backtracking)
=========================================================
• Intuition: Try placing all possible valid elements from 1 to m at each of the n positions.
• Approach: Use a recursive function to build the array, ensuring the adjacent divisibility rule is met.
• Why it Works: It exhaustively searches the entire valid state space of sequences.
• Time Complexity (TC): O(M^N) - Exponential branching for each array position.
• Space Complexity (SC): O(N) - Maximum depth of the recursion stack.

=========================================================
2. Better (Dynamic Programming)
=========================================================
• Intuition: The count of valid arrays ending at length `i` with value `j` only depends on the results of length `i-1`.
• Approach: Maintain a DP array `dp[j]` representing the count of sequences ending in `j`. Update it iteratively by checking all pairs `(j, k)`.
• Why it Works: Eliminates redundant calculations of overlapping subproblems.
• Time Complexity (TC): O(N * M^2) - Three nested loops checking every combination of elements.
• Space Complexity (SC): O(M) - Two 1D arrays to store current and next states.

=========================================================
3. Most Optimal (DP with Divisor/Multiple Iteration)
=========================================================
• Intuition: Instead of iterating through all M elements to check divisibility, mathematically target the exact valid transitions.
• Approach: For a fixed element `j`, calculate its next state strictly by summing `dp[k]` where `k` is either a divisor or a multiple of `j`.
• Why it Works: Bypasses the vast majority of invalid `(j, k)` pairs, updating states rapidly.
• Time Complexity (TC): O(N * M log M) - Harmonic sum traversal for multiples and O(sqrt(M)) for divisors.
• Space Complexity (SC): O(M) - Two 1D arrays for DP transitions.
*/

/*
=========================================================
FINAL APPROACH: Most Optimal
• Chosen because it scales efficiently, even if constraints were unexpectedly raised to 10^5.
• By restricting inner loop traversals only to mathematical multiples and divisors, we avoid unnecessary modulo operations. 
=========================================================
*/

#include <vector>
using namespace std;

class Solution {
public:
    int count(int n, int m) {
        // Edge case
        if (n == 0) return 0;

        // dp[j] stores the number of valid sequences of the current length ending with j.
        // Base state for length 1: exactly 1 valid sequence for each number from 1 to m.
        vector<int> dp(m + 1, 1);
        dp[0] = 0; // 1-based indexing constraint 

        // Iteratively build valid sequences up to length n
        for (int i = 2; i <= n; ++i) {
            vector<int> next_dp(m + 1, 0);

            for (int j = 1; j <= m; ++j) {
                
                // 1. Add sequences where the previous element 'k' is a DIVISOR of 'j'
                for (int k = 1; k * k <= j; ++k) {
                    if (j % k == 0) {
                        next_dp[j] += dp[k];
                        // If k is not the perfect square root, add its complementary divisor pair
                        if (k * k != j) {
                            next_dp[j] += dp[j / k];
                        }
                    }
                }

                // 2. Add sequences where the previous element 'k' is a MULTIPLE of 'j'
                // Loop starts at j * 2 to strictly prevent double-counting 'j' itself
                for (int k = j * 2; k <= m; k += j) {
                    next_dp[j] += dp[k];
                }
            }

            // Transition state to next array length
            dp = next_dp;
        }

        // Aggregate total valid sequences of length n
        int total_sequences = 0;
        for (int j = 1; j <= m; ++j) {
            total_sequences += dp[j];
        }

        return total_sequences;
    }
};
