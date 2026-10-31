/*
=========================================================
Date        : 31-10-2026
Problem Name: Maximum Packages within Time
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Arrays, Sliding Window, Two Pointers

Problem Summary:
Find the maximum sum of packages collected from consecutive
locations within the given totalTime.
Visiting each location takes exactly one unit of time.

Key Observation:
Since every location takes one unit of time, we need to
find the maximum sum of a subarray of length totalTime.
=========================================================

1. BRUTE FORCE

- Intuition:
  Check every possible consecutive subarray of length k.

- Approach:
  Calculate the sum of each window independently.

- Why it Works:
  Every valid starting position is considered.

- Time Complexity: O(N * K)
- Space Complexity: O(1)


2. OPTIMIZED - SLIDING WINDOW

- Intuition:
  Avoid recalculating the entire window sum.

- Approach:
  Calculate the first window sum.
  Remove the outgoing element and add the incoming element.

- Why it Works:
  Every consecutive window is evaluated exactly once.

- Time Complexity: O(N)
- Space Complexity: O(1)


FINAL APPROACH:
- Sliding Window is chosen because it reduces the time
  complexity from O(N * K) to O(N).
- It uses constant extra space and efficiently handles
  all consecutive subarrays of the required length.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxPackages(vector<int>& arr, int totalTime) {

        int n = arr.size();
        int k = min(n, totalTime);

        int windowSum = 0;

        // Calculate the first window sum.
        for (int i = 0; i < k; i++) {
            windowSum += arr[i];
        }

        int maxSum = windowSum;

        // Slide the window across the array.
        for (int i = k; i < n; i++) {

            windowSum += arr[i];
            windowSum -= arr[i - k];

            maxSum = max(maxSum, windowSum);
        }

        return maxSum;
    }
};

/*
=========================================================
Example:

Input:
arr[] = {2, 1, 3, 5, 0, 1, 4}
totalTime = 3

Output:
9

Explanation:
The maximum sum of 3 consecutive elements is:

1 + 3 + 5 = 9

Time Complexity  : O(N)
Space Complexity : O(1)
=========================================================
*/
