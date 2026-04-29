// 

/*
Date: 29-04-2026
Problem Name: Min Swaps to Group 1s
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Array, Sliding Window, Two Pointers

Problem Summary:
You are given a binary array consisting only of 0s and 1s. The objective is to 
find the minimum number of swaps required to group all the 1s together in a 
contiguous subarray. A swap operation allows exchanging any two indices. 
If the array contains no 1s, the function should return -1.

Methods to Solve:
1. Brute Force (Subarray Checking)
2. Optimal Approach (Sliding Window)

================================================================================
Method 1: Brute Force (Subarray Checking)
================================================================================
Intuition:
If we know the total number of 1s in the array (let's call it `totalOnes`), then 
the final grouped block of 1s will have exactly that size. We can check every 
possible subarray of size `totalOnes` and count how many 0s are in it. The number 
of 0s represents the number of swaps needed to fill that subarray entirely with 1s.

Approach:
- Count the total number of 1s in the array.
- If `totalOnes` is 0, return -1.
- Iterate through every valid starting index `i` of a subarray of size `totalOnes`.
- For each subarray, count the number of 0s.
- Keep track of the minimum count of 0s across all subarrays.

Dry Run (Small example): arr = [1, 0, 1, 0, 1]
- totalOnes = 3
- Subarrays of size 3:
  - [1, 0, 1] -> one 0 -> 1 swap
  - [0, 1, 0] -> two 0s -> 2 swaps
  - [1, 0, 1] -> one 0 -> 1 swap
- Minimum swaps = 1

Time Complexity: O(N * totalOnes) ≈ O(N^2) in the worst case.
Space Complexity: O(1)

Why better than previous method: It's the most basic logical deduction.
When to use: Only acceptable for very small array sizes (N <= 1000).

================================================================================
Method 2: Optimal Approach (Sliding Window)
================================================================================
Intuition:
Instead of recounting the number of 0s for every single subarray of size `totalOnes`, 
we can use a Sliding Window. As the window moves one step to the right, only two 
elements change: one element leaves the window from the left, and one element 
enters the window from the right. We can update our 0-count in O(1) time.

Approach:
1. Traverse the array to count `totalOnes`.
2. Handle edge cases: if `totalOnes == 0`, return -1. If `totalOnes == n`, return 0.
3. Form the initial window of size `totalOnes` (from index 0 to `totalOnes - 1`) 
   and count the number of 0s (current swaps needed).
4. Initialize `min_swaps` with this initial count.
5. Slide the window from `totalOnes` to the end of the array:
   - If the element leaving the window (at `i - totalOnes`) was a 0, decrement the count.
   - If the new element entering the window (at `i`) is a 0, increment the count.
   - Update `min_swaps` with the minimum of `min_swaps` and the current count.
6. Return `min_swaps`.

Dry Run: arr = [1, 0, 1, 0, 1, 1]
- totalOnes = 4. Window size = 4.
- Initial window: [1, 0, 1, 0] -> 0s count = 2. min_swaps = 2.
- Slide right by 1: leaving arr[0]=1, entering arr[4]=1.
  Window [0, 1, 0, 1] -> 0s count = 2. min_swaps = 2.
- Slide right by 1: leaving arr[1]=0 (count--), entering arr[5]=1.
  Window [1, 0, 1, 1] -> 0s count = 1. min_swaps = 1.
- End of array. Return 1.

Time Complexity: O(N) - We traverse the array exactly twice (once to count 1s, once to slide).
Space Complexity: O(1) - Only a few integer variables are used.

Why better than previous method: Reduces time complexity from quadratic to linear.
When to use: Always. This is the optimal industry-standard approach.

================================================================================
Comparison Table:
Method               | TC     | SC   | Best Use Case
---------------------|--------|------|------------------------------------------
1. Brute Force       | O(N^2) | O(1) | Never (unless N is extremely small)
2. Sliding Window    | O(N)   | O(1) | Ideal for all constraints (GFG accepted)

Final Recommended Solution: Method 2 (Sliding Window)
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSwaps(vector<int>& arr) {
        int n = arr.size();
        int totalOnes = 0;
        
        // Step 1: Count total number of 1s in the array
        for (int num : arr) {
            if (num == 1) {
                totalOnes++;
            }
        }
        
        // Edge Case: If there are no 1s, return -1 as per requirements
        if (totalOnes == 0) return -1;
        
        // Edge Case: If the array is already full of 1s
        if (totalOnes == n) return 0;
        
        // Step 2: Initialize the first window of size `totalOnes`
        int currentZeroes = 0;
        for (int i = 0; i < totalOnes; i++) {
            if (arr[i] == 0) {
                currentZeroes++;
            }
        }
        
        int minSwaps = currentZeroes;
        
        // Step 3: Slide the window across the rest of the array
        for (int i = totalOnes; i < n; i++) {
            // Remove the element going out of the window
            if (arr[i - totalOnes] == 0) {
                currentZeroes--;
            }
            
            // Add the new element coming into the window
            if (arr[i] == 0) {
                currentZeroes++;
            }
            
            // Update the minimum swaps required
            minSwaps = min(minSwaps, currentZeroes);
        }
        
        return minSwaps;
    }
};

// Driver code to test the solution locally (GitHub Ready)
int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> arr1 = {1, 0, 1, 0, 1};
    cout << "Test Case 1 Output: " << sol.minSwaps(arr1) << " (Expected: 1)\n";
    
    // Test Case 2
    vector<int> arr2 = {1, 0, 1, 0, 1, 1};
    cout << "Test Case 2 Output: " << sol.minSwaps(arr2) << " (Expected: 1)\n";
    
    // Test Case 3 (No 1s)
    vector<int> arr3 = {0, 0, 0};
    cout << "Test Case 3 Output: " << sol.minSwaps(arr3) << " (Expected: -1)\n";

    return 0;
}
