
/*
=========================================================
Date        : 16-11-2026
Problem Name: K-th Missing in Natural Numbers
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Arrays, Sorting

Problem Summary:
Find the k-th smallest positive natural number that is
not present in the given array of distinct integers.

Key Observation:
After sorting, every array element <= current answer
pushes the k-th missing number one position forward.
=========================================================

APPROACH 1: Brute Force
- Intuition: Check natural numbers one by one.
- Approach: Skip numbers present in the array.
- Why it Works: Counts exactly k missing numbers.
- TC: O(k * n)
- SC: O(1)

APPROACH 2: Sorting + Gap Counting
- Intuition: Missing numbers exist between sorted elements.
- Approach: Calculate missing elements in each gap.
- Why it Works: Identifies the gap containing the k-th missing number.
- TC: O(n log n)
- SC: O(1)

APPROACH 3: Sorting + Answer Adjustment (Optimal)
- Intuition: Start with k; every array element <= answer
  increases the answer by one.
- Approach: Sort the array and update the answer.
- Why it Works: Each encountered element removes one
  candidate from the natural number sequence.
- TC: O(n log n)
- SC: O(1)

FINAL APPROACH:
- Choose sorting + answer adjustment.
- It is simple, efficient and uses constant auxiliary space.
- Sorting is performed in-place.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int findKthSmall(vector<int>& arr, int k) {

        sort(arr.begin(), arr.end());

        int ans = k;

        for (int x : arr) {
            if (x <= ans) {
                ans++;
            } else {
                break;
            }
        }

        return ans;
    }
};
