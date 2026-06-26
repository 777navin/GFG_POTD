/*
Date: 26-06-2026
Problem Name: Count Matching Subsequences
Platform: GeeksforGeeks
Difficulty: Medium
Tags: String, Dynamic Programming, Subsequence

Problem Summary:
Given two strings s1 and s2, find the number of ways to pick indices from s1 
such that they form the string s2 as a subsequence. Return the count modulo 1e9 + 7.

Methods to Solve:
1. Recursive Approach (Exponential)
2. Memoized Dynamic Programming (Top-Down)
3. Tabulated Dynamic Programming (Bottom-Up - Optimal)

For Method 3 (Optimal):

- Intuition: 
  We use a DP table where dp[i][j] represents the number of ways s2[0...i-1] 
  can be formed as a subsequence of s1[0...j-1].
- Approach:
  - If s1[j-1] == s2[i-1], then we can either include this character or exclude it.
    dp[i][j] = dp[i][j-1] + dp[i-1][j-1]
  - If they don't match, we can only exclude s1[j-1].
    dp[i][j] = dp[i][j-1]
  - Base case: If s2 is empty, there is 1 way (empty subsequence).
- Time Complexity: O(N * M) where N = s1.length, M = s2.length
- Space Complexity: O(M) using space optimization (since we only need the previous row)
- Why better: Reduces space from O(N*M) to O(M).
- When to use: When N, M <= 1000.

Comparison Table:
Method | TC | SC | Best Use Case
---------------------------------------
Recursion | O(2^N) | O(N) | Never (Constraints too high)
Memoization | O(N*M) | O(N*M) | When simple recursion isn't enough
Tabulation | O(N*M) | O(M) | Standard optimal solution

Final Recommended Solution: Space-optimized Tabulation
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    int countWays(string &s1, string &s2) {
        int n = s1.size();
        int m = s2.size();
        int MOD = 1e9 + 7;

        // dp[i] will store the number of ways to form s2[0...i-1]
        // using the prefix of s1 processed so far.
        vector<int> dp(m + 1, 0);
        
        // Base case: An empty s2 is a subsequence of any prefix of s1 in 1 way.
        dp[0] = 1;

        for (int j = 1; j <= n; j++) {
            // Traverse backwards to avoid using updated values from the same s1 char
            for (int i = m; i >= 1; i--) {
                if (s1[j - 1] == s2[i - 1]) {
                    dp[i] = (dp[i] + dp[i - 1]) % MOD;
                }
            }
        }

        return dp[m];
    }
};

// Driver code to test locally
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    string s1 = "geeksforgeeks";
    string s2 = "gks";
    
    cout << "Input: s1 = " << s1 << ", s2 = " << s2 << endl;
    cout << "Output: " << sol.countWays(s1, s2) << endl;

    return 0;
}
