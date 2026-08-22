/*
=========================================================
Date        : 22-08-2026
Problem Name: Number of Turns in Binary Tree
Platform    : GeeksforGeeks (GFG)
Difficulty  : Hard
Tags        : Tree, LCA, DFS, Binary Tree

Problem Summary:
Given the root of a binary tree and two node values, p and q.
Count the number of turns taken on the path from p to q.
A turn is defined as a change of direction from left to right or right to left.
If no turns occur (straight line), return -1.

Key Observation:
The path between p and q passes through their Lowest Common Ancestor (LCA).
We can count turns from LCA to p and LCA to q, plus 1 turn at the LCA if neither p nor q is the LCA.
=========================================================
*/

/*
=========================================================
3. APPROACH EXPLANATION
=========================================================

Approach 1: Optimized LCA + Recursive Path Turn Counting
• Intuition:
  - Find the Lowest Common Ancestor (LCA) of p and q.
  - Traverse downwards from LCA to p and LCA to q, tracking direction changes.
  
• Approach:
  - Find the LCA of nodes p and q.
  - If p is LCA, count turns down to q. If q is LCA, count turns down to p.
  - If LCA is neither, count turns from LCA to p, turns from LCA to q, and add 1 for the turn at LCA.
  - Return -1 if total turns count is 0.

• Why it Works:
  - Tree paths between two nodes are unique and go via their LCA.
  - Counting directional transitions (left->right or right->left) along both branches accurately captures all turns.

• Time Complexity (TC):
  - O(N) where N is the number of nodes (traversal for LCA + search paths).

• Space Complexity (SC):
  - O(H) where H is the height of the binary tree (call stack space).
*/

/*
=========================================================
4. FINAL APPROACH
=========================================================
• Why this approach is chosen:
  - It runs in linear time O(N) and uses minimal recursion auxiliary space O(H).
• Why it is better:
  - Directly counts turns during tree traversal without allocating additional strings or path arrays.
*/

/* Structure of Binary Tree Node
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

class Solution {
private:
    Node* findLCA(Node* root, int p, int q) {
        if (!root || root->data == p || root->data == q) {
            return root;
        }

        Node* left = findLCA(root->left, p, q);
        Node* right = findLCA(root->right, p, q);

        if (left && right) return root;
        return left ? left : right;
    }

    bool countTurns(Node* curr, int target, bool isTurnLeft, int& turns) {
        if (!curr) return false;

        if (curr->data == target) return true;

        if (isTurnLeft) {
            if (countTurns(curr->left, target, true, turns)) {
                return true;
            }
            if (countTurns(curr->right, target, false, turns)) {
                turns++;
                return true;
            }
        } else {
            if (countTurns(curr->right, target, false, turns)) {
                return true;
            }
            if (countTurns(curr->left, target, true, turns)) {
                turns++;
                return true;
            }
        }

        return false;
    }

public:
    int numberOfTurns(Node* root, int p, int q) {
        if (!root || p == q) return -1;

        Node* lca = findLCA(root, p, q);
        if (!lca) return -1;

        int turns = 0;

        // Case 1: LCA is one of the nodes
        if (lca->data == p) {
            countTurns(lca->left, q, true, turns);
            countTurns(lca->right, q, false, turns);
            return (turns == 0) ? -1 : turns;
        }

        if (lca->data == q) {
            countTurns(lca->left, p, true, turns);
            countTurns(lca->right, p, false, turns);
            return (turns == 0) ? -1 : turns;
        }

        // Case 2: LCA is an intermediate ancestor (1 turn at LCA itself)
        countTurns(lca->left, p, true, turns);
        countTurns(lca->right, p, false, turns);

        countTurns(lca->left, q, true, turns);
        countTurns(lca->right, q, false, turns);

        return turns + 1;
    }
};
