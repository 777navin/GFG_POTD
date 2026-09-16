/*
=========================================================
Date        : 16-09-2026
Problem Name: Dominant Pairs
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Array, Sorting, Two Pointers

Problem Summary:
Given an even-sized integer array, count pairs (i, j) such that i is in the first half, j is in the second half, and arr[i] >= 5 * arr[j].

Key Observation:
Since we only care about the relative values between the two halves, we can sort both halves independently and use a two-pointer approach to count valid pairs efficiently.
=========================================================

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: BRUTE FORCE
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
* Intuition: Check every possible pair of (i, j) across the two halves.
* Approach: Use nested loops. Outer loop for the first half, inner loop for the second half.
* Why it Works: It exhaustively validates the condition against every possible pair combination.
* Time Complexity (TC): O(N^2) where N is the size of the array.
* Space Complexity (SC): O(1) as no extra memory is used.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: OPTIMIZED (Two Pointers & Sorting)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
* Intuition: Sorting both halves allows us to skip redundant checks by leveraging the ordered nature of the arrays.
* Approach: 
  - Sort the left half [0, n/2 - 1] and the right half [n/2, n - 1] in ascending order independently.
  - Initialize pointer i for the left half and j for the right half.
  - If arr[i] >= 5 * arr[j], then all subsequent elements in the sorted left half are also valid for arr[j]. Add (n/2 - i) to the count and increment j.
  - If arr[i] < 5 * arr[j], increment i to find a larger value in the left half.
* Why it Works: The monotonicity of the sorted halves guarantees that if a condition holds for an element, it holds for all larger elements, preventing O(N^2) comparisons.
* Time Complexity (TC): O(N log N) due to the sorting step. The two-pointer traversal takes O(N).
* Space Complexity (SC): O(1) auxiliary space (ignoring recursive stack space for sorting).

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
* Why this approach is chosen: The optimized two-pointer approach avoids the Time Limit Exceeded (TLE) error that would occur with a brute force O(N^2) solution on an array of size 10^4.
* Why it is better: It drastically reduces the time complexity to O(N log N) which easily executes within the given constraints.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int dominantPairs(vector<int>& arr) {
        int n = arr.size();
        int half = n / 2;
        
        // Sort the first half and the second half independently
        sort(arr.begin(), arr.begin() + half);
        sort(arr.begin() + half, arr.end());
        
        int count = 0;
        int i = 0;
        int j = half;
        
        // Two-pointer traversal
        while (i < half && j < n) {
            if (arr[i] >= 5 * arr[j]) {
                // If arr[i] is valid, all elements from i to half-1 are also valid
                count += (half - i);
                j++;
            } else {
                // We need a larger element in the first half
                i++;
            }
        }
        
        return count;
    }
};
