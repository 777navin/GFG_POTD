/*
=========================================================
Date        : 28-10-2026
Problem Name: Nth character in concatenated decimal string
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Math, String

Problem Summary:
- Consider an infinite string formed by concatenating positive integers: "123456789101112...".
- Given a 1-based index `n`, find the character at the nth position in the string.

Key Observation:
- Numbers have varying digit lengths (1-digit numbers from 1 to 9, 2-digit numbers from 10 to 99, etc.).
- We can determine which number block `n` falls into and pinpoint the exact digit using mathematical range calculations.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Optimized (Digit-Range Counting)
• Intuition: Instead of generating the string, count how many characters are contributed by numbers of length 1, length 2, length 3, etc.
• Approach: 
  - Iterate through digit lengths (`len = 1, 2, 3...`).
  - Calculate the count of numbers having `len` digits and their total character contribution (`count * len`).
  - If `n` exceeds this contribution, subtract it from `n` and move to the next digit length.
  - Once `n` falls within the current digit length, calculate the exact number and the specific digit position within that number.
• Why itWorks: Bypasses string generation entirely by directly jumping to the target number block using arithmetic bounds, easily handling large constraints up to 10^9.
• Time Complexity (TC): O(log10(n))
• Space Complexity (SC): O(1)
=========================================================
*/

/*
=========================================================
FINAL APPROACH
=========================================================
- The digit-range counting approach is chosen because `n` can be as large as 10^9, making a simulation or brute-force string concatenation approach impossible due to memory and time limits.
- It operates in logarithmic time with constant extra space, which is optimal.
- The function name matches the driver code's expected method name (`nthCharacter`).
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    char nthCharacter(int n) {
        long long len = 1;      // Current digit length of numbers being processed
        long long count = 9;    // Total numbers having 'len' digits
        long long start = 1;    // The first number with 'len' digits

        // Find the block of numbers where the nth character lies
        while (n > len * count) {
            n -= len * count;
            len++;
            count *= 10;
            start *= 10;
        }

        // Find the exact number containing the nth character
        long long targetNumber = start + (n - 1) / len;
        
        // Find the exact digit index within the target number
        int digitIndex = (n - 1) % len;

        // Convert the target number to a string and return the specific character
        string s = to_string(targetNumber);
        return s[digitIndex];
    }
};
