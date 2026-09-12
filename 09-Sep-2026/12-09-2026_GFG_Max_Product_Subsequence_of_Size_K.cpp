/*
=========================================================
Date        : 12-09-2026
Problem Name: Max Product Subsequence of Size K
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Arrays, Greedy, Sorting, Two Pointers

Problem Summary:
Given an array arr[] of integers and an integer k, find a subsequence of size k
whose product is maximum among all possible subsequences of size k.
Return the maximum product that can be obtained.

Key Observation:
Sorting the array allows choosing pairs of negative numbers (which produce positive
products) or the largest positive numbers from opposite ends using a two-pointer approach.
Special edge cases occur when k is odd and all numbers are negative, or when the optimal product is negative/zero.
=========================================================
*/

/*
APPROACH 1: Brute Force (Recursion / Backtracking)
- Intuition:
  Generate all possible combinations of subsequences of length k, compute their products,
  and track the maximum product encountered.
- Approach:
  Use recursive backtracking to pick/not-pick elements up to size k, calculating the product
  at base cases.
- Why it Works:
  Exhaustively explores the entire search space, guaranteeing the global maximum.
- Time Complexity (TC): O(C(N, K)) where N is the size of arr[].
- Space Complexity (SC): O(K) recursion stack space.

APPROACH 2: Sorting + Greedy (Two Pointers) [Most Optimal]
- Intuition:
  A maximum positive product can be formed either by multiplying two large positive numbers
  or two large negative numbers (whose product turns positive).
- Approach:
  1. Sort arr[] in non-decreasing order.
  2. If arr[N - 1] <= 0 and k is odd: the maximum product must be negative (or zero);
     greedily pick the k largest elements from the right end.
  3. Otherwise, use two pointers (left at 0, right at N - 1):
     - If k is odd, take the largest positive element arr[right--] to make k even.
     - While k >= 2, compare the product of the two leftmost elements (arr[left] * arr[left + 1])
       with the product of the two rightmost elements (arr[right] * arr[right - 1]).
     - Greedily pick the pair with the greater product and decrement k by 2.
- Why it Works:
  Pairs of negative numbers become positive, and comparing pairs at both ends always
  locally and globally maximizes the contribution towards a positive product.
- Time Complexity (TC): O(N log N) dominated by sorting.
- Space Complexity (SC): O(1) auxiliary space.
*/

/*
FINAL APPROACH:
We choose Approach 2 (Sorting + Greedy Two Pointers).
It reduces the exponential time complexity O(C(N, K)) down to O(N log N), making it highly
optimal and easily fitting well within standard execution time limits.
*/

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& arr, int k) {
        int n = arr.size();
        sort(arr.begin(), arr.end());

        int left = 0;
        int right = n - 1;
        long long max_prod = 1;

        // Case 1: If the largest element is <= 0 and k is odd,
        // the product is guaranteed to be non-positive.
        // To maximize it, pick the k elements with the smallest absolute values (from the right).
        if (arr[right] <= 0 && (k % 2 != 0)) {
            for (int i = n - 1; i >= n - k; --i) {
                max_prod *= arr[i];
            }
            return (int)max_prod;
        }

        // Case 2: If k is odd, pick the largest available element first to make k even
        if (k % 2 != 0) {
            max_prod *= arr[right];
            right--;
            k--;
        }

        // Case 3: Greedily pick pairs from left or right
        while (k > 0) {
            long long left_pair = 1LL * arr[left] * arr[left + 1];
            long long right_pair = 1LL * arr[right] * arr[right - 1];

            if (left_pair > right_pair) {
                max_prod *= left_pair;
                left += 2;
            } else {
                max_prod *= right_pair;
                right -= 2;
            }
            k -= 2;
        }

        return (int)max_prod;
    }
};
