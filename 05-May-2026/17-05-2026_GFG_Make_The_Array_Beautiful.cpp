/*
Date: 17-05-2026
Problem Name: Make the array beautiful
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Stack, Data Structures, Arrays

Problem Summary:
Given an array of negative and non-negative integers, make the array "beautiful". 
An array is beautiful if no two adjacent elements have different signs (i.e., one is negative and the other is positive).
If two adjacent elements have different signs, they must be removed. This removal process should be done from 
left to right to maintain consistency with the test cases. An empty array is also considered beautiful.

Methods to Solve:
1. Brute Force (Iterative Erasure)
2. Optimal Approach (Using Stack / Vector Simulation)

--------------------------------------------------------------------------------

1. Brute Force (Iterative Erasure)
- Intuition: Repeatedly scan the array from left to right. Whenever two adjacent elements with opposite signs are found, remove them using `vector::erase` and restart or continue scanning until no such pairs remain.
- Approach: Use a loop that sets a flag `changed = false`. Iterate through the vector, check if `(arr[i] >= 0 && arr[i+1] < 0) || (arr[i] < 0 && arr[i+1] >= 0)`. If true, erase both elements, set `changed = true`, and break or adjust the pointer. Repeat until `changed` remains false.
- Dry Run: arr = [4, 2, -2, 1]
  - Scan: 4 and 2 (same sign) -> ok.
  - Scan: 2 and -2 (diff sign) -> erase 2 and -2. Array becomes [4, 1].
  - Next scan: 4 and 1 (same sign) -> ok. No more changes. Output: [4, 1].
- Time Complexity: O(N^2) because each erasure operation takes O(N) time and we might perform it O(N) times.
- Space Complexity: O(1) auxiliary space if performed in-place.
- Why better than previous method: N/A (Baseline method).
- When to use: Only when constraints are extremely small (e.g., N <= 100).

--------------------------------------------------------------------------------

2. Optimal Approach (Using Stack / Vector Simulation)
- Intuition: This problem follows a typical "elimination of adjacent elements" pattern, perfectly suited for a Stack data structure. Instead of an actual `std::stack`, we can use a `std::vector` to simulate the stack operations, which avoids a final reverse operation when returning the result.
- Approach: 
  - Initialize an empty vector `res` to act as our stack.
  - Iterate through each element `x` of the input array.
  - If `res` is not empty, check the sign of the top element `res.back()` against the current element `x`.
  - If one is negative and the other is non-negative, they cancel each other out: pop the top element from `res`.
  - Otherwise, push `x` into `res`.
  - Return `res`.
- Dry Run: arr = [4, 2, -2, 1]
  - x = 4: stack is empty -> push 4. [stack: 4]
  - x = 2: stack top (4 >= 0) and x (2 >= 0) -> same sign -> push 2. [stack: 4, 2]
  - x = -2: stack top (2 >= 0) and x (-2 < 0) -> diff sign -> pop 2. [stack: 4]
  - x = 1: stack top (4 >= 0) and x (1 >= 0) -> same sign -> push 1. [stack: 4, 1]
  - Loop ends. Output: [4, 1].
- Time Complexity: O(N) as we traverse the array exactly once, performing O(1) push/pop operations per element.
- Space Complexity: O(N) to store the elements in the resulting vector/stack.
- Why better than previous method: Reduces time complexity drastically from quadratic O(N^2) to linear O(N), allowing it to easily pass within the 1-second limit for N = 10^5.
- When to use: Always preferred for tracking dynamic adjacent relationships and pairs matching.

--------------------------------------------------------------------------------

Comparison Table:
Method       | TC     | SC     | Best Use Case
---------------------------------------------------------
Brute Force  | O(N^2) | O(1)   | Small inputs (N <= 100)
Optimal Stack| O(N)   | O(N)   | Large inputs (N <= 10^5) [Recommended]

Final Recommended Solution: Optimal Approach using Vector as a Stack.
*/

#include <iostream>
#include <vector>

class Solution {
public:
    std::vector<int> makeBeautiful(std::vector<int> arr) {
        std::vector<int> res; // Using vector to simulate stack efficiently
        
        for (int x : arr) {
            if (res.empty()) {
                res.push_back(x);
            } else {
                // Check if one is non-negative and the other is negative
                if ((res.back() >= 0 && x < 0) || (res.back() < 0 && x >= 0)) {
                    res.pop_back(); // Remove the adjacent element with a different sign
                } else {
                    res.push_back(x); // Same sign, safely push to stack
                }
            }
        }
        
        return res;
    }
};
