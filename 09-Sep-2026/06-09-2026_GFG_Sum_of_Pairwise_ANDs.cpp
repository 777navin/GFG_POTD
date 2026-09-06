/*
=========================================================
Date        : 06-09-2026
Problem Name: Sum of Pairwise ANDs
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Bit Manipulation, Arrays, Mathematics

Problem Summary:
Given an array arr[] of integers, calculate the total sum 
of bitwise AND results for all pairs (arr[i], arr[j]) 
such that 0 <= i < j < arr.size().

Key Observation:
A particular bit position k contributes (1 << k) to the 
bitwise AND only if BOTH elements in the pair have the k-th 
bit set.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  Iterate over all pairs (i, j) with i < j and compute the 
  bitwise AND directly, accumulating the result.
• Approach:
  Use nested loops: outer loop runs from 0 to n - 1, inner 
  loop runs from i + 1 to n - 1. Sum up (arr[i] & arr[j]).
• Why it Works:
  It explicitly checks and adds the bitwise AND of every 
  valid pair according to the definition.
• Time Complexity (TC):
  O(n^2), where n is the size of the array.
• Space Complexity (SC):
  O(1), requiring no extra auxiliary memory.

---------------------------------------------------------
APPROACH 2: Bit Contribution (Optimal)
---------------------------------------------------------
• Intuition:
  Evaluate the sum bit by bit independently instead of 
  generating all pairs.
• Approach:
  For each bit position from 0 to 31:
  - Count how many elements have the k-th bit set (say, count).
  - The number of pairs having the k-th bit set is count * (count - 1) / 2.
  - Add (count * (count - 1) / 2) * (1LL << k) to the total sum.
• Why it Works:
  The k-th bit of (A & B) is 1 if and only if the k-th bit 
  of both A and B is 1. Bitwise addition over pairs is additive 
  across all bit positions.
• Time Complexity (TC):
  O(32 * n) = O(n), where n is the number of elements in arr.
• Space Complexity (SC):
  O(1), using a few variables for counting.
*/

/*
---------------------------------------------------------
FINAL APPROACH CHOICE
---------------------------------------------------------
The Bit Contribution approach (Approach 2) is chosen because 
n can be up to 10^5, meaning the O(n^2) brute force will cause 
a Time Limit Exceeded (TLE). The O(32 * n) approach runs in linear 
time and easily passes within the time limit.
---------------------------------------------------------
*/

#include <vector>

class Solution {
public:
    long long pairAndSum(std::vector<int>& arr) {
        long long totalSum = 0;
        int n = arr.size();

        // Since arr[i] <= 10^8, integers fit within 32 bits (10^8 < 2^27)
        for (int bit = 0; bit < 32; ++bit) {
            long long countSetBits = 0;

            for (int i = 0; i < n; ++i) {
                if ((arr[i] >> bit) & 1) {
                    countSetBits++;
                }
            }

            // Number of pairs where both elements have the 'bit'-th position set
            long long pairs = (countSetBits * (countSetBits - 1)) / 2;

            // Contribution of this bit to the total sum
            totalSum += pairs * (1LL << bit);
        }

        return totalSum;
    }
};
