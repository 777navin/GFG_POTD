/*
=========================================================
Date        : 04-08-2026
Problem Name: Pairs with Less Than K Diff
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Array, Sorting, Two Pointers, Sliding Window

Problem Summary:
Given an array of positive integers and an integer k, find the total 
number of unique pairs of elements whose absolute difference is strictly 
less than k.

Key Observation:
Sorting the array ensures elements are in increasing order, allowing 
us to use a two-pointer sliding window to count valid pairs efficiently 
in a single pass after sorting.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Brute Force
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition: The simplest way is to check every possible pair in the array to see if their difference is valid.
• Approach: Use two nested loops to iterate through all pairs (i, j) where i < j. Check if abs(arr[i] - arr[j]) < k.
• Why it Works: It exhaustively checks all combinations, guaranteeing no valid pair is missed.
• Time Complexity (TC): O(N^2) where N is the size of the array. Will cause Time Limit Exceeded (TLE) for N = 10^5.
• Space Complexity (SC): O(1) as no extra space is used.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Optimized (Sorting + Two Pointers)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition: If the array is sorted, the difference between elements grows monotonically. We can use a sliding window to track valid pairs.
• Approach: Sort the array. Maintain two pointers, left and right. Iterate right from 0 to N-1. If arr[right] - arr[left] >= k, increment left. Add (right - left) to the count.
• Why it Works: Sorting groups closer elements together. The two-pointer approach efficiently finds the valid window of pairs ending at 'right'.
• Time Complexity (TC): O(N log N) for sorting + O(N) for the two-pointer traversal = O(N log N).
• Space Complexity (SC): O(1) auxiliary space (or O(log N) depending on the sorting algorithm).

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• We choose Approach 2 (Sorting + Two Pointers).
• It is chosen because an O(N^2) brute force will fail for the given N = 10^5 constraints.
• The O(N log N) two-pointer method is optimal and easily passes within the time limits.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int countPairs(vector<int>& arr, int k) {
        int n = arr.size();
        if (n < 2) return 0;

        // Step 1: Sort the array to enable the two-pointer approach
        sort(arr.begin(), arr.end());

        int count = 0;
        int left = 0;

        // Step 2: Use a sliding window to find the number of valid pairs
        for (int right = 0; right < n; ++right) {
            
            // Shrink the window from the left if the difference is >= k
            while (arr[right] - arr[left] >= k) {
                left++;
            }
            
            // All elements from left to right-1 form a valid pair with arr[right]
            count += (right - left);
        }

        return count;
    }
};
