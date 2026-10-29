/*
=========================================================
Date        : 29-10-2026
Problem Name: Optimal File Merge
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Greedy, Heap, Priority Queue

Problem Summary:
- Given an array of file sizes, merge all files into one.
- Merging files of sizes x and y costs x + y.
- Return the minimum total merging cost.

Key Observation:
- Always merge the two smallest files first.
- A min-heap efficiently retrieves the two smallest sizes.
=========================================================

APPROACH 1: BRUTE FORCE
- Intuition:
  Merge the two smallest files at every step.
- Approach:
  Find the two minimum elements by scanning the array,
  remove them, and insert their sum.
- Why it Works:
  Greedily merging the smallest files minimizes total cost.
- Time Complexity (TC): O(n^2)
- Space Complexity (SC): O(n)

APPROACH 2: OPTIMIZED MIN-HEAP
- Intuition:
  A min-heap always provides the smallest file sizes.
- Approach:
  1. Insert every file size into a min-heap.
  2. Extract the two smallest sizes.
  3. Add their sum to the total cost.
  4. Insert the merged size back into the heap.
  5. Repeat until one file remains.
- Why it Works:
  The optimal merge pattern always combines the two
  smallest available files, as in Huffman merging.
- Time Complexity (TC): O(n log n)
- Space Complexity (SC): O(n)

FINAL APPROACH:
- Use the min-heap for efficient minimum extraction.
- It improves repeated linear scans to logarithmic operations.
- The solution follows the exact GFG class-based format.
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
  public:
    int minComputation(vector<int>& files) {
        priority_queue<int, vector<int>, greater<int>> minHeap;

        for (int file : files) {
            minHeap.push(file);
        }

        int totalCost = 0;

        while (minHeap.size() > 1) {
            int first = minHeap.top();
            minHeap.pop();

            int second = minHeap.top();
            minHeap.pop();

            int mergedSize = first + second;
            totalCost += mergedSize;

            minHeap.push(mergedSize);
        }

        return totalCost;
    }
};
