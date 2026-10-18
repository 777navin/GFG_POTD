/*
=========================================================
Date        : 18-10-2026
Problem Name: Shortest Path From 1 To n
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Graph, Breadth First Search, Dynamic Programming, Greedy

Problem Summary:
Given a directed graph with vertices from 1 to n where edges exist from i to i + 1 and from i to 3 * i.
The task is to find the minimum number of edges required to reach vertex n starting from vertex 1.

Key Observation:
Working backwards from n to 1 is much more efficient than searching forwards. If n is divisible by 3, dividing by 3 gives the optimal jump; otherwise, decrementing by 1 is the only valid reverse step.
=========================================================
*/

/*
=========================================================
APPROACH 1: Greedy / Backtracking (Most Optimal)
=========================================================

• Intuition:
  Instead of building paths from 1 to n, we can work backwards from n down to 1. At any number, 
  multiplying by 3 is better than adding 1 multiple times, so we should greedily divide by 3 whenever possible.

• Approach:
  - Initialize steps count to 0.
  - While n is greater than 1:
    - If n is divisible by 3, divide n by 3 and increment step count by 1.
    - Otherwise, decrement n by 1 and increment step count by 1.
  - Return the total steps.

• Why it Works:
  Greedily taking the division by 3 reduces the value much faster than subtracting 1, ensuring the minimum edge count.

• Time Complexity (TC): O(log3(n))
• Space Complexity (SC): O(1)
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minimumStep(int n) {
        int steps = 0;
        while (n > 1) {
            if (n % 3 == 0) {
                n /= 3;
            } else {
                n -= 1;
            }
            steps++;
        }
        return steps;
    }
};

/*
=========================================================
FINAL APPROACH CHOSEN
=========================================================
• The greedy backwards approach is chosen because it avoids explicit graph traversal, queue overhead, 
  and memory allocation.
• It is optimal with O(log3(n)) time complexity and O(1) auxiliary space, making it ideal for large constraints up to 10^8.
=========================================================
*/
