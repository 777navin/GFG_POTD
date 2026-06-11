/*
Date: 11-06-2026
Problem Name: Equal Point in Brackets
Platform: GeeksforGeeks
Difficulty: Easy
Tags: String, Stack, Prefix Sum

Problem Summary:
Given a string s of opening '(' and closing ')' brackets, find an equal point k (0-based). 
An equal point k is defined such that the number of opening brackets before position k 
is equal to the number of closing brackets from position k to the end of the string.

Methods to Solve:
1. Brute Force (Nested Loops)
2. Optimal Approach (Precomputation/Single Pass)

For EACH method include:

Method 1: Brute Force
- Intuition: Check every possible split point from 0 to n and count opening/closing brackets.
- Approach: Iterate k from 0 to n. For each k, count '(' in s[0...k-1] and ')' in s[k...n-1].
- Time Complexity: O(n^2)
- Space Complexity: O(1)

Method 2: Optimal Approach (Two Pass)
- Intuition: The count of '(' before k is essentially a prefix count. The count of ')' 
  after k (inclusive) can be precomputed or calculated using total counts.
- Approach:
  1. Count total closing brackets in the string.
  2. Iterate through the string, maintaining a count of opening brackets seen so far.
  3. At each index k, if `countOpen == countClosing`, that is our point.
  4. Decrement `countClosing` whenever we encounter a ')' at the current index.
- Time Complexity: O(n)
- Space Complexity: O(1)
- Why better: Reduces nested iteration to a single linear pass.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Brute Force | O(n^2) | O(1) | Small strings
Optimal | O(n) | O(1) | Large constraints (10^5)

Final Recommended Solution: Optimal Approach
*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    /**
     * Finds the first equal point k in the string.
     * @param s The input string of brackets.
     * @return The 0-based index of the equal point.
     */
    int findIndex(string& s) {
        int n = s.length();
        int totalClosing = 0;
        
        // Count total closing brackets initially
        for (char c : s) {
            if (c == ')') {
                totalClosing++;
            }
        }
        
        int countOpen = 0;
        int currentClosing = totalClosing;
        
        // Check split points from 0 to n
        for (int k = 0; k <= n; ++k) {
            // At index k:
            // Opening brackets before k: countOpen
            // Closing brackets from k to end: currentClosing
            if (countOpen == currentClosing) {
                return k;
            }
            
            // Update counts for next position
            if (k < n) {
                if (s[k] == '(') {
                    countOpen++;
                } else {
                    currentClosing--;
                }
            }
        }
        
        return n;
    }
};

// Driver code for local testing
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Solution sol;
    string s = "(())))(";
    cout << "Equal Point: " << sol.findIndex(s) << endl; // Output: 4
    
    return 0;
}
