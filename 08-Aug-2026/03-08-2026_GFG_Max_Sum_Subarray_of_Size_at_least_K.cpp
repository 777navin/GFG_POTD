/*
=========================================================
Date        : 03-08-2026
Problem Name: Max Sum Subarray of Size at least K
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Arrays, Sliding Window, Dynamic Programming, Kadane's Algorithm

Problem Summary:
Find the maximum contiguous subarray sum out of all subarrays 
that have a length of at least 'k'.

Key Observation:
A subarray of length >= k can be split into a window of exact 
size k, plus a prefix subarray that contributes a positive sum.
=========================================================

1. Brute Force
• Intuition: Check all possible valid subarrays.
• Approach: Generate all subarrays of size >= k, calculate their sums, and track the maximum.
• Why it Works: It exhaustively explores the entire search space.
• Time Complexity (TC): O(N^2)
• Space Complexity (SC): O(1)

2. Better (Prefix Maximum Array)
• Intuition: Reusing previously computed maximum sums ending at an index.
• Approach: Compute an array where dp[i] is the max subarray sum ending at i. Use a sliding window of size k and add dp[i-k] if positive.
• Why it Works: Avoids recalculating the maximum sum for the prefix elements.
• Time Complexity (TC): O(N)
• Space Complexity (SC): O(N)

3. Most Optimal (Sliding Window + Running Kadane's)
• Intuition: We only need the max prefix sum immediately before the current window.
• Approach: Maintain a sliding window of size k. Simultaneously track the running Kadane's sum for elements exactly k steps behind.
• Why it Works: Keeps track of the best contiguous sum we can attach to the left of our window without using extra space.
• Time Complexity (TC): O(N)
• Space Complexity (SC): O(1)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
We choose the Most Optimal (Sliding Window + Running Kadane's) approach.
It elegantly solves the problem in a single pass O(N) time and requires 
only O(1) auxiliary space, making it perfectly optimized for the given constraints.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxSumWithK(vector<int>& arr, int k) {
        int n = arr.size();
        int windowSum = 0;
        
        // Step 1: Calculate the sum of the first window of exact size 'k'
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }
        
        int maxSum = windowSum;
        int prevSum = 0; // Tracks Kadane's maximum sum for elements before the window
        
        // Step 2: Slide the window from index 'k' to 'n-1'
        for (int i = k; i < n; i++) {
            // Update window sum by adding current element and removing the element k steps back
            windowSum = windowSum + arr[i] - arr[i - k];
            
            // Step 3: Track the running Kadane's sum for the prefix elements
            prevSum += arr[i - k];
            
            // If the prefix sum becomes negative, it won't help maximize our answer, so reset to 0
            if (prevSum < 0) {
                prevSum = 0;
            }
            
            // The maximum sum ending at 'i' of size >= k is the current window plus any positive prefix sum
            maxSum = max(maxSum, windowSum + prevSum);
        }
        
        return maxSum;
    }
};
