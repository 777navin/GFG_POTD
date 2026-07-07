/*
=========================================================
Date        : 07-07-2026
Problem Name: Largest Unblocked Submatrix
Platform    : GeeksforGeeks
Difficulty  : Medium
Tags        : Sorting, Two Pointers, Greedy

Problem Summary:
Given an n x m grid with k blocked cells. Each blocked cell (r, c)
renders its entire row 'r' and column 'c' unusable. Find the area
of the largest continuous unblocked rectangular submatrix.

Key Observation:
Since no two blocked cells share a row or column, the problem reduces to 
finding the largest gap between blocked row indices and blocked column indices.
=========================================================
*/

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

/*
APPROACH:

1. Optimized (Sorting)
   - Intuition: Each blocked cell effectively splits the remaining grid into 
     smaller rectangles. Because no two blocked cells share a row or column,
     we can independently find the maximum gap between consecutive row/column 
     indices after sorting them.
   - Approach: 
     1. Store all blocked rows in a vector and add boundary values (0 and n+1).
     2. Store all blocked columns in a vector and add boundary values (0 and m+1).
     3. Sort both vectors.
     4. Find the maximum difference between consecutive elements in both vectors.
     5. The result is (max_row_gap - 1) * (max_col_gap - 1).
   - Why it Works: The grid is partitioned by lines that cannot be crossed.
     The largest rectangular area is formed by the largest empty strip of rows
     multiplied by the largest empty strip of columns.
   - Time Complexity: O(k log k) due to sorting the blocked indices.
   - Space Complexity: O(k) to store the indices.
*/

class Solution {
public:
    int largestArea(int n, int m, vector<vector<int>>& arr) {
        vector<int> rows = {0, n + 1};
        vector<int> cols = {0, m + 1};

        for (const auto& p : arr) {
            rows.push_back(p[0]);
            cols.push_back(p[1]);
        }

        sort(rows.begin(), rows.end());
        sort(cols.begin(), cols.end());

        int max_r = 0;
        for (size_t i = 1; i < rows.size(); ++i) {
            max_r = max(max_r, rows[i] - rows[i - 1] - 1);
        }

        int max_c = 0;
        for (size_t i = 1; i < cols.size(); ++i) {
            max_c = max(max_c, cols[i] - cols[i - 1] - 1);
        }

        return max_r * max_c;
    }
};

/*
FINAL APPROACH:
The chosen approach is optimal because sorting the k blocked positions 
takes O(k log k). Calculating the gaps is a linear pass. This is 
significantly more efficient than simulating the grid, especially 
since constraints allow n, m up to 10^4.
*/

// Filename: 07-07-2026_GFG_Largest_Unblocked_Submatrix.cpp
