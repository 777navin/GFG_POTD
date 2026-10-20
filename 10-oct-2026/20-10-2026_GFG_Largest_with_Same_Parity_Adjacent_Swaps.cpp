/*
=========================================================
Date        : 20-10-2026
Problem Name: Largest with Same Parity Adjacent Swaps
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Sorting, Greedy, Two Pointers

Problem Summary:
- Given an array arr[], we can swap two adjacent elements only if their sum is even.
- This means we can only swap adjacent elements if both have the same parity (both even or both odd).
- Find the lexicographically largest array obtainable by any number of such swaps.

Key Observation:
- Elements of different parities can never cross each other because their sum would be odd.
- Thus, the array is partitioned into contiguous segments of elements with the same parity (all even or all odd) that can be permuted internally in any order.
=========================================================
*/

/*
=========================================================
APPROACH 1: Greedy Sorting within Parity Segments

• Intuition: Since elements of different parities cannot cross each other, the positions of parity boundaries are fixed. Within each contiguous block of the same parity, we can freely swap adjacent elements to achieve any permutation, including sorting them in descending order to make the array lexicographically largest.
• Approach: 
  1. Iterate through the array to identify contiguous segments of the same parity (all even or all odd).
  2. For each segment, extract its elements, sort them in descending order, and place them back into their respective positions in the array.
• Why it Works: Sorting each isolated same-parity block in descending order maximizes the elements at the earliest possible positions, guaranteeing the lexicographically largest result without violating the parity swap restriction.
• Time Complexity (TC): O(N log N) due to sorting segments (where N is the size of the array).
• Space Complexity (SC): O(N) auxiliary space to store segments or indices.
=========================================================
*/

/*
=========================================================
FINAL APPROACH CHOICE
- We use the Greedy Sorting approach because it is optimal and directly exploits the property that same-parity segments can be independently sorted to maximize the lexicographical order.
- It efficiently handles large inputs up to 10^5 within expected time limits.
=========================================================
*/

#include <vector>
#include <algorithm>
#include <iostream>

class Solution {
public:
    std::vector<int> lexicographicallyLargest(std::vector<int>& arr) {
        int n = arr.size();
        int i = 0;
        
        while (i < n) {
            int j = i;
            // Find the end of the current contiguous segment of the same parity
            while (j < n && (arr[j] % 2 == arr[i] % 2)) {
                j++;
            }
            
            // Sort the elements in this segment in descending order
            std::sort(arr.begin() + i, arr.begin() + j, std::greater<int>());
            
            // Move to the next segment
            i = j;
        }
        
        return arr;
    }
};
