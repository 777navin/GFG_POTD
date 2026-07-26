/*
=========================================================
Date        : 26-07-2026
Problem Name: Complete Binary Tree Traversal with Array Input
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Tree, Array, Sorting

Problem Summary:
Given an array representing a complete binary tree in level-order 
traversal, group the nodes by their level and sort each level in 
ascending order. Return the result as a 2D array.

Key Observation:
Since the tree is complete, the number of nodes at level 'i' is exactly 2^i, 
except possibly for the last level which will hold any remaining nodes. 
The input array is already level-by-level contiguous.
=========================================================
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/*
=========================================================
APPROACH 1: Grouping by Level Capacity & Sorting (Most Optimal)
=========================================================
* Intuition:
  - In a complete binary tree given in level order, level 0 has 1 node, 
    level 1 has 2 nodes, level 2 has 4 nodes, and so on.
  - We can traverse the array and slice it into contiguous chunks of sizes 
    1, 2, 4, 8... up to the array's end.

* Approach:
  - Initialize an index `i` to 0 and `levelSize` to 1.
  - While `i` is less than the total number of elements:
    - Collect up to `levelSize` elements starting from `i` into a temporary vector.
    - Sort this temporary vector.
    - Push the sorted vector into our final 2D result.
    - Multiply `levelSize` by 2 for the next level.
  - Return the 2D result.

* Why it Works:
  - Complete binary trees are strictly populated left-to-right on every level.
  - Hence, the array slice matches exactly the nodes present at that specific level.

* Time Complexity (TC): 
  - O(N log N) where N is the total number of elements. In the worst-case, 
    we are sorting all elements across different levels.
    
* Space Complexity (SC): 
  - O(N) to store the 2D result array and the intermediate level vectors.
=========================================================
*/

/*
=========================================================
FINAL APPROACH CHOSEN
=========================================================
The grouping and sorting approach is chosen because it directly 
exploits the mathematical properties of a complete binary tree represented 
in an array. It avoids the overhead of actually building a tree structure, 
making it both time and space optimal for this problem.
=========================================================
*/

class Solution {
public:
    vector<vector<int>> levelSort(vector<int>& arr) {
        vector<vector<int>> result;
        int n = arr.size();
        int i = 0;
        int currentLevelCapacity = 1;
        
        while (i < n) {
            vector<int> currentLevelNodes;
            int count = 0;
            
            // Extract nodes for the current level up to its capacity or array end
            while (i < n && count < currentLevelCapacity) {
                currentLevelNodes.push_back(arr[i]);
                i++;
                count++;
            }
            
            // Sort the nodes at the current level independently
            sort(currentLevelNodes.begin(), currentLevelNodes.end());
            
            // Add the sorted level to our result
            result.push_back(currentLevelNodes);
            
            // The capacity of the next level in a complete binary tree is double
            currentLevelCapacity *= 2;
        }
        
        return result;
    }
};
