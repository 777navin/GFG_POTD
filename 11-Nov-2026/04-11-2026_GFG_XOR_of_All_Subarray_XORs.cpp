/*
=========================================================
Date        : 04-11-2026
Problem Name: XOR of All Subarray XORs
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Bit Manipulation, Array, Combinatorics

Problem Summary:
Given an integer array arr[], we need to find the XOR of the XOR values of all possible non-empty subarrays.
The length of the array can be up to 10^5, requiring an efficient O(N) or O(N log MAX_VAL) solution.

Key Observation:
Each element arr[i] appears in multiple subarrays. Specifically, arr[i] is included in subarrays starting at index s (0 <= s <= i) and ending at e (i <= e < n).
The number of subarrays containing arr[i] is (i + 1) * (n - i). If this product is odd, arr[i] contributes to the final XOR sum; if even, it cancels out.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int subarrayXor(vector<int>& arr) {
        int n = arr.size();
        
        /*
        Approach: Frequency Count & Bit Manipulation (Optimized)
        
        • Intuition:
          Instead of generating all O(N^2) subarrays (which is too slow for N = 10^5), we analyze how many times each element contributes to the total XOR sum.
          
        • Approach:
          1. For an array of size n, an element at index i (0-indexed) is part of all subarrays starting from index s (0 <= s <= i) and ending at e (i <= e < n).
          2. The total number of such subarrays is (i + 1) * (n - i).
          3. If the frequency (i + 1) * (n - i) is odd, the element arr[i] contributes to the final XOR result (since x ^ x = 0). If even, its contribution is 0.
          
        • Why it Works:
          XOR operation is associative and commutative. By counting the exact contribution frequency of each element in O(1) per element, we can compute the answer in a single pass without explicitly generating subarrays.
          
        • Time Complexity (TC):
          O(N), where N is the size of the array. We iterate through the array once.
          
        • Space Complexity (SC):
          O(1), as we only use a few variables for computation.
        */
        
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            // Number of subarrays containing arr[i] is (i + 1) * (n - i)
            long long freq = 1LL * (i + 1) * (n - i);
            if (freq % 2 != 0) {
                ans ^= arr[i];
            }
        }
        
        return ans;
    }
};

/*
=========================================================
FINAL APPROACH & RATIONALE
=========================================================
• Why this approach is chosen:
  The brute force approach of generating all subarrays takes O(N^2) or O(N^3) time, which will time out given N <= 10^5.
  
• Why it is better than previous ones:
  By leveraging combinatorics to count the exact frequency of each element's appearance in subarrays, we reduce the time complexity to linear O(N) with O(1) auxiliary space, making it optimal and fully compliant with constraints.
=========================================================
*/
