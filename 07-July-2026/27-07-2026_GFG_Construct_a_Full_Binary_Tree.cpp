/*
=========================================================
Date        : 27-07-2026
Problem Name: Construct a Full Binary Tree
Platform:     GeeksforGeeks (GFG)
Difficulty:   Medium
Tags:         Tree, Data Structures, Binary Tree

Problem Summary:
Given the preorder traversal of a full binary tree (pre[]) and its mirror 
tree (preMirror[]), we need to uniquely construct the original tree.

Key Observation:
In a full binary tree, every internal node has exactly 2 children. We can find 
the left child in the mirror traversal to perfectly divide the tree into left 
and right subtrees.

Error Resolution:
The previous compilation error ("redefinition of 'class Node'") occurred 
because GeeksforGeeks already defines the `Node` structure and driver code 
in their backend. To fix this while keeping the file GitHub-ready, the 
driver code and Node structure are now commented out for GFG submission.
=========================================================
*/

/*
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 1: Recursive Partitioning without HashMap (Better)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  The first element is the root. The next element in `pre` is the left child.
  In `preMirror`, the right subtree comes before the left subtree.
• Approach:
  Find the left child in `preMirror` using a linear search. This index acts 
  as a partition boundary to determine the sizes of the left and right subtrees.
• Why it Works:
  A full binary tree guarantees nodes have 2 children, meaning subtrees can be 
  strictly isolated by finding the opposite child's bounds in the mirror traversal.
• Time Complexity (TC):
  O(N^2) worst case, due to searching the element linearly at every recursive step.
• Space Complexity (SC):
  O(N) for the recursive call stack space.

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
APPROACH 2: Recursive Partitioning with HashMap (Most Optimal)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
• Intuition:
  We can optimize the linear search for the left child by pre-storing the 
  indices of `preMirror` in a hash map.
• Approach:
  Map each value in `preMirror` to its index. During recursion, get the 
  boundary index for the left child in O(1) time, then split and recurse.
• Why it Works:
  It removes the inner loop from the recursive function, effectively turning 
  the recurrence relation into a linear traversal.
• Time Complexity (TC):
  O(N) since each node is processed exactly once with an O(1) lookup.
• Space Complexity (SC):
  O(N) to store elements in the hash map and O(N) for recursion depth.
*/

// =========================================================
// FINAL APPROACH
// =========================================================
// We use the Most Optimal Approach (Recursive Partitioning with HashMap).
// It reduces the time complexity from O(N^2) to O(N), which is necessary 
// to pass the constraints of N = 10^5 without Time Limit Exceeded (TLE).

#include <bits/stdc++.h>
using namespace std;

/* 
=========================================================
UNCOMMENT THIS BLOCK FOR LOCAL GITHUB TESTING ONLY
(GeeksforGeeks backend already defines this)
=========================================================
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
    Node* buildTree(vector<int>& pre, vector<int>& preMirror, int preStart, int preEnd, 
                    int mirrorStart, int mirrorEnd, unordered_map<int, int>& mirrorMap) {
        
        // Base cases
        if (preStart > preEnd) return nullptr;
        Node* root = new Node(pre[preStart]);
        if (preStart == preEnd) return root;

        // The left child is immediately after the root in preorder
        int leftChild = pre[preStart + 1];
        
        // Find the index of the left child in the mirror preorder
        int mirrorLeftStart = mirrorMap[leftChild];
        
        // Calculate the sizes of right and left subtrees
        int sizeRight = mirrorLeftStart - mirrorStart - 1;
        int sizeLeft = (preEnd - preStart) - sizeRight;

        // Recursively build left and right subtrees
        root->left = buildTree(pre, preMirror, 
                               preStart + 1, preStart + sizeLeft, 
                               mirrorLeftStart, mirrorEnd, 
                               mirrorMap);
                               
        root->right = buildTree(pre, preMirror, 
                                preStart + sizeLeft + 1, preEnd, 
                                mirrorStart + 1, mirrorLeftStart - 1, 
                                mirrorMap);

        return root;
    }

public:
    Node* constructBinaryTree(vector<int>& pre, vector<int>& preMirror) {
        unordered_map<int, int> mirrorMap;
        
        // Pre-compute indices of elements in preMirror for O(1) lookup
        for (int i = 0; i < preMirror.size(); i++) {
            mirrorMap[preMirror[i]] = i;
        }
        
        return buildTree(pre, preMirror, 0, pre.size() - 1, 0, preMirror.size() - 1, mirrorMap);
    }
};

/*
=========================================================
UNCOMMENT THIS BLOCK FOR LOCAL GITHUB TESTING ONLY
(GeeksforGeeks backend already defines driver functions)
=========================================================
void printInorder(Node* node) {
    if (!node) return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    if (cin >> t) {
        while (t--) {
            int n;
            cin >> n;
            vector<int> pre(n);
            for (int i = 0; i < n; i++) cin >> pre[i];
            
            vector<int> preMirror(n);
            for (int i = 0; i < n; i++) cin >> preMirror[i];

            Solution obj;
            Node* root = obj.constructBinaryTree(pre, preMirror);
            
            printInorder(root);
            cout << "\n";
        }
    } else {
        vector<int> pre = {0, 1, 2};
        vector<int> preMirror = {0, 2, 1};
        
        Solution obj;
        Node* root = obj.constructBinaryTree(pre, preMirror);
        
        cout << "Inorder Traversal of Constructed Tree: ";
        printInorder(root);
        cout << "\n";
    }

    return 0;
}
*/
