// File Name: 10-06-2026_GFG_Binary_Searchable_Count.cpp

/*
Date: 10-06-2026
Problem Name: Binary Searchable Count
Platform: GeeksforGeeks (GFG)
Difficulty: Medium
Tags: Binary Search, Divide and Conquer, Trees, Arrays

Problem Summary:
Given an array arr[] of n distinct integers, find the count of elements that 
can be successfully found using a standard, deterministic binary search 
algorithm (where mid = (l + r) / 2).

Methods to Solve:
1. Brute Force (Simulation)
   - Simulating the binary search function explicitly for every single element.
   - Intuition: Check each element manually by running the binary search routine.
   - Time Complexity: O(N log N)
   - Space Complexity: O(1)
   - When to use: When constraints are small (N <= 10^4).

2. Optimal Approach (Binary Search Decision Tree Traversal)
   - Intuition: The indices visited by standard binary search form a fixed 
     decision tree structure. When we move left from a 'mid', every valid target 
     in that left subtree must be strictly less than arr[mid]. When we move right, 
     every valid target must be strictly greater than arr[mid].
   - Approach: Perform a Pre-order DFS traversal mirroring the binary search splits. 
     Maintain a valid `(min_val, max_val)` range. If arr[mid] falls within this range, 
     it is binary searchable.
   - Time Complexity: O(N)
   - Space Complexity: O(N) auxiliary space for the recursion stack.
   - Why better than previous method: It avoids redundant work, visiting each element exactly once.
   - When to use: Ideal for large constraints (N = 10^5).

Comparison Table:
Method         | TC       | SC   | Best Use Case
---------------|----------|------|-----------------
Brute Force    | O(N log N)| O(1) | Small arrays
Optimal (DFS)  | O(N)     | O(N) | Maximum efficiency for N = 10^5

Final Recommended Solution: Optimal Approach (DFS Tree Traversal)
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
private:
    /**
     * @brief Helper function to traverse the binary search decision tree.
     * * @param l Lower bound of the current search space
     * @param r Upper bound of the current search space
     * @param min_val The strict lower bound value constraint inherited from ancestors
     * @param max_val The strict upper bound value constraint inherited from ancestors
     * @param arr Reference to the original array
     * @param count Reference to the searchable element counter
     */
    void traverseTree(int l, int r, int min_val, int max_val, const vector<int>& arr, int& count) {
        if (l > r) return;

        // Calculate mid exactly matching the platform's standard implementation
        int mid = l + (r - l) / 2;

        // If the current element satisfies the constraints set by all its ancestors path,
        // it means the binary search path will successfully land here.
        if (arr[mid] > min_val && arr[mid] < max_val) {
            count++;
        }

        // When moving left, all target elements must be smaller than the current arr[mid]
        traverseTree(l, mid - 1, min_val, min(max_val, arr[mid]), arr, count);

        // When moving right, all target elements must be greater than the current arr[mid]
        traverseTree(mid + 1, r, max(min_val, arr[mid]), max_val, arr, count);
    }

public:
    int binarySearchable(vector<int>& arr) {
        int count = 0;
        int n = arr.size();
        
        if (n == 0) return 0;
        
        // Initiate the traversal across the entire array space
        traverseTree(0, n - 1, INT_MIN, INT_MAX, arr, count);
        
        return count;
    }
};

// Driver code compatible for local execution and quick validation
int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Solution solver;

    // Test Case 1 (Failing case mentioned: 3 2 1)
    vector<int> arr1 = {3, 2, 1};
    cout << "Test Case 1 Output: " << solver.binarySearchable(arr1) << " (Expected: 1)\n";

    // Test Case 2 (Standard Example)
    vector<int> arr2 = {2, 1, 3, 5, 4, 6};
    cout << "Test Case 2 Output: " << solver.binarySearchable(arr2) << " (Expected: 4)\n";

    return 0;
}
