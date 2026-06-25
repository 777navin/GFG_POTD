/*
Date: 25-06-2026
Problem Name: N-Digit Numbers with Increasing Digits
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Backtracking, Recursion, Combinatorics

Problem Summary:
Given an integer n, return all the n-digit numbers such that their digits are 
in strictly increasing order (from left to right).

Methods to Solve:
1. Backtracking (Recursive)
2. Combinatorial/Iterative (Constructive)

For EACH method include:

- Intuition:
  The problem requires digits to be in strictly increasing order. This means for 
  a number of length n, we are essentially choosing n distinct digits from the 
  set {0, 1, 2, ..., 9}. If n > 10, no such number exists.
  
- Approach:
  We can use a recursive function that tracks the last digit used and the 
  current length of the number being formed. We only pick digits greater 
  than the last digit added.

- Time Complexity: O(10^n) roughly, but significantly constrained by the 
  strictly increasing requirement. Total numbers are C(10, n).
- Space Complexity: O(n) for the recursion stack.

Comparison Table:
Method         | TC      | SC   | Best Use Case
-------------------------------------------------------
Backtracking   | O(10^n) | O(n) | General case, intuitive
Combinatorial  | O(C)    | O(C) | When n is very small

Final Recommended Solution:
Backtracking is preferred for clarity and handling edge cases like n=1 
(where 0 is allowed) vs n > 1.
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution {
public:
    /**
     * @brief Generates all n-digit numbers with strictly increasing digits.
     * * @param n The number of digits.
     * @return vector<int> Sorted list of valid numbers.
     */
    vector<int> increasingNumbers(int n) {
        if (n == 1) return {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        if (n > 10) return {};
        
        vector<int> result;
        // Start recursion: last digit is -1, current number is 0, count is 0
        backtrack(n, -1, 0, result);
        return result;
    }

private:
    void backtrack(int n, int lastDigit, int currentNum, vector<int>& result) {
        if (n == 0) {
            result.push_back(currentNum);
            return;
        }
        
        // Start from lastDigit + 1. If lastDigit is -1, start from 1 (to avoid leading zero)
        int start = (lastDigit == -1) ? 1 : lastDigit + 1;
        
        for (int i = start; i <= 9; ++i) {
            backtrack(n - 1, i, currentNum * 10 + i, result);
        }
    }
};

// Driver Code
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    int n = 2;
    vector<int> ans = sol.increasingNumbers(n);
    
    cout << "Output for n=" << n << ": ";
    for (int num : ans) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}
