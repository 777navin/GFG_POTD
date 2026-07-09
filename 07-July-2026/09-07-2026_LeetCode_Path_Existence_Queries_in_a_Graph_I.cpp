/*
=========================================================
Date        : 09-07-2026
Problem Name: Count Pairs Divisible By K
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Arrays, Hash, Math

Problem Summary:
Given an array and an integer k, count the number of pairs (i, j)
with i < j such that (arr[i] + arr[j]) is divisible by k.

Key Observation:
(a + b) % k == 0 is equivalent to (a % k + b % k) % k == 0.
We can use a frequency array to store remainders of elements modulo k.
=========================================================
*/

/*
1. Optimized Approach (Frequency Array / Hash Map)
   • Intuition:
     For every element, we need a pair such that (arr[i] % k + arr[j] % k) % k == 0.
     If an element has remainder 'rem', we need to find how many previous elements 
     had a remainder of (k - rem) % k.
   • Approach:
     - Maintain a frequency array 'freq' of size k.
     - Iterate through the array, calculate remainder 'rem = arr[i] % k'.
     - Add the count of existing numbers with remainder '(k - rem) % k' to the total.
     - Increment the count of current 'rem' in the frequency array.
   • Why it Works:
     It efficiently counts valid pairs in a single pass without nested loops, 
     utilizing the property of remainders.
   • Time Complexity (TC): O(n)
   • Space Complexity (SC): O(k)
*/

/*
Final Approach:
The frequency array approach is chosen because it achieves linear time complexity.
It is significantly better than the O(n^2) brute force approach, as it avoids
checking every possible pair, making it ideal for the given constraints.
*/

#include <vector>

using namespace std;

class Solution {
public:
    int countKdivPairs(vector<int>& arr, int k) {
        // Frequency array to store count of remainders
        vector<int> freq(k, 0);
        int count = 0;

        for (int x : arr) {
            int rem = x % k;
            
            // Calculate the required remainder to make sum divisible by k
            int target = (k - rem) % k;
            
            // Add the count of numbers already seen with this required remainder
            count += freq[target];
            
            // Update frequency of current remainder
            freq[rem]++;
        }

        return count;
    }
};

// 09-07-2026_GFG_Count_Pairs_Divisible_By_K.cpp
