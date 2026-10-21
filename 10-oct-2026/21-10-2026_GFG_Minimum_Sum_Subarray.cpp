/*
=========================================================
Date        : 21-10-2026
Problem Name: Minimum Sum Subarray
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Array, Kadane's Algorithm, Dynamic Programming

Problem Summary:
Given an array of integers, find the minimum sum of a contiguous subarray 
containing at least one element.

Key Observation:
This is the exact counterpart of Kadane's Algorithm for maximum subarray sum. 
We can invert the logic to find the minimum sum by tracking the minimum ending at each position.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Optimized (Kadane's Algorithm Variant)
   • Intuition: Maintain a running minimum sum of subarrays ending at the current index.
   • Approach: Iterate through the array. Update current running sum, taking the minimum of the current element alone or combined with the previous running sum. Track the global minimum.
   • Why it Works: If the running sum becomes greater than zero, it will only increase future sums, so we reset or discard it (or rather, since we want the minimum sum, if running sum becomes positive, keeping it won't help minimize, but wait—actually, for minimum sum, if current running sum is positive, adding a new element will increase it, so we reset the running sum if it exceeds the current element, or standard Kadane: if current sum > 0, reset to current element).
   • Time Complexity (TC): O(N) where N is the size of the array.
   • Space Complexity (SC): O(1) auxiliary space.

=========================================================
FINAL APPROACH
=========================================================
• We use Kadane's algorithm modified for minimum subarray sum.
• It processes the array in a single linear scan without extra space.
• It is optimal in both time and space compared to O(N^2) or O(N^3) brute force approaches.
=========================================================
*/

#include <vector>
#include <algorithm>
#include <climits>

class Solution {
public:
    int minSubarraySum(std::vector<int>& arr) {
        int minSoFar = arr[0];
        int currMin = arr[0];
        
        for (size_t i = 1; i < arr.size(); ++i) {
            // If the current minimum sum becomes greater than 0, 
            // it's better to start a new subarray from the current element.
            currMin = std::min(arr[i], currMin + arr[i]);
            minSoFar = std::min(minSoFar, currMin);
        }
        
        return minSoFar;
    }
};
