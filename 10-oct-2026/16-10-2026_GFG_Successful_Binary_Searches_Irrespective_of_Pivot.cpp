/*
=========================================================
Date        : 16-10-2026
Problem Name: Successful Binary Searches Irrespective of Pivot
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Binary Search, Array, Divide and Conquer

Problem Summary:
- Given an array of n distinct integers, we simulate a custom search for a target value.
- At each step, any index in the current [lo, hi] range can be picked as a pivot.
- We need to count how many elements can always be found regardless of which valid pivot is chosen at every step.

Key Observation:
- An element arr[i] is "always found" if and only if no matter how the search range is split or reduced, the target is never bypassed or cut off.
- Specifically, every element to the left of arr[i] must be smaller than arr[i] if it can appear on its left, and every element to the right must be greater, or more precisely, arr[i] acts as a natural partition boundary.
- An element at index i can be successfully found for all pivot sequences if and only if all elements to its left are strictly less than arr[i] (or max of left is < arr[i]) and all elements to its right are strictly greater than arr[i] (or min of right is > arr[i]).
=========================================================
*/

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

/*
=========================================================
APPROACH 1: Prefix Maximum and Suffix Minimum
=========================================================

• Intuition:
  - For a target arr[i] to be found under any arbitrary pivot choice, it must never be eliminated prematurely when a pivot is chosen.
  - If there is any element to the left of i that is greater than arr[i], choosing that element as a pivot would push the search range to the left, losing i forever.
  - Similarly, if any element to the right of i is smaller than arr[i], choosing it as a pivot would push the search range to the right, losing i forever.

• Approach:
  - Precompute the prefix maximum array where prefMax[i] stores the maximum element from index 0 to i.
  - Precompute the suffix minimum array where suffMin[i] stores the minimum element from index i to n-1.
  - An element arr[i] is valid if for all j < i, arr[j] < arr[i] (i.e., prefMax[i-1] < arr[i]) and for all k > i, arr[k] > arr[i] (i.e., suffMin[i+1] > arr[i]).
  - Handle boundary conditions for index 0 and index n-1.

• Why it Works:
  - Checking prefix maximums ensures no larger element exists on the left to falsely redirect the search.
  - Checking suffix minimums ensures no smaller element exists on the right to falsely redirect the search.

• Time Complexity (TC): O(n)
• Space Complexity (SC): O(n)
=========================================================
*/

/*
=========================================================
FINAL APPROACH
=========================================================
- We use the Prefix Maximum and Suffix Minimum approach.
- It is optimal because it avoids simulating all exponential pivot permutations, reducing the check for each element to O(1) time after O(n) precomputation.
=========================================================
*/

class Solution {
public:
    int countAlwaysFound(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;
        if (n == 1) return 1;

        vector<int> prefMax(n);
        vector<int> suffMin(n);

        prefMax[0] = arr[0];
        for (int i = 1; i < n; ++i) {
            prefMax[i] = max(prefMax[i - 1], arr[i]);
        }

        suffMin[n - 1] = arr[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            suffMin[i] = min(suffMin[i + 1], arr[i]);
        }

        int count = 0;
        for (int i = 0; i < n; ++i) {
            bool leftValid = (i == 0) || (prefMax[i - 1] < arr[i]);
            bool rightValid = (i == n - 1) || (suffMin[i + 1] > arr[i]);

            if (leftValid && rightValid) {
                count++;
            }
        }

        return count;
    }
};
