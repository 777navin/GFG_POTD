// 28-04-2026_GFG_Longest_Repeating_Character_Replacement.cpp

/*
Date: 28-04-2026
Problem Name: Longest Repeating Character Replacement
Platform: GeeksforGeeks
Difficulty: Medium
Tags: String, Sliding Window, Two Pointers, Hash Table

Problem Summary:
Given a string 's' of uppercase English letters and an integer 'k', you can replace at most 'k' 
characters with any other uppercase English letter. The goal is to find the length of the longest 
substring containing all identical characters after performing these replacements.

=================================================================================================
Methods to Solve:
=================================================================================================

1. Brute Force (Conceptual)
---------------------------
- Intuition: Generate all possible substrings, calculate the most frequent character in each 
  substring, and check if the remaining characters (which need to be replaced) are <= k.
- Approach: Use nested loops to define the start and end of every substring. Use a hash map or 
  frequency array to find the maximum frequency character in the current substring. If 
  `length - max_frequency <= k`, update the maximum length found so far.
- Dry Run: For "ABBA", k=2. Check "A", "AB", "ABB", "ABBA", etc.
- Time Complexity: O(N^2) to iterate all substrings.
- Space Complexity: O(1) as the frequency array size is constant (26 uppercase letters).
- Why better than previous method: It serves as the fundamental baseline logic.
- When to use: Never use in a real contest/interview (will result in Time Limit Exceeded for large N).

2. Optimal Approach (Sliding Window)
------------------------------------
- Intuition: Instead of recalculating frequencies for every substring, we can maintain a dynamic 
  "window" using two pointers (`left` and `right`). As long as the number of characters we need 
  to replace in our current window is less than or equal to `k`, the window is valid, and we 
  can expand it.
- Approach: 
  1. Use an array `hash` of size 26 to store character frequencies in the current window.
  2. Iterate with a `right` pointer. Add the current character to the hash and update `maxFreq` 
     (the frequency of the most common character in the window).
  3. The number of characters to replace is `(window_length - maxFreq)`.
  4. If `(right - left + 1) - maxFreq > k`, our window is invalid. We shrink it by moving the 
     `left` pointer forward and decreasing the frequency of the outgoing character.
  5. Update `maxLength` with the size of the valid window.
- Dry Run (Example 1: s = "ABBA", k = 2):
  - right=0, char='A': hash['A']=1, maxFreq=1. Replacements: 1-1=0 <= 2. maxLength=1.
  - right=1, char='B': hash['B']=1, maxFreq=1. Replacements: 2-1=1 <= 2. maxLength=2.
  - right=2, char='B': hash['B']=2, maxFreq=2. Replacements: 3-2=1 <= 2. maxLength=3.
  - right=3, char='A': hash['A']=2, maxFreq=2. Replacements: 4-2=2 <= 2. maxLength=4.
  - Result: 4.
- Time Complexity: O(N) where N is the length of the string. Both left and right pointers 
  traverse the string at most once.
- Space Complexity: O(1) auxiliary space (array of fixed size 26).
- Why better than previous method: Reduces time complexity from quadratic O(N^2) to linear O(N).
- When to use: Standard optimal solution expected in all competitive programming and interviews.

=================================================================================================
Comparison Table:
=================================================================================================
+-------------------+-------------------+-------------------+---------------------------------+
| Method            | Time Complexity   | Space Complexity  | Best Use Case                   |
+-------------------+-------------------+-------------------+---------------------------------+
| 1. Brute Force    | O(N^2)            | O(1)              | Purely theoretical/understanding|
| 2. Sliding Window | O(N)              | O(1)              | Production, Contests, Interviews|
+-------------------+-------------------+-------------------+---------------------------------+

Final Recommended Solution: Approach 2 (Sliding Window)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestSubstr(string& s, int k) {
        int n = s.length();
        int maxFreq = 0;
        int maxLength = 0;
        int left = 0;
        
        // Frequency array for uppercase English letters
        vector<int> hash(26, 0);
        
        for (int right = 0; right < n; ++right) {
            // Include current character in the window
            hash[s[right] - 'A']++;
            
            // Track the maximum frequency of a single character in the current window
            maxFreq = max(maxFreq, hash[s[right] - 'A']);
            
            // Current window size is (right - left + 1).
            // Elements to replace = (Window Size) - (Max Frequency Character Count)
            // If replacements needed exceed k, shrink the window from the left
            if ((right - left + 1) - maxFreq > k) {
                hash[s[left] - 'A']--;
                left++;
            }
            
            // Update the maximum length found so far
            // Note: Since we only increment `left` by 1 when the window is invalid,
            // the window size never shrinks, it only stays the same or grows.
            // This is a neat optimization allowing us to find the absolute maximum.
            maxLength = max(maxLength, right - left + 1);
        }
        
        return maxLength;
    }
};

// ==============================================================================
// Driver Code (For Local Testing / GitHub Completeness)
// ==============================================================================
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Test Case 1
    string s1 = "ABBA";
    int k1 = 2;
    cout << "Input: s = \"" << s1 << "\", k = " << k1 << "\n";
    cout << "Output: " << sol.longestSubstr(s1, k1) << " (Expected: 4)\n\n";

    // Test Case 2
    string s2 = "ADBD";
    int k2 = 1;
    cout << "Input: s = \"" << s2 << "\", k = " << k2 << "\n";
    cout << "Output: " << sol.longestSubstr(s2, k2) << " (Expected: 3)\n";

    return 0;
}
