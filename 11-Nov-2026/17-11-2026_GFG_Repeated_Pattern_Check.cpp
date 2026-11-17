/*
=========================================================
Date        : 17-11-2026
Problem Name: Repeated Pattern Check
Platform: GeeksforGeeks (GFG)
Difficulty: Easy
Tags: Strings, Two Pointers, Stack

Problem Summary:
Given a string s consisting solely of characters 'x' and 'y', verify if the 
entire string can be partitioned into concatenated substrings matching the 
pattern (x^n)(y^n), where every consecutive block of 'x's is immediately 
followed by an equal number of consecutive 'y's.

Key Observation:
Every maximal contiguous block of 'x's must be strictly followed by a maximal 
contiguous block of 'y's of the exact same length; the string cannot start 
with 'y' or end with 'x'.
=========================================================
*/

/*
=========================================================
APPROACHES
=========================================================

1. Brute Force (Recursive / Substring Slicing)
• Intuition:
  Greedily match the first prefix of 'x's with an equal number of 'y's, slice 
  that valid block off, and repeat on the remaining suffix.
• Approach:
  Count leading 'x's (countX), verify the next countX characters are 'y's, 
  and recursively or iteratively pass a new sliced substring.
• Why it Works:
  Since substrings are concatenated without overlap, the prefix must form a 
  valid x^n y^n block before the next block can begin.
• Time Complexity (TC): O(N^2) due to repeated string slicing/copying.
• Space Complexity (SC): O(N) for auxiliary substrings and recursion stack.

2. Better (Stack-Based Simulation)
• Intuition:
  Use a stack to push 'x' characters and pop them when encountering 'y' 
  characters, ensuring phase transitions only happen at valid boundaries.
• Approach:
  Push 'x' onto a stack. When 'y' appears, pop 'x' for each consecutive 'y'. 
  If a new 'x' arrives while the stack is non-empty, return false.
• Why it Works:
  Enforces strict ordering (all 'x's before 'y's per block) and guarantees 
  exact 1-to-1 matching before starting a new block.
• Time Complexity (TC): O(N), where N is the length of string s.
• Space Complexity (SC): O(N) in the worst case when all characters are 'x'.

3. Most Optimal (Two-Pointer / Linear Block Counting)
• Intuition:
  Instead of storing characters in a stack, directly count the lengths of 
  adjacent 'x' and 'y' groups in a single linear pass.
• Approach:
  Use an index pointer i. Count consecutive 'x's, then count consecutive 'y's. 
  If either count is 0 or countX != countY, return false. Repeat until end.
• Why it Works:
  Counting consecutive frequencies directly validates the x^n y^n structure 
  for each segment without extra memory overhead.
• Time Complexity (TC): O(N), each character is visited exactly once.
• Space Complexity (SC): O(1), only integer counters are used.
=========================================================
*/

/*
=========================================================
FINAL APPROACH
=========================================================
The Most Optimal (Two-Pointer / Linear Block Counting) approach is chosen.
It eliminates the O(N) auxiliary space required by stack or substring slicing 
solutions while maintaining a strict single-pass O(N) runtime, easily handling 
constraints up to 10^5.
=========================================================
*/

#include <string>

using namespace std;

class Solution {
  public:
    bool findPattern(string& s) {
        int n = s.size();
        int i = 0;

        while (i < n) {
            int countX = 0;
            int countY = 0;

            // Count consecutive 'x' characters
            while (i < n && s[i] == 'x') {
                countX++;
                i++;
            }

            // Count consecutive 'y' characters immediately following 'x'
            while (i < n && s[i] == 'y') {
                countY++;
                i++;
            }

            // Every valid block requires at least one 'x' and an equal number of 'y's
            if (countX == 0 || countX != countY) {
                return false;
            }
        }

        return true;
    }
};
