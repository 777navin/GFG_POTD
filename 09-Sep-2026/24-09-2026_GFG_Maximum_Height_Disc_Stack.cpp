/*
=========================================================
Date        : 24-09-2026
Problem Name: Maximum Height Disc Stack
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Dynamic Programming, Binary Indexed Tree / Segment Tree, Sorting

Problem Summary:
Given two arrays r[] and h[] of size n representing the radius and height of discs.
A disc can be placed above another disc only if both its radius and height are 
strictly smaller than the disc below it.
Find the maximum possible sum of heights of a valid disc stack where each disc 
is used at most once.

Key Observation:
Sorting discs primarily by radius ascending (and height descending for ties) 
reduces the 2D condition to finding the Maximum Weight Increasing Subsequence 
on height, solvable via coordinate compression and a Fenwick tree.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Dynamic Programming (LIS-variant)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - Sort the discs by radius ascending. If radius matches, sort height ascending.
  - Apply standard O(N^2) Longest Increasing Subsequence DP to maximize accumulated height.

• Approach:
  - Create a vector of pairs (r[i], h[i]) and sort them.
  - Let dp[i] be the maximum height achievable with disc i at the top.
  - For each i, check all j < i: if r[j] < r[i] and h[j] < h[i], dp[i] = max(dp[i], dp[j] + h[i]).

• Why it Works:
  - Guarantees valid chains of strictly increasing radius and height.

• Time Complexity (TC):
  - O(N^2), where N is the number of discs. TLE for N = 10^5.

• Space Complexity (SC):
  - O(N) to store DP states and sorted pairs.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Fenwick Tree (Binary Indexed Tree) with Coordinate Compression
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  - Sorting radius ascending and height descending for ties eliminates strict radius 
    equality issues.
  - Querying the maximum stack height among all previously processed discs with smaller 
    height becomes a prefix maximum range query.

• Approach:
  - Pair each disc as (r[i], h[i]).
  - Coordinate-compress unique heights into ranks in [1, M] (where M <= 1000 or unique values <= N).
  - Sort discs by: r ascending; if r is equal, h descending.
  - Iterate through sorted discs: query the BIT for the max height among strictly smaller heights (< rank(h)).
  - Update the BIT at rank(h) with (queried_max + h).

• Why it Works:
  - Sorting order ensures any previously processed disc has radius <= current disc.
  - Sorting ties with height descending ensures discs with the same radius cannot stack on each other.
  - The Fenwick Tree maintains prefix maximums in O(log M) time.

• Time Complexity (TC):
  - O(N log N) for sorting, coordinate compression, and BIT updates/queries.

• Space Complexity (SC):
  - O(N) auxiliary space for storing discs and the Fenwick tree.
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH: Fenwick Tree (Binary Indexed Tree)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Chosen because N can be up to 10^5, where O(N^2) DP would exceed time limits.
• Achieves optimal O(N log N) time complexity and O(N) space, fitting well within competitive limits.
*/

#include <vector>
#include <algorithm>

using namespace std;

class FenwickTree {
private:
    int n;
    vector<int> tree;

public:
    FenwickTree(int n) : n(n), tree(n + 1, 0) {}

    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) {
            tree[idx] = max(tree[idx], val);
        }
    }

    int query(int idx) {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) {
            res = max(res, tree[idx]);
        }
        return res;
    }
};

class Solution {
public:
    int maxStackHeight(vector<int>& r, vector<int>& h) {
        int n = r.size();
        if (n == 0) return 0;

        vector<pair<int, int>> discs(n);
        vector<int> unique_heights;
        unique_heights.reserve(n);

        for (int i = 0; i < n; i++) {
            discs[i] = {r[i], h[i]};
            unique_heights.push_back(h[i]);
        }

        // Coordinate compression for heights
        sort(unique_heights.begin(), unique_heights.end());
        unique_heights.erase(unique(unique_heights.begin(), unique_heights.end()), unique_heights.end());

        // Sort: radius ascending; for ties, height descending to enforce strictly smaller radius
        sort(discs.begin(), discs.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second;
        });

        int m = unique_heights.size();
        FenwickTree bit(m);
        int total_max_height = 0;

        for (int i = 0; i < n; i++) {
            int current_h = discs[i].second;
            // 1-based rank of current_h
            int rank = lower_bound(unique_heights.begin(), unique_heights.end(), current_h) - unique_heights.begin() + 1;

            // Query max height with height strictly smaller than current_h
            int best_prev = bit.query(rank - 1);
            int current_total = best_prev + current_h;

            bit.update(rank, current_total);
            total_max_height = max(total_max_height, current_total);
        }

        return total_max_height;
    }
};
