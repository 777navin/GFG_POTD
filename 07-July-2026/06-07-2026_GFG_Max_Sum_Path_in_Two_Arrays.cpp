/*
=========================================================
Date        : 06-07-2026
Problem Name: Max Sum Path in Two Arrays
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Arrays, Greedy, Two Pointers

Problem Summary:
- Given two sorted arrays, find the maximum path sum from beginning to end.
- You can switch between arrays only at common elements.
- Count common elements only once when switching.

Key Observation:
- Since arrays are sorted, we can use a two-pointer approach to traverse both arrays simultaneously and accumulate sums between intersection points.
=========================================================
*/

#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Solution {
public:
    /*
    1. Optimized Approach (Two Pointers)
    
    * Intuition:
      - Since the arrays are sorted, we can maintain two running sums.
      - We move pointers based on which element is smaller to find common elements.
    
    * Approach:
      - Use two pointers, i and j, initialized to 0. 
      - Use two running sums (sum1, sum2) to store path values for array a and b.
      - If a[i] < b[j], add a[i] to sum1 and increment i.
      - If b[j] < a[i], add b[j] to sum2 and increment j.
      - If a[i] == b[j], add the max of (sum1, sum2) + a[i] to the total, reset sum1/sum2 to 0, and increment both.
      - After loops, add remaining elements to the total.
    
    * Why it Works:
      - The greedy choice ensures we always pick the maximum segment before the next intersection.
    
    * Time Complexity (TC): O(N + M), where N and M are lengths of the arrays.
    * Space Complexity (SC): O(1).
    */

    int maxPathSum(vector<int>& a, vector<int>& b) {
        int i = 0, j = 0;
        int sum1 = 0, sum2 = 0;
        int totalSum = 0;
        int n = a.size(), m = b.size();

        while (i < n && j < m) {
            if (a[i] < b[j]) {
                sum1 += a[i++];
            } else if (b[j] < a[i]) {
                sum2 += b[j++];
            } else {
                // Common element found
                totalSum += max(sum1, sum2) + a[i];
                sum1 = 0;
                sum2 = 0;
                i++;
                j++;
            }
        }

        // Add remaining elements
        while (i < n) sum1 += a[i++];
        while (j < m) sum2 += b[j++];

        totalSum += max(sum1, sum2);

        return totalSum;
    }
};

/*
Final Approach Choice:
- The Two-Pointer approach is chosen because it operates in linear time O(N+M) and constant space O(1).
- It is the most optimal way to handle sorted arrays as it avoids any overhead of auxiliary data structures like maps or sets.
*/
