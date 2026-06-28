/*
Date: 28-06-2026
Problem Name: k Times Appearing Adjacent Two 1's
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Dynamic Programming, Combinatorics, Strings

Problem Summary:
Given two integers n and k, count the number of binary strings of length n 
where adjacent 1s ('11') appear exactly k times.
Return the answer modulo 10^9 + 7.

Methods to Solve:
1. Dynamic Programming (Tabulation/Memoization)

For EACH method include:

- Intuition:
  We need to keep track of the current length of the string, the number of 
  adjacent 1s formed so far, and the previous character added (to know if 
  adding a '1' creates a new adjacent pair).

- Approach:
  Define dp[i][j][last]:
  - i: current length of the string (1 to n)
  - j: current count of adjacent 1s (0 to k)
  - last: the last character added (0 or 1)
  
  Transitions:
  - If we add '0':
    - New state: (i+1, j, 0)
    - Always possible regardless of last char.
  - If we add '1':
    - If last was '0': new state (i+1, j, 1)
    - If last was '1': new state (i+1, j+1, 1) (this forms an adjacent pair)

- Time Complexity: O(n * k)
- Space Complexity: O(n * k)

Comparison Table:
Method | TC | SC | Best Use Case
DP     | O(n*k) | O(n*k) | Standard for small constraints (n, k <= 1000)

Final Recommended Solution: Dynamic Programming
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int countStrings(int n, int k) {
        if (k >= n) return (k == n - 1 && n > 0) ? 1 : 0;
        
        const int MOD = 1e9 + 7;
        
        // dp[i][j][last]
        // i: current length
        // j: current adjacent 1s count
        // last: 0 or 1
        vector<vector<vector<long long>>> dp(n + 1, vector<vector<long long>>(k + 1, vector<long long>(2, 0)));
        
        // Base cases for length 1
        dp[1][0][0] = 1; // "0"
        dp[1][0][1] = 1; // "1"
        
        for (int i = 1; i < n; ++i) {
            for (int j = 0; j <= k; ++j) {
                // If last was 0
                if (dp[i][j][0] > 0) {
                    // Add 0
                    dp[i + 1][j][0] = (dp[i + 1][j][0] + dp[i][j][0]) % MOD;
                    // Add 1
                    dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][0]) % MOD;
                }
                // If last was 1
                if (dp[i][j][1] > 0) {
                    // Add 0
                    dp[i + 1][j][0] = (dp[i + 1][j][0] + dp[i][j][1]) % MOD;
                    // Add 1 (increments adjacent pair count)
                    if (j + 1 <= k) {
                        dp[i + 1][j + 1][1] = (dp[i + 1][j + 1][1] + dp[i][j][1]) % MOD;
                    }
                }
            }
        }
        
        return (dp[n][k][0] + dp[n][k][1]) % MOD;
    }
};
