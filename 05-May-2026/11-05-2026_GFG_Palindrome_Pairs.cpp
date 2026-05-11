/*
Date: 11-05-2026
Problem Name: Palindrome Pairs
Platform: GeeksforGeeks (GFG)
Difficulty: Hard
Tags: String, Data Structures, Hash, Trie

Problem Summary:
Given an array of n strings, determine if there exists a pair of indices (i, j) 
such that i != j and the concatenation of arr[i] + arr[j] forms a palindrome.

Methods to Solve:

1. Brute Force:
- Intuition: Check every possible pair (i, j) and verify if the concatenated string is a palindrome.
- Approach: Use nested loops to pick two strings, concatenate them, and use a helper function to check for palindrome property.
- Dry Run: ["abc", "cba"] -> "abccba" (True).
- Time Complexity: O(n^2 * L), where n is the number of strings and L is the max length of a string.
- Space Complexity: O(L) for the concatenated string.
- Why better than previous method: N/A (Baseline).
- When to use: Only when n is very small (e.g., n < 1000).

2. Optimal Approach (Hash Map / String Splitting):
- Intuition: If arr[i] + arr[j] is a palindrome, then one part of the palindrome is formed by one string and the other part is the reverse of the remaining substring.
- Approach: 
    1. Store all strings in a hash map for O(1) lookup.
    2. For each string S:
        a. Split S into two parts, S1 and S2 (S = S1 + S2).
        b. If S1 is a palindrome, then if reverse(S2) exists in the map and is not S itself, then reverse(S2) + S1 + S2 is a palindrome.
        c. If S2 is a palindrome, then if reverse(S1) exists in the map and is not S itself, then S1 + S2 + reverse(S1) is a palindrome.
- Dry Run: arr = ["abc", "xyxcba"]. S = "xyxcba". 
    Split: S1="xyx", S2="cba". S1 is palindrome. reverse(S2)="abc". "abc" exists. (True).
- Time Complexity: O(n * L^2), where L is the maximum length of a string (L=10 in this problem).
- Space Complexity: O(n * L) to store strings in the map.
- Why better than previous method: Reduces quadratic complexity relative to n to linear complexity.
- When to use: When n is large but L is relatively small.

Comparison Table:
Method         | TC          | SC       | Best Use Case
---------------|-------------|----------|---------------------------
Brute Force    | O(n^2 * L)  | O(L)     | Small n
Hash Map Split | O(n * L^2)  | O(n * L) | Large n, Small L (Optimal)

Final Recommended Solution:
The Hash Map approach is optimal given the constraints (n = 2*10^4, L = 10).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Helper function to check if a substring is a palindrome
    bool isPalindrome(const string& s, int low, int high) {
        while (low < high) {
            if (s[low++] != s[high--]) return false;
        }
        return true;
    }

    bool palindromePair(vector<string>& arr) {
        int n = arr.size();
        if (n < 2) return false;

        unordered_map<string, int> mp;
        for (int i = 0; i < n; i++) {
            mp[arr[i]] = i;
        }

        for (int i = 0; i < n; i++) {
            string s = arr[i];
            int len = s.length();

            // Check every possible split point in the string
            for (int j = 0; j <= len; j++) {
                // Split string into s[0...j-1] and s[j...len-1]
                string s1 = s.substr(0, j);
                string s2 = s.substr(j);

                // Case 1: If s1 is a palindrome, check if reverse(s2) exists
                if (isPalindrome(s, 0, j - 1)) {
                    string rev_s2 = s2;
                    reverse(rev_s2.begin(), rev_s2.end());
                    if (mp.count(rev_s2) && mp[rev_s2] != i) {
                        return true;
                    }
                }

                // Case 2: If s2 is a palindrome, check if reverse(s1) exists
                // Note: j < len avoids duplicate checking of the full string if s1 is empty
                if (j < len && isPalindrome(s, j, len - 1)) {
                    string rev_s1 = s1;
                    reverse(rev_s1.begin(), rev_s1.end());
                    if (mp.count(rev_s1) && mp[rev_s1] != i) {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};

//{ Driver Code Starts
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    // Assuming multiple test cases might be handled in local testing
    // or standard competitive environments.
    // For GFG interface, only the class is usually required.
    
    // Example test run:
    Solution sol;
    vector<string> arr1 = {"geekf", "geeks", "or", "keeg", "abc", "bc"};
    cout << (sol.palindromePair(arr1) ? "true" : "false") << endl; // Expected: true

    return 0;
}
// } Driver Code Ends
