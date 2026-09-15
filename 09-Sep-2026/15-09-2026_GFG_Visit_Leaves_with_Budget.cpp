/*
=========================================================
Date        : 15-09-2026
Problem Name: Visit Leaves with Budget
Platform    : GeeksforGeeks
Difficulty  : Easy
Tags        : Binary Tree, Greedy, BFS, Sorting

Problem Summary:
Given a binary tree, visit the maximum number of leaf nodes such that
the total sum of their levels (cost) does not exceed a given budget k.

Key Observation:
To maximize the total number of leaves visited, we must always greedily 
pick the leaves that are at the lowest levels first (least cost).
=========================================================
*/

/*
=========================================================
Approach 1: BFS + Greedy Sorting (Most Optimal)
=========================================================
• Intuition:
  To maximize the count of visited leaves, we need to minimize the cost spent per leaf.
  By extracting the levels (costs) of all leaf nodes and sorting them, we can greedily 
  choose the cheapest leaves first until we run out of budget.

• Approach:
  1. Perform a Level Order Traversal (BFS) starting with the root at level 1.
  2. Whenever a leaf node (no left or right child) is encountered, store its level in a list.
  3. Sort the list of accumulated leaf levels in ascending order.
  4. Iterate through the sorted costs and greedily subtract each from k until k is exhausted, incrementing the count.

• Why it Works:
  Sorting guarantees that we are picking the absolute minimum possible cost at each step. 
  This leaves the maximum possible remaining budget for subsequent leaves, effectively 
  maximizing the total count.

• Time Complexity (TC):
  O(N + L log L) where N is the total number of nodes and L is the number of leaf nodes.
  In the worst case, TC is bounded by O(N log N).

• Space Complexity (SC):
  O(N) for storing the levels of leaf nodes in a vector and for the BFS queue.
=========================================================
*/

/*
=========================================================
Final Approach:
We choose the BFS + Greedy Sorting approach because it efficiently maps 
all leaves to their costs and optimally selects the maximum count. 
It cleanly satisfies both time and space constraints for tree traversal.
=========================================================
*/

#include <bits/stdc++.h>
using namespace std;

/* Binary Tree Node Structure
class Node {
public:
    int data;
    Node *left;
    Node *right;
    Node(int x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};
*/

class Solution {
public:
    int getCount(Node *root, int k) {
        if (!root) return 0;

        vector<int> leafLevels;
        queue<pair<Node*, int>> q;
        
        // Start BFS with root at level 1
        q.push({root, 1});

        while (!q.empty()) {
            auto [curr, level] = q.front();
            q.pop();

            // Check if current node is a leaf node
            if (!curr->left && !curr->right) {
                leafLevels.push_back(level);
            }

            // Push children with incremented level
            if (curr->left) q.push({curr->left, level + 1});
            if (curr->right) q.push({curr->right, level + 1});
        }

        // Sort leaf levels to apply the greedy approach
        sort(leafLevels.begin(), leafLevels.end());

        int count = 0;
        for (int cost : leafLevels) {
            if (k >= cost) {
                k -= cost;
                count++;
            } else {
                // If we can't afford the current cheapest leaf, we can't afford any others
                break;
            }
        }

        return count;
    }
};
