/*
Date        : 01-07-2026
Problem Name: Max Sum Subarray by Removing At Most One
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Array, Dynamic Programming, Kadane's Algorithm

Problem Summary:
Given an array arr[], find the maximum sum of a non-empty subarray.
You are allowed to skip at most one element in the subarray.
Note: After skipping, the subarray must still be non-empty.

Constraints:
1 <= arr.size() <= 10^6
-10^3 <= arr[i] <= 10^3

Key Observation:
This is a variation of Kadane’s Algorithm. We can maintain two states:

Max sum ending at i with zero elements skipped.

Max sum ending at i with one element skipped.
=========================================================
*/

/*

Approaches
Dynamic Programming (Most Optimal)

Intuition: At any index i, we have two choices for a subarray ending at i:
a) Keep all elements (Standard Kadane's).
b) Skip one element from a subarray ending at i.

Approach:

Let fwd[i] be max subarray sum ending at i.

Let bwd[i] be max subarray sum starting at i.

The answer is either max(fwd[i]) or max(fwd[i-1] + bwd[i+1]).

Time Complexity: O(N)

Space Complexity: O(N) (Can be optimized to O(1) using variables)

Comparison Table
Method          | Idea                | Time | Space | Difficulty | Recommended
DP (Two-Pass)   | Fwd/Bwd arrays      | O(N) | O(N)  | Medium     | Yes DP (Optimized)  | Running variables   | O(N) | O(1)  | Medium     | Yes
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
int maxSumSubarray(vector<int>& arr) {
int n = arr.size();
if (n == 0) return 0;
if (n == 1) return arr[0];

    // fwd[i]: Max subarray sum ending at i
    vector<int> fwd(n);
    fwd[0] = arr[0];
    int max_so_far = arr[0];
    for (int i = 1; i < n; i++) {
        fwd[i] = max(arr[i], fwd[i - 1] + arr[i]);
        max_so_far = max(max_so_far, fwd[i]);
    }

    // bwd[i]: Max subarray sum starting at i
    vector<int> bwd(n);
    bwd[n - 1] = arr[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        bwd[i] = max(arr[i], bwd[i + 1] + arr[i]);
    }

    // Try skipping each element at index i
    // The subarray would be from (i-1) to (i+1)
    for (int i = 1; i < n - 1; i++) {
        max_so_far = max(max_so_far, fwd[i - 1] + bwd[i + 1]);
    }

    return max_so_far;
}
};
