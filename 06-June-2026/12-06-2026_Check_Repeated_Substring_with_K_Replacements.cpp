/*
Date: 12-06-2026
Problem Name: Check Repeated Substring with K Replacements
Platform: GeeksforGeeks
Difficulty: Medium
Tags: String, Hashing, Frequency Mapping

Problem Summary:
Given a string s and an integer k, determine if the string can be converted into a 
repetition of a substring of length k by replacing exactly one substring of length k 
starting at index i where i % k == 0.

Methods to Solve:
1. Frequency Counting Approach
   - Intuition: If the string is a repetition of a length-k substring, then all 
     other blocks of length k must be identical. We can count the frequency of each 
     k-length block. If there are at most two distinct types of blocks, we can 
     potentially replace one to make all blocks identical.
   - Approach:
     a. If s.size() % k != 0, it's impossible to form a repetition.
     b. Split the string into blocks of size k.
     c. Use a map to store the frequency of each unique block.
     d. If the number of unique blocks is 1, it's already a repetition (return true).
     e. If the number of unique blocks is 2:
        - Check if one of the blocks appears exactly once. If yes, we can replace 
          that single block with the other type to make all blocks identical.
     f. Otherwise, return false.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Frequency Map | O(N) | O(N) | String processing where N is string length

Final Recommended Solution: Frequency Map
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool kSubstr(string &s, int k) {
        int n = s.size();
        
        // A string must be divisible by k to be a repetition of a k-length substring
        if (n % k != 0) {
            return false;
        }
        
        // Count frequencies of all k-length blocks
        unordered_map<string, int> counts;
        for (int i = 0; i < n; i += k) {
            counts[s.substr(i, k)]++;
        }
        
        // If all blocks are already the same
        if (counts.size() == 1) {
            return true;
        }
        
        // If there are exactly two different types of blocks
        if (counts.size() == 2) {
            for (auto const& [block, count] : counts) {
                // If one type of block appears exactly once, 
                // we can replace it to match the other blocks.
                if (count == 1) {
                    return true;
                }
            }
        }
        
        return false;
    }
};

// Driver Code
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Solution sol;
    string s = "abcbedabcabc";
    int k = 3;
    
    if (sol.kSubstr(s, k)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    
    return 0;
}
