/*

Date: 22-04-2026
Problem Name: Mean of range in array
Platform: GeeksforGeeks (GFG)
Difficulty: Easy
Tags:
Array, Prefix Sum, Range Query, Math

=========================================================
Problem Summary:

Given:
- Integer array arr[]
- 2D array queries[][] where each query = [l, r]

For every query:
- Find subarray from index l to r (inclusive)
- Compute mean (average)
- Return floor(mean)

Return result array for all queries.

=========================================================
Methods to Solve:

1. Brute Force
---------------------------------------------------------
Intuition:
For each query, iterate from l to r and compute sum.

Time Complexity:
O(Q * N)

Space Complexity:
O(1)

Not ideal for many queries.

---------------------------------------------------------

2. Prefix Sum (Optimal)
---------------------------------------------------------
Intuition:
Precompute cumulative sums so each range sum can be found
in O(1).

Formula:
rangeSum = prefix[r] - prefix[l - 1]

mean = rangeSum / length

Dry Run:

arr = [1,2,3,4,5]

prefix = [1,3,6,10,15]

Query [1,3]
sum = 10 - 1 = 9
len = 3
mean = 9/3 = 3

=========================================================
Comparison Table:

Method          TC              SC      Best Use
---------------------------------------------------------
Brute Force     O(Q*N)          O(1)    Small input
Prefix Sum      O(N + Q)        O(N)    Large queries

=========================================================
Final Recommended Solution:
Use Prefix Sum.

=========================================================
*/

class Solution {
public:
    vector<int> findMean(vector<int> &arr, vector<vector<int>> &queries) {
        int n = arr.size();

        // Prefix sum array using long long for safety
        vector<long long> prefix(n, 0);
        prefix[0] = arr[0];

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1] + arr[i];
        }

        vector<int> answer;

        for (auto &q : queries) {
            int l = q[0];
            int r = q[1];

            long long sum = prefix[r] - (l > 0 ? prefix[l - 1] : 0);
            int len = r - l + 1;

            answer.push_back(sum / len); // floor automatically in integer division
        }

        return answer;
    }
};
