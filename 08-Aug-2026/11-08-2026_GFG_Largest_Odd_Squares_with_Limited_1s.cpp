/*
=========================================================
Date        : 11-08-2026
Problem Name: Largest Odd Squares with Limited 1s
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Matrix, 2D Prefix Sum, Binary Search

Problem Summary:
Given a binary matrix, process queries to find the maximum
odd-sized square centered at cell (i, j) that contains
at most k ones. If no such square exists, return -1.

Key Observation:
The count of 1s in a square expanding from a given center
increases monotonically, allowing binary search on the radius.
=========================================================
*/

/*
1. Brute Force
- Intuition: Iteratively expand the square radius layer by layer from the center.
- Approach: For each query, iterate over all possible radii, counting 1s manually in the expanding square. Stop when the count exceeds k.
- Why it Works: Simulates the exact physical expansion of the square and validates the condition.
- TC: O(Q * R^2) where Q is the number of queries and R is the max possible radius.
- SC: O(1) as no extra space is used for counting.

2. Optimized (2D Prefix Sum + Binary Search)
- Intuition: Repeatedly counting 1s in overlapping regions is redundant and slow. We need O(1) range sum queries.
- Approach: Precompute a 2D prefix sum array. For each query, binary search the maximum valid "radius" (distance from center to edge).
- Why it Works: 2D prefix sum gives the count of 1s in any subgrid in O(1) time. Since the count of 1s monotonically increases with radius, binary search is perfectly applicable.
- TC: O(N * M + Q * log(min(N, M))) where N*M is matrix size. Precomputation takes O(N*M), each of Q queries takes O(log R).
- SC: O(N * M) auxiliary space for the prefix sum matrix.

Final Approach:
The Optimized approach is chosen because evaluating up to 10^4 queries on a 
500x500 matrix strictly requires sub-linear query time. The combination of 
O(log R) binary search and O(1) area sum checks easily passes time limits.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> largestSquare(vector<vector<int>>& mat, vector<vector<int>>& queries, int k) {
        int n = mat.size();
        int m = mat[0].size();
        
        // 1-based indexing for 2D Prefix Sum to elegantly handle edge cases without out-of-bounds checks
        vector<vector<int>> pref(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                pref[i + 1][j + 1] = mat[i][j] + pref[i][j + 1] + pref[i + 1][j] - pref[i][j];
            }
        }
        
        // Lambda to get sum of 1s in a submatrix bounded by (r1, c1) top-left and (r2, c2) bottom-right
        auto getSum = [&](int r1, int c1, int r2, int c2) {
            return pref[r2 + 1][c2 + 1] - pref[r1][c2 + 1] - pref[r2 + 1][c1] + pref[r1][c1];
        };
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (const auto& q : queries) {
            int i = q[0];
            int j = q[1];
            
            // Binary search range for the radius
            int low = 0;
            // Max radius is constrained by the closest matrix boundary
            int high = min({i, j, n - 1 - i, m - 1 - j});
            int best_r = -1;
            
            while (low <= high) {
                int mid = low + (high - low) / 2;
                int ones_count = getSum(i - mid, j - mid, i + mid, j + mid);
                
                if (ones_count <= k) {
                    best_r = mid;     // Valid radius, record it
                    low = mid + 1;    // Try to find a larger valid square
                } else {
                    high = mid - 1;   // Square has too many 1s, shrink radius
                }
            }
            
            if (best_r != -1) {
                ans.push_back(2 * best_r + 1); // Side length = 2 * radius + 1
            } else {
                ans.push_back(-1); // Even a 1x1 square at this center has > k ones
            }
        }
        
        return ans;
    }
};

// Standalone driver code to ensure full execution capability 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m;
    if (cin >> n >> m) {
        vector<vector<int>> mat(n, vector<int>(m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> mat[i][j];
            }
        }
        
        int k, q_size;
        cin >> k >> q_size;
        vector<vector<int>> queries(q_size, vector<int>(2));
        for (int i = 0; i < q_size; ++i) {
            cin >> queries[i][0] >> queries[i][1];
        }
        
        Solution sol;
        vector<int> result = sol.largestSquare(mat, queries, k);
        
        for (int i = 0; i < result.size(); ++i) {
            cout << result[i] << (i == result.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
