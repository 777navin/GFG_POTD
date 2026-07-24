/*
=========================================================
Date        : 24-07-2026
Problem Name: Longest Consecutive Path in Binary tree
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Tree, Depth-First Search (DFS), Recursion

Problem Summary:
Given the root of a binary tree, find the maximum length of a parent-to-child 
path where each consecutive node's value is exactly 1 greater than its parent. 
If no consecutive path of length >= 2 exists, return -1.

Key Observation:
We can maintain a running count of the consecutive sequence length during a top-down 
DFS traversal, incrementing the length when node->data == parent->data + 1 and resetting 
it to 1 otherwise.
=========================================================
*/

#include <iostream>
#include <algorithm>
using namespace std;

/*
Structure of Binary Tree Node (Provided by Platform)
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};
*/

/*
=========================================================
APPROACH 1: Recursive DFS Traversal (Optimal)
=========================================================

• Intuition:
  Perform a top-down DFS traversal passing the parent node and current sequence length 
  to evaluate each node-child pair.

• Approach:
  - Traversal tracks the current consecutive path length.
  - If current node value equals parent value + 1, extend the length by 1.
  - Otherwise, reset the sequence length to 1 starting at the current node.
  - Track the global maximum length found across all paths.
  - If maximum length < 2, return -1 as required.

• Why it Works:
  Since the path must strictly follow parent-to-child direction, checking each 
  parent-child edge individually guarantees all valid consecutive paths are explored.

• Time Complexity (TC):
  O(N) - Every node in the binary tree is visited exactly once.

• Space Complexity (SC):
  O(H) - Auxiliary stack space proportional to the height of the binary tree H.
=========================================================
*/

/*
=========================================================
FINAL APPROACH CHOICE
=========================================================
• DFS traversal directly computes the consecutive sequence in a single pass.
• It operates within optimal O(N) time and O(H) auxiliary space bounds.
=========================================================
*/

class Solution {
private:
    void dfs(Node* curr, Node* parent, int currentLen, int& maxLen) {
        if (!curr) return;

        if (parent && curr->data == parent->data + 1) {
            currentLen++;
        } else {
            currentLen = 1;
        }

        maxLen = max(maxLen, currentLen);

        dfs(curr->left, curr, currentLen, maxLen);
        dfs(curr->right, curr, currentLen, maxLen);
    }

public:
    int longestConsecutive(Node* root) {
        if (!root) return -1;

        int maxLen = 0;
        dfs(root, nullptr, 0, maxLen);

        return (maxLen >= 2) ? maxLen : -1;
    }
};
