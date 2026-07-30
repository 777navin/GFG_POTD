/*
=========================================================
Date        : 30-07-2026
Problem Name: Maximum Subset XOR
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Bit Magic, Greedy, Mathematical, Algorithms

Problem Summary:
Given an array arr[] of non-negative integers, select any subset of elements 
such that the bitwise XOR sum of the chosen elements is maximized.

Key Observation:
Maximum subset XOR can be constructed bit-by-bit using Gaussian Elimination 
(Linear Basis) to eliminate overlapping set bits from most significant bit (MSB) to LSB.
=========================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
---------------------------------------------------------
APPROACH EXPLANATION
---------------------------------------------------------

Approach 1: Gaussian Elimination (Linear Basis) - Optimal
- Intuition:
  We want to process numbers bit-by-bit from the most significant bit (31st bit down to 0th bit).
  For each bit position, find an element that has this bit set, place it as a pivot, and use bitwise XOR 
  to clear that bit in all other remaining elements.

- Approach:
  1. Maintain an index `index` pointing to the current position in array to swap the pivot.
  2. Iterate bit position `i` from 31 down to 0.
  3. Find the element from `index` to `N-1` with the `i`-th bit set.
  4. Swap it with `arr[index]`.
  5. XOR all other elements in the array that have their `i`-th bit set with `arr[index]`.
  6. Increment `index` and repeat.
  7. Finally, XOR all pivot elements to construct the maximum subset XOR value.

- Why it Works:
  XOR operation forms a vector space over GF(2). Gaussian elimination reduces the set of numbers 
  to a basis set where each basis vector uniquely contributes to a distinct MSB, allowing a greedy choice.

- Time Complexity (TC):
  O(30 * N) = O(N), where N is the size of the array and 30 is maximum bits for 10^6.

- Space Complexity (SC):
  O(1) auxiliary space as elimination is done in-place.
*/

/*
---------------------------------------------------------
FINAL APPROACH
---------------------------------------------------------
Gaussian Elimination is selected as it directly finds the linear basis 
of the input set in O(N) time and O(1) extra space, eliminating the exponential 
O(2^N) complexity of brute-force subset generation.
*/

class Solution {
public:
    int maxSubsetXOR(vector<int>& arr) {
        int n = arr.size();
        int index = 0; // Tracks position of pivot element

        // Process bits from Most Significant Bit (31) to Least Significant Bit (0)
        for (int i = 31; i >= 0; i--) {
            int maxIdx = index;
            int maxEle = INT_MIN;

            // Find element with i-th bit set
            for (int j = index; j < n; j++) {
                if ((arr[j] & (1 << i)) != 0 && arr[j] > maxEle) {
                    maxEle = arr[j];
                    maxIdx = j;
                }
            }

            // If no element has i-th bit set, move to next bit
            if (maxEle == INT_MIN) continue;

            // Swap to bring pivot element to front
            swap(arr[index], arr[maxIdx]);

            maxIdx = index;

            // Clear i-th bit from all other numbers using XOR
            for (int j = 0; j < n; j++) {
                if (j != maxIdx && (arr[j] & (1 << i)) != 0) {
                    arr[j] ^= arr[maxIdx];
                }
            }

            index++;
        }

        // Calculate maximum XOR by taking XOR of all basis vectors
        int res = 0;
        for (int i = 0; i < n; i++) {
            res ^= arr[i];
        }

        return res;
    }
};
