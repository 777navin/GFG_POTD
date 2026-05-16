/*
Date: 16-05-2026
Problem Name: Not a subset sum
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Arrays, Greedy, Data Structures

Problem Summary:
Given a sorted array of positive integers, find the smallest positive integer 
that cannot be represented as the sum of elements of any subset of the given array.

Methods to Solve:

1. Optimal Approach (Greedy Gap Finding)
- Intuition: 
  If we can represent all sums from 1 to 'res', and the next element in the 
  sorted array is 'arr[i]', we can extend our range to 'res + arr[i]' ONLY IF 
  'arr[i]' is not greater than 'res + 1'. If 'arr[i] > res + 1', then 'res + 1' 
  is the smallest unreachable sum.
- Approach:
  1. Initialize `res = 1` (the smallest positive integer we are looking for).
  2. Sort the array (if not already sorted, though GFG usually provides it sorted 
     for this specific variation, or the constraints allow sorting).
  3. Iterate through the array:
     - If `arr[i] <= res`, add `arr[i]` to `res`.
     - Else, break the loop.
  4. Return `res`.
- Dry Run (arr = [1, 2, 3]):
  - res = 1. arr[0] = 1. (1 <= 1) -> res = 1 + 1 = 2.
  - res = 2. arr[1] = 2. (2 <= 2) -> res = 2 + 2 = 4.
  - res = 4. arr[2] = 3. (3 <= 4) -> res = 4 + 3 = 7.
  - End of loop. Return 7.
- Time Complexity: O(N) for a sorted array, O(N log N) if sorting is required.
- Space Complexity: O(1)
- Why better than previous method: It avoids the exponential complexity of 
  generating all possible subset sums.
- When to use: When the array contains positive integers and you need the 
  smallest missing sum.

Comparison Table:
Method           | TC       | SC   | Best Use Case
-----------------|----------|------|---------------------------------------
Optimal (Greedy) | O(N)     | O(1) | Large arrays where subset generation is impossible.

Final Recommended Solution:
The Greedy approach is the standard optimal solution for this problem.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Finds the smallest positive integer that cannot be represented as a subset sum.
     * @param arr: Vector of positive integers
     * @return: Smallest unreachable positive integer sum
     */
    long long findSmallest(vector<int> &arr) {
        // 'res' represents the smallest positive integer we cannot currently form.
        // We can form every sum from 1 to res-1.
        long long res = 1;

        // Note: The logic assumes the array is sorted. 
        // Based on GFG's "Not a subset sum" typical constraints, 
        // if it's not guaranteed, we sort it.
        sort(arr.begin(), arr.end());

        for (int i = 0; i < arr.size(); i++) {
            // If the current element is greater than the smallest number 
            // we are trying to form, then 'res' will never be reachable.
            if (arr[i] > res) {
                break;
            }
            
            // Otherwise, we can now form all sums from 1 to (res + arr[i] - 1)
            res += arr[i];
        }

        return res;
    }
};

//{ Driver Code Starts.
int main() {
    int t;
    // Standard competitive programming loop for test cases
    if (!(cin >> t)) return 0;
    while (t--) {
        int n;
        cin >> n;
        vector<int> arr(n);
        for (int i = 0; i < n; i++) {
            cin >> arr[i];
        }
        Solution ob;
        auto ans = ob.findSmallest(arr);
        cout << ans << "\n";
    }
    return 0;
}
// } Driver Code Ends
