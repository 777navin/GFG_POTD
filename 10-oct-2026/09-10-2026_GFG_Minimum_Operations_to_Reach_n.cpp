/*
=========================================================
Date        : 09-10-2026
Problem Name: Minimum Operations to Reach n
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Dynamic Programming, Greedy, Mathematics

Problem Summary:
Given a number n, find the minimum number of operations required to reach n starting from 0.
The available operations are:
1. Double the current number.
2. Add one to the current number.

Key Observation:
Working backwards from n to 0 is optimal: if n is even, dividing by 2 (reversing doubling) 
reduces the value fastest; if n is odd, subtracting 1 (reversing adding 1) makes it even.
=========================================================
*/

#include <bits/stdc++. or stream>
#include <iostream>

using namespace std;

/*
---------------------------------------------------------
APPROACH 1: Working Backwards (Greedy - Most Optimal)
---------------------------------------------------------

• Intuition:
  Instead of building up from 0 to n using addition and doubling, work backwards from n to 0.
  Dividing an even number by 2 reduces its magnitude much faster than subtracting 1.

• Approach:
  Start with `n` and count operations until reaching 0:
  - If n is even, divide n by 2.
  - If n is odd, decrement n by 1.
  Increment the operation count at each step.

• Why it Works:
  Greedy choice property holds because dividing an even number by 2 always yields a value 
  less than or equal to subtracting 1 twice, minimizing the total operational steps.

• Time Complexity (TC): O(log n)
  Dividing n by 2 at least every two steps reduces n logarithmically.

• Space Complexity (SC): O(1)
  Only uses a few scalar variables for tracking operations.
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
• Chosen Approach: Working Backwards (Greedy)
• Reasons for Selection:
  1. Reduces time complexity to logarithmic time O(log n), which easily handles n up to 10^6 within constraints.
  2. Uses O(1) auxiliary space compared to dynamic programming which requires O(n) space.
  3. Simple, highly efficient, and directly computes the optimal answer without state overhead.
*/

class Solution {
public:
    int minOperation(int n) {
        int operations = 0;
        
        while (n > 0) {
            if (n % 2 == 0) {
                n /= 2;
            } else {
                n -= 1;
            }
            operations++;
        }
        
        return operations;
    }
};09-10-2026_GFG_Minimum_Operations_to_Reach_n.cpp
