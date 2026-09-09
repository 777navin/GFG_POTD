/*
=========================================================
Date        : 09-09-2026
Problem Name: Max Digit Sum Number in 1 to n
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Greedy, Math, Number Theory

Problem Summary:
Given an integer n, find a number in the range [1, n] that has
the maximum sum of its digits. If multiple such numbers exist,
return the largest one among them.

Key Observation:
Numbers ending with trailing 9s maximize digit sums. Any optimal candidate 
in [1, n] is either n itself or formed by decrementing one prefix digit 
of n by 1 and setting all following digits to 9.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Greedy Prefix Testing (Optimal)
---------------------------------------------------------
• Intuition:
  To maximize the digit sum within [1, n], trailing positions should 
  be filled with 9s wherever possible.

• Approach:
  - Convert n into its string representation S.
  - Set the initial best candidate to n with its digit sum.
  - For each digit position i from 0 to length - 1:
    - If S[i] > '0', decrement S[i] by 1 and set all subsequent digits to '9'.
    - Convert back to a number and compute its digit sum.
    - Update best candidate if the sum is greater, or if equal and the number is larger.

• Why it Works:
  - Any number <= n that differs from n must be smaller at the first point 
    of difference. Maximizing the remaining digits to 9 ensures maximum sum.

• Time Complexity (TC):
  - O(d^2), where d is the number of digits in n (d <= 10). Runs in O(1) time.

• Space Complexity (SC):
  - O(d) auxiliary space for string manipulation.
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION:
---------------------------------------------------------
This approach directly targets the <= 10 valid candidate prefixes in O(log n)
steps, completely bypassing the O(n) TLE constraint.
---------------------------------------------------------
*/

#include <string>
#include <algorithm>

class Solution {
private:
    int getDigitSum(long long num) {
        int sum = 0;
        while (num > 0) {
            sum += (num % 10);
            num /= 10;
        }
        return sum;
    }

public:
    int findMax(int n) {
        std::string s = std::to_string(n);
        int len = s.length();

        long long bestNum = n;
        int maxSum = getDigitSum(n);

        for (int i = 0; i < len; ++i) {
            if (s[i] == '0') continue;

            std::string candidateStr = s;
            candidateStr[i]--;

            for (int j = i + 1; j < len; ++j) {
                candidateStr[j] = '9';
            }

            long long candidate = std::stoll(candidateStr);
            int currentSum = getDigitSum(candidate);

            if (currentSum > maxSum) {
                maxSum = currentSum;
                bestNum = candidate;
            } else if (currentSum == maxSum) {
                bestNum = std::max(bestNum, candidate);
            }
        }

        return static_cast<int>(bestNum);
    }
};
