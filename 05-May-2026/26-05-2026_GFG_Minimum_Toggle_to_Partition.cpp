/*
Date: 26-05-2026
Problem Name: Minimum Toggle to Partition
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Array, Prefix Sum, Greedy

Problem Summary:
Given an array containing only 0s and 1s, find the minimum number of toggles (changing 0 to 1 or 1 to 0) 
required to partition the array such that all 0s appear before all 1s.

Methods to Solve:
1. Brute Force
2. Optimal Approach (Prefix/Suffix Counting)

For EACH method include:

Method 1: Brute Force
- Intuition: Check every possible partition index where we divide the array into a left part (all 0s) and a right part (all 1s).
- Approach: For each index `i` from -1 to N-1, iterate through the left side to count 1s (needs to be toggled to 0) and iterate through the right side to count 0s (needs to be toggled to 1). Add both counts for the current split and take the minimum across all possible splits.
- Dry Run: On arr = [1, 0, 1]. 
  - Partition at -1 (all 1s): right needs 1 toggle (0 at index 1). Cost = 1.
  - Partition at 0: left needs 1 toggle (1 at index 0), right needs 0. Cost = 1.
- Time Complexity: O(N^2)
- Space Complexity: O(1)
- Why better than previous method: N/A
- When to use: When N is extremely small and optimization isn't necessary.

Method 2: Optimal Approach (Prefix/Suffix Counting)
- Intuition: Instead of recounting for every partition, we can maintain the counts dynamically in a single pass. Total toggles at partition `i` = (1s on left) + (0s on right).
- Approach: 
  1. Count the total number of 0s in the array (`total_zeros`).
  2. The initial cost if the partition is *before* the first element (meaning we want the whole array to be 1s) is simply `total_zeros` (since every 0 must flip to 1).
  3. Initialize `min_toggles` with `total_zeros`.
  4. Iterate through the array keeping track of `ones_so_far` and `zeros_so_far`.
  5. At index `i`, if we partition here, the toggles needed will be `ones_so_far` (to make the left all 0s) + `total_zeros - zeros_so_far` (to make the right all 1s).
  6. Update `min_toggles` with the minimum cost found.
- Dry Run: arr = [1, 0, 1, 1, 0]
  - total_zeros = 2
  - min_toggles initialized to 2 (partition before index 0).
  - i=0 (arr[0]=1): ones_so_far=1, zeros_so_far=0. cost = 1 + 2 - 0 = 3. min_toggles = min(2, 3) = 2.
  - i=1 (arr[1]=0): ones_so_far=1, zeros_so_far=1. cost = 1 + 2 - 1 = 2. min_toggles = min(2, 2) = 2.
  - i=2 (arr[2]=1): ones_so_far=2, zeros_so_far=1. cost = 2 + 2 - 1 = 3. min_toggles = min(2, 3) = 2.
  - Result: 2.
- Time Complexity: O(N) where N is the size of the array.
- Space Complexity: O(1) as we use only a few integer variables.
- Why better than previous method: Reduces time complexity from quadratic to linear by caching the sum.
- When to use: Always optimal for this problem, highly scalable for N up to 10^5.

Comparison Table:
Method           | TC     | SC   | Best Use Case
-----------------|--------|------|---------------------------------------
Brute Force      | O(N^2) | O(1) | Small arrays
Optimal Approach | O(N)   | O(1) | Standard CP execution (Constraints up to 10^5)

Final Recommended Solution: Optimal Approach
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// GFG Class Format
class Solution {
public:
    int minToggle(vector<int>& arr) {
        int n = arr.size();
        int total_zeros = 0;
        
        // Count total zeros in the array
        for (int i = 0; i < n; i++) {
            if (arr[i] == 0) {
                total_zeros++;
            }
        }
        
        // Initial case: partition before index 0 (all elements should become 1s)
        int min_toggles = total_zeros;
        
        int ones_so_far = 0;
        int zeros_so_far = 0;
        
        // Iterate and test every partition index `i`
        for (int i = 0; i < n; i++) {
            if (arr[i] == 1) {
                ones_so_far++;
            } else {
                zeros_so_far++;
            }
            
            // Toggles needed = (1s on the left) + (0s on the right)
            int current_toggles = ones_so_far + (total_zeros - zeros_so_far);
            min_toggles = min(min_toggles, current_toggles);
        }
        
        return min_toggles;
    }
};

// Driver Code for standalone execution and testing
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int t;
    // Reading from competitive programming standard input
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<int> arr(n);
            for (int i = 0; i < n; i++) {
                cin >> arr[i];
            }
            
            Solution obj;
            cout << obj.minToggle(arr) << "\n";
        }
    } else {
        // Fallback testing for direct IDE runs without standard inputs
        Solution obj;
        
        vector<int> arr1 = {1, 0, 1, 1, 0};
        cout << "Test Case 1: " << obj.minToggle(arr1) << "\n"; // Expected Output: 2
        
        vector<int> arr2 = {0, 1, 0, 0, 1, 1, 1};
        cout << "Test Case 2: " << obj.minToggle(arr2) << "\n"; // Expected Output: 1
    }
    
    return 0;
}
