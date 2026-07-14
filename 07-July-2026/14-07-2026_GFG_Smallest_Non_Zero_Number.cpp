/*
=========================================================
Date        : 14-07-2026
Problem Name: Smallest Non-Zero Number
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Binary Search, Greedy, Algorithms

Problem Summary:
Given an array arr[], find the smallest positive integer x such that when 
processed sequentially through the array, it never becomes negative. 
If x > arr[i], x increases by (x - arr[i]). If x <= arr[i], x decreases by (arr[i] - x).

Key Observation:
The rules boil down to a simple transformation: new_x = 2 * x - arr[i]. 
Since this function is monotonically increasing with respect to x, we can use 
either a reverse linear scan or binary search to find the minimum starting value.
=========================================================
*/

#include <vector>
#include <algorithm>

/*
=========================================================
APPROACH 1: Binary Search on Answer
=========================================================
• Intuition:
  - The final value of x after processing depends monotonically on the initial value. 
  - If a starting value x works, any value greater than x will also work. This allows 
    us to binary search for the minimum valid x.

• Approach:
  - Define a search space for x from 1 to the maximum element in the array (or a safe upper bound).
  - For each mid value, simulate the process element by element.
  - If x drops below 0 during simulation, mid is too small. If it survives, mid is a candidate, 
    so we try smaller values.
  - Cap x during simulation to prevent integer overflow since x can grow exponentially.

• Why it Works:
  - The monotonicity ensures that the predicate function `isValid(x)` changes from 
    false to true at exactly one point, which is our answer.

• Time Complexity (TC): 
  - O(N * log(Max_Element)), where N is the size of the array and Max_Element is the maximum value in arr.
• Space Complexity (SC): 
  - O(1), as it only uses a few variables for simulation.
*/

/*
=========================================================
APPROACH 2: Backward Linear Scan (Most Optimal)
=========================================================
• Intuition:
  - We can trace the transition rule backward. The forward transition is: 
    next_x = 2 * x - arr[i] => 2 * x = next_x + arr[i] => x = (next_x + arr[i]) / 2.
  - Since x must be an integer and we want the minimum initial value, any fractional 
    part must be rounded up to ensure x is sufficient.

• Approach:
  - Start from the end of the array. At the very end (after the last element), 
    the minimum safe value for x to remain non-negative is 0.
  - Move backward from index n-1 down to 0, updating x at each step:
    x = (x + arr[i] + 1) / 2 (integer division equivalent to ceiling division).
  - The value of x after processing index 0 will be the minimum required starting value.

• Why it Works:
  - By working backward, we eliminate the need to guess or binary search the initial value. 
  - The ceiling division guarantees that we compute the exact minimum integer value required 
    at each step to not fall below the required threshold for the subsequent steps.

• Time Complexity (TC): 
  - O(N), where N is the size of the array, because we iterate through the array exactly once.
• Space Complexity (SC): 
  - O(1), as the calculation is done in place using a single tracking variable.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
Approach 2 (Backward Linear Scan) is chosen for the final code.
It reduces the time complexity from O(N log M) to a strict O(N) linear time solution.
It bypasses potential overflow handling required during forward simulation in Binary Search.
*/

class Solution {
public:
    int find(std::vector<int>& arr) {
        long long x = 0; // Represents the required value after the current element
        
        // Traverse the array backward to find the initial starting value
        for (int i = arr.size() - 1; i >= 0; --i) {
            // Reverse transition: x_prev = ceil((x_curr + arr[i]) / 2)
            x = (x + arr[i] + 1) / 2;
        }
        
        // If the calculated minimum starting value is 0, return 1 as we need a non-zero number
        return x == 0 ? 1 : x;
    }
};
