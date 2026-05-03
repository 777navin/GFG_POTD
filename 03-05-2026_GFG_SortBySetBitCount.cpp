/*
Date: 03-05-2026
Problem Name: Sort by Set Bit Count
Platform: GeeksforGeeks (GFG)
Difficulty: Easy
Tags: Bit Manipulation, Sorting, Stable Sort

-------------------------------------------------
Problem Summary:
Given an array arr[] of integers, sort the array 
(in descending order) according to the count of 
set bits in the binary representation of array 
elements. If two numbers have the same number of 
set bits, maintain their relative order (stable sort).

-------------------------------------------------
Methods to Solve:

1. Brute Force
2. Custom Comparator with Stable Sort
3. Counting Sort by Set Bits (Optimal)

-------------------------------------------------
Method 1: Brute Force
- Intuition: Count set bits for each element, then 
  repeatedly pick the maximum set-bit element.
- Approach: O(n^2) selection-like sorting.
- Dry Run: arr = [5,2,3]
  setbits = [2,1,2] → pick 5, then 3, then 2.
- TC: O(n^2)
- SC: O(1)
- Why better: Simple but inefficient.
- When to use: Only for very small arrays.

-------------------------------------------------
Method 2: Custom Comparator with Stable Sort
- Intuition: Use built-in stable_sort with comparator 
  based on set bit count.
- Approach: Count set bits using __builtin_popcount 
  and sort descending.
- Dry Run: arr = [5,2,3,9]
  setbits = [2,1,2,2] → stable_sort keeps [5,3,9] order.
- TC: O(n log n)
- SC: O(1)
- Why better: Efficient and concise.
- When to use: General case, recommended.

-------------------------------------------------
Method 3: Counting Sort by Set Bits (Optimal)
- Intuition: Since max bits ≤ 20 (for 10^6), bucket 
  elements by set bit count.
- Approach: Create buckets [0..20], push elements, 
  then concatenate in descending order.
- Dry Run: arr = [5,2,3]
  bucket[2] = [5,3], bucket[1] = [2] → result [5,3,2].
- TC: O(n)
- SC: O(n)
- Why better: Linear time, stable by construction.
- When to use: Large arrays, performance critical.

-------------------------------------------------
Comparison Table:
Method        | TC       | SC   | Best Use Case
-------------------------------------------------
Brute Force   | O(n^2)   | O(1) | Small arrays
Comparator    | O(n log n)| O(1)| General case
Counting Sort | O(n)     | O(n) | Large arrays

-------------------------------------------------
Final Recommended Solution:
Method 2 (Comparator + stable_sort) for simplicity 
and reliability. Method 3 for optimal performance 
on very large arrays.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Method 2: Comparator with stable_sort
    vector<int> sortBySetBitCount(vector<int>& arr) {
        stable_sort(arr.begin(), arr.end(), [](int a, int b) {
            int ca = __builtin_popcount(a);
            int cb = __builtin_popcount(b);
            return ca > cb; // descending order
        });
        return arr;
    }

    // Method 3: Counting Sort by Set Bits
    vector<int> sortBySetBitCountCounting(vector<int>& arr) {
        const int MAX_BITS = 20; // since arr[i] ≤ 10^6
        vector<vector<int>> buckets(MAX_BITS+1);
        for(int num : arr) {
            int bits = __builtin_popcount(num);
            buckets[bits].push_back(num);
        }
        vector<int> result;
        for(int b = MAX_BITS; b >= 0; b--) {
            for(int num : buckets[b]) {
                result.push_back(num);
            }
        }
        return result;
    }
};

// Driver Code (for GFG practice environment)
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> arr(n);
    for(int i=0; i<n; i++) cin >> arr[i];

    Solution sol;
    vector<int> ans = sol.sortBySetBitCount(arr);

    for(int x : ans) cout << x << " ";
    cout << "\n";
    return 0;
}
