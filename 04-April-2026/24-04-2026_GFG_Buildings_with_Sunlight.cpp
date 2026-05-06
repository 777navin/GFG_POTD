/*
File Name: 24-04-2026_GFG_Buildings_with_Sunlight.cpp

Date: 24-04-2026
Problem Name: Buildings with Sunlight
Platform: GeeksforGeeks
Difficulty: Easy
Tags: Array, Traversal, Prefix Maximum, Greedy

Problem Summary:
Given an array arr[] representing heights of buildings placed adjacent
to each other. Sunlight comes from the left side.

A building receives sunlight if no taller building exists before it.
Find the total number of buildings that receive sunlight.

------------------------------------------------------------

Methods to Solve:

1. Brute Force
- For every building, check all previous buildings.
- If current building is greater than all previous, count it.

Time: O(n^2)
Space: O(1)

2. Better / Optimal Approach (Prefix Maximum)
- First building always receives sunlight.
- Keep track of maximum height seen so far.
- If current height >= maxHeight:
    it receives sunlight
    update maxHeight

Time: O(n)
Space: O(1)

------------------------------------------------------------

Dry Run:

arr = [6, 2, 8, 4, 11, 13]

6 -> visible (count=1, max=6)
2 -> hidden
8 -> visible (count=2, max=8)
4 -> hidden
11 -> visible (count=3, max=11)
13 -> visible (count=4, max=13)

Answer = 4

------------------------------------------------------------

Comparison Table:

Method              TC       SC      Best Use
Brute Force         O(n^2)   O(1)    Small arrays
Optimal             O(n)     O(1)    Best for all inputs

------------------------------------------------------------

Final Recommended Solution:
Use one pass with running maximum.

*/

class Solution {
public:
    int visibleBuildings(vector<int>& arr) {
        int n = arr.size();
        if (n == 0) return 0;

        int count = 1;              // First building always visible
        int maxHeight = arr[0];

        for (int i = 1; i < n; i++) {
            if (arr[i] >= maxHeight) {
                count++;
                maxHeight = arr[i];
            }
        }

        return count;
    }
};
