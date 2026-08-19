/*
=========================================================
Date        : 19-08-2026
Problem Name: Triplets with Sum in Range
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Arrays, Two-Pointers, Sorting

Problem Summary:
Given an array `arr` and a range `[l, r]`, count the total 
number of unique index triplets `(i, j, k)` such that 
their sum satisfies `l <= arr[i] + arr[j] + arr[k] <= r`.

Key Observation:
Counting triplets in `[l, r]` is equivalent to counting 
triplets with sum <= r minus triplets with sum <= (l - 1).
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force
---------------------------------------------------------
• Intuition:
  Iterate through all possible combinations of three elements and verify if their sum lies in [l, r].

• Approach:
  Run three nested loops from i = 0 to n-1, j = i+1 to n-1, and k = j+1 to n-1. Check condition and increment count.

• Why it Works:
  Exhaustively explores all nC3 index triplets.

• Time Complexity (TC) : O(N^3)
• Space Complexity (SC): O(1)
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Sorting + Two Pointers (Most Optimal)
---------------------------------------------------------
• Intuition:
  Transform the range sum query into prefix counting:
  countInRange(l, r) = countTripletsLessOrEqual(r) - countTripletsLessOrEqual(l - 1).

• Approach:
  1. Sort `arr` in ascending order.
  2. For a fixed target `X`, iterate `i` from 0 to `n-3`.
  3. Use two pointers `left = i + 1` and `right = n - 1`.
  4. If `arr[i] + arr[left] + arr[right] <= X`, then all elements between `left` and `right` also form valid sums with `arr[i]` and `arr[left]`. Add `(right - left)` to the count and increment `left`.
  5. Otherwise, decrement `right`.

• Why it Works:
  Monotonicity from sorting allows calculating valid pairs in O(1) per left pointer advance, reducing total time.

• Time Complexity (TC) : O(N^2)
• Space Complexity (SC): O(1) (excluding sorting stack space)
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH CHOICE:
Approach 2 is chosen because N <= 10^3, making an O(N^3) brute 
force solution result in a Time Limit Exceeded (TLE). 
The O(N^2) two-pointer approach executes comfortably within 
the 1-second time limit.
=========================================================
*/

#include <vector>
#include <algorithm>

class Solution {
private:
    // Helper function to count triplets with sum <= target
    int countTripletsLessOrEqual(std::vector<int>& arr, int target) {
        int n = arr.size();
        int count = 0;

        for (int i = 0; i < n - 2; ++i) {
            int left = i + 1;
            int right = n - 1;

            while (left < right) {
                int currentSum = arr[i] + arr[left] + arr[right];
                if (currentSum <= target) {
                    count += (right - left);
                    left++;
                } else {
                    right--;
                }
            }
        }
        return count;
    }

public:
    int countTriplets(std::vector<int>& arr, int l, int r) {
        std::sort(arr.begin(), arr.end());
        return countTripletsLessOrEqual(arr, r) - countTripletsLessOrEqual(arr, l - 1);
    }
};
