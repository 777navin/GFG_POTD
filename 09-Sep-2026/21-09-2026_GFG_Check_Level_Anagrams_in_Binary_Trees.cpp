/*
=========================================================
Date        : 21-09-2026
Problem Name: Check Level Anagrams in Binary Trees
Platform    : GeeksforGeeks (GFG)
Difficulty  : Medium
Tags        : Tree, BFS, Hash Table, Queue

Problem Summary:
Given the roots of two binary trees root1 and root2, determine if the nodes 
at every corresponding level are anagrams of each other. Two levels are anagrams 
if they share the exact same values with identical frequencies.

Key Observation:
Performing a simultaneous level-order traversal (BFS) allows us to compare 
the multiset of node values at each level using frequency counts or sorting.
=========================================================
*/

/*
---------------------------------------------------------
APPROACH 1: BFS with Sorting at Each Level
---------------------------------------------------------
• Intuition:
  Traverse both trees level by level. At each level, collect the values of 
  nodes into two separate lists, sort them, and check if they are identical.

• Approach:
  1. Use two queues to run BFS on both trees simultaneously.
  2. If the number of nodes at the current level differs, return false.
  3. Store values in vectors, sort both vectors, and compare.
  4. Repeat until all levels are processed.

• Why it Works:
  Sorting arranges the multiset in a canonical order, making anagram verification 
  a direct linear equality check.

• Time Complexity (TC):
  O(N log K), where N is the total number of nodes and K is the maximum width of the tree.
• Space Complexity (SC):
  O(W), where W is the maximum width of the tree to store queue and level elements.

---------------------------------------------------------
APPROACH 2: BFS with Hash Map / Frequency Counting (Optimal)
---------------------------------------------------------
• Intuition:
  Instead of sorting the level vectors, track value counts using an unordered map 
  to achieve linear time per level.

• Approach:
  1. Initialize two queues with root1 and root2 respectively.
  2. At each level, verify both queues have the same size. If not, return false.
  3. For each node in tree1, increment its count in an unordered_map; for tree2, decrement it.
  4. After visiting the current level, ensure all counts in the map are zero.
  5. If both queues become empty at the same time, return true; otherwise, return false.

• Why it Works:
  An anagram test simply requires identical multiset frequencies; incrementing for one 
  tree and decrementing for the other reduces the check to verifying all net counts equal zero.

• Time Complexity (TC):
  O(N) average time, visiting each node and map entry once.
• Space Complexity (SC):
  O(W), where W is the maximum width of the tree.
*/

/*
=========================================================
FINAL APPROACH: BFS with Hash Map Frequency Counting
=========================================================
• Achieves strict linear O(N) average time without the overhead of O(K log K) sorting.
• Handles arbitrary node values (up to 10^6) cleanly using an unordered hash map.
• Memory footprint remains bounded by the maximum level width O(W).
*/

#include <queue>
#include <unordered_map>

/*
Structure of binary tree Node
class Node {
public:
    int data;
    Node *left, *right;
    Node(int x) {
        data = x;
        left = right = nullptr;
    }
};
*/

class Solution {
public:
    bool areAnagrams(Node *root1, Node *root2) {
        // Base edge cases
        if (!root1 && !root2) return true;
        if (!root1 || !root2) return false;

        std::queue<Node*> q1, q2;
        q1.push(root1);
        q2.push(root2);

        while (!q1.empty() && !q2.empty()) {
            int n1 = q1.size();
            int n2 = q2.size();

            // Unequal number of nodes at the current level
            if (n1 != n2) return false;

            std::unordered_map<int, int> freq;

            for (int i = 0; i < n1; ++i) {
                Node* curr1 = q1.front();
                q1.pop();
                freq[curr1->data]++;

                if (curr1->left) q1.push(curr1->left);
                if (curr1->right) q1.push(curr1->right);

                Node* curr2 = q2.front();
                q2.pop();
                freq[curr2->data]--;

                if (curr2->left) q2.push(curr2->left);
                if (curr2->right) q2.push(curr2->right);
            }

            // Verify if current level elements are anagrams
            for (const auto& entry : freq) {
                if (entry.second != 0) {
                    return false;
                }
            }
        }

        return q1.empty() && q2.empty();
    }
};
