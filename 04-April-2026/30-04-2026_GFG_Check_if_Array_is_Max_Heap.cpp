/*
Date: 30-04-2026
Problem Name: Check if an Array is Max Heap
Platform: GeeksforGeeks (GFG)
Difficulty: Easy
Tags: Heap, Array, Binary Tree

-----------------------------------------------------

🧠 Problem Summary:
Given an array arr[], determine whether it represents the level-order traversal
of a valid Max Heap.

A Max Heap satisfies:
1. It is a Complete Binary Tree.
2. Every parent node is greater than or equal to its children.

Return true if it is a Max Heap, else false.

-----------------------------------------------------

🚀 Methods to Solve:

========================
1. Brute Force Approach
========================

Intuition:
- Convert array into a tree structure explicitly.
- Then check each node manually.

Approach:
- Build tree using nodes.
- Traverse and verify heap property.

Dry Run:
arr = [90, 15, 10, 7, 12, 2]
Tree formed → check each node

Time Complexity: O(N)
Space Complexity: O(N)

Why not optimal:
- Extra space for tree creation.

-----------------------------------------------------

========================
2. Better Approach
========================

Intuition:
- Instead of building tree, use array indexing.

Approach:
- For each index i:
    left child = 2*i + 1
    right child = 2*i + 2
- Check if parent >= children

Dry Run:
i = 0 → 90 ≥ 15, 10 ✅
i = 1 → 15 ≥ 7, 12 ✅
i = 2 → 10 ≥ 2 ✅

Time Complexity: O(N)
Space Complexity: O(1)

-----------------------------------------------------

========================
3. Optimal Approach (Recommended)
========================

Intuition:
- Only check non-leaf nodes.
- Leaf nodes automatically satisfy heap property.

Key Insight:
- Last non-leaf node = (n/2) - 1

Approach:
- Loop from i = 0 to (n/2 - 1)
- Check:
    if arr[i] < arr[left] OR arr[i] < arr[right] → false

Dry Run:
arr = [9, 15, 10, 7, 12, 11]
i = 0 → 9 < 15 ❌ → return false

Time Complexity: O(N)
Space Complexity: O(1)

Why Best:
- No extra space
- Minimal checks
- Clean and efficient

-----------------------------------------------------

📊 Comparison Table:

Method           | TC   | SC   | Best Use Case
-----------------------------------------------
Brute Force      | O(N) | O(N) | Learning concept
Better Approach  | O(N) | O(1) | General use
Optimal Approach | O(N) | O(1) | Best & recommended

-----------------------------------------------------

🏁 Final Recommended Solution:
- Use array index logic
- Traverse till (n/2 - 1)
- Check heap property

-----------------------------------------------------
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool isMaxHeap(vector<int> &arr) {
        int n = arr.size();

        // Traverse only non-leaf nodes
        for (int i = 0; i <= (n / 2) - 1; i++) {

            int left = 2 * i + 1;
            int right = 2 * i + 2;

            // Check left child
            if (left < n && arr[i] < arr[left]) {
                return false;
            }

            // Check right child
            if (right < n && arr[i] < arr[right]) {
                return false;
            }
        }

        return true;
    }
};

/*
-----------------------------------------------------
💡 Example:

Input:
arr = [90, 15, 10, 7, 12, 2]

Output:
true

Explanation:
Each parent node is greater than its children.

-----------------------------------------------------

Input:
arr = [9, 15, 10, 7, 12, 11]

Output:
false

Explanation:
9 < 15 → violates max heap property.

-----------------------------------------------------
*/
