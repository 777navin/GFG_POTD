/*
Date: 06-05-2026
Problem Name: Size of Binary Tree
Platform: GeeksforGeeks
Difficulty: Basic
Tags: Tree, Binary Tree, Data Structures, Recursion, BFS, DFS

Problem Summary: 
Given the root of a binary tree, calculate and return the total number of nodes present in the tree.

Methods to Solve:
1. Recursive Approach (Depth-First Search)
2. Iterative Approach (Breadth-First Search / Level Order Traversal)

-------------------------------------------------------------------
Method 1: Recursive Approach (Depth-First Search)
-------------------------------------------------------------------
- Intuition: 
  A binary tree's total size can be broken down into smaller subproblems. The total number of nodes is the current node (1) plus the number of nodes in its left subtree, plus the number of nodes in its right subtree.

- Approach: 
  1. Base case: If the current node is NULL, return 0.
  2. Recursive step: Recursively call the function for the left child and right child.
  3. Return 1 + size of left subtree + size of right subtree.

- Dry Run: 
  Tree:      1
           /   \
          2     3
  getSize(1) -> 1 + getSize(2) + getSize(3)
  getSize(2) -> 1 + getSize(NULL) + getSize(NULL) -> 1 + 0 + 0 = 1
  getSize(3) -> 1 + getSize(NULL) + getSize(NULL) -> 1 + 0 + 0 = 1
  getSize(1) -> 1 + 1 + 1 = 3. Return 3.

- Time Complexity: O(N), where N is the number of nodes in the tree. We visit every node exactly once.
- Space Complexity: O(H), where H is the height of the tree due to auxiliary stack space used by recursion. In the worst case (skewed tree), H = N, so space is O(N). For a balanced tree, space is O(log N).
- Why better than previous method: It is the most natural, concise, and standard way to traverse a tree. No explicit data structures are needed.
- When to use: When you need a simple, readable solution and stack overflow is not a concern (tree height is manageable).

-------------------------------------------------------------------
Method 2: Iterative Approach (Breadth-First Search)
-------------------------------------------------------------------
- Intuition: 
  Instead of using the call stack, we can use an explicit queue to traverse the tree level by level. Every time we pop a node from the queue, we count it.

- Approach: 
  1. If the root is NULL, return 0.
  2. Initialize a queue and push the root node into it. Initialize a `count` variable to 0.
  3. While the queue is not empty:
     a. Pop the front node and increment `count`.
     b. If the popped node has a left child, push it to the queue.
     c. If the popped node has a right child, push it to the queue.
  4. Return `count`.

- Dry Run:
  Tree:      1
           /   \
          2     3
  Queue: [1], Count: 0
  Pop 1. Count: 1. Push 2, 3. Queue: [2, 3]
  Pop 2. Count: 2. Push NULL, NULL. Queue: [3]
  Pop 3. Count: 3. Push NULL, NULL. Queue: []
  Queue is empty. Return Count: 3.

- Time Complexity: O(N), as we visit every node exactly once.
- Space Complexity: O(W), where W is the maximum width of the tree. In the worst case (a perfect binary tree), the lowest level has N/2 nodes, so the space complexity is O(N).
- Why better than previous method: Avoids the risk of stack overflow errors on extremely deep/skewed trees.
- When to use: When tree depth is exceptionally large and recursive call stack limits might be exceeded.

-------------------------------------------------------------------
Comparison Table:
Method      | TC   | SC   | Best Use Case
-------------------------------------------------------------------
Recursive   | O(N) | O(H) | Standard binary trees, highly readable code.
Iterative   | O(N) | O(W) | Very deep or skewed trees where stack overflow is a risk.

Final Recommended Solution: 
The Recursive Approach is standard for this problem due to its simplicity and elegance, fitting well within typical tree constraints.
*/

#include <iostream>
#include <queue>

using namespace std;

// Definition for a binary tree node (Included for GitHub completeness).
// NOTE: Comment out this struct when pasting into GeeksforGeeks to avoid redefinition errors.
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};

class Solution {
public:
    // Optimal Approach: Recursive DFS
    int getSize(Node* node) {
        // Base case: if tree is empty
        if (node == NULL) {
            return 0;
        }
        
        // Return 1 (current node) + size of left subtree + size of right subtree
        return 1 + getSize(node->left) + getSize(node->right);
    }

    // Alternative Approach: Iterative BFS (Level Order Traversal)
    int getSizeIterative(Node* node) {
        if (node == NULL) {
            return 0;
        }
        
        int count = 0;
        queue<Node*> q;
        q.push(node);
        
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            count++; // Increment count for each node processed
            
            if (current->left != NULL) {
                q.push(current->left);
            }
            if (current->right != NULL) {
                q.push(current->right);
            }
        }
        
        return count;
    }
};

/*
// Driver Code for Local Testing (GitHub Ready)
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // Constructing the tree for Example 1:
    //      1
    //    /   \
    //   2     3
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    
    Solution obj;
    
    cout << "Testing Recursive Approach...\n";
    int sizeRec = obj.getSize(root);
    cout << "Size of the Binary Tree: " << sizeRec << "\n";
    
    cout << "\nTesting Iterative Approach...\n";
    int sizeIter = obj.getSizeIterative(root);
    cout << "Size of the Binary Tree: " << sizeIter << "\n";
    
    // Clean up memory
    delete root->left;
    delete root->right;
    delete root;
    
    return 0;
}
*/
