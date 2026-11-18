/*
=========================================================
Date        : 18-11-2026
Problem Name: XOR of Number Range
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Bit Manipulation, Mathematical, Prefix XOR

Problem Summary:
Given two integers l and r (1 <= l <= r <= 10^9), compute the 
bitwise XOR of all integers in the inclusive range [l, r].

Key Observation:
XOR from l to r equals (XOR from 1 to r) ^ (XOR from 1 to l-1), 
and the prefix XOR from 1 to n follows a repeating cycle of length 4.
=========================================================
*/

/*
=========================================================
APPROACH 1: Brute Force
=========================================================
• Intuition:
  Directly iterate through every integer from l to r and 
  accumulate their bitwise XOR.

• Approach:
  Initialize ans = 0, run a loop from i = l to r, and update 
  ans ^= i at each step.

• Why it Works:
  Bitwise XOR is associative and commutative, so sequential 
  XORing computes the exact range XOR.

• Time Complexity (TC): O(r - l + 1) -> TLE for r - l up to 10^9.
• Space Complexity (SC): O(1)
=========================================================

=========================================================
APPROACH 2: Most Optimal (Prefix XOR Pattern)
=========================================================
• Intuition:
  Since X ^ X = 0, range XOR [l, r] can be derived by canceling 
  out [1, l-1] from [1, r] using xorToN(r) ^ xorToN(l - 1).

• Approach:
  Compute prefix XOR from 1 to n in O(1) using n % 4:
  - n % 4 == 0 -> n
  - n % 4 == 1 -> 1
  - n % 4 == 2 -> n + 1
  - n % 4 == 3 -> 0
  Return xorToN(r) ^ xorToN(l - 1).

• Why it Works:
  Every block of 4 consecutive integers starting at a multiple of 4 
  (4k, 4k+1, 4k+2, 4k+3) has a combined XOR of 0, creating a strict 
  modulo-4 pattern.

• Time Complexity (TC): O(1)
• Space Complexity (SC): O(1)
=========================================================
*/

/*
=========================================================
FINAL APPROACH
=========================================================
The Most Optimal (Prefix XOR Pattern) approach is chosen because 
r can be as large as 10^9, making an O(r - l) loop too slow. 
Using the modulo-4 property reduces both time and space complexity 
to strict O(1) with zero extra memory.
=========================================================
*/

class Solution {
  private:
    // Helper to compute XOR of all integers from 1 to n in O(1)
    int xorToN(int n) {
        if (n % 4 == 0) return n;
        if (n % 4 == 1) return 1;
        if (n % 4 == 2) return n + 1;
        return 0; // n % 4 == 3
    }

  public:
    int findXOR(int l, int r) {
        return xorToN(r) ^ xorToN(l - 1);
    }
};
