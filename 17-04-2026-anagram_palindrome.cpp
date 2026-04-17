/**
 * Date: 17-04-2026
 * Problem: Anagram Palindrome
 * Platform: GeeksforGeeks (GFG)
 * Difficulty: Basic
 */

/*
    Intuition:
    A string can be rearranged into a palindrome if and only if at most one character 
    appears an odd number of times. 
    - If string length is even: All characters must have even frequencies.
    - If string length is odd: Exactly one character must have an odd frequency.

    Approach:
    1. Count the frequency of each character in the string using a hash map or 
       a frequency array (since characters are lowercase English letters).
    2. Count how many characters have an 'odd' frequency.
    3. If the count of odd frequencies is greater than 1, return false.
    4. Otherwise, return true.

    Time Complexity (TC): O(N) 
    Where N is the length of the string, as we traverse the string once.

    Space Complexity (SC): O(1) 
    Since the character set is fixed (26 lowercase alphabets), the space 
    used by the frequency array is constant.
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

// --- GFG Class Structure Start ---
class Solution {
public:
    /**
     * Function to check if characters of a string can form a palindrome.
     */
    bool canFormPalindrome(string s) {
        // Since we only care about odd/even counts, we can use an array of size 256 
        // to handle all ASCII characters or an unordered_map.
        unordered_map<char, int> freq;
        
        // Step 1: Count frequencies
        for (char ch : s) {
            freq[ch]++;
        }
        
        // Step 2: Count how many characters appear odd times
        int oddCount = 0;
        for (auto it : freq) {
            if (it.second % 2 != 0) {
                oddCount++;
            }
        }
        
        // Step 3: Rule check
        // For a palindrome, odd frequency characters cannot be more than 1
        return (oddCount <= 1);
    }
};
// --- GFG Class Structure End ---

// Main function for local testing and full code completion
int main() {
    Solution sol;
    
    // Example 1
    string s1 = "baba";
    cout << "Input: " << s1 << " | Output: " << (sol.canFormPalindrome(s1) ? "true" : "false") << endl;

    // Example 2
    string s2 = "geeksogeeks";
    cout << "Input: " << s2 << " | Output: " << (sol.canFormPalindrome(s2) ? "true" : "false") << endl;

    // Example 3
    string s3 = "geeksforgeeks";
    cout << "Input: " << s3 << " | Output: " << (sol.canFormPalindrome(s3) ? "true" : "false") << endl;

    return 0;
}
