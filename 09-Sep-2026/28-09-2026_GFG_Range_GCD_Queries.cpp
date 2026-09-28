/*
=========================================================
Date        : 28-09-2026
Problem Name: Range GCD Queries
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Segment Tree, GCD, Data Structures, Algorithms

Problem Summary:
Given an array arr[] and q queries of two types:
Type 1: [0, l, r] -> Find the Greatest Common Divisor (GCD) of elements in range [l, r].
Type 2: [1, index, value] -> Update arr[index] to value.
Return an array containing answers for all Type 1 queries.

Key Observation:
GCD is an associative operation: gcd(a, gcd(b, c)) = gcd(gcd(a, b), c).
A Segment Tree can efficiently support point updates and range GCD queries in O(log N) time per operation.
=========================================================
*/

#include <vector>
#include <numeric>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Array Traversal)
---------------------------------------------------------
• Intuition:
  Directly update the array element on Type 2 queries and iterate through elements from index l to r to compute GCD on Type 1 queries.

• Approach:
  - For update query: set arr[index] = value.
  - For range query: compute running GCD from arr[l] to arr[r].

• Why it Works:
  Computes exact GCD linearly for every query.

• Time Complexity (TC):
  - Update: O(1)
  - Range Query: O(N * log(MAX_VAL))
  - Overall TC: O(Q * N * log(MAX_VAL)) -> TLE for N, Q <= 10^5.

• Space Complexity (SC):
  - O(1) auxiliary space.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Optimized (Segment Tree)
---------------------------------------------------------
• Intuition:
  Since GCD is associative and point updates occur dynamically, a Segment Tree can aggregate segment GCDs and answer range queries efficiently.

• Approach:
  - Build a Segment Tree of size 4 * N where each node stores the GCD of its corresponding segment.
  - Range Query [l, r]: Combine GCDs of disjoint segments fully covered in [l, r].
  - Point Update: Update the leaf node and recompute GCD for all ancestor nodes up to the root.

• Why it Works:
  Segment trees break down range queries into O(log N) tree node combinations, allowing fast logarithmic updates and range evaluations.

• Time Complexity (TC):
  - Build: O(N * log(MAX_VAL))
  - Update Query: O(log N * log(MAX_VAL))
  - Range Query: O(log N * log(MAX_VAL))
  - Overall TC: O(Q * log N * log(MAX_VAL)), well within time limits.

• Space Complexity (SC):
  - O(N) for storing the Segment Tree array.
---------------------------------------------------------
*/

// =========================================================
// FINAL APPROACH SELECTION
// =========================================================
// Segment Tree is selected because N, Q <= 10^5.
// The brute-force approach requires O(Q * N) operations which leads to Time Limit Exceeded (TLE).
// Segment Tree processes each update and range query in O(log N) time, making it optimal and fast.
// =========================================================

class SegmentTree {
private:
    int n;
    vector<int> tree;

    int gcd(int a, int b) {
        return std::gcd(a, b);
    }

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
            return;
        }
        int mid = start + (end - start) / 2;
        build(arr, 2 * node, start, mid);
        build(arr, 2 * node + 1, mid + 1, end);
        tree[node] = gcd(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, int val) {
        if (start == end) {
            tree[node] = val;
            return;
        }
        int mid = start + (end - start) / 2;
        if (idx <= mid) {
            update(2 * node, start, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, end, idx, val);
        }
        tree[node] = gcd(tree[2 * node], tree[2 * node + 1]);
    }

    int query(int node, int start, int end, int l, int r) {
        if (r < start || end < l) {
            return 0; // gcd(x, 0) = x
        }
        if (l <= start && end <= r) {
            return tree[node];
        }
        int mid = start + (end - start) / 2;
        int leftGcd = query(2 * node, start, mid, l, r);
        int rightGcd = query(2 * node + 1, mid + 1, end, l, r);
        return gcd(leftGcd, rightGcd);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n, 0);
        if (n > 0) {
            build(arr, 1, 0, n - 1);
        }
    }

    void update(int idx, int val) {
        update(1, 0, n - 1, idx, val);
    }

    int query(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }
};

class Solution {
public:
    vector<int> processQueries(vector<int>& arr, vector<vector<int>>& queries) {
        SegmentTree st(arr);
        vector<int> ans;

        for (const auto& q : queries) {
            int type = q[0];
            if (type == 0) {
                int l = q[1];
                int r = q[2];
                ans.push_back(st.query(l, r));
            } else if (type == 1) {
                int index = q[1];
                int value = q[2];
                st.update(index, value);
            }
        }

        return ans;
    }
};
