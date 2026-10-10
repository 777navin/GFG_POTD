/*
=========================================================
Date        : 10-10-2026
Problem Name: Balancing with Distinct Powers
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Math, Number System, Greedy

Problem Summary:
Given a target weight b and a base a, determine if a weighing scale 
can be balanced by adding distinct powers of a to either side such 
that b + (some powers of a) = (some other powers of a).

Key Observation:
This problem can be viewed as representing b in a balanced base 'a' 
where digits can be -1, 0, or 1. At each step, the remainder modulo 'a' 
must be 0, 1, or a - 1 (which corresponds to -1 with a carry).
=========================================================
*/

class Solution {
public:
    bool balancePan(int a, int b) {
        /*
        Approach: Balanced Base-a Representation (Greedy / Carry Propagation)
        
        • Intuition:
          Adding powers of 'a' to the side with 'b' or to the opposite side 
          corresponds to digits in {-1, 0, 1} when expressing 'b' in base 'a'.
          
        • Approach:
          1. While b > 0, compute remainder rem = b % a.
          2. If rem == 0 or rem == 1, set b = b / a.
          3. If rem == a - 1, it requires a carry, so set b = (b + 1) / a.
          4. If rem is any other value, it cannot be balanced using distinct powers, return false.
          
        • Why it Works:
          Every valid digit in balanced base 'a' must be 0, 1, or a-1 (which acts as -1). 
          Any other remainder cannot be resolved with single carries, violating the 
          distinct power constraint.
          
        • Time Complexity (TC): O(log_a(b))
        • Space Complexity (SC): O(1)
        */
        
        long long currentB = b;
        while (currentB > 0) {
            long long rem = currentB % a;
            if (rem == 0 || rem == 1) {
                currentB /= a;
            } else if (rem == a - 1) {
                currentB = (currentB + 1) / a;
            } else {
                return false;
            }
        }
        return true;
    }
};

/*
FINAL APPROACH:
The balanced base conversion approach is chosen because it correctly handles remainders equal to a - 1 (representing a subtraction with a carry). This fixes the previous logic error on test cases like a = 4, b = 11 where the remainder is 3, running in optimal logarithmic time with constant space.
*/
