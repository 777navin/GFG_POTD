/*
=========================================================
Date        : 25-10-2026
Problem Name: Sum of Beauty of All Substrings
Platform: GeeksforGeeks
Difficulty: Easy
Tags: String, Hash Table, Frequency Counting

Problem Summary:
Given a string s, return the sum of the beauty of all its substrings.
The beauty of a substring is defined as the difference between the 
maximum and minimum frequencies of characters present in that substring.

Key Observation:
Since the length of the string s is up to 500, an O(N^2) solution 
is well within the time limit. We can iterate over all possible starting 
points of substrings and expand the ending point.
=========================================================
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Brute Force / Optimized Iteration
• Intuition: Generate all possible substrings using nested loops and calculate the maximum and minimum character frequencies for each substring.
• Approach: Maintain an outer loop for the start index `i` and an inner loop for the end index `j`. Keep a frequency array of size 26 for characters in the current substring.
• Why it Works: With $N \le 500$, $N^2$ is $2.5 \times 10^5$ operations, which easily runs within the time limit. Updating frequencies incrementally avoids redundant recounting.
• Time Complexity (TC): O(N^2 * 26) which simplifies to O(N^2)
• Space Complexity (SC): O(26) = O(1) auxiliary space for the frequency array.

=========================================================
FINAL APPROACH
=========================================================
• Why this approach is chosen: It efficiently visits every substring in O(N^2) time while maintaining character counts on the fly.
• Why it is better than previous ones: Recomputing frequencies from scratch for every substring would take O(N^3), whereas updating incrementally reduces it to O(N^2).
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Solution {
public:
    int beautySum(std::string &s) {
        int totalBeauty = 0;
        int n = s.length();
        
        // Iterate over all possible starting positions of substrings
        for (int i = 0; i < n; ++i) {
            std::vector<int> freq(26, 0);
            
            // Expand the substring ending position
            for (int j = i; j < n; ++j) {
                freq[s[j] - 'a']++;
                
                int maxFreq = 0;
                int minFreq = INT_MAX;
                
                // Find max and min frequencies among characters present in the substring
                for (int k = 0; k < 26; ++k) {
                    if (freq[k] > 0) {
                        maxFreq = std::max(maxFreq, freq[k]);
                        minFreq = std::min(minFreq, freq[k]);
                    }
                }
                
                // Add the beauty of the current substring
                totalBeauty += (maxFreq - minFreq);
            }
        }
        
        return totalBeauty;
    }
};
