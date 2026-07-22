/*
=========================================================
Date        : 22-07-2026
Problem Name: Minimum Deletions to Make Sorted
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Dynamic Programming, Binary Search, Longest Increasing Subsequence

Problem Summary:
Given an array `arr[]`, find the minimum number of elements to delete 
so that the remaining elements form a strictly increasing sequence in 
the same relative order.

Key Observation:
To minimize the number of deletions, we need to maximize the length of 
the remaining strictly increasing sequence. Thus, the answer is:
Min Deletions = (Total Elements) - (Length of Longest Strictly Increasing Subsequence)
=========================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Dynamic Programming (Standard LIS)
---------------------------------------------------------
• Intuition:
  We can compute the length of the Longest Increasing Subsequence (LIS) 
  ending at each index using dynamic programming.

• Approach:
  - Maintain a `dp` array where `dp[i]` represents the length of the LIS 
    ending at index `i`.
  - For each element `arr[i]`, iterate through previous elements `arr[j]` 
    where `j < i`. If `arr[j] < arr[i]`, update `dp[i] = max(dp[i], dp[j] + 1)`.
  - The answer is `n - max(dp)`.

• Why it Works:
  By checking all previous valid predecessors for each element, we build up 
  the longest possible strictly increasing subsequence incrementally.

• Time Complexity (TC): O(N^2)
  Nested loops iterate through pairs of indices.

• Space Complexity (SC): O(N)
  Used for the DP array.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Binary Search + Patience Sorting (Optimal LIS)
---------------------------------------------------------
• Intuition:
  Instead of comparing with every previous element, we can maintain a dynamic 
  tails array where `tails[k]` stores the smallest tail of all strictly 
  increasing subsequences of length `k + 1`.

• Approach:
  - Iterate through `arr`. For each element `x`, use `lower_bound` to find 
    the first element in `tails` that is greater than or equal to `x`.
  - If `x` is larger than all elements in `tails`, append `x` to `tails`.
  - Otherwise, replace the found element with `x` to keep tail values as 
    small as possible.
  - The length of `tails` gives the length of the LIS.
  - Answer is `n - tails.size()`.

• Why it Works:
  Keeping the tail elements as small as possible maximizes the chances for 
  subsequent elements to extend the increasing subsequence.

• Time Complexity (TC): O(N log N)
  Binary search (`lower_bound`) takes O(log N) for each of the N elements.

• Space Complexity (SC): O(N)
  To store the `tails` array.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH CHOICE:
The O(N log N) Binary Search approach is selected because the constraint on N is 
up to 10^5, for which an O(N^2) dynamic programming solution would result in a 
Time Limit Exceeded (TLE) error. The lower_bound technique optimizes both execution 
speed and memory overhead.
=========================================================
*/

class Solution {
public:
    int minDeletions(vector<int>& arr) {
        int n = arr.size();
        if (n <= 1) return 0;

        vector<int> tails;

        for (int x : arr) {
            // Find the first element in tails that is >= x (for strictly increasing)
            auto it = lower_bound(tails.begin(), tails.end(), x);

            if (it == tails.end()) {
                tails.push_back(x);
            } else {
                *it = x;
            }
        }

        // Min deletions = Total elements - LIS length
        return n - static_cast<int>(tails.size());
    }
};
