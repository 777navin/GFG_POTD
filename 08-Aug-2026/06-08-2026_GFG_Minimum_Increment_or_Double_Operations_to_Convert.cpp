/*
=========================================================
Date        : 06-08-2026
Problem Name: Minimum Increment or Double Operations to Convert
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Array, Bit Manipulation, Greedy

Problem Summary:
Convert an all-zero array to a given target array using two operations: 
increment one element by 1, or double all elements simultaneously. 
Find the minimum total operations required.

Key Observation:
View numbers in binary. The number of set bits equals the increment operations, 
and the highest set bit across all numbers dictates the total doubling operations.
=========================================================

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH EXPLANATION
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

1. Reverse Simulation (Better)
• Intuition: Work backwards from the target array to an array of all zeros.
• Approach: Iterate through the array. Decrement odd numbers by 1 (counts as an increment). If all numbers are even and > 0, divide all by 2 (counts as a double).
• Why it Works: It greedily reverses the operations, ensuring the minimum steps taken to reach zero.
• Time Complexity (TC): O(N * log(max_val))
• Space Complexity (SC): O(1)

2. Bit Manipulation (Most Optimal)
• Intuition: Each bit '1' in a number's binary form requires an independent +1 operation. The global '*2' operations shift these bits left.
• Approach: Sum the set bits (1s) for all numbers (total increments). Find the highest set bit position among all numbers (total global doublings).
• Why it Works: Doubling applies to the whole array, so we only need to double as many times as the largest power of 2 present in the array.
• Time Complexity (TC): O(N) where N is the size of the array.
• Space Complexity (SC): O(1)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
The Bit Manipulation approach is chosen because it extracts the answer 
directly from the binary properties of the integers in a single pass. 
It entirely avoids simulating array mutations, resulting in an elegant 
and highly efficient O(N) solution.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countMinOperations(vector<int>& arr) {
        int total_increments = 0;
        int max_doublings = 0;
        
        for (int num : arr) {
            if (num > 0) {
                // Count the number of set bits (1s) in the binary representation.
                // Each set bit corresponds to a required +1 increment operation.
                total_increments += __builtin_popcount(num);
                
                // Find the 0-indexed position of the most significant bit (highest set bit).
                // This corresponds to how many times we need to double this specific number.
                int highest_bit_pos = 31 - __builtin_clz(num);
                
                // The global doubling operations required is the maximum across all numbers.
                max_doublings = max(max_doublings, highest_bit_pos);
            }
        }
        
        return total_increments + max_doublings;
    }
};
