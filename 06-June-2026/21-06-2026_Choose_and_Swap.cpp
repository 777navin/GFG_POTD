/*
Date: 22-06-2026
Problem Name: Choose and Swap
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Greedy, Strings, Sorting

Problem Summary:
Given a string s, you are allowed to swap all occurrences of any two distinct characters 
at most once. The goal is to make the resulting string lexicographically as small as possible.

Methods to Solve:
1. Optimal Approach (Greedy)

For Method 1:
- Intuition: To make the string lexicographically smallest, we want to replace the 
  leftmost character that can be replaced by a 'smaller' character available in the 
  string that hasn't appeared yet. We iterate through the string and for each 
  character, check if there is a smaller character present in the string that 
  appears after or at the current position.
- Approach:
  1. Store the first occurrence of each character in a frequency map or boolean array.
  2. Iterate through the string from left to right.
  3. For the current character 's[i]', check if there exists any character 'ch' 
     smaller than 's[i]' that has appeared in the string.
  4. If found, swap all occurrences of 's[i]' and 'ch' throughout the string and 
     terminate (since we can only perform the operation once).
- Time Complexity: O(N), where N is the length of the string.
- Space Complexity: O(1), as we only track 26 lowercase English letters.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Greedy | O(N)| O(1)| Lexicographical minimization problems

Final Recommended Solution: Use the greedy approach with a frequency map for optimal performance.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

class Solution {
public:
    string chooseSwap(string s) {
        // Track the presence of characters in the string
        vector<bool> present(26, false);
        for (char c : s) {
            present[c - 'a'] = true;
        }

        // Iterate through the string to find the first potential swap
        for (int i = 0; i < s.length(); ++i) {
            present[s[i] - 'a'] = false; // Current char is now 'used'

            // Look for a smaller character that exists in the string
            for (int j = 0; j < (s[i] - 'a'); ++j) {
                if (present[j]) {
                    char charToReplace = s[i];
                    char replacementChar = (char)(j + 'a');

                    // Perform the swap for all occurrences
                    for (int k = 0; k < s.length(); ++k) {
                        if (s[k] == charToReplace) {
                            s[k] = replacementChar;
                        } else if (s[k] == replacementChar) {
                            s[k] = charToReplace;
                        }
                    }
                    return s; // Only one swap allowed
                }
            }
        }
        return s;
    }
};

// Driver code to test locally
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    string s = "ccad";
    cout << "Original: " << s << " | Result: " << sol.chooseSwap(s) << endl;
    
    return 0;
}
