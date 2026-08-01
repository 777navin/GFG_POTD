/*
=========================================================
Date        : 01-08-2026
Problem Name: Max After m Range Increments
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Array, Difference Array, Prefix Sum

Problem Summary:
Given an array of size n initialized with zeros, perform m range increment operations.
Each operation (a[i], b[i], k[i]) adds k[i] to all elements in the index range [a[i], b[i]].
Find and return the maximum value present in the array after all operations are completed.

Key Observation:
Updating a range [L, R] naively takes O(N) time per operation, leading to TLE.
Using a Difference Array (Prefix Sum technique), range updates take O(1) time by modifying 
only the boundaries, and the final array values can be computed in a single pass.
=========================================================
*/

#include <bits/stdc++. Durante>
#include <vector>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH 1: Brute Force
=========================================================
• Intuition:
  Iterate through each operation and update every element in the given range [a[i], b[i]] 
  one by one, then find the maximum value in the final array.

• Approach:
  - Initialize an array of size n with all 0s.
  - For each operation i from 0 to m-1, loop through index j from a[i] to b[i] and add k[i].
  - Find and return the maximum element in the array.

• Why it Works:
  Directly simulates the problem instructions step-by-step to guarantee correct values.

• Time Complexity (TC):
  O(m * n) - In the worst case, each range operation spans almost the entire array.

• Space Complexity (SC):
  O(n) - To store the array elements.
=========================================================
*/

/*
=========================================================
APPROACH 2: Difference Array / Prefix Sum (Optimized & Most Optimal)
=========================================================
• Intuition:
  Adding k to range [L, R] is equivalent to adding +k at index L and subtracting -k at index R + 1.
  Taking the prefix sum of this difference array yields the actual values after all range operations.

• Approach:
  - Create a difference array `diff` of size n + 1 initialized to 0.
  - For each operation i, set `diff[a[i]] += k[i]` and `diff[b[i] + 1] -= k[i]`.
  - Calculate the prefix sum iteratively while tracking the maximum value encountered.

• Why it Works:
  The difference array encodes point changes. The prefix sum accumulates these additions 
  and handles range terminations automatically, reducing range update time to O(1).

• Time Complexity (TC):
  O(n + m) - O(m) to process m updates and O(n) to compute prefix sum and maximum element.

• Space Complexity (SC):
  O(n) - For the difference array of size n + 1.
=========================================================
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
The Difference Array approach is chosen because n and m can both be up to 10^6.
The brute-force approach requires O(m * n) time, which leads to Time Limit Exceeded (TLE).
The O(n + m) Difference Array approach easily processes all range operations within 
the given execution limits.
=========================================================
*/

class Solution {
public:
    int findMax(int n, vector<int>& a, vector<int>& b, vector<int>& k) {
        // Difference array of size n + 1 to handle 0-based boundary condition at b[i] + 1
        vector<long long> diff(n + 1, 0);
        int m = a.size();

        // Perform range updates in O(1) time each
        for (int i = 0; i < m; i++) {
            diff[a[i]] += k[i];
            if (b[i] + 1 < n) {
                diff[b[i] + 1] -= k[i];
            }
        }

        // Compute prefix sum and track maximum element
        long long current_val = 0;
        long long max_val = 0;

        for (int i = 0; i < n; i++) {
            current_val += diff[i];
            max_val = max(max_val, current_val);
        }

        return max_val;
    }
};
