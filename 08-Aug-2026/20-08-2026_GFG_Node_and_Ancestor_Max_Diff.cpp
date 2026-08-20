/*
=========================================================
Date        : 20-08-2026
Problem Name: Node and Ancestor Max Diff
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Tree, Binary Tree, DFS, Recursion

Problem Summary:
Given the root of a binary tree, find the maximum value of (A - B)
where node A is an ancestor of node B.

Key Observation:
For each node A, the maximum difference (A - B) is achieved when B is 
the minimum value node in the entire subtree rooted at A.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: Brute Force (Check all descendants for each node)
---------------------------------------------------------
• Intuition:
  For every node A, traverse its entire left and right subtrees to find the minimum value B, then compute (A->data - B).

• Approach:
  1. For each node, run a helper DFS to find the minimum value among all descendants.
  2. Compute (node->data - min_descendant) and update the global maximum.
  3. Recurse for left and right children.

• Why it Works:
  Directly checks all valid ancestor-descendant pairs as defined by the problem.

• Time Complexity (TC) : O(N^2) in worst case (skewed tree).
• Space Complexity (SC): O(H) recursion stack space, where H is tree height.
---------------------------------------------------------
*/

/*
---------------------------------------------------------
APPROACH 2: Post-order Traversal (Bottom-Up Optimal)
---------------------------------------------------------
• Intuition:
  Instead of re-scanning subtrees, each subtree can return its minimum value to its parent.

• Approach:
  1. Recursively compute the minimum value in the left and right subtrees.
  2. The minimum descendant value for the current node is min(left_min, right_min).
  3. Update max difference with (current->data - min_descendant).
  4. Return min(current->data, min_descendant) to the parent.

• Why it Works:
  Post-order traversal processes children before parents, providing the exact minimum descendant value in O(1) time per node.

• Time Complexity (TC) : O(N) since each node is visited once.
• Space Complexity (SC): O(H) auxiliary stack space for recursion.
---------------------------------------------------------
*/

/*
=========================================================
FINAL APPROACH: Bottom-Up Post-Order DFS
=========================================================
• Why this approach is chosen:
  It visits every node exactly once, reducing time complexity from O(N^2) to O(N).
  It computes the subtree minimum bottom-up and updates the maximum difference on the fly.
=========================================================
*/

/*
Structure of Binary Tree Node
class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};
*/

#include <algorithm>
#include <climits>

class Solution {
private:
    int maxDifference;

    int solve(Node* root) {
        if (!root) return INT_MAX;

        // If it's a leaf node, it has no descendants
        if (!root->left && !root->right) {
            return root->data;
        }

        // Find minimum value in left and right subtrees
        int leftMin = solve(root->left);
        int rightMin = solve(root->right);

        int minDescendant = std::min(leftMin, rightMin);

        // Update maximum difference (Ancestor - Descendant)
        maxDifference = std::max(maxDifference, root->data - minDescendant);

        // Return minimum value in the subtree rooted at current node
        return std::min(root->data, minDescendant);
    }

public:
    int maxDiff(Node* root) {
        maxDifference = INT_MIN;
        solve(root);
        return maxDifference;
    }
};
