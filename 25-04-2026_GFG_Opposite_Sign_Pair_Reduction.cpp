/*
Date: 25-04-2026
Problem Name: Opposite Sign Pair Reduction
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Stack, Array, Simulation, Two Pointers

Problem Summary:
Given an array of integers, repeatedly reduce adjacent elements if they have opposite signs.
1. If |a| != |b|, remove both and keep the one with the larger absolute value (preserve sign).
2. If |a| == |b|, remove both.
The process continues from left to right until no more reductions are possible.

Methods to Solve:

1. Brute Force (Iterative Rescan):
   - Intuition: Repeatedly scan the array for adjacent opposite signs. Perform reduction and restart the scan.
   - TC: O(N^2) - In the worst case, one reduction occurs per scan.
   - SC: O(N) to store intermediate results.
   - When to use: Only for very small constraints (N < 1000).

2. Optimal Approach (Stack-based Simulation):
   - Intuition: Use a stack to track elements. When a new element comes, check if it "collides" 
     with the top of the stack (opposite signs). Resolve all collisions before moving to the next element.
   - Approach: 
     a. Traverse array. For each 'curr', check the stack top.
     b. If signs are opposite, compare absolute values.
     c. Pop from stack if stack top is smaller; destroy 'curr' if it's smaller; pop and destroy if equal.
   - Dry Run (arr = [10, -5, -8]):
     - result = [10]. Next is -5. 10 and -5 opposite signs. |10| > |-5|. -5 destroyed.
     - result = [10]. Next is -8. 10 and -8 opposite signs. |10| > |-8|. -8 destroyed.
     - Output: [10].
   - Time Complexity: O(N) - Each element is pushed and popped at most once.
   - Space Complexity: O(N) - To store the result stack.
   - Why better: Reduces time complexity from quadratic to linear by avoiding repeated rescans.
   - When to use: Best for large constraints (N up to 10^6).

Comparison Table:
Method         | TC     | SC     | Best Use Case
---------------|--------|--------|--------------------------
Brute Force    | O(N^2) | O(N)   | Small inputs / Educational
Stack Optimal  | O(N)   | O(N)   | Production / Competitive

Final Recommended Solution: Stack-based Approach (Linear Time).
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Reduces the array by resolving collisions between adjacent opposite-sign integers.
     * * @param arr Input vector of integers.
     * @return Reduced vector of integers.
     */
    vector<int> reducePairs(vector<int>& arr) {
        // We use a vector as a stack for O(1) tail operations and easy return format.
        vector<int> result;
        
        for (int curr : arr) {
            bool currentDestroyed = false;
            
            // Logic: Collision occurs only if signs are different.
            // (top > 0 && curr < 0) OR (top < 0 && curr > 0)
            while (!result.empty() && ((result.back() > 0 && curr < 0) || (result.back() < 0 && curr > 0))) {
                
                // Use long long to handle absolute value of INT_MIN without overflow
                long long topAbs = abs(static_cast<long long>(result.back()));
                long long currAbs = abs(static_cast<long long>(curr));
                
                if (currAbs > topAbs) {
                    // Top of stack is smaller, it gets destroyed. 
                    // Continue checking 'curr' against the new top.
                    result.pop_back();
                } 
                else if (currAbs == topAbs) {
                    // Both are equal, both are destroyed.
                    result.pop_back();
                    currentDestroyed = true;
                    break;
                } 
                else {
                    // Current element is smaller, it gets destroyed.
                    currentDestroyed = true;
                    break;
                }
            }
            
            // If current element was not destroyed by any collisions, add to stack.
            if (!currentDestroyed) {
                result.push_back(curr);
            }
        }
        
        return result;
    }
};

// --- Driver Code for GFG/Local Testing ---
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution sol;
    
    // Example 1
    vector<int> arr1 = {10, -5, -8, 2, -5};
    vector<int> res1 = sol.reducePairs(arr1);
    // Expected Output: [10]
    for (int x : res1) cout << x << " ";
    cout << endl;

    return 0;
}
