/*
Date: 12-05-2026
Problem Name: Range LCM Queries
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Segment Tree, GCD, LCM, Data Structures

Problem Summary:
Given an array 'arr' and a series of queries. There are two types of queries:
1. Update Query: [1, index, value] -> Update arr[index] to the new value.
2. Range Query: [2, L, R] -> Calculate the Least Common Multiple (LCM) of the elements from index L to R.
Return the results of all Type 2 queries in order.

Methods to Solve:

1. Brute Force:
   - Intuition: For every Type 2 query, iterate through the range [L, R] and calculate the LCM step-by-step.
   - Approach: For Type 1, update the array. For Type 2, result = arr[L], then for i = L+1 to R, result = lcm(result, arr[i]).
   - Time Complexity: O(Q * N * log(max_val))
   - Space Complexity: O(1) (excluding input)
   - When to use: Only if N and Q are very small (e.g., < 100).

2. Segment Tree (Optimal Approach):
   - Intuition: Range queries and point updates are the hallmark of Segment Trees. Since LCM is associative (lcm(a, b, c) = lcm(a, lcm(b, c))), we can store the LCM of a range in each node.
   - Approach: 
     - Build a segment tree where each leaf node stores arr[i].
     - Internal nodes store the LCM of their children: lcm(left_child, right_child).
     - Update: Standard point update in O(log N).
     - Query: Standard range query in O(log N).
   - Dry Run: arr = [2, 3, 4]. Tree: Root [0,2] stores lcm(2,3,4)=12. Left [0,1] stores lcm(2,3)=6. Right [2,2] stores 4.
   - Time Complexity: O(N + Q * log N * log(max_val))
   - Space Complexity: O(N) for tree storage.
   - Why better: Reduces query time from linear to logarithmic, allowing it to handle 10^5 queries easily.
   - When to use: When range queries and point updates are frequent.

Comparison Table:
Method       | TC                        | SC   | Best Use Case
-------------|---------------------------|------|-------------------------
Brute Force  | O(Q * N * log(max))       | O(1) | Small constraints
Segment Tree | O((N+Q) * log N * log(max))| O(N) | Standard Range/Update problems

Final Recommended Solution: Segment Tree
*/

#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

/**
 * @brief Solution class for Range LCM Queries
 * Utilizes a Segment Tree to handle point updates and range LCM queries efficiently.
 */
class Solution {
private:
    vector<long long> tree;
    int n;

    // Helper to calculate GCD (C++17 std::gcd is available, but explicit for clarity)
    long long get_gcd(long long a, long long b) {
        while (b) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    // Helper to calculate LCM
    long long get_lcm(long long a, long long b) {
        if (a == 0 || b == 0) return 0;
        return (a * b) / get_gcd(a, b);
    }

    // Build the Segment Tree
    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = get_lcm(tree[2 * node], tree[2 * node + 1]);
    }

    // Point Update: Update index 'idx' with 'val'
    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid)
            update(2 * node, start, mid, idx, val);
        else
            update(2 * node + 1, mid + 1, end, idx, val);
        
        tree[node] = get_lcm(tree[2 * node], tree[2 * node + 1]);
    }

    // Range Query: Get LCM in range [L, R]
    long long query(int node, int start, int end, int L, int R) {
        if (R < start || end < L) {
            return 1; // Neutral element for LCM
        }
        if (L <= start && end <= R) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        long long left_lcm = query(2 * node, start, mid, L, R);
        long long right_lcm = query(2 * node + 1, mid + 1, end, L, R);
        
        // If one side is neutral (1), return the other side directly to avoid extra GCD
        if (left_lcm == 1) return right_lcm;
        if (right_lcm == 1) return left_lcm;
        
        return get_lcm(left_lcm, right_lcm);
    }

public:
    /**
     * @param arr The initial array
     * @param queries The list of queries [[type, param1, param2]]
     * @return List of results for type 2 queries
     */
    vector<long long> RangeLCMQuery(vector<int> &arr, vector<vector<int>> &queries) {
        n = arr.size();
        tree.assign(4 * n + 1, 0);
        build(arr, 1, 0, n - 1);

        vector<long long> results;
        for (const auto& q : queries) {
            int type = q[0];
            if (type == 1) {
                // Update Query: [1, index, value]
                int idx = q[1];
                int val = q[2];
                update(1, 0, n - 1, idx, val);
            } else {
                // Range Query: [2, L, R]
                int L = q[1];
                int R = q[2];
                results.push_back(query(1, 0, n - 1, L, R));
            }
        }
        return results;
    }
};12-05-2026_GFG_Range_LCM_Queries.cpp
