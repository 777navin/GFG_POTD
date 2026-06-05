/*
Date: 05-06-2026
Problem Name: Lexicographically smallest after removing k
Platform: GeeksforGeeks
Difficulty: Medium
Tags: String, Greedy, Stack, Math

Problem Summary:
Given a string s of length n. First, adjust k: 
- If n is a power of 2, k = k / 2.
- Otherwise, k = k * 2.
Remove exactly k characters from s to make the remaining string lexicographically 
smallest. If k >= n or the resulting string is empty, return "-1".

Methods to Solve:
1. Greedy Approach using Monotonic Stack
- Intuition: To get the lexicographically smallest string, we want smaller characters 
  to appear as early as possible. We use a monotonic stack to maintain the smallest 
  possible character sequence.
- Approach:
  1. Calculate n. Check if it's a power of 2 using (n & (n - 1)) == 0.
  2. Adjust k based on the rule. If k >= n, return "-1".
  3. Iterate through string characters. While the current character is smaller than 
     the top of the stack and we still have removals left, pop from the stack.
  4. Push current character to stack.
  5. If stack size exceeds (n - k), pop from the stack.
  6. The stack now contains the lexicographically smallest result.
- Time Complexity: O(n)
- Space Complexity: O(n)

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Monotonic Stack | O(n) | O(n) | Optimal for lexicographical smallest string problems

Final Recommended Solution: Monotonic Stack
*/

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    string lexicographicallySmallest(string& s, int k) {
        int n = s.length();
        
        // Determine if n is a power of 2
        bool isPowerOfTwo = (n > 0) && ((n & (n - 1)) == 0);
        
        // Correct the value of k
        if (isPowerOfTwo) {
            k /= 2;
        } else {
            k *= 2;
        }
        
        // Check if removal is possible
        if (k >= n) {
            return "-1";
        }
        
        int removalsNeeded = k;
        string result = "";
        
        // Monotonic stack approach to keep string smallest
        for (char c : s) {
            while (removalsNeeded > 0 && !result.empty() && result.back() > c) {
                result.pop_back();
                removalsNeeded--;
            }
            result.push_back(c);
        }
        
        // If we still need to remove characters (e.g., string was non-decreasing)
        while (removalsNeeded > 0 && !result.empty()) {
            result.pop_back();
            removalsNeeded--;
        }
        
        return result.empty() ? "-1" : result;
    }
};

// Driver code to demonstrate functionality
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Example 1
    string s1 = "fooland";
    int k1 = 2;
    cout << "Input: " << s1 << ", " << k1 << " | Output: " << sol.lexicographicallySmallest(s1, k1) << endl;
    
    // Example 2
    string s2 = "code";
    int k2 = 4;
    cout << "Input: " << s2 << ", " << k2 << " | Output: " << sol.lexicographicallySmallest(s2, k2) << endl;

    return 0;
}
