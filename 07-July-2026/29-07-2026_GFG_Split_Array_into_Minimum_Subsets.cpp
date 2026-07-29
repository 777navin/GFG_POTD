/*
=========================================================
Date        : 29-07-2026
Problem Name: Split Array into Minimum Subsets
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Array, Sorting

Problem Summary:
Given an array of distinct positive integers, split it into
the minimum number of subsets where each subset contains only
consecutive numbers. Return the total count of such subsets.

Key Observation:
Sorting the array automatically groups consecutive numbers 
together, making it easy to spot where sequences break.
=========================================================

1. Optimal Approach (Sorting)
- Intuition:
  Since the original order doesn't matter for forming subsets, sorting 
  brings elements that can form consecutive sequences adjacent to each other.
- Approach:
  Sort the given array in ascending order.
  Initialize a subset count to 1 (since at least one element exists).
  Iterate from the second element: if the current element is not exactly 
  one greater than the previous element, increment the subset count.
- Why it Works:
  Consecutive numbers will always have a difference of exactly 1 when sorted. 
  Any difference greater than 1 signifies a break, requiring a new subset.
- Time Complexity (TC): O(N log N) for sorting the array.
- Space Complexity (SC): O(1) auxiliary space (ignoring recursion stack of sorting).

FINAL APPROACH
- Chosen the Optimized Approach (Sorting).
- It is straightforward, robust, and highly efficient without requiring 
  additional memory overhead like HashSets (which would take O(N) space).
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minSubsets(vector<int>& arr) {
        if (arr.empty()) return 0;
        
        // Sort the array to bring potential consecutive elements together
        sort(arr.begin(), arr.end());
        
        int subsets = 1;
        
        // Traverse and count breaks in consecutive sequences
        for (int i = 1; i < arr.size(); i++) {
            if (arr[i] != arr[i - 1] + 1) {
                subsets++;
            }
        }
        
        return subsets;
    }
};

// Driver code included for local GitHub testing
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Test Case 1
    vector<int> arr1 = {100, 56, 5, 6, 102, 58, 101, 57, 7, 103, 59};
    cout << "Output: " << sol.minSubsets(arr1) << "\n"; // Expected: 3

    // Test Case 2
    vector<int> arr2 = {10, 100, 105};
    cout << "Output: " << sol.minSubsets(arr2) << "\n"; // Expected: 3

    return 0;
}
