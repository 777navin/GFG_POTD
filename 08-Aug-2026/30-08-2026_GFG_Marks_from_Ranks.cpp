/*
=========================================================
Date        : 30-08-2026
Problem Name: Marks from Ranks
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Binary Search, Prefix Sum, Arrays

Problem Summary:
- Marks are partitioned into sorted, non-overlapping consecutive intervals [l[i], r[i]].
- Ranks are assigned in 1-based increasing order across all valid marks.
- Given an array rank[], return the corresponding mark for each rank.

Key Observation:
- Each interval [l[i], r[i]] contains (r[i] - l[i] + 1) marks.
- A prefix sum array of interval counts allows O(log N) lookup per rank via binary search.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/*
=========================================================
APPROACH 1: Brute Force (Linear Scan over Intervals)
=========================================================
• Intuition:
  - For each rank, iterate through intervals sequentially while subtracting interval sizes until the rank falls within the current interval.

• Approach:
  - For each query rank, loop i from 0 to n-1:
    - Count marks in interval i: len = r[i] - l[i] + 1.
    - If rank <= len, mark is l[i] + rank - 1.
    - Else, rank -= len.

• Why it Works:
  - Intervals are sorted and non-overlapping, so sequential deduction tracks cumulative ranks directly.

• Time Complexity (TC):
  - O(Q * N), where Q is rank.size() and N is l.size(). TLE for large constraints.
• Space Complexity (SC):
  - O(1) auxiliary space.
*/

/*
=========================================================
APPROACH 2: Optimized (Prefix Sum + Binary Search) [MOST OPTIMAL]
=========================================================
• Intuition:
  - Since interval sizes are strictly positive, the cumulative count of marks across intervals is strictly increasing.
  - We can use binary search (lower_bound) on prefix counts to find the target interval in O(log N) time.

• Approach:
  - Build a prefix sum array `pref` of size N, where pref[i] represents total marks in intervals 0 to i.
  - For each target rank in `rank`:
    - Binary search for the first index `idx` where pref[idx] >= rank.
    - Calculate previous cumulative marks before `idx` (pref[idx - 1] if idx > 0 else 0).
    - Offset into current interval: offset = rank - prev_count - 1.
    - Mark = l[idx] + offset.

• Why it Works:
  - Monotonicity of cumulative counts guarantees binary search correctness.

• Time Complexity (TC):
  - Precomputation: O(N)
  - Queries: O(Q * log N)
  - Total Time: O(N + Q * log N)
• Space Complexity (SC):
  - O(N) auxiliary space for prefix sums.
*/

/*
=========================================================
FINAL APPROACH CHOICE:
- Approach 2 (Prefix Sum + Binary Search) is selected.
- It reduces the per-query time complexity from O(N) to O(log N), easily passing within the time limit for N, Q <= 10^5.
=========================================================
*/

class Solution {
public:
    vector<int> getMarks(vector<int>& l, vector<int>& r, vector<int>& rank) {
        int n = l.size();
        vector<long long> pref(n);
        
        // Step 1: Precompute prefix sums of interval capacities
        for (int i = 0; i < n; i++) {
            long long count = (long long)r[i] - l[i] + 1;
            pref[i] = (i == 0 ? count : pref[i - 1] + count);
        }
        
        int q = rank.size();
        vector<int> ans(q);
        
        // Step 2: Binary search for each rank query
        for (int i = 0; i < q; i++) {
            long long targetRank = rank[i];
            
            // Find first interval where cumulative marks >= targetRank
            int idx = lower_bound(pref.begin(), pref.end(), targetRank) - pref.begin();
            
            long long prevCount = (idx == 0 ? 0 : pref[idx - 1]);
            long long offset = targetRank - prevCount - 1;
            
            ans[i] = l[idx] + offset;
        }
        
        return ans;
    }
};
