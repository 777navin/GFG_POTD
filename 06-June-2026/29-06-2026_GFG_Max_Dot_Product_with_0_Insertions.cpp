/*
Date: 29-06-2026
Problem Name: Maximize Dot Product
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Dynamic Programming, Arrays, Space Optimization

Problem Summary
Given two arrays `a[]` and `b[]` of positive integers of size `n` and `m` (m <= n). 
We are allowed to insert exactly `n - m` zeros anywhere into array `b` so that its length becomes equal to `n`. 
The goal is to maximize the dot product of the two arrays.

Methods to Solve:
1. Space-Optimized 1D Dynamic Programming

For EACH method include:

- Intuition: At each step we either match `a[i]` with `b[j]` or skip `a[i]` (which is equivalent to matching it with a 0 inserted in `b`). We must match all `m` elements of `b`.
- Approach: We maintain a 1D DP array where `dp[j]` represents the maximum dot product for the suffix of `b` starting at index `j`. We iterate through `a` from right to left. Invalid states (where remaining elements in `a` are fewer than remaining in `b`) are skipped and penalized with `-INF` to ensure we match all `m` elements of `b`.
- Dry Run (small example):
  a = [5, 8], b = [9, 1]
  Initially, dp = [-INF, -INF, 0]
  i=1 (a=8):
     j=0: 8*9 + dp[1](-INF) = -INF. skip = dp[0] = -INF. dp[0] = -INF.
     j=1: 8*1 + dp[2](0) = 8. skip = dp[1] = -INF. dp[1] = 8.
     dp becomes [-INF, 8, 0]
  i=0 (a=5):
     j=0: 5*9 + dp[1](8) = 53. skip = dp[0] = -INF. dp[0] = 53.
     j=1: 5*1 + dp[2](0) = 5. skip = dp[1] = 8. dp[1] = 8.
     dp becomes [53, 8, 0]
  Result: dp[0] = 53
- Time Complexity: O(n * m)
- Space Complexity: O(m)
- Why better than previous method: The previous code caused a Compilation Error because GeeksforGeeks driver code passes `std::vector<int>&` instead of primitive arrays `int[]`. This updated solution correctly matches the `maxDotProduct(vector<int>&, vector<int>&)` signature expected by the platform while keeping the optimal 1D space logic.
- When to use: Ideal for DP subsequence matching problems with space constraints.

Comparison Table:
Method               | TC     | SC     | Best Use Case
---------------------|--------|--------|--------------
Space-Optimized DP   | O(n*m) | O(m)   | Optimal, exact platform signature match

Final Recommended Solution: Space-Optimized 1D Dynamic Programming
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxDotProduct(vector<int>& a, vector<int>& b) {
        int n = a.size();
        int m = b.size();
        
        // Use 1e9 to represent invalid states to avoid integer underflow during addition
        const int INF = 1e9; 
        
        // dp[j] will store the max dot product for suffix of b starting at j
        vector<int> dp(m + 1, -INF); 
        dp[m] = 0; // Base case: both arrays perfectly exhausted
        
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < m; ++j) {
                // BOUNDARY CHECK: 
                // If remaining elements in 'a' are fewer than remaining in 'b',
                // we cannot possibly match all elements of 'b'. It's an invalid state.
                if (n - i < m - j) {
                    dp[j] = -INF;
                    continue;
                }
                
                // Option 1: Match a[i] and b[j]
                // Check against -INF to prevent invalid states from becoming "less invalid"
                int match = (dp[j + 1] == -INF) ? -INF : a[i] * b[j] + dp[j + 1];
                
                // Option 2: Skip a[i] (effectively b[j] matches with a later element of a)
                int skip = dp[j];
                
                dp[j] = max(match, skip);
            }
        }
        
        return dp[0];
    }
};

// Driver Code
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Example 1
    vector<int> a1 = {2, 3, 1, 7, 8};
    vector<int> b1 = {3, 6, 7};
    cout << "Output 1: " << sol.maxDotProduct(a1, b1) << "\n"; // Expected: 107
    
    // Example 2
    vector<int> a2 = {1, 2, 3};
    vector<int> b2 = {4};
    cout << "Output 2: " << sol.maxDotProduct(a2, b2) << "\n"; // Expected: 12
    
    // Example 3 (Failing test case validation)
    vector<int> a3 = {5, 8}; 
    vector<int> b3 = {9, 1};
    cout << "Output 3: " << sol.maxDotProduct(a3, b3) << "\n"; // Expected: 53

    return 0;
}
