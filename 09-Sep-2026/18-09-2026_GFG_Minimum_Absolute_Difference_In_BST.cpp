/*
=========================================================
Date        : 18-09-2026
Problem Name: Minimum Absolute Difference In BST
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Binary Search Tree, Tree, Inorder Traversal

Problem Summary:
- Given the root of a Binary Search Tree (BST) containing n nodes.
- Find the minimum absolute difference between the values of any two different nodes in the tree.
- Return the minimum absolute difference value.

Key Observation:
- The inorder traversal of a BST yields nodes in sorted order.
- The minimum absolute difference between any two nodes in a BST will always occur between adjacent elements in its sorted inorder traversal.
=========================================================
*/

/*
Approach 1: Inorder Traversal with Vector Storage
- Intuition: Store all node values using an inorder traversal and then find the minimum difference between adjacent elements.
- Approach:
  1. Perform a recursive inorder traversal to collect all node values into a vector.
  2. Since the vector will be sorted, iterate through adjacent pairs and find the minimum difference.
- Why it Works: Inorder traversal of a BST guarantees sorted sequence, making adjacent comparisons sufficient.
- Time Complexity (TC): O(n) where n is the number of nodes in the BST.
- Space Complexity (SC): O(n) to store the node values in a vector.
*/

/*
Approach 2: Optimized Inorder Traversal (Constant Extra Space)
- Intuition: Instead of storing all elements, keep track of the previously visited node during the inorder traversal.
- Approach:
  1. Initialize a pointer or variable `prev` with a null/invalid state and `min_diff` with infinity.
  2. Perform an inorder traversal (Left -> Root -> Right).
  3. For each node, if `prev` is not null, update `min_diff = min(min_diff, current->data - prev->data)`.
  4. Update `prev` to the current node and continue.
- Why it Works: Avoids extra space by computing the difference on-the-fly during the naturally sorted traversal.
- Time Complexity (TC): O(n) to visit each node once.
- Space Complexity (SC): O(h) recursion stack space, where h is the height of the BST.
*/

/*
Final Approach Chosen:
- We choose the Optimized Inorder Traversal (Approach 2) because it avoids allocating an extra vector to store values, reducing auxiliary space complexity from O(n) to O(h) while keeping the time complexity at O(n).
*/

#include <bits/stdc++.h>
using namespace std;

/* Binary Tree Node Structure
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
    void inorder(Node* root, Node*& prev, int& min_diff) {
        if (!root) return;
        
        inorder(root->left, prev, min_diff);
        
        if (prev != nullptr) {
            min_diff = min(min_diff, root->data - prev->data);
        }
        prev = root;
        
        inorder(root->right, prev, min_diff);
    }

public:
    int absDiff(Node *root) {
        Node* prev = nullptr;
        int min_diff = INT_MAX;
        inorder(root, prev, min_diff);
        return min_diff;
    }
};
