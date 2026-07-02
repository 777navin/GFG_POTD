/*
=========================================================
Date        : 02-07-2026
Problem Name: Check Subset sum divisible by k
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Dynamic Programming, Subset Sum, Pigeonhole Principle, Mathematics

Problem Summary:
Given an array arr[] of positive integers and a value k. Return true if the sum of any non-empty subset of the given array is divisible by k. Otherwise, return false.

Constraints:
1 <= arr.size(), k <= 10^3
1 <= arr[i] <= 10^3

Key Observation:
According to the Pigeonhole Principle, if the size of the array (N) is greater than or equal to k, there will ALWAYS be at least one subarray (and therefore a subset) whose sum is completely divisible by k. Thus, for N >= k, the answer is unconditionally true. For N < k, we can use a space-optimized Dynamic Programming approach to track the reachable remainders modulo k.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
STEP 3: INCLUDE EVERY POSSIBLE APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Brute Force (Recursive Subset Generation)
• Intuition: Check every single possible subset configuration to see if its sum modulo k equals 0.
• Idea: Use recursion to either include or exclude the current element in our subset sum.
• Approach: Maintain a running sum. For each element, branch into two recursive calls (pick or don't pick). Check if the sum % k == 0 for any valid non-empty subset.
• Dry Run: arr = [1, 2, 6], k = 5. Subsets: {1}, {2}, {6}, {1,2}, {1,6}, {2,6}, {1,2,6}. Sums: 1, 2, 6, 3, 7, 8, 9. None of these modulo 5 equal 0. Return false.
• Why it works: It exhaustively searches the entire solution space.
• Time Complexity: O(2^N)
• Space Complexity: O(N) for the recursive call stack.
• Advantages: Extremely simple to understand and implement.
• Disadvantages: Exponential time complexity leads to Time Limit Exceeded (TLE) for N > 20.
• When to use: Only when N is very small (e.g., N <= 15).
• Why next approach is better: We are repeatedly calculating sums that yield the same remainders. We can track remainders dynamically instead.

2. Dynamic Programming (1D Space Optimized)
• Intuition: The divisibility depends purely on the remainders modulo k.
• Idea: Maintain a boolean array of size k to mark which remainders are achievable using a subset of the elements seen so far.
• Approach: Initialize a dp array of size k to false. For each element in the array, find its remainder. Create a temporary next_dp array. If a remainder j is true in dp, then (j + remainder) % k becomes true in next_dp. Also, mark the single element's remainder as true. Stop early if index 0 becomes true.
• Dry Run: arr = [3, 1, 7, 5], k = 6.
  - 3 % 6 = 3. dp[3] = true.
  - 1 % 6 = 1. dp[1] = true, dp[(3+1)%6] -> dp[4] = true.
  - 7 % 6 = 1. dp[1] = true, dp[(1+1)%6] -> dp[2] = true, dp[(4+1)%6] -> dp[5] = true.
  - 5 % 6 = 5. dp[5] = true, dp[(1+5)%6] -> dp[0] = true! Return true.
• Why it works: Uses the modular arithmetic property (A + B) % k = ((A % k) + (B % k)) % k.
• Time Complexity: O(N * k)
• Space Complexity: O(k) for the 1D dp array.
• Advantages: Efficient and perfectly fits standard constraints.
• Disadvantages: Unnecessary computation if N is significantly larger than k.
• When to use: When N and k are within limits like 10^3.
• Why next approach is better: It leverages mathematical properties to achieve an O(1) conditional check for large N, drastically reducing runtime.

3. Most Optimal (Pigeonhole Principle + DP)
• Intuition: If we have k or more elements, the mathematical properties of combinations guarantee a multiple of k exists.
• Idea: Apply the Pigeonhole Principle. There are exactly k possible remainders (0 to k-1). If we calculate prefix sums, by the time we process k elements, at least two prefix sums must have the exact same remainder modulo k. The difference between these two prefix sums represents a subarray whose sum is completely divisible by k. Since a subarray is a subset, the answer is always true if N >= k.
• Approach: If N >= k, return true immediately. Otherwise, N < k, so we fall back to the 1D DP approach which will now strictly take O(k^2) time at worst.
• Dry Run: arr length is 1500, k = 1000. Since 1500 >= 1000, immediately return true without any iteration.
• Why it works: Pure mathematical certainty via the Pigeonhole Principle.
• Time Complexity: O(k^2) in the worst case (since N < k when the DP runs).
• Space Complexity: O(k) for the DP array.
• Advantages: Instantly solves the problem for massive arrays.
• Disadvantages: None.
• When to use: Always the best approach for subset/subarray modulo divisibility problems.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
STEP 4: COMPARISON TABLE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
-------------------------------------------------------
Method              Idea                        Time        Space   Difficulty  Recommended
Brute Force         Explore all subsets         O(2^N)      O(N)    Easy        No
DP (1D Optimized)   Track remainder states      O(N * k)    O(k)    Medium      Yes
Pigeonhole + DP     Math check + DP fallback    O(k^2)      O(k)    Hard        Highly
-------------------------------------------------------
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
STEP 5: FINAL RECOMMENDED APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
The Pigeonhole Principle + 1D DP is the most optimal solution. It intelligently identifies that computing the DP is entirely redundant when the array size meets or exceeds k. For arrays smaller than k, it smoothly transitions into a highly space-optimized O(k) Dynamic Programming sequence, guaranteeing the absolute best performance possible in both time and memory.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
STEP 6: CODE GENERATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
*/

class Solution {
public:
    bool divisibleByK(vector<int>& arr, int k) {
        int n = arr.size();
        
        // Pigeonhole Principle: 
        // If elements are >= k, there's always a subarray (and thus a subset) divisible by k.
        if (n >= k) {
            return true;
        }

        // 1D DP array to track achievable remainders
        vector<bool> dp(k, false);

        for (int i = 0; i < n; i++) {
            int rem = arr[i] % k;
            
            // If the element itself is a multiple of k
            if (rem == 0) {
                return true;
            }

            // Temporary array for simultaneous state updates
            vector<bool> next_dp = dp;
            
            // Include the single element's remainder
            next_dp[rem] = true;

            // Try adding the current remainder to all previously achievable remainders
            for (int j = 0; j < k; j++) {
                if (dp[j]) {
                    int next_rem = (j + rem) % k;
                    if (next_rem == 0) {
                        return true;
                    }
                    next_dp[next_rem] = true;
                }
            }
            
            // Propagate states forward
            dp = next_dp;
        }

        return false;
    }
};
