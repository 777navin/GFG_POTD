/*
=========================================================
Date        : 04-09-2026
Problem Name: Bird and Max Fruit Gathering
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Arrays, Sliding Window, Two Pointers

Problem Summary:
Given an array arr[] representing fruits on trees arranged in a circle and an integer m,
find the maximum total fruits a bird can collect by visiting at most m contiguous trees.
The first and last trees in the array are also considered adjacent neighbors.

Key Observation:
Visiting at most m contiguous trees on a circular array of non-negative values is equivalent
to finding the maximum sum of a contiguous subarray of length at most min(n, m).
Since all elements are non-negative, the maximum sum always occurs at window size min(n, m).
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  Evaluate the sum of every possible circular window of size k = min(n, m) by checking each
  starting index from 0 to n - 1.

• Approach:
  For each index i from 0 to n - 1, run an inner loop of size k and compute the sum using
  modulo arithmetic ((i + j) % n). Track the maximum sum found.

• Why it Works:
  It explicitly checks every valid contiguous sequence of length k on the circular array.

• Time Complexity (TC):
  O(n * min(n, m)) - An inner loop of size min(n, m) runs for each starting index.

• Space Complexity (SC):
  O(1) - Only a few scalar variables are used.
*/

/*
---------------------------------------------------------
APPROACH 2: Sliding Window (Most Optimal)
---------------------------------------------------------
• Intuition:
  Instead of recomputing the entire window sum for each start position, slide a fixed-size
  window across the circular array by adding the new element entering the window and
  subtracting the element leaving it.

• Approach:
  1. Let k = min(n, m). If k == n, return the sum of all elements.
  2. Compute the sum of the first window of size k (indices 0 to k - 1).
  3. Slide the window from starting index 1 to n - 1. At step i, remove arr[i - 1] and add
     arr[(i + k - 1) % n].
  4. Update the maximum window sum at each step.

• Why it Works:
  Consecutive circular windows of size k overlap by k - 1 elements, allowing transitions in
  O(1) time. All elements are non-negative, so taking the maximum possible window size k
  guarantees the optimal fruit gathering.

• Time Complexity (TC):
  O(n) - Single pass to compute initial window sum, followed by O(1) transitions for n steps.

• Space Complexity (SC):
  O(1) - Constant extra space used.
*/

/*
---------------------------------------------------------
FINAL APPROACH CHOICE
---------------------------------------------------------
Approach 2 (Sliding Window) is chosen because n and m can be up to 10^6.
The O(n * k) brute force approach results in Time Limit Exceeded (TLE).
Sliding Window achieves an optimal O(n) runtime and O(1) auxiliary space.
*/

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxFruits(vector<int>& arr, int m) {
        int n = arr.size();
        if (n == 0 || m <= 0) return 0;

        int k = min(n, m);

        // Sum of the initial window of size k
        long long current_sum = 0;
        for (int i = 0; i < k; ++i) {
            current_sum += arr[i];
        }

        long long max_sum = current_sum;

        // Slide the window across the circular array
        for (int i = 1; i < n; ++i) {
            // Remove the element going out of the window
            current_sum -= arr[i - 1];
            // Add the new element entering the window
            current_sum += arr[(i + k - 1) % n];

            max_sum = max(max_sum, current_sum);
        }

        return static_cast<int>(max_sum);
    }
};
