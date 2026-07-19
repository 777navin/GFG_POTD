/*
=========================================================
Date        : 19-07-2026
Problem Name: Mountain Subarray Queries
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Prefix Sum, Arrays, Data Structures

Problem Summary:
Given an array and multiple queries [l, r], determine if each subarray forms a 
mountain array. A mountain subarray first non-decreases up to an index k and 
then non-increases until r. Single-direction trends are also valid.

Key Observation:
For a subarray [l, r] to be a mountain, the longest non-decreasing subarray 
starting at l and the longest non-increasing subarray ending at r must overlap 
or meet at some peak index k. Thus, last[l] >= first[r].
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
APPROACH 1: Precomputed Directional Subarrays (Optimized)
=========================================================
• Intuition:
  Checking every element between l and r for each query is too slow. We can 
  precalculate how far each element can extend to its right in a non-decreasing 
  order, and how far each element can extend to its left in a non-decreasing order.

• Approach:
  1. Maintain an array 'left' where left[i] stores the closest index to the left 
     of i where the elements stop increasing (going right to left).
  2. Maintain an array 'right' where right[i] stores the furthest index to the right 
     of i up to which elements keep increasing or stay equal.
  3. For each query [l, r], if right[l] >= left[r], it means the increasing phase 
     from l and the decreasing phase towards r cross or meet, forming a valid mountain.

• Why it Works:
  If right[l] >= left[r], there exists at least one common index k in between 
  where the array increases from l to k and decreases from k to r.

• Time Complexity (TC):
  - Precomputation: O(N) to populate left and right arrays.
  - Query Processing: O(1) per query.
  - Total Time Complexity: O(N + Q) where N is array size and Q is number of queries.

• Space Complexity (SC):
  - O(N) auxiliary space to store the left and right prefix tables.
=========================================================
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
This precomputation approach is selected because it optimizes query response 
to O(1) time. A brute-force check per query would result in O(Q * N) worst-case 
complexity, causing a Time Limit Exceeded (TLE) given the constraints (N, Q <= 10^5).
=========================================================
*/

class Solution {
  public:
    vector<bool> processQueries(vector<int> &arr, vector<vector<int>> &queries) {
        int n = arr.size();
        vector<int> left(n, 0);
        vector<int> right(n, 0);

        // Precompute left bounds: stores the index of the nearest peak/start 
        // going left that maintains non-increasing order towards the left.
        left[0] = 0;
        for (int i = 1; i < n; i++) {
            if (arr[i] <= arr[i - 1]) {
                left[i] = left[i - 1];
            } else {
                left[i] = i;
            }
        }

        // Precompute right bounds: stores the furthest index to the right 
        // up to which elements are non-decreasing.
        right[n - 1] = n - 1;
        for (int i = n - 2; i >= 0; i--) {
            if (arr[i] <= arr[i + 1]) {
                right[i] = right[i + 1];
            } else {
                right[i] = i;
            }
        }

        // Process each query in O(1) time
        vector<bool> ans;
        ans.reserve(queries.size());
        
        for (const auto &q : queries) {
            int l = q[0];
            int r = q[1];
            
            // If the right boundary of l matches or exceeds the left boundary of r,
            // they share a common peak or valid overlapping transition.
            if (right[l] >= left[r]) {
                ans.push_back(true);
            } else {
                ans.push_back(false);
            }
        }

        return ans;
    }
};
