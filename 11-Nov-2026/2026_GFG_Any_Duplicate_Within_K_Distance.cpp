
/*
=========================================================
Date        : 11-11-2026
Problem Name: Any Duplicate Within K Distance
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Array, Hashing, Sliding Window

Problem Summary:
Check whether two distinct indices contain the same
element and their absolute difference is at most k.

Key Observation:
Only the previous k elements need to be checked.
An unordered_set provides O(1) average lookup.
=========================================================

APPROACH 1: BRUTE FORCE

- Intuition: Compare every pair of elements.
- Approach: Check whether arr[i] == arr[j] and j-i <= k.
- Why it Works: It examines every possible valid pair.
- TC: O(n * k)
- SC: O(1)

APPROACH 2: HASH MAP

- Intuition: Remember the last occurrence of each element.
- Approach: Store each element's most recent index.
- Why it Works: The latest occurrence gives the minimum
  distance from the current index.
- TC: O(n) average
- SC: O(n)

APPROACH 3: SLIDING WINDOW + HASH SET (OPTIMAL)

- Intuition: Only the previous k elements matter.
- Approach:
  1. Check whether the current element exists in the set.
  2. If yes, return true.
  3. Otherwise, insert the current element.
  4. Remove arr[i-k] when the window exceeds k elements.
- Why it Works: The set always contains exactly the
  relevant previous k elements.

- TC: O(n) average
- SC: O(min(n, k))

FINAL APPROACH:
Sliding Window + Unordered Set is chosen because it
checks duplicates in O(1) average time and maintains
only the necessary k previous elements.
*/

// User function Template for C++

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    bool checkWithinK(vector<int>& arr, int k) {

        unordered_set<int> window;

        for (int i = 0; i < arr.size(); i++) {

            // Check whether duplicate exists in the window
            if (window.count(arr[i])) {
                return true;
            }

            // Insert current element
            window.insert(arr[i]);

            // Maintain at most k previous elements
            if (i >= k) {
                window.erase(arr[i - k]);
            }
        }

        return false;
    }
};
