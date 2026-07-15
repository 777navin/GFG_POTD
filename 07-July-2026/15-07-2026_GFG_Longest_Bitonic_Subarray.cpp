/*
=========================================================
Date        : 15-07-2026
Problem Name: Longest Bitonic Subarray
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Array, Dynamic Programming

Problem Summary:
Find the maximum length of a contiguous subarray that first monotonically 
increases and then monotonically decreases.

Key Observation:
Any element can be considered the "peak" of a bitonic subarray. By finding 
the longest non-decreasing subarray ending at each index and the longest 
non-increasing subarray starting at each index, we can determine the 
maximum bitonic length around any peak.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
1. Brute Force
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Check every possible subarray to see if it forms a valid bitonic sequence, 
  and keep track of the maximum length found.
• Approach:
  Use nested loops to generate all subarrays. For each subarray, use another 
  loop to verify if it strictly increases then decreases.
• Why it Works:
  It exhaustively checks all possibilities, ensuring the longest valid bitonic 
  subarray is found by definition.
• Time Complexity (TC): O(N^3)
• Space Complexity (SC): O(1)

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
2. Most Optimal
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  Instead of re-checking lengths for every subarray, we can precompute the 
  increasing and decreasing lengths around every element.
• Approach:
  Create an 'inc' array for the longest non-decreasing subarray ending at 'i'. 
  Create a 'dec' array for the longest non-increasing subarray starting at 'i'.
• Why it Works:
  Combining 'inc[i]' and 'dec[i]' at any peak index 'i' gives the length of the 
  bitonic subarray peaking at 'i' (subtract 1 to avoid double counting 'i').
• Time Complexity (TC): O(N)
• Space Complexity (SC): O(N)
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
FINAL APPROACH
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
The DP Prefix & Suffix Arrays (Most Optimal) approach is chosen because it 
optimizes the time complexity to O(N). This fits the large constraint of 
N = 10^6 perfectly, avoiding the Time Limit Exceeded (TLE) of the brute force.
*/

class Solution {
public:
    int bitonic(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;

        vector<int> inc(n, 1);
        vector<int> dec(n, 1);

        // Calculate longest non-decreasing sequence ending at each index
        for (int i = 1; i < n; i++) {
            if (arr[i] >= arr[i - 1]) {
                inc[i] = inc[i - 1] + 1;
            }
        }

        // Calculate longest non-increasing sequence starting at each index
        for (int i = n - 2; i >= 0; i--) {
            if (arr[i] >= arr[i + 1]) {
                dec[i] = dec[i + 1] + 1;
            }
        }

        // Find the maximum length bitonic subarray
        int max_len = 0;
        for (int i = 0; i < n; i++) {
            max_len = max(max_len, inc[i] + dec[i] - 1);
        }

        return max_len;
    }
};
