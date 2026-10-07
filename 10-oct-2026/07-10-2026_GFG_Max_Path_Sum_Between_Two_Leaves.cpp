/*
=========================================================
Date        : 07-10-2026
Problem Name: Max Path Sum Between Two Leaves
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Binary Tree, Recursion, Dynamic Programming, Tree-DP

Problem Summary:
Given the root of a binary tree with integer node values, find the maximum possible path sum 
between any two leaf nodes. If the tree contains fewer than two leaf nodes, return -1.

Key Observation:
A path between two leaves passes through their Lowest Common Ancestor (LCA). At every node, 
if both left and right subtrees exist, a candidate leaf-to-leaf path sum can be formed by 
summing the max root-to-leaf paths of both subtrees along with the current node's value.
=========================================================
*/

#include <bits/stdc++.h>
using std::max;

/*
---------------------------------------------------------
APPROACH 1: Recursive Post-Order Traversal (Optimized Tree-DP)
---------------------------------------------------------

1. Intuition:
   To maximize the path sum between two leaves, we need to find a subtree node that acts as 
   the turning point (LCA) between two leaves. The maximum sum passing through a node is the sum 
   of the maximum root-to-leaf path in its left subtree, the maximum root-to-leaf path in its 
   right subtree, and the node's own value.

2. Approach:
   - Use a helper recursive function `maxPathSumUtil(root, maxi)` that returns the maximum sum 
     of a path from the current node down to a leaf in its subtree.
   - If a node is `nullptr`, return 0.
   - If a node is a leaf, return its value.
   - Recursively calculate maximum root-to-leaf path sums for the left and right subtrees.
   - If both left and right children exist:
     - Update the global maximum path sum `maxi = max(maxi, left_sum + right_sum + root->data)`.
     - Return `max(left_sum, right_sum) + root->data` to the parent.
   - If only one child exists (left or right):
     - Return `(root->left ? left_sum : right_sum) + root->data`.
   - Special Case: Handle single-line / skewed trees where fewer than two leaves exist across 
     the entire tree by using a flag/check or initial value indicator.

3. Why it Works:
   A leaf-to-leaf path requires valid leaves on both sides of the junction node. By ensuring 
   `maxi` is only updated when both left and right subtrees exist (or when valid leaves exist 
   on both sides), we enforce the "between two leaves" condition properly.

4. Time Complexity (TC):
   O(N), where N is the number of nodes in the binary tree, as each node is visited exactly once.

5. Space Complexity (SC):
   O(H), where H is the height of the binary tree, representing the recursion call stack depth 
   (O(N) in the worst case for a skewed tree, O(log N) for a balanced tree).
*/

/*
---------------------------------------------------------
FINAL APPROACH SELECTION
---------------------------------------------------------
• Chosen Approach: Recursive Post-Order Traversal (Tree-DP)
• Reason: It computes the optimal path sum in a single O(N) traversal bottom-up without repeating 
  computations, satisfying both time and space efficiency requirements.
---------------------------------------------------------
*/

/* 
Tree Node Structure (provided by GFG platform):
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
*/

class Solution {
private:
    int maxPathToLeaf(Node* root, int &maxi) {
        if (!root) return 0;
        
        // Base case: leaf node
        if (!root->left && !root->right) {
            return root->data;
        }

        int leftSum = maxPathToLeaf(root->left, maxi);
        int rightSum = maxPathToLeaf(root->right, maxi);

        // If both left and right subtrees exist, we can form a leaf-to-leaf path through root
        if (root->left && root->right) {
            maxi = max(maxi, leftSum + rightSum + root->data);
            return max(leftSum, rightSum) + root->data;
        }

        // If only one child exists, path must go through that existing child
        return (!root->left ? rightSum : leftSum) + root->data;
    }

public:
    int maxPathSum(Node* root) {
        int maxi = INT_MIN;
        int val = maxPathToLeaf(root, maxi);

        // Special case: If the root itself has only one child and no leaf-to-leaf path was updated,
        // but both subtrees overall contain at least two leaves (e.g. root has only left child, 
        // but left child splits into 2 leaves).
        if (maxi == INT_MIN) {
            // Check if tree has less than two leaves altogether
            return -1;
        }

        return maxi;
    }
};
