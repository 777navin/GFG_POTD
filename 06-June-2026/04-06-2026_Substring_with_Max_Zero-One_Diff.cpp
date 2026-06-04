/*
Date: 04-06-2026
Problem Name: Substring with Max Zero-One Diff
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Array, Kadane's Algorithm, Greedy

Problem Summary
Given a binary string 's' consisting of 0s and 1s, find the maximum difference 
of the number of 0s and the number of 1s (count(0s) - count(1s)) in any substring 
of the string. If the string contains only 1s, the result should be -1.

Methods to Solve:
1. Optimal Approach (Modified Kadane's Algorithm)

For Optimal Approach:
- Intuition: This is a variation of the Maximum Subarray Sum problem. 
  If we map '0' to +1 and '1' to -1, finding the maximum difference in a 
  substring is equivalent to finding the Maximum Subarray Sum.
- Approach: Iterate through the string. Maintain a running current_sum and 
  max_sum. If the current_sum becomes negative, reset it to 0.
- Dry Run: s = "11000010001"
  - Map: -1, -1, +1, +1, +1, +1, -1, +1, +1, +1, -1
  - Kadane's logic will identify the range with the max sum of these values.
- Time Complexity: O(n), where n is the length of the string.
- Space Complexity: O(1).
- Why better: It processes the string in a single pass without extra memory.

Comparison Table:
Method | TC | SC | Best Use Case
-------|----|----|--------------
Kadane | O(n)| O(1)| Optimal for finding max subarray difference

Final Recommended Solution: Kadane's Algorithm
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * @brief Calculates the maximum difference of 0s and 1s in a substring.
     * Maps '0' to +1 and '1' to -1, then applies Kadane's.
     * * @param s The input binary string.
     * @return int The maximum difference found, or -1 if only 1s exist.
     */
    int maxSubstring(string &s) {
        int max_so_far = -1;
        int current_max = 0;
        bool has_zero = false;

        for (char c : s) {
            int val = (c == '0') ? 1 : -1;
            
            if (c == '0') has_zero = true;

            current_max += val;

            if (current_max > max_so_far) {
                max_so_far = current_max;
            }

            if (current_max < 0) {
                current_max = 0;
            }
        }

        // If no zeros were present, the max difference is defined as -1
        return has_zero ? max_so_far : -1;
    }
};

// Driver code to demonstrate functionality
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    string s1 = "11000010001";
    string s2 = "111111";

    cout << "Max diff for " << s1 << ": " << sol.maxSubstring(s1) << endl;
    cout << "Max diff for " << s2 << ": " << sol.maxSubstring(s2) << endl;

    return 0;
}
