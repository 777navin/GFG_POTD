/*
=========================================================
Date        : 12-11-2026
Problem Name: Closest in BST
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Binary Search Tree, Tree, DFS

Problem Summary:
Find the minimum absolute difference between a given
integer K and the value of any node in a BST.

Key Observation:
BST property allows us to eliminate half of the
remaining search space at every step.
=========================================================

APPROACH 1: BRUTE FORCE (Inorder Traversal)

- Intuition:
  Inorder traversal visits every node in sorted order.

- Approach:
  Traverse the entire BST and calculate the minimum
  absolute difference with K.

- Why it Works:
  Every node is checked, so the minimum is guaranteed.

- TC: O(N)
- SC: O(H) recursion stack.


APPROACH 2: OPTIMIZED (BST Search)

- Intuition:
  BST ordering helps us decide which subtree to explore.

- Approach:
  Start from root, update minimum difference and:
  - If K < node->data, move left.
  - Otherwise, move right.
  - If equal, return 0.

- Why it Works:
  The discarded subtree cannot contain a closer value
  than the candidate found along the search path.

- TC: O(H)
- SC: O(1)


FINAL APPROACH:
- Use iterative BST traversal.
- Avoids visiting unnecessary nodes.
- Uses constant auxiliary space instead of recursion.
=========================================================
*/

class Solution {
public:
    int minDiff(Node* root, int k) {

        int ans = INT_MAX;
        Node* curr = root;

        while (curr != nullptr) {

            ans = min(ans, abs(curr->data - k));

            if (ans == 0) {
                return 0;
            }

            if (k < curr->data) {
                curr = curr->left;
            }
            else {
                curr = curr->right;
            }
        }

        return ans;
    }
};
