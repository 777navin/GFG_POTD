/*
Date: 02-05-2026
Problem Name: Position of the Set Bit
Platform: GeeksforGeeks (GFG)
Difficulty: Basic
Tags: Bit Magic, Algorithms

Problem Summary:
Given an integer n, find the position of the only set bit (1) in its binary representation.
- Positions are 1-indexed, starting from the Least Significant Bit (LSB).
- If the number has zero set bits or more than one set bit, return -1.

Methods to Solve:
1. Iterative Bit Shifting (Brute Force)
2. Logarithmic Approach (Optimal)
3. Bit Manipulation Trick (Check Power of 2)

---

Method 1: Iterative Bit Shifting
- Intuition: A number with exactly one set bit is a power of 2. We can shift the number right until it becomes zero, counting how many shifts it takes.
- Approach: First, check if n > 0. Then, loop and check (n & 1). If we find a 1, record the position. If we find another 1 later, it's invalid.
- Dry Run (n=2): 
  - Binary: 10. 
  - Iteration 1: bit=0, pos=1. 
  - Iteration 2: bit=1, pos=2. 
  - Result: 2.
- Time Complexity: O(log N) - specifically O(number of bits).
- Space Complexity: O(1).
- Why better: Easiest to explain in an interview.
- When to use: When bit manipulation tricks are not immediately obvious.

Method 2: Bit Manipulation Trick (Optimal)
- Intuition: A number has exactly one set bit if and only if it is a power of 2. We check this using (n > 0 && (n & (n - 1)) == 0).
- Approach: 
  1. Validate if it is a power of 2.
  2. If yes, the position is simply log2(n) + 1.
- Time Complexity: O(1) if using built-in log or bit instructions.
- Space Complexity: O(1).
- Why better: Highly efficient, avoids loops entirely.
- When to use: In performance-critical competitive programming.

Comparison Table:
Method         | TC       | SC   | Best Use Case
---------------------------------------------------
Iterative      | O(log N) | O(1) | General clarity
Bit Trick + Log| O(1)     | O(1) | Optimal performance

Final Recommended Solution: Method 2 for its elegance and O(1) efficiency.
*/

#include <iostream>
#include <cmath>

class Solution {
public:
    /**
     * @brief Finds the position of the only set bit.
     * Uses bit manipulation to verify power of 2, then calculates position.
     */
    int findPosition(int n) {
        // Step 1: A number with exactly one set bit must be > 0 
        // and must satisfy the power-of-two property: (n & (n-1)) == 0
        if (n <= 0 || (n & (n - 1)) != 0) {
            return -1;
        }

        // Step 2: Calculate the position. 
        // log2(n) gives the 0-indexed position, so we add 1.
        // For n=2 (10 in binary), log2(2) = 1. 1+1 = 2.
        // For n=8 (1000 in binary), log2(8) = 3. 3+1 = 4.
        return (int)log2(n) + 1;
    }
    
    /**
     * @brief Alternative approach using bit shifting (Method 1).
     */
    int findPositionIterative(int n) {
        if (n <= 0 || (n & (n - 1)) != 0) return -1;
        
        int pos = 0;
        while (n > 0) {
            n >>= 1;
            pos++;
        }
        return pos;
    }
};

// Driver code for local testing (GFG compatible)
int main() {
    Solution sol;
    int n;
    std::cout << "Enter n: ";
    if (std::cin >> n) {
        std::cout << "Position: " << sol.findPosition(n) << std::endl;
    }
    return 0;
}
