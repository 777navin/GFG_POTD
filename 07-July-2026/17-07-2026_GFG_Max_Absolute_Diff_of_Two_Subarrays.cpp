/*
=========================================================
Date        : 17-07-2026
Problem Name: Max Absolute Diff of Two Subarrays
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Dynamic Programming, Arrays

Problem Summary:
Given an array of integers, find two non-overlapping contiguous subarrays 
such that the absolute difference between the sums of these two subarrays 
is maximized. Return the maximum absolute difference.

Key Observation:
To maximize |Sum1 - Sum2|, we need to find either (Max_Left_Subarray - Min_Right_Subarray) 
or (Min_Left_Subarray - Max_Right_Subarray) for every possible partition point in the array.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
APPROACH EXPLANATION
=========================================================
1. Optimized (Dynamic Programming / Kadane's Variant)
• Intuition:
  The maximum absolute difference across a partition can occur in two ways:
  a max-sum subarray on the left and a min-sum subarray on the right, or vice versa. 
  Precomputing these values from both ends allows us to evaluate all partition points efficiently.

• Approach:
  - Maintain four arrays: leftMax, leftMin (traversing left to right), and rightMax, rightMin (traversing right to left).
  - Use standard Kadane's algorithm to fill leftMax and leftMin, storing the best subarray sum seen up to index i.
  - Similarly, traverse from the right to fill rightMax and rightMin.
  - Iterate through all possible splitting points from 0 to n-2, tracking the maximum absolute difference:
    max(abs(leftMax[i] - rightMin[i+1]), abs(leftMin[i] - rightMax[i+1])).

• Why it Works:
  By isolating the maximum and minimum contiguous sums possible on either side of a split point, 
  we exhaustively evaluate every candidate pair of non-overlapping subarrays without recalculating combinations.

• Time Complexity (TC) : O(n) - Requires four single-pass linear scans to precompute arrays and one final linear scan.
• Space Complexity (SC): O(n) - Requires extra arrays of size n to store maximum and minimum subarray prefix/suffix sums.
=========================================================
*/

/*
• Why this approach is chosen:
  It achieves the optimal linear time complexity O(n), which comfortably passes within the 10^5 constraint.
  A brute-force solution checking all sub-array combinations would run in O(n^2) or O(n^3) time, resulting in a TLE.
*/

class Solution {
public:
    int maxDiffSubArrays(vector<int>& arr) {
        int n = arr.size();
        if (n < 2) return 0;

        vector<int> leftMax(n), leftMin(n);
        vector<int> rightMax(n), rightMin(n);

        // Forward pass: Compute max and min subarray sums from the left
        int currentMax = arr[0], maxSoFar = arr[0];
        int currentMin = arr[0], minSoFar = arr[0];
        leftMax[0] = maxSoFar;
        leftMin[0] = minSoFar;

        for (int i = 1; i < n; i++) {
            currentMax = max(arr[i], currentMax + arr[i]);
            maxSoFar = max(maxSoFar, currentMax);
            leftMax[i] = maxSoFar;

            currentMin = min(arr[i], currentMin + arr[i]);
            minSoFar = min(minSoFar, currentMin);
            leftMin[i] = minSoFar;
        }

        // Backward pass: Compute max and min subarray sums from the right
        currentMax = arr[n - 1]; maxSoFar = arr[n - 1];
        currentMin = arr[n - 1]; minSoFar = arr[n - 1];
        rightMax[n - 1] = maxSoFar;
        rightMin[n - 1] = minSoFar;

        for (int i = n - 2; i >= 0; i--) {
            currentMax = max(arr[i], currentMax + arr[i]);
            maxSoFar = max(maxSoFar, currentMax);
            rightMax[i] = maxSoFar;

            currentMin = min(arr[i], currentMin + arr[i]);
            minSoFar = min(minSoFar, currentMin);
            rightMin[i] = minSoFar;
        }

        // Find the maximum absolute difference between two non-overlapping subarrays
        int maxDiff = INT_MIN;
        for (int i = 0; i < n - 1; i++) {
            int diff1 = abs(leftMax[i] - rightMin[i + 1]);
            int diff2 = abs(leftMin[i] - rightMax[i + 1]);
            maxDiff = max({maxDiff, diff1, diff2});
        }

        return maxDiff;
    }
};
