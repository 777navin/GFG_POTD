/*
=========================================================
Date        : 18-07-2026
Problem Name: Cut Matrix
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Dynamic Programming, Matrix, Prefix Sum

Problem Summary:
Given an $n \times m$ binary matrix and an integer $k$, divide the matrix into $k$ pieces such that each piece contains at least one '1'.
Return the total number of valid ways to divide the matrix modulo $10^9 + 7$.

Key Observation:
The previous recursive approach iterating through all possible cut indices takes $\mathcal{O}(n \cdot m \cdot k \cdot (n+m))$, causing Time Limit Exceeded (TLE) on stricter test cases.
We can reduce the cut iteration from $\mathcal{O}(n+m)$ to $\mathcal{O}(1)$ by precomputing the first valid cut position and using 2D suffix sums of our DP states.
=========================================================
*/

#include <vector>
using namespace std;

/*
• Intuition:
  - We need to avoid looping over all possible horizontal `i` and vertical `j` cuts for every subproblem state.
  - Since a valid cut means the partitioned piece contains at least one '1', any cut at or after the first occurrence of a '1' is valid.
  - If we maintain suffix sums of the ways to form `rem - 1` pieces, we can calculate the transitions in $\mathcal{O}(1)$ time.

1. Recursion + Memoization (TLE)
  - Approach: 3D DP trying all `i` and `j` combinations per state.
  - Why it fails: Too many overlapping combinations, $\mathcal{O}(n^2 \cdot m \cdot k + n \cdot m^2 \cdot k)$ is too slow for constraints up to 200.

2. Iterative DP with Suffix Sums (Most Optimal)
  - Approach:
    - Precompute `ones[r][c]` to count '1's in any subgrid.
    - Precompute `next_r[r][c]` (the first valid row to start the bottom piece) and `next_c[r][c]` (the first valid col for the right piece).
    - Use iterative DP where `dp[r][c]` stores ways to cut the current subgrid into `rem` pieces.
    - Maintain 2D suffix sums (`suf_r` and `suf_c`) of the DP table for `rem - 1` pieces to instantly fetch the total valid ways.
  - Why it Works: It strictly computes $\mathcal{O}(1)$ transitions by substituting the inner loop with precomputed suffix sums.
  - Time Complexity (TC): $\mathcal{O}(n \cdot m \cdot k)$ – strictly three nested loops.
  - Space Complexity (SC): $\mathcal{O}(n \cdot m)$ – DP states are optimized to only require the previous and current $k$ layers.
*/

/*
=========================================================
FINAL APPROACH:
The iterative DP with Suffix Sums approach is chosen because it successfully drops the time complexity to $\mathcal{O}(n \cdot m \cdot k)$.
By precomputing `next_r` and `next_c`, and pulling the sum of valid states instantly from `suf_r` and `suf_c`, it flawlessly avoids TLE. Space is also heavily optimized.
=========================================================
*/

class Solution {
public:
    int findWays(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        int m = matrix[0].size();
        const int MOD = 1e9 + 7;
        
        // 1. Precompute 2D suffix sum of '1's
        vector<vector<int>> ones(n + 1, vector<int>(m + 1, 0));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = m - 1; j >= 0; --j) {
                ones[i][j] = matrix[i][j] + ones[i + 1][j] + ones[i][j + 1] - ones[i + 1][j + 1];
            }
        }
        
        // 2. Precompute the first row that starts a valid bottom piece
        vector<vector<int>> next_r(n, vector<int>(m, n));
        for (int c = 0; c < m; ++c) {
            int first_1_row = n;
            for (int r = n - 1; r >= 0; --r) {
                int ones_in_row = ones[r][c] - ones[r + 1][c];
                if (ones_in_row > 0) first_1_row = r;
                next_r[r][c] = (first_1_row < n) ? first_1_row + 1 : n;
            }
        }
        
        // 3. Precompute the first column that starts a valid right piece
        vector<vector<int>> next_c(n, vector<int>(m, m));
        for (int r = 0; r < n; ++r) {
            int first_1_col = m;
            for (int c = m - 1; c >= 0; --c) {
                int ones_in_col = ones[r][c] - ones[r][c + 1];
                if (ones_in_col > 0) first_1_col = c;
                next_c[r][c] = (first_1_col < m) ? first_1_col + 1 : m;
            }
        }
        
        // Base state DP for rem = 1 piece
        vector<vector<long long>> dp(n, vector<long long>(m, 0));
        vector<vector<long long>> suf_r(n + 1, vector<long long>(m + 1, 0));
        vector<vector<long long>> suf_c(n + 1, vector<long long>(m + 1, 0));
        
        for (int r = n - 1; r >= 0; --r) {
            for (int c = m - 1; c >= 0; --c) {
                if (ones[r][c] > 0) {
                    dp[r][c] = 1;
                }
                suf_r[r][c] = (dp[r][c] + suf_r[r + 1][c]) % MOD;
                suf_c[r][c] = (dp[r][c] + suf_c[r][c + 1]) % MOD;
            }
        }
        
        // DP for rem = 2 to k pieces
        for (int rem = 2; rem <= k; ++rem) {
            vector<vector<long long>> new_dp(n, vector<long long>(m, 0));
            vector<vector<long long>> new_suf_r(n + 1, vector<long long>(m + 1, 0));
            vector<vector<long long>> new_suf_c(n + 1, vector<long long>(m + 1, 0));
            
            for (int r = n - 1; r >= 0; --r) {
                for (int c = m - 1; c >= 0; --c) {
                    if (ones[r][c] > 0) { // Valid subgrid check
                        long long ways = 0;
                        
                        // Add valid horizontal cuts in O(1)
                        int nr = next_r[r][c];
                        if (nr < n) ways = (ways + suf_r[nr][c]) % MOD;
                        
                        // Add valid vertical cuts in O(1)
                        int nc = next_c[r][c];
                        if (nc < m) ways = (ways + suf_c[r][nc]) % MOD;
                        
                        new_dp[r][c] = ways;
                    }
                    
                    // Build suffix sums for the next layer
                    new_suf_r[r][c] = (new_dp[r][c] + new_suf_r[r + 1][c]) % MOD;
                    new_suf_c[r][c] = (new_dp[r][c] + new_suf_c[r][c + 1]) % MOD;
                }
            }
            // Move into current state
            dp = move(new_dp);
            suf_r = move(new_suf_r);
            suf_c = move(new_suf_c);
        }
        
        return dp[0][0];
    }
};
