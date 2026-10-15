/*
=========================================================
Date        : 15-10-2026
Problem Name: Maximum Without 3 Consecutive Set Bits
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Bit Manipulation, Greedy

Problem Summary:
Given a non-negative integer n, you can change any set bit (1) to an unset bit (0). Find the maximum possible value of n such that its binary representation does not contain three consecutive set bits (111).

Key Observation:
We can iterate through the bits from the most significant bit down to 2 and check for three consecutive set bits (i.e., (n & (1 << i)) && (n & (1 << (i - 1))) && (n & (1 << (i - 2)))). When found, we clear the lowest bit of the three to break the sequence while maximizing the value.
=========================================================
*/

#include <iostream>

class Solution {
public:
    int maxValue(int n) {
        /*
        =========================================================
        Approach 1: Greedy Bit Manipulation
        
        • Intuition:
          To maximize the number, we should preserve higher bits as much as possible. If a triplet of consecutive ones '111' appears, we must unset one of them. Unsetting the lowest bit among the three yields a larger number than unsetting a higher bit.
          
        • Approach:
          Iterate from the highest possible bit down to 2. Check if bits at i, i-1, and i-2 are all set. If they are, turn off the (i-2)-th bit using bitwise operations and continue checking.
          
        • Why it Works:
          Greedily fixing from left to right ensures that we eliminate all occurrences of '111' while making minimal reductions to the value of n.
          
        • Time Complexity (TC): O(32) ~ O(1) since an integer has a fixed number of bits.
        • Space Complexity (SC): O(1)
        =========================================================
        */
        
        for (int i = 31; i >= 2; --i) {
            if ((n & (1 << i)) && (n & (1 << (i - 1))) && (n & (1 << (i - 2)))) {
                // Clear the lowest bit of the three consecutive set bits
                n = n ^ (1 << (i - 2));
            }
        }
        return n;
    }
};
