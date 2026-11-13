/*
=========================================================
Date        : 13-11-2026
Problem Name: Common Nodes in Two BSTs
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Binary Search Tree, Tree, Data Structures

Problem Summary:
Given the roots r1 and r2 of two Binary Search Trees (BSTs), find all nodes 
that are present in both trees (i.e., intersection nodes). Return the common 
node values sorted in ascending order.

Key Observation:
An in-order traversal of a BST yields elements in sorted order. We can either 
merge in-order traversals or simulate iterative in-order traversals using two 
stacks simultaneously to achieve dynamic comparison in O(H1 + H2) auxiliary space.
=========================================================
*/

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
// Definition for a Binary Search Tree node provided by the platform:
class Node {
public:
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};
*/

/*
=========================================================
APPROACH EXPLANATION
=========================================================

1. Brute Force (Store In-order & Linear Search / Hashing)
   • Intuition: Store in-order traversal of both BSTs in arrays and find common elements using a set/hash table.
   • Approach: Traverse r1 into array A, traverse r2 into array B, then use a hash set to collect common elements.
   • Why it Works: In-order traversal collects all values, and hash lookups check for presence in O(1) time.
   • Time Complexity (TC): O(N1 + N2)
   • Space Complexity (SC): O(N1 + N2) to store traversal elements and hash set.

2. Optimized (Simultaneous Iterative In-order Traversal)
   • Intuition: Perform iterative in-order traversals of both BSTs concurrently using stacks.
   • Approach: Push left-most nodes onto stacks s1 and s2. Compare top nodes: advance the tree with smaller top element, or record common value and advance both when tops match.
   • Why it Works: Generates nodes of both BSTs in sorted order on-the-fly, allowing two-pointer style matching without storing full tree traversals in arrays.
   • Time Complexity (TC): O(N1 + N2)
   • Space Complexity (SC): O(H1 + H2) where H1 and H2 are the heights of the two trees.
=========================================================
*/

/*
=========================================================
FINAL APPROACH SELECTION
=========================================================
• We choose Simultaneous Iterative In-order Traversal using stacks.
• It processes nodes in sorted order dynamically with O(H1 + H2) space complexity.
• This avoids storing entire tree node values into intermediate vectors/hash sets.
=========================================================
*/

class Solution {
public:
    vector<int> findCommon(Node *r1, Node *r2) {
        vector<int> result;
        stack<Node*> s1, s2;

        while (true) {
            // Push left nodes of tree 1
            while (r1 != nullptr) {
                s1.push(r1);
                r1 = r1->left;
            }

            // Push left nodes of tree 2
            while (r2 != nullptr) {
                s2.push(r2);
                r2 = r2->left;
            }

            // If both stacks are empty, traversal is complete
            if (s1.empty() || s2.empty()) {
                break;
            }

            Node* top1 = s1.top();
            Node* top2 = s2.top();

            if (top1->data == top2->data) {
                result.push_back(top1->data);
                s1.pop();
                s2.pop();
                r1 = top1->right;
                r2 = top2->right;
            } 
            else if (top1->data < top2->data) {
                s1.pop();
                r1 = top1->right;
                r2 = nullptr; // keep r2 null so s2 retains state
            } 
            else {
                s2.pop();
                r2 = top2->right;
                r1 = nullptr; // keep r1 null so s1 retains state
            }
        }

        return result;
    }
};
