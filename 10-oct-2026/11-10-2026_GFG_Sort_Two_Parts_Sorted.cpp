/*
=========================================================
Date        : 11-10-2026
Problem Name: Sort Two Parts Sorted
Platform    : GeeksforGeeks (GFG)
Difficulty  : Easy
Tags        : Two Pointers, Sorting, Arrays

Problem Summary:
Given an array where two contiguous parts are individually sorted around an unknown break point, merge them into a single sorted array in-place or using standard merging techniques.

Key Observation:
Since the array consists of two individually sorted segments, we can find where the break point occurs, or alternatively, use standard sorting / two-pointer merging to combine them efficiently.
=========================================================
*/

#include <vector>
#include <algorithm>

class Solution {
public:
    /*
    1. Optimized (Two-Pointer Merge / Standard Sorting)
    
    • Intuition:
      We can locate the point where the sorted order breaks, and then merge the two sorted halves similar to the merge step in Merge Sort.
    • Approach:
      Find the break index where arr[i] > arr[i+1]. If no such break exists, the array is already sorted. Otherwise, use an auxiliary array or standard merge logic. Alternatively, built-in sort can be used if constraints allow, but a linear scan to find the break and merge is $O(N)$.
    • Why it Works:
      Leverages the property that both halves are pre-sorted, reducing the merge complexity to linear time.
    • Time Complexity (TC):
      O(N) where N is the size of the array.
    • Space Complexity (SC):
      O(N) to store temporary elements for merging, or O(1) auxiliary space depending on implementation.
    */
    void mergeTwoParts(std::vector<int>& arr) {
        int n = arr.size();
        int break_idx = -1;
        
        // Find the break point
        for (int i = 0; i < n - 1; ++i) {
            if (arr[i] > arr[i + 1]) {
                break_idx = i;
                break;
            }
        }
        
        // If already sorted
        if (break_idx == -1) return;
        
        // Using standard sorting for simplicity and efficiency within competitive programming limits,
        // or a two-pointer merge using a temporary vector.
        std::vector<int> temp(arr.begin(), arr.end());
        int i = 0, j = break_idx + 1, k = 0;
        
        while (i <= break_idx && j < n) {
            if (temp[i] <= temp[j]) {
                arr[k++] = temp[i++];
            } else {
                arr[k++] = temp[j++];
            }
        }
        
        while (i <= break_idx) {
            arr[k++] = temp[i++];
        }
        
        while (j < n) {
            arr[k++] = temp[j++];
        }
    }
};
