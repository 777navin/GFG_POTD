/*
Date: 22-06-2026
Problem Name: Maximum Area Between Bars (Dam of Candies)
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Two Pointers, Array, Greedy

Problem Summary:
Given an array `height[]` where `height[i]` represents the height of the i-th bar, 
find the maximum rectangular area that can be formed by selecting any two bars. 
The area is calculated as: min(height[i], height[j]) * (number of bars between them).
Number of bars between index i and j (where i < j) is calculated as: (j - i - 1).

Methods to Solve:
1. Brute Force
2. Two Pointer Approach (Optimal)

Method 1: Brute Force
- Intuition: Check every possible pair of bars and calculate the area.
- Approach: Use nested loops to iterate through all pairs (i, j) where i < j.
  Maintain a variable `maxArea` and update it with `min(height[i], height[j]) * (j - i - 1)`.
- Time Complexity: O(N^2)
- Space Complexity: O(1)

Method 2: Two Pointer Approach (Optimal)
- Intuition: Start with the widest possible gap (first and last bars). To potentially 
  increase the area, we must move the pointer pointing to the shorter bar, as moving the 
  taller one will only decrease the width without the possibility of increasing height 
  sufficient to compensate.
- Approach:
  1. Initialize `left = 0`, `right = n - 1`, `maxArea = 0`.
  2. While `left < right`:
     a. `width = right - left - 1`. (Crucial difference: number of bars BETWEEN them)
     b. `h = min(height[left], height[right])`.
     c. `maxArea = max(maxArea, h * width)`.
     d. If `height[left] < height[right]`, increment `left`. Else, decrement `right`.
- Time Complexity: O(N)
- Space Complexity: O(1)

Comparison Table:
Method | TC    | SC   | Best Use Case
-------|-------|------|--------------
Brute  | O(N^2)| O(1) | Small constraints
Optimal| O(N)  | O(1) | Large arrays (General purpose)

Final Recommended Solution: Two Pointer Approach
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

class Solution {
public:
    /**
     * Calculates the maximum area between two bars.
     * @param height A vector of integers representing bar heights.
     * @return The maximum area possible.
     */
    int maxArea(vector<int>& height) {
        int n = height.size();
        int left = 0;
        int right = n - 1;
        int max_water = 0;

        while (left < right) {
            // Calculate width as the number of bars strictly BETWEEN left and right
            int width = right - left - 1;
            
            // Height is bounded by the shorter bar
            int h = min(height[left], height[right]);
            
            // Update maximum area
            max_water = max(max_water, h * width);
            
            // Move the pointer of the shorter bar to find a potentially taller bar
            if (height[left] < height[right]) {
                left++;
            } else {
                right--;
            }
        }
        
        return max_water;
    }
};

// Driver code for local testing
int main() {
    Solution sol;
    
    // Test Case 1
    vector<int> height1 = {2, 5, 4, 3, 7};
    cout << "Test Case 1 Maximum Area: " << sol.maxArea(height1) << endl; // Expected: 10
    
    // Test Case 2
    vector<int> height2 = {1, 3, 4};
    cout << "Test Case 2 Maximum Area: " << sol.maxArea(height2) << endl; // Expected: 1

    return 0;
}
