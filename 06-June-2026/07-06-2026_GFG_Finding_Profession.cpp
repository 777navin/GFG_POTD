/*
Date: 07-06-2026
Problem Name: Finding Profession
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Recursion, Bit Manipulation, Math

Problem Summary:
In a family tree where an Engineer (E) has children (E, D) and a Doctor (D) has children (D, E),
every generation starts with an Engineer. We need to find the profession of a person at a 
given level and position.

Methods to Solve:
1. Recursive Approach (Simulation)
2. Bit Manipulation (Optimal)

For EACH method include:

- Method 1: Recursive Approach
  - Intuition: Determine the parent's profession. If the current position is even, it is the 
    second child of the parent. If odd, it is the first.
  - Approach: Find the parent at (level-1, (pos+1)/2). If the parent is an Engineer: 
    1st child is E, 2nd is D. If parent is Doctor: 1st child is D, 2nd is E.
  - Time Complexity: O(level)
  - Space Complexity: O(level) due to recursion stack.

- Method 2: Bit Manipulation (Optimal)
  - Intuition: The profession depends on the number of set bits (1s) in (pos - 1). 
    An even number of set bits results in an Engineer, while an odd number results in a Doctor.
  - Approach: Count the number of set bits in (pos - 1). If count is even, return 'e', else 'd'.
  - Time Complexity: O(log(pos))
  - Space Complexity: O(1)
  - Why better: Avoids recursion stack overhead and solves in logarithmic time.

Comparison Table:
Method             | TC       | SC      | Best Use Case
-------------------------------------------------------
Recursive          | O(level) | O(level)| Small constraints
Bit Manipulation   | O(log P) | O(1)    | Large constraints (Optimal)

Final Recommended Solution: Bit Manipulation
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Optimal solution using Bit Manipulation.
     * The pattern follows the parity of set bits in (pos - 1).
     */
    string profession(int level, long long pos) {
        // Count set bits in (pos - 1)
        long long n = pos - 1;
        int setBits = 0;
        
        while (n > 0) {
            n &= (n - 1); // Brian Kernighan's Algorithm
            setBits++;
        }
        
        // Even set bits -> Engineer, Odd set bits -> Doctor
        return (setBits % 2 == 0) ? "Engineer" : "Doctor";
    }
};

// Driver code for local testing
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Example 1
    cout << "Level 4, Pos 2: " << sol.profession(4, 2) << endl; // Output: Doctor
    
    // Example 2
    cout << "Level 3, Pos 4: " << sol.profession(3, 4) << endl; // Output: Engineer

    return 0;
}
