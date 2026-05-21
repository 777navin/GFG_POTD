/*
Date: 21-05-2026
Problem Name: Check if All Bits Set
Platform: GeeksforGeeks
Difficulty: Basic
Tags: Bit Magic, Amazon

Problem Summary: 
Given a number n, check whether every bit in its binary representation is set to 1. Return true if yes, otherwise false. Note that if n = 0, the output must be false.

Methods to Solve:
1. Iterative Bit Check (Brute Force)
2. Bitwise AND Property (Optimal Approach)

-------------------------------------------------------------------------
Method 1: Iterative Bit Check (Brute Force)
- Intuition: Extract and check the least significant bit (LSB) one by one. If any bit is 0 during the process, the condition fails.
- Approach:
  1. If n == 0, return false.
  2. Loop while n > 0.
  3. Check if (n & 1) == 0 (meaning the LSB is 0). If so, return false.
  4. Right shift n by 1 (n >>= 1).
  5. Return true if the loop completes without finding any 0s.
- Dry Run: n = 7 (111 in binary)
  - Iter 1: LSB = 1. n becomes 3 (011)
  - Iter 2: LSB = 1. n becomes 1 (001)
  - Iter 3: LSB = 1. n becomes 0.
  - Returns true.
- Time Complexity: O(log N) - where log N represents the number of bits in N.
- Space Complexity: O(1)
- Why better than previous method: N/A (Baseline approach).
- When to use: When you want to demonstrate basic iterative bit manipulation.

-------------------------------------------------------------------------
Method 2: Bitwise AND Property (Optimal Approach)
- Intuition: A number `n` with all bits set (e.g., 7: 111, 15: 1111) has a unique mathematical property. If you add 1 to it, it becomes the next power of 2 (e.g., 8: 1000, 16: 10000). Therefore, the bitwise AND of `n` and `n + 1` will always be 0. 
- Approach:
  1. If n == 0, return false (handle edge case separately).
  2. Return true if (n & (n + 1)) == 0, else return false.
- Dry Run: n = 7 (111 in binary)
  - n + 1 = 8 (1000 in binary)
  - 7 & 8 -> 0111 & 1000 = 0000
  - (0000 == 0) evaluates to True.
- Time Complexity: O(1)
- Space Complexity: O(1)
- Why better than previous method: Evaluates the condition in a single, constant-time bitwise operation without requiring loops.
- When to use: Always recommended for optimal performance in competitive programming and production code.

Comparison Table:
Method                   | TC       | SC   | Best Use Case
-------------------------|----------|------|---------------------------
1. Iterative Bit Check   | O(log N) | O(1) | Explaining bit traversal 
2. Bitwise AND Property  | O(1)     | O(1) | Optimal & standard coding 

Final Recommended Solution: Method 2 (Bitwise AND Property)
*/

#include <iostream>
using namespace std;

class Solution {
public:
    // Optimal Approach: Bitwise AND Property
    bool isBitSet(int n) {
        // Base case: 0 has no set bits, should return false
        if (n == 0) {
            return false;
        }
        
        // If all bits are set, n + 1 becomes a power of 2.
        // Therefore, n & (n + 1) will perfectly evaluate to 0.
        return (n & (n + 1)) == 0;
    }

    /*
    // Method 1: Iterative Approach (Alternative)
    bool isBitSetIterative(int n) {
        if (n == 0) return false;
        
        while (n > 0) {
            // If the least significant bit is 0, then not all bits are set
            if ((n & 1) == 0) { 
                return false;
            }
            n >>= 1; // Shift right by 1 to check the next bit
        }
        return true;
    }
    */
};

// Driver Code for Local / Platform Testing
int main() {
    // Fast I/O for competitive programming
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // Comment out standard I/O prompts if pasting directly into strict OJ platforms
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;

            Solution obj;
            if (obj.isBitSet(n)) {
                cout << "true\n";
            } else {
                cout << "false\n";
            }
        }
    }
    return 0;
}
