/*
Date: 02-06-2026
Problem Name: Pairs with certain difference
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Array, Sorting, Greedy, Dynamic Programming

Problem Summary:
Given an array of integers and a number k, find the maximum sum of disjoint pairs 
such that the absolute difference between the elements in each pair is strictly less than k.

Methods to Solve:
1. Dynamic Programming (Tabulation)
2. Greedy Approach (Optimal)

===================================================================

Method 1: Dynamic Programming
- Intuition: After sorting, at each element `i`, we have a choice: either include it in a 
  pair with `i-1` (if the difference condition is met) or skip it.
- Approach: Sort the array in ascending order. Maintain a `dp` array where `dp[i]` stores 
  the maximum pair sum up to index `i`. If `arr[i] - arr[i-1] < k`, 
  `dp[i] = max(dp[i-1], dp[i-2] + arr[i] + arr[i-1])`. Else, `dp[i] = dp[i-1]`.
- Dry Run: arr = [3, 5, 10, 15, 17, 12, 9], k = 4
  Sorted: [3, 5, 9, 10, 12, 15, 17]
  dp[0] = 0
  dp[1] = (5-3 < 4) ? 8 : 0 = 8
  dp[2] = max(8, 0+9+5 (invalid)) = 8
  ...
- Time Complexity: O(N log N) for sorting + O(N) for DP = O(N log N)
- Space Complexity: O(N) for the DP array.
- Why better than previous method: Standard systematic approach for "take or not take" scenarios.
- When to use: When exploring all combinations systematically is required.

===================================================================

Method 2: Greedy Approach (Optimal)
- Intuition: To maximize the total sum, we should greedily form pairs out of the largest 
  available elements. 
- Approach: Sort the array in descending order (or sort ascending and traverse from right to left). 
  Start from the largest element. Check if the difference with the next largest is less than `k`. 
  If it is, they form a valid pair; add their sum and jump 2 steps. If not, jump 1 step to 
  check the next possibility.
- Dry Run: arr = [3, 5, 10, 15, 17, 12, 9], k = 4
  Sorted Ascending: [3, 5, 9, 10, 12, 15, 17]
  Start at rightmost i = 6 (val 17). 17 - 15 = 2 < 4. Pair (17, 15), sum = 32. Jump to i = 4.
  i = 4 (val 12). 12 - 10 = 2 < 4. Pair (12, 10), sum = 32 + 22 = 54. Jump to i = 2.
  i = 2 (val 9). 9 - 5 = 4 (Not < 4). Jump to i = 1.
  i = 1 (val 5). 5 - 3 = 2 < 4. Pair (5, 3), sum = 54 + 8 = 62.
- Time Complexity: O(N log N) dominated by sorting. Array traversal is O(N).
- Space Complexity: O(1) auxiliary space.
- Why better than previous method: Avoids the O(N) space overhead of DP while achieving the same optimal result.
- When to use: When local optimal choices (taking the largest possible valid pairs) lead to a global optimum.

Comparison Table:
Method | TC         | SC   | Best Use Case
---------------------------------------------------
1. DP  | O(N log N) | O(N) | When constraints might invalidate a pure greedy approach (not the case here).
2. Greedy| O(N log N) | O(1) | Always preferred for this problem due to zero extra space.

Final Recommended Solution: Method 2 (Greedy Approach)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    // Optimal Approach: Greedy Iteration after Sorting
    int sumDiffPairs(vector<int>& arr, int k) {
        // Step 1: Sort the array in ascending order
        sort(arr.begin(), arr.end());
        
        int maxSum = 0;
        int n = arr.size();
        
        // Step 2: Traverse from right to left to greedily pick the largest pairs
        int i = n - 1;
        while (i > 0) {
            // Check if the difference between current and previous element is strictly less than k
            if (arr[i] - arr[i - 1] < k) {
                // Add to sum and skip the paired element
                maxSum += arr[i] + arr[i - 1];
                i -= 2;
            } else {
                // If not valid, move to the next largest element
                i--;
            }
        }
        
        return maxSum;
    }
};

// ==========================================
// Driver Code for Local Testing
// ==========================================
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Test Case 1
    vector<int> arr1 = {3, 5, 10, 15, 17, 12, 9};
    int k1 = 4;
    cout << "Test Case 1 Output: " << sol.sumDiffPairs(arr1, k1) << "\n"; // Expected: 62
    
    // Test Case 2
    vector<int> arr2 = {5, 15, 10, 300};
    int k2 = 12;
    cout << "Test Case 2 Output: " << sol.sumDiffPairs(arr2, k2) << "\n"; // Expected: 25
    
    return 0;
}
