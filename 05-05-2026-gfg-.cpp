/*
Date: 05-05-2026
Problem Name: Sum of XOR of all pairs
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Bit Manipulation, Arrays, Mathematical

Problem Summary:
Given an integer array `arr[]` of size `n`, compute the sum of the bitwise XOR for all distinct pairs of elements. Return the total sum of `(arr[i] XOR arr[j])` for all valid pairs where `0 <= i < j < n`.

Methods to Solve:
1. Brute Force
2. Optimal Approach (Bit Manipulation)

---------------------------------------------------------
Method 1: Brute Force
- Intuition: The simplest way to find the sum of XOR of all pairs is to generate all possible pairs, compute their XOR, and add it to a running total.
- Approach: Use two nested loops. The outer loop runs from `i = 0` to `n-1`, and the inner loop runs from `j = i+1` to `n-1`. For each pair, calculate `arr[i] ^ arr[j]` and add it to `total_sum`.
- Dry Run: For `arr = [7, 3, 5]`:
  - 7 ^ 3 = 4
  - 7 ^ 5 = 2
  - 3 ^ 5 = 6
  - Sum = 4 + 2 + 6 = 12
- Time Complexity: O(N^2) - We are iterating through all pairs.
- Space Complexity: O(1) - No extra space is used.
- Why better than previous method: N/A (Baseline).
- When to use: When N is very small (N <= 10^3) and time limits are relaxed.

---------------------------------------------------------
Method 2: Optimal Approach (Bit Manipulation)
- Intuition: Instead of calculating pairs directly, we can analyze the contribution of each bit position (from 0 to 31) across all numbers. A bit at position `i` will contribute to the total XOR sum only if it is `1` in one number and `0` in the other number of a pair.
- Approach:
  1. Iterate through each bit position `i` from `0` to `31`.
  2. For each bit position, count how many numbers in the array have the `i-th` bit set (`one_cnt`) and how many have it unset (`zero_cnt`).
  3. The number of pairs that will have the `i-th` bit set in their XOR result is exactly `one_cnt * zero_cnt`.
  4. The contribution of these pairs to the total sum is `(one_cnt * zero_cnt) * (1 << i)`.
  5. Add this contribution to the total sum.
- Dry Run: For `arr = [7, 3, 5]` (in binary: 7=111, 3=011, 5=101):
  - Bit 0: 7(1), 3(1), 5(1) -> ones=3, zeros=0. Pairs=0. Contrib = 0 * 1 = 0
  - Bit 1: 7(1), 3(1), 5(0) -> ones=2, zeros=1. Pairs=2. Contrib = 2 * 2 = 4
  - Bit 2: 7(1), 3(0), 5(1) -> ones=2, zeros=1. Pairs=2. Contrib = 2 * 4 = 8
  - Total sum = 0 + 4 + 8 = 12.
- Time Complexity: O(N * 32) -> O(N) - We iterate through the array 32 times.
- Space Complexity: O(1) - Constant space used.
- Why better than previous method: Reduces time complexity from quadratic to linear, easily passing the constraints for N = 10^5.
- When to use: Always for this problem, especially for large arrays.

---------------------------------------------------------
Comparison Table:
Method          | TC      | SC   | Best Use Case
----------------|---------|------|-----------------------
Brute Force     | O(N^2)  | O(1) | Small arrays (N <= 1000)
Optimal (Bits)  | O(N)    | O(1) | Large arrays (N <= 10^5)

Final Recommended Solution: Optimal Approach (Bit Manipulation)
*/

#include <iostream>
#include <vector>

using namespace std;

// GFG Platform Block
class Solution {
public:
    long long sumXOR(vector<int>& arr) {
        long long total_sum = 0;
        int n = arr.size();
        
        // Iterate through each bit position from 0 to 31
        for (int i = 0; i < 32; i++) {
            long long zero_cnt = 0, one_cnt = 0;
            
            // Count numbers with the i-th bit set and unset
            for (int j = 0; j < n; j++) {
                if (arr[j] & (1 << i)) {
                    one_cnt++;
                } else {
                    zero_cnt++;
                }
            }
            
            // Number of pairs where i-th bit contributes to XOR
            long long pairs = zero_cnt * one_cnt;
            
            // Add the contribution to the total sum safely using 1LL to prevent overflow
            total_sum += pairs * (1LL << i);
        }
        
        return total_sum;
    }
};

// Driver code to test the solution locally (GitHub Ready)
