// File Name: 03-06-2026_GFG_Subarray_Frequency_Count_Queries.cpp

/*
Date: 03-06-2026
Problem Name: Subarray Frequency Count Queries
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Array, Binary Search, Hash Map, Data Structures

Problem Summary:
Given an array `arr[]` of `n` integers and a 2D array `queries[][]` where each query contains `[l, r, x]`. 
For each query, find the frequency of the element `x` in the subarray from index `l` to `r` (both inclusive).
Return a vector of results for each query.

Methods to Solve:
1. Brute Force
2. Optimal Approach (Hash Map / Array of Vectors + Binary Search)

-------------------------------------------------------------------
1. Brute Force
-------------------------------------------------------------------
- Intuition:
  The most straightforward way is to traverse the array from index `l` to `r` for every single query and count the occurrences of `x`.

- Approach:
  1. Iterate through each query in `queries`.
  2. For each query `[l, r, x]`, run a loop from index `l` to `r` on the array.
  3. Increment a counter every time `arr[i] == x`.
  4. Store the count in the result array.

- Dry Run (small example):
  arr = [1, 2, 1, 3], query = [0, 2, 1]
  Loop from index 0 to 2: arr[0]=1 (count=1), arr[1]=2, arr[2]=1 (count=2). Result = 2.

- Time Complexity: O(q * n), where q is the number of queries and n is the size of the array. This will give a Time Limit Exceeded (TLE) for constraints up to 10^5.
- Space Complexity: O(1) auxiliary space (excluding the output array).

- Why better than previous method: N/A (Baseline)
- When to use: When the array size and number of queries are very small (e.g., <= 1000).

-------------------------------------------------------------------
2. Optimal Approach (Hash Map + Binary Search)
-------------------------------------------------------------------
- Intuition:
  Since the array doesn't change (static array) and we have multiple queries, we can preprocess the array. If we store all the indices where a particular element appears, those indices will naturally be in strictly increasing sorted order. We can then use binary search (`lower_bound` and `upper_bound`) to quickly count how many indices fall within the range `[l, r]`.

- Approach:
  1. Create an `unordered_map<int, vector<int>>` named `pos` to store the 0-based indices of each element.
  2. Traverse the array once and populate this map: `pos[arr[i]].push_back(i)`.
  3. For each query `[l, r, x]`, check if `x` exists in our map.
  4. If it does, fetch its vector of indices.
  5. Use `lower_bound` to find the first index >= `l` (start iterator).
  6. Use `upper_bound` to find the first index > `r` (end iterator).
  7. The frequency in the range `[l, r]` is the difference between these two iterators.
  8. Store the frequency in the result vector.

- Dry Run (small example):
  arr = [1, 2, 1, 3, 1, 2, 3]
  Map precomputation:
  1 -> [0, 2, 4]
  2 -> [1, 5]
  3 -> [3, 6]
  
  Query: [0, 4, 1] (l=0, r=4, x=1)
  Vector for 1 is `v = [0, 2, 4]`.
  lower_bound(0) points to index 0 (value 0).
  upper_bound(4) points to index 3 (out of bounds).
  Result = 3 - 0 = 3.

- Time Complexity: O(n + q * log(n))
  Preprocessing takes O(n). Each query takes O(log k) where k is the frequency of `x` (k <= n).
- Space Complexity: O(n) to store the indices in the hash map.

- Why better than previous method: It dramatically reduces the query time from O(n) to O(log n), passing the 10^5 constraints easily.
- When to use: When dealing with multiple range frequency queries on an immutable array.

Comparison Table:
Method         | TC               | SC   | Best Use Case
-------------------------------------------------------------------
Brute Force    | O(q * n)         | O(1) | Small arrays/queries
Optimal        | O(n + q*log n)   | O(n) | Large arrays/queries (CP standard)

Final Recommended Solution: Optimal Approach (Hash Map + Binary Search)
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> freqInRange(vector<int>& arr, vector<vector<int>>& queries) {
        // Map to store the indices of each element.
        // Elements are naturally sorted as we iterate from left to right.
        unordered_map<int, vector<int>> pos;
        int n = arr.size();
        
        for (int i = 0; i < n; ++i) {
            pos[arr[i]].push_back(i);
        }
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        // Process each query
        for (const auto& q : queries) {
            int l = q[0];
            int r = q[1];
            int x = q[2];
            
            // If the element 'x' doesn't exist in the array at all
            if (pos.find(x) == pos.end()) {
                ans.push_back(0);
                continue;
            }
            
            const vector<int>& indices = pos[x];
            
            // Binary search to find the bounds
            // lower_bound gives the first index >= l
            auto it_start = lower_bound(indices.begin(), indices.end(), l);
            // upper_bound gives the first index > r
            auto it_end = upper_bound(indices.begin(), indices.end(), r);
            
            // The number of valid indices in the range is the difference between iterators
            ans.push_back(distance(it_start, it_end));
        }
        
        return ans;
    }
};

// Driver Code for local testing (GFG compatible)
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    Solution sol;
    
    // Test Case 1
    vector<int> arr1 = {1, 2, 1, 3, 1, 2, 3};
    vector<vector<int>> queries1 = {{0, 4, 1}, {2, 5, 2}, {1, 6, 3}, {0, 6, 5}};
    vector<int> res1 = sol.freqInRange(arr1, queries1);
    
    cout << "Test Case 1 Output: ";
    for (int count : res1) {
        cout << count << " "; // Expected: 3 1 2 0
    }
    cout << "\n";
    
    // Test Case 2
    vector<int> arr2 = {11, 21, 51, 101, 11, 51};
    vector<vector<int>> queries2 = {{0, 4, 11}, {2, 5, 51}};
    vector<int> res2 = sol.freqInRange(arr2, queries2);
    
    cout << "Test Case 2 Output: ";
    for (int count : res2) {
        cout << count << " "; // Expected: 2 2
    }
    cout << "\n";

    return 0;
}
