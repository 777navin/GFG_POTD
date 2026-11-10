/*
=========================================================
Date        : 10-11-2026
Problem Name: At Least K Occurrences
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Hashing, Arrays, Frequency Count

Problem Summary:
- Given an array arr[] and an integer k, find the first element that occurs at least k times.
- If multiple elements satisfy this, return the one whose k-th occurrence appears earliest.
- Return -1 if no element meets the condition.

Key Observation:
- We need to track both the frequency of each element and the index of its k-th occurrence to determine which element qualifies first.
=========================================================
*/

/*
1. Brute Force
• Intuition: Iterate through every element and count its frequency across the entire array, keeping track of the first one to reach count k.
• Approach: Use nested loops or an outer loop with frequency checks up to each index.
• Why it Works: Directly simulates the problem statement but is inefficient for large constraints.
• Time Complexity (TC): O(N^2)
• Space Complexity (SC): O(1)

2. Optimized (Hash Map)
• Intuition: Use a hash map to maintain the frequency of elements as we traverse the array from left to right.
• Approach: Iterate through the array, increment the frequency count of each element. The moment any element's frequency reaches k, we can record or check its validity. Since we want the element whose k-th occurrence appears earliest, we can either store the first time an element hits count k or check upon reaching frequency k during a single forward pass.
• Why it Works: A single traversal allows us to encounter the k-th occurrence of elements in the exact order they appear in the array.
• Time Complexity (TC): O(N)
• Space Complexity (SC): O(N)
*/

/*
Final Approach Chosen:
- We use a Hash Map to count the frequencies of elements dynamically during a single left-to-right pass.
- This is optimal because it avoids redundant nested scans, reducing time complexity from quadratic to linear while using efficient hashing.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int firstElementKTime(vector<int>& arr, int k) {
        unordered_map<int, int> freq;
        for (int i = 0; i < arr.size(); i++) {
            freq[arr[i]]++;
            if (freq[arr[i]] == k) {
                return arr[i];
            }
        }
        return -1;
    }
};
