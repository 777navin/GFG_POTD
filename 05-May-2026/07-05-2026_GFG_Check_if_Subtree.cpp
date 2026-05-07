/*
Date: 07-05-2026
Problem Name: Check if subtree
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Tree, Recursion, Data Structures

Problem Summary:
Given two binary trees root1 (T) and root2 (S), determine if S is a subtree of T. 
A subtree of T is a tree consisting of a node in T and all of its descendants.

Methods to Solve:
1. Recursive Comparison (Standard O(N*M))
2. String Serialization (KMP-based O(N+M))

---------------------------------------------------------------------------
1. Recursive Comparison (Brute Force/Optimal for average cases)

- Intuition:
  A tree S is a subtree of T if S is identical to T, or S is a subtree of T->left, 
  or S is a subtree of T->right. We need a helper function to check if two 
  trees are identical.

- Approach:
  1. Traverse tree T using recursion.
  2. For every node in T, check if the tree rooted at this node is identical to S.
  3. The `isIdentical` function checks if both nodes are null (true), one is null 
     (false), or if data matches and left/right subtrees are identical.

- Dry Run (Small Example):
  T: [1, 2, 3], S: [3]
  - Check (1, 3): Not identical.
  - Check (2, 3): Not identical.
  - Check (3, 3): Identical -> Return True.

- Time Complexity: O(N * M) 
  In the worst case (skewed trees), we might check the identity for every node.
  N = nodes in T, M = nodes in S.

- Space Complexity: O(H) 
  Where H is the height of the taller tree (recursion stack).

- Why better than previous method: 
  It is the most intuitive and memory-efficient in terms of auxiliary space.

- When to use: 
  When N and M are relatively small (up to 10^3 as per constraints).

---------------------------------------------------------------------------

Comparison Table:
Method               | TC      | SC      | Best Use Case
-------------------------------------------------------
Recursive Comparison | O(N*M)  | O(H)    | Memory-constrained environments
String Serialization | O(N+M)  | O(N+M)  | Large trees with strict time limits

Final Recommended Solution:
Recursive Comparison fits the GFG constraints perfectly and is clean for interviews.
*/

#include <iostream>
using namespace std;

/* ===================================================================
GITHUB/LOCAL RUN CODE (Commented out to prevent GFG Compiler Error)
===================================================================
struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};
*/

class Solution {
public:
    /**
     * Helper function to check if two trees are identical in structure and values.
     */
    bool isIdentical(Node* r1, Node* r2) {
        // Both null means identical
        if (!r1 && !r2) return true;
        
        // One null or data mismatch means not identical
        if (!r1 || !r2 || r1->data != r2->data) return false;

        // Recursively check left and right children
        return isIdentical(r1->left, r2->left) && 
               isIdentical(r1->right, r2->right);
    }

    /**
     * Main function to check if root2 is a subtree of root1.
     */
    bool isSubTree(Node* root1, Node* root2) {
        // If root2 is null, it's always a subtree
        if (!root2) return true;

        // If root1 is null but root2 isn't, root2 can't be a subtree
        if (!root1) return false;

        // 1. Check if tree rooted at current root1 is identical to root2
        if (isIdentical(root1, root2)) {
            return true;
        }

        // 2. If not, check if root2 is a subtree of the left or right child
        return isSubTree(root1->left, root2) || 
               isSubTree(root1->right, root2);
    }
};

/*
===================================================================
GITHUB/LOCAL RUN CODE (Commented out to prevent GFG Compiler Error)
===================================================================
int main() {
    Node* root1 = new Node(1);
    root1->left = new Node(2);
    root1->right = new Node(3);
    root1->right->left = new Node(4);

    Node* root2 = new Node(3);
    root2->left = new Node(4);

    Solution sol;
    if (sol.isSubTree(root1, root2)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    return 0;
}
*/
