/*
=========================================================
Date        : 16-08-2026
Problem Name: Min Product Subset
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Arrays, Greedy, Data Structures

Problem Summary:
Given an array arr[], find the minimum possible product that 
can be obtained by multiplying elements of any non-empty subset.

Key Observation:
An odd count of negative numbers yields the minimum negative product, 
while an even count requires dividing out the maximum negative number.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Generate All Subsets)
---------------------------------------------------------
• Intuition:
  Generate all non-empty subsets (2^N - 1) and find the minimal product.
• Approach:
  Recursively iterate over subset inclusions.
• Why it Works:
  Exhaustively explores the entire search space.
• Time Complexity : O(2^N * N)
• Space Complexity: O(N)

---------------------------------------------------------
APPROACH 2: Greedy Analysis (Most Optimal)
---------------------------------------------------------
• Intuition:
  Compute product greedily based on negative count, zero count, and extreme values.
• Approach:
  1. Count negatives, zeros, and compute non-zero product.
  2. If all elements are 0 -> return 0.
  3. If no negatives: return 0 if zero exists, else min positive.
  4. If even negatives: divide total product by max negative (closest to 0).
• Why it Works:
  Maximizes negative magnitude while strictly keeping the sign negative.
• Time Complexity : O(N)
• Space Complexity: O(1)
*/

/*
---------------------------------------------------------
FINAL APPROACH CHOICE:
---------------------------------------------------------
Approach 2 (Greedy) runs in O(N) time and O(1) auxiliary space,
which is optimal and fits well within the problem constraints.
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int minProd(vector<int>& arr) {
        int n = arr.size();
        if (n == 1) return arr[0];

        int neg_count = 0;
        int zero_count = 0;
        int min_pos = INT_MAX;
        int max_neg = INT_MIN;
        int prod = 1;

        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                zero_count++;
                continue;
            }

            if (arr[i] < 0) {
                neg_count++;
                max_neg = max(max_neg, arr[i]);
            } else {
                min_pos = min(min_pos, arr[i]);
            }

            prod *= arr[i];
        }

        // Case 1: Array contains only zeros
        if (zero_count == n) {
            return 0;
        }

        // Case 2: No negative numbers present
        if (neg_count == 0) {
            if (zero_count > 0) return 0;
            return min_pos;
        }

        // Case 3: Even number of negative numbers
        if (neg_count % 2 == 0) {
            prod /= max_neg;
        }

        return prod;
    }
};
