/*
Date: 28-05-2026
Problem Name: Vertical Sum
Platform: GeeksforGeeks
Difficulty: Medium
Tags: Binary Tree, Hash Map, DFS, BFS, Doubly Linked List

Problem Summary:
Given a binary tree having n nodes, find the vertical sum of the nodes that are in the same vertical line. 
Return all sums through different vertical lines starting from the left-most vertical line to the right-most vertical line.

Methods to Solve:
1. Map with DFS (Standard Approach)
2. Map with BFS (Level Order)
3. Doubly Linked List (Highly Optimal - Avoids Map overhead)

For EACH method include:

Method 1: Map with DFS
- Intuition: Each node exists at a specific horizontal distance (HD) from the root. The root is at HD 0, the left child is at HD - 1, and the right child is at HD + 1. We can use a map to accumulate the sum of node values at each HD.
- Approach: Traverse the tree using Depth-First Search (DFS). Keep passing the current HD down the recursive calls. Add the current node's value to the map at its corresponding HD. Maps in C++ are naturally sorted by key, so iterating through the map at the end yields the sums strictly from left to right.
- Dry Run: 
  Tree:      1 (HD 0)
           /   \
 (HD -1) 2       3 (HD +1)
  Map state during traversal: {-1: 2, 0: 1, +1: 3}. 
  Result extracted: [2, 1, 3]
- Time Complexity: O(N log W) where N is the number of nodes and W is the max width (due to O(log W) map insertions).
- Space Complexity: O(W) for the map + O(H) for the recursion stack.
- Why better than previous method: Standard, intuitive, and the most universally accepted approach.
- When to use: When standard constraints allow O(N log W) time and you need a fast, readable implementation.

Method 2: Map with BFS
- Intuition: Operates on the same principle as DFS, but uses level-order traversal.
- Approach: Use a queue that stores pairs of `{Node*, HD}`. Traverse the tree level by level, updating the map at the current HD.
- Dry Run: Queue: [{1, 0}] -> map[0]+=1. Pop 1, push {2, -1}, {3, 1}. map[-1]+=2, map[1]+=3.
- Time Complexity: O(N log W)
- Space Complexity: O(N) for queue in the worst-case width + O(W) for the map.
- Why better than previous method: Avoids recursion stack overflow risks for heavily skewed trees.
- When to use: When the tree depth is massive and recursive space complexity is a concern.

Method 3: Doubly Linked List (Optimal Space/Time)
- Intuition: Instead of a map (which takes O(log W) per insertion), maintain a Doubly Linked List (DLL) where each node represents an independent vertical line. 
- Approach: As we traverse left recursively, move to the `prev` node in the DLL (create it dynamically if it is null). If we traverse right, move to the `next` node. After traversal, walk to the absolute head of the DLL and collect the accumulated values sequentially.
- Dry Run: Root(1) creates DLLNode(1). Go left to 2: creates DLLNode(2)<-DLLNode(1). etc.
- Time Complexity: O(N) - completely removes the O(log W) map insertion overhead.
- Space Complexity: O(W) for DLL nodes + O(H) for the recursion stack.
- Why better than previous method: Reduces time complexity from O(N log W) to true O(N).
- When to use: When dealing with extremely strict time limits where standard C++ map operations trigger Time Limit Exceeded (TLE).

Comparison Table:
Method       | TC         | SC       | Best Use Case
Map + DFS    | O(N log W) | O(W + H) | Fast implementation, standard interview solution
Map + BFS    | O(N log W) | O(N + W) | Very deep trees to avoid stack overflow
DLL + DFS    | O(N)       | O(W + H) | Strict time constraints, showing advanced DS mastery

Final Recommended Solution: 
Method 1 (Map + DFS) is the primary recommended solution due to its brevity and standard acceptance on platforms like GFG. Method 3 (DLL) is provided in the code below as an alternative to demonstrate advanced optimization.
*/

#include <iostream>
#include <vector>
#include <map>

using namespace std;

#if 0 
// =========================================================================
// LOCAL TESTING SETUP (Ignored by GFG compiler to prevent redefinition)
// To run on your local machine, change '#if 0' to '#if 1'
// =========================================================================
struct Node {
    int data;
    Node *left, *right;
    Node(int item) {
        data = item;
        left = right = nullptr;
    }
};
#endif

class Solution {
private:
    // Helper function for Method 1: DFS approach
    void dfs(Node* root, int hd, map<int, int>& hdSum) {
        if (root == nullptr) return;
        
        // Add the current node's data to the corresponding horizontal distance
        hdSum[hd] += root->data;
        
        // Traverse left (HD - 1) and right (HD + 1)
        dfs(root->left, hd - 1, hdSum);
        dfs(root->right, hd + 1, hdSum);
    }

public:
    // Method 1: Map + DFS (Primary standard Solution)
    vector<int> verticalSum(Node *root) {
        map<int, int> hdSum;
        vector<int> result;
        
        // Populate the map using DFS starting at HD 0
        dfs(root, 0, hdSum);
        
        // The map automatically iterates from the smallest key (left-most) 
        // to the largest key (right-most)
        for (auto const& [hd, sum] : hdSum) {
            result.push_back(sum);
        }
        
        return result;
    }
};

#if 0 
// =========================================================================
// LOCAL DRIVER CODE (Ignored by GFG compiler to prevent redefinition)
// To run on your local machine, change '#if 0' to '#if 1'
// =========================================================================
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // Constructing the GFG Example 1 Tree:
    //         1
    //       /   \
    //      2     3
    //     / \   / \
    //    4   5 6   7
    
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    
    Solution sol;
    vector<int> result = sol.verticalSum(root);
    
    cout << "Vertical Sum Output:\n";
    for(int val : result) {
        cout << val << " ";
    }
    cout << "\n";
    
    return 0;
}
#endif
