/*
=========================================================
Date        : 13-10-2026
Problem Name: Adding Ones
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Array, Prefix Sum

Problem Summary:
Given an array of size n initially set to zero, and an array of updates containing 1-based indices. For each index j in updates, add 1 to all array elements from index j to n. Return the final modified array.

Key Observation:
Instead of updating every element from index j to n for each query (which leads to O(n * k) complexity), we can use frequency counting or prefix sum to accumulate updates efficiently in O(n + k).
=========================================================
*/

#include <vector>

using namespace std;

class Solution {
public:
    /*
    ---------------------------------------------------------
    Approach 1: Optimized Prefix Sum / Frequency Counting
    ---------------------------------------------------------
    • Intuition: Each update adds 1 to all elements starting from index j onwards. This forms a cumulative effect similar to a difference array or frequency count of the update start points.
    • Approach: Maintain a frequency array where the count at index j represents how many times an update started at or before j. Then compute the prefix sum to propagate these increments across the array.
    • Why it Works: Counting the occurrences of each 1-based update index and taking the running prefix sum computes the exact increment for each position in linear time.
    • Time Complexity (TC): O(n + k) where k is the size of the updates array and n is the size of the result array.
    • Space Complexity (SC): O(n) to store the result/frequency array.
    ---------------------------------------------------------
    
    Why this approach is chosen:
    It avoids nested loops by recording update frequencies and calculating cumulative sums in a single pass, making it optimal and well within the time limits for large constraints.
    */
    vector<int> update(int n, vector<int>& updates) {
        vector<int> ans(n, 0);
        
        // Count frequencies of each update index (converting 1-based to 0-based)
        for (int x : updates) {
            ans[x - 1]++;
        }
        
        // Compute running prefix sum to propagate updates to subsequent elements
        int current_sum = 0;
        for (int i = 0; i < n; i++) {
            current_sum += ans[i];
            ans[i] = current_sum;
        }
        
        return ans;
    }
};
