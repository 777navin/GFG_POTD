/*
=========================================================
Date        : 23-07-2026
Problem Name: Check Preorder of BST
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Binary Search Tree, Stack, Data Structures

Problem Summary:
Given an array of distinct integers, determine whether it represents the preorder 
traversal of a valid Binary Search Tree (BST). In preorder traversal, nodes are 
visited in the order: Root -> Left -> Right.

Key Observation:
In a BST preorder traversal, whenever we encounter a value greater than the previous values, 
we are moving to a right subtree. All subsequent elements in the array must be greater than 
the root of this right subtree.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Recursive Simulation (Brute Force)
---------------------------------------------------------
• Intuition:
  Find the first element greater than the root to divide the array into left and right subtrees, 
  then recursively verify that all elements in the right subtree are greater than the root.

• Approach:
  1. Pick the first element as root.
  2. Find index 'i' of the first element greater than root.
  3. Verify all elements from index 'i' to end are strictly greater than root.
  4. Recursively apply the same logic to the left and right sub-arrays.

• Why it Works:
  It directly checks the fundamental BST property (left child < root < right child) recursively for every subtree.

• Time Complexity (TC): O(N^2) in the worst case (e.g., skewed tree).
• Space Complexity (SC): O(N) auxiliary stack space due to recursion depth.
*/

/*
---------------------------------------------------------
APPROACH 2: Monotonic Stack (Optimal)
---------------------------------------------------------
• Intuition:
  Use a stack to simulate traversal. When we encounter a value greater than the stack top, 
  we pop elements to find the last popped node (which serves as the lower bound for all future elements).

• Approach:
  1. Initialize `root = INT_MIN` and an empty stack.
  2. Iterate through each element in the array:
     a. If current element < `root`, return false (violates BST property).
     b. While stack is not empty and stack top < current element:
        Pop elements and set `root` to the popped value.
     c. Push current element onto the stack.
  3. If iteration completes without violation, return true.

• Why it Works:
  Popping elements from the stack signifies moving to a right child. The last popped element represents 
  the parent/ancestor root, ensuring that all remaining elements fall into its right subtree and must be greater than it.

• Time Complexity (TC): O(N) because each element is pushed and popped at most once.
• Space Complexity (SC): O(N) to store elements in the explicit stack.
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
• We choose Approach 2 (Monotonic Stack).
• It runs in linear O(N) time complexity, efficiently handling input size constraints up to N = 10^5,
  whereas the recursive brute force approach would TLE with O(N^2) complexity.
=========================================================
*/

#include <vector>
#include <stack>
#include <climits>

using namespace std;

class Solution {
  public:
    bool canRepresentBST(vector<int>& arr) {
        int root = INT_MIN;
        stack<int> st;

        for (int val : arr) {
            // If we find a node in the right subtree smaller than its root, it's not a BST
            if (val < root) {
                return false;
            }

            // Pop elements smaller than val to find the parent/ancestor root
            while (!st.empty() && st.top() < val) {
                root = st.top();
                st.pop();
            }

            // Push current value to stack
            st.push(val);
        }

        return true;
    }
};
