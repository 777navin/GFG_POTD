/*
=========================================================
Date        : 15-08-2026
Problem Name: Numbers Without d as Digit
Platform    : GeeksforGeeks
Difficulty  : Hard
Tags        : Dynamic Programming, Digit DP, Math

Problem Summary:
Count all integers from 1 to n that do not contain the digit d in their decimal representation.

Key Observation:
Since we are evaluating numbers based on their structural digits up to n, we can construct the numbers digit by digit. 
We must account for leading zeros carefully, especially when the prohibited digit d is 0.
=========================================================

1. Brute Force
• Intuition: Check every number from 1 to n to see if it contains the digit d.
• Approach: Loop i from 1 to n, isolate each digit, and skip if any digit equals d.
• Why it Works: It exhaustively verifies all numbers in the given range.
• Time Complexity (TC): O(n * log10(n)) - Iterating n times and checking each digit.
• Space Complexity (SC): O(1) - Constant extra space used.

2. Optimized (Digit DP)
• Intuition: Counting digit by digit avoids iterating over all sequential numbers, drastically reducing states.
• Approach: Track current index, a tight bound (if we can place up to 9 or restricted by n), and leading zero status.
• Why it Works: We build valid valid prefixes and reuse overlapping subproblems using memoization.
• Time Complexity (TC): O(log10(n) * 2 * 2 * 10) ~ O(log10(n)) - State space is small, processing up to 10 digits.
• Space Complexity (SC): O(log10(n)) - For the recursion depth and small 3D memoization array.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• The chosen approach is the Optimized Digit DP.
• Given the constraint n <= 10^9, the Brute Force approach will definitely result in Time Limit Exceeded (TLE).
• Digit DP easily runs in O(log10(n)) making it extremely efficient and perfectly scalable.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
    int dp[15][2][2];
    
    int solve(int idx, bool tight, bool is_zero, const string& s, int d) {
        if (idx == s.length()) return 1;
        if (dp[idx][tight][is_zero] != -1) return dp[idx][tight][is_zero];
        
        int limit = tight ? s[idx] - '0' : 9;
        int ans = 0;
        
        for (int i = 0; i <= limit; i++) {
            if (i == d) {
                // We only allow digit 'd' if 'd' is 0 and it acts as a leading zero
                if (d == 0 && is_zero) {
                    ans += solve(idx + 1, tight && (i == limit), true, s, d);
                }
                // Otherwise, skip this digit
            } else {
                ans += solve(idx + 1, tight && (i == limit), is_zero && (i == 0), s, d);
            }
        }
        
        return dp[idx][tight][is_zero] = ans;
    }
    
public:
    int countWithout(int n, int d) {
        string s = to_string(n);
        memset(dp, -1, sizeof(dp));
        
        // We subtract 1 at the end to exclude the counting of absolute '0'
        return solve(0, true, true, s, d) - 1;
    }
};

// Driver code to ensure it's fully GitHub-ready and standalone
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    if (cin >> t) {
        while (t--) {
            int n, d;
            cin >> n >> d;
            Solution obj;
            cout << obj.countWithout(n, d) << "\n";
        }
    }
    return 0;
}
