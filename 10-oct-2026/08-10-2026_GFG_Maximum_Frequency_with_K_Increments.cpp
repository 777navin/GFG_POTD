/*
=========================================================
Date        : 08-10-2026
Problem Name: Maximum Frequency with K Increments
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Sliding Window, Two Pointers, Sorting, Prefix Sum

Problem Summary:
Given an array of integers and an integer k, you can increment any element by 1 in one operation.
Find the maximum possible frequency of any element after performing at most k operations.

Key Observation:
Sorting the array helps process elements sequentially. To make a subarray equal to a target element
arr[right], total operations needed = (length of subarray * target) - sum(subarray).
=========================================================
*/

#include <vector>
#include <algorithm>

/*
---------------------------------------------------------
APPROACH 1: Sliding Window / Two Pointers
---------------------------------------------------------
• Intuition:
  To minimize the number of increment operations needed to make a set of elements equal, we should 
  always increment smaller numbers to match a larger existing element in the array. Sorting allows 
  us to consider contiguous subsegments.

• Approach:
  1. Sort the array `arr`.
  2. Maintain a sliding window `[left, right]` where `arr[right]` is the target value to make all elements in the window equal to.
  3. Keep track of the running sum of elements in the window (`current_sum`).
  4. The cost to transform all elements in `[left, right]` to `arr[right]` is `(right - left + 1) * arr[right] - current_sum`.
  5. If this cost exceeds `k`, shrink the window by advancing `left` and subtracting `arr[left]` from `current_sum`.
  6. Track the maximum valid window size `(right - left + 1)`.

• Why it Works:
  Sorting guarantees that all elements in the window `[left, right]` are $\le$ `arr[right]`, which gives the minimum total increments needed to bring them up to `arr[right]`.

• Time Complexity (TC):
  O(N log N) due to sorting, where N is the size of the array. The sliding window processing runs in O(N).

• Space Complexity (SC):
  O(1) auxiliary space (excluding the space required by `std::sort`).
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
• We choose the Sliding Window approach after sorting.
• Sorting ensures contiguous elements are optimal candidates, and the sliding window dynamically updates costs in O(1) time per element.
• It satisfies the constraints (N <= 10^5) comfortably within O(N log N) time and O(1) space.
=========================================================
*/

class Solution {
public:
    int maxFrequency(std::vector<int>& arr, int k) {
        // Step 1: Sort the array to process elements in non-decreasing order
        std::sort(arr.begin(), arr.end());

        int left = 0;
        int max_freq = 0;
        long long current_sum = 0;

        // Step 2: Expand the window with `right` pointer
        for (int right = 0; right < arr.size(); ++right) {
            current_sum += arr[right];

            // Operations needed to make all elements in window [left, right] equal to arr[right]
            // Operations = (window_size * target_val) - sum_of_window
            while ((long long)(right - left + 1) * arr[right] - current_sum > k) {
                current_sum -= arr[left];
                left++;
            }

            // Update maximum frequency found so far
            max_freq = std::max(max_freq, right - left + 1);
        }

        return max_freq;
    }
};
